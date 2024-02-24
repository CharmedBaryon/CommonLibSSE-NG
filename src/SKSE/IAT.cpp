#include "SKSE/IAT.h"

#include "SKSE/Logger.h"

#include "REX/W32/KERNEL32.h"

namespace SKSE
{
	std::uintptr_t GetIATAddr(std::string_view a_dll, std::string_view a_function)
	{
		return reinterpret_cast<std::uintptr_t>(GetIATPtr(std::move(a_dll), std::move(a_function)));
	}

	std::uintptr_t GetIATAddr(REX::W32::HMODULE a_module, std::string_view a_dll, std::string_view a_function)
	{
		return reinterpret_cast<std::uintptr_t>(GetIATPtr(a_module, std::move(a_dll), std::move(a_function)));
	}

	void* GetIATPtr(std::string_view a_dll, std::string_view a_function)
	{
		return GetIATPtr(REL::Module::get().pointer(), std::move(a_dll), std::move(a_function));
	}

	// https://guidedhacking.com/attachments/pe_imptbl_headers-jpg.2241/
	void* GetIATPtr(REX::W32::HMODULE a_module, std::string_view a_dll, std::string_view a_function)
	{
		assert(a_module);
		const auto dosHeader = reinterpret_cast<REX::W32::IMAGE_DOS_HEADER*>(a_module);
		if (dosHeader->magic != REX::W32::IMAGE_DOS_SIGNATURE) {
			log::error("Invalid DOS header");
			return nullptr;
		}

		const auto  ntHeader = stl::adjust_pointer<REX::W32::IMAGE_NT_HEADERS64>(dosHeader, dosHeader->lfanew);
		const auto& dataDir = ntHeader->optionalHeader.dataDirectory[REX::W32::IMAGE_DIRECTORY_ENTRY_IMPORT];
		const auto  importDesc = stl::adjust_pointer<REX::W32::IMAGE_IMPORT_DESCRIPTOR>(dosHeader, dataDir.virtualAddress);

		for (auto import = importDesc; import->characteristics != 0; ++import) {
			auto name = stl::adjust_pointer<const char>(dosHeader, import->name);
			if (a_dll.size() == strlen(name) && _strnicmp(a_dll.data(), name, a_dll.size()) != 0) {
				continue;
			}

			const auto thunk = stl::adjust_pointer<REX::W32::IMAGE_THUNK_DATA64>(dosHeader, import->firstThunkOriginal);
			for (std::size_t i = 0; thunk[i].ordinal; ++i) {
				if (REX::W32::IMAGE_SNAP_BY_ORDINAL64(thunk[i].ordinal)) {
					continue;
				}

				const auto importByName = stl::adjust_pointer<REX::W32::IMAGE_IMPORT_BY_NAME>(dosHeader, thunk[i].address);
				if (a_function.size() == strlen(importByName->name) &&
					_strnicmp(a_function.data(), importByName->name, a_function.size()) == 0) {
					return stl::adjust_pointer<REX::W32::IMAGE_THUNK_DATA64>(dosHeader, import->firstThunk) + i;
				}
			}
		}

		log::warn("Failed to find {} ({})", a_dll, a_function);
		return nullptr;
	}

	std::uintptr_t PatchIAT(std::uintptr_t a_newFunc, std::string_view a_dll, std::string_view a_function)
	{
		std::uintptr_t origAddr = 0;

		const auto oldFunc = GetIATAddr(a_dll, a_function);
		if (oldFunc) {
			origAddr = *reinterpret_cast<std::uintptr_t*>(oldFunc);
			REL::safe_write(oldFunc, a_newFunc);
		} else {
			log::warn("Failed to patch {} ({})", a_dll, a_function);
		}

		return origAddr;
	}
}

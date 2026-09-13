#include "RE/H/hkStringPtr.h"
#include "RE/H/hkMemoryRouter.h"

namespace RE
{
	hkStringPtr::hkStringPtr(std::string_view a_data, const std::uint32_t a_mask, const bool a_mark) :
		_data(nullptr)
	{
		using func_t = std::add_pointer_t<void(hkStringPtr&, const char*, std::uint32_t, bool)>;
		static REL::Relocation<func_t> func{ RELOCATION_ID(56806, 57236) };
		func(*this, a_data.data(), a_mask, a_mark);
	}

	hkStringPtr::hkStringPtr(const char* a_data) :
		_data(nullptr)
	{
		using func_t = std::add_pointer_t<void(hkStringPtr&, const char*)>;
		static REL::Relocation<func_t> func{ RELOCATION_ID(56801, 57231) };
		func(*this, a_data);
	}

	const char* hkStringPtr::data() const noexcept
	{
		return reinterpret_cast<const char*>(reinterpret_cast<std::uintptr_t>(_data) & ~kManaged);
	}

	const char* hkStringPtr::c_str() const noexcept
	{
		return data();
	}

	bool hkStringPtr::empty() const noexcept
	{
		return !_data || _data[0] == '\0';
	}

	auto hkStringPtr::size() const
		-> size_type
	{
		return static_cast<size_type>(std::strlen(data()));
	}

	auto hkStringPtr::length() const
		-> size_type
	{
		return size();
	}
}

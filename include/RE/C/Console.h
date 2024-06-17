#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/I/IMenu.h"
#include "RE/N/NiSmartPointer.h"
#include <SKSE/Version.h>

namespace RE
{
	class TESObjectREFR;

	// menuDepth = 12
	// flags = kPausesGame | kAlwaysOpen | kUsesCursor | kAllowSaving
	// context = kConsole
	class Console : public IMenu
	{
	public:
		inline static constexpr auto      RTTI = RTTI_Console;
		constexpr static std::string_view MENU_NAME = "Console";

		struct EXTENDED_CONSOLE_DATA
		{
#define EXTENDED_CONSOLE_DATA_CONTENT                                  \
private:                                                               \
	[[maybe_unused]] std::uint32_t pad48; /* 48 */                     \
	[[maybe_unused]] std::uint8_t  pad4c; /* 4c */                     \
public:                                                                \
	bool         showAchievementWarning; /* 4d -- only used in ctor */ \
	bool         ctrlKeyHeld;            /* 4e */                      \
	std::uint8_t pad4f;                  /* 4f */

			EXTENDED_CONSOLE_DATA_CONTENT
		};

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT       \
	void*         opcode; /* 00 */ \
	std::uint64_t unk38;  /* 08 */ \
	std::uint64_t unk40;  /* 10 */

			RUNTIME_DATA_CONTENT
		};

		struct RUNTIME_DATA2
		{
#define RUNTIME_DATA_CONTENT2     \
	std::uint64_t unk48; /* 18 */ \
	std::uint64_t unk50; /* 20 */

			RUNTIME_DATA_CONTENT2
		};

		~Console() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;  // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;    // 04

		static NiPointer<TESObjectREFR> GetSelectedRef();
		static ObjectRefHandle          GetSelectedRefHandle();

		void SetSelectedRef(NiPointer<TESObjectREFR> a_refPtr);
		void SetSelectedRef(TESObjectREFR* a_ref);
		void SetSelectedRef(ObjectRefHandle a_handle);

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x30, 0x40);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x30, 0x40);
		}

		[[nodiscard]] inline RUNTIME_DATA2& GetRuntimeData2() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA2>(this, 0x48, 0x60);
		}

		[[nodiscard]] inline const RUNTIME_DATA2& GetRuntimeData2() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA2>(this, 0x48, 0x60);
		}

		[[nodiscard]] inline EXTENDED_CONSOLE_DATA* TryGetExtendedConsoleData() noexcept
		{
			if (REL::Module::IsAE()) {
				return nullptr;
			}
			return &REL::RelocateMember<EXTENDED_CONSOLE_DATA>(this, 0, 0x58);
		}

		[[nodiscard]] inline const EXTENDED_CONSOLE_DATA* TryGetExtendedConsoleData() const noexcept
		{
			if (REL::Module::IsAE()) {
				return nullptr;
			}
			return &REL::RelocateMember<EXTENDED_CONSOLE_DATA>(this, 0, 0x58);
		}

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT
		EXTENDED_CONSOLE_DATA_CONTENT
		RUNTIME_DATA_CONTENT2
#endif

	protected:
		void
			SetSelectedRef_Impl(ObjectRefHandle& a_handle);

	private:
		KEEP_FOR_RE()
	};
}
#undef RUNTIME_DATA_CONTENT
#undef RUNTIME_DATA_CONTENT2
#undef EXTENDED_CONSOLE_DATA_CONTENT

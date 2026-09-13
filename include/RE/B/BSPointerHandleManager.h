#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	template <class T>
	class BSPointerHandleManager
	{
	public:
		struct Entry
		{
		public:
			enum class EntryBitfieldConstants
			{
				kAgeInc = 1 << 20,            // (1 << T::kFreeListBits)
				kFreeListMask = kAgeInc - 1,  // 0xFFFFF
				kInUseBit = 1 << 26           // kAgeInc << T::kAgeShift
			};

			[[nodiscard]] bool IsInUse() const
			{
				return handleEntryBits.any(EntryBitfieldConstants::kInUseBit);
			}

			// members
			REX::EnumSet<EntryBitfieldConstants, std::uint32_t> handleEntryBits;  // 00
			std::uint32_t                                       pad04;            // 04
			NiPointer<BSHandleRefObject>                        pointer;          // 08
		};
		static_assert(sizeof(Entry) == 0x10);

		[[nodiscard]] static bool IsValid(const ObjectRefHandle& a_handle)
		{
			using func_t = decltype(&BSPointerHandleManager<TESObjectREFR>::IsValid);
			static REL::Relocation<func_t> func{ RELOCATION_ID(75454, 77239) };
			return func(a_handle);
		}

		[[nodiscard]] static auto GetHandleEntries()
		{
			static REL::Relocation<Entry(*)[0x100000]> entries{ RELOCATION_ID(514478, 400622) };
			return std::span<Entry, 0x100000>{ *entries };
		}

		[[nodiscard]] static BSReadWriteLock& GetHandleManagerLock()
		{
			static REL::Relocation<BSReadWriteLock*> handleManagerLock{ RELOCATION_ID(514477, 400621) };
			return *handleManagerLock;
		}
	};
}

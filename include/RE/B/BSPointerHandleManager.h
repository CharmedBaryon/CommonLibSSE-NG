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

			[[nodiscard]] std::uint32_t QNextFreeEntry() const
			{
				return (handleEntryBits & EntryBitfieldConstants::kFreeListMask).underlying();
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

		[[nodiscard]] static std::uint32_t GetFreeListHead()
		{
			static REL::Relocation<std::uint32_t*> head{ RELOCATION_ID(514475, 400619) };
			return *head;
		}

		[[nodiscard]] static std::uint32_t GetFreeListTail()
		{
			static REL::Relocation<std::uint32_t*> tail{ RELOCATION_ID(514476, 400620) };
			return *tail;
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

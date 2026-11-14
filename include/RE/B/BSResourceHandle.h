#pragma once

#include "RE/B/BSResourceEntryDB.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BGSDistantObjectBlock;
	class BGSDistantTreeBlock;
	class BGSTerrainChunk;
	class NiNode;
	class NiTexture;

	namespace BGSBtoDB
	{
		struct DBTraits;
	}

	namespace BGSBtrDB
	{
		struct DBTraits;
	}

	namespace BGSBttDB
	{
		struct DBTraits;
	}

	namespace BSModelDB
	{
		struct DBTraits;
	}

	namespace BSTextureDB
	{
		struct DBTraits;
	}

	namespace BSResource
	{
		// This doesn't exist in SkyrimSE, it's actually a BSTSmartPointer with a custom RefManager doing template specific stuff in the Release func
		template <class T_Entry, class T_EntryDB>
		class RHandleType
		{
		public:
			using U_Entry = T_Entry;
			using U_EntryDB = T_EntryDB;

			[[nodiscard]] constexpr T_Entry* get() const noexcept
			{
				return _entry;
			}

			[[nodiscard]] explicit constexpr operator bool() const noexcept
			{
				return static_cast<bool>(_entry);
			}

			[[nodiscard]] constexpr T_Entry& operator*() const noexcept
			{
				assert(static_cast<bool>(*this));
				return *_entry;
			}

			[[nodiscard]] constexpr T_Entry* operator->() const noexcept
			{
				assert(static_cast<bool>(*this));
				return _entry;
			}

		protected:
			// members
			T_Entry* _entry;  // 00
		};
	}

	using BGSBtoDBHandle = BSResource::RHandleType<BSResource::Entry<BGSDistantObjectBlock*, BSResource::EntryDBTraits<BGSBtoDB::DBTraits, BSResource::EntryDB<BGSBtoDB::DBTraits>>::CArgs>, BSResource::EntryDB<BGSBtoDB::DBTraits>>;
	using BGSBtrDBHandle = BSResource::RHandleType<BSResource::Entry<BGSTerrainChunk*, BSResource::EntryDBTraits<BGSBtrDB::DBTraits, BSResource::EntryDB<BGSBtrDB::DBTraits>>::CArgs>, BSResource::EntryDB<BGSBtrDB::DBTraits>>;
	using BGSBttDBHandle = BSResource::RHandleType<BSResource::Entry<BGSDistantTreeBlock*, BSResource::EntryDBTraits<BGSBttDB::DBTraits, BSResource::EntryDB<BGSBttDB::DBTraits>>::CArgs>, BSResource::EntryDB<BGSBttDB::DBTraits>>;

	using ModelDBHandle = BSResource::RHandleType<BSResource::Entry<NiPointer<NiNode>, BSResource::EntryDBTraits<BSModelDB::DBTraits, BSResource::EntryDB<BSModelDB::DBTraits>>::CArgs>, BSResource::EntryDB<BSModelDB::DBTraits>>;
	using TextureDBHandle = BSResource::RHandleType<BSResource::Entry<NiPointer<NiTexture>, BSResource::EntryDBTraits<BSTextureDB::DBTraits, BSResource::EntryDB<BSTextureDB::DBTraits>>::CArgs>, BSResource::EntryDB<BSTextureDB::DBTraits>>;
}

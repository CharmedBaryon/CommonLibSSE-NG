#pragma once

#include "RE/B/BSResourceEntry.h"
#include "RE/B/BSResourceEntryCache.h"
#include "RE/B/BSResourceEntryQueue.h"
#include "RE/B/BSTSingleton.h"

namespace RE
{
	namespace BSResource
	{
		class Location;
		class EntryBase;

		template <class T>
		class EntryDB;

		template <class T_DBTraits, class T_EntryDB>
		class EntryDBTraits
		{
		public:
			using U_DBTraits = T_DBTraits;
			using U_EntryDB = T_EntryDB;

			class CArgs
			{
			public:
				// members
				T_DBTraits::ArgsType userArgs;  // 00
				BSFixedString        nameText;  // ??
			};
		};
		static_assert(std::is_empty_v<EntryDBTraits<void, void>>);

		class IEntryDB
		{
		public:
			inline static constexpr auto RTTI = RTTI_BSResource__IEntryDB;
			inline static constexpr auto VTABLE = VTABLE_BSResource__IEntryDB;

			class NotifyLoadDone
			{
			public:
				inline static constexpr auto RTTI = RTTI_BSResource__IEntryDB__NotifyLoadDone;
				inline static constexpr auto VTABLE = VTABLE_BSResource__IEntryDB__NotifyLoadDone;

				virtual ~NotifyLoadDone();  // 00

				// add
				virtual void operator()() = 0;  // 01
			};
			static_assert(sizeof(NotifyLoadDone) == 0x08);

			class PostFlushNotify
			{
			public:
				inline static constexpr auto RTTI = RTTI_BSResource__IEntryDB__PostFlushNotify;
				inline static constexpr auto VTABLE = VTABLE_BSResource__IEntryDB__PostFlushNotify;

				virtual ~PostFlushNotify();  // 00

				// add
				virtual bool DoOnNotify() = 0;    // 01
				virtual void DoOnFinalize() = 0;  // 02

				// members
				std::uint32_t    state;  // 08
				PostFlushNotify* next;   // 10
			};
			static_assert(sizeof(PostFlushNotify) == 0x18);

			virtual ~IEntryDB();  // 00

			// add
			virtual void Unk_01(void) = 0;  // 01
			virtual void Unk_02(void) = 0;  // 02
			virtual void Unk_03(void) = 0;  // 03
			virtual void Unk_04(void) = 0;  // 04
			virtual void Unk_05(void) = 0;  // 05

			// members
			EntryBucketQueue<PostFlushNotify, 8> postFlushNotifyQueue;  // 08
		};
		static_assert(sizeof(IEntryDB) == 0xD0);

		template <class T_EntryDBTraits>
		class EntryDBBase :
			public T_EntryDBTraits::U_DBTraits
		{
		public:
			// members
			std::byte                                                                                                                                               unk00[0x40];             // 00
			REntryCache<EntryCacheTraits<typename T_EntryDBTraits::U_DBTraits::U_Type, typename T_EntryDBTraits::CArgs, DAP, 64>>                                   cache;                   // ??
			EntryBucketQueue<Entry<typename T_EntryDBTraits::U_DBTraits::U_Type, typename T_EntryDBTraits::CArgs>, T_EntryDBTraits::U_DBTraits::LOAD_QUEUE_SIZE>    loadQueue;               // ??
			EntryBucketQueue<Entry<typename T_EntryDBTraits::U_DBTraits::U_Type, typename T_EntryDBTraits::CArgs>, T_EntryDBTraits::U_DBTraits::RELEASE_QUEUE_SIZE> releaseQueue;            // ??
			Location*                                                                                                                                               rootLocation;            // ??
			std::byte                                                                                                                                               unk168[0x8170 - 0x168];  // ??
			std::uint64_t                                                                                                                                           unk8170;                 // ??
		};

		template <class T_DBTraits>
		class EntryDB :
			public IEntryDB,
			public EntryDBBase<EntryDBTraits<T_DBTraits, BSResource::EntryDB<T_DBTraits>>>,
			public BSTSingletonSDM<EntryDB<T_DBTraits>>
		{
		public:
			~EntryDB() override;  // 00

			// override (IEntryDB)
			void Unk_01(void) override;  // 01
			void Unk_02(void) override;  // 02
			void Unk_03(void) override;  // 03
			void Unk_04(void) override;  // 04
			void Unk_05(void) override;  // 05
		};
	}
}

#pragma once
#include "RE/B/BSStorage.h"
#include "RE/C/CodeTasklet.h"
#include "RE/L/LoadStorageWrapper.h"
#include "RE/O/Object.h"
#include "RE/S/SaveFileHandleReaderWriter.h"
namespace RE
{
	namespace BSScript
	{
		enum class StringIndexSize
		{
			kSmall,
			kLarge
		};

		class ReadableStringTable
		{
		public:
			class StringEntry
			{
			public:
				// members
				const char*   originalData;     // 00
				BSFixedString convertedString;  // 08
			};
			static_assert(sizeof(StringEntry) == 0x10);

			// members
			void*                                           unk00;      // 00
			BSScrapArray<StringEntry>*                      entries;    // 08
			stl::enumeration<StringIndexSize, std::int32_t> indexSize;  // 10
		};
		static_assert(sizeof(ReadableStringTable) == 0x18);

		class WritableStringTable
		{
		public:
			// members
			void*                                           unk00;         // 00
			BSTScrapHashMap<BSFixedString, std::uint32_t>*  referenceMap;  // 08
			stl::enumeration<StringIndexSize, std::int32_t> indexSize;     // 10
		};
		static_assert(sizeof(WritableStringTable) == 0x18);

		class IVMSaveLoadInterface
		{
		public:
			inline static constexpr auto RTTI = RTTI_BSScript__IVMSaveLoadInterface;
			inline static constexpr auto VTABLE = VTABLE_BSScript__IVMSaveLoadInterface;

			virtual ~IVMSaveLoadInterface();  // 00

			// add
			virtual void                                                              SaveGame(SaveStorageWrapper* a_wrapper, SkyrimScript::SaveFileHandleReaderWriter* a_handle, bool unk) = 0;  // 01
			virtual void                                                              LoadGame(LoadStorageWrapper* a_wrapper, SkyrimScript::SaveFileHandleReaderWriter* a_handle) = 0;            // 02
			virtual void                                                              MarkSaveInvalid(BSStorage* a_storage) = 0;                                                                  // 03
			virtual std::byte                                                         GetSaveGameVersion() = 0;                                                                                   // 04
			virtual void                                                              CleanupSave() = 0;                                                                                          // 05
			virtual void                                                              Unk_06(void) = 0;                                                                                           // 06
			virtual void                                                              DropAllRunningData() = 0;                                                                                   // 07
			virtual void                                                              Unk_08(void* unk) = 0;                                                                                      // 08
			virtual void                                                              Unk_09(void) = 0;                                                                                           // 09
			virtual void                                                              Unk_0A(VMHandle a_handle, Object** a_out) = 0;                                                              // 0A
			virtual void                                                              Unk_0B(void* unk) = 0;                                                                                      // 0B
			virtual void                                                              Unk_0C(void) = 0;                                                                                           // 0C
			virtual void                                                              Unk_0D(VMHandle a_handle, Array** a_out) = 0;                                                               // 0D
			virtual void                                                              Unk_0E(LoadStorageWrapper* a_storage, void* unk) = 0;                                                       // 0E
			virtual bool                                                              GetStackByID(VMStackID a_stackID, Stack** a_out) = 0;                                                       // 0F
			virtual WritableStringTable                                               GetWritableStringTable() = 0;                                                                               // 10
			virtual const WritableStringTable                                         GetWritableStringTable2() = 0;                                                                              // 11
			virtual ReadableStringTable                                               GetReadableStringTable() = 0;                                                                               // 12
			virtual BSTHashMap<BSFixedString, BSTSmartPointer<ObjectTypeInfo>>*       GetWritableTypeTable() = 0;                                                                                 // 13
			virtual const BSTHashMap<BSFixedString, BSTSmartPointer<ObjectTypeInfo>>* GetWritableTypeTable2() = 0;                                                                                // 14
			virtual BSTHashMap<BSFixedString, BSTSmartPointer<ObjectTypeInfo>>*       GetReadableTypeTable() = 0;                                                                                 // 15
			virtual bool                                                              CreateEmptyTasklet(Stack* a_stack, Internal::CodeTasklet** a_out) = 0;                                      // 16
		};
		static_assert(sizeof(IVMSaveLoadInterface) == 0x8);
	}
}

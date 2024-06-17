#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTArray.h"
#include "RE/N/NiObjectGroup.h"
#include "RE/N/NiTArray.h"
#include "RE/N/NiTPointerMap.h"

#include "REX/W32/BASE.h"

namespace RE
{
	class NiBinaryStream;
	class NiObjectGroup;

	struct BSStreamHeader
	{
	public:
		// members
		std::uint32_t version;            // 00
		char          author[64];         // 04
		char          processScript[64];  // 44
		char          exportScript[64];   // 84
		std::uint32_t padC4;              // C4
	};
	static_assert(sizeof(BSStreamHeader) == 0xC8);

	class NiStream
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiStream;
		inline static constexpr auto VTABLE = VTABLE_NiStream;

		virtual ~NiStream();  // 00

		// add
		virtual bool          Load1(NiBinaryStream* a_stream);                          // 01
		virtual bool          Load2(char* a_buffer, std::uint64_t a_len);               // 02
		virtual bool          Load3(const char* a_path);                                // 03
		virtual bool          Save1(NiBinaryStream* a_stream);                          // 04
		virtual bool          Save2(char*& a_path, std::uint64_t& a_len);               // 05
		virtual bool          Save3(const char* a_path);                                // 06
		virtual void          Unk_07(void);                                             // 07 - { return 0; }
		virtual bool          RegisterFixedString(const BSFixedString& a_fixedString);  // 08
		virtual bool          RegisterSaveObject(NiObject* a_object);                   // 09
		virtual bool          ChangeObject(NiObject* a_object);                         // 0A
		virtual std::uint32_t GetLinkIDFromObject(const NiObject* a_object);            // 0B
		virtual void          SaveLinkID(const NiObject* a_object);                     // 0C
		virtual bool          LoadHeader();                                             // 0D
		virtual void          SaveHeader();                                             // 0E
		virtual bool          LoadStream();                                             // 0F
		virtual void          SaveStream();                                             // 10
		virtual void          RegisterObjects();                                        // 11
		virtual void          LoadTopLevelObjects();                                    // 12
		virtual void          SaveTopLevelObjects();                                    // 13
		virtual bool          LoadObject();                                             // 14
		virtual std::uint64_t PreSaveObjectSizeTable();                                 // 15
		virtual bool          SaveObjectSizeTable(std::uint64_t a_size);                // 16
		virtual bool          LoadObjectSizeTable();                                    // 17

		void LoadLinkID()
		{
			using func_t = decltype(&NiStream::LoadLinkID);
			REL::Relocation<func_t> func{ RELOCATION_ID(69002, 70359) };
			return func(this);
		}

		// members
		BSStreamHeader                                header;                                // 008
		BSTSmallArray<NiObjectGroup>                  groups;                                // 0D0
		std::uint32_t                                 nifMaxVersion;                         // 100
		std::uint32_t                                 nifMaxUserDefinedVersion;              // 104
		char                                          inputFilePath[REX::W32::MAX_PATH];     // 108
		std::uint16_t                                 unk20C;                                // 20C
		std::uint16_t                                 unk20E;                                // 20E
		std::uint64_t                                 unk210;                                // 210
		NiTLargeObjectArray<NiPointer<NiObject>>      objects;                               // 218
		NiTLargePrimitiveArray<std::uint32_t>         objectSizes;                           // 238
		NiTLargeObjectArray<NiPointer<NiObject>>      topObjects;                            // 258
		NiTLargeObjectArray<BSFixedString>            fixedStrings;                          // 278
		NiBinaryStream*                               iStr;                                  // 298
		NiBinaryStream*                               oStr;                                  // 2A0
		std::uint32_t                                 linkIndex;                             // 2A8
		std::uint32_t                                 linkBlockIndex;                        // 2AC
		NiTPointerMap<NiObject const*, std::uint32_t> registerMap;                           // 2B0
		std::uint16_t                                 niAVObjectFlags;                       // 2D0
		std::uint16_t                                 niTimeControllerFlags;                 // 2D2
		std::uint16_t                                 niPropertyFlags;                       // 2D4
		std::uint32_t                                 unk2D8;                                // 2D8
		bool                                          unk2DC;                                // 2DC
		std::uint32_t                                 load;                                  // 2E0
		std::uint32_t                                 link;                                  // 2E4
		std::uint32_t                                 postLink;                              // 2E8
		std::uint64_t                                 unk2F0;                                // 2F0
		std::uint64_t                                 unk2F8;                                // 2F8
		std::uint32_t                                 unk300;                                // 300
		std::uint32_t                                 unk304;                                // 304
		std::int32_t                                  unk308;                                // 308
		char                                          lastLoadedRTTI[REX::W32::MAX_PATH];    // 30C
		std::uint32_t                                 lastError;                             // 410
		char                                          lastErrorMessage[REX::W32::MAX_PATH];  // 414
		char                                          filePath[REX::W32::MAX_PATH];          // 518
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(NiStream) == 0x620);
}

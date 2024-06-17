#pragma once

#include "RE/N/NiStream.h"

namespace RE
{
	class BSNodeReferences;

	class BSStream : public NiStream
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSStream;
		inline static constexpr auto VTABLE = VTABLE_BSStream;

		~BSStream() override;  // 00

		// overwrite (NiStream)
		bool Load1(NiBinaryStream* a_stream) override;             // 01
		bool Load2(char* a_buffer, std::uint64_t a_len) override;  // 02
		bool Load3(const char* a_path) override;                   // 03
		bool Save1(NiBinaryStream* a_stream) override;             // 04
		bool Save2(char*& a_path, std::uint64_t& a_len) override;  // 05
		bool Save3(const char* a_path) override;                   // 06
		bool RegisterSaveObject(NiObject* a_object) override;      // 09
		bool LoadStream() override;                                // 0F
		void SaveStream() override;                                // 10

		// members
		void*                       objectRefMap;    // 620 - BSTHashMap<const char*,NiObjectNET *>* ?
		NiPointer<BSNodeReferences> nodeReferences;  // 628
		std::uint64_t               unk630;          // 630
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSStream) == 0x638);
}

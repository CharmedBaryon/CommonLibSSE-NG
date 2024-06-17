#pragma once

#include "RE/N/NiExtraData.h"

namespace RE
{
	class NiFloatsExtraData : public NiExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiFloatsExtraData;
		inline static auto           Ni_RTTI = NiRTTI_NiFloatsExtraData;
		inline static constexpr auto VTABLE = VTABLE_NiFloatsExtraData;

		~NiFloatsExtraData() override;  // 00

		// override (NiExtraData)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void          LoadBinary(NiStream& a_stream) override;            // 18
		void          LinkObject(NiStream& a_stream) override;            // 19 - { NiExtraData::LinkObject(a_stream); }
		bool          RegisterStreamables(NiStream& a_stream) override;   // 1A - { return NiExtraData::RegisterStreamables(a_stream); }
		void          SaveBinary(NiStream& a_stream) override;            // 1B
		bool          IsEqual(NiObject* a_object) override;               // 1C

		static NiFloatsExtraData* Create(const BSFixedString& a_name, const std::vector<float>& a_Floats);

		[[nodiscard]] std::optional<std::uint32_t> GetIndex(float a_element) const;
		bool                                       Insert(float a_element);
		bool                                       Remove(float a_element);

		// members
		std::uint32_t size;   // 18
		std::uint32_t pad;    // 1C
		float*        value;  // 20
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(NiFloatsExtraData) == 0x28);
}

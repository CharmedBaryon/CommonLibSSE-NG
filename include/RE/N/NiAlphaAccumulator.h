#pragma once

#include "RE/N/NiBackToFrontAccumulator.h"

namespace RE
{
	class NiAlphaAccumulator : public NiBackToFrontAccumulator
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiAlphaAccumulator;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiAlphaAccumulator;
		inline static constexpr auto VTABLE = VTABLE_NiAlphaAccumulator;

		~NiAlphaAccumulator() override = default;  // 00

		// override (NiObject)
		[[nodiscard]] const NiRTTI* GetRTTI() const override;                                            // 02
		NiObject*                   CreateClone([[maybe_unused]] NiCloningProcess& a_cloning) override;  // 17
		void                        LoadBinary([[maybe_unused]] NiStream& a_stream) override;            // 18
		void                        LinkObject([[maybe_unused]] NiStream& a_stream) override;            // 19
		bool                        RegisterStreamables(NiStream& a_stream) override;                    // 1A
		void                        SaveBinary([[maybe_unused]] NiStream& a_stream) override;            // 1B
		bool                        IsEqual(NiObject* a_object) override;                                // 1C

		// override (NiAccumulator)
		void RegisterObjectArray(NiVisibleArray& a_visibleArray) override;  // 27

		// members
		bool observeNoSortHint;   //50
		bool sortByClosestPoint;  //51
		bool interfaceSort;       //52
	};
	static_assert(sizeof(NiAlphaAccumulator) == 0x58);
}
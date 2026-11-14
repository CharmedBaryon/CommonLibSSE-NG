#pragma once

#include "RE/N/NiAccumulator.h"
#include "RE/N/NiTPointerList.h"

namespace RE
{
	class BSGeometry;
	class NiVisibleArray;

	class NiBackToFrontAccumulator : public NiAccumulator
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiBackToFrontAccumulator;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiBackToFrontAccumulator;
		inline static constexpr auto VTABLE = VTABLE_NiBackToFrontAccumulator;

		~NiBackToFrontAccumulator() override = default;  // 00

		// override (NiObject)
		[[nodiscard]] const NiRTTI* GetRTTI() const override;                                  // 02
		void                        LoadBinary([[maybe_unused]] NiStream& a_stream) override;  // 18
		void                        LinkObject([[maybe_unused]] NiStream& a_stream) override;  // 19
		bool                        RegisterStreamables(NiStream& a_stream) override;          // 1A
		void                        SaveBinary([[maybe_unused]] NiStream& a_stream) override;  // 1B
		bool                        IsEqual(NiObject* a_object) override;                      // 1C

		// override (NiAccumulator)
		void FinishAccumulating() override;                                 // 26
		void RegisterObjectArray(NiVisibleArray& a_visibleArray) override;  // 27

		void ClearItemsList();

		// members
		NiTPointerList<BSGeometry*> itemsList;  // 18
		int32_t                     numItems;   // 30
		int32_t                     maxItems;   // 34
		BSGeometry**                items;      // 38
		float*                      depths;     // 40
		int32_t                     currItem;   // 48
	};
	static_assert(sizeof(NiBackToFrontAccumulator) == 0x50);
}
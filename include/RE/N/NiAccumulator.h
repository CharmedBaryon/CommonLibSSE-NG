#pragma once

#include "RE/B/BSBatchRenderer.h"
#include "RE/N/NiBound.h"
#include "RE/N/NiCamera.h"
#include "RE/N/NiObject.h"

namespace RE
{
	class BSBatchRenderer;
	class NiVisibleArray;

	class NiAccumulator : public NiObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiAccumulator;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiAccumulator;
		inline static constexpr auto VTABLE = VTABLE_NiAccumulator;

		~NiAccumulator() override = default;  // 00

		// override (NiObject)
		[[nodiscard]] const NiRTTI* GetRTTI() const override;                                  // 02
		void                        LoadBinary([[maybe_unused]] NiStream& a_stream) override;  // 18
		void                        LinkObject([[maybe_unused]] NiStream& a_stream) override;  // 19
		bool                        RegisterStreamables(NiStream& a_stream) override;          // 1A
		void                        SaveBinary([[maybe_unused]] NiStream& a_stream) override;  // 1B
		bool                        IsEqual(NiObject* a_object) override;                      // 1C

		// add
		virtual void                            StartAccumulating(NiCamera* a_camera);                        // 25
		virtual void                            FinishAccumulating();                                         // 26
		virtual void                            RegisterObjectArray(NiVisibleArray& a_visibleArray);          // 27
		virtual BSBatchRenderer::GeometryGroup* StartGroupingAlphas(NiBound* a_bound);                        // 28
		virtual void                            StopGroupingAlphas(BSBatchRenderer::GeometryGroup* a_group);  // 29

		// members
		const NiCamera* camera;  // 10
	};
	static_assert(sizeof(NiAccumulator) == 0x18);
}

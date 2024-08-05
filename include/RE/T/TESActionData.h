#pragma once

#include "RE/B/BGSActionData.h"

namespace RE
{
	class TESActionData : public BGSActionData
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESActionData;
		inline static constexpr auto VTABLE = VTABLE_TESActionData;

		virtual ~TESActionData() override;  // 00

		// override (ActionInput)
		ActorState*            GetSourceActorState() const override;  // 01
		void                   Unk_02(void) override;                 // 02 - { return 0; }
		BGSAnimationSequencer* GetSourceSequencer() const override;   // 03

		// override (BGSActionData)
		BGSActionData* Clone() const override;  // 04
		bool           Process() override;      // 05

		static TESActionData* Create()
		{
			auto tesActionData = malloc<TESActionData>();
			std::memset(reinterpret_cast<void*>(tesActionData), 0, sizeof(TESActionData));
			if (tesActionData) {
				tesActionData->Ctor();
			}
			return tesActionData;
		}

	private:
		TESActionData* Ctor()
		{
			using func_t = decltype(&TESActionData::Ctor);
			static REL::Relocation<func_t> func{ RELOCATION_ID(15916, 41558) };
			TESActionData*                 tesActionData = func(this);
			stl::emplace_vtable<TESActionData>(tesActionData);
			return tesActionData;
		}

	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(TESActionData) == 0x60);
}

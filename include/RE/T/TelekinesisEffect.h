#pragma once

#include "RE/A/ActiveEffect.h"
#include "RE/B/BSPointerHandle.h"

namespace RE
{
	class TelekinesisEffect : public ActiveEffect
	{
	public:
		inline static constexpr auto RTTI = RTTI_TelekinesisEffect;
		inline static constexpr auto VTABLE = VTABLE_TelekinesisEffect;

		// override (ActiveEffect)
		void Update(float a_delta) override;  // 04

		~TelekinesisEffect() override;  // 13

		void Start() override;   // 14
		void Finish() override;  // 15

		// members
		void*           unk90;          // 90 - smart ptr
		float           moveVelocity;   // 98
		float           unk9C;          // 9C
		ObjectRefHandle grabbedObject;  // A0
		std::uint32_t   unkA4;          // A4
		bool            unkA8;          // A8
		bool            unkA9;          // A9
		std::uint8_t    unkAA;          // AA
		std::uint8_t    unkAB;          // AB
		std::uint32_t   unkAC;          // AC
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(TelekinesisEffect) == 0xB0);
}

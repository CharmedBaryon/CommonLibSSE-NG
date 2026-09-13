#pragma once

#include "RE/T/TESCameraState.h"

#include "REL/Common.h"

namespace RE
{
	class AutoVanityState : public TESCameraState
	{
	public:
		inline static constexpr auto RTTI = RTTI_AutoVanityState;
		inline static constexpr auto VTABLE = VTABLE_AutoVanityState;

		~AutoVanityState() override;  // 00

		// override (TESCameraState)
		void Begin() override;  // 01
		void End() override;    // 02
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		// Function doesn't exist in SE/AE-only builds
#elif defined(EXCLUSIVE_SKYRIM_VR)
		void Unk_03() override;  // 03 - VR only
#else
		void Unk_03();  // 03 - Multi-runtime
#endif
		void Update(BSTSmartPointer<TESCameraState>& a_nextState) override;  // 03/04
		void GetRotation(NiQuaternion& a_rotation) override;                 // 04/05
		void GetTranslation(NiPoint3& a_translation) override;               // 05/06

		// members
		float         autoVanityRot;  // 20
		std::uint32_t pad24;          // 24
	};
	static_assert(sizeof(AutoVanityState) == 0x28);
}

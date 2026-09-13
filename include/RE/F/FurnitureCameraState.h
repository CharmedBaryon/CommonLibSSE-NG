#pragma once

#include "RE/T/TESCameraState.h"

#include "REL/Common.h"

namespace RE
{
	class FurnitureCameraState : public TESCameraState
	{
	public:
		inline static constexpr auto RTTI = RTTI_FurnitureCameraState;
		inline static constexpr auto VTABLE = VTABLE_FurnitureCameraState;

		~FurnitureCameraState() override;  // 00

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
		void SaveGame(BGSSaveFormBuffer* a_buf) override;                    // 06/07
		void LoadGame(BGSLoadFormBuffer* a_buf) override;                    // 07/08
		void Revert(BGSLoadFormBuffer* a_buf) override;                      // 08/09

		std::uint32_t unk20;  // 20
		NiPoint3      unk24;  // 24
		std::uint64_t unk30;  // 30
		std::uint32_t unk38;  // 38
		std::uint16_t unk3C;  // 3C
		std::uint16_t unk3E;  // 3E
	};
	static_assert(sizeof(FurnitureCameraState) == 0x40);
}

#pragma once

#include "RE/B/BSIntrusiveRefCounted.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/P/PlayerCamera.h"

#include "REL/Common.h"

namespace RE
{
	class BGSLoadFormBuffer;
	class BGSSaveFormBuffer;
	class NiPoint3;
	class NiQuaternion;
	class TESCamera;

	class TESCameraState : public BSIntrusiveRefCounted
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESCameraState;
		inline static constexpr auto VTABLE = VTABLE_TESCameraState;

		virtual ~TESCameraState();  // 00

		// add
		virtual void Begin();  // 01 - { return; }
		virtual void End();    // 02 - { return; }
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		// Function doesn't exist in SE/AE-only builds
#elif defined(EXCLUSIVE_SKYRIM_VR)
		virtual void Unk_03();  // 03 - VR only: Directly calls Update
#else
		void Unk_03();  // 03 - Multi-runtime
#endif
		virtual void Update(BSTSmartPointer<TESCameraState>& a_nextState);  // 03/04
		virtual void GetRotation(NiQuaternion& a_rotation);                 // 04/05
		virtual void GetTranslation(NiPoint3& a_translation);               // 05/06
		virtual void SaveGame(BGSSaveFormBuffer* a_buf);                    // 06/07 - { return; }
		virtual void LoadGame(BGSLoadFormBuffer* a_buf);                    // 07/08 - { return; }
		virtual void Revert(BGSLoadFormBuffer* a_buf);                      // 08/09 - { return; }

		// members
		std::uint32_t pad0C;   // 0C
		TESCamera*    camera;  // 10
		CameraState   id;      // 18
		std::uint32_t pad1C;   // 1C
	};
	static_assert(sizeof(TESCameraState) == 0x20);
}

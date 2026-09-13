#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTSingleton.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/N/NiPoint3.h"
#include "RE/T/TESCamera.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class bhkRigidBody;
	class bhkSimpleShapePhantom;
	class NiRefObject;
	class TESCameraState;

	struct CameraStates
	{
		enum CameraState : std::uint32_t
		{
			kFirstPerson = 0,
			kAutoVanity,
			kVATS,
			kFree,
			kIronSights,
			kFurniture,
			kPCTransition,
			kTween,
			kAnimated,
			kThirdPerson,
			kMount,
			kBleedout,
			kDragon,
			kTotal,

			// VR has kVR in between Animated and ThirdPerson
			kVR = 9,
			kVRThirdPerson,
			kVRMount,
			kVRBleedout,
			kVRDragon,
			kVRTotal
		};
	};
	using CameraState = CameraStates::CameraState;

	class PlayerCamera :
		public TESCamera,                     // 000
		public BSTSingletonSDM<PlayerCamera>  // 038
	{
	public:
		inline static constexpr auto RTTI = RTTI_PlayerCamera;
		inline static constexpr auto VTABLE = VTABLE_PlayerCamera;

		struct Unk120
		{
			NiPointer<bhkSimpleShapePhantom> unk00;  // 00
			NiPointer<bhkSimpleShapePhantom> unk08;  // 08
		};
		static_assert(sizeof(Unk120) == 0x10);

		~PlayerCamera() override;  // 00

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                                                  \
	BSTSmallArray<TESCameraState*, CameraStates::kTotal> tempReturnStates;                   /* 040, VR 040*/ \
	BSTSmartPointer<TESCameraState>                      cameraStates[CameraStates::kTotal]; /* 0B8, VR 0C0*/ \
	Unk120*                                              unk120;                             /* 120, VR 130*/ \
	NiPointer<bhkRigidBody>                              rigidBody;                          /* 128, VR 138*/ \
	RefHandle                                            objectFadeHandle;                   /* 130, VR 140*/ \
	mutable BSSpinLock                                   lock;                               /* 134, VR 14C*/

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x100);
		static_assert(offsetof(RUNTIME_DATA, cameraStates) == 0x78);
		static_assert(offsetof(RUNTIME_DATA, rigidBody) == 0xE8);
		static_assert(offsetof(RUNTIME_DATA, objectFadeHandle) == 0xF0);
		static_assert(offsetof(RUNTIME_DATA, lock) == 0xF4);

		struct VR_RUNTIME_DATA
		{
#define VR_RUNTIME_DATA_CONTENT                                                                                                             \
	BSTSmallArray<TESCameraState*, CameraStates::kVRTotal> tempReturnStates;                     /* 040, VR 040*/                           \
	BSTSmartPointer<TESCameraState>                        cameraStates[CameraStates::kVRTotal]; /* 0B8, VR 0C0*/                           \
	Unk120*                                                unk120;                               /* 120, VR 130*/                           \
	NiPointer<bhkRigidBody>                                rigidBody;                            /* 128, VR 138*/                           \
	RefHandle                                              objectFadeHandle;                     /* 130, VR 140*/                           \
	RefHandle                                              unk144;                               /* VR 144 - default 0xFFFFFFFF, VR-only */ \
	bool                                                   unk148;                               /* VR 148 - VR-only */                     \
	std::uint8_t                                           pad149[3];                            /* VR 149 */                               \
	mutable BSSpinLock                                     lock;                                 /* 134, VR 14C*/                           \
	std::uint32_t                                          unk154;                               /* VR 154 - VR-only */
            VR_RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(VR_RUNTIME_DATA) == 0x118);
		static_assert(offsetof(VR_RUNTIME_DATA, cameraStates) == 0x80);
		static_assert(offsetof(VR_RUNTIME_DATA, unk120) == 0xF0);
		static_assert(offsetof(VR_RUNTIME_DATA, rigidBody) == 0xF8);
		static_assert(offsetof(VR_RUNTIME_DATA, objectFadeHandle) == 0x100);
		static_assert(offsetof(VR_RUNTIME_DATA, unk144) == 0x104);
		static_assert(offsetof(VR_RUNTIME_DATA, unk148) == 0x108);
		static_assert(offsetof(VR_RUNTIME_DATA, lock) == 0x10C);
		static_assert(offsetof(VR_RUNTIME_DATA, unk154) == 0x114);

		struct RUNTIME_DATA2
		{
#define RUNTIME_DATA2_CONTENT                                                                                               \
	float    worldFOV;                 /* 13C, VR 158*/                                                                     \
	float    firstPersonFOV;           /* 140, VR 15c*/                                                                     \
	NiPoint3 pos;                      /* 144, VR 160 - cached camera-anchor position; recomputed from the camera */        \
									   /*                node's world position or actor-root + eye-level offset, */         \
									   /*                cf. ThirdPersonState::collisionPos's cache+valid-flag pattern */   \
	float         idleTimer;           /* 150, VR 16c - countdown to auto-vanity camera when idle */                        \
	float         yaw;                 /* 154, VR 170 - target's heading + per-state offset, radians, set by UpdateYaw() */ \
	std::uint32_t unk158;              /* 158 - ?*/                                                                         \
	std::uint32_t unk15C;              /* 15C - ?*/                                                                         \
	bool          allowAutoVanityMode; /* 160, VR 17c - default depends on a game setting */                                \
	bool          bowZoomedIn;         /* 161, VR 17d - default false*/                                                     \
	bool          isWeapSheathed;      /* 162, VR 17e - default true*/                                                      \
	bool          isProcessed;         /* 163, VR 17f - default false*/                                                     \
	std::uint8_t  unk164;              /* 164*/                                                                             \
	std::uint8_t  unk165;              /* 165*/                                                                             \
	std::uint16_t pad166;              /* 166*/
			RUNTIME_DATA2_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA2) == 0x2c);

		// override (TESCamera)
		void SetCameraRoot(NiPointer<NiNode> a_root) override;  // 01

		static PlayerCamera* GetSingleton();

		bool                          ForceFirstPerson();
		bool                          ForceThirdPerson();
		[[nodiscard]] static NiPoint3 GetActiveCameraPosition();
		bool                          IsInBleedoutMode() const;
		bool                          IsInFirstPerson() const;
		bool                          IsInFreeCameraMode() const;
		bool                          IsInThirdPerson() const;
		void                          PushCameraState(CameraState a_state);
		void                          ToggleFreeCameraMode(bool a_freezeTime);
		void                          Update();
		void                          UpdateThirdPerson(bool a_weaponDrawn);
		bool                          CheckCameraCollision(NiPoint3& a_pos, bool a_fadeCharacter);
		void                          UpdateYaw();

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x40, 0);

		VR_ONLY_POINTER_ACCESSOR(VR_RUNTIME_DATA, GetVRRuntimeData, 0x40);
		RUNTIME_DATA_ACCESSOR_EX(RUNTIME_DATA2, GetRuntimeData2, 0x13c, 0x158);

		// cameraStates shifts offset per runtime AND VR's enum inserts kVR
		// before kThirdPerson/kMount, shifting indices too -- pass the SE/AE
		// and VR slot for the same state, e.g. IsCurrentState(kThirdPerson, kVRThirdPerson).
		[[nodiscard]] inline bool IsCurrentState(CameraState a_seState, CameraState a_vrState) const noexcept
		{
			if (REL::Module::IsVR()) {
				return currentState == GetVRRuntimeData()->cameraStates[a_vrState];
			}
			return currentState == GetRuntimeData().cameraStates[a_seState];
		}
		std::uint8_t  pad039;        // 039
		std::uint16_t pad03A;        // 03A
		ActorHandle   cameraTarget;  // 03C
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		RUNTIME_DATA_CONTENT;
		RUNTIME_DATA2_CONTENT;
#elif defined(EXCLUSIVE_SKYRIM_VR)
		VR_RUNTIME_DATA_CONTENT;
		RUNTIME_DATA2_CONTENT;
#endif

	private:
		// VR requires a_cameraState with kVR enums > kAnimated
		bool QCameraEquals(CameraState a_cameraState) const;
	};
	STATIC_ASSERT_SIZE(PlayerCamera, 0x168, 0x168, 0x188, 0x40);
}
#undef RUNTIME_DATA_CONTENT
#undef VR_RUNTIME_DATA_CONTENT
#undef RUNTIME_DATA2_CONTENT

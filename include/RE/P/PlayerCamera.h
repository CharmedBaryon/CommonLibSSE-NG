#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTSingleton.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/N/NiPoint3.h"
#include "RE/T/TESCamera.h"

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
			NiPointer<bhkSimpleShapePhantom*> unk00;  // 00
			NiPointer<bhkSimpleShapePhantom*> unk08;  // 08
		};
		static_assert(sizeof(Unk120) == 0x10);

		~PlayerCamera() override;  // 00

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                                                      \
	BSTSmallArray<TESCameraState*, CameraStates::kTotal> tempReturnStates;                   /* 040, VR 040*/     \
	BSTSmartPointer<TESCameraState>                      cameraStates[CameraStates::kTotal]; /* 0B8, VR 0C0*/     \
	Unk120*                                              unk120;                             /* 120, */           \
	NiPointer<bhkRigidBody>                              rigidBody;                          /* 128, VR 130 - ?*/ \
	RefHandle                                            objectFadeHandle;                   /* 130, VR 138 - ?*/ \
	mutable BSSpinLock                                   lock;                               /* 134, VR 13c*/

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x100);
		static_assert(offsetof(RUNTIME_DATA, cameraStates) == 0x78);
		static_assert(offsetof(RUNTIME_DATA, rigidBody) == 0xE8);
		static_assert(offsetof(RUNTIME_DATA, objectFadeHandle) == 0xF0);
		static_assert(offsetof(RUNTIME_DATA, lock) == 0xF4);

		struct VR_RUNTIME_DATA
		{
#define VR_RUNTIME_DATA_CONTENT                                                                                       \
	BSTSmallArray<TESCameraState*, CameraStates::kVRTotal> tempReturnStates;                     /* 040, VR 040*/     \
	BSTSmartPointer<TESCameraState>                        cameraStates[CameraStates::kVRTotal]; /* 0B8, VR 0C0*/     \
	NiPointer<bhkRigidBody>                                rigidBody;                            /* 128, VR 130 - ?*/ \
	RefHandle                                              objectFadeHandle;                     /* 130, VR 138 - ?*/ \
	mutable BSSpinLock                                     lock;                                 /* 134, VR 13c*/     \
	char                                                   VRpad144[14];                         /* VR 144 */
            VR_RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(VR_RUNTIME_DATA) == 0x118);
		static_assert(offsetof(VR_RUNTIME_DATA, cameraStates) == 0x80);
		static_assert(offsetof(VR_RUNTIME_DATA, rigidBody) == 0xF0);
		static_assert(offsetof(VR_RUNTIME_DATA, objectFadeHandle) == 0xF8);
		static_assert(offsetof(VR_RUNTIME_DATA, lock) == 0xFC);

		struct RUNTIME_DATA2
		{
#define RUNTIME_DATA2_CONTENT                                            \
	float         worldFOV;            /* 13C, VR 158*/                  \
	float         firstPersonFOV;      /* 140, VR 15c*/                  \
	NiPoint3      pos;                 /* 144, VR 160 - ?*/              \
	float         idleTimer;           /* 150, VR 16c - ?*/              \
	float         yaw;                 /* 154, VR 170 - ? - in radians*/ \
	std::uint32_t unk158;              /* 158 - ?*/                      \
	std::uint32_t unk15C;              /* 15C - ?*/                      \
	bool          allowAutoVanityMode; /* 160, VR 17c*/                  \
	bool          bowZoomedIn;         /* 161, VR 17d*/                  \
	bool          isWeapSheathed;      /* 162, VR 17e - ?*/              \
	bool          isProcessed;         /* 163, VR 17f - ?*/              \
	std::uint8_t  unk164;              /* 164*/                          \
	std::uint8_t  unk165;              /* 165*/                          \
	std::uint16_t pad166;              /* 166*/
			RUNTIME_DATA2_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA2) == 0x2c);

		// override (TESCamera)
		void SetCameraRoot(NiPointer<NiNode> a_root) override;  // 01

		static PlayerCamera* GetSingleton();

		bool ForceFirstPerson();
		bool ForceThirdPerson();
		bool IsInBleedoutMode() const;
		bool IsInFirstPerson() const;
		bool IsInFreeCameraMode() const;
		bool IsInThirdPerson() const;
		void ToggleFreeCameraMode(bool a_freezeTime);
		void UpdateThirdPerson(bool a_weaponDrawn);

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x40, 0);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x40, 0);
		}

		[[nodiscard]] inline VR_RUNTIME_DATA& GetVRRuntimeData() noexcept
		{
			return REL::RelocateMember<VR_RUNTIME_DATA>(this, 0, 0x40);
		}

		[[nodiscard]] inline const VR_RUNTIME_DATA& GetVRRuntimeData() const noexcept
		{
			return REL::RelocateMember<VR_RUNTIME_DATA>(this, 0, 0x40);
		}

		[[nodiscard]] inline RUNTIME_DATA2& GetRuntimeData2() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA2>(this, 0x13c, 0x158);
		}

		[[nodiscard]] inline const RUNTIME_DATA2& GetRuntimeData2() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA2>(this, 0x13c, 0x158);
		}
		// members
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
		KEEP_FOR_RE();
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(PlayerCamera) == 0x168);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(PlayerCamera) == 0x180);
#endif
}
#undef RUNTIME_DATA_CONTENT
#undef VR_RUNTIME_DATA_CONTENT
#undef RUNTIME_DATA2_CONTENT

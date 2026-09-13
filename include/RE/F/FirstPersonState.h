#pragma once

#include "RE/N/NiPoint3.h"
#include "RE/P/PlayerInputHandler.h"
#include "RE/T/TESCameraState.h"

#include "REL/Common.h"

namespace RE
{
	class NiNode;

	class FirstPersonState :
		public TESCameraState,     // 00
		public PlayerInputHandler  // 20
	{
	public:
		inline static constexpr auto RTTI = RTTI_FirstPersonState;
		inline static constexpr auto VTABLE = VTABLE_FirstPersonState;

		~FirstPersonState() override;  // 00

		// override (TESCameraState)
		void Begin() override;  // 01
		void End() override;    // 02
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		// Function doesn't exist in SE/AE-only builds
#elif defined(EXCLUSIVE_SKYRIM_VR)
		void          Unk_03() override;    // 03 - VR only
#else
		void          Unk_03();             // 03 - Multi-runtime
#endif
		void Update(BSTSmartPointer<TESCameraState>& a_nextState) override;  // 03/04
		void GetRotation(NiQuaternion& a_rotation) override;                 // 04/05
		void GetTranslation(NiPoint3& a_translation) override;               // 05/06
		void SaveGame(BGSSaveFormBuffer* a_buf) override;                    // 06/07
		void LoadGame(BGSLoadFormBuffer* a_buf) override;                    // 07/08
		void Revert(BGSLoadFormBuffer* a_buf) override;                      // 08/09

		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;  // 01
#ifdef EXCLUSIVE_SKYRIM_VR
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_movementData) override;  // 04
#endif

#if defined(HAS_SKYRIM_MULTI_TARGETING) && defined(ENABLE_SKYRIM_SE) && defined(ENABLE_SKYRIM_AE)
		// Both runtimes are compiled in: dispatch by REL::Module::IsAE(), not #ifdef.
#	pragma pack(push, 4)
		struct SE_RUNTIME_DATA
		{
			float         unk7C;                // 7C
			std::uint32_t unk80;                // 80
			bool          cameraOverride;       // 84
			bool          cameraPitchOverride;  // 85
			std::uint16_t unk86;                // 86
			std::uint64_t unk88;                // 88 -- tightly packed against unk86, no gap
		};
#	pragma pack(pop)
		static_assert(sizeof(SE_RUNTIME_DATA) == 0x14);

#	pragma pack(push, 4)
		struct AE_RUNTIME_DATA
		{
			std::uint32_t unk7C;                // 7C
			float         unk80;                // 80
			std::uint32_t unk84;                // 84
			bool          cameraOverride;       // 88
			bool          cameraPitchOverride;  // 89
			std::uint16_t unk8A;                // 8A
			std::uint32_t pad8C;                // 8C -- real 4-byte gap before unk90
			std::uint64_t unk90;                // 90
		};
#	pragma pack(pop)
		static_assert(sizeof(AE_RUNTIME_DATA) == 0x1C);

		[[nodiscard]] inline SE_RUNTIME_DATA* GetSERuntimeData() noexcept
		{
			if (!REL::Module::IsAE()) {
				return &REL::RelocateMember<SE_RUNTIME_DATA>(this, 0x7C, 0);
			}
			return nullptr;
		}
		[[nodiscard]] inline const SE_RUNTIME_DATA* GetSERuntimeData() const noexcept
		{
			return const_cast<FirstPersonState*>(this)->GetSERuntimeData();
		}

		[[nodiscard]] inline AE_RUNTIME_DATA* GetAERuntimeData() noexcept
		{
			if (REL::Module::IsAE()) {
				return &REL::RelocateMember<AE_RUNTIME_DATA>(this, 0, 0x7C);
			}
			return nullptr;
		}
		[[nodiscard]] inline const AE_RUNTIME_DATA* GetAERuntimeData() const noexcept
		{
			return const_cast<FirstPersonState*>(this)->GetAERuntimeData();
		}
#endif

		// members
		NiPoint3      lastPosition;             // 30
		NiPoint3      lastFrameSpringVelocity;  // 3C
		NiPoint3      dampeningOffset;          // 48
		std::uint32_t pad54;                    // 54
		NiAVObject*   firstPersonCameraObj;     // 58
		NiNode*       firstPersonFOVControl;    // 60
		float         sittingRotation;          // 68
		float         unk6C;                    // 6C
		float         unk70;                    // 70
		float         currentPitchOffset;       // 74 - [-100, 100]
		float         targetPitchOffset;        // 78 - [-100, 100]
#if defined(HAS_SKYRIM_MULTI_TARGETING) && defined(ENABLE_SKYRIM_SE) && defined(ENABLE_SKYRIM_AE)
		// Placeholder sized to the larger (AE) layout; real access goes through
		// GetSERuntimeData()/GetAERuntimeData() above, not this member directly.
		std::uint8_t runtimeDataPlaceholder[0x1C];  // 7C
#elif !defined(ENABLE_SKYRIM_AE)
		float         unk7C;                // 7C
		std::uint32_t unk80;                // 80
		bool          cameraOverride;       // 84
		bool          cameraPitchOverride;  // 85
		std::uint16_t unk86;                // 86
		std::uint64_t unk88;                // 88
#else
		std::uint32_t unk7C;                // 7C
		float         unk80;                // 80
		std::uint32_t unk84;                // 84
		bool          cameraOverride;       // 88
		bool          cameraPitchOverride;  // 89
		std::uint16_t unk8A;                // 8A
		std::uint64_t unk90;                // 90
#endif
	};
	STATIC_ASSERT_SIZE(FirstPersonState, 0x90, 0x98, 0xA8);
}

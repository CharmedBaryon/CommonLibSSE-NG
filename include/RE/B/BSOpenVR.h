#pragma once

#include "RE/B/BSTArray.h"
#include "RE/B/BSTHashMap.h"
#include "RE/B/BSVRInterface.h"
#include "RE/N/NiNode.h"

#ifdef ENABLE_SKYRIM_VR
namespace RE
{
	class BSOpenVR : public BSVRInterface
	{
	public:
#	if defined(EXCLUSIVE_SKYRIM_VR)
		inline static constexpr auto RTTI = RTTI_BSOpenVR;
#	endif

		struct Unk238
		{
			// members
			std::uint64_t unk00;  // 00
			std::uint64_t unk08;  // 08
			std::uint64_t unk10;  // 10
			std::uint64_t unk18;  // 18
			std::uint64_t unk20;  // 20
			std::uint64_t unk28;  // 28
			std::uint64_t unk30;  // 30
			std::uint64_t unk38;  // 38
		};
		static_assert(sizeof(Unk238) == 0x40);

		// override
		void                     InitializeVR() override;                                                                                             // 00
		void                     ShutdownVR() override;                                                                                               // 01
		void                     PostPresentHandoff() override;                                                                                       // 02
		void                     Submit(void* a_directXTextureHandle) override;                                                                       // 03 - SubmitForEye, except the logic runs for both eyes
		void                     SubmitForEye(vr::EVREye a_eye, void* a_directXTextureHandle) override;                                               // 04
		void                     SetTrackingSpaceAsStanding() override;                                                                               // 05 - { VR_GetIVRCompositor_140C57880()->SetTrackingSpace(TrackingUniverseStanding) }
		void                     SetTrackingSpaceAsSeated() override;                                                                                 // 06 - { VR_GetIVRCompositor_140C57880()->SetTrackingSpace(TrackingUniverseSeated) }
		void                     Unk_07(void) override;                                                                                               // 07
		void                     GetProjectionRaw(vr::EVREye a_eEye, float* a_pfLeft, float* a_pfRight, float* a_pfTop, float* a_pfBottom) override;  // 08
		NiTransform*             GetEyeToHeadTransform(NiTransform& a_out, bool getRightEye) override;                                                // 09
		NiTransform*             Unk_0A(NiTransform& a_out, bool getRightController, bool a_unk1) override;                                           // 0A
		void                     Unk_0B(void) override;                                                                                               // 0B - Process VR events?
		vr::TrackedDeviceIndex_t GetTrackedDeviceIndexForHMD() override;                                                                              // 0C - { return vr::k_unTrackedDeviceIndex_Hmd; }
		vr::TrackedDeviceIndex_t GetTrackedDeviceIndexForHand(bool getRightHand) override;                                                            // 0D - { return vrSystem->GetTrackedDeviceIndexForControllerRole(isRightHand + 1); } Can return invalid role if not 0 or 1
		void                     TriggerHapticPulse(bool doRightController, float duration) override;                                                 // 0E - Trigger haptics for X * 4,000 microseconds (250 = 1 second)
		void                     Unk_0F(void) override;                                                                                               // 0F
		void                     Unk_10(void) override;                                                                                               // 10
		void                     Unk_11(void) override;                                                                                               // 11 - { return 0; }
		void                     GetRenderTargetSize(std::uint32_t* a_width, std::uint32_t* a_height) override;                                                     // 12
		void                     Unk_13() override;                                                                                                   // 13
		NiPointer<NiNode>*       GetControllerNode(RE::NiPointer<NiNode>& a_out, Hand a_hand) override;                                               // 14
		void                     Unk_15(void) override;                                                                                               // 15 - { return 0; }
		HMDDeviceType            GetHMDDeviceType() override;                                                                                         // 16 - { return hmdDeviceType; }
		NiPointer<NiNode>*       CreateControllerNode(RE::NiPointer<NiNode>& a_out, Hand a_hand) override;                                            // 17

		static BSOpenVR* GetSingleton();

		static vr::IVRCompositor*   GetIVRCompositor();
		static vr::IVROverlay*      GetIVROverlay(Unk190* a_unk190);
		static vr::IVRRenderModels* GetIVRRenderModels();
		static vr::IVRSettings*     GetIVRSettings();
		static vr::IVRSystem*       GetIVRSystem();

		// members
		vr::IVRSystem*             vrSystem;                       // 208
		void*                      unk210;                         // 210
		std::uint64_t              unk218;                         // 218
		std::uint64_t              unk220;                         // 220
		std::uint64_t              unk228;                         // 228
		NiPointer<NiSourceTexture> unk230;                         // 230 - name is SIMPLE_NORMAL_MAP
		Unk238                     unk238[4];                      // 238
		std::uint64_t              unk338;                         // 380
		std::uint64_t              unk340[9];                      // 340
		NiPointer<NiNode>          controllerNodes[Hand::kTotal];  // 388 - Cloned for PlayerCharacter's LeftValveIndexControllerNode/RightValveIndexControllerNode
		HMDDeviceType              hmdDeviceType;                  // 398 - Set by comparing TrackedSystemName to "lighthouse", "oculus" and "holographic". Defaults to "lighthouse" if none match
		NiTransform                eyeToHeadTransform[2];          // 39C - 0 is left eye, 1 is right eye
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSOpenVR) == 0x408);
}
#endif

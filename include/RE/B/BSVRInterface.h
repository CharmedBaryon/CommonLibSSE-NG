#pragma once

#ifdef ENABLE_SKYRIM_VR

#	include "RE/B/BSTEvent.h"
#	include "RE/N/NiNode.h"
#	include "RE/N/NiSmartPointer.h"
#	include "RE/N/NiTransform.h"
#	include "openvr.h"

namespace RE
{
	struct VROverlayChange;
	struct VRDeviceConnectionChange;
	struct VRResetHMDHeight;

	class BSVRInterface :
		public BSTEventSource<VROverlayChange>,           // 08
		public BSTEventSource<VRDeviceConnectionChange>,  // 60
		public BSTEventSource<VRResetHMDHeight>           // B8
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSVRInterface;

		enum class HMDDeviceType : std::uint32_t
		{
			kLighthouse,   // used for sDriverVive:VR?
			kOculus,       // used for sDriverOculus:VR?
			kHolographics  // used for sDriverWindowsMR:VR?
		};

		enum Hand : std::uint32_t
		{
			kLeft,
			kRight,
			kTotal
		};

		struct Unk118
		{
#	pragma pack(push, 4)
			struct PoseTransform
			{
				// Status based on openvr's ETrackingResult. Calibrated/uninitialized = kNotRunning
				enum class TrackingStatus : std::uint32_t
				{
					kNotRunning,
					kRunningOk,
					kOutOfRange
				};

				TrackingStatus poseStatus;           // 00
				NiTransform    renderPoseTransform;  // 04
				NiTransform    gamePoseTransform;    // 38
			};
			static_assert(sizeof(PoseTransform) == 0x6C);
#	pragma pack(pop)

			// members
			Unk118*        unk00;          // 00
			Unk118*        unk08;          // 08
			Unk118*        unk10;          // 10
			std::uint8_t   unk18;          // 18
			bool           unk19;          // 19
			std::uint16_t  unk1A;          // 18
			std::uint32_t  poseIndex;      // 1C
			PoseTransform* poseTransform;  // 20
			std::uint64_t  unk28;          // 28
			std::uint64_t  unk30;          // 30
			std::uint64_t  unk38;          // 38
			std::uint64_t  unk40;          // 40
			std::uint64_t  unk48;          // 48
			std::uint64_t  unk50;          // 50
			NiTransform    unk58;          // 58
		};
		static_assert(sizeof(Unk118) == 0x90);

		struct COpenVRContext
		{
			vr::IVRSystem*          vrSystem;           // 00
			vr::IVRChaperone*       vrChaperone;        // 08
			vr::IVRChaperoneSetup*  vrChaperoneSetup;   // 10
			vr::IVRCompositor*      vrCompositor;       // 18
			vr::IVROverlay*         vrOverlay;          // 20
			vr::IVRResources*       vrResources;        // 28
			vr::IVRRenderModels*    vrRenderModels;     // 30
			vr::IVRExtendedDisplay* vrExtendedDisplay;  // 38
			vr::IVRSettings*        vrSettings;         // 40
			vr::IVRApplications*    vrApplications;     // 48
			vr::IVRTrackedCamera*   vrTrackedCamera;    // 50
			vr::IVRScreenshots*     vrScreenshots;      // 58
			vr::IVRDriverManager*   vrDriverManager;    // 60
		};
		static_assert(sizeof(COpenVRContext) == 0x68);

		// add
		virtual void                       InitializeVR();                                                                                                                                                 // 00
		virtual void                       ShutdownVR();                                                                                                                                                   // 01
		virtual void                       PostPresentHandoff();                                                                                                                                           // 02
		virtual vr::EVRCompositorError     Submit(const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds = nullptr, vr::EVRSubmitFlags nSubmitFlags = vr::Submit_Default) = 0;                // 03
		virtual vr::EVRCompositorError     SubmitForEye(vr::EVREye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds = nullptr, vr::EVRSubmitFlags nSubmitFlags = vr::Submit_Default);  // 04
		virtual void                       SetTrackingSpaceAsStanding();                                                                                                                                   // 05
		virtual void                       SetTrackingSpaceAsSeated();                                                                                                                                     // 06
		virtual void                       GetProjectionMatrix(NiTransform* a_out, vr::EVREye a_eye, float a_fNearZ, float a_fFarZ);                                                                       // 07
		virtual void                       GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom);                                                                // 08
		virtual NiTransform*               GetEyeToHeadTransform(NiTransform& a_out, bool getRightEye);                                                                                                    // 09
		virtual NiTransform*               GetHandTransform(NiTransform& a_out, bool getRightController, bool a_unk1);                                                                                     // 0A - maps getRightController to vr::ETrackedControllerRole, resolves the device index via IVRSystem::GetTrackedDeviceIndexForControllerRole, and writes its transform to a_out. Role of a_unk1 unconfirmed.
		virtual void                       ProcessVREvents(void);                                                                                                                                          // 0B
		virtual vr::TrackedDeviceIndex_t   GetTrackedDeviceIndexForHMD();                                                                                                                                  // 0C
		virtual vr::TrackedDeviceIndex_t   GetTrackedDeviceIndexForHand(bool getRightHand);                                                                                                                // 0D
		virtual void                       TriggerHapticPulse(bool doRightController, float duration);                                                                                                     // 0E
		virtual vr::ETrackedControllerRole GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t a_deviceIndex);                                                                                 // 0F
		virtual void                       UpdatePoses(bool a_useLivePoses);                                                                                                                               // 10 - a_useLivePoses selects IVRCompositor::WaitGetPoses (true) vs GetLastPoses (false), then processes each device with a valid render+game pose.
		virtual void                       Unk_11(void);                                                                                                                                                   // 11
		virtual void                       GetRenderTargetSize(std::uint32_t* a_width, std::uint32_t* a_height);                                                                                           // 12
		virtual void                       UpdateHMDFoV(void);                                                                                                                                             // 13
		virtual RE::NiPointer<NiNode>*     GetControllerNode(RE::NiPointer<NiNode>& a_out, Hand a_hand);                                                                                                   // 14
		virtual void                       Unk_15(void);                                                                                                                                                   // 15
		virtual HMDDeviceType              GetHMDDeviceType();                                                                                                                                             // 16
		virtual RE::NiPointer<NiNode>*     CreateControllerNode(RE::NiPointer<NiNode>& a_out, Hand a_hand);                                                                                                // 17

		// members
		std::uint8_t          unk110;               // 110
		Unk118*               unk118;               // 118 - Possibly a data structure for storing pose data?
		std::uint64_t         unk120;               // 120
		NiTransform           renderTransform;      // 128 - Headset pose render transform
		NiTransform           gameTransform;        // 15C - Headset pose game transform
		COpenVRContext        vrContext;            // 190
		vr::VROverlayHandle_t inputOverlay;         // 1F8 - current overlay handle? Used in 2D overlay menus like JournalMenu
		bool                  isHeadsetTrackingOk;  // 200 - Headset is active and skyrim is receiving tracking data
	};
	static_assert(sizeof(BSVRInterface) == 0x208);
}
#endif

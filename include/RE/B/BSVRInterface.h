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

		struct Unk190
		{
			// members
			std::uint64_t   unk00;       // 00
			std::uint64_t   unk08;       // 08
			std::uint64_t   unk10;       // 10
			std::uint64_t   unk18;       // 18
			vr::IVROverlay* ivrOverlay;  // 20
			std::uint64_t   unk28;       // 28
			std::uint64_t   unk30;       // 30
			std::uint64_t   unk38;       // 38
			std::uint64_t   unk40;       // 40
			std::uint64_t   unk48;       // 48
			std::uint64_t   unk50;       // 50
			std::uint64_t   unk58;       // 58
			std::uint64_t   unk60;       // 60
		};
		static_assert(sizeof(Unk190) == 0x68);

		// add
		virtual void                     InitializeVR();                                                                                   // 00
		virtual void                     ShutdownVR();                                                                                     // 01
		virtual void                     PostPresentHandoff();                                                                             // 02
		virtual void                     Submit(void* a_directXTextureHandle);                                                             // 03
		virtual void                     SubmitForEye(vr::EVREye, void* a_directXTextureHandle);                                           // 04
		virtual void                     SetTrackingSpaceAsStanding();                                                                     // 05
		virtual void                     SetTrackingSpaceAsSeated();                                                                       // 06
		virtual void                     Unk_07(void);                                                                                     // 07
		virtual void                     GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom);  // 08
		virtual NiTransform*             GetEyeToHeadTransform(NiTransform& a_out, bool getRightEye);                                      // 09
		virtual NiTransform*             Unk_0A(NiTransform& a_out, bool getRightController, bool a_unk1);                                 // 0A
		virtual void                     Unk_0B(void);                                                                                     // 0B - Processes events?
		virtual vr::TrackedDeviceIndex_t GetTrackedDeviceIndexForHMD();                                                                    // 0C
		virtual vr::TrackedDeviceIndex_t GetTrackedDeviceIndexForHand(bool getRightHand);                                                  // 0D
		virtual void                     TriggerHapticPulse(bool doRightController, float duration);                                       // 0E
		virtual void                     Unk_0F(void);                                                                                     // 0F
		virtual void                     Unk_10(void);                                                                                     // 10
		virtual void                     Unk_11(void);                                                                                     // 11
		virtual void                     GetRenderTargetSize(std::uint32_t* a_width, std::uint32_t* a_height);                             // 12
		virtual void                     Unk_13(void);                                                                                     // 13
		virtual RE::NiPointer<NiNode>*   GetControllerNode(RE::NiPointer<NiNode>& a_out, Hand a_hand);                                     // 14
		virtual void                     Unk_15(void);                                                                                     // 15
		virtual HMDDeviceType            GetHMDDeviceType();                                                                               // 16
		virtual RE::NiPointer<NiNode>*   CreateControllerNode(RE::NiPointer<NiNode>& a_out, Hand a_hand);                                  // 17

		// members
		std::uint8_t          unk110;               // 110
		Unk118*               unk118;               // 118 - Possibily a data structure for storing pose data?
		std::uint64_t         unk120;               // 120
		NiTransform           renderTransform;      // 128 - Headset pose render transform
		NiTransform           gameTransform;        // 15C - Headset pose game transform
		Unk190*               unk190;               // 190
		std::uint64_t         unk198;               // 198
		std::uint64_t         unk1A0;               // 1A0
		std::uint64_t         unk1A8;               // 1A8
		vr::IVROverlay*       ivrOverlay;           // 1B0
		std::uint64_t         unk1B8;               // 1B8
		std::uint64_t         unk1C0;               // 1C0
		std::uint64_t         unk1C8;               // 1C8
		std::uint64_t         unk1D0;               // 1D0
		std::uint64_t         unk1D8;               // 1D8
		std::uint64_t         unk1E0;               // 1E0
		std::uint64_t         unk1E8;               // 1E8
		std::uint64_t         unk1F0;               // 1F0
		vr::VROverlayHandle_t unk1F8;               // 1F8 - current overlay handle? Used in 2D overlay menus like JournalMenu
		bool                  isHeadsetTrackingOk;  // 200 - Headset is active and skyrim is receiving tracking data
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSVRInterface) == 0x208);
}
#endif

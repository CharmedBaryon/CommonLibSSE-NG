#pragma once

#include "REX/W32.h"

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
		void                       InitializeVR() override;                                                                                                                                                       // 00
		void                       ShutdownVR() override;                                                                                                                                                         // 01
		void                       PostPresentHandoff() override;                                                                                                                                                 // 02
		vr::EVRCompositorError     Submit(const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds = nullptr, vr::EVRSubmitFlags nSubmitFlags = vr::Submit_Default) override;                          // 03 - SubmitForEye, except the logic runs for both eyes
		vr::EVRCompositorError     SubmitForEye(vr::EVREye a_eye, const vr::Texture_t* pTexture, const vr::VRTextureBounds_t* pBounds = nullptr, vr::EVRSubmitFlags nSubmitFlags = vr::Submit_Default) override;  // 04
		void                       SetTrackingSpaceAsStanding() override;                                                                                                                                         // 05 - { VR_GetIVRCompositor_140C57880()->SetTrackingSpace(TrackingUniverseStanding) }
		void                       SetTrackingSpaceAsSeated() override;                                                                                                                                           // 06 - { VR_GetIVRCompositor_140C57880()->SetTrackingSpace(TrackingUniverseSeated) }
		void                       GetProjectionMatrix(NiTransform* a_out, vr::EVREye a_eye, float a_fNearZ, float a_fFarZ) override;                                                                             // 07
		void                       GetProjectionRaw(vr::EVREye a_eEye, float* a_pfLeft, float* a_pfRight, float* a_pfTop, float* a_pfBottom) override;                                                            // 08
		NiTransform*               GetEyeToHeadTransform(NiTransform& a_out, bool getRightEye) override;                                                                                                          // 09
		NiTransform*               GetHandTransform(NiTransform& a_out, bool getRightController, bool a_unk1) override;                                                                                           // 0A - maps getRightController to vr::ETrackedControllerRole, resolves the device index via IVRSystem::GetTrackedDeviceIndexForControllerRole, and writes its transform to a_out. Role of a_unk1 unconfirmed.
		void                       ProcessVREvents(void) override;                                                                                                                                                // 0B
		vr::TrackedDeviceIndex_t   GetTrackedDeviceIndexForHMD() override;                                                                                                                                        // 0C - { return vr::k_unTrackedDeviceIndex_Hmd; }
		vr::TrackedDeviceIndex_t   GetTrackedDeviceIndexForHand(bool getRightHand) override;                                                                                                                      // 0D - { return vrSystem->GetTrackedDeviceIndexForControllerRole(isRightHand + 1); } Can return invalid role if not 0 or 1
		void                       TriggerHapticPulse(bool doRightController, float duration) override;                                                                                                           // 0E - Trigger haptics for X * 4,000 microseconds (250 = 1 second)
		vr::ETrackedControllerRole GetControllerRoleForTrackedDeviceIndex(vr::TrackedDeviceIndex_t a_deviceIndex) override;                                                                                       // 0F
		void                       UpdatePoses(bool a_useLivePoses) override;                                                                                                                                     // 10 - a_useLivePoses selects IVRCompositor::WaitGetPoses (true) vs GetLastPoses (false), then processes each device with a valid render+game pose.
		void                       Unk_11(void) override;                                                                                                                                                         // 11 - { return 0; }
		void                       GetRenderTargetSize(std::uint32_t* a_width, std::uint32_t* a_height) override;                                                                                                 // 12
		void                       UpdateHMDFoV() override;                                                                                                                                                       // 13
		NiPointer<NiNode>*         GetControllerNode(RE::NiPointer<NiNode>& a_out, Hand a_hand) override;                                                                                                         // 14
		void                       Unk_15(void) override;                                                                                                                                                         // 15 - { return 0; }
		HMDDeviceType              GetHMDDeviceType() override;                                                                                                                                                   // 16 - { return hmdDeviceType; }
		NiPointer<NiNode>*         CreateControllerNode(RE::NiPointer<NiNode>& a_out, Hand a_hand) override;                                                                                                      // 17

		static BSOpenVR* GetSingleton();

		static vr::IVRCompositor* GetIVRCompositor();
		/**
		 * Ensures the IVROverlay pointer in the given COpenVRContext is valid and up-to-date.
		 *
		 * This function checks if the OpenVR initialization token has changed. If so, it clears all interface pointers
		 * in the context and updates the token. If the overlay pointer is null, it calls VR_GetGenericInterface to
		 * retrieve the IVROverlay interface and stores it in the context. This matches the lazy initialization pattern
		 * used internally by OpenVR. Call this before using context->vrOverlay to ensure it is valid.
		 *
		 * @warning The returned IVROverlay interface is the game's proxied version. While it is valid for most
		 * overlay operations (creation, positioning, etc.), it appears to lack the necessary permissions for
		 * texture submission from a custom DLL. Calls to SetOverlayTexture using this pointer will likely fail
		 * with VROverlayError_PermissionDenied. The recommended workaround is to use `GetCleanIVROverlay()` for
		 * texture submission and this interface for all other overlay operations.
		 *
		 * Typical usage (as seen in Skyrim VR):
		 *     auto* context = RE::BSOpenVR::GetSingleton()->vrContext;
		 *     RE::BSOpenVR::GetIVROverlayFromContext(context);
		 *     auto* overlay = context->vrOverlay;
		 *
		 * @param a_vrContext Pointer to the COpenVRContext structure to update.
		 */
		static vr::IVROverlay*      GetIVROverlayFromContext(COpenVRContext* a_vrContext);
		static vr::IVRRenderModels* GetIVRRenderModels();
		static vr::IVRSettings*     GetIVRSettings();
		static vr::IVRSystem*       GetIVRSystem();

		/**
		 * Acquires a "clean" IVROverlay interface directly from the OpenVR runtime.
		 *
		 * This bypasses the game's proxied interface and should be used for any operations
		 * that require direct, unproxied access, such as SetOverlayTexture, which may otherwise
		 * fail with VROverlayError_PermissionDenied.
		 *
		 * The function handles one-time initialization and returns a cached pointer on subsequent calls.
		 *
		 * @return A valid vr::IVROverlay* on success, otherwise nullptr.
		 */
		static vr::IVROverlay* GetCleanIVROverlay()
		{
			if (cleanOverlay) {
				return cleanOverlay;
			}

			// Define the function pointer type locally to avoid header conflicts
			typedef void* (*pfnVRGetGenericInterface)(const char* pchInterfaceVersion, vr::EVRInitError* peError);

			REX::W32::HMODULE openvr_handle = REX::W32::GetModuleHandleA("openvr_api.dll");
			if (!openvr_handle) {
				return nullptr;
			}

			auto VR_GetGenericInterface = (pfnVRGetGenericInterface)REX::W32::GetProcAddress(openvr_handle, "VR_GetGenericInterface");
			if (!VR_GetGenericInterface) {
				return nullptr;
			}

			vr::EVRInitError eError = vr::VRInitError_None;
			cleanOverlay = (vr::IVROverlay*)VR_GetGenericInterface(vr::IVROverlay_Version, &eError);

			if (eError != vr::VRInitError_None) {
				cleanOverlay = nullptr;
			}

			return cleanOverlay;
		}

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

		static float GetHapticPulseScale();
		static void  SetHapticPulseScale(float value);

	private:
		inline static vr::IVROverlay* cleanOverlay = nullptr;
	};
	static_assert(sizeof(BSOpenVR) == 0x408);
}
#endif

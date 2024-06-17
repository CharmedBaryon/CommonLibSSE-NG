#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTSingleton.h"
#include "RE/I/InterfaceLightSchemes.h"
#include "RE/N/NiColor.h"
#include "RE/N/NiFrustum.h"
#include "RE/N/NiMatrix3.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BSCullingProcess;
	class BSLight;
	class BSShaderAccumulator;
	class NiAVObject;
	class NiCamera;
	class NiNode;
	class ShadowSceneNode;
	class TESImageSpaceModifier;

	class MenuLight
	{
	public:
		// members
		NiColor            color;         // 00
		NiPoint3           translate;     // 0C
		float              radius;        // 18
		float              fade;          // 1C
		bool               castsShadows;  // 20
		NiPointer<BSLight> light;         // 28
		MenuLight*         last;          // 30
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(MenuLight) == 0x38);

	class UI3DSceneManager : public BSTSingletonSDM<UI3DSceneManager>
	{
	public:
		static UI3DSceneManager* GetSingleton();

		void AttachChild(NiAVObject* a_obj);
		void AttachChild(NiAVObject* a_obj, INTERFACE_LIGHT_SCHEME a_scheme);
		void DetachChild(NiAVObject* a_obj);
		void SetCameraFOV(float a_fov);
		void SetCameraRotate(const NiMatrix3& a_rotate);
		void SetCameraPosition(const NiPoint3& a_pos);

		// members
		std::uint8_t                               pad01;               // 01
		std::uint16_t                              pad02;               // 02
		std::uint32_t                              pad04;               // 04
		BSCullingProcess*                          cullingProcess;      // 08
		NiPointer<BSShaderAccumulator>             unk10;               // 10
		NiPointer<BSShaderAccumulator>             unk18;               // 18
		NiPointer<NiCamera>                        camera;              // 20
		mutable BSSpinLock                         lock;                // 28
		ShadowSceneNode*                           shadowSceneNode;     // 30
		NiPointer<NiNode>                          menuObjects[8];      // 38
		BSTArray<MenuLight*>                       menuLights;          // 78
		INTERFACE_LIGHT_SCHEME                     currentlightScheme;  // 90
		std::uint32_t                              pad94;               // 94
		BSTArray<INTERFACE_LIGHT_SCHEME>           lightSchemes;        // 98
		BSTArray<NiPointer<TESImageSpaceModifier>> imageSpaceMods;      // B0
		NiPoint3                                   cachedCameraPos;     // C8
		NiMatrix3                                  cachedCameraRot;     // D0
		NiFrustum                                  viewFrustum;         // F8
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(UI3DSceneManager) == 0x118);
}

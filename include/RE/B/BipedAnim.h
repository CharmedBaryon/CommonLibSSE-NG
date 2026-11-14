#pragma once

#include "RE/B/BSIntrusiveRefCounted.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSResourceHandle.h"
#include "RE/B/BSTObjectArena.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/B/BipedObjects.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/W/WeaponAnimationGraphManagerHolder.h"

namespace RE
{
	class BGSTextureSet;
	class NiAVObject;
	class NiNode;
	class TESForm;
	class TESModel;
	class TESObjectARMA;

	struct BIPOBJECT
	{
	public:
		// members
		TESForm*                                           item;           // 00
		TESObjectARMA*                                     addon;          // 08
		TESModel*                                          part;           // 10
		BGSTextureSet*                                     skinTexture;    // 18
		NiPointer<NiAVObject>                              partClone;      // 20
		BSTHeapObjectArena<ModelDBHandle, 16>              handleList;     // 28
		BSTSmartPointer<WeaponAnimationGraphManagerHolder> weaponManager;  // 60 - smart ptr
		bool                                               skinned;        // 68
		ModelDBHandle                                      partHandle;     // 70
	};
	static_assert(sizeof(BIPOBJECT) == 0x78);

	class BipedAnim : public BSIntrusiveRefCounted
	{
	public:
		~BipedAnim();

		void       RemoveAllParts();
		BIPOBJECT* GetShieldObject();

		std::uint32_t   pad0004;                                 // 0004
		NiNode*         root;                                    // 0008
		BIPOBJECT       objects[BIPED_OBJECTS::kTotal];          // 0010
		BIPOBJECT       bufferedObjects[BIPED_OBJECTS::kTotal];  // 13C0
		ObjectRefHandle actorRef;                                // 2770
		std::uint32_t   pad2774;                                 // 2774

	private:
		void Dtor();
	};
	static_assert(sizeof(BipedAnim) == 0x2778);
}

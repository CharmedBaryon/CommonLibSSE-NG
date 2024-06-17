#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class NiAVObject;
	class QueuedAnimationObject;
	class TESObjectANIO;

	class AnimationObject
	{
	public:
		//members
		ObjectRefHandle                  handle;          // 00
		std::uint32_t                    pad04;           // 04
		TESObjectANIO*                   object;          // 08
		NiPointer<NiAVObject>            attachedObject;  // 10
		NiPointer<QueuedAnimationObject> queuedObject;    // 18
		bool                             visible;         // 20
		std::uint8_t                     pad21;           // 21
		std::uint16_t                    pad22;           // 22
		std::uint32_t                    pad24;           // 24
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(AnimationObject) == 0x28);

	class AnimationObjects : public BSTSingletonSDM<AnimationObjects>
	{
	public:
		[[nodiscard]] static AnimationObjects* GetSingleton()
		{
			REL::Relocation<AnimationObjects**> singleton{ RELOCATION_ID(514179, 400328) };
			return *singleton;
		}

		// members
		std::uint8_t                               pad01;             // 01
		std::uint16_t                              pad02;             // 02
		std::uint32_t                              pad04;             // 04
		BSTArray<BSTSmartPointer<AnimationObject>> animationObjects;  // 08
		BSSpinLock                                 lock;              // 20
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(AnimationObjects) == 0x28);
}

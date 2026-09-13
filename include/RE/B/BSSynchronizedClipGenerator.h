#pragma once
#include "RE/H/hkbClipGenerator.h"

namespace RE
{
	class BSSynchronizedClipGenerator : public hkbGenerator
	{
	public:
		class hkbDefaultSynchronizedScene : public hkReferencedObject
		{
			inline static constexpr auto RTTI = RTTI_BSSynchronizedClipGenerator__hkbDefaultSynchronizedScene;
			inline static constexpr auto VTABLE = VTABLE_BSSynchronizedClipGenerator__hkbDefaultSynchronizedScene;

			~hkbDefaultSynchronizedScene() override;  // 00

			// members
			BSReadWriteLock lock;  // 10
		};
		static_assert(sizeof(hkbDefaultSynchronizedScene) == 0x18);

		class hkbSynchronizedAnimationScene : public hkbDefaultSynchronizedScene
		{
		public:
			inline static constexpr auto RTTI = RTTI_BSSynchronizedClipGenerator__hkbSynchronizedAnimationScene;
			inline static constexpr auto VTABLE = VTABLE_BSSynchronizedClipGenerator__hkbSynchronizedAnimationScene;

			~hkbSynchronizedAnimationScene() override;  // 00
		};
		static_assert(sizeof(hkbSynchronizedAnimationScene) == 0x18);

		inline static constexpr auto RTTI = RTTI_BSSynchronizedClipGenerator;
		inline static constexpr auto VTABLE = VTABLE_BSSynchronizedClipGenerator;

		~BSSynchronizedClipGenerator() override;  // 00

		// members
		std::uint32_t                           unk48;
		std::uint32_t                           unk4C;
		hkbClipGenerator*                       clipGenerator;                // 50
		hkStringPtr                             syncAnimPrefix;               // 58
		bool                                    syncClipIgnoreMarkPlacement;  // 60
		float                                   getToMarkTime;                // 64
		float                                   markErrorThreshold;           // 68
		bool                                    leadCharacter;                // 6C
		bool                                    reorientSupportChar;          // 6D
		bool                                    applyMotionFromRoot;          // 6E
		class BGSSynchronizedAnimationInstance* synchronizedScene;            // 70
		std::uint32_t                           unk78;
		std::uint32_t                           unk7C;
		hkQsTransform                           startingWorldFromModel;                      // 80
		hkQsTransform                           worldFromModelWithRootMotion;                // B0
		hkQsTransform                           unkTransform;                                // E0
		float                                   getToMarkProgress;                           // 110
		hkaAnimationBinding*                    binding;                                     // 118
		void*                                   eventWithPrefixIdToEventWithoutPrefixIdMap;  // 120  hkPointerMap<int, int>*
		std::uint16_t                           synchronizedAnimationBindingIndex;           // 128
		bool                                    doneReorientingSupportChar;                  // 12A
		bool                                    unk12B;                                      // 12B
		bool                                    unk12C;                                      // 12C
	};
	static_assert(sizeof(BSSynchronizedClipGenerator) == 0x130);
}

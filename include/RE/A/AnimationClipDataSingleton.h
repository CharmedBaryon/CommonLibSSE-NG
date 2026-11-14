#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSIntrusiveRefCounted.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTHashMap.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class AnimationClipDataSingleton
	{
		class BoundAnimationData
		{
		};

		class ClipTriggerData
		{
			BSFixedString name;
			float         time;
			uint32_t      padC;
		};
		static_assert(sizeof(ClipTriggerData) == 0x10);

		class ClipData
		{
		public:
			bool GetEventTime(const BSFixedString& event_name, float& time);

			// members
			float           motionSpeed;     // 00
			uint16_t        bound_data_ind;  // 04
			uint16_t        numTriggers;     // 06
			ClipTriggerData triggerData[1];  // 08 -- actually [numTriggers]
		};
		static_assert(sizeof(ClipData) == 0x18);

		class AnimationClipData
		{
		public:
			ClipData*           clipGeneratorData;
			BoundAnimationData* boundAnimationData;
		};
		static_assert(sizeof(AnimationClipData) == 0x10);

		class AnimationData : public BSIntrusiveRefCounted
		{
		public:
			BSTHashMap<BSFixedString, ClipData*> clips;        // 08 -- key = clip_name
			BSTArray<BoundAnimationData>         bound_datas;  // 38
			BSTArray<BSFixedString>              hkxFiles;     // 50
		};
		static_assert(sizeof(AnimationData) == 0x68);

		virtual ~AnimationClipDataSingleton();

		bool GetClipInformation(const BSFixedString& project_name, const BSFixedString& clip_name, AnimationClipData& ClipInformation);

		// members
		uint64_t                                            field_8;      // 08
		BSTHashMap<BSFixedString, NiPointer<AnimationData>> anim_datas;   // 10 -- key = project_name
		BSTArray<BSFixedString>                             mb_hkxFiles;  // 40
	};
	static_assert(sizeof(AnimationClipDataSingleton) == 0x58);
}

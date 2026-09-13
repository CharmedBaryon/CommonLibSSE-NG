#pragma once

#include "RE/B/BSTArray.h"

namespace RE
{
	class BSFaceGenKeyframe
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSFaceGenKeyframe;
		inline static constexpr auto VTABLE = VTABLE_BSFaceGenKeyframe;

		enum class Type : std::int32_t
		{
			Undefined = -1,
			Phoneme,
			Expression,
			Modifier,
			Custom
		};

		virtual ~BSFaceGenKeyframe();  // 00

		// add
		virtual bool               Unk_01(BSTArray<BSFaceGenKeyframe*>& a_arr) = 0;                                                // 01
		virtual bool               Interpolate(BSFaceGenKeyframe* a_keyframe1, BSFaceGenKeyframe* a_keyframe2, float a_k) = 0;     // 02 - Linear interpolation between keyframes
		virtual bool               Interpolate(BSFaceGenKeyframe* a_keyframe, float a_k, bool a_ignoreSmall, bool a_copyBig) = 0;  // 03 - Linear interpolation between keyframes
		virtual void               Reset(bool a_initToZero) = 0;                                                                   // 04
		virtual BSFaceGenKeyframe* Clone() = 0;                                                                                    // 05
		virtual void               Copy(BSFaceGenKeyframe* a_keyframe) = 0;                                                        // 06
		virtual bool               NotEqual(BSFaceGenKeyframe* a_keyframe) = 0;                                                    // 07
		virtual float              GetMaxValue() = 0;                                                                              // 08
		virtual bool               IsZero() = 0;                                                                                   // 09
		virtual bool               TransitionUpdate(float a_timeDelta, BSFaceGenKeyframe* a_keyframe) = 0;                         // 0A
		virtual bool               NotZero() = 0;                                                                                  // 0B
		virtual bool               IsKeyframeMultiple();                                                                           // 0C { return false; };
		virtual bool               IsKeyframeExclusive();                                                                          // 0D { return false; };

		// members
		Type  type;   // 08
		float timer;  // 0C
	};
	static_assert(sizeof(BSFaceGenKeyframe) == 0x10);
}

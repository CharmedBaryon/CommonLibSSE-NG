#pragma once

#include "RE/H/hkQsTransform.h"
#include "RE/H/hkaDefaultAnimationControl.h"
#include "RE/H/hkbContext.h"
#include "RE/H/hkbEventBase.h"
#include "RE/H/hkbGenerator.h"

namespace RE
{
	class hkbEventProperty : public hkbEventBase
	{
	private:
		KEEP_FOR_RE()
	};

	class hkClipTrigger
	{
	public:
		float            localTime;            // 00
		hkbEventProperty event;                // 08
		bool             relativeToEndOfClip;  // 18
		bool             acyclic;              // 19
		bool             isAnnotation;         // 1A
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkClipTrigger) == 0x20);

	class hkbClipTriggerArray : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbClipTriggerArray;
		inline static constexpr auto VTABLE = VTABLE_hkbClipTriggerArray;

		~hkbClipTriggerArray() override;  // 00

		// members
		hkArray<hkClipTrigger> triggers;  // 10
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkbClipTriggerArray) == 0x20);

	class hkbClipGenerator : public hkbGenerator
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbClipGenerator;
		inline static constexpr auto VTABLE = VTABLE_hkbClipGenerator;

		enum PlaybackMode
		{
			kModeSinglePlay = 0,
			kModeLooping = 1,
			kModeUserControlled = 2,
			kModePingPong = 3,
			kModeCount = 4
		};

		~hkbClipGenerator() override;  // 00

		// override (hkbNode)
		void Activate(const hkbContext& a_context) override;                  // 04
		void Update(const hkbContext& a_context, float a_timestep) override;  // 05
		void Deactivate(const hkbContext& a_context) override;                // 07

		// override (hkbGenerator)
		void Generate(const hkbContext& a_context) override;    // 17
		void UpdateSync(const hkbContext& a_context) override;  // 19

		// members
		hkStringPtr                             animationName;                       // 048
		hkRefPtr<hkbClipTriggerArray>           triggers;                            // 050
		float                                   cropStartAmountLocalTime;            // 058
		float                                   cropEndAmountLocalTime;              // 05C
		float                                   startTime;                           // 060
		float                                   playbackSpeed;                       // 064
		float                                   enforcedDuration;                    // 068
		float                                   userControlledTimeFraction;          // 06C
		std::uint16_t                           animationBindingIndex;               // 070
		stl::enumeration<PlaybackMode, uint8_t> mode;                                // 072
		std::uint8_t                            flags;                               // 073
		std::uint32_t                           unk74;                               // 074
		hkArray<hkRefVariant>                   animDatas;                           // 078
		hkRefPtr<hkaDefaultAnimationControl>    animationControl;                    // 088
		hkRefPtr<hkbClipTriggerArray>           originalTriggers;                    // 090
		hkaDefaultAnimationControlMapperData*   mapperData;                          // 098
		hkaAnimationBinding*                    binding;                             // 0A0
		hkRefVariant                            mirroredAnimation;                   // 0A8
		hkQsTransform                           extractedMotion;                     // 0B0
		hkArray<hkRefVariant>                   echos;                               // 0E0
		float                                   localTime;                           // 0F0
		float                                   time;                                // 0F4
		float                                   previousUserControlledTimeFraction;  // 0F8
		std::int32_t                            bufferSize;                          // 0FC
		std::int32_t                            echoBufferSize;                      // 100
		bool                                    atEnd;                               // 104
		bool                                    ignoreStartTime;                     // 105
		bool                                    pingPongBackward;                    // 106
		std::uint8_t                            pad107[9];                           // 107
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkbClipGenerator) == 0x110);
}

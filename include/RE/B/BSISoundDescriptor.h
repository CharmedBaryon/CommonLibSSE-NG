#pragma once

#include "RE/B/BSAudioMonitor.h"
#include "RE/B/BSCoreTypes.h"
#include "RE/B/BSTArray.h"
#include "RE/I/ID.h"

namespace RE
{
	class BSISoundCategory;
	class BSISoundOutputModel;

	class BSISoundDescriptor
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSISoundDescriptor;
		inline static constexpr auto VTABLE = VTABLE_BSISoundDescriptor;

		class BSIPlaybackCharacteristics
		{
		public:
			inline static constexpr auto RTTI = RTTI_BSISoundDescriptor__BSIPlaybackCharacteristics;
			inline static constexpr auto VTABLE = VTABLE_BSISoundDescriptor__BSIPlaybackCharacteristics;

			virtual ~BSIPlaybackCharacteristics();  // 00

			// add
			virtual std::uint8_t  GetFrequencyShift() = 0;     // 01
			virtual std::uint8_t  GetFrequencyVariance() = 0;  // 02
			virtual std::uint8_t  GetPriority() = 0;           // 03
			virtual std::uint16_t GetStaticAttenuation() = 0;  // 04
			virtual std::uint8_t  GetDBVariance() = 0;         // 05
		};
		static_assert(sizeof(BSIPlaybackCharacteristics) == 0x8);

		struct Resolution
		{
		public:
			// members
			BSResource::ID                            resourceID;               // 00
			FormID                                    formID;                   // 0C
			FormID                                    alternateFormID;          // 10
			std::uint32_t                             flags;                    // 14
			BSIPlaybackCharacteristics*               playbackCharacteristics;  // 18
			BSISoundOutputModel*                      outputModel;              // 20
			BSISoundCategory*                         soundCategory;            // 28
			BSTSmallArray<BSAudioMonitor::Request, 2> monitorRequests;          // 30
		};

		virtual ~BSISoundDescriptor();  // 00

		// add
		virtual bool DoResolve(Resolution& a_resolution) = 0;  // 01
		virtual void Unk_02(void) = 0;                         // 02
	};
	static_assert(sizeof(BSISoundDescriptor) == 0x8);
}

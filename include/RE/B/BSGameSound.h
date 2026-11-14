#pragma once

#include "RE/B/BSAudioMonitor.h"
#include "RE/B/BSTArray.h"
#include "RE/I/ID.h"
#include "RE/M/MemoryManager.h"
#include "RE/N/NiPoint3.h"
#include "RE/S/SoundMessageList.h"

namespace RE
{
	class BSISoundCategory;
	class BSISoundOutputModel;

	class BSGameSound
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSGameSound;
		inline static constexpr auto VTABLE = VTABLE_BSGameSound;

		enum class Flags
		{
			HasBeenOpened = 1 << 0,
			IsSoundFinished = 1 << 4,
			IsPlaying = 1 << 5,
			IsPaused = 1 << 6,
			IsValid = 1 << 8,
			IsPlayable = 1 << 11,
			IsOpening = 1 << 12,
			IsValidBeam = 1 << 15,
			IsAsyncOpening = 1 << 18,
			IsInDecay = 1 << 19,
			PositionSet = 1 << 20,
		};

		enum class SoundType
		{
			Music = 1 << 5,
		};

		// add
		virtual void OutputModelChangedImpl();  // 00 - { return; }

		virtual ~BSGameSound();  // 01

		virtual bool          IsSoundFinished() const;                                                                                                                // 02
		virtual void          SetSoundFinished(bool a_set);                                                                                                           // 03
		virtual std::uint32_t GetCurrentPlaybackPosition() const = 0;                                                                                                 // 04
		virtual bool          PriorityTest(const BSGameSound* a_other) const;                                                                                         // 05
		virtual bool          SyncOpen() = 0;                                                                                                                         // 06
		virtual bool          StartAsyncOpen() = 0;                                                                                                                   // 07
		virtual bool          TestAsyncOpenReady() = 0;                                                                                                               // 08
		virtual bool          FinishAsyncOpen() = 0;                                                                                                                  // 09
		virtual bool          HandleExternalOpen() = 0;                                                                                                               // 0A
		virtual bool          Prepare();                                                                                                                              // 0B
		virtual void          Copy(BSGameSound* a_other, bool a_updateImpl);                                                                                          // 0C
		virtual void          UpdateEmitterPosition() = 0;                                                                                                            // 0D
		virtual bool          Update();                                                                                                                               // 0E
		virtual void          SetEmitterPositionImpl(const NiPoint3& a_position) = 0;                                                                                 // 0F
		virtual void          GetEmitterPositionImpl(NiPoint3& a_position) const = 0;                                                                                 // 10
		virtual void          Unk_11(float a_arg1, float a_arg2) = 0;                                                                                                 // 11
		virtual void          SetAttenuationCurve(std::uint16_t a_val1, std::uint16_t a_val2, std::uint16_t a_val3, std::uint16_t a_val4, std::uint16_t a_val5) = 0;  // 12
		virtual void          DoApplyFrequency();                                                                                                                     // 13
		virtual void          Seek(std::uint32_t a_milliseconds) = 0;                                                                                                 // 14
		virtual void          PlayImpl() = 0;                                                                                                                         // 15
		virtual void          PauseImpl() = 0;                                                                                                                        // 16
		virtual void          StopImpl() = 0;                                                                                                                         // 17
		virtual void          SetVolumeImpl() = 0;                                                                                                                    // 18

		TES_HEAP_REDEFINE_NEW();

		void SetOutputModel(BSISoundOutputModel* a_outputModel);
		void SetVolume(float a_volume);

		[[nodiscard]] constexpr float                   GetFrequency() const noexcept { return frequency * 0.01f; }
		[[nodiscard]] constexpr bool                    HasBeenOpened() const noexcept { return flags.all(Flags::HasBeenOpened); }
		[[nodiscard]] constexpr bool                    IsAsyncOpening() const noexcept { return flags.all(Flags::IsAsyncOpening); }
		[[nodiscard]] constexpr bool                    IsInDecay() const noexcept { return flags.all(Flags::IsInDecay); }
		[[nodiscard]] constexpr bool                    IsOpening() const noexcept { return flags.all(Flags::IsOpening); }
		[[nodiscard]] constexpr bool                    IsMusic() const noexcept { return soundType.all(SoundType::Music); }
		[[nodiscard]] constexpr bool                    IsPaused() const noexcept { return flags.all(Flags::IsPaused); }
		[[nodiscard]] constexpr bool                    IsPlayable() const noexcept { return flags.all(Flags::IsPlayable); }
		[[nodiscard]] constexpr bool                    IsPlaying() const noexcept { return flags.all(Flags::IsPlaying); }
		[[nodiscard]] constexpr bool                    IsValid() const noexcept { return flags.all(Flags::IsValid); }
		[[nodiscard]] constexpr bool                    IsValidBeam() const noexcept { return flags.all(Flags::IsValidBeam); }
		[[nodiscard]] constexpr const BSISoundCategory* QCategory() const noexcept { return category; }
		[[nodiscard]] constexpr bool                    QPositionSet() const noexcept { return flags.all(Flags::PositionSet); }

		using UnkCallbackFunc = void(void*, std::uint32_t);

		// members
		BSTSmallArray<BSAudioMonitor::Request, 2> requests;              // 08
		NiPoint3                                  beamEnd;               // 20
		std::byte                                 pad2C[4];              // 2C
		SoundMessageList                          soundMessageList;      // 30
		BSResource::ID                            resourceID;            // 40
		std::uint32_t                             unk4C;                 // 4C
		REX::EnumSet<SoundType, std::uint32_t>    soundType;             // 50
		std::uint32_t                             unk54;                 // 54
		std::uint32_t                             unk58;                 // 58
		REX::EnumSet<Flags, std::uint32_t>        flags;                 // 5C
		std::uint32_t                             durationMilliseconds;  // 60
		std::uint16_t                             staticAttenuation;     // 64
		std::uint16_t                             unk66;                 // 66
		std::uint16_t                             systemAttenuation;     // 68
		std::uint16_t                             unk6A;                 // 6A
		std::uint16_t                             unk6C;                 // 6C
		std::byte                                 pad6E[2];              // 6E
		float                                     volume;                // 70
		float                                     unk74;                 // 74
		float                                     unk78;                 // 78
		std::uint32_t                             unk7C;                 // 7C
		float                                     listenerDistance;      // 80
		std::uint32_t                             unk84;                 // 84
		std::uint64_t                             unk88;                 // 88
		UnkCallbackFunc*                          unk90;                 // 90
		std::uint64_t                             unk98;                 // 98
		std::uint64_t                             unkA0;                 // A0
		std::uint32_t                             priority;              // A8
		std::uint32_t                             unkAC;                 // AC
		BSISoundCategory*                         category;              // B0
		BSISoundOutputModel*                      outputModel;           // B8
		std::uint8_t                              frequency;             // C0
		std::uint8_t                              freqVariance;          // C1
		std::byte                                 padC2[6];              // C2
	};
	static_assert(sizeof(BSGameSound) == 0xC8);
}

#pragma once

#include "RE/B/BSGameSound.h"
#include "RE/B/BSXAudio2DataSrc.h"
#include "RE/I/IXAudio2VoiceCallback.h"
#include "RE/X/X3DAudio.h"

namespace RE
{
	class BSXAudio2Audio;
	struct IXAudio2SourceVoice;

	class BSXAudio2GameSound :
		public BSGameSound,           // 000
		public IXAudio2VoiceCallback  // 0C8
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSXAudio2GameSound;
		inline static constexpr auto VTABLE = VTABLE_BSXAudio2GameSound;

		// override (BSGameSound)
		void OutputModelChangedImpl() override;  // 00

		~BSXAudio2GameSound() override;  // 01

		std::uint32_t GetCurrentPlaybackPosition() const override;                                                                                                 // 04
		bool          SyncOpen() override;                                                                                                                         // 06
		bool          StartAsyncOpen() override;                                                                                                                   // 07
		bool          TestAsyncOpenReady() override;                                                                                                               // 08
		bool          FinishAsyncOpen() override;                                                                                                                  // 09
		bool          HandleExternalOpen() override;                                                                                                               // 0A
		bool          Prepare() override;                                                                                                                          // 0B
		void          Copy(BSGameSound* a_other, bool a_update) override;                                                                                          // 0C
		void          UpdateEmitterPosition() override;                                                                                                            // 0D
		bool          Update() override;                                                                                                                           // 0E
		void          SetEmitterPositionImpl(const NiPoint3& a_position) override;                                                                                 // 0F
		void          GetEmitterPositionImpl(NiPoint3& a_position) const override;                                                                                 // 10
		void          Unk_11(float a_arg1, float a_arg2) override;                                                                                                 // 11
		void          SetAttenuationCurve(std::uint16_t a_val1, std::uint16_t a_val2, std::uint16_t a_val3, std::uint16_t a_val4, std::uint16_t a_val5) override;  // 12
		void          DoApplyFrequency() override;                                                                                                                 // 13
		void          Seek(std::uint32_t a_milliseconds) override;                                                                                                 // 14
		void          PlayImpl() override;                                                                                                                         // 15
		void          PauseImpl() override;                                                                                                                        // 16
		void          StopImpl() override;                                                                                                                         // 17
		void          SetVolumeImpl() override;                                                                                                                    // 18

		[[nodiscard]] static BSXAudio2Audio* GetAudioImplementation();
		static void                          SetAudioImplementation(BSXAudio2Audio* a_impl);

		void SeekInSamples(std::uint32_t a_samples);

		// members
		BSXAudio2DataSrc*               src;               // 0D0
		std::uint32_t                   buffersSubmitted;  // 0D8
		std::uint16_t                   buffersQueued;     // 0DC
		std::uint16_t                   packetIndex;       // 0DE
		X3DAUDIO_DISTANCE_CURVE         volumeCurve;       // 0E0
		X3DAUDIO_DISTANCE_CURVE_POINT   curvePoints[6];    // 0EC
		std::uint32_t                   lastUpdateTime;    // 11C
		std::uint32_t                   samplesPlayed;     // 120
		std::uint32_t                   playbackPosition;  // 124
		IXAudio2SourceVoice*            sourceVoice;       // 128
		X3DAUDIO_DSP_SETTINGS           dspSettings;       // 130
		X3DAUDIO_EMITTER                emitter;           // 168
		X3DAUDIO_CONE                   cone;              // 1E8
		std::uint32_t                   dataOffset;        // 208
		std::byte                       pad20C[4];         // 20C
		BSXAudio2DataSrc::StreamPacket* streamPackets[2];  // 210
	};
	static_assert(sizeof(BSXAudio2GameSound) == 0x220);
}

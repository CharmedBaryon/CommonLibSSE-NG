#pragma once

namespace RE
{
	struct IUnknown;
	struct IXAudio2Voice;
	using BOOL = std::int32_t;

#pragma pack(push, 1)

	// Numeric boundary values
	inline constexpr auto XAUDIO2_MAX_BUFFER_BYTES = 0x80000000;
	inline constexpr auto XAUDIO2_MAX_QUEUED_BUFFERS = 64;
	inline constexpr auto XAUDIO2_MAX_BUFFERS_SYSTEM = 2;
	inline constexpr auto XAUDIO2_MAX_AUDIO_CHANNELS = 64;
	inline constexpr auto XAUDIO2_MIN_SAMPLE_RATE = 1000;
	inline constexpr auto XAUDIO2_MAX_SAMPLE_RATE = 200000;
	inline constexpr auto XAUDIO2_MAX_VOLUME_LEVEL = 16777216.0f;
	inline constexpr auto XAUDIO2_MIN_FREQ_RATIO = (1 / 1024.0f);
	inline constexpr auto XAUDIO2_MAX_FREQ_RATIO = 1024.0f;
	inline constexpr auto XAUDIO2_DEFAULT_FREQ_RATIO = 2.0f;
	inline constexpr auto XAUDIO2_MAX_FILTER_ONEOVERQ = 1.5f;
	inline constexpr auto XAUDIO2_MAX_FILTER_FREQUENCY = 1.0f;
	inline constexpr auto XAUDIO2_MAX_LOOP_COUNT = 254;
	inline constexpr auto XAUDIO2_MAX_INSTANCES = 8;

	// Numeric values with special meanings
	inline constexpr auto XAUDIO2_COMMIT_NOW = 0;
	inline constexpr auto XAUDIO2_COMMIT_ALL = 0;
	inline constexpr auto XAUDIO2_INVALID_OPSET = static_cast<std::uint32_t>(-1);
	inline constexpr auto XAUDIO2_NO_LOOP_REGION = 0;
	inline constexpr auto XAUDIO2_LOOP_INFINITE = 255;
	inline constexpr auto XAUDIO2_DEFAULT_CHANNELS = 0;
	inline constexpr auto XAUDIO2_DEFAULT_SAMPLERATE = 0;

	// Flags
	enum XAUDIO2_FLAGS
	{
		XAUDIO2_DEBUG_ENGINE = 0x0001,
		XAUDIO2_VOICE_NOPITCH = 0x0002,
		XAUDIO2_VOICE_NOSRC = 0x0004,
		XAUDIO2_VOICE_USEFILTER = 0x0008,
		XAUDIO2_VOICE_MUSIC = 0x0010,
		XAUDIO2_PLAY_TAILS = 0x0020,
		XAUDIO2_END_OF_STREAM = 0x0040,
		XAUDIO2_SEND_USEFILTER = 0x0080
	};

	// Used in IXAudio2::Initialize
	struct XAUDIO2_PROCESSORS
	{
		enum XAUDIO2_WINDOWS_PROCESSOR_SPECIFIER
		{
			Processor1 = 0x00000001,
			Processor2 = 0x00000002,
			Processor3 = 0x00000004,
			Processor4 = 0x00000008,
			Processor5 = 0x00000010,
			Processor6 = 0x00000020,
			Processor7 = 0x00000040,
			Processor8 = 0x00000080,
			Processor9 = 0x00000100,
			Processor10 = 0x00000200,
			Processor11 = 0x00000400,
			Processor12 = 0x00000800,
			Processor13 = 0x00001000,
			Processor14 = 0x00002000,
			Processor15 = 0x00004000,
			Processor16 = 0x00008000,
			Processor17 = 0x00010000,
			Processor18 = 0x00020000,
			Processor19 = 0x00040000,
			Processor20 = 0x00080000,
			Processor21 = 0x00100000,
			Processor22 = 0x00200000,
			Processor23 = 0x00400000,
			Processor24 = 0x00800000,
			Processor25 = 0x01000000,
			Processor26 = 0x02000000,
			Processor27 = 0x04000000,
			Processor28 = 0x08000000,
			Processor29 = 0x10000000,
			Processor30 = 0x20000000,
			Processor31 = 0x40000000,
			Processor32 = 0x80000000,
			ANY_PROCESSOR = 0xffffffff,
			DEFAULT_PROCESSOR = ANY_PROCESSOR
		};
	};
	using XAUDIO2_PROCESSOR = XAUDIO2_PROCESSORS::XAUDIO2_WINDOWS_PROCESSOR_SPECIFIER;
	inline constexpr auto XAUDIO2_ANY_PROCESSOR = XAUDIO2_PROCESSORS::ANY_PROCESSOR;
	inline constexpr auto XAUDIO2_DEFAULT_PROCESSOR = XAUDIO2_PROCESSORS::DEFAULT_PROCESSOR;

	// Used in XAUDIO2_DEVICE_DETAILS below to describe the types of applications
	// that the user has specified each device as a default for.  0 means that the
	// device isn't the default for any role.
	struct XAUDIO2_DEVICE_ROLES
	{
		enum XAUDIO2_DEVICE_ROLE
		{
			NotDefaultDevice = 0x0,
			DefaultConsoleDevice = 0x1,
			DefaultMultimediaDevice = 0x2,
			DefaultCommunicationsDevice = 0x4,
			DefaultGameDevice = 0x8,
			GlobalDefaultDevice = 0xf,
			InvalidDeviceRole = ~GlobalDefaultDevice
		};
	};
	using XAUDIO2_DEVICE_ROLE = XAUDIO2_DEVICE_ROLES::XAUDIO2_DEVICE_ROLE;

	// Returned by IXAudio2::GetDeviceDetails
	struct XAUDIO2_DEVICE_DETAILS
	{
		wchar_t              DeviceID[256];     // 000 - String identifier for the audio device.
		wchar_t              DisplayName[256];  // 100 - Friendly name suitable for display to a human.
		XAUDIO2_DEVICE_ROLE  Role;              // 200 - Roles that the device should be used for.
		WAVEFORMATEXTENSIBLE OutputFormat;      // 204 - The device's native PCM audio output format.
	};
	static_assert(sizeof(XAUDIO2_DEVICE_DETAILS) == 0x42C);

	// Returned by IXAudio2Voice::GetVoiceDetails
	struct XAUDIO2_VOICE_DETAILS
	{
		std::uint32_t CreationFlags;    // 0 - Flags the voice was created with.
		std::uint32_t InputChannels;    // 4 - Channels in the voice's input audio.
		std::uint32_t InputSampleRate;  // 8 - Sample rate of the voice's input audio.
	};

	// Used in XAUDIO2_VOICE_SENDS below
	struct XAUDIO2_SEND_DESCRIPTOR
	{
		std::uint32_t  Flags;         // 0 - Either 0 or XAUDIO_SEND_USEFILTER.
		IXAudio2Voice* pOutputVoice;  // 4 - This send's destination voice.
	};
	static_assert(sizeof(XAUDIO2_SEND_DESCRIPTOR) == 0xC);

	// Used in the voice creation functions and in IXAudio2Voice::SetOutputVoices
	struct XAUDIO2_VOICE_SENDS
	{
		std::uint32_t            SendCount;  // 0 - Number of sends from this voice.
		XAUDIO2_SEND_DESCRIPTOR* pSends;     // 4 - Array of SendCount send descriptors.
	};

	// Used in XAUDIO2_EFFECT_CHAIN below
	struct XAUDIO2_EFFECT_DESCRIPTOR
	{
		IUnknown*     pEffect;         // 0 - Pointer to the effect object's IUnknown interface.
		BOOL          InitialState;    // 8 - TRUE if the effect should begin in the enabled state.
		std::uint32_t OutputChannels;  // 9 - How many output channels the effect should produce.
	};

	// Used in the voice creation functions and in IXAudio2Voice::SetEffectChain
	struct XAUDIO2_EFFECT_CHAIN
	{
		std::uint32_t              EffectCount;         // 0 - Number of effects in this voice's effect chain.
		XAUDIO2_EFFECT_DESCRIPTOR* pEffectDescriptors;  // 4 - Array of effect descriptors.
	};

	// Used in XAUDIO2_FILTER_PARAMETERS below
	struct XAUDIO2_FILTER_TYPES
	{
		enum XAUDIO2_FILTER_TYPE
		{
			LowPassFilter,   // Attenuates frequencies above the cutoff frequency.
			BandPassFilter,  // Attenuates frequencies outside a given range.
			HighPassFilter,  // Attenuates frequencies below the cutoff frequency.
			NotchFilter      // Attenuates frequencies inside a given range.
		};
	};
	using XAUDIO2_FILTER_TYPE = XAUDIO2_FILTER_TYPES::XAUDIO2_FILTER_TYPE;

	// Default parameters for the built-in filter
	inline constexpr auto XAUDIO2_DEFAULT_FILTER_TYPE = XAUDIO2_FILTER_TYPE::LowPassFilter;
	inline constexpr auto XAUDIO2_DEFAULT_FILTER_FREQUENCY = XAUDIO2_MAX_FILTER_FREQUENCY;
	inline constexpr auto XAUDIO2_DEFAULT_FILTER_ONEOVERQ = 1.0f;

	// Used in IXAudio2::Set/GetFilterParameters and Set/GetOutputFilterParameters
	struct XAUDIO2_FILTER_PARAMETERS
	{
		XAUDIO2_FILTER_TYPE Type;  // 0 - Low-pass, band-pass, or high-pass.

		float Frequency;  // 4 - Radian frequency (2 * sin(pi*CutoffFrequency/SampleRate));
						  //      must be >= 0 and <= XAUDIO2_MAX_FILTER_FREQUENCY
						  //      (giving a maximum CutoffFrequency of SampleRate/6).
		float OneOverQ;   // 8 - Reciprocal of the filter's quality factor Q;
						  //      must be > 0 and <= XAUDIO2_MAX_FILTER_ONEOVERQ.
	};

	// Used in IXAudio2SourceVoice::SubmitSourceBuffer
	struct XAUDIO2_BUFFER
	{
		std::uint32_t    Flags;       // 00 - Either 0 or XAUDIO2_END_OF_STREAM.
		std::uint32_t    AudioBytes;  // 04 - Size of the audio data buffer in bytes.
		const std::byte* pAudioData;  // 08 - Pointer to the audio data buffer.

		std::uint32_t PlayBegin;   // 10 - First sample in this buffer to be played.
		std::uint32_t PlayLength;  // 14 - Length of the region to be played in samples,
								   //       or 0 to play the whole buffer.
		std::uint32_t LoopBegin;   // 18 - First sample of the region to be looped.
		std::uint32_t LoopLength;  // 1C - Length of the desired loop region in samples,
								   //       or 0 to loop the entire buffer.
		std::uint32_t LoopCount;   // 20 - Number of times to repeat the loop region,
								   //       or XAUDIO2_LOOP_INFINITE to loop forever.
		void* pContext;            // 24 - Context value to be passed back in callbacks.
	};

	// Used in IXAudio2SourceVoice::SubmitSourceBuffer when submitting XWMA data.
	// NOTE: If an XWMA sound is submitted in more than one buffer, each buffer's
	// pDecodedPacketCumulativeBytes[PacketCount-1] value must be subtracted from
	// all the entries in the next buffer's pDecodedPacketCumulativeBytes array.
	// And whether a sound is submitted in more than one buffer or not, the final
	// buffer of the sound should use the XAUDIO2_END_OF_STREAM flag, or else the
	// client must call IXAudio2SourceVoice::Discontinuity after submitting it.
	struct XAUDIO2_BUFFER_WMA
	{
		const std::uint32_t* pDecodePacketCumulativeBytes;  // 00 - Decoded packet's cumulative size array.
															//       Each element is the number of bytes accumulated
															//       when the corresponding XWMA packet is decoded in
															//       order.  The array must have PacketCount elements.

		std::uint32_t PacketCount;  // 08 - Number of XWMA packets submitted. Must be >= 1 and
									//       divide evenly into XAUDIO2_BUFFER.AudioBytes.
	};

	// Returned by IXAudio2SourceVoice::GetState
	struct XAUDIO2_VOICE_STATE
	{
		void* pCurrentBufferContext;  // 00 - The pContext value provided in the XAUDIO2_BUFFER
									  //       that is currently being processed, or NULL if
									  //       there are no buffers in the queue.
		std::uint32_t BuffersQueued;  // 08 - Number of buffers currently queued on the voice
									  //       (including the one that is being processed).
		std::uint64_t SamplesPlayed;  // 0C - Total number of samples produced by the voice since
									  //       it began processing the current audio stream.
	};

	// Returned by IXAudio2::GetPerformanceData
	struct XAUDIO2_PERFORMANCE_DATA
	{
		// CPU usage information
		std::uint64_t AudioCyclesSinceLastQuery;  // 00 - CPU cycles spent on audio processing since the
												  //       last call to StartEngine or GetPerformanceData.
		std::uint64_t TotalCyclesSinceLastQuery;  // 08 - Total CPU cycles elapsed since the last call
												  //       (only counts the CPU XAudio2 is running on).
		std::uint32_t MinimumCyclesPerQuantum;    // 10 - Fewest CPU cycles spent processing any one
												  //       audio quantum since the last call.
		std::uint32_t MaximumCyclesPerQuantum;    // 14 - Most CPU cycles spent processing any one
												  //       audio quantum since the last call.

		// Memory usage information
		std::uint32_t MemoryUsageInBytes;  // 18 - Total heap space currently in use.

		// Audio latency and glitching information
		std::uint32_t CurrentLatencyInSamples;     // 1C - Minimum delay from when a sample is read from a
												   //       source buffer to when it reaches the speakers.
		std::uint32_t GlitchesSinceEngineStarted;  // 20 - Audio dropouts since the engine was started.

		// Data about XAudio2's current workload
		std::uint32_t ActiveSourceVoiceCount;  // 24 - Source voices currently playing.
		std::uint32_t TotalSourceVoiceCount;   // 28 - Source voices currently existing.
		std::uint32_t ActiveSubmixVoiceCount;  // 2C - Submix voices currently playing/existing.

		std::uint32_t ActiveResamplerCount;  // 30 - Resample xAPOs currently active.
		std::uint32_t ActiveMatrixMixCount;  // 34 - MatrixMix xAPOs currently active.

		// Usage of the hardware XMA decoder (Xbox 360 only)
		std::uint32_t ActiveXmaSourceVoices;  // 38 - Number of source voices decoding XMA data.
		std::uint32_t ActiveXmaStreams;       // 3C - A voice can use more than one XMA stream.
	};

	// Used in IXAudio2::SetDebugConfiguration
	struct XAUDIO2_DEBUG_CONFIGURATION
	{
		std::uint32_t TraceMask;        // 00 - Bitmap of enabled debug message types.
		std::uint32_t BreakMask;        // 04 - Message types that will break into the debugger.
		BOOL          LogThreadID;      // 08 - Whether to log the thread ID with each message.
		BOOL          LogFileline;      // 0C - Whether to log the source file and line number.
		BOOL          LogFunctionName;  // 10 - Whether to log the function name.
		BOOL          LogTiming;        // 14 - Whether to log message timestamps.
	};
#pragma pack(pop)
}

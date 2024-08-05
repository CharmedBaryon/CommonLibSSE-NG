#pragma once

namespace RE
{
	class BSISoundOutputModel;
	class NiAVObject;
	class NiPoint3;

	struct BSSoundHandle
	{
	public:
		enum : std::uint32_t
		{
			kInvalidID = static_cast<std::uint32_t>(-1)
		};

		enum class AssumedState
		{
			kInitialized = 0,
			kPlaying = 1,
			kStopped = 2,
			kPaused = 3
		};

		enum class LoopType
		{
			kNone = 0,
			kWholeFile = 1,
			kEnvFast = 2,
			kEnvSlow = 3
		};

		BSSoundHandle();
		~BSSoundHandle() = default;

		bool               FadeInPlay(std::uint16_t a_fadeTimeMS);
		bool               FadeOutAndRelease(std::uint16_t a_fadeTimeMS);
		std::uint64_t      GetDuration();
		[[nodiscard]] bool IsPlaying() const;
		[[nodiscard]] bool IsValid() const;
		bool               SetFrequency(float a_frequency);
		bool               SetPosition(NiPoint3 a_pos);
		void               SetObjectToFollow(NiAVObject* a_node);
		void               SetOutputModel(const BSISoundOutputModel* a_outputModel);
		bool               SetVolume(float a_volume);
		bool               Stop();
		bool               Play();
		bool               Pause();

		// members
		std::uint32_t                                 soundID;        // 00
		bool                                          assumeSuccess;  // 04
		std::uint8_t                                  pad05;          // 05
		std::uint16_t                                 pad06;          // 06
		stl::enumeration<AssumedState, std::uint32_t> state;          // 08
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSSoundHandle) == 0xC);
}

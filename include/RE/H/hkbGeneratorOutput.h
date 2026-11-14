#pragma once

namespace RE
{
	// Ported from https://github.com/adamhynek/activeragdoll (GPL-3.0)
	struct hkbGeneratorOutput
	{
	public:
		enum class StandardTracks
		{
			kWorldFromModel = 0x00,
			kExtractedMotion = 0x01,
			kPose = 0x02,
			kFloatSlots = 0x03,
			kRigidBodyRagdollControls = 0x04,
			kRigidBodyRagdollBlendTime = 0x05,
			kPoweredRagdollControls = 0x06,
			kPoweredRagdollWorldFromModelMode = 0x07,
			kKeyframedRagdollBones = 0x08,
			kKeyframeTargets = 0x09,
			kAnimationBlendFraction = 0x0A,
			kAttributes = 0x0B,
			kFootIkControls = 0x0C,
			kCharacterControllerControls = 0x0D,
			kHandIkControls0 = 0x0E,
			kHandIkControls1 = 0x0F,
			kHandIkControls2 = 0x10,
			kHandIkControls3 = 0x11,
			kHandIkControlsNonBlendable0 = 0x12,
			kHandIkControlsNonBlendable1 = 0x13,
			kHandIkControlsNonBlendable2 = 0x14,
			kHandIkControlsNonBlendable3 = 0x15,
			kDockingControls = 0x16,
			kAiControlControlsBlendable = 0x17,
			kAiControlControlsNonBlendable = 0x18,
			kTotal = 0x19,
		};

		enum class TrackType : std::int8_t
		{
			kReal = 0,
			kQsTransform = 1,
			kBinary = 2,
		};

		enum class TrackFlag : std::int8_t
		{
			kAdditivePose = 1 << 0,
			kPalette = 1 << 1,
			kSparse = 1 << 2,
		};

		struct TrackHeader
		{
		public:
			// members
			std::int16_t capacity;          // 00
			std::int16_t numData;           // 02
			std::int16_t dataOffset;        // 04
			std::int16_t elementSizeBytes;  // 06
			float        onFraction;        // 08
			TrackFlag    flags;             // 0C
			TrackType    type;              // 0D
		};
		static_assert(sizeof(TrackHeader) == 0x10);

		struct TrackMasterHeader
		{
		public:
			// members
			std::int32_t numBytes;   // 00
			std::int32_t numTracks;  // 04
			std::uint8_t unused[8];  // 08
		};

		struct Tracks
		{
		public:
			// members
			TrackMasterHeader masterHeader;     // 00
			TrackHeader       trackHeaders[1];  // 10
		};

		struct Track
		{
		public:
			// members
			TrackHeader* header;  // 00
			float*       data;    // 08
		};

		// members
		Tracks* tracks;        // 00
		bool    deleteTracks;  // 08
	};
}

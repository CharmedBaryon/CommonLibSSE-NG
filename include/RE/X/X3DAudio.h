#pragma once

#include "REX/W32/D3D.h"

namespace RE
{
#pragma pack(push, 1)

	using X3DAUDIO_VECTOR = REX::W32::D3DVECTOR;

	// instance handle of precalculated constants
	using X3DAUDIO_HANDLE = std::byte[20];

	// Distance curve point:
	// Defines a DSP setting at a given normalized distance.
	struct X3DAUDIO_DISTANCE_CURVE_POINT
	{
		float Distance;    // 0 - normalized distance, must be within [0.0f, 1.0f]
		float DSPSetting;  // 4 - DSP setting
	};
	static_assert(sizeof(X3DAUDIO_DISTANCE_CURVE_POINT) == 0x8);

	// Distance curve:
	// A piecewise curve made up of linear segments used to
	// define DSP behaviour with respect to normalized distance.
	//
	// Note that curve point distances are normalized within [0.0f, 1.0f].
	// X3DAUDIO_EMITTER.CurveDistanceScaler must be used to scale the
	// normalized distances to user-defined world units.
	// For distances beyond CurveDistanceScaler * 1.0f,
	// pPoints[PointCount-1].DSPSetting is used as the DSP setting.
	//
	// All distance curve spans must be such that:
	//      pPoints[k-1].DSPSetting + ((pPoints[k].DSPSetting-pPoints[k-1].DSPSetting) / (pPoints[k].Distance-pPoints[k-1].Distance)) * (pPoints[k].Distance-pPoints[k-1].Distance) != NAN or infinite values
	// For all points in the distance curve where 1 <= k < PointCount.
	struct X3DAUDIO_DISTANCE_CURVE
	{
		X3DAUDIO_DISTANCE_CURVE_POINT* pPoints;     // 0 - distance curve point array, must have at least PointCount elements with no duplicates and be sorted in ascending order with respect to Distance
		std::uint32_t                  PointCount;  // 8 - number of distance curve points, must be >= 2 as all distance curves must have at least two endpoints, defining DSP settings at 0.0f and 1.0f normalized distance
	};
	static_assert(sizeof(X3DAUDIO_DISTANCE_CURVE) == 0xC);
	inline static constexpr X3DAUDIO_DISTANCE_CURVE_POINT X3DAudioDefault_LinearCurvePoints[2] = { { 0.0f, 1.0f }, { 1.0f, 0.0f } };
	inline static constexpr X3DAUDIO_DISTANCE_CURVE       X3DAudioDefault_LinearCurve = { (X3DAUDIO_DISTANCE_CURVE_POINT*)&X3DAudioDefault_LinearCurvePoints[0], 2 };

	// Cone:
	// Specifies directionality for a listener or single-channel emitter by
	// modifying DSP behaviour with respect to its front orientation.
	// This is modeled using two sound cones: an inner cone and an outer cone.
	// On/within the inner cone, DSP settings are scaled by the inner values.
	// On/beyond the outer cone, DSP settings are scaled by the outer values.
	// If on both the cones, DSP settings are scaled by the inner values only.
	// Between the two cones, the scaler is linearly interpolated between the
	// inner and outer values.  Set both cone angles to 0 or X3DAUDIO_2PI for
	// omnidirectionality using only the outer or inner values respectively.
	struct X3DAUDIO_CONE
	{
		float InnerAngle;   // 00 - inner cone angle in radians, must be within [0.0f, X3DAUDIO_2PI]
		float OuterAngle;   // 04 - outer cone angle in radians, must be within [InnerAngle, X3DAUDIO_2PI]
		float InnerVolume;  // 08 - volume level scaler on/within inner cone, used only for matrix calculations, must be within [0.0f, 2.0f] when used
		float OuterVolume;  // 0C - volume level scaler on/beyond outer cone, used only for matrix calculations, must be within [0.0f, 2.0f] when used
		float InnerLPF;     // 10 - LPF (both direct and reverb paths) coefficient subtrahend on/within inner cone, used only for LPF (both direct and reverb paths) calculations, must be within [0.0f, 1.0f] when used
		float OuterLPF;     // 14 - LPF (both direct and reverb paths) coefficient subtrahend on/beyond outer cone, used only for LPF (both direct and reverb paths) calculations, must be within [0.0f, 1.0f] when used
		float InnerReverb;  // 18 - reverb send level scaler on/within inner cone, used only for reverb calculations, must be within [0.0f, 2.0f] when used
		float OuterReverb;  // 1C - reverb send level scaler on/beyond outer cone, used only for reverb calculations, must be within [0.0f, 2.0f] when used
	};
	static_assert(sizeof(X3DAUDIO_CONE) == 0x20);

	// Listener:
	// Defines a point of 3D audio reception.
	//
	// The cone is directed by the listener's front orientation.
	struct X3DAUDIO_LISTENER
	{
		X3DAUDIO_VECTOR OrientFront;  // 00 - orientation of front direction, used only for matrix and delay calculations or listeners with cones for matrix, LPF (both direct and reverb paths), and reverb calculations, must be normalized when used
		X3DAUDIO_VECTOR OrientTop;    // 0C - orientation of top direction, used only for matrix and delay calculations, must be orthonormal with OrientFront when used
		X3DAUDIO_VECTOR Position;     // 18 - position in user-defined world units, does not affect Velocity
		X3DAUDIO_VECTOR Velocity;     // 24 - velocity vector in user-defined world units/second, used only for doppler calculations, does not affect Position
		X3DAUDIO_CONE*  pCone;        // 30 - sound cone, used only for matrix, LPF (both direct and reverb paths), and reverb calculations, NULL specifies omnidirectionality
	};
	static_assert(sizeof(X3DAUDIO_LISTENER) == 0x38);

	// Emitter:
	// Defines a 3D audio source, divided into two classifications:
	//
	// Single-point -- For use with single-channel sounds.
	//                 Positioned at the emitter base, i.e. the channel radius
	//                 and azimuth are ignored if the number of channels == 1.
	//
	//                 May be omnidirectional or directional using a cone.
	//                 The cone originates from the emitter base position,
	//                 and is directed by the emitter's front orientation.
	//
	// Multi-point  -- For use with multi-channel sounds.
	//                 Each non-LFE channel is positioned using an
	//                 azimuth along the channel radius with respect to the
	//                 front orientation vector in the plane orthogonal to the
	//                 top orientation vector.  An azimuth of X3DAUDIO_2PI
	//                 specifies a channel is an LFE.  Such channels are
	//                 positioned at the emitter base and are calculated
	//                 with respect to pLFECurve only, never pVolumeCurve.
	//
	//                 Multi-point emitters are always omnidirectional,
	//                 i.e. the cone is ignored if the number of channels > 1.
	//
	// Note that many properties are shared among all channel points,
	// locking certain behaviour with respect to the emitter base position.
	// For example, doppler shift is always calculated with respect to the
	// emitter base position and so is constant for all its channel points.
	// Distance curve calculations are also with respect to the emitter base
	// position, with the curves being calculated independently of each other.
	// For instance, volume and LFE calculations do not affect one another.
	struct X3DAUDIO_EMITTER
	{
		X3DAUDIO_CONE*           pCone;                // 00 - sound cone, used only with single-channel emitters for matrix, LPF (both direct and reverb paths), and reverb calculations, NULL specifies omnidirectionality
		X3DAUDIO_VECTOR          OrientFront;          // 08 - orientation of front direction, used only for emitter angle calculations or with multi-channel emitters for matrix calculations or single-channel emitters with cones for matrix, LPF (both direct and reverb paths), and reverb calculations, must be normalized when used
		X3DAUDIO_VECTOR          OrientTop;            // 14 - orientation of top direction, used only with multi-channel emitters for matrix calculations, must be orthonormal with OrientFront when used
		X3DAUDIO_VECTOR          Position;             // 20 - position in user-defined world units, does not affect Velocity
		X3DAUDIO_VECTOR          Velocity;             // 2C - velocity vector in user-defined world units/second, used only for doppler calculations, does not affect Position
		float                    InnerRadius;          // 38 - inner radius, must be within [0.0f, FLT_MAX]
		float                    InnerRadiusAngle;     // 3C - inner radius angle, must be within [0.0f, X3DAUDIO_PI/4.0)
		std::uint32_t            ChannelCount;         // 40 - number of sound channels, must be > 0
		float                    ChannelRadius;        // 44 - channel radius, used only with multi-channel emitters for matrix calculations, must be >= 0.0f when used
		float*                   pChannelAzimuths;     // 48 - channel azimuth array, used only with multi-channel emitters for matrix calculations, contains positions of each channel expressed in radians along the channel radius with respect to the front orientation vector in the plane orthogonal to the top orientation vector, or X3DAUDIO_2PI to specify an LFE channel, must have at least ChannelCount elements, all within [0.0f, X3DAUDIO_2PI] when used
		X3DAUDIO_DISTANCE_CURVE* pVolumeCurve;         // 50 - volume level distance curve, used only for matrix calculations, NULL specifies a default curve that conforms to the inverse square law, calculated in user-defined world units with distances <= CurveDistanceScaler clamped to no attenuation
		X3DAUDIO_DISTANCE_CURVE* pLFECurve;            // 58 - LFE level distance curve, used only for matrix calculations, NULL specifies a default curve that conforms to the inverse square law, calculated in user-defined world units with distances <= CurveDistanceScaler clamped to no attenuation
		X3DAUDIO_DISTANCE_CURVE* pLPFDirectCurve;      // 60 - LPF direct-path coefficient distance curve, used only for LPF direct-path calculations, NULL specifies the default curve: [0.0f,1.0f], [1.0f,0.75f]
		X3DAUDIO_DISTANCE_CURVE* pLPFReverbCurve;      // 68 - LPF reverb-path coefficient distance curve, used only for LPF reverb-path calculations, NULL specifies the default curve: [0.0f,0.75f], [1.0f,0.75f]
		X3DAUDIO_DISTANCE_CURVE* pReverbCurve;         // 70 - reverb send level distance curve, used only for reverb calculations, NULL specifies the default curve: [0.0f,1.0f], [1.0f,0.0f]
		float                    CurveDistanceScalar;  // 78 - curve distance scaler, used to scale normalized distance curves to user-defined world units and/or exaggerate their effect, used only for matrix, LPF (both direct and reverb paths), and reverb calculations, must be within [FLT_MIN, FLT_MAX] when used
		float                    DopplerScalar;        // 7C - doppler shift scaler, used to exaggerate doppler shift effect, used only for doppler calculations, must be within [0.0f, FLT_MAX] when used
	};
	static_assert(sizeof(X3DAUDIO_EMITTER) == 0x80);

	// DSP settings:
	// Receives results from a call to X3DAudioCalculate to be sent
	// to the low-level audio rendering API for 3D signal processing.
	//
	// The user is responsible for allocating the matrix coefficient table,
	// delay time array, and initializing the channel counts when used.
	struct X3DAUDIO_DSP_SETTINGS
	{
		float*        pMatrixCoefficients;        // 00 - [inout] matrix coefficient table, receives an array representing the volume level used to send from source channel S to destination channel D, stored as pMatrixCoefficients[SrcChannelCount * D + S], must have at least SrcChannelCount*DstChannelCount elements
		float*        pDelayTimes;                // 08 - [inout] delay time array, receives delays for each destination channel in milliseconds, must have at least DstChannelCount elements (stereo final mix only)
		std::uint32_t SrcChannelCount;            // 10 - [in] number of source channels, must equal number of channels in respective emitter
		std::uint32_t DstChannelCount;            // 14 - [in] number of destination channels, must equal number of channels of the final mix
		float         LPFDirectCoefficient;       // 18 - [out] LPF direct-path coefficient
		float         LPFReverbCoefficient;       // 1C - [out] LPF reverb-path coefficient
		float         ReverbLevel;                // 20 - [out] reverb send level
		float         DopplerFactor;              // 24 - [out] doppler shift factor, scales resampler ratio for doppler shift effect, where the effective frequency = DopplerFactor * original frequency
		float         EmitterToListenerAngle;     // 28 - [out] emitter-to-listener interior angle, expressed in radians with respect to the emitter's front orientation
		float         EmitterToListenerDistance;  // 2C - [out] distance in user-defined world units from the emitter base to listener position, always calculated
		float         EmitterVelocityComponent;   // 30 - [out] component of emitter velocity vector projected onto emitter->listener vector in user-defined world units/second, calculated only for doppler
		float         ListenerVelocityComponent;  // 34 - [out] component of listener velocity vector projected onto emitter->listener vector in user-defined world units/second, calculated only for doppler
	};
	static_assert(sizeof(X3DAUDIO_DSP_SETTINGS) == 0x38);

#pragma pack(pop)
}

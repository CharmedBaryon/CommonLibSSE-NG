#pragma once

#include "RE/H/hkReferencedObject.h"

namespace RE
{
	class hkpConstraintMotor : public hkReferencedObject
	{
	public:
		enum class MotorType
		{
			kInvalid = 0,

			kPosition,
			kVelocity,
			kSpring,
			kCallback,

			kNUM
		};

		inline static constexpr auto RTTI = RTTI_hkpConstraintMotor;
		inline static constexpr auto VTABLE = VTABLE_hkpConstraintMotor;

		// members
		stl::enumeration<MotorType, uint8_t> type;  // 10
	};
	static_assert(sizeof(hkpConstraintMotor) == 0x18);

	class hkpLimitedForceConstraintMotor : public hkpConstraintMotor
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpLimitedForceConstraintMotor;
		inline static constexpr auto VTABLE = VTABLE_hkpLimitedForceConstraintMotor;

		// members
		float minForce;  // 18
		float maxForce;  // 1C
	};
	static_assert(sizeof(hkpLimitedForceConstraintMotor) == 0x20);

	class hkpPositionConstraintMotor : public hkpLimitedForceConstraintMotor
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpPositionConstraintMotor;
		inline static constexpr auto VTABLE = VTABLE_hkpPositionConstraintMotor;

		// members
		float tau;                           // 20
		float damping;                       // 24
		float proportionalRecoveryVelocity;  // 28
		float constantRecoveryVelocity;      // 2C
	};
	static_assert(sizeof(hkpPositionConstraintMotor) == 0x30);

	class hkpVelocityConstraintMotor : public hkpLimitedForceConstraintMotor
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpVelocityConstraintMotor;
		inline static constexpr auto VTABLE = VTABLE_hkpVelocityConstraintMotor;

		// members
		float tau;                  // 20
		float targetVelocity;       // 24
		bool  useConstraintTarget;  // 28
	};
	static_assert(sizeof(hkpVelocityConstraintMotor) == 0x30);

	class hkpSpringDamperConstraintMotor : public hkpLimitedForceConstraintMotor
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpSpringDamperConstraintMotor;
		inline static constexpr auto VTABLE = VTABLE_hkpSpringDamperConstraintMotor;

		// members
		float springConstant;  // 20
		float springDamping;   // 24
	};
	static_assert(sizeof(hkpSpringDamperConstraintMotor) == 0x28);

	class hkpCallbackConstraintMotor : public hkpLimitedForceConstraintMotor
	{
	public:
		enum class CallbackType
		{
			kUnk = 0,

			kUser0,
			kUser1,
			kUser2,

			kNUM
		};

		inline static constexpr auto RTTI = RTTI_hkpCallbackConstraintMotor;
		inline static constexpr auto VTABLE = VTABLE_hkpCallbackConstraintMotor;

		using CallbackFunction = void(const hkpCallbackConstraintMotor& motor, const void* unk0, void* unk1);

		// members
		CallbackFunction*                             func;          // 20
		stl::enumeration<CallbackType, std::uint32_t> callbackType;  // 28
		std::uint64_t                                 userData0;     // 30
		std::uint64_t                                 userData1;     // 38
		std::uint64_t                                 userData2;     // 40
	};
	static_assert(sizeof(hkpCallbackConstraintMotor) == 0x48);
}
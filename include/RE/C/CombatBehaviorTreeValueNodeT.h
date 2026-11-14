#pragma once

#include "RE/A/Actor.h"
#include "RE/C/CombatBehaviorContextMagic.h"
#include "RE/C/CombatBehaviorContextRangedMovement.h"
#include "RE/C/CombatBehaviorExpression.h"
#include "RE/C/CombatBehaviorTreeUtils.h"
#include "RE/C/CombatBehaviorTreeValueNode.h"
#include "RE/C/CombatController.h"
#include "RE/C/CombatGroup.h"
#include "RE/C/CombatInventory.h"
#include "RE/C/CombatState.h"
#include "RE/T/TESCombatStyle.h"

namespace RE
{
	template <typename T, typename Expr>
	class CombatBehaviorTreeValueNodeTImpl : public CombatBehaviorTreeValueNode<T>
	{
	public:
		CombatBehaviorTreeValueNodeTImpl(auto&& expr) :
			expr(std::forward<decltype(expr)>(expr)) {}

		T GetValue() override
		{
			return static_cast<T>(expr);
		}

		// members
		Expr expr;  // 30
	};

	template <typename T, typename Expr>
	class CombatBehaviorTreeValueNodeT : public CombatBehaviorTreeValueNodeTImpl<T, Expr>
	{
	public:
		using CombatBehaviorTreeValueNodeTImpl<T, Expr>::CombatBehaviorTreeValueNodeTImpl;
	};

	// Specs for instantiated nodes

#define DECLARE_SPECIALIZATION(T, Expr, size, ARR)                                                 \
	template <>                                                                                    \
	class CombatBehaviorTreeValueNodeT<T, Expr> : public CombatBehaviorTreeValueNodeTImpl<T, Expr> \
	{                                                                                              \
	public:                                                                                        \
		CombatBehaviorTreeValueNodeT(auto&& expr) :                                                \
			CombatBehaviorTreeValueNodeTImpl<T, Expr>(std::forward<decltype(expr)>(expr))          \
		{                                                                                          \
			this->SetVftable(ARR[0]);                                                              \
		}                                                                                          \
	};

	// sizeof instatiates template, so use for tests
	//static_assert(sizeof(CombatBehaviorTreeValueNodeT<T, Expr>) == (size))

#define COMMA ,
	DECLARE_SPECIALIZATION(unsigned int, int, 0x38, RE::VTABLE_CombatBehaviorTreeValueNodeT_uint_int_);
	DECLARE_SPECIALIZATION(unsigned int, MagicSystem::CastingType, 0x38, RE::VTABLE_CombatBehaviorTreeValueNodeT_uint_MagicSystem__CastingType_);
	DECLARE_SPECIALIZATION(unsigned int, CombatInventoryItem::TYPE, 0x38, RE::VTABLE_CombatBehaviorTreeValueNodeT_uint_CombatInventoryItem__TYPE_);
	DECLARE_SPECIALIZATION(unsigned int, CombatBehaviorExpression<CombatBehaviorUnaryExpression<CombatBehaviorMemberFunc<CombatState COMMA decltype(&CombatState::QTargetLost)> COMMA OpNot>>, 0x38, RE::VTABLE_CombatBehaviorTreeValueNodeT_uint_CombatBehaviorExpression_CombatBehaviorUnaryExpression_CombatBehaviorMemberFunc_CombatState_bool__CombatState_____void___OpNot___);
	DECLARE_SPECIALIZATION(unsigned int, CombatBehaviorExpression<CombatBehaviorUnaryExpression<CombatBehaviorMemberFunc<CombatBehaviorEquipContext COMMA decltype(&CombatBehaviorEquipContext::CheckEquipmentChanged)> COMMA OpNot>>, 0x38, RE::VTABLE_CombatBehaviorTreeValueNodeT_uint_CombatBehaviorExpression_CombatBehaviorUnaryExpression_CombatBehaviorMemberFunc_CombatBehaviorEquipContext_bool__CombatBehaviorEquipContext_____void___OpNot___);
	DECLARE_SPECIALIZATION(unsigned int, CombatBehaviorExpression<CombatBehaviorUnaryExpression<CombatBehaviorMemberFunc<CombatController COMMA decltype(&CombatController::CheckCombatArea) COMMA CombatBehaviorTreeUtils::CombatBehaviorAttacker> COMMA OpNot>>, 0x40, RE::VTABLE_CombatBehaviorTreeValueNodeT_uint_CombatBehaviorExpression_CombatBehaviorUnaryExpression_CombatBehaviorMemberFunc1_CombatController_bool__CombatController_____Actor____CombatBehaviorTree__CombatBehaviorAttacker__OpNot___);
	DECLARE_SPECIALIZATION(unsigned int, CombatBehaviorExpression<CombatBehaviorMemberFunc<CombatState COMMA decltype(&CombatState::CheckShouldHide)>>, 0x38, RE::VTABLE_CombatBehaviorTreeValueNodeT_uint_CombatBehaviorExpression_CombatBehaviorMemberFunc_CombatState_bool__CombatState_____void____);
	DECLARE_SPECIALIZATION(unsigned int, CombatBehaviorExpression<CombatBehaviorMemberFunc<CombatGroup COMMA decltype(&CombatGroup::IsSearching)>>, 0x38, RE::VTABLE_CombatBehaviorTreeValueNodeT_uint_CombatBehaviorExpression_CombatBehaviorMemberFunc_CombatGroup_bool__CombatGroup_____void____);
	DECLARE_SPECIALIZATION(unsigned int, CombatBehaviorExpression<CombatBehaviorMemberFunc<CombatBehaviorEquipContext COMMA decltype(&CombatBehaviorEquipContext::GetEquipmentType)>>, 0x38, RE::VTABLE_CombatBehaviorTreeValueNodeT_uint_CombatBehaviorExpression_CombatBehaviorMemberFunc_CombatBehaviorEquipContext_CombatInventoryItem__TYPE__CombatBehaviorEquipContext_____void____);
	DECLARE_SPECIALIZATION(unsigned int, CombatBehaviorExpression<CombatBehaviorMemberFunc<CombatBehaviorContextRangedMovement COMMA decltype(&CombatBehaviorContextRangedMovement::CheckOutOfRange)>>, 0x38, RE::VTABLE_CombatBehaviorTreeValueNodeT_uint_CombatBehaviorExpression_CombatBehaviorMemberFunc_CombatBehaviorContextRangedMovement_bool__CombatBehaviorContextRangedMovement_____void____);
	DECLARE_SPECIALIZATION(unsigned int, CombatBehaviorExpression<CombatBehaviorMemberFunc<CombatBehaviorContextMagic COMMA decltype(&CombatBehaviorContextMagic::GetCastingType)>>, 0x38, RE::VTABLE_CombatBehaviorTreeValueNodeT_uint_CombatBehaviorExpression_CombatBehaviorMemberFunc_CombatBehaviorContextMagic_MagicSystem__CastingType__CombatBehaviorContextMagic_____void____);
	DECLARE_SPECIALIZATION(unsigned int, CombatBehaviorExpression<CombatBehaviorMemberFunc<CombatBehaviorContextCloseMovement COMMA decltype(&CombatBehaviorContextCloseMovement::CheckOutOfRange)>>, 0x38, RE::VTABLE_CombatBehaviorTreeValueNodeT_uint_CombatBehaviorExpression_CombatBehaviorMemberFunc_CombatBehaviorContextCloseMovement_bool__CombatBehaviorContextCloseMovement_____void____);
	DECLARE_SPECIALIZATION(unsigned int, CombatBehaviorExpression<CombatBehaviorMemberFunc<ActorState COMMA decltype(&ActorState::CanStrafe)>>, 0x38, RE::VTABLE_CombatBehaviorTreeValueNodeT_uint_CombatBehaviorExpression_CombatBehaviorMemberFunc_Actor_bool__IMovementState_____void____);
	DECLARE_SPECIALIZATION(unsigned int, CombatBehaviorExpression<CombatBehaviorMemberFunc<ActorState COMMA decltype(&ActorState::IsFlying)>>, 0x38, RE::VTABLE_CombatBehaviorTreeValueNodeT_uint_CombatBehaviorExpression_CombatBehaviorMemberFunc_Actor_bool__ActorState_____void____);
	DECLARE_SPECIALIZATION(unsigned int, CombatBehaviorExpression<CombatBehaviorMemberFunc<TESCombatStyle COMMA decltype(&TESCombatStyle::HasFlag) COMMA TESCombatStyle::FLAG>>, 0x40, RE::VTABLE_CombatBehaviorTreeValueNodeT_uint_CombatBehaviorExpression_CombatBehaviorMemberFunc1_TESCombatStyle_bool__TESCombatStyle_____uint__TESCombatStyle__FLAG___);
	DECLARE_SPECIALIZATION(unsigned int, CombatBehaviorExpression<CombatBehaviorBinaryExpression<CombatBehaviorUnaryExpression<CombatBehaviorMemberFunc<CombatState COMMA decltype(&CombatState::QTargetLost)> COMMA OpNot> COMMA CombatBehaviorExpression<CombatBehaviorBinaryExpression<CombatBehaviorFunc<float (*)(TESObjectREFR* COMMA TESObjectREFR*) COMMA CombatBehaviorTreeUtils::CombatBehaviorAttacker COMMA CombatBehaviorTreeUtils::CombatBehaviorTarget> COMMA float COMMA OpLessThan>> COMMA OpAnd>>, 0x50, RE::VTABLE_CombatBehaviorTreeValueNodeT_uint_CombatBehaviorExpression_CombatBehaviorBinaryExpression_CombatBehaviorUnaryExpression_CombatBehaviorMemberFunc_CombatState_bool__CombatState_____void___OpNot__CombatBehaviorExpression_CombatBehaviorBinaryExpression_CombatBehaviorFunc2_float_____TESObjectREFR___TESObjectREFR____CombatBehaviorTree__CombatBehaviorAttacker_CombatBehaviorTree__CombatBehaviorTarget__float_OpLessThan___OpAnd___);
	DECLARE_SPECIALIZATION(unsigned int, CombatBehaviorExpression<CombatBehaviorBinaryExpression<CombatBehaviorMemberFunc<CombatInventory COMMA decltype(&CombatInventory::QRawMaxRange)> COMMA float COMMA OpGreaterThan>>, 0x40, RE::VTABLE_CombatBehaviorTreeValueNodeT_uint_CombatBehaviorExpression_CombatBehaviorBinaryExpression_CombatBehaviorMemberFunc_CombatInventory_float__CombatInventory_____void___float_OpGreaterThan___);
	DECLARE_SPECIALIZATION(unsigned int, CombatBehaviorExpression<CombatBehaviorBinaryExpression<CombatBehaviorMemberFunc<ActorState COMMA decltype(&ActorState::GetFlyState)> COMMA FLY_STATE COMMA OpEquals>>, 0x40, RE::VTABLE_CombatBehaviorTreeValueNodeT_uint_CombatBehaviorExpression_CombatBehaviorBinaryExpression_CombatBehaviorMemberFunc_Actor_FLY_STATE__ActorState_____void___FLY_STATE_OpEquals___);
	DECLARE_SPECIALIZATION(unsigned int, CombatBehaviorExpression<CombatBehaviorBinaryExpression<CombatBehaviorMemberFunc<Actor COMMA decltype(&Actor::IsOnWaterTriangle)> COMMA CombatBehaviorExpression<CombatBehaviorUnaryExpression<CombatBehaviorMemberFunc<Actor COMMA decltype(&Actor::FightsInWater)> COMMA OpNot>> COMMA OpAnd>>, 0x50, RE::VTABLE_CombatBehaviorTreeValueNodeT_uint_CombatBehaviorExpression_CombatBehaviorBinaryExpression_CombatBehaviorMemberFunc_Actor_bool__Actor_____void___CombatBehaviorExpression_CombatBehaviorUnaryExpression_CombatBehaviorMemberFunc_Actor_bool__Actor_____void___OpNot___OpAnd___);
	DECLARE_SPECIALIZATION(unsigned int, CombatBehaviorExpression<CombatBehaviorBinaryExpression<CombatBehaviorMemberFunc<Actor COMMA decltype(&Actor::CanFly)> COMMA CombatBehaviorExpression<CombatBehaviorBinaryExpression<CombatBehaviorMemberFunc<ActorState COMMA decltype(&ActorState::GetFlyState)> COMMA FLY_STATE COMMA OpNotEquals>> COMMA OpOr>>, 0x50, RE::VTABLE_CombatBehaviorTreeValueNodeT_uint_CombatBehaviorExpression_CombatBehaviorBinaryExpression_CombatBehaviorMemberFunc_Actor_bool__Actor_____void___CombatBehaviorExpression_CombatBehaviorBinaryExpression_CombatBehaviorMemberFunc_Actor_FLY_STATE__ActorState_____void___FLY_STATE_OpNotEquals___OpOr___);
	DECLARE_SPECIALIZATION(unsigned int, CombatBehaviorExpression<CombatBehaviorBinaryExpression<CombatBehaviorMemberFunc<CombatState COMMA decltype(&CombatState::CheckShouldFlee)> COMMA CombatBehaviorExpression<CombatBehaviorMemberFunc<Actor COMMA decltype(&Actor::IsInBleedout)>> COMMA OpOr>>, 0x48, RE::VTABLE_CombatBehaviorTreeValueNodeT_uint_CombatBehaviorExpression_CombatBehaviorBinaryExpression_CombatBehaviorMemberFunc_CombatState_bool__CombatState_____void___CombatBehaviorExpression_CombatBehaviorMemberFunc_Actor_bool__Actor_____void____OpOr___);
	DECLARE_SPECIALIZATION(unsigned int, CombatBehaviorExpression<CombatBehaviorMemberFunc<Actor COMMA decltype(&Actor::IsEssentialDown)>>, 0x40, RE::VTABLE_CombatBehaviorTreeValueNodeT_uint_CombatBehaviorExpression_CombatBehaviorMemberFunc_Actor_bool__Actor_____void____);
	DECLARE_SPECIALIZATION(float, CombatBehaviorExpression<CombatBehaviorFunc<float (*)(Actor*) COMMA CombatBehaviorTreeUtils::CombatBehaviorAttacker>>, 0x40, RE::VTABLE_CombatBehaviorTreeValueNodeT_float_CombatBehaviorExpression_CombatBehaviorFunc1_float_____Actor____CombatBehaviorTree__CombatBehaviorAttacker___);
#undef COMMA

#undef DECLARE_SPECIALIZATION
}

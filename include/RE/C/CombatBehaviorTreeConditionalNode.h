#pragma once

#include "RE/A/Actor.h"
#include "RE/C/CombatBehaviorContextAcquireWeapon.h"
#include "RE/C/CombatBehaviorContextSearch.h"
#include "RE/C/CombatBehaviorContextShout.h"
#include "RE/C/CombatBehaviorExpression.h"
#include "RE/C/CombatBehaviorTreeNode.h"
#include "RE/C/CombatBehaviorTreeUtils.h"

namespace RE
{
	template <typename Expr>
	class CombatBehaviorTreeConditionalNodeImpl : public CombatBehaviorTreeNode
	{
	public:
		~CombatBehaviorTreeConditionalNodeImpl() = default;

		CombatBehaviorTreeConditionalNodeImpl(auto&& expr, bool isSelector) :
			expr(std::forward<decltype(expr)>(expr)), isSelector(isSelector)
		{}

		void Enter(CombatBehaviorThread* thread) override
		{
			if (this->expr) {
				thread->Descend();
			} else {
				if (this->isSelector)
					thread->failState = CombatBehaviorThread::FailState::kFailed;
				thread->Ascend();
			}
		}

		bool Validate(CombatBehaviorTreeNode* node) const override
		{
			return CombatBehaviorBranch::Validate(node);
		}

		const BSFixedString& GetType() const override
		{
			static BSFixedString ans("CombatBehaviorTreeConditionalNode");
			return ans;
		}

		// members
		Expr expr;
		bool isSelector;
	};

	template <typename Expr>
	class CombatBehaviorTreeConditionalNode : public CombatBehaviorTreeConditionalNodeImpl<Expr>
	{
	public:
		static constexpr inline bool HAS_CREATE = false;
		static constexpr inline bool HAS_VFTABLE = false;

		using CombatBehaviorTreeConditionalNodeImpl<Expr>::CombatBehaviorTreeConditionalNodeImpl;
	};

	// Specs for nodes with Create

#define DECLARE_SPECIALIZATION(Expr, size, SE_ID, AE_ID)                                               \
	template <>                                                                                        \
	class CombatBehaviorTreeConditionalNode<Expr> : public CombatBehaviorTreeConditionalNodeImpl<Expr> \
	{                                                                                                  \
	public:                                                                                            \
		static constexpr inline bool HAS_CREATE = true;                                                \
		static constexpr inline bool HAS_VFTABLE = true;                                               \
                                                                                                       \
		CombatBehaviorTreeConditionalNode() = delete;                                                  \
                                                                                                       \
		static CombatBehaviorTreeConditionalNode<Expr>* Create(const Expr& expr, bool isSelector)      \
		{                                                                                              \
			REL::Relocation<decltype(Create)> func{ RELOCATION_ID((SE_ID), (AE_ID)) };                 \
			return func(expr, isSelector);                                                             \
		}                                                                                              \
	};

	//static_assert(sizeof(CombatBehaviorTreeConditionalNode<Expr>) == (size))

#define COMMA ,
	DECLARE_SPECIALIZATION(CombatBehaviorExpression<CombatBehaviorUnaryExpression<CombatBehaviorFunc<bool (*)(Actor* COMMA Actor*) COMMA CombatBehaviorTreeUtils::CombatBehaviorAttacker COMMA CombatBehaviorTreeUtils::CombatBehaviorTarget> COMMA OpNot>>, 0x40, 47786, 0);
	DECLARE_SPECIALIZATION(CombatBehaviorExpression<CombatBehaviorMemberFunc<CombatBehaviorEquipContext COMMA decltype(&CombatBehaviorEquipContext::CanEquipItem)>>, 0x38, 46484, 0);
	DECLARE_SPECIALIZATION(CombatBehaviorExpression<CombatBehaviorMemberFunc<CombatBehaviorContextFlee COMMA decltype(&CombatBehaviorContextFlee::CheckShouldFlee)>>, 0x38, 47448, 0);
	DECLARE_SPECIALIZATION(CombatBehaviorExpression<CombatBehaviorMemberFunc<CombatBehaviorContextFlankingMovement COMMA decltype(&CombatBehaviorContextFlankingMovement::CheckShouldStalk)>>, 0x38, 47163, 0);
	DECLARE_SPECIALIZATION(CombatBehaviorExpression<CombatBehaviorMemberFunc<CombatBehaviorContextDodgeThreat COMMA decltype(&CombatBehaviorContextDodgeThreat::CheckShouldDodge)>>, 0x38, 46598, 0);
	DECLARE_SPECIALIZATION(CombatBehaviorExpression<CombatBehaviorMemberFunc<CombatBehaviorContextCloseMovement COMMA decltype(&CombatBehaviorContextCloseMovement::CheckShouldFallbackToRanged)>>, 0x38, 46752, 0);
	DECLARE_SPECIALIZATION(CombatBehaviorExpression<CombatBehaviorMemberFunc<CombatBehaviorContextAcquireWeapon COMMA decltype(&CombatBehaviorContextAcquireWeapon::HasAmmoTarget)>>, 0x38, 46372, 0);
	DECLARE_SPECIALIZATION(CombatBehaviorExpression<CombatBehaviorFunc<bool (*)(Actor*) COMMA CombatBehaviorTreeUtils::CombatBehaviorAttacker>>, 0x40, 47785, 0);
	DECLARE_SPECIALIZATION(CombatBehaviorExpression<CombatBehaviorBinaryExpression<CombatBehaviorMemberFunc<CombatBehaviorContextSearch COMMA decltype(&CombatBehaviorContextSearch::QCurrentSearchPriority)> COMMA unsigned int COMMA OpGreaterThan>>, 0x40, 48571, 0);
	DECLARE_SPECIALIZATION(CombatBehaviorExpression<CombatBehaviorBinaryExpression<CombatBehaviorMemberFunc<ActorState COMMA decltype(&ActorState::GetFlyState)> COMMA FLY_STATE COMMA OpEquals>>, 0x40, 47784, 0);
#undef COMMA

	// Specs for instantiated nodes

#define DECLARE_SPECIALIZATION(Expr, size, ARR)                                                         \
	template <>                                                                                         \
	class CombatBehaviorTreeConditionalNode<Expr> : public CombatBehaviorTreeConditionalNodeImpl<Expr>  \
	{                                                                                                   \
	public:                                                                                             \
		static constexpr inline bool HAS_CREATE = false;                                                \
		static constexpr inline bool HAS_VFTABLE = true;                                                \
                                                                                                        \
		CombatBehaviorTreeConditionalNode(auto&& expr, bool isSelector) :                               \
			CombatBehaviorTreeConditionalNodeImpl<Expr>(std::forward<decltype(expr)>(expr), isSelector) \
		{                                                                                               \
			this->SetVftable(ARR[0]);                                                                   \
		}                                                                                               \
	};

	//static_assert(sizeof(CombatBehaviorTreeConditionalNode<Expr>) == (size))

#define COMMA ,
	DECLARE_SPECIALIZATION(CombatBehaviorExpression<CombatBehaviorFunc<bool (*)(float) COMMA CombatBehaviorExpression<CombatBehaviorMemberFunc<CombatBehaviorContextShout COMMA decltype(&CombatBehaviorContextShout::CalcCastMagicChance)>>>>, 0x40, RE::VTABLE_CombatBehaviorTreeConditionalNode_CombatBehaviorExpression_CombatBehaviorFunc1_bool_____float__CombatBehaviorExpression_CombatBehaviorMemberFunc_CombatBehaviorContextShout_float__CombatBehaviorContextShout_____void______);
	DECLARE_SPECIALIZATION(CombatBehaviorExpression<CombatBehaviorFunc<bool (*)(float) COMMA CombatBehaviorExpression<CombatBehaviorMemberFunc<CombatBehaviorContextMagic COMMA decltype(&CombatBehaviorContextMagic::CalcCastMagicChance)>>>>, 0x40, RE::VTABLE_CombatBehaviorTreeConditionalNode_CombatBehaviorExpression_CombatBehaviorFunc1_bool_____float__CombatBehaviorExpression_CombatBehaviorMemberFunc_CombatBehaviorContextMagic_float__CombatBehaviorContextMagic_____void______);
	DECLARE_SPECIALIZATION(CombatBehaviorExpression<CombatBehaviorFunc<bool (*)(float) COMMA CombatBehaviorExpression<CombatBehaviorFunc<float (*)()>>>>, 0x40, RE::VTABLE_CombatBehaviorTreeConditionalNode_CombatBehaviorExpression_CombatBehaviorFunc1_bool_____float__CombatBehaviorExpression_CombatBehaviorFunc_float_____void______);
	DECLARE_SPECIALIZATION(CombatBehaviorExpression<CombatBehaviorFunc<bool (*)(float) COMMA CombatBehaviorExpression<CombatBehaviorFunc<float (*)(Actor* COMMA Actor*) COMMA CombatBehaviorTreeUtils::CombatBehaviorAttacker COMMA CombatBehaviorTreeUtils::CombatBehaviorTarget>>>>, 0x48, RE::VTABLE_CombatBehaviorTreeConditionalNode_CombatBehaviorExpression_CombatBehaviorFunc1_bool_____float__CombatBehaviorExpression_CombatBehaviorFunc2_float_____Actor___Actor____CombatBehaviorTree__CombatBehaviorAttacker_CombatBehaviorTree__CombatBehaviorTarget_____);
	DECLARE_SPECIALIZATION(CombatBehaviorExpression<CombatBehaviorFunc<bool (*)(float) COMMA CombatBehaviorExpression<CombatBehaviorFunc<float (*)(Actor*) COMMA CombatBehaviorTreeUtils::CombatBehaviorAttacker>>>>, 0x48, RE::VTABLE_CombatBehaviorTreeConditionalNode_CombatBehaviorExpression_CombatBehaviorFunc1_bool_____float__CombatBehaviorExpression_CombatBehaviorFunc1_float_____Actor____CombatBehaviorTree__CombatBehaviorAttacker_____);
#undef COMMA

#undef DECLARE_SPECIALIZATION
}

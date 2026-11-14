#pragma once

#include "RE/A/AITimer.h"
#include "RE/C/CombatBehaviorAcquireResource.h"
#include "RE/C/CombatBehaviorBlock.h"
#include "RE/C/CombatBehaviorBlockAttack.h"
#include "RE/C/CombatBehaviorChildSelector.h"
#include "RE/C/CombatBehaviorContextAcquireWeapon.h"
#include "RE/C/CombatBehaviorExpression.h"
#include "RE/C/CombatBehaviorFallbackSelector.h"
#include "RE/C/CombatBehaviorParallel.h"
#include "RE/C/CombatBehaviorRepeat.h"
#include "RE/C/CombatBehaviorSequence.h"
#include "RE/C/CombatBehaviorTreeNode.h"
#include "RE/C/CombatBlackboardKey.h"

namespace RE
{
	template <typename Object>
	class CombatBehaviorTreeNodeObjectBaseImpl : public CombatBehaviorTreeNode
	{
	public:
		CombatBehaviorTreeNodeObjectBaseImpl() = default;
		~CombatBehaviorTreeNodeObjectBaseImpl() = default;

		void Update(CombatBehaviorThread* thread) override
		{
			thread->template GetCurrentStackObject<Object>().Update();
		}

		void Exit(CombatBehaviorThread* thread) override
		{
			thread->template GetCurrentStackObject<Object>().Exit();
			thread->stack.template Deallocate<Object>();
		}

		void SaveGame(CombatBehaviorThread*, BGSSaveFormBuffer*) override
		{
			// TODO
		}

		void LoadGame(CombatBehaviorThread*, BGSLoadFormBuffer*) override
		{
			// TODO
		}

		void Abort(CombatBehaviorThread* thread) override
		{
			thread->template GetCurrentStackObject<Object>().Abort();
		}

		bool Validate(CombatBehaviorTreeNode* node) const override
		{
			return Object::Validate(node);
		}

		const BSFixedString& GetType() const override
		{
			static BSFixedString ans("CombatBehaviorTreeNodeObject");
			return ans;
		}
	};

	template <typename Object, typename... Fields>
	class CombatBehaviorTreeNodeObjectImpl : public CombatBehaviorTreeNodeObjectBaseImpl<Object>
	{
	public:
		CombatBehaviorTreeNodeObjectImpl(auto&&... params) :
			fields(std::make_tuple(std::forward<decltype(params)>(params)...))
		{}
		~CombatBehaviorTreeNodeObjectImpl() = default;

		void Enter(CombatBehaviorThread* a_thread) override
		{
			//a_thread->stack.Allocate<Object>();
			std::apply(
				[a_thread](const auto&... args) { a_thread->stack.template Allocate<Object>(args...); }, fields);
			a_thread->template GetCurrentStackObject<Object>().Enter();
		}

		// members
		std::tuple<Fields...> fields;
	};

	template <typename Object>
	class CombatBehaviorTreeNodeObjectImpl<Object> : public CombatBehaviorTreeNodeObjectBaseImpl<Object>
	{
	public:
		CombatBehaviorTreeNodeObjectImpl() = default;
		~CombatBehaviorTreeNodeObjectImpl() = default;

		void Enter(CombatBehaviorThread* a_thread) override
		{
			a_thread->stack.template Allocate<Object>();
			a_thread->template GetCurrentStackObject<Object>().Enter();
		}
	};

	template <typename Object, typename... Fields>
	class CombatBehaviorTreeNodeObject : public CombatBehaviorTreeNodeObjectImpl<Object, Fields...>
	{
	public:
		static constexpr inline bool HAS_CREATE = false;
		static constexpr inline bool HAS_VFTABLE = false;

		using CombatBehaviorTreeNodeObjectImpl<Object, Fields...>::CombatBehaviorTreeNodeObjectImpl;
	};

	// Specs for nodes with Create

#define DECLARE_SPECIALIZATION(Object, SE_ID, AE_ID)                                             \
	template <>                                                                                  \
	class CombatBehaviorTreeNodeObject<Object> : public CombatBehaviorTreeNodeObjectImpl<Object> \
	{                                                                                            \
	public:                                                                                      \
		static constexpr inline bool HAS_CREATE = true;                                          \
		static constexpr inline bool HAS_VFTABLE = true;                                         \
                                                                                                 \
		CombatBehaviorTreeNodeObject() = delete;                                                 \
                                                                                                 \
		static CombatBehaviorTreeNodeObject<Object>* Create()                                    \
		{                                                                                        \
			REL::Relocation<decltype(&Create)> func{ RELOCATION_ID((SE_ID), (AE_ID)) };          \
			return func();                                                                       \
		}                                                                                        \
	};

	//static_assert(sizeof(CombatBehaviorTreeNodeObject<Object>) == 0x28)

	DECLARE_SPECIALIZATION(CombatBehaviorBlock, 46647, 0);
	DECLARE_SPECIALIZATION(CombatBehaviorBlockAttack, 46648, 0);
	DECLARE_SPECIALIZATION(CombatBehaviorChildSelector<ConditionalChildSelector>, 46756, 0);
	DECLARE_SPECIALIZATION(CombatBehaviorChildSelector<RandomValueChildSelector>, 46757, 0);
	DECLARE_SPECIALIZATION(CombatBehaviorChildSelector<ValueChildSelector>, 46477, 0);
	DECLARE_SPECIALIZATION(CombatBehaviorFallbackSelector<NextChildSelector>, 32407, 0);
	DECLARE_SPECIALIZATION(CombatBehaviorFallbackSelector<WeightedRandomChildSelector>, 47787, 0);
	DECLARE_SPECIALIZATION(CombatBehaviorParallel, 46279, 0);
	DECLARE_SPECIALIZATION(CombatBehaviorRepeat, 32409, 0);
	DECLARE_SPECIALIZATION(CombatBehaviorSequence, 46375, 0);

#undef DECLARE_SPECIALIZATION

	// Specs for instantiated nodes

#define DECLARE_SPECIALIZATION(List, size, ARR)                                               \
	template <>                                                                               \
	class CombatBehaviorTreeNodeObject<List> : public CombatBehaviorTreeNodeObjectImpl<List>  \
	{                                                                                         \
	public:                                                                                   \
		static constexpr inline bool HAS_CREATE = false;                                      \
		static constexpr inline bool HAS_VFTABLE = true;                                      \
                                                                                              \
		CombatBehaviorTreeNodeObject(auto&&... params) :                                      \
			CombatBehaviorTreeNodeObjectImpl<List>(std::forward<decltype(params)>(params)...) \
		{                                                                                     \
			this->SetVftable(ARR[0]);                                                         \
		}                                                                                     \
	};

	//static_assert(sizeof(CombatBehaviorTreeNodeObject<List>) == (size))

#define COMMA ,
	// TODO: rest

	DECLARE_SPECIALIZATION(CombatBehaviorRepeat COMMA float, 0x30, RE::VTABLE_CombatBehaviorTreeNodeObject1_CombatBehaviorRepeat_float_);
	DECLARE_SPECIALIZATION(CombatBehaviorRepeat COMMA float COMMA CombatBehaviorRepeat::Flags, 0x30, RE::VTABLE_CombatBehaviorTreeNodeObject2_CombatBehaviorRepeat_float_CombatBehaviorRepeat__FLAGS_);
#undef COMMA

#undef DECLARE_SPECIALIZATION
}

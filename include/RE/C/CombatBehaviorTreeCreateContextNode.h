#pragma once

#include "RE/C/CombatBehaviorTreeNode.h"

namespace RE
{
	class CombatBehaviorContextAcquireWeapon;
	class CombatBehaviorContextCloseMovement;
	class CombatBehaviorContextCover;
	class CombatBehaviorContextDodgeThreat;
	class CombatBehaviorContextFindAttackLocation;
	class CombatBehaviorContextFlankingMovement;
	class CombatBehaviorContextFlee;
	class CombatBehaviorContextHide;
	class CombatBehaviorContextRangedMovement;
	class CombatBehaviorContextSearch;

	class CombatBehaviorContextMagic;
	class CombatBehaviorContextRanged;
	class CombatBehaviorContextShout;
	class CombatBehaviorContextUsePotion;
	class CombatBehaviorEquipContext;

	template <typename Context>
	class CombatBehaviorTreeCreateContextNodeBaseImpl : public CombatBehaviorTreeNode
	{
	public:
		CombatBehaviorTreeCreateContextNodeBaseImpl() = default;
		~CombatBehaviorTreeCreateContextNodeBaseImpl() = default;

		void Exit(CombatBehaviorThread* thread) override
		{
			auto old_context_sptr = thread->template GetCurrentStackObject<CombatBehaviorStack::ObjectPtr>();
			thread->stack.template Deallocate<CombatBehaviorStack::ObjectPtr>();
			thread->template GetCurrentStackObject<Context>().Exit();
			thread->stack.template Deallocate<Context>();
			thread->currentContextPtr = old_context_sptr;
		}

		void SaveGame(CombatBehaviorThread*, BGSSaveFormBuffer*) override
		{
			// TODO
		}

		void LoadGame(CombatBehaviorThread*, BGSLoadFormBuffer*) override
		{
			// TODO
		}

		bool Validate(CombatBehaviorTreeNode* node) const override
		{
			return Context::Validate(node);
		}

		const BSFixedString& GetType() const override
		{
			static BSFixedString ans("CombatBehaviorTreeNodeObject");
			return ans;
		}

		void EnterContext(CombatBehaviorThread* thread, CombatBehaviorStack::ObjectPtr new_context_sptr)
		{
			thread->stack.StoreData(thread->currentContextPtr);
			thread->currentContextPtr = new_context_sptr;
			auto active_node = thread->currentNode;
			thread->template GetCurrentObject<Context>()->Enter();
			if (active_node == thread->currentNode)
				thread->Descend();
		}
	};

	template <typename Context, typename... Fields>
	class CombatBehaviorTreeCreateContextNodeImpl : public CombatBehaviorTreeCreateContextNodeBaseImpl<Context>
	{
	public:
		template <typename... Params>
		CombatBehaviorTreeCreateContextNodeImpl(Params&&... params) :
			fields(std::make_tuple(std::forward<Params>(params)...))
		{}
		~CombatBehaviorTreeCreateContextNodeImpl() = default;

		void Enter(CombatBehaviorThread* a_thread) override
		{
			//EnterContext(a_thread, a_thread->stack.Allocate<Context>());
			this->EnterContext(a_thread, std::apply(&CombatBehaviorStack::Allocate<Context, const Fields&...>, std::tuple_cat(std::make_tuple(a_thread->stack), fields)));
		}

		// members
		std::tuple<Fields...> fields;
	};

	template <typename Context>
	class CombatBehaviorTreeCreateContextNodeImpl<Context> : public CombatBehaviorTreeCreateContextNodeBaseImpl<Context>
	{
	public:
		CombatBehaviorTreeCreateContextNodeImpl() = default;
		~CombatBehaviorTreeCreateContextNodeImpl() = default;

		void Enter(CombatBehaviorThread* a_thread) override
		{
			this->EnterContext(a_thread, a_thread->stack.Allocate<Context>());
		}
	};

	template <typename Context, typename... Fields>
	class CombatBehaviorTreeCreateContextNode : public CombatBehaviorTreeCreateContextNodeImpl<Context, Fields...>
	{
	public:
		static constexpr inline bool HAS_CREATE = false;
		static constexpr inline bool HAS_VFTABLE = false;

		using CombatBehaviorTreeCreateContextNodeImpl<Context, Fields...>::CombatBehaviorTreeCreateContextNodeImpl;
	};

	// Specs for nodes with Create

#define DECLARE_SPECIALIZATION(List, SE_ID, AE_ID)                                                         \
	template <>                                                                                            \
	class CombatBehaviorTreeCreateContextNode<List> : public CombatBehaviorTreeCreateContextNodeImpl<List> \
	{                                                                                                      \
	public:                                                                                                \
		static constexpr inline bool HAS_CREATE = true;                                                    \
		static constexpr inline bool HAS_VFTABLE = true;                                                   \
                                                                                                           \
		CombatBehaviorTreeCreateContextNode() = delete;                                                    \
                                                                                                           \
		static CombatBehaviorTreeCreateContextNode<List>* Create()                                         \
		{                                                                                                  \
			REL::Relocation<decltype(&Create)> func{ RELOCATION_ID((SE_ID), (AE_ID)) };                    \
			return func();                                                                                 \
		}                                                                                                  \
	};                                                                                                     \
	static_assert(sizeof(CombatBehaviorTreeCreateContextNode<List>) == 0x28)

	// TODO: rest

	DECLARE_SPECIALIZATION(CombatBehaviorContextAcquireWeapon, 46373, 0);
	//DECLARE_SPECIALIZATION(CombatBehaviorContextCloseMovement, 46753, 0);
	//DECLARE_SPECIALIZATION(CombatBehaviorContextCover, 48865, 0);
	//DECLARE_SPECIALIZATION(CombatBehaviorContextDodgeThreat, 46599, 0);
	//DECLARE_SPECIALIZATION(CombatBehaviorContextFindAttackLocation, 46985, 0);
	//DECLARE_SPECIALIZATION(CombatBehaviorContextFlankingMovement, 47164, 0);
	//DECLARE_SPECIALIZATION(CombatBehaviorContextFlee, 47449, 0);
	//DECLARE_SPECIALIZATION(CombatBehaviorContextHide, 47450, 0);
	//DECLARE_SPECIALIZATION(CombatBehaviorContextRangedMovement, 48484, 0);
	//DECLARE_SPECIALIZATION(CombatBehaviorContextSearch, 48572, 0);

#undef DECLARE_SPECIALIZATION

	// Specs for instantiated nodes

#define DECLARE_SPECIALIZATION(List, size, SE_ID, AE_ID)                                                   \
	template <>                                                                                            \
	class CombatBehaviorTreeCreateContextNode<List> : public CombatBehaviorTreeCreateContextNodeImpl<List> \
	{                                                                                                      \
	public:                                                                                                \
		static constexpr inline bool HAS_CREATE = false;                                                   \
		static constexpr inline bool HAS_VFTABLE = true;                                                   \
                                                                                                           \
		CombatBehaviorTreeCreateContextNode(auto&&... params) :                                            \
			CombatBehaviorTreeCreateContextNodeImpl<List>(std::forward<decltype(params)>(params)...)       \
		{                                                                                                  \
			this->SetVftable(RELOCATION_ID((SE_ID), (AE_ID)));                                             \
		}                                                                                                  \
	};                                                                                                     \
	static_assert(sizeof(CombatBehaviorTreeCreateContextNode<List>) == (size))

	// TODO: rest

#undef DECLARE_SPECIALIZATION
}

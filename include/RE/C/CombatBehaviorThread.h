#pragma once

#include "RE/B/BSTArray.h"
#include "RE/B/BSTTuple.h"
#include "RE/C/CombatBehaviorStack.h"

namespace RE
{
	class CombatBehaviorController;
	class CombatBehaviorTreeNode;

	class CombatBehaviorThread
	{
	public:
		enum class FailState : std::uint32_t
		{
			kOk = 0,
			kFailed = 1,
			kAborted = 2
		};

		enum class State : std::uint32_t
		{
			kAscending = 0,
			kUpdating = 1,
			kDescending = 2,
			kRestarting = 3
		};

		enum class Flags : std::uint32_t
		{
			kPaused = 1 << 0,
			kSuspended = 1 << 1,
			kUnk2 = 1 << 2,
			kIsWorking_mb = 1 << 3
		};

		CombatBehaviorThread(CombatBehaviorController* a_controller, CombatBehaviorThread* a_parent);
		~CombatBehaviorThread();

		template <typename T>
		T* GetCurrentObject()
		{
			return currentContextPtr.GetObject<T>();
		}

		template <typename T>
		const T* GetCurrentObject() const
		{
			return currentContextPtr.GetObject<T>();
		}

		template <typename T>
		T& GetCurrentStackObject()
		{
			return stack.Access<T>(stackPos);
		}

		template <typename T>
		T* GetCurrentContext()
		{
			return currentContextPtr.stack ? &currentContextPtr.stack->Access<T>(currentContextPtr.frame) : nullptr;
		}

		void          Abort();
		void          AddChildThread(CombatBehaviorThread* a_thread);
		void          Ascend();
		void          Ascend(CombatBehaviorTreeNode* a_node);
		bool          CheckRelated(CombatBehaviorThread* a_other) const;
		bool          CheckParent(CombatBehaviorThread* a_parent) const;
		void          Descend(std::uint32_t a_index = 0);
		void          Descend(CombatBehaviorTreeNode* a_node);
		bool          GetAscendingUpdate() const;
		std::uint32_t GetChildIndex() const;
		bool          GetInitialUpdate() const;
		void          Pause();
		void          Resume();
		void          SetAborted();
		void          SetFailed(bool a_failed);
		void          Suspend();
		void          Update();
		void          Unpause();
		void          Unsuspend();

		// members
		CombatBehaviorStack                                                       stack;              // 000
		BSTSmallArray<BSTTuple<const CombatBehaviorTreeNode*, std::uint32_t>, 16> stackFrame;         // 010
		std::uint32_t                                                             stackPos;           // 120
		std::uint32_t                                                             pad124;             // 124
		CombatBehaviorStack::ObjectPtr                                            currentContextPtr;  // 128
		const CombatBehaviorTreeNode*                                             currentNode;        // 138
		const CombatBehaviorTreeNode*                                             previousNode;       // 140
		REX::EnumSet<FailState, std::uint32_t>                                    failState;          // 148
		REX::EnumSet<State, std::uint32_t>                                        state;              // 14C
		REX::EnumSet<Flags, std::uint32_t>                                        flags;              // 150
		std::uint32_t                                                             threadID;           // 154
		CombatBehaviorController*                                                 controller;         // 158
		CombatBehaviorThread*                                                     parent;             // 160
		BSTSmallArray<CombatBehaviorThread*, 4>                                   children;           // 168
	};
	static_assert(sizeof(CombatBehaviorThread) == 0x198);
}

#pragma once

namespace RE
{
	template <typename Expr>
	class CombatBehaviorTreeNodeEvaluateFunction : public CombatBehaviorTreeNode
	{
	public:
		~CombatBehaviorTreeNodeEvaluateFunction() = default;

		void Update(CombatBehaviorThread* thread) override
		{
			auto old_active = thread->currentNode;

			if (!this->expr) {
				thread->failState = CombatBehaviorThread::FailState::kFailed;
			}

			if (thread->currentNode == old_active)
				thread->Ascend();
		}

		const BSFixedString& GetType() const override
		{
			static BSFixedString ans("CombatBehaviorTreeNodeEvaluateFunction");
			return ans;
		}

		// members
		Expr expr;
	};
}

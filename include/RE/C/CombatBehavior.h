#pragma once

namespace RE
{
	class BGSLoadFormBuffer;
	class BGSSaveFormBuffer;
	class CombatBehaviorThread;
	class CombatBehaviorTreeNode;

#pragma warning(push)
#pragma warning(disable: 4324)  // structure was padded due to alignment specifier

	class alignas(4) CombatBehavior
	{
	public:
		void                  Abort();  // Ascend
		bool                  CheckTargetChanged();
		CombatBehaviorThread* CreateChildThread(uint32_t child_ind, bool isControlChild);
		void                  Enter() {}
		void                  Exit() {}
		void                  LoadGame(BGSLoadFormBuffer*) {}
		void                  SaveGame(BGSSaveFormBuffer*) {}
		void                  StartChildThread(CombatBehaviorThread* thread, uint32_t child_ind, bool isControlChild);
		void                  Update();  // Ascend
	};

#pragma warning(pop)

	// !ch.empty()
	class CombatBehaviorNode : public CombatBehavior
	{
	public:
		static bool Validate(CombatBehaviorTreeNode* node);
	};

	// ch.size == 1
	class CombatBehaviorBranch : public CombatBehavior
	{
	public:
		static bool Validate(CombatBehaviorTreeNode* node);
	};

	// ch.empty()
	class CombatBehaviorAction : public CombatBehavior
	{
	public:
		static bool Validate(CombatBehaviorTreeNode* node);
	};
}

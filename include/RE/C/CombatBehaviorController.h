#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTHashMap.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class Actor;
	class CombatBehaviorResource;
	class CombatBehaviorThread;
	class CombatBehaviorTreeNode;
	class CombatController;
	class CombatGroup;
	class CombatInventory;
	class CombatState;

	class CombatBehaviorController
	{
	public:
		static Actor*            GetCurrentAttacker();
		static CombatController* GetCurrentCombatController();
		static CombatGroup*      GetCurrentCombatGroup();
		static CombatInventory*  GetCurrentCombatInventory();
		static CombatState*      GetCurrentCombatState();

		void                  Abort();
		void                  AddResource(CombatBehaviorResource* a_resource);
		void                  AddThread(CombatBehaviorThread* a_thread);
		void                  AddThreads(const BSTArray<CombatBehaviorThread*>& a_threads);
		bool                  GetResource(const BSFixedString& a_name, NiPointer<CombatBehaviorResource>& a_resource);
		CombatBehaviorThread* GetThread(std::uint32_t a_index) const;
		void                  RemoveResource(CombatBehaviorResource* a_resource);
		void                  RemoveThread(CombatBehaviorThread* a_thread);
		void                  Start(CombatBehaviorTreeNode* a_startNode);
		void                  QueueThread(CombatBehaviorThread* a_thread);
		void                  Update();
		void                  UpdateThread(CombatBehaviorThread* a_thread);

		// members
		CombatBehaviorThread*                                        defaultThread;     // 00
		BSTArray<CombatBehaviorThread*>                              activeThreads;     // 08
		CombatController*                                            combatController;  // 20
		BSTHashMap<BSFixedString, NiPointer<CombatBehaviorResource>> resources;         // 28
		BSTArray<CombatBehaviorThread*>                              queued;            // 58
		std::uint32_t                                                nextThreadID;      // 70
		std::uint32_t                                                pad74;             // 74
	};
	static_assert(sizeof(CombatBehaviorController) == 0x78);
}

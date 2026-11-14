#include "RE/C/CombatBehaviorController.h"

namespace RE
{
	Actor* CombatBehaviorController::GetCurrentAttacker()
	{
		using func_t = decltype(&CombatBehaviorController::GetCurrentAttacker);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46114, 47379) };
		return func();
	}

	CombatController* CombatBehaviorController::GetCurrentCombatController()
	{
		using func_t = decltype(&CombatBehaviorController::GetCurrentCombatController);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46113, 47378) };
		return func();
	}

	CombatGroup* CombatBehaviorController::GetCurrentCombatGroup()
	{
		using func_t = decltype(&CombatBehaviorController::GetCurrentCombatGroup);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46112, 47377) };
		return func();
	}

	CombatInventory* CombatBehaviorController::GetCurrentCombatInventory()
	{
		using func_t = decltype(&CombatBehaviorController::GetCurrentCombatInventory);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46111, 47376) };
		return func();
	}

	CombatState* CombatBehaviorController::GetCurrentCombatState()
	{
		using func_t = decltype(&CombatBehaviorController::GetCurrentCombatState);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46110, 47375) };
		return func();
	}

	void CombatBehaviorController::Abort()
	{
		using func_t = decltype(&CombatBehaviorController::Abort);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46099, 47364) };
		return func(this);
	}

	void CombatBehaviorController::AddResource(CombatBehaviorResource* a_resource)
	{
		using func_t = decltype(&CombatBehaviorController::AddResource);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46106, 47371) };
		return func(this, a_resource);
	}

	void CombatBehaviorController::AddThread(CombatBehaviorThread* a_thread)
	{
		using func_t = decltype(&CombatBehaviorController::AddThread);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46100, 47365) };
		return func(this, a_thread);
	}

	void CombatBehaviorController::AddThreads(const BSTArray<CombatBehaviorThread*>& a_threads)
	{
		using func_t = decltype(&CombatBehaviorController::AddThreads);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46101, 47366) };
		return func(this, a_threads);
	}

	bool CombatBehaviorController::GetResource(const BSFixedString& a_name, NiPointer<CombatBehaviorResource>& a_resource)
	{
		using func_t = decltype(&CombatBehaviorController::GetResource);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46105, 47370) };
		return func(this, a_name, a_resource);
	}

	CombatBehaviorThread* CombatBehaviorController::GetThread(std::uint32_t a_index) const
	{
		using func_t = decltype(&CombatBehaviorController::GetThread);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46104, 47369) };
		return func(this, a_index);
	}

	void CombatBehaviorController::RemoveResource(CombatBehaviorResource* a_resource)
	{
		using func_t = decltype(&CombatBehaviorController::RemoveResource);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46107, 47372) };
		return func(this, a_resource);
	}

	void CombatBehaviorController::RemoveThread(CombatBehaviorThread* a_thread)
	{
		using func_t = decltype(&CombatBehaviorController::RemoveThread);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46103, 47368) };
		return func(this, a_thread);
	}

	void CombatBehaviorController::Start(CombatBehaviorTreeNode* a_startNode)
	{
		using func_t = decltype(&CombatBehaviorController::Start);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46096, 47361) };
		return func(this, a_startNode);
	}

	void CombatBehaviorController::QueueThread(CombatBehaviorThread* a_thread)
	{
		using func_t = decltype(&CombatBehaviorController::QueueThread);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46102, 47367) };
		return func(this, a_thread);
	}

	void CombatBehaviorController::Update()
	{
		using func_t = decltype(&CombatBehaviorController::Update);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46097, 47362) };
		return func(this);
	}

	void CombatBehaviorController::UpdateThread(CombatBehaviorThread* a_thread)
	{
		using func_t = decltype(&CombatBehaviorController::UpdateThread);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46098, 47363) };
		return func(this, a_thread);
	}
}

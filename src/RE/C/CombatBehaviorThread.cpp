#include "RE/C/CombatBehaviorThread.h"

namespace RE
{
	CombatBehaviorThread::CombatBehaviorThread(CombatBehaviorController* a_controller, CombatBehaviorThread* a_parent)
	{
		using func_t = CombatBehaviorThread*(CombatBehaviorThread*, CombatBehaviorController*, CombatBehaviorThread*);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46226, 47481) };
		func(this, a_controller, a_parent);
	}

	CombatBehaviorThread::~CombatBehaviorThread()
	{
		using func_t = void(CombatBehaviorThread*);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46227, 47482) };
		func(this);
	}

	void CombatBehaviorThread::Abort()
	{
		using func_t = decltype(&CombatBehaviorThread::Abort);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46237, 47492) };
		return func(this);
	}

	void CombatBehaviorThread::AddChildThread(CombatBehaviorThread* a_thread)
	{
		using func_t = decltype(&CombatBehaviorThread::AddChildThread);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46251, 47506) };
		return func(this, a_thread);
	}

	void CombatBehaviorThread::Ascend()
	{
		using func_t = void(CombatBehaviorThread*);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46229, 47484) };
		return func(this);
	}

	void CombatBehaviorThread::Ascend(CombatBehaviorTreeNode* a_node)
	{
		using func_t = void(CombatBehaviorThread*, CombatBehaviorTreeNode*);
		static REL::Relocation<func_t> func{ RELOCATION_ID(529915, 47485) };
		return func(this, a_node);
	}

	bool CombatBehaviorThread::CheckRelated(CombatBehaviorThread* a_other) const
	{
		using func_t = decltype(&CombatBehaviorThread::CheckRelated);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46235, 47490) };
		return func(this, a_other);
	}

	bool CombatBehaviorThread::CheckParent(CombatBehaviorThread* a_parent) const
	{
		using func_t = decltype(&CombatBehaviorThread::CheckParent);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46234, 47489) };
		return func(this, a_parent);
	}

	void CombatBehaviorThread::Descend(std::uint32_t a_index)
	{
		using func_t = void(CombatBehaviorThread*, std::uint32_t);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46230, 47486) };
		return func(this, a_index);
	}

	void CombatBehaviorThread::Descend(CombatBehaviorTreeNode* a_node)
	{
		using func_t = void(CombatBehaviorThread*, CombatBehaviorTreeNode*);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46231, 47487) };
		return func(this, a_node);
	}

	bool CombatBehaviorThread::GetAscendingUpdate() const
	{
		using func_t = decltype(&CombatBehaviorThread::GetAscendingUpdate);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46233, 47488) };
		return func(this);
	}

	std::uint32_t CombatBehaviorThread::GetChildIndex() const
	{
		using func_t = decltype(&CombatBehaviorThread::GetChildIndex);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46531, 47786) };
		return func(this);
	}

	bool CombatBehaviorThread::GetInitialUpdate() const
	{
		using func_t = decltype(&CombatBehaviorThread::GetInitialUpdate);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46232, 47487) };
		return func(this);
	}

	void CombatBehaviorThread::Pause()
	{
		flags.set(Flags::kPaused);
	}

	void CombatBehaviorThread::Resume()
	{
		using func_t = decltype(&CombatBehaviorThread::Resume);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46236, 47491) };
		return func(this);
	}

	void CombatBehaviorThread::SetAborted()
	{
		using func_t = decltype(&CombatBehaviorThread::SetAborted);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46243, 47498) };
		return func(this);
	}

	void CombatBehaviorThread::SetFailed(bool a_failed)
	{
		using func_t = decltype(&CombatBehaviorThread::SetFailed);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46240, 47495) };
		return func(this, a_failed);
	}

	void CombatBehaviorThread::Unpause()
	{
		flags.reset(Flags::kPaused);
	}

	void CombatBehaviorThread::Suspend()
	{
		using func_t = decltype(&CombatBehaviorThread::Suspend);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46238, 47493) };
		return func(this);
	}

	void CombatBehaviorThread::Update()
	{
		using func_t = decltype(&CombatBehaviorThread::Update);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46228, 47483) };
		return func(this);
	}

	void CombatBehaviorThread::Unsuspend()
	{
		using func_t = decltype(&CombatBehaviorThread::Unsuspend);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46239, 47494) };
		return func(this);
	}
}

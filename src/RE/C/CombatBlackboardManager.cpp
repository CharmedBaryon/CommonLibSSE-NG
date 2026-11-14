#include "RE/C/CombatBlackboardManager.h"

namespace RE
{
	CombatBlackboardManager* CombatBlackboardManager::GetSingleton()
	{
		using func_t = decltype(&CombatBlackboardManager::GetSingleton);
		static REL::Relocation<func_t> func{ RELOCATION_ID(43340, 0) };
		return func();
	}

	void CombatBlackboardManager::AddFlag(const CombatBlackboardFlag* val)
	{
		using func_t = decltype(&CombatBlackboardManager::AddFlag);
		static REL::Relocation<func_t> func{ RELOCATION_ID(43319, 0) };
		return func(this, val);
	}

	void CombatBlackboardManager::AddMember(const CombatBlackboardKeyBase* val)
	{
		using func_t = decltype(&CombatBlackboardManager::AddMember);
		static REL::Relocation<func_t> func{ RELOCATION_ID(43317, 0) };
		return func(this, val);
	}

	const CombatBlackboardFlag* CombatBlackboardManager::GetFlag(uint32_t flag)
	{
		using func_t = decltype(&CombatBlackboardManager::GetFlag);
		static REL::Relocation<func_t> func{ RELOCATION_ID(43318, 0) };
		return func(this, flag);
	}

	const CombatBlackboardKeyBase* CombatBlackboardManager::GetMember(const BSFixedString& name)
	{
		auto found = keys.find(name);
		return found != keys.end() ? (*found).second : nullptr;
	}
}

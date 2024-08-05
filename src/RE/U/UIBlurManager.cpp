#include "RE/U/UIBlurManager.h"

namespace RE
{
	UIBlurManager* UIBlurManager::GetSingleton()
	{
		REL::Relocation<UIBlurManager**> singleton{ RELOCATION_ID(516871, 403350) };
		return *singleton;
	}

	void UIBlurManager::DecrementBlurCount()
	{
		using func_t = decltype(&UIBlurManager::DecrementBlurCount);
		static REL::Relocation<func_t> func{ RELOCATION_ID(51900, 52777) };
		return func(this);
	}

	void UIBlurManager::IncrementBlurCount()
	{
		using func_t = decltype(&UIBlurManager::IncrementBlurCount);
		static REL::Relocation<func_t> func{ RELOCATION_ID(51899, 52776) };
		return func(this);
	}
}

#pragma once

#include "RE/B/BSTCreateFactoryManager.h"
#include "RE/B/BSTDerivedCreator.h"

namespace RE
{
	namespace UIMessageDataFactory
	{
		[[nodiscard]] inline IUIMessageData* Create(const BSFixedString& a_name)
		{
			const auto manager = MessageDataFactoryManager::GetSingleton();
			const auto creator = manager->GetCreator(a_name);
			return creator->Create();
		}

		template <typename T>
		[[nodiscard]] inline T* Create()
		{
			const auto manager = MessageDataFactoryManager::GetSingleton();
			const auto creator = manager->GetCreator<T>(T::CLASS_NAME);
			return creator->Create();
		}
	}
}

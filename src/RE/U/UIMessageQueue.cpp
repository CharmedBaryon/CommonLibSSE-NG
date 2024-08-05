#include "RE/U/UIMessageQueue.h"

#include "RE/B/BSFixedString.h"
#include "RE/U/UIMessage.h"

namespace RE
{
	UIMessageQueue* UIMessageQueue::GetSingleton()
	{
		REL::Relocation<UIMessageQueue**> singleton{ RELOCATION_ID(514285, 400445) };
		return *singleton;
	}

	void UIMessageQueue::AddMessage(const BSFixedString& a_menuName, UI_MESSAGE_TYPE a_type, IUIMessageData* a_data)
	{
		using func_t = decltype(&UIMessageQueue::AddMessage);
		static REL::Relocation<func_t> func{ RELOCATION_ID(13530, 13631) };
		return func(this, a_menuName, a_type, a_data);
	}

	IUIMessageData* UIMessageQueue::CreateUIMessageData(const BSFixedString& a_name)
	{
		using func_t = decltype(&UIMessageQueue::CreateUIMessageData);
		static REL::Relocation<func_t> func{ RELOCATION_ID(80061, 82169) };
		return func(this, a_name);
	}

	void UIMessageQueue::ProcessCommands()
	{
		using func_t = decltype(&UIMessageQueue::ProcessCommands);
		static REL::Relocation<func_t> func{ RELOCATION_ID(80059, 82167) };
		return func(this);
	}
}

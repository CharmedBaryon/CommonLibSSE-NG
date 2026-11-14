#include "RE/B/BSUIMessageData.h"
#include "RE/U/UIMessageDataFactory.h"
#include "RE/U/UIMessageQueue.h"

namespace RE
{
	void BSUIMessageData::SendUIBoolMessage(const BSFixedString& a_menu, UI_MESSAGE_TYPE a_type, bool a_data)
	{
		const auto uiMessageQueue = UIMessageQueue::GetSingleton();
		if (uiMessageQueue) {
			const auto msgData = UIMessageDataFactory::Create<BSUIMessageData>();
			msgData->data.b = a_data;

			uiMessageQueue->AddMessage(a_menu, a_type, msgData);
		}
	}

	void BSUIMessageData::SendUIMessage(const BSFixedString& a_menu, UI_MESSAGE_TYPE a_type, std::uint32_t a_data)
	{
		const auto uiMessageQueue = UIMessageQueue::GetSingleton();
		if (uiMessageQueue) {
			const auto msgData = UIMessageDataFactory::Create<BSUIMessageData>();
			msgData->data.u = a_data;

			uiMessageQueue->AddMessage(a_menu, a_type, msgData);
		}
	}

	void BSUIMessageData::SendUIPtrMessage(const BSFixedString& a_menu, UI_MESSAGE_TYPE a_type, void* a_data)
	{
		const auto uiMessageQueue = UIMessageQueue::GetSingleton();
		if (uiMessageQueue) {
			const auto msgData = UIMessageDataFactory::Create<BSUIMessageData>();
			msgData->data.p = a_data;

			uiMessageQueue->AddMessage(a_menu, a_type, msgData);
		}
	}

	void BSUIMessageData::SendUIStringBoolMessage(const BSFixedString& a_menu, UI_MESSAGE_TYPE a_type, const BSFixedString& a_str, bool a_data)
	{
		const auto uiMessageQueue = UIMessageQueue::GetSingleton();
		if (uiMessageQueue) {
			const auto msgData = UIMessageDataFactory::Create<BSUIMessageData>();
			msgData->fixedStr = a_str;
			msgData->data.b = a_data;

			uiMessageQueue->AddMessage(a_menu, a_type, msgData);
		}
	}

	void BSUIMessageData::SendUIStringFloatMessage(const BSFixedString& a_menu, UI_MESSAGE_TYPE a_type, const BSFixedString& a_str, float a_data)
	{
		const auto uiMessageQueue = UIMessageQueue::GetSingleton();
		if (uiMessageQueue) {
			const auto msgData = UIMessageDataFactory::Create<BSUIMessageData>();
			msgData->fixedStr = a_str;
			msgData->data.f = a_data;

			uiMessageQueue->AddMessage(a_menu, a_type, msgData);
		}
	}

	void BSUIMessageData::SendUIStringMessage(const BSFixedString& a_menu, UI_MESSAGE_TYPE a_type, const BSFixedString& a_str)
	{
		const auto uiMessageQueue = UIMessageQueue::GetSingleton();
		if (uiMessageQueue) {
			const auto msgData = UIMessageDataFactory::Create<BSUIMessageData>();
			msgData->fixedStr = a_str;

			uiMessageQueue->AddMessage(a_menu, a_type, msgData);
		}
	}

	void BSUIMessageData::SendUIStringUIntMessage(const BSFixedString& a_menu, UI_MESSAGE_TYPE a_type, const BSFixedString& a_str, std::uint32_t a_data)
	{
		const auto uiMessageQueue = UIMessageQueue::GetSingleton();
		if (uiMessageQueue) {
			const auto msgData = UIMessageDataFactory::Create<BSUIMessageData>();
			msgData->fixedStr = a_str;
			msgData->data.u = a_data;

			uiMessageQueue->AddMessage(a_menu, a_type, msgData);
		}
	}
}

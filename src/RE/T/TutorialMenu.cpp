#include "RE/T/TutorialMenu.h"

#include "RE/B/BGSMessage.h"
#include "RE/B/BSTArray.h"
#include "RE/C/CRC.h"
#include "RE/F/FormTraits.h"
#include "RE/I/INISettingCollection.h"
#include "RE/T/TESFile.h"
#include "RE/T/TESFormUIData.h"
#include "RE/U/UIMessageDataFactory.h"
#include "RE/U/UIMessageQueue.h"

namespace RE
{
	using namespace literals;

	BSTArray<DEFAULT_OBJECT>& TutorialMenu::QTutorialsShown()
	{
		static REL::Relocation<BSTArray<DEFAULT_OBJECT>*> tutorialsShown{ RELOCATION_ID(520058, 406588) };
		return *tutorialsShown;
	}

	void TutorialMenu::OpenMenu(DEFAULT_OBJECT a_key)
	{
		const auto defaultObjectManager = BGSDefaultObjectManager::GetSingleton();
		const auto message = defaultObjectManager->GetObject<BGSMessage>(a_key);
		if (message) {
			OpenMenu(a_key, message);
		}
	}

	void TutorialMenu::OpenMenu(BGSMessage* a_message)
	{
		if (!a_message) {
			return;
		}

		const auto file = a_message->GetFile(0);
		const auto filename = file ? file->GetFilename() : ""sv;
		FormID     relativeID = a_message->GetFormID() & 0xFFFFFF;
		if (file && file->IsLight()) {
			relativeID &= 0xFFF;
		}

		std::uint32_t hash = BSCRC32<std::string_view>{}(filename);
		hash ^= (BSCRC32<FormID>{}(relativeID)) + 0x9e3779b9 + (hash << 6) + (hash >> 2);

		static constexpr std::uint32_t reduced_min = DEFAULT_OBJECTS::kTotal;
		static constexpr std::uint32_t reduced_range = 1u + ~reduced_min;

		const std::uint32_t reduced_hash = reduced_min + (__emulu(hash, reduced_range) >> 32);

		const auto key = static_cast<DEFAULT_OBJECT>(reduced_hash);
		OpenMenu(key, a_message);
	}

	void TutorialMenu::OpenMenu(DEFAULT_OBJECT a_key, BGSMessage* a_message)
	{
		auto& tutorialsShown = QTutorialsShown();

		const auto it = std::ranges::lower_bound(tutorialsShown, a_key);
		if (it != std::ranges::end(tutorialsShown) && *it == a_key) {
			return;
		}

		if (!"bShowTutorials:Interface"_ini.value_or(false)) {
			return;
		}

		const auto msgData = UIMessageDataFactory::Create<TESFormUIData>();
		msgData->data = a_message;
		const auto uiMessageQueue = UIMessageQueue::GetSingleton();
		uiMessageQueue->AddMessage(TutorialMenu::MENU_NAME, UI_MESSAGE_TYPE::kShow, msgData);

		tutorialsShown.emplace(it, a_key);
	}
}

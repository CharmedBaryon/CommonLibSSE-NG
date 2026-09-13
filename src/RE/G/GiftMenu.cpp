#include "RE/G/GiftMenu.h"
#include "RE/P/PlayerCharacter.h"
#include "RE/T/TESObjectREFR.h"

namespace RE
{
	RefHandle GiftMenu::GetGifterRefHandle()
	{
		static REL::Relocation<RefHandle*> handle{ RELOCATION_ID(519570, 406111) };
		return *handle;
	}

	RefHandle GiftMenu::GetReceiverRefHandle()
	{
		static REL::Relocation<RefHandle*> handle{ RELOCATION_ID(519571, 406112) };
		return *handle;
	}

	bool GiftMenu::GetShowStolenItems()
	{
		static REL::Relocation<bool*> showStolenItems{ RELOCATION_ID(519545, 406086) };
		return *showStolenItems;
	}

	BGSListForm* GiftMenu::GetFilterList()
	{
		static REL::Relocation<BGSListForm**> filterList{ RELOCATION_ID(519544, 406085) };
		return *filterList;
	}

	IGiftMenuScriptCallback* GiftMenu::GetCallbackFn()
	{
		static REL::Relocation<IGiftMenuScriptCallback**> callbackFn{ RELOCATION_ID(519572, 406113) };
		return *callbackFn;
	}

	bool GiftMenu::IsPlayerGifting()
	{
		TESObjectREFRPtr refptr = nullptr;

		if (TESObjectREFR::LookupByHandle(GetGifterRefHandle(), refptr)) {
			return refptr && refptr.get() == PlayerCharacter::GetSingleton();
		}
		return false;
	}

	bool GiftMenu::IsPlayerReceiving()
	{
		TESObjectREFRPtr refptr = nullptr;

		if (TESObjectREFR::LookupByHandle(GetReceiverRefHandle(), refptr)) {
			return refptr && refptr.get() == PlayerCharacter::GetSingleton();
		}
		return false;
	}

	void GiftMenu::OpenMenuAsGifter(Actor* a_receiver)
	{
		BSTSmartPointer<IGiftMenuScriptCallback> callbackFn = nullptr;
		return OpenMenu_Impl(PlayerCharacter::GetSingleton(), a_receiver, &callbackFn, nullptr, false);
	}

	void GiftMenu::OpenMenuAsGifter(Actor* a_receiver, GiftMenuCallback_t a_callbackFn, BGSListForm* a_filterList, bool a_showStolenItems)
	{
		auto callback = IGiftMenuScriptCallback::Create(a_callbackFn);
		return OpenMenu_Impl(PlayerCharacter::GetSingleton(), a_receiver, &callback, a_filterList, a_showStolenItems, false);
	}

	void GiftMenu::OpenMenuAsGifter(Actor* a_receiver, BSTSmartPointer<IGiftMenuScriptCallback>* a_callbackFn, BGSListForm* a_filterList, bool a_showStolenItems)
	{
		return OpenMenu_Impl(PlayerCharacter::GetSingleton(), a_receiver, a_callbackFn, a_filterList, a_showStolenItems, false);
	}

	void GiftMenu::OpenMenuAsReceiver(Actor* a_gifter)
	{
		BSTSmartPointer<IGiftMenuScriptCallback> callbackFn = nullptr;
		return OpenMenu_Impl(a_gifter, PlayerCharacter::GetSingleton(), &callbackFn, nullptr, false);
	}

	void GiftMenu::OpenMenuAsReceiver(Actor* a_gifter, GiftMenuCallback_t a_callbackFn, BGSListForm* a_filterList, bool a_showStolenItems)
	{
		auto callback = IGiftMenuScriptCallback::Create(a_callbackFn);
		return OpenMenu_Impl(a_gifter, PlayerCharacter::GetSingleton(), &callback, a_filterList, a_showStolenItems, false);
	}

	void GiftMenu::OpenMenuAsReceiver(Actor* a_gifter, BSTSmartPointer<IGiftMenuScriptCallback>* a_callbackFn, BGSListForm* a_filterList, bool a_showStolenItems)
	{
		return OpenMenu_Impl(a_gifter, PlayerCharacter::GetSingleton(), a_callbackFn, a_filterList, a_showStolenItems, false);
	}

	void GiftMenu::OpenMenu_Impl(Actor* a_gifter, Actor* a_receiver, BSTSmartPointer<IGiftMenuScriptCallback>* a_callbackFn, BGSListForm* a_filterList, bool a_showStolenItems, bool a_useFavorPoints)
	{
		using func_t = decltype(&GiftMenu::OpenMenu_Impl);
		static REL::Relocation<func_t> func{ RELOCATION_ID(50680, 51576) };
		return func(a_gifter, a_receiver, a_callbackFn, a_filterList, a_showStolenItems, a_useFavorPoints);
	}
}

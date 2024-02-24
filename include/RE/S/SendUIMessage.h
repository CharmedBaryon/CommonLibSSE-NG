#pragma once

namespace RE
{
	class TESBoundObject;
	class TESObjectREFR;

	namespace SendUIMessage
	{
		void SendInventoryUpdateMessage(TESObjectREFR* a_inventoryRef, const TESBoundObject* a_updateObj);
	}
}

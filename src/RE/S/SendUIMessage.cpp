#include "RE/S/SendUIMessage.h"

namespace RE
{
	namespace SendUIMessage
	{
		void SendInventoryUpdateMessage(TESObjectREFR* a_inventoryRef, const TESBoundObject* a_updateObj)
		{
			using func_t = decltype(&SendInventoryUpdateMessage);
			static REL::Relocation<func_t> func{ RELOCATION_ID(51911, 52849) };
			return func(a_inventoryRef, a_updateObj);
		}
	}
}

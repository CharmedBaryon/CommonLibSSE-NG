#include "RE/M/MagicSystem.h"
#include "RE/M/MagicItem.h"

namespace RE
{
	namespace MagicSystem
	{
		const char* GetCannotCastString(MagicSystem::CannotCastReason a_reason)
		{
			using func_t = decltype(&MagicSystem::GetCannotCastString);
			static REL::Relocation<func_t> func{ RELOCATION_ID(11295, 11423) };
			return func(a_reason);
		}

		float GetMagicCasterTargetUpdateInterval()
		{
			using func_t = decltype(&MagicSystem::GetMagicCasterTargetUpdateInterval);
			static REL::Relocation<func_t> func{ RELOCATION_ID(11294, 11422) };
			return func();
		}

		BGSSoundDescriptorForm* GetMagicFailureSound(MagicSystem::SpellType a_type)
		{
			using func_t = decltype(&MagicSystem::GetMagicFailureSound);
			static REL::Relocation<func_t> func{ RELOCATION_ID(11286, 11411) };
			return func(a_type);
		}

		void GetMagicItemDescription(BSString& a_out, MagicItem* a_magicItem, const char* a_beginTagFormat, const char* a_endTagFormat)
		{
			using func_t = decltype(&MagicSystem::GetMagicItemDescription);
			static REL::Relocation<func_t> func{ RELOCATION_ID(11299, 11427) };
			return func(a_out, a_magicItem, a_beginTagFormat, a_endTagFormat);
		}
	}
}

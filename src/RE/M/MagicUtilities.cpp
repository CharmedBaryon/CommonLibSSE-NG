#include "RE/M/MagicUtilities.h"

namespace RE
{
	namespace MagicUtilities
	{
		ActorValue GetAssociatedResource(MagicItem* a_item, MagicSystem::CastingSource a_castingSource)
		{
			using func_t = decltype(&GetAssociatedResource);
			static REL::Relocation<func_t> func{ RELOCATION_ID(33817, 34609) };
			return func(a_item, a_castingSource);
		}

		MagicSystem::CannotCastReason GetAssociatedResourceReason(MagicItem* a_item, MagicSystem::CastingSource a_castingSource)
		{
			using func_t = decltype(&GetAssociatedResourceReason);
			static REL::Relocation<func_t> func{ RELOCATION_ID(33818, 34610) };
			return func(a_item, a_castingSource);
		}

		bool UsesResourceOnRelease(MagicItem* a_item, MagicSystem::CastingSource a_castingSource)
		{
			using func_t = decltype(&UsesResourceOnRelease);
			static REL::Relocation<func_t> func{ RELOCATION_ID(33821, 34613) };
			return func(a_item, a_castingSource);
		}

		bool UsesResourceWhileCasting(MagicItem* a_item, MagicSystem::CastingSource a_castingSource)
		{
			using func_t = decltype(&UsesResourceWhileCasting);
			static REL::Relocation<func_t> func{ RELOCATION_ID(33820, 34612) };
			return func(a_item, a_castingSource);
		}

		bool UsesResourceWhileCharging(MagicItem* a_item, MagicSystem::CastingSource a_castingSource)
		{
			using func_t = decltype(&UsesResourceWhileCharging);
			static REL::Relocation<func_t> func{ RELOCATION_ID(33819, 34611) };
			return func(a_item, a_castingSource);
		}
	}
}

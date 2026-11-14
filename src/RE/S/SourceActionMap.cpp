#include "RE/S/SourceActionMap.h"

namespace RE
{
	namespace SourceActionMap
	{
		std::span<DEFAULT_OBJECT, 12> GetSingleton()
		{
			static DEFAULT_OBJECT singleton[12] = {
				DEFAULT_OBJECT::kActionLeftAttack,
				DEFAULT_OBJECT::kActionLeftReady,
				DEFAULT_OBJECT::kActionLeftRelease,
				DEFAULT_OBJECT::kActionLeftInterrupt,
				DEFAULT_OBJECT::kActionRightAttack,
				DEFAULT_OBJECT::kActionRightReady,
				DEFAULT_OBJECT::kActionRightRelease,
				DEFAULT_OBJECT::kActionRightInterrupt,
				DEFAULT_OBJECT::kActionVoice,
				DEFAULT_OBJECT::kActionVoiceReady,
				DEFAULT_OBJECT::kActionVoiceRelease,
				DEFAULT_OBJECT::kActionVoiceInterrupt,
			};

			return singleton;
		}

		bool DoAction(Actor* a_actor, DEFAULT_OBJECT a_action)
		{
			using func_t = decltype(&SourceActionMap::DoAction);
			static REL::Relocation<func_t> func{ RELOCATION_ID(33423, 34202) };
			return func(a_actor, a_action);
		}
	}
}

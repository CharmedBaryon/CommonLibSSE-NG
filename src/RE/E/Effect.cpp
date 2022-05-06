#include "RE/E/Effect.h"

#include "RE/E/EffectSetting.h"

namespace RE
{
	Effect::EffectItem::EffectItem() :
		magnitude(0.0),
		area(0),
		duration(0)
	{}

	Effect::Effect() :
		effectItem(),
		pad0C(0),
		baseEffect(nullptr),
		cost(0.0),
		pad1C(0),
		conditions()
	{}

	float Effect::GetMagnitude() const
	{
		if (baseEffect->data.flags.any(EffectSetting::EffectSettingData::Flag::kNoMagnitude)) {
			return 0.0f;
		}
		return effectItem.magnitude;
	}

	std::uint32_t Effect::GetArea() const
	{
		if (baseEffect->data.flags.any(EffectSetting::EffectSettingData::Flag::kNoArea)) {
			return 0;
		}
		return effectItem.area;
	}

	std::uint32_t Effect::GetDuration() const
	{
		if (baseEffect->data.flags.any(EffectSetting::EffectSettingData::Flag::kNoDuration)) {
			return 0;
		}
		return effectItem.duration;
	}

	bool Effect::IsHostile() const
	{
		return baseEffect->IsHostile();
	}
}

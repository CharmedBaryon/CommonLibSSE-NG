#include "RE/I/IngredientItem.h"

#include "RE/E/Effect.h"

namespace RE
{
	bool IngredientItem::LearnEffect(std::uint32_t a_index)
	{
		if (a_index < 4) {
			gamedata.knownEffectFlags |= 1 << a_index;
			AddChange(ChangeFlags::kIngredientUse);
			return true;
		}
		return false;
	}

	bool IngredientItem::LearnEffect(EffectSetting* a_effect)
	{
		if (!a_effect) {
			return false;
		}
		std::uint32_t index = 0;
		for (auto& effect : effects) {
			if (effect->baseEffect == a_effect) {
				LearnEffect(index);
				return true;
			}
			index++;
		}
		return false;
	}

	std::optional<std::uint32_t> IngredientItem::LearnNextEffect()
	{
		std::uint16_t flags = gamedata.knownEffectFlags;
		std::uint32_t index = 0;
		while ((flags & 1 << index) != 0) {
			if (++index >= 4) {
				return std::nullopt;
			}
		}
		LearnEffect(index);
		return index;
	}

	void IngredientItem::LearnAllEffects()
	{
		for (std::uint32_t index = 0; index < 4; ++index) {
			LearnEffect(index);
		}
	}
}

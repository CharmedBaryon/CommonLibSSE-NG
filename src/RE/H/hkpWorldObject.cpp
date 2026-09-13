#include "RE/H/hkpWorldObject.h"

#include "RE/T/TESHavokUtilities.h"

namespace RE
{
	const hkpCollidable* hkpWorldObject::GetCollidable() const
	{
		return &collidable;
	}

	hkpCollidable* hkpWorldObject::GetCollidableRW()
	{
		return &collidable;
	}

	std::optional<hkpProperty> hkpWorldObject::GetProperty(std::uint32_t a_key)
	{
		for (const auto& property : properties) {
			if (property.key == a_key) {
				return property;
			}
		}

		return std::nullopt;
	}

	const hkpShape* hkpWorldObject::GetShape() const
	{
		const auto hkpCollidable = GetCollidable();
		return hkpCollidable ? hkpCollidable->GetShape() : nullptr;
	}

	TESObjectREFR* hkpWorldObject::GetUserData() const
	{
		const auto hkpCollidable = GetCollidable();
		return hkpCollidable ? TESHavokUtilities::FindCollidableRef(*hkpCollidable) : nullptr;
	}

	bool hkpWorldObject::HasProperty(std::uint32_t a_key)
	{
		for (const auto& property : properties) {
			if (property.key == a_key) {
				return true;
			}
		}
		return false;
	}

	void hkpWorldObject::RemoveProperty(std::uint32_t a_key)
	{
		using func_t = decltype(&hkpWorldObject::RemoveProperty);
		static REL::Relocation<func_t> func{ RELOCATION_ID(75976, 77802) };
		return func(this, a_key);
	}

	void hkpWorldObject::SetProperty(std::uint32_t a_key, hkpPropertyValue a_value)
	{
		using func_t = decltype(&hkpWorldObject::SetProperty);
		static REL::Relocation<func_t> func{ RELOCATION_ID(60628, 61479) };
		return func(this, a_key, a_value);
	}
}

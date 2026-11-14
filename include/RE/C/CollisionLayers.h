#pragma once

namespace RE
{
	enum class COL_LAYER
	{
		kUnidentified = 0,
		kStatic = 1,
		kAnimStatic = 2,
		kTransparent = 3,
		kClutter = 4,
		kWeapon = 5,
		kProjectile = 6,
		kSpell = 7,
		kBiped = 8,
		kTrees = 9,
		kProps = 10,
		kWater = 11,
		kTrigger = 12,
		kTerrain = 13,
		kTrap = 14,
		kNonCollidable = 15,
		kCloudTrap = 16,
		kGround = 17,
		kPortal = 18,
		kDebrisSmall = 19,
		kDebrisLarge = 20,
		kAcousticSpace = 21,
		kActorZone = 22,
		kProjectileZone = 23,
		kGasTrap = 24,
		kShellCasting = 25,
		kTransparentSmall = 26,
		kInvisibleWall = 27,
		kTransparentSmallAnim = 28,
		kWard = 29,
		kCharController = 30,
		kStairHelper = 31,
		kDeadBip = 32,
		kBipedNoCC = 33,
		kAvoidBox = 34,
		kCollisionBox = 35,
		kCameraSphere = 36,
		kDoorDetection = 37,
		kConeProjectile = 38,
		kCameraPick = 39,
		kItemPick = 40,
		kLineOfSight = 41,
		kLOS = kLineOfSight,
		kPathPick = 42,
		kCustomPick1 = 43,
		kCustomPick2 = 44,
		kSpellExplosion = 45,
		kDroppingPick = 46,
		kUnused1 = 47,
		kUnused2 = 48,
		kUnused3 = 49,
		kUnused4 = 50,
		kUnused5 = 51,
		kUnused6 = 52,
		kUnused7 = 53,
		kInvalid = 54  // Occurs at the start of "coc BleakFallsBarrow02"
	};

	std::string_view CollisionLayerToString(COL_LAYER a_layer) noexcept;
}

namespace std
{
	[[nodiscard]] inline std::string to_string(RE::COL_LAYER a_layer)
	{
		return RE::CollisionLayerToString(a_layer).data();
	}
}

#ifdef FMT_VERSION
namespace fmt
{
	template <>
	struct formatter<RE::COL_LAYER> : formatter<std::string_view>
	{
		template <class FormatContext>
		auto format(const RE::COL_LAYER& a_layer, FormatContext& a_ctx) const
		{
			return formatter<std::string_view>::format(RE::CollisionLayerToString(a_layer), a_ctx);
		}
	};
}
#endif

#ifdef __cpp_lib_format
namespace std
{
	template <class CharT>
	struct formatter<RE::COL_LAYER, CharT> : std::formatter<std::string_view, CharT>
	{
		template <class FormatContext>
		auto format(RE::COL_LAYER a_layer, FormatContext& a_ctx) const
		{
			return formatter<std::string_view, CharT>::format(RE::CollisionLayerToString(a_layer), a_ctx);
		}
	};
}
#endif

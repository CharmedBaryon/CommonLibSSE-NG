#pragma once

#include "RE/B/BSIntrusiveRefCounted.h"
#include "RE/N/NiPoint2.h"

namespace RE
{
	class BSShaderMaterial : public BSIntrusiveRefCounted
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSShaderMaterial;
		inline static constexpr auto VTABLE = VTABLE_BSShaderMaterial;

		enum class Feature
		{
			kNone = static_cast<std::underlying_type_t<Feature>>(-1),
			kDefault = 0,
			kEnvironmentMap = 1,
			kGlowMap = 2,
			kParallax = 3,
			kFaceGen = 4,
			kFaceGenRGBTint = 5,
			kHairTint = 6,
			kParallaxOcc = 7,
			kMultiTexLand = 8,
			kLODLand = 9,
			kUnknown = 10,
			kMultilayerParallax = 11,
			kTreeAnim = 12,
			kMultiIndexTriShapeSnow = 14,
			kLODObjectsHD = 15,
			kEye = 16,
			kCloud = 17,
			kLODLandNoise = 18,
			kMultiTexLandLODBlend = 19
		};

		enum class Type
		{
			kBase = 0,
			kEffect = 1,
			kLighting = 2,
			kWater = 3
		};

		virtual ~BSShaderMaterial() = default;  // 00

		// add
		virtual BSShaderMaterial* Create();                             // 01
		virtual void              CopyMembers(BSShaderMaterial* that);  // 02
		virtual bool              DoIsCopy(BSShaderMaterial* that);     // 03
		virtual std::uint32_t     ComputeCRC32(uint32_t srcHash);       // 04
		virtual BSShaderMaterial* GetDefault();                         // 05
		virtual Feature           GetFeature() const;                   // 06 - { return Feature::kDefault; }
		virtual Type              GetType() const;                      // 07 - { return Type::kBase; }

		// members
		NiPoint2      texCoordOffset[2];                                  // 0C
		NiPoint2      texCoordScale[2] = { { 1.f, 1.f }, { 1.f, 1.f } };  // 1C
		std::uint32_t hashKey = std::numeric_limits<uint32_t>::max();     // 2C
		std::uint32_t unk30;                                              // 30
		std::uint32_t unk34;                                              // 34

	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSShaderMaterial) == 0x38);

	inline BSShaderMaterial* BSShaderMaterial::Create()
	{
		auto vtable = REL::Relocation<uintptr_t***>(BSShaderMaterial::VTABLE[0]);
		auto baseMethod = reinterpret_cast<BSShaderMaterial* (*)(BSShaderMaterial*)>((vtable.get()[0x1]));
		return baseMethod(this);
	}

	inline void BSShaderMaterial::CopyMembers(BSShaderMaterial* that)
	{
		auto vtable = REL::Relocation<uintptr_t***>(BSShaderMaterial::VTABLE[0]);
		auto baseMethod = reinterpret_cast<void (*)(BSShaderMaterial*, BSShaderMaterial*)>((vtable.get()[0x2]));
		return baseMethod(this, that);
	}

	inline bool BSShaderMaterial::DoIsCopy(BSShaderMaterial* that)
	{
		auto vtable = REL::Relocation<uintptr_t***>(BSShaderMaterial::VTABLE[0]);
		auto baseMethod = reinterpret_cast<bool (*)(BSShaderMaterial*, BSShaderMaterial*)>((vtable.get()[0x3]));
		return baseMethod(this, that);
	}

	inline std::uint32_t BSShaderMaterial::ComputeCRC32(uint32_t srcHash)
	{
		auto vtable = REL::Relocation<uintptr_t***>(BSShaderMaterial::VTABLE[0]);
		auto baseMethod = reinterpret_cast<uint32_t (*)(BSShaderMaterial*, uint32_t)>((vtable.get()[0x4]));
		return baseMethod(this, srcHash);
	}

	inline BSShaderMaterial* BSShaderMaterial::GetDefault()
	{
		auto vtable = REL::Relocation<uintptr_t***>(BSShaderMaterial::VTABLE[0]);
		auto baseMethod = reinterpret_cast<BSShaderMaterial* (*)(BSShaderMaterial*)>((vtable.get()[0x5]));
		return baseMethod(this);
	}

	inline BSShaderMaterial::Feature BSShaderMaterial::GetFeature() const
	{
		return Feature::kDefault;
	}

	inline BSShaderMaterial::Type BSShaderMaterial::GetType() const
	{
		return Type::kBase;
	}
}

#pragma once

#include "RE/B/BSTriShape.h"
#include "RE/N/NiColor.h"
#include "RE/N/NiSmartPointer.h"
#include <DirectXMath.h>

#include "REX/W32/D3D.h"

namespace RE
{
	namespace BSGraphics
	{
		class IndexBuffer;
	}

	class BSShaderProperty;

	class BSMultiIndexTriShape : public BSTriShape
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSMultiIndexTriShape;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSMultiIndexTriShape;
		inline static constexpr auto VTABLE = VTABLE_BSMultiIndexTriShape;

		struct MULTI_INDEX_TRISHAPE_RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                       \
	BSGraphics::IndexBuffer*    altIndexBuffer;           /* 00 */ \
	std::uint32_t               altPrimCount;             /* 08 */ \
	REX::W32::XMFLOAT4X4        materialProjection;       /* 0C */ \
	std::uint32_t               pad1AC;                   /* 4C */ \
	NiPointer<BSShaderProperty> additionalShaderProperty; /* 50 */ \
	std::uint8_t                useAdditionalTriList;     /* 58 */ \
	std::uint8_t                pad1B9;                   /* 59 */ \
	std::uint16_t               pad1BA;                   /* 5A */ \
	NiColorA                    materialParams;           /* 5C */ \
	float                       materialScale;            /* 6C */ \
	float                       normalDampener;           /* 70 */ \
	std::uint32_t               unk1D4;                   /* 74 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(MULTI_INDEX_TRISHAPE_RUNTIME_DATA) == 0x78);

		~BSMultiIndexTriShape() override;  // 00

		// override (BSGeometry)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		// Compatibility between VR and non-VR breaks beyond this point.
		BSMultiIndexTriShape* AsMultiIndexTriShape() override;  // 35 - { return this; }
#endif

		[[nodiscard]] inline MULTI_INDEX_TRISHAPE_RUNTIME_DATA& GetMultiIndexTrishapeRuntimeData() noexcept
		{
			return REL::RelocateMember<MULTI_INDEX_TRISHAPE_RUNTIME_DATA>(this, 0x160, 0x1A8);
		}

		[[nodiscard]] inline const MULTI_INDEX_TRISHAPE_RUNTIME_DATA& GetMultiIndexTrishapeRuntimeData() const noexcept
		{
			return REL::RelocateMember<MULTI_INDEX_TRISHAPE_RUNTIME_DATA>(this, 0x160, 0x1A8);
		}

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT  // 160, 1A8
#endif
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(BSMultiIndexTriShape) == 0x1D8);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(BSMultiIndexTriShape) == 0x220);
#endif
}
#undef RUNTIME_DATA_CONTENT

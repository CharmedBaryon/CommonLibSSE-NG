#pragma once

#include "RE/B/BSGeometry.h"

namespace RE
{
	class BSTriShape : public BSGeometry
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSTriShape;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSTriShape;
		inline static constexpr auto VTABLE = VTABLE_BSTriShape;
;

		struct TRISHAPE_RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT             \
	std::uint16_t triangleCount; /* 0 */ \
	std::uint16_t vertexCount;   /* 2 */ \
	std::uint32_t pad15C;        /* 3 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(TRISHAPE_RUNTIME_DATA) == 0x8);

		~BSTriShape() override;  // 00

		// override (BSGeometry)
		const NiRTTI* GetRTTI() const override;                           // 02
		BSTriShape*   AsTriShape() override;                              // 09
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void          LoadBinary(NiStream& a_stream) override;            // 18
		void          LinkObject(NiStream& a_stream) override;            // 19 - { BSGeometry::LinkObject(a_stream); }
		bool          RegisterStreamables(NiStream& a_stream) override;   // 1A - { return BSGeometry::RegisterStreamables(a_stream); }
		void          SaveBinary(NiStream& a_stream) override;            // 1B
		bool          IsEqual(NiObject* a_object) override;               // 1C - { return false; }

		[[nodiscard]] inline TRISHAPE_RUNTIME_DATA& GetTrishapeRuntimeData() noexcept
		{
			return REL::RelocateMember<TRISHAPE_RUNTIME_DATA>(this, 0x158, 0x198);
		}

		[[nodiscard]] inline const TRISHAPE_RUNTIME_DATA& GetTrishapeRuntimeData() const noexcept
		{
			return REL::RelocateMember<TRISHAPE_RUNTIME_DATA>(this, 0x158, 0x198);
		}

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT  // 158, 1A0
#endif
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(BSTriShape) == 0x160);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(BSTriShape) == 0x1A8);
#endif
}
#undef RUNTIME_DATA_CONTENT

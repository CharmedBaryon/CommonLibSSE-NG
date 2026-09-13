#pragma once

#include "RE/B/BSNiNode.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class BSOrderedNode : public BSNiNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSOrderedNode;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSOrderedNode;
		inline static constexpr auto VTABLE = VTABLE_BSOrderedNode;

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT               \
	NiBound       orderedBound;   /* 00 */ \
	bool          useStaticBound; /* 10 */ \
	std::uint32_t pad13C;         /* 11 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x18);

		~BSOrderedNode() override;  // 00

		// override (BSNiNode)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void          LoadBinary(NiStream& a_stream) override;            // 18
		void          LinkObject(NiStream& a_stream) override;            // 19
		bool          RegisterStreamables(NiStream& a_stream) override;   // 1A
		void          SaveBinary(NiStream& a_stream) override;            // 1B
		bool          IsEqual(NiObject* a_object) override;               // 1C
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		// The following are virtual functions past the point where VR compatibility breaks.
		void UpdateDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;          // 2C
		void UpdateSelectedDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;  // 2D
		void OnVisible(NiCullingProcess& a_process, std::int32_t a_alphaGroupIndex) override;  // 34
#endif

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x128, 0x150);
		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT  // 128, 150
#endif
	};
	STATIC_ASSERT_SIZE(BSOrderedNode, 0x140, 0x140, 0x168, 0x110);
}
#undef RUNTIME_DATA_CONTENT

#pragma once

#include "RE/N/NiNode.h"

namespace RE
{
	class BSLeafAnimNode;
	class BSTreeNode;

	class BSFadeNode : public NiNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSFadeNode;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSFadeNode;
		inline static constexpr auto VTABLE = VTABLE_BSFadeNode;

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT            \
	float         unk128;      /* 00 */ \
	float         unk12C;      /* 04 */ \
	float         currentFade; /* 08 */ \
	std::uint32_t unk134;      /* 0C */ \
	std::uint32_t unk138;      /* 10 */ \
	std::uint32_t unk13C;      /* 14 */ \
	float         unk140;      /* 18 */ \
	std::uint32_t unk144;      /* 1C */ \
	std::uint32_t unk148;      /* 20 */ \
	float         unk14C;      /* 24 */ \
	std::uint16_t unk150;      /* 28 */ \
	std::uint8_t  unk152;      /* 2A */ \
	std::uint8_t  unk153;      /* 2B */ \
	std::uint8_t  unk154;      /* 2C */ \
	std::uint8_t  unk155;      /* 2D */ \
	std::uint16_t unk156;      /* 2E */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x30);

		~BSFadeNode() override;  // 00

		// override (NiNode)
		const NiRTTI* GetRTTI() const override;                           // 02
		BSFadeNode*   AsFadeNode() override;                              // 05 - { return this; }
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void          LoadBinary(NiStream& a_stream) override;            // 18
		void          LinkObject(NiStream& a_stream) override;            // 19
		bool          RegisterStreamables(NiStream& a_stream) override;   // 1A
		void          SaveBinary(NiStream& a_stream) override;            // 1B
		bool          IsEqual(NiObject* a_object) override;               // 1C
#ifndef SKYRIM_CROSS_VR
		// The following are virtual functions past the point where VR compatibility breaks.
		void UpdateSelectedDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;  // 2D
		void OnVisible(NiCullingProcess& a_process) override;                                  // 34
#endif

		// add
		SKYRIM_REL_VR_VIRTUAL BSTreeNode*     AsTreeNode();      // 3E - { return 0; }
		SKYRIM_REL_VR_VIRTUAL BSLeafAnimNode* AsLeafAnimNode();  // 3F - { return 0; }

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x128, 0x150);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x128, 0x150);
		}

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT  // 128, 150
#endif
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(BSFadeNode) == 0x158);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(BSFadeNode) == 0x180);
#endif
}
#undef RUNTIME_DATA_CONTENT

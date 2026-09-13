#pragma once

#include "RE/B/BSNiNode.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class BSMasterParticleSystem;

	class BSValueNode : public BSNiNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSValueNode;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSValueNode;
		inline static constexpr auto VTABLE = VTABLE_BSValueNode;

		~BSValueNode() override;  // 00

		// override (BSNiNode)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void          LoadBinary(NiStream& a_stream) override;            // 18
		void          LinkObject(NiStream& a_stream) override;            // 19
		bool          RegisterStreamables(NiStream& a_stream) override;   // 1A
		void          SaveBinary(NiStream& a_stream) override;            // 1B
		bool          IsEqual(NiObject* a_object) override;               // 1C
#ifndef SKYRIM_CROSS_VR
		void UpdateWorldData(NiUpdateData* a_data) override;  // 30
#endif

		// add
		virtual bool ParseNameForValue();  // 35

		struct VALUE_NODE_RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                      \
	std::uint8_t                      flags;            /* 128 */ \
	std::uint32_t                     value;            /* 12C */ \
	NiPointer<BSMasterParticleSystem> associatedObject; /* 130 */
		};

		RUNTIME_DATA_ACCESSOR_EX(VALUE_NODE_RUNTIME_DATA, GetValueNodeRuntimeData, 0x128, 0x150);
		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT  // 128, 150
#endif
	};
}
#undef RUNTIME_DATA_CONTENT

#pragma once
#include "BSFadeNode.h"

namespace RE
{
	class BSLeafAnimNode : public BSFadeNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSLeafAnimNode;
		inline static auto           Ni_RTTI = NiRTTI_BSLeafAnimNode;

		~BSLeafAnimNode() override;  //00

		// override (BSFadeNode)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void          LoadBinary(NiStream& a_stream) override;            // 18
		void          LinkObject(NiStream& a_stream) override;            // 19
		bool          RegisterStreamables(NiStream& a_stream) override;   // 1A
		void          SaveBinary(NiStream& a_stream) override;            // 1B
		bool          IsEqual(NiObject* a_object) override;               // 1C
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		void            OnVisible(NiCullingProcess& a_process, std::int32_t a_alphaGroupIndex) override;  // 34
		BSLeafAnimNode* AsLeafAnimNode() override;                                                        // 3F
#elif defined(EXCLUSIVE_SKYRIM_VR)
		// VR has different vtable layout - these functions don't exist
#else
		void            OnVisible(NiCullingProcess& a_process, std::int32_t a_alphaGroupIndex);  // 34 - Multi-runtime (non-virtual)
		BSLeafAnimNode* AsLeafAnimNode();                                                        // 3F - Multi-runtime (non-virtual)
#endif
	private:
		float sqrDistanceToCamera;  // 158 / 110
		float leafAmplitudeRefr;    // 15C / 114
		float leafFrequency;        // 160 / 118
		float runningTime;          // 164 / 11C
		float previousTimer;        // 168 / 120
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(BSLeafAnimNode) == 0x170);
#endif
}

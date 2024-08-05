#pragma once

#include "RE/N/NiNode.h"

namespace RE
{
	class NiBillboardNode : public NiNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiBillboardNode;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiBillboardNode;
		inline static constexpr auto VTABLE = VTABLE_NiBillboardNode;

		enum
		{
			FACE_MODE_POS = 0,
			FACE_MODE_MASK = 7,
		};

		enum class FaceMode
		{
			kAlwaysFaceCamera,
			kRotateAboutUp,
			kRigidFaceCamera,
			kAlwaysFaceCenter,
			kRigidFaceCenter,
			kBSRotateAboutUp
		};

		~NiBillboardNode() override;  // 00

		// override (NiNode)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void          LoadBinary(NiStream& a_stream) override;            // 18
		void          LinkObject(NiStream& a_stream) override;            // 19
		bool          RegisterStreamables(NiStream& a_stream) override;   // 1A
		void          SaveBinary(NiStream& a_stream) override;            // 1B
		bool          IsEqual(NiObject* a_object) override;               // 1C
#ifndef SKYRIM_CROSS_VR
		void          UpdateWorldBound() override;                        // 2F
		void          UpdateWorldData(NiUpdateData* a_data) override;     // 30
		void          OnVisible(NiCullingProcess& a_process) override;    // 34
#endif
		[[nodiscard]] FaceMode GetMode() const
		{
			return static_cast<FaceMode>(userFlags & FACE_MODE_MASK);
		}

		void SetMode(FaceMode a_mode)
		{
			userFlags = static_cast<uint16_t>((std::to_underlying(a_mode) << FACE_MODE_POS) | userFlags & ~FACE_MODE_MASK);
		}

		// members
		std::uint16_t userFlags;  // 128
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(NiBillboardNode) == 0x130);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(NiBillboardNode) == 0x158);
#else
	static_assert(sizeof(NiBillboardNode) == 0x118);
#endif
}

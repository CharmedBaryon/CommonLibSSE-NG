#pragma once

#include "RE/B/BSLightingShaderProperty.h"
#include "RE/B/BSShaderProperty.h"
#include "RE/N/NiAVObject.h"
#include "RE/N/NiRTTI.h"
#include "RE/N/NiSkinPartition.h"
#include "RE/N/NiSmartPointer.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class BSMultiIndexTriShape;
	class BSSkinnedDecalTriShape;
	class NiProperty;
	class NiSkinInstance;

	class BSGeometry : public NiAVObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSGeometry;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSGeometry;
		inline static constexpr auto VTABLE = VTABLE_BSGeometry;

		enum class Type
		{
			kGeometry = 0,
			kParticles = 1,
			kStripParticles = 2,
			kTriShape = 3,
			kDynamicTriShape = 4,
			kMeshLODTriShape = 5,
			kLODMultiIndexTriShape = 6,
			kMultiIndexTriShape = 7,
			kSubIndexTriShape = 8,
			kSubIndexLandTriShape = 9,
			kMultiStreamInstanceTriShape = 10,
			kParticleShaderDynamicTriShape = 11,
			kLines = 12,
			kDynamicLines = 13,
			kInstanceGroup = 14
		};

		struct MODEL_DATA
		{
#if defined(EXCLUSIVE_SKYRIM_VR)
#	define MODEL_DATA_CONTENT        \
		NiBound  modelBound; /* 0 */  \
		NiPoint3 unk148;     /* 10 */ \
		NiPoint3 unk154;     /* 2C */
#else
#	define MODEL_DATA_CONTENT NiBound modelBound; /* 0 */
#endif
			MODEL_DATA_CONTENT
		};
		STATIC_ASSERT_SIZE(MODEL_DATA, 0x10, 0x28);

		struct GEOMETRY_RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                         \
	NiPointer<NiAlphaProperty>  alphaProperty;  /* 00 */             \
	NiPointer<BSShaderProperty> shaderProperty; /* 08 */             \
	NiPointer<NiSkinInstance>   skinInstance;   /* 10 */             \
	BSGraphics::TriShape*       rendererData;   /* 18 */             \
	void*                       unk140;         /* 20 - smart ptr */ \
	BSGraphics::VertexDesc      vertexDesc;     /* 28 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(GEOMETRY_RUNTIME_DATA) == 0x30);

		~BSGeometry() override;  // 00

		// override (NiAVObject)
		const NiRTTI* GetRTTI() const override;                            // 02
		BSGeometry*   AsGeometry() override;                               // 07 - { return this; }
		void          LoadBinary(NiStream& a_stream) override;             // 18
		void          LinkObject(NiStream& a_stream) override;             // 19
		bool          RegisterStreamables(NiStream& a_stream) override;    // 1A
		void          SaveBinary(NiStream& a_stream) override;             // 1B
		bool          IsEqual(NiObject* a_object) override;                // 1C - { return false; }
		void          ProcessClone(NiCloningProcess& a_cloning) override;  // 1D
		void          PostLinkObject(NiStream& a_stream) override;         // 1E
#ifndef SKYRIM_CROSS_VR
		// The following are virtual functions past the point where VR compatibility breaks.
		void AttachProperty(NiAlphaProperty* a_property) override;                                                        // 27
		void SetSelectiveUpdateFlags(bool& a_selectiveUpdate, bool a_selectiveUpdateTransforms, bool& a_rigid) override;  // 2B
		void UpdateDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;                                     // 2C
		void UpdateSelectedDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;                             // 2D
		void UpdateRigidDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;                                // 2E
		void UpdateWorldBound() override;                                                                                 // 2F
		void OnVisible(NiCullingProcess& a_process, std::int32_t a_alphaGroupIndex) override;                             // 34
#endif

		// add
		SKYRIM_REL_VR_VIRTUAL BSMultiIndexTriShape*   AsMultiIndexTriShape();    // 35 - { return 0; }
		SKYRIM_REL_VR_VIRTUAL BSSkinnedDecalTriShape* AsSkinnedDecalTriShape();  // 36 - { return 0; }
		SKYRIM_REL_VR_VIRTUAL std::uint32_t GetVisibleGroupsTriangleCount();     // 37 - { return 0; }

		RUNTIME_DATA_ACCESSOR_EX(MODEL_DATA, GetModelData, 0x110, 0x138);
		RUNTIME_DATA_ACCESSOR_EX(GEOMETRY_RUNTIME_DATA, GetGeometryRuntimeData, 0x120, 0x160);
		using BSGeometryTypeSet = REX::EnumSet<Type, std::uint8_t>;
		RUNTIME_DATA_ACCESSOR_EX(BSGeometryTypeSet, GetType, 0x150, 0x190);

		inline BSLightingShaderProperty* lightingShaderProp_cast()
		{
			if (auto effect = GetGeometryRuntimeData().shaderProperty.get(); effect) {
				if (auto rtti = effect->GetRTTI(); rtti) {
					const std::string rttiStr(rtti->GetName());
					if (rttiStr == "BSLightingShaderProperty") {
						return static_cast<BSLightingShaderProperty*>(effect);
					}
				}
			}
			return nullptr;
		}

		// members
#ifndef SKYRIM_CROSS_VR
		MODEL_DATA_CONTENT;    // 110, 138
		RUNTIME_DATA_CONTENT;  // 120, 160
#	if defined(EXCLUSIVE_SKYRIM_FLAT)
		REX::EnumSet<Type, std::uint8_t> type;    // 150
		std::uint8_t                     pad151;  // 151
		std::uint16_t                    pad152;  // 152
		std::uint32_t                    pad154;  // 154
#	elif defined(EXCLUSIVE_SKYRIM_VR)
		BSGeometryTypeSet type;    // 190
		std::uint8_t      pad191;  // 191
		std::uint16_t     pad192;  // 192
		std::uint32_t     pad194;  // 194
#	endif
#endif
	};
	STATIC_ASSERT_SIZE(BSGeometry, 0x158, 0x198);
}
#undef MODEL_DATA_CONTENT
#undef RUNTIME_DATA_CONTENT

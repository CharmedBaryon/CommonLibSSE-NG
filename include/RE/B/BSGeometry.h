#pragma once

#include "RE/B/BSLightingShaderProperty.h"
#include "RE/N/NiAVObject.h"
#include "RE/N/NiRTTI.h"
#include "RE/N/NiSkinPartition.h"
#include "RE/N/NiSmartPointer.h"

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

		struct States
		{
			enum State
			{
				kProperty,
				kEffect,
				kTotal
			};
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
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		static_assert(sizeof(MODEL_DATA) == 0x10);
#elif defined(EXCLUSIVE_SKYRIM_VR)
		static_assert(sizeof(MODEL_DATA) == 0x28);
#endif

		struct GEOMETRY_RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                   \
	NiPointer<NiProperty>     properties[States::kTotal]; /* 00 */             \
	NiPointer<NiSkinInstance> skinInstance;               /* 10 */             \
	BSGraphics::TriShape*     rendererData;               /* 18 */             \
	void*                     unk20;                      /* 20 - smart ptr */ \
	BSGraphics::VertexDesc    vertexDesc;                 /* 28 */

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
		void OnVisible(NiCullingProcess& a_process) override;                                                             // 34
#endif

		// add
		SKYRIM_REL_VR_VIRTUAL BSMultiIndexTriShape*   AsMultiIndexTriShape();    // 35 - { return 0; }
		SKYRIM_REL_VR_VIRTUAL BSSkinnedDecalTriShape* AsSkinnedDecalTriShape();  // 36 - { return 0; }
		SKYRIM_REL_VR_VIRTUAL void                    Unk_37(void);              // 37 - { return 0; }

		[[nodiscard]] inline MODEL_DATA& GetModelData() noexcept
		{
			return REL::RelocateMember<MODEL_DATA>(this, 0x110, 0x138);
		}

		[[nodiscard]] inline const MODEL_DATA& GetModelData() const noexcept
		{
			return REL::RelocateMember<MODEL_DATA>(this, 0x110, 0x138);
		}

		[[nodiscard]] inline GEOMETRY_RUNTIME_DATA& GetGeometryRuntimeData() noexcept
		{
			return REL::RelocateMember<GEOMETRY_RUNTIME_DATA>(this, 0x120, 0x160);
		}

		[[nodiscard]] inline const GEOMETRY_RUNTIME_DATA& GetGeometryRuntimeData() const noexcept
		{
			return REL::RelocateMember<GEOMETRY_RUNTIME_DATA>(this, 0x120, 0x160);
		}

		[[nodiscard]] inline stl::enumeration<Type, std::uint8_t>& GetType() noexcept
		{
			return REL::RelocateMember<stl::enumeration<Type, std::uint8_t>>(this, 0x150, 0x190);
		}

		[[nodiscard]] inline const stl::enumeration<Type, std::uint8_t>& GetType() const noexcept
		{
			return REL::RelocateMember<stl::enumeration<Type, std::uint8_t>>(this, 0x150, 0x190);
		}

		inline BSLightingShaderProperty* lightingShaderProp_cast()
		{
			if (auto effect = GetGeometryRuntimeData().properties[States::kEffect].get(); effect) {
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
#	ifndef ENABLE_SKYRIM_VR
		stl::enumeration<Type, std::uint8_t> type;   // 150
		std::uint8_t                         pad31;  // 151
		std::uint16_t                        pad32;  // 152
		std::uint32_t                        pad34;  // 154
#	elif defined(EXCLUSIVE_SKYRIM_VR)
		stl::enumeration<Type, std::uint32_t> type;   // 190
		std::uint8_t                          pad31;  // 194
		std::uint16_t                         pad32;  // 195
		std::uint32_t                         pad34;  // 197
#	endif
#endif
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(BSGeometry) == 0x158);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(BSGeometry) == 0x1A0);
#endif
}
#undef MODEL_DATA_CONTENT
#undef RUNTIME_DATA_CONTENT

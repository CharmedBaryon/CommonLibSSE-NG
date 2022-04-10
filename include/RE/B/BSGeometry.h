#pragma once

#include "RE/N/NiAVObject.h"
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
		inline static auto RTTI = RTTI_BSGeometry;
		inline static auto Ni_RTTI = NiRTTI_BSGeometry;

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

		struct RUNTIME_DATA {
			NiPointer<NiProperty>                properties[States::kTotal];  // 00
			NiPointer<NiSkinInstance>            skinInstance;                // 10
			BSGraphics::TriShape*                rendererData;                // 18
			void*                                unk20;                       // 20 - smart ptr
			BSGraphics::VertexDesc               vertexDesc;                  // 28
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x30);

		~BSGeometry() override;  // 00

		// override (NiAVObject)
		const NiRTTI* GetRTTI() const override;                                                                                    // 02
		BSGeometry*   AsGeometry() override;                                                                                       // 07 - { return this; }
		void          LoadBinary(NiStream& a_stream) override;                                                                     // 18
		void          LinkObject(NiStream& a_stream) override;                                                                     // 19
		bool          RegisterStreamables(NiStream& a_stream) override;                                                            // 1A
		void          SaveBinary(NiStream& a_stream) override;                                                                     // 1B
		bool          IsEqual(NiObject* a_object) override;                                                                        // 1C - { return false; }
		void          ProcessClone(NiCloningProcess& a_cloning) override;                                                          // 1D
		void          PostLinkObject(NiStream& a_stream) override;                                                                 // 1E
		// The following are virtual functions past the point where VR compatibility breaks.
//		void          AttachProperty(NiAlphaProperty* a_property) override;                                                        // 27
//		void          SetSelectiveUpdateFlags(bool& a_selectiveUpdate, bool a_selectiveUpdateTransforms, bool& a_rigid) override;  // 2B
//		void          UpdateDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;                                     // 2C
//		void          UpdateSelectedDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;                             // 2D
//		void          UpdateRigidDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;                                // 2E
//		void          UpdateWorldBound() override;                                                                                 // 2F
//		void          OnVisible(NiCullingProcess& a_process) override;                                                             // 34

		// add
		BSMultiIndexTriShape*   AsMultiIndexTriShape();    // 35 - { return 0; }
		BSSkinnedDecalTriShape* AsSkinnedDecalTriShape();  // 36 - { return 0; }
		void                    Unk_37(void);              // 37 - { return 0; }

		[[nodiscard]] inline NiBound& GetModelBound() noexcept
		{
			return REL::RelocateMember<NiBound>(this, 0x110, 0x138);
		}

		[[nodiscard]] inline const NiBound& GetModelBound() const noexcept
		{
			return REL::RelocateMember<NiBound>(this, 0x110, 0x138);
		}

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x120, 0x160);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x120, 0x160);
		}

		[[nodiscard]] inline stl::enumeration<Type, std::uint8_t>& GetType() noexcept
		{
			return REL::RelocateMember<stl::enumeration<Type, std::uint8_t>>(this, 0x150, 0x190);
		}

		[[nodiscard]] inline const stl::enumeration<Type, std::uint8_t>& GetType() const noexcept
		{
			return REL::RelocateMember<stl::enumeration<Type, std::uint8_t>>(this, 0x150, 0x190);
		}

		// members
		NiBound                               modelBound;           // 110, 138
#if !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
		NiPoint3                              unk148;               // 148
		NiPoint3                              unk154;               // 154
#endif
		RUNTIME_DATA                          runtimeData;          // 120, 160
#ifndef ENABLE_SKYRIM_VR
		stl::enumeration<Type, std::uint8_t>  type;                        // 150
		std::uint8_t                          pad31;                       // 151
		std::uint16_t                         pad32;                       // 152
		std::uint32_t                         pad34;                       // 154
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
		stl::enumeration<Type, std::uint32_t> type;                        // 190
		std::uint8_t                          pad31;                       // 194
		std::uint16_t                         pad32;                       // 195
		std::uint32_t                         pad34;                       // 197
#else
		std::uint64_t                         pad150;                      // 150
#endif
	};
#if !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(BSGeometry) == 0x1A0);
#else
	static_assert(sizeof(BSGeometry) == 0x158);
#endif
}

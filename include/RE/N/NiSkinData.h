#pragma once

#include "RE/N/NiBound.h"
#include "RE/N/NiObject.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/N/NiTransform.h"
#include "REL/Common.h"
#include "REL/Module.h"
#include "REL/Relocation.h"

namespace RE
{
	class NiSkinPartition;

	class NiSkinData : public NiObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiSkinData;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiSkinData;
		inline static constexpr auto VTABLE = VTABLE_NiSkinData;

		class BoneVertData
		{
		public:
			// members
			std::uint16_t vert;    // 0
			std::uint16_t pad2;    // 2
			float         weight;  // 4
		};
		static_assert(sizeof(BoneVertData) == 0x8);

		class BoneData
		{
		public:
			// members
			NiTransform skinToBone;  // 00
			NiBound     bound;       // 34
#if defined(EXCLUSIVE_SKYRIM_VR)
			std::byte     vrExtra[0x1C];  // 44
			BoneVertData* boneVertData;   // 60
			std::uint16_t verts;          // 68
			std::uint16_t pad6A;          // 6A
			std::uint32_t pad6C;          // 6C
#else
			std::uint32_t pad44;         // 44
			BoneVertData* boneVertData;  // 48
			std::uint16_t verts;         // 50
			std::uint16_t pad52;         // 52
			std::uint32_t pad54;         // 54
#endif
		};
#if defined(EXCLUSIVE_SKYRIM_VR)
		static_assert(sizeof(BoneData) == 0x70);
#else
		static_assert(sizeof(BoneData) == 0x58);
#endif

		~NiSkinData() override;  // 00

		// override (NiObject)
		const NiRTTI* GetRTTI() const override;                          // 02
		void          LoadBinary(NiStream& a_stream) override;           // 18
		void          LinkObject(NiStream& a_stream) override;           // 19 - { NiObject::LinkObject(a_stream); }
		bool          RegisterStreamables(NiStream& a_stream) override;  // 1A - { NiObject::RegisterStreamables(a_stream) != false; }
		void          SaveBinary(NiStream& a_stream) override;           // 1B
		bool          IsEqual(NiObject* a_object) override;              // 1C

		[[nodiscard]] static SKYRIM_REL_VR std::size_t GetBoneDataStride() noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (REL::Module::IsVR()) {
				return 0x70;
			} else {
				return 0x58;
			}
		}

		[[nodiscard]] NiTransform& GetBoneDataSkinToBone(std::uint32_t a_idx) noexcept
		{
			return *reinterpret_cast<NiTransform*>(GetBoneDataAddress(a_idx));
		}

		[[nodiscard]] const NiTransform& GetBoneDataSkinToBone(std::uint32_t a_idx) const noexcept
		{
			return *reinterpret_cast<const NiTransform*>(GetBoneDataAddress(a_idx));
		}

		[[nodiscard]] NiBound& GetBoneDataBound(std::uint32_t a_idx) noexcept
		{
			return *reinterpret_cast<NiBound*>(GetBoneDataAddress(a_idx) + 0x34);
		}

		[[nodiscard]] const NiBound& GetBoneDataBound(std::uint32_t a_idx) const noexcept
		{
			return *reinterpret_cast<const NiBound*>(GetBoneDataAddress(a_idx) + 0x34);
		}

		[[nodiscard]] BoneVertData*& GetBoneDataBoneVertData(std::uint32_t a_idx) noexcept
		{
			const auto offset = REL::Module::IsVR() ? 0x60 : 0x48;
			return *reinterpret_cast<BoneVertData**>(GetBoneDataAddress(a_idx) + offset);
		}

		[[nodiscard]] BoneVertData* GetBoneDataBoneVertData(std::uint32_t a_idx) const noexcept
		{
			const auto offset = REL::Module::IsVR() ? 0x60 : 0x48;
			return *reinterpret_cast<BoneVertData* const*>(GetBoneDataAddress(a_idx) + offset);
		}

		[[nodiscard]] std::uint16_t& GetBoneDataVerts(std::uint32_t a_idx) noexcept
		{
			const auto offset = REL::Module::IsVR() ? 0x68 : 0x50;
			return *reinterpret_cast<std::uint16_t*>(GetBoneDataAddress(a_idx) + offset);
		}

		[[nodiscard]] const std::uint16_t& GetBoneDataVerts(std::uint32_t a_idx) const noexcept
		{
			const auto offset = REL::Module::IsVR() ? 0x68 : 0x50;
			return *reinterpret_cast<const std::uint16_t*>(GetBoneDataAddress(a_idx) + offset);
		}

		[[nodiscard]] std::uint32_t& GetBoneCount() noexcept
		{
			return REL::RelocateMember<std::uint32_t>(this, 0x58, 0x58);
		}

		[[nodiscard]] const std::uint32_t& GetBoneCount() const noexcept
		{
			return REL::RelocateMember<std::uint32_t>(this, 0x58, 0x58);
		}

		[[nodiscard]] std::byte* GetBoneDataAddress(std::uint32_t a_idx) noexcept
		{
			return reinterpret_cast<std::byte*>(GetBoneData()) + (static_cast<std::size_t>(a_idx) * GetBoneDataStride());
		}

		[[nodiscard]] const std::byte* GetBoneDataAddress(std::uint32_t a_idx) const noexcept
		{
			return reinterpret_cast<const std::byte*>(GetBoneData()) + (static_cast<std::size_t>(a_idx) * GetBoneDataStride());
		}

		[[nodiscard]] BoneData* GetBoneData() noexcept
		{
			return REL::RelocateMember<BoneData*>(this, 0x50, 0x50);
		}

		[[nodiscard]] const BoneData* GetBoneData() const noexcept
		{
			return REL::RelocateMember<BoneData*>(this, 0x50, 0x50);
		}

		// members
		NiPointer<NiSkinPartition> skinPartition;     // 10
		NiTransform                rootParentToSkin;  // 18
#ifndef SKYRIM_CROSS_VR
		BoneData*     boneData;  // 50
		std::uint32_t bones;     // 58
		std::uint32_t pad5C;     // 5C
#endif
	};
	STATIC_ASSERT_SIZE(NiSkinData, 0x60, 0x60, 0x60, 0x50, 0x60);
}

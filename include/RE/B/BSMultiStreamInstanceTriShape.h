#pragma once

#include "RE/B/BSInstanceTriShape.h"

namespace RE
{
	class BSMultiStreamInstanceTriShape : public BSInstanceTriShape
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSMultiStreamInstanceTriShape;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSMultiStreamInstanceTriShape;
		inline static constexpr auto VTABLE = VTABLE_BSMultiStreamInstanceTriShape;

		struct MULTISTREAM_TRISHAPE_RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT         \
	BSTArray<void*> unk160; /* 00 */ \
	std::uint32_t   unk178; /* 18 */ \
	std::uint32_t   unk17C; /* 1C */ \
	std::uint64_t   unk180; /* 20 */ \
	std::uint64_t   unk188; /* 28 */ \
	std::uint32_t   unk190; /* 30 */ \
	std::uint32_t   unk194; /* 34 */ \
	std::uint32_t   unk198; /* 38 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(MULTISTREAM_TRISHAPE_RUNTIME_DATA) == 0x40);

		~BSMultiStreamInstanceTriShape() override;  // 00

		// override (BSInstanceTriShape)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		// The following are virtual functions past the point where VR compatibility breaks.
		void OnVisible(NiCullingProcess& a_process) override;  // 34

		// overrides for BSTriShape
		void          Unk_37(void) override;                                                                                               // 37
		void          BeginAddingInstances(std::uint32_t a_numFloatsPerInstance) override;                                                 // 38
		void          AddInstances(std::uint32_t a_numFloatsPerInstance, std::uint16_t& a_instanceData) override;                          // 39
		void          DoneAddingInstances(BSTArray<std::uint32_t>& a_instances) override;                                                  // 3A
		bool          GetIsAddingInstances() override;                                                                                     // 3B
		std::uint32_t AddGroup(std::uint32_t a_numInstances, std::uint16_t& a_instanceData, std::uint32_t a_arg3, float a_arg4) override;  // 3C
		void          RemoveGroup(std::uint32_t a_numInstance) override;                                                                   // 3D
#endif

		[[nodiscard]] inline MULTISTREAM_TRISHAPE_RUNTIME_DATA& GetMultiStreamTrishapeRuntimeData() noexcept
		{
			return REL::RelocateMember<MULTISTREAM_TRISHAPE_RUNTIME_DATA>(this, 0x160, 0x1A8);
		}

		[[nodiscard]] inline const MULTISTREAM_TRISHAPE_RUNTIME_DATA& GetMultiStreamTrishapeRuntimeData() const noexcept
		{
			return REL::RelocateMember<MULTISTREAM_TRISHAPE_RUNTIME_DATA>(this, 0x160, 0x1A8);
		}

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT  // 160, 1A8
#endif
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(BSMultiStreamInstanceTriShape) == 0x1A0);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(BSMultiStreamInstanceTriShape) == 0x1E8);
#endif
}
#undef RUNTIME_DATA_CONTENT

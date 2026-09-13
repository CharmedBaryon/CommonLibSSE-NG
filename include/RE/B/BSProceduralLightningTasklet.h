#pragma once

#include "RE/B/BSTaskletData.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class BSProceduralLightningTasklet : public BSTaskletData
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSProceduralLightningTasklet;
		inline static constexpr auto VTABLE = VTABLE_BSProceduralLightningTasklet;

		~BSProceduralLightningTasklet() override { Dtor(); }  // 00

		// override (BSTaskletData)
		void Func2() override;  // 02
		void Func3() override;  // 03

		// members
		bool          unk08;        // 08
		std::uint8_t  pad09[7];     // 09
		void*         unk10;        // 10 - group/manager pointer
		bool          active;       // 18
		std::uint8_t  pad19[3];     // 19
		std::uint32_t unk1C;        // 1C
		std::uint8_t  unk20[0x60];  // 20 - own container/array bookkeeping; not yet identified

		// VR inserts 0x18 unidentified bytes at this offset instead of appending
		// a trailing tail, shifting every field after it by +0x18.
		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                                                         \
	void*         linkedObject; /* 80 - refcounted pointer, reassigned via a dedicated helper */                     \
	std::uint16_t unk88;        /* 88 - real offset (compiled position, not 84 -- unk80 is a full 8-byte pointer) */ \
	std::uint8_t  pad8A[2];     /* 8A */                                                                             \
	std::uint16_t unk8C;        /* 8C */                                                                             \
	std::uint8_t  pad8E[2];     /* 8E */                                                                             \
	float         floatData[4]; /* 90 - same bytes as the old unk90/94/98/9C, confirmed float not uint32_t */        \
	void*         unkA0;        /* A0 */                                                                             \
	std::uint32_t unkA8;        /* A8 */                                                                             \
	bool          unkAC;        /* AC */                                                                             \
	std::uint8_t  padAD[3];     /* AD */
            RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x30);

		struct VR_RUNTIME_DATA
		{
#define VR_RUNTIME_DATA_CONTENT                                                      \
	std::uint8_t  unk80[0x18];  /* 80 - VR-only inserted data; not yet identified */ \
	void*         linkedObject; /* 98 */                                             \
	std::uint16_t unk88;        /* A0 */                                             \
	std::uint8_t  pad8A[2];     /* A2 */                                             \
	std::uint16_t unk8C;        /* A4 */                                             \
	std::uint8_t  pad8E[2];     /* A6 */                                             \
	float         floatData[4]; /* A8 */                                             \
	void*         unkA0;        /* B8 */                                             \
	std::uint32_t unkA8;        /* C0 */                                             \
	bool          unkAC;        /* C4 */                                             \
	std::uint8_t  padAD[3];     /* C5 */
            VR_RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(VR_RUNTIME_DATA) == 0x48);

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x80, 0x0);
		VR_ONLY_POINTER_ACCESSOR(VR_RUNTIME_DATA, GetVRRuntimeData, 0x80);

#if defined(EXCLUSIVE_SKYRIM_FLAT)
		RUNTIME_DATA_CONTENT;  // 80
#elif defined(EXCLUSIVE_SKYRIM_VR)
		VR_RUNTIME_DATA_CONTENT;  // 80
#endif

	private:
		void Dtor();
	};
#undef RUNTIME_DATA_CONTENT
#undef VR_RUNTIME_DATA_CONTENT
	STATIC_ASSERT_SIZE(BSProceduralLightningTasklet, 0xB0, 0xB0, 0xC8, 0x80);
}

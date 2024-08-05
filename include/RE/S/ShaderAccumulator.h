#pragma once

// see https://github.com/Nukem9/SkyrimSETest/blob/master/skyrim64_test/src/patches/TES/BSShader/BSShaderAccumulator.h
namespace RE
{
	namespace BSGraphics
	{

		class BSShaderAccumulator : public NiAlphaAccumulator
		{
		public:
			inline static constexpr auto RTTI = RTTI_BSShaderAccumulator;
			inline static auto           Ni_RTTI = NiRTTI_BSShaderAccumulator;

			virtual ~BSShaderAccumulator() = default;
			virtual void StartAccumulating(NiCamera const*) override;
			virtual void FinishAccumulatingDispatch(uint32_t RenderFlags);

			struct RUNTIME_DATA
			{
#define RUNTIME_DATA_CONTENT                \
	BSBatchRenderer* batchRenderer;         \
	uint32_t         currentPass;           \
	uint32_t         currentBucket;         \
	bool             currentActive;         \
	char             _pad[0x7];             \
	ShadowSceneNode* activeShadowSceneNode; \
	uint32_t         renderMode;            \
	char             _pad2[0x18];           \
	NiPoint3         eyePosition;           \
	char             _pad3[0x8];
                RUNTIME_DATA_CONTENT
			};
			static_assert(sizeof(RUNTIME_DATA) == 0x50);
			static_assert(offsetof(RUNTIME_DATA, batchRenderer) == 0);
			static_assert(offsetof(RUNTIME_DATA, activeShadowSceneNode) == 0x18);

			[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
			{
				return REL::RelocateMember<RUNTIME_DATA>(this, 0x130, 0x158);
			}

			[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
			{
				return REL::RelocateMember<RUNTIME_DATA>(this, 0x148, 0x170);
			}
			[[nodiscard]] static BSShaderAccumulator* GetCurrentAccumulator()
			{
				using func_t = decltype(&GetCurrentAccumulator);
				REL::Relocation<func_t> func{ REL::RelocationID(98997, 105651) };
				return func();
			}

			//members
			char _pad1[0xD0];
			bool firstPerson;      // 128
			char _pad0[0x3];       // 129
			bool drawDecals;       // 130
#if defined(EXCLUSIVE_SKYRIM_FLAT)
			RUNTIME_DATA_CONTENT;  // 130
#elif defined(EXCLUSIVE_SKYRIM_VR)
			std::uint64_t unk000[(0x158 - 0x130) >> 3];  // 130
			RUNTIME_DATA_CONTENT;                        // 158
#endif
		};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		static_assert(sizeof(BSShaderAccumulator) == 0x180);
		static_assert(offsetof(BSShaderAccumulator, batchRenderer) == 0x130);
		static_assert(offsetof(BSShaderAccumulator, currentPass) == 0x138);
		static_assert(offsetof(BSShaderAccumulator, currentBucket) == 0x13C);
		static_assert(offsetof(BSShaderAccumulator, currentActive) == 0x140);
		static_assert(offsetof(BSShaderAccumulator, activeShadowSceneNode) == 0x148);
		static_assert(offsetof(BSShaderAccumulator, renderMode) == 0x150);
		static_assert(offsetof(BSShaderAccumulator, eyePosition) == 0x16C);
#elif defined(EXCLUSIVE_SKYRIM_VR)
		static_assert(offsetof(BSShaderAccumulator, batchRenderer) == 0x158);
		static_assert(offsetof(BSShaderAccumulator, currentPass) == 0x160);
		static_assert(offsetof(BSShaderAccumulator, currentBucket) == 0x164);
		static_assert(offsetof(BSShaderAccumulator, currentActive) == 0x168);
		static_assert(offsetof(BSShaderAccumulator, activeShadowSceneNode) == 0x170);
		static_assert(offsetof(BSShaderAccumulator, renderMode) == 0x178);
		static_assert(offsetof(BSShaderAccumulator, eyePosition) == 0x194);
#else
		static_assert(sizeof(BSShaderAccumulator) == 0x130);
		static_assert(offsetof(BSShaderAccumulator, firstPerson) == 0x128);
		static_assert(offsetof(BSShaderAccumulator, drawDecals) == 0x12C);
#endif
	};
}
#undef RUNTIME_DATA_CONTENT

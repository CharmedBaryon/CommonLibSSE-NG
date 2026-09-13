#pragma once

#include "RE/B/BSCullingProcess.h"
#include "RE/B/BSScaleformExternalTexture.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/G/GFxValue.h"
#include "RE/I/ImageSpaceShaderParam.h"
#include "RE/L/LocalMapCamera.h"
#include "RE/M/MenuEventHandler.h"
#include "RE/N/NiCamera.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BSShaderAccumulator;
	class NiNode;
	struct MapMenuMarker;

	struct LocalMapMenu
	{
	public:
		struct LocalMapCullingProcess  // actually: LocalMapRenderer
		{
		public:
			// Common renderer data shared by SE/AE and VR (at different offsets)
#define RENDERER_DATA_CONTENT                                                              \
	LocalMapCamera                 camera;                /* 30260 (SE/AE) / 30270 (VR) */ \
	NiPointer<BSShaderAccumulator> accumulator;           /* 302C8 (SE/AE) / 302D8 (VR) */ \
	ImageSpaceShaderParam          imageSpaceShaderParam; /* 302D0 (SE/AE) / 302E0 (VR) */ \
	std::uint32_t                  renderTarget;          /* 30350 (SE/AE) / 30360 (VR) */ \
	std::uint32_t                  renderMode;            /* 30354 (SE/AE) / 30364 (VR) */ \
	NiPointer<NiNode>              unk30358;              /* 30358 (SE/AE) / 30368 (VR) */

			// VR-specific additional renderer data
#define VR_EXTRA_RENDERER_DATA_CONTENT    \
	BSTArray<void*> unk30370; /* 30370 */ \
	BSTArray<void*> unk30388; /* 30388 */ \
	BSTArray<void*> unk303A0; /* 303A0 */ \
	void*           unk303B8; /* 303B8 */ \
	NiCamera*       unk303C0; /* 303C0 */ \
	std::uint32_t   unk303C8; /* 303C8 */ \
	std::uint32_t   pad303CC; /* 303CC */ \
	std::uint64_t   unk303D0; /* 303D0 */

			// SE/AE renderer data
			struct RENDERER_DATA
			{
				RENDERER_DATA_CONTENT
			};

			// VR renderer data with extra arrays
			struct VR_RENDERER_DATA
			{
				RENDERER_DATA_CONTENT
				VR_EXTRA_RENDERER_DATA_CONTENT
			};

			[[nodiscard]] inline RENDERER_DATA* GetRendererData() noexcept
			{
				if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
					return &REL::RelocateMember<RENDERER_DATA>(this, 0x30260, 0);
				} else {
					return nullptr;
				}
			}

			[[nodiscard]] inline const RENDERER_DATA* GetRendererData() const noexcept
			{
				if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
					return &REL::RelocateMember<RENDERER_DATA>(this, 0x30260, 0);
				} else {
					return nullptr;
				}
			}

			[[nodiscard]] inline VR_RENDERER_DATA* GetVRRendererData() noexcept
			{
				if SKYRIM_REL_VR_CONSTEXPR (REL::Module::IsVR()) {
					return &REL::RelocateMember<VR_RENDERER_DATA>(this, 0, 0x30270);
				} else {
					return nullptr;
				}
			}

			[[nodiscard]] inline const VR_RENDERER_DATA* GetVRRendererData() const noexcept
			{
				if SKYRIM_REL_VR_CONSTEXPR (REL::Module::IsVR()) {
					return &REL::RelocateMember<VR_RENDERER_DATA>(this, 0, 0x30270);
				} else {
					return nullptr;
				}
			}

			[[nodiscard]] inline LocalMapCamera* GetLocalMapCamera() const noexcept
			{
				return &REL::RelocateMember<LocalMapCamera>(this, 0x30260, 0x30270);
			}

			void SetLocalMapCamera(const LocalMapCamera& localMapCamera) noexcept
			{
				REL::RelocateMember<LocalMapCamera>(this, 0x30260, 0x30270) = localMapCamera;
			}

			// members
			BSCullingProcess cullingProcess;  // 00000
			BSCullingJob     cullingJob;      // 301F8
#if !defined(SKYRIM_CROSS_VR)
#	if defined(EXCLUSIVE_SKYRIM_FLAT)
			RENDERER_DATA_CONTENT
#	elif defined(EXCLUSIVE_SKYRIM_VR)
			std::uint64_t unk30260;  // 30260
			std::uint64_t unk30268;  // 30268
			RENDERER_DATA_CONTENT
			VR_EXTRA_RENDERER_DATA_CONTENT
#	endif
#endif
		};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		static_assert(sizeof(LocalMapCullingProcess) == 0x30360);
#elif defined(EXCLUSIVE_SKYRIM_VR)
		static_assert(sizeof(LocalMapCullingProcess) == 0x303D8);
#else
		static_assert(sizeof(LocalMapCullingProcess) == 0x30260);  // Cross-VR: only base members (cullingProcess + cullingJob), use accessors for runtime data
#endif

		class InputHandler : public MenuEventHandler
		{
		public:
			inline static constexpr auto RTTI = RTTI_LocalMapMenu__InputHandler;
			inline static constexpr auto VTABLE = VTABLE_LocalMapMenu__InputHandler;

			~InputHandler() override;  // 00

			// override (MenuEventHandler)
			bool CanProcess(InputEvent* a_event) override;  // 01
#ifdef EXCLUSIVE_SKYRIM_VR
			bool ProcessThumbstick(ThumbstickEvent* a_event) override;  // 03 (VR 06)
			bool ProcessMouseMove(MouseMoveEvent* a_event) override;    // 04 (VR 07)
			bool ProcessButton(ButtonEvent* a_event) override;          // 05 (VR 08)
#endif

			// members
			LocalMapMenu* localMapMenu;  // 10
		};
		static_assert(sizeof(InputHandler) == 0x18);

		struct RUNTIME_DATA
		{
			BSScaleformExternalTexture    unk303A0;        // 00
			GFxValue                      localMapMovie;   // 18
			GFxValue                      mapMovie;        // 30
			void*                         unk303E8;        // 48
			BSTSmartPointer<InputHandler> unk303F0;        // 50
			std::int32_t                  selectedMarker;  // 58
			bool                          showingMap;      // 5C
			bool                          dragging;        // 5D
			bool                          controlsReady;   // 5E
			std::uint8_t                  unk303FF;        // 5F
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x60);

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x303A0, 0x30418);

		// members
		BSTArray<MapMenuMarker> mapMarkers;           // 00000
		GFxValue                unk00018;             // 00018
		float                   unk00030;             // 00030
		float                   unk00034;             // 00034
		float                   unk00038;             // 00038
		float                   unk0003C;             // 0003C
		LocalMapCullingProcess  localCullingProcess;  // 00040
		RUNTIME_DATA            runtimeData;          // 303A0, 30418
#if defined(EXCLUSIVE_SKYRIM_VR)
		std::uint32_t unk30478;  // 30478
		std::uint32_t pad3047C;  // 3047C
#endif
	};
	STATIC_ASSERT_SIZE(LocalMapMenu, 0x30400, 0x30400, 0x30480, 0x30300);
}

#undef RENDERER_DATA_CONTENT
#undef VR_EXTRA_RENDERER_DATA_CONTENT

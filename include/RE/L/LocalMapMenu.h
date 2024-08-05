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
		struct LocalMapCullingProcess
		{
		public:
			struct Data
			{
			public:
				// members
				NiPointer<BSShaderAccumulator> shaderAccumulator;  // 00
				void*                          unk08;              // 08 - smart ptr
				NiPointer<NiCamera>            camera;             // 10
				std::uint64_t                  unk18;              // 18
				std::uint64_t                  unk20;              // 20
				std::uint64_t                  unk28;              // 28
				std::uint64_t                  unk30;              // 30
				std::uint64_t                  unk38;              // 38
				void*                          unk40;              // 40 - smart ptr
			};
			static_assert(sizeof(Data) == 0x48);

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
			Data             unk301F8;        // 301F8
			std::uint64_t    unk30240;        // 30240
			std::uint64_t    unk30248;        // 30248
#if defined(EXCLUSIVE_SKYRIM_FLAT)
			std::uint64_t                  unk30250;  // 30250
			std::uint64_t                  unk30258;  // 30258
			LocalMapCamera                 camera;    // 30260
			NiPointer<BSShaderAccumulator> unk302C8;  // 302C8
			ImageSpaceShaderParam          unk302D0;  // 302D0
			std::uint64_t                  unk30350;  // 30350
			NiPointer<NiNode>              unk30358;  // 30358
#elif defined(EXCLUSIVE_SKYRIM_VR)
			std::uint64_t                  padVR1;    // 30250
			std::uint64_t                  padVR2;    // 30258
			std::uint64_t                  unk30260;  // 30260
			std::uint64_t                  unk30268;  // 30268
			LocalMapCamera                 camera;    // 30270
			NiPointer<BSShaderAccumulator> unk302D8;  // 302D8
			ImageSpaceShaderParam          unk302E0;  // 302E0
			std::uint64_t                  unk30360;  // 30360
			NiPointer<NiNode>              unk30368;  // 30368
			BSTArray<void*>                unk30370;  // 30370
			BSTArray<void*>                unk30388;  // 30388
			BSTArray<void*>                unk303A0;  // 303A0
			void*                          unk303B8;  // 303B8
			NiCamera*                      unk303C0;  // 303C0
			std::uint32_t                  unk303C8;  // 303C8
			std::uint32_t                  pad303CC;  // 303CC
			std::uint64_t                  unk303D0;  // 303D0
#else
			std::uint64_t unk30250;         // 30250
			std::uint64_t unk30258;         // 30258
			std::uint8_t  unk30260[0x100];  // 30260
#endif
		};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		static_assert(sizeof(LocalMapCullingProcess) == 0x30360);
#elif defined(EXCLUSIVE_SKYRIM_VR)
		static_assert(sizeof(LocalMapCullingProcess) == 0x303D8);
#endif

		class InputHandler : public MenuEventHandler
		{
		public:
			inline static constexpr auto RTTI = RTTI_LocalMapMenu__InputHandler;
			inline static constexpr auto VTABLE = VTABLE_LocalMapMenu__InputHandler;

			~InputHandler() override;  // 00

			// override (MenuEventHandler)
			bool CanProcess(InputEvent* a_event) override;              // 01
			bool ProcessThumbstick(ThumbstickEvent* a_event) override;  // 03
			bool ProcessMouseMove(MouseMoveEvent* a_event) override;    // 04
			bool ProcessButton(ButtonEvent* a_event) override;          // 05

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

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x303A0, 0x30418);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x303A0, 0x30418);
		}

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
	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(LocalMapMenu) == 0x30480);
#else
	static_assert(sizeof(LocalMapMenu) == 0x30400);
#endif
}

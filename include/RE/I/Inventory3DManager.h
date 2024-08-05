#pragma once

#include "RE/B/BSTArray.h"
#include "RE/B/BSTSingleton.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/E/ExtraDataList.h"
#include "RE/I/InterfaceLightSchemes.h"
#include "RE/M/MenuEventHandler.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiSmartPointer.h"
#include "SKSE/Version.h"

namespace RE
{
	class InventoryEntryData;
	class NewInventoryMenuItemLoadTask;
	class NiAVObject;
	class TESBoundObject;
	class TESObjectREFR;

	struct LoadedInventoryModel
	{
	public:
		// members
		TESForm*               itemBase;     // 00 - smart ptr
		TESBoundObject*        modelObj;     // 08
		NiPointer<NiAVObject>  spModel;      // 10
		INTERFACE_LIGHT_SCHEME lightScheme;  // 18
		float                  boundRadius;  // 1C
	};
	static_assert(sizeof(LoadedInventoryModel) == 0x20);

	class Inventory3DManager :
		public BSTSingletonSDM<Inventory3DManager>,  // 10
		public MenuEventHandler                      // 00
	{
	public:
		~Inventory3DManager() override;  // 00

		static Inventory3DManager* GetSingleton();

		void Begin3D(INTERFACE_LIGHT_SCHEME a_scheme);
		void End3D();
		void LoadInventoryItem(InventoryEntryData* a_objDesc);
		void LoadInventoryItem(TESBoundObject* a_object, ExtraDataList* a_extraDataList);
		void Render();
		bool ToggleItemZoom();
		void UnloadInventoryItem();

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                                                                               \
	BSTSmallArray<LoadedInventoryModel, 7>        loadedModels;    /* 058, 060 */                                                          \
	float                                         zoomDistance;    /* 148, 150 */                                                          \
	float                                         zoomProgress;    /* 14C, 154 - 1 if zoomed in, 0 if not, in-between during transition */ \
	BSTSmartPointer<NewInventoryMenuItemLoadTask> loadTask;        /* 150, 158 */                                                          \
	bool                                          enableUserInput; /* 158, 160 */                                                          \
	std::uint8_t                                  unk159;          /* 159, 161 */                                                          \
	bool                                          startedZoom;     /* 15A, 162 */                                                          \
	std::uint8_t                                  pad15B;          /* 15B, 163 */                                                          \
	std::uint32_t                                 pad15C;          /* 15C, 164 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x108);

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMemberIfNewer<RUNTIME_DATA>(SKSE::RUNTIME_SSE_1_6_629, this, 0x58, 0x60);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMemberIfNewer<RUNTIME_DATA>(SKSE::RUNTIME_SSE_1_6_629, this, 0x58, 0x60);
		}

		// members
		std::uint8_t           unk011;              // 011
		std::uint16_t          unk012;              // 012
		NiPoint3               itemPosCopy;         // 014
		NiPoint3               itemPos;             // 020
		float                  itemScaleCopy;       // 02C
		float                  itemScale;           // 030
		INTERFACE_LIGHT_SCHEME currentLightScheme;  // 034 - kInventory or kInventoryMagic
		TESObjectREFR*         tempRef;             // 038
		ExtraDataList          originalExtra;       // 040

#ifndef ENABLE_SKYRIM_AE
		RUNTIME_DATA_CONTENT;
#endif
	private:
		KEEP_FOR_RE()
	};
#ifndef ENABLE_SKYRIM_AE
	static_assert(sizeof(Inventory3DManager) == 0x160);
#endif
}
#undef RUNTIME_DATA
#undef RUNTIME_DATA_CONTENT

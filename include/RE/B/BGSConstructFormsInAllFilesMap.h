#pragma once

#include "RE/B/BSTArray.h"
#include "RE/B/BSTHashMap.h"

namespace RE
{
	class TESFile;
	class TESForm;

	struct ConstructFormData
	{
	public:
		// members
		TESForm*      form;   // 00
		std::uint32_t flags;  // 08
		std::uint32_t pad0C;  // 0C
	};
	static_assert(sizeof(ConstructFormData) == 0x10);

	class BGSConstructFormsMap : public BSTHashMap<std::uint32_t, ConstructFormData>
	{
	public:
		// members
		std::uint32_t flags;  // 30
		std::uint32_t pad34;  // 34
	};
	static_assert(sizeof(BGSConstructFormsMap) == 0x38);

	class BGSConstructCellsMap : public BSTHashMap<std::uint32_t, BGSConstructFormsMap*>
	{};
	static_assert(sizeof(BGSConstructCellsMap) == 0x30);

	class BGSConstructCellSubBlocksMap : public BSTHashMap<std::uint32_t, BGSConstructCellsMap*>
	{};
	static_assert(sizeof(BGSConstructCellSubBlocksMap) == 0x30);

	class BGSConstructCellBlocksMap : public BSTHashMap<std::uint32_t, BGSConstructCellSubBlocksMap*>
	{
	public:
		// members
		BGSConstructFormsMap* persistentCell;  // 30
		bool                  isExteriors;     // 38
		std::uint8_t          pad39;           // 39
		std::uint16_t         pad3A;           // 3A
		std::uint32_t         pad3C;           // 3C
	};
	static_assert(sizeof(BGSConstructCellBlocksMap) == 0x40);

	class BGSConstructWorldSpacesMap : public BSTHashMap<std::uint32_t, BGSConstructCellBlocksMap*>
	{};
	static_assert(sizeof(BGSConstructWorldSpacesMap) == 0x30);

	class BGSConstructFormsInFileMap
	{
	public:
		// members
		BGSConstructCellsMap        cellsMap;        // 00
		BGSConstructCellBlocksMap*  cellBlocksMap;   // 30
		BGSConstructWorldSpacesMap* worldSpacesMap;  // 38
		std::uint32_t               formCount;       // 40
		std::uint32_t               pad44;           // 44
	};
	static_assert(sizeof(BGSConstructFormsInFileMap) == 0x48);

	class BGSConstructedForms
	{
	public:
		// members
		BSTArray<ConstructFormData> data[3];  // 00
	};
	static_assert(sizeof(BGSConstructedForms) == 0x48);

	class BGSConstructFormsInAllFilesMap
	{
	public:
		// members
		BSTHashMap<TESFile*, BGSConstructFormsInFileMap> files;             // 00
		BGSConstructedForms                              constructedForms;  // 30
		std::uint32_t                                    count;             // 78 - sum size of all three BSTArrays
		std::uint32_t                                    pad7C;             // 7C
	};
	static_assert(sizeof(BGSConstructFormsInAllFilesMap) == 0x80);
}

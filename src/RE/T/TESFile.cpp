#include "RE/T/TESFile.h"

namespace RE
{
	bool TESFile::CloseTES(bool a_force)
	{
		using func_t = decltype(&TESFile::CloseTES);
		static REL::Relocation<func_t> func{ RELOCATION_ID(13857, 13933) };
		return func(this, a_force);
	}

	TESFile* TESFile::Duplicate(std::uint32_t a_cacheSize)
	{
		using func_t = decltype(&TESFile::Duplicate);
		static REL::Relocation<func_t> func{ RELOCATION_ID(13923, 14018) };
		return func(this, a_cacheSize);
	}

	std::uint32_t TESFile::GetCurrentSubRecordType()
	{
		using func_t = decltype(&TESFile::GetCurrentSubRecordType);
		static REL::Relocation<func_t> func{ RELOCATION_ID(13902, 13988) };
		return func(this);
	}

	FormType TESFile::GetFormType()
	{
		using func_t = decltype(&TESFile::GetFormType);
		static REL::Relocation<func_t> func{ RELOCATION_ID(13897, 13982) };
		return func(this);
	}

	bool TESFile::IsFormInMod(FormID a_formID) const
	{
		if (!IsLight() && (a_formID >> 24) == compileIndex) {
			return true;
		}
		if (IsLight() && (a_formID >> 24) == 0xFE && ((a_formID & 0x00FFF000) >> 12) == smallFileCompileIndex) {
			return true;
		}
		return false;
	}

	bool TESFile::OpenTES(NiFile::OpenMode a_accessMode, bool a_lock)
	{
		using func_t = decltype(&TESFile::OpenTES);
		static REL::Relocation<func_t> func{ RELOCATION_ID(13855, 13931) };
		return func(this, a_accessMode, a_lock);
	}

	bool TESFile::ReadData(void* a_buf, std::uint32_t a_size)
	{
		using func_t = decltype(&TESFile::ReadData);
		static REL::Relocation<func_t> func{ RELOCATION_ID(13904, 13991) };
		return func(this, a_buf, a_size);
	}

	bool TESFile::Seek(std::uint32_t a_offset)
	{
		using func_t = decltype(&TESFile::Seek);
		static REL::Relocation<func_t> func{ RELOCATION_ID(13898, 13984) };
		return func(this, a_offset);
	}

	bool TESFile::SeekNextForm(bool a_skipIgnored)
	{
		using func_t = decltype(&TESFile::SeekNextForm);
		static REL::Relocation<func_t> func{ RELOCATION_ID(13894, 13979) };
		return func(this, a_skipIgnored);
	}

	bool TESFile::SeekNextSubrecord()
	{
		using func_t = decltype(&TESFile::SeekNextSubrecord);
		static REL::Relocation<func_t> func{ RELOCATION_ID(13903, 13990) };
		return func(this);
	}

	bool TESFile::SeekNextSubrecordType(const uint32_t a_type)
	{
		auto currentType = GetCurrentSubRecordType();
		while (currentType != a_type) {
			if (!SeekNextSubrecord())
				return false;
			currentType = GetCurrentSubRecordType();
		}
		return true;
	}

	bool TESFile::SeekForm(TESForm* a_form)
	{
		using func_t = decltype(&TESFile::SeekForm);
		static REL::Relocation<func_t> func{ RELOCATION_ID(13888, 13972) };
		return func(this, a_form);
	}

	bool TESFile::SeekCell(TESWorldSpace* a_worldSpace, int32_t a_x, int32_t a_y)
	{
		using func_t = bool (*)(TESWorldSpace*, TESFile*, int32_t, int32_t);
		static REL::Relocation<func_t> func{ RELOCATION_ID(20022, 20456).address() };
		return func(a_worldSpace, this, a_x, a_y);
	}

	bool TESFile::SeekLandscapeForCurrentCell()
	{
		using func_t = decltype(&TESFile::SeekLandscapeForCurrentCell);
		static REL::Relocation<func_t> func{ RELOCATION_ID(18631, 19103) };
		return func(this);
	}

	uint32_t TESFile::GetRuntimeFormID(const FormID a_rawFormID) const
	{
		if (a_rawFormID - 1 <= 0x7FE)
			return a_rawFormID;

		const TESFile* owner = this;
		const auto     masterIndex = a_rawFormID >> 24;
		if (masterIndex < masterCount && masterPtrs)
			owner = masterPtrs[masterIndex];

		if (owner->recordFlags.any(RecordFlag::kSmallFile))
			return (a_rawFormID & 0xFFF) | 0xFE000000 | owner->smallFileCompileIndex << 12;

		return (a_rawFormID & 0xFFFFFF) | owner->compileIndex << 24;
	}
}

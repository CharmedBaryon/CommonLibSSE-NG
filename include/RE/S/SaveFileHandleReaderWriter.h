#pragma once

#include "RE/B/BaseHandleReaderWriter.h"

namespace RE::SkyrimScript
{
	class SaveFileHandleReaderWriter : public BaseHandleReaderWriter
	{
	public:
		inline static constexpr auto RTTI = RTTI_SkyrimScript__SaveFileHandleReaderWriter;
		inline static constexpr auto VTABLE = VTABLE_SkyrimScript__SaveFileHandleReaderWriter;

		~SaveFileHandleReaderWriter() override;  // 0

		// override BaseHandleReaderWriter
		void Unk_08() override;
		bool SaveHandle(SaveStorageWrapper* saveWrapper, VMHandle handle) override;
		bool LoadHandle(BSMemStorage* loadWrapper, VMHandle* out) override;
		bool SaveRefID(SaveStorageWrapper* saveWrapper, uint32_t handleLow) override;
		bool ParseScriptInstance(BSMemStorage* loadWrapper, uint32_t* scriptInstanceValues) override;

	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(SaveFileHandleReaderWriter) == 0x8);
}

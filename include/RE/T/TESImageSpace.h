#pragma once

#include "RE/F/FormTypes.h"
#include "RE/I/ImageSpaceData.h"
#include "RE/T/TESForm.h"

namespace RE
{
	class TESImageSpace : public TESForm
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESImageSpace;
		inline static constexpr auto VTABLE = VTABLE_TESImageSpace;
		inline static constexpr auto FORMTYPE = FormType::ImageSpace;

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		~TESImageSpace() override;  // 00

		// override (TESForm)
		void InitializeData() override;      // 04
		bool Load(TESFile* a_mod) override;  // 06

		// members
		ImageSpaceBaseData data;  // 20
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(TESImageSpace) == 0x70);
}

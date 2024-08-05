#pragma once

namespace RE
{
	class TESChildCell
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESChildCell;
		inline static constexpr auto VTABLE = VTABLE_TESChildCell;

		virtual ~TESChildCell();  // 00

		// add
		[[nodiscard]] virtual TESObjectCELL* GetSaveParentCell() = 0;  // 01
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(TESChildCell) == 0x8);
}

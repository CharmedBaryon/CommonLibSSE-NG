#pragma once

namespace RE
{
	class hkBaseObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkBaseObject;
		inline static constexpr auto VTABLE = VTABLE_hkBaseObject;

		virtual ~hkBaseObject() = default;  // 00
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkBaseObject) == 0x8);
}

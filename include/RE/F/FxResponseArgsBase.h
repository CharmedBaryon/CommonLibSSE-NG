#pragma once

namespace RE
{
	class GFxValue;

	class FxResponseArgsBase
	{
	public:
		FxResponseArgsBase() = default;
		FxResponseArgsBase(const FxResponseArgsBase&) = default;
		FxResponseArgsBase(FxResponseArgsBase&&) = default;

		virtual ~FxResponseArgsBase() = default;  // 00

		FxResponseArgsBase& operator=(const FxResponseArgsBase&) = default;
		FxResponseArgsBase& operator=(FxResponseArgsBase&&) = default;

		// add
		virtual std::uint32_t GetValues(GFxValue** a_params) = 0;  // 01
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(FxResponseArgsBase) == 0x8);
}

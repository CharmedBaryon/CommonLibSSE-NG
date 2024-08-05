#pragma once

#include "RE/G/GRefCountImplCore.h"

namespace RE
{
	class GRefCountImpl : GRefCountImplCore
	{
	public:
		inline static constexpr auto RTTI = RTTI_GRefCountImpl;
		inline static constexpr auto VTABLE = VTABLE_GRefCountImpl;

		~GRefCountImpl() override = default;  // 00

		void AddRef();
		void Release();

	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(GRefCountImpl) == 0x10);
}

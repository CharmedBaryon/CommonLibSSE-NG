#pragma once

#include "RE/N/NiRefObject.h"

namespace RE
{
	class BSHandleRefObject : public NiRefObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSHandleRefObject;
		inline static constexpr auto VTABLE = VTABLE_BSHandleRefObject;

		enum
		{
			kRefCountMask = 0x3FF,
			kHandleValid = 1 << 10
		};

		~BSHandleRefObject() override;  // 00

		void                        DecRefCount();
		void                        IncRefCount();
		[[nodiscard]] bool          IsHandleValid() const;
		[[nodiscard]] std::uint32_t QRefCount() const;

	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSHandleRefObject) == 0x10);
}

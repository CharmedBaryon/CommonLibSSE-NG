#pragma once

#include "RE/B/BSIntrusiveRefCounted.h"
#include "RE/B/BSTSmartPointer.h"

namespace RE
{
	using GiftMenuCallback_t = std::function<void(std::int32_t)>;

	class IGiftMenuScriptCallback : public BSIntrusiveRefCounted
	{
	public:
		inline static constexpr auto RTTI = RTTI_IGiftMenuScriptCallback;
		inline static constexpr auto VTABLE = VTABLE_IGiftMenuScriptCallback;

		virtual ~IGiftMenuScriptCallback() = default;  // 00

		virtual void Run(std::int32_t a_totalValueTransferred) = 0;  // 01

		static BSTSmartPointer<IGiftMenuScriptCallback> Create(GiftMenuCallback_t a_callback)
		{
			class Callback : public IGiftMenuScriptCallback
			{
			public:
				Callback(GiftMenuCallback_t a_callback) :
					IGiftMenuScriptCallback(), _callback(std::move(a_callback)) {}

				virtual void Run(std::int32_t a_totalValueTransferred) override { _callback(a_totalValueTransferred); }

			private:
				GiftMenuCallback_t _callback;
			};

			return BSTSmartPointer<IGiftMenuScriptCallback>(new Callback(std::move(a_callback)));
		}

		// members
		std::uint32_t pad0C;  // 0C
	};
	static_assert(sizeof(IGiftMenuScriptCallback) == 0x10);
}

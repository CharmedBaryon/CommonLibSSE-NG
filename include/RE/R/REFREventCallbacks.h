#pragma once

#include "RE/B/BSIntrusiveRefCounted.h"

namespace RE
{
	class BSStorage;

	namespace REFREventCallbacks
	{
		class IEventCallback : public BSIntrusiveRefCounted
		{
		public:
			inline static constexpr auto RTTI = RTTI_REFREventCallbacks__IEventCallback;
			inline static constexpr auto VTABLE = VTABLE_REFREventCallbacks__IEventCallback;

			virtual ~IEventCallback();  // 00

			// add
			virtual void                 operator()() = 0;                  // 01
			virtual bool                 Save(BSStorage& a_storage);        // 02
			virtual const BSFixedString* GetType() = 0;                     // 03
			virtual bool                 Load(const BSStorage& a_storage);  // 04
		};
		static_assert(sizeof(IEventCallback) == 0x10);
	}
}

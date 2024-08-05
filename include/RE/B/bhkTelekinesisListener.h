#pragma once

#include "RE/B/BSTSingleton.h"
#include "RE/B/bhkContactListener.h"

namespace RE
{
	class bhkTelekinesisListener :
		public bhkContactListener,
		public BSTSingletonSDM<bhkTelekinesisListener>
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkTelekinesisListener;
		inline static constexpr auto VTABLE = VTABLE_bhkTelekinesisListener;

		// override (bhkContactListener)
		void ContactPointCallback(const hkpContactPointEvent&) override;  // 00

		~bhkTelekinesisListener() override;  // 04

		static bhkTelekinesisListener* GetSingleton()
		{
			REL::Relocation<bhkTelekinesisListener**> singleton{ RELOCATION_ID(515445, 401584) };
			return *singleton;
		}
	};
	static_assert(sizeof(bhkTelekinesisListener) == 0x10);
}

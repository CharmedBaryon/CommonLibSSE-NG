#pragma once

#include "RE/I/IFormFactory.h"

namespace RE
{
	class FindFormTypeHelper : IFormFactory::IFactoryVisitor
	{
	public:
		inline static constexpr auto RTTI = RTTI___FindFormTypeHelper;
		inline static constexpr auto VTABLE = VTABLE___FindFormTypeHelper;

		~FindFormTypeHelper() override;  // 00

		// override (IFormFactory::IFactoryVisitor)
		BSContainer::ForEachResult VisitFactory(const IFormFactory* a_factory) override;

		// members
		const char* textToMatch;  // 08
		FormType    type;         // 10
	};
	static_assert(sizeof(FindFormTypeHelper) == 0x18);
}

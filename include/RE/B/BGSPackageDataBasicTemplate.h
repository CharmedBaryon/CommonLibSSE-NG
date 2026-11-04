#pragma once

#include "RE/B/BGSNamedPackageData.h"

namespace RE
{
	template <class Parent, class Value /*, const BSFixedString& TYPE_NAME*/>
	class BGSPackageDataBasicTemplate : public BGSNamedPackageData<Parent>
	{
	public:
		// members
		Value value;  // ??
	};
}

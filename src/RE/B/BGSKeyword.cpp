#include "RE/B/BGSKeyword.h"
#include "RE/B/BSFixedString.h"
#include "RE/C/ConcreteFormFactory.h"
#include "RE/I/IFormFactory.h"
#include <RE/B/BSEffectShaderData.h>

namespace RE
{
	BGSKeyword* RE::BGSKeyword::CreateKeyword(const BSFixedString& a_formEditorID)
	{
		auto factory = IFormFactory::GetConcreteFormFactoryByType<BGSKeyword>();
		auto keyword = factory->Create();
		keyword->formEditorID = a_formEditorID;
		return keyword;
	}
}

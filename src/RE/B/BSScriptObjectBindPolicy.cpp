#include "RE/B/BSScriptObjectBindPolicy.h"

namespace RE
{
	namespace BSScript
	{
		void ObjectBindPolicy::BindObject(BSTSmartPointer<Object>& a_objectPtr, VMHandle a_handle)
		{
			using func_t = decltype(&ObjectBindPolicy::BindObject);
			static REL::Relocation<func_t> func{ RELOCATION_ID(97379, 104184) };
			return func(this, a_objectPtr, a_handle);
		}

		void ObjectBindPolicy::GetInitialPropertyValues(VMHandle a_handle, const BSFixedString& a_className, BSTScrapHashMap<BSFixedString, Variable>& a_propertyValues, std::uint32_t& a_nonConvertedProperties) const
		{
			using func_t = decltype(&ObjectBindPolicy::GetInitialPropertyValues);
			static REL::Relocation<func_t> func{ RELOCATION_ID(97371, 104176) };
			return func(this, a_handle, a_className, a_propertyValues, a_nonConvertedProperties);
		}
	}
}

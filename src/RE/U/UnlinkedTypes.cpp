#include "RE/U/UnlinkedTypes.h"

#include "RE/M/MemoryManager.h"

namespace RE
{
	namespace BSScript
	{
		namespace UnlinkedTypes
		{
			Object::~Object()
			{
				Dtor();
				stl::memzero(this);
			}

			void Object::Dtor()
			{
				using func_t = decltype(&Object::Dtor);
				static REL::Relocation<func_t> func{ RELOCATION_ID(98654, 105309) };
				return func(this);
			}

			Object* Object::Ctor()
			{
				using func_t = decltype(&Object::Ctor);
				static REL::Relocation<func_t> func{ RELOCATION_ID(98759, 105410) };
				return func(this);
			}

			Object* Object::Create()
			{
				auto object = malloc<Object>();
				std::memset(object, 0, sizeof(Object));
				if (object) {
					object->Ctor();
				}
				return object;
			}
		}
	}
}

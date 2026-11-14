#include "RE/B/BSVisit.h"

#include "RE/B/bhkNiCollisionObject.h"
#include "RE/N/NiAVObject.h"
#include "RE/N/NiNode.h"
#include "RE/N/NiPointLight.h"
#include "RE/N/NiRTTI.h"

namespace RE
{
	namespace BSVisit
	{
		BSVisitControl TraverseScenegraphCollision(NiAVObject* a_object, std::function<BSVisitControl(bhkNiCollisionObject*)> a_func)
		{
			auto result = BSVisitControl::kContinue;

			if (!a_object) {
				return result;
			}

			auto collision = static_cast<bhkNiCollisionObject*>(a_object->collisionObject.get());
			if (collision) {
				result = a_func(collision);
				if (result == BSVisitControl::kStop) {
					return result;
				}
			}

			auto node = a_object->AsNode();
			if (node) {
				for (auto& child : node->GetChildren()) {
					result = TraverseScenegraphCollision(child.get(), a_func);
					if (result == BSVisitControl::kStop) {
						break;
					}
				}
			}

			return result;
		}

		BSVisitControl TraverseScenegraphGeometries(NiAVObject* a_object, std::function<BSVisitControl(BSGeometry*)> a_func)
		{
			auto result = BSVisitControl::kContinue;

			if (!a_object) {
				return result;
			}

			auto geom = a_object->AsGeometry();
			if (geom) {
				return a_func(geom);
			}

			auto node = a_object->AsNode();
			if (node) {
				for (auto& child : node->GetChildren()) {
					result = TraverseScenegraphGeometries(child.get(), a_func);
					if (result == BSVisitControl::kStop) {
						break;
					}
				}
			}

			return result;
		}

		BSVisitControl TraverseScenegraphLights(NiAVObject* a_object, std::function<BSVisitControl(NiPointLight*)> a_func)
		{
			auto result = BSVisitControl::kContinue;

			if (!a_object) {
				return result;
			}

			auto ptLight = netimmerse_cast<NiPointLight*>(a_object);
			if (ptLight) {
				return a_func(ptLight);
			}

			auto node = a_object->AsNode();
			if (node) {
				for (auto& child : node->GetChildren()) {
					result = TraverseScenegraphLights(child.get(), a_func);
					if (result == BSVisitControl::kStop) {
						break;
					}
				}
			}

			return result;
		}

		BSVisitControl TraverseScenegraphObjects(NiAVObject* a_object, std::function<BSVisitControl(NiAVObject*)> a_func)
		{
			auto result = BSVisitControl::kContinue;

			if (!a_object) {
				return result;
			}

			result = a_func(a_object);
			if (result == BSVisitControl::kStop) {
				return result;
			}

			auto node = a_object->AsNode();
			if (node) {
				for (auto& child : node->GetChildren()) {
					result = TraverseScenegraphObjects(child.get(), a_func);
					if (result == BSVisitControl::kStop) {
						break;
					}
				}
			}

			return result;
		}
	}
}

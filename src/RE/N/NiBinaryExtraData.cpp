#include "RE/N/NiBinaryExtraData.h"

#include "RE/N/NiTCollection.h"

#include <cstring>

namespace RE
{
	NiBinaryExtraData* NiBinaryExtraData::Create(std::string_view a_name, const std::uint8_t* a_data, std::uint32_t a_size)
	{
		auto* created = NiExtraData::Create<NiBinaryExtraData>();
		if (created) {
			created->SetName(a_name);
			if (a_size > 0 && a_data) {
				created->data = NiAlloc<std::uint8_t>(a_size);
				std::memcpy(created->data, a_data, a_size);
				created->size = a_size;
			} else {
				created->data = nullptr;
				created->size = 0;
			}
		}
		return created;
	}
}

#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/E/ExtraDataTypes.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class TESObjectREFR;

	class ExtraReferenceHandle : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraReferenceHandle;
		inline static constexpr auto VTABLE = VTABLE_ExtraReferenceHandle;
		inline static auto           EXTRADATATYPE = ExtraDataType::kReferenceHandle;

		ExtraReferenceHandle();
		explicit ExtraReferenceHandle(ObjectRefHandle a_containerRef);
		~ExtraReferenceHandle() override = default;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override;                             // 01 - { return kReferenceHandle; }
		bool          IsNotEqual(const BSExtraData* a_rhs) const override;  // 02 - { return containerRef != a_rhs->containerRef; }

		NiPointer<TESObjectREFR> GetOriginalReference();

		// members
		ObjectRefHandle containerRef;  // 10
		std::uint32_t   pad14;         // 14
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraReferenceHandle) == 0x18);
}

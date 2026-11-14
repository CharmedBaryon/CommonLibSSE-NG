#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkReferencedObject.h"

namespace RE
{
	class hkbVariableBindingSet : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbVariableBindingSet;
		inline static constexpr auto VTABLE = VTABLE_hkbVariableBindingSet;

		enum class BindingMode : std::int8_t
		{
			kGet = 0,
			kSet = 1,
		};

		struct Binding
		{
		public:
			// members
			std::uint32_t bindingPath;         // 00
			std::uint32_t pad04;               // 04
			std::uint32_t arrayElementSize;    // 08
			std::uint32_t padC;                // 0C
			std::int32_t  memberOffset;        // 10
			std::int32_t  arrayElementOffset;  // 14
			std::uint32_t unk18;               // 18
			std::int32_t  variableIndex;       // 1C
			std::uint8_t  bitIndex;            // 20
			BindingMode   bindingMode;         // 21
			std::uint8_t  memberType;          // 22
			std::uint8_t  unk23;               // 23
			std::uint8_t  flags;               // 24
			std::uint8_t  unk25[3];            // 25
		};
		static_assert(sizeof(Binding) == 0x28);

		~hkbVariableBindingSet() override;  // 00

		// members
		hkArray<Binding> bindings;                  // 10
		std::int32_t     indexOfActivationBinding;  // 20
		bool             needsValueAtActivation;    // 24
		std::uint8_t     unk25[3];                  // 25
	};
	static_assert(sizeof(hkbVariableBindingSet) == 0x28);
}

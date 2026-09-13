#pragma once

#include "RE/A/ActorValueInfo.h"
#include "RE/A/ActorValues.h"

namespace RE
{
	class ActorValueList
	{
	public:
		[[nodiscard]] static ActorValueList* GetSingleton()
		{
			static REL::Relocation<ActorValueList**> singleton{ RELOCATION_ID(514139, 400267) };
			return *singleton;
		}

		[[nodiscard]] static ActorValueInfo* GetActorValueInfo(ActorValue a_actorValue);
		[[nodiscard]] static ActorValue      LookupActorValueByName(const char* a_enumName);
		[[nodiscard]] static const char*     GetActorValueName(ActorValue a_actorValue);

		// members
		std::uint32_t   unk00;                                                // 00
		std::uint32_t   pad04;                                                // 04
		ActorValueInfo* actorValues[std::to_underlying(ActorValue::kTotal)];  // 08
	};

	[[nodiscard]] std::string_view ActorValueToString(ActorValue a_actorValue) noexcept;
}

#ifdef FMT_VERSION
namespace fmt
{
	template <>
	struct formatter<RE::ActorValue> : formatter<std::string_view>
	{
		template <class FormatContext>
		auto format(const RE::ActorValue& a_actorValue, FormatContext& a_ctx) const
		{
			return formatter<std::string_view>::format(RE::ActorValueToString(a_actorValue), a_ctx);
		}
	};
}
#endif

#ifdef __cpp_lib_format
namespace std
{
	template <class CharT>
	struct formatter<RE::ActorValue, CharT> : formatter<std::string_view, CharT>
	{
		template <class FormatContext>
		auto format(RE::ActorValue a_actorValue, FormatContext& a_ctx) const
		{
			return formatter<std::string_view, CharT>::format(RE::ActorValueToString(a_actorValue), a_ctx);
		}
	};
}
#endif

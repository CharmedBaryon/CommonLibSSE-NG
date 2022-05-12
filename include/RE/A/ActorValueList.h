#pragma once

#include "RE/A/ActorValues.h"
#include "RE/A/ActorValueInfo.h"

namespace RE
{
	class ActorValueList
	{
	public:
		[[nodiscard]] static ActorValueList* GetSingleton()
		{
			REL::Relocation<ActorValueList**> singleton{ RELOCATION_ID(514139, 400267) };
			return *singleton;
		}

		[[nodiscard]] ActorValueInfo* GetActorValue(ActorValue a_actorValue);
		[[nodiscard]] ActorValue      LookupActorValueByName(std::string_view a_enumName);

		// members
		std::uint32_t   unk00;                                                // 00
		std::uint32_t   pad04;                                                // 04
		ActorValueInfo* actorValues[stl::to_underlying(ActorValue::kTotal)];  // 08
	};
}

namespace std
{
	[[nodiscard]] inline std::string to_string(RE::ActorValue a_actorValue)
	{
		auto* info = RE::ActorValueList::GetSingleton()->GetActorValue(a_actorValue);
		return info ? info->enumName : "None";
	}

#ifdef __cpp_lib_format
	template <class CharT>
	struct formatter<RE::ActorValue, CharT> : formatter<std::string_view, CharT>
	{
		template <class FormatContext>
		auto format(RE::ActorValue a_actorValue, FormatContext& a_ctx)
		{
			auto* info = RE::ActorValueList::GetSingleton()->GetActorValue(a_actorValue);
			return formatter<std::string_view, CharT>::format(info ? info->enumName : "None", a_ctx);
		}
	};
#endif
}

namespace fmt
{
	template <>
	struct formatter<RE::ActorValue>
	{
		template <class ParseContext>
		constexpr auto parse(ParseContext& a_ctx)
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		auto format(const RE::ActorValue& a_actorValue, FormatContext& a_ctx)
		{
			auto* info = RE::ActorValueList::GetSingleton()->GetActorValue(a_actorValue);
			return fmt::format_to(a_ctx.out(), "{}", info ? info->enumName : "None");
		}
	};
}

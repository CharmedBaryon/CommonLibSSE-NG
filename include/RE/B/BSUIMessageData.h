#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSString.h"
#include "RE/I/IUIMessageData.h"
#include "RE/U/UIMessage.h"

namespace RE
{
	class BSUIMessageData : public IUIMessageData
	{
	public:
		inline static constexpr auto             RTTI = RTTI_BSUIMessageData;
		inline static constexpr auto             VTABLE = VTABLE_BSUIMessageData;
		inline static constexpr std::string_view CLASS_NAME = "BSUIMessageData";

		union Data
		{
			bool          b;
			std::uint32_t u;
			float         f;
			void*         p;
		};
		static_assert(sizeof(Data) == 0x8);

		~BSUIMessageData() override;  // 00

		static void SendUIBoolMessage(const BSFixedString& a_menu, UI_MESSAGE_TYPE a_type, bool a_data);
		static void SendUIMessage(const BSFixedString& a_menu, UI_MESSAGE_TYPE a_type, std::uint32_t a_data);
		static void SendUIPtrMessage(const BSFixedString& a_menu, UI_MESSAGE_TYPE a_type, void* a_data);
		static void SendUIStringBoolMessage(const BSFixedString& a_menu, UI_MESSAGE_TYPE a_type, const BSFixedString& a_str, bool a_data);
		static void SendUIStringFloatMessage(const BSFixedString& a_menu, UI_MESSAGE_TYPE a_type, const BSFixedString& a_str, float a_data);
		static void SendUIStringMessage(const BSFixedString& a_menu, UI_MESSAGE_TYPE a_type, const BSFixedString& a_str);
		static void SendUIStringUIntMessage(const BSFixedString& a_menu, UI_MESSAGE_TYPE a_type, const BSFixedString& a_str, std::uint32_t a_data);

		// members
		BSString*     str;       // 10
		BSFixedString fixedStr;  // 18
		Data          data;      // 20
	};
	static_assert(sizeof(BSUIMessageData) == 0x28);
}

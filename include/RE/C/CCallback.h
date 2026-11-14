#pragma once

using SteamAPICall_t = std::uint64_t;

namespace RE
{
	class CCallbackBase
	{
	public:
		enum
		{
			k_ECallbackFlagsRegistered = 0x01,
			k_ECallbackFlagsGameServer = 0x02
		};

		// add
		virtual void         Run(void* a_param);                                                   // 01
		virtual void         Run(void* a_param, bool a_IOFailure, SteamAPICall_t a_steamAPICall);  // 00
		virtual std::int32_t GetCallbackSizeBytes();                                               // 02

		// members
		std::uint8_t  callbackFlags;  // 08
		std::uint8_t  pad09;          // 09
		std::uint16_t pad0A;          // 0A
		std::int32_t  callback;       // 0C
	};
	static_assert(sizeof(CCallbackBase) == 0x10);

	template <class T, class P>
	class CCallResult : public CCallbackBase
	{
	public:
		using func_t = void (T::*)(P*);

		// override (CCallbackBase)
		void         Run(void* a_param) override;                                                   // 01
		void         Run(void* a_param, bool a_IOFailure, SteamAPICall_t a_steamAPICall) override;  // 00
		std::int32_t GetCallbackSizeBytes() override;                                               // 02

		// members
		SteamAPICall_t apiCall;  // 10
		T*             obj;      // 18
		func_t         func;     // 20
	};
	// size == 0x30

	template <class T, class P, bool bGameserver = false>
	class CCallback : public CCallbackBase
	{
	public:
		using func_t = void (T::*)(P*);

		// override (CCallbackBase)
		void         Run(void* a_param) override;                                                   // 01
		void         Run(void* a_param, bool a_IOFailure, SteamAPICall_t a_steamAPICall) override;  // 00
		std::int32_t GetCallbackSizeBytes() override;                                               // 02

		// add
		virtual ~CCallback();  // 03

		// members
		T*     obj;   // 10
		func_t func;  // 18
	};
	// size == 0x28
}

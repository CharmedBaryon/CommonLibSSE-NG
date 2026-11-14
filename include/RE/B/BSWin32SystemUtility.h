#pragma once

#include "RE/B/BSSystemUtility.h"
#include "RE/B/BSVirtualKeyboardDevice.h"
#include "RE/C/CCallback.h"

class ISteamClient;
class ISteamUtils;
struct EncryptedAppTicketResponse_t;
struct FloatingGamepadTextInputDismissed_t;
struct GameOverlayActivated_t;
struct GamepadTextInputDismissed_t;

using HSteamPipe = std::int32_t;

namespace RE
{
	class BSWin32SystemUtility : public BSSystemUtility
	{
	public:
		template <class P>
		using SteamCallback = CCallback<BSWin32SystemUtility, P, false>;
		template <class P>
		using SteamCallResult = CCallResult<BSWin32SystemUtility, P>;

		using VirtualKeyboardDoneCallback = void(void*, const char*);
		using VirtualKeyboardCancelCallback = void();

		virtual ~BSWin32SystemUtility();  // 00

#ifndef ENABLE_SKYRIM_AE
		// override (BSSystemUtility)
		void GetAuthenticationInfo(char*& a_userAuthID, std::uint64_t& a_size) override;  // 02
		void DoInitialize() override;                                                     // 04
		void DoUpdate() override;                                                         // 06
		void DoGetUserName(char* a_buffer, std::uint64_t a_size) override;                // 08
		void DoGetComputerName(char* a_buffer, std::uint64_t a_size) override;            // 0D
		void DoAuthenticateUser() override;                                               // 10
		bool Unk_12() override;                                                           // 12
#endif

		[[nodiscard]] static BSWin32SystemUtility* GetSingleton()
		{
			using func_t = decltype(&BSWin32SystemUtility::GetSingleton);
			static REL::Relocation<func_t> func{ RELOCATION_ID(101821, 453511) };
			return func();
		}

		// members
		SteamCallback<GameOverlayActivated_t>              steamcallback_GameOverlayActivated;               // 128
		SteamCallback<FloatingGamepadTextInputDismissed_t> steamcallback_FloatingGamepadTextInputDismissed;  // 150 - added in 1.6.1130
		SteamCallback<GamepadTextInputDismissed_t>         steamcallback_GamepadTextInputDismissed;          // 178 - added in 1.6.1130
		SteamCallResult<EncryptedAppTicketResponse_t>      steamcallresult_EncryptedAppTicketResponse;       // 1A0
		VirtualKeyboardDoneCallback*                       virtualKeyboardDone;                              // 1D0 - added in 1.6.1130
		VirtualKeyboardCancelCallback*                     virtualKeyboardCancel;                            // 1D8 - added in 1.6.1130
		void*                                              virtualKeyboardUserParam;                         // 1E0 - added in 1.6.1130
		bool                                               steamAPIInitialized;                              // 1E8
		std::uint8_t                                       pad1E9;                                           // 1E9
		std::uint16_t                                      pad1EA;                                           // 1EA
		std::uint32_t                                      pad1EC;                                           // 1EC
		ISteamClient*                                      steamClient;                                      // 1F0 - added in 1.6.1130
		HSteamPipe                                         steamPipe;                                        // 1F8 - added in 1.6.1130
		std::uint32_t                                      pad1FC;                                           // 1FC
		ISteamUtils*                                       steamUtils;                                       // 200 - added in 1.6.1130
		bool                                               isRunningOnSteamDeck;                             // 208 - added in 1.6.1130
	};
	static_assert(sizeof(BSWin32SystemUtility) == 0x210);
}

#pragma once

#include "RE/B/BSTSingleton.h"

#include "REX/W32/BASE.h"

namespace REX::W32
{
	struct DIDEVICEOBJECTDATA;
	struct IDirectInput8A;
	struct IDirectInputDevice8A;
}

namespace RE
{
	class BSDirectInputManager : public BSTSingletonSDM<BSDirectInputManager>
	{
	public:
		static BSDirectInputManager* GetSingleton();

		REX::W32::IDirectInputDevice8A* CreateDeviceWithGUID(REX::W32::GUID* a_guid);
		void                            GetDeviceState(REX::W32::IDirectInputDevice8A* a_device, std::uint32_t a_size, void* a_outData);
		void                            GetDeviceData(REX::W32::IDirectInputDevice8A* a_device, std::uint32_t* a_dataSize, REX::W32::DIDEVICEOBJECTDATA** a_outData);
		void                            ReleaseDevice(REX::W32::IDirectInputDevice8A* a_device);

		// members
		std::uint32_t             pad00;        // 00
		REX::W32::IDirectInput8A* diInterface;  // 08
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSDirectInputManager) == 0x10);
}

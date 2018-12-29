#pragma once

#include "RE/BSMouseDevice.h"  // BSMouseDevice


namespace RE
{
	class BSWin32MouseDevice : public BSMouseDevice
	{
	public:
		enum class Mouse : UInt32
		{
			kLeftButton,
			kRightButton,
			kMiddleButton,
			kButton3,
			kButton4,
			kButton5,
			kButton6,
			kButton7,
			kWheelUp,
			kWheelDown
		};


		virtual ~BSWin32MouseDevice();					// 00

		// override (BSMouseDevice)
		virtual void	Initialize() override;			// 01
		virtual	void	Process(float a_unk1) override;	// 02


		// members
		UInt64	unk78;	// 78
		UInt64	unk80;	// 80
		UInt64	unk88;	// 88
		UInt64	unk90;	// 90
		UInt64	unk98;	// 98
		UInt64	unkA0;	// A0
		UInt64	unkA8;	// A8
		UInt64	unkB0;	// B0
	};
	STATIC_ASSERT(sizeof(BSWin32MouseDevice) == 0xB8);
}

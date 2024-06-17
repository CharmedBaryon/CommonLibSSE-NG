#pragma once

#include "RE/G/GASFunctionObject.h"
#include "RE/G/GFxFunctionHandler.h"
#include "RE/G/GPtr.h"

namespace RE
{
	class GASUserDefinedFunctionObject : public GASFunctionObject
	{
	public:
		// override (GASFunctionObject)
		void Unk_01(void) override;  // 01

		~GASUserDefinedFunctionObject() override;  // 02

		void Unk_09(void) override;  // 09
		void Unk_0A(void) override;  // 0A
		void Unk_0B(void) override;  // 0B - { return handler == nullptr; }
		void Unk_0C(void) override;  // 0C - { return 0; }
		void Unk_10(void) override;  // 10 - { return -1; }

		// members
		GPtr<GFxFunctionHandler> handler;   // 68
		void*                    userData;  // 70
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(GASUserDefinedFunctionObject) == 0x78);
}

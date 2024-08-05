#pragma once

#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class NiNode;
	class Sky;

	class SkyObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_SkyObject;
		inline static constexpr auto VTABLE = VTABLE_SkyObject;

		virtual ~SkyObject();  // 00

		// add
		virtual NiNode* GetRoot();                         // 01 - { return root.get(); }
		virtual void    Init(NiNode* a_root);              // 02
		virtual void    Update(Sky* a_sky, float a_arg2);  // 03 - { return; }

		// members
		NiPointer<NiNode> root;  // 10
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(SkyObject) == 0x10);
}

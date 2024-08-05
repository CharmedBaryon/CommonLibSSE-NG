#pragma once

#include "RE/B/BSBloodSplatterShaderProperty.h"
#include "RE/B/BSTSingleton.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class NiCamera;
	class NiNode;
	class NiSourceTexture;

	class ScreenSplatter : public BSTSingletonSDM<ScreenSplatter>
	{
	public:
		static ScreenSplatter* GetSingleton()
		{
			REL::Relocation<ScreenSplatter**> singleton{ RELOCATION_ID(514512, 400672) };
			return *singleton;
		}

		void Clear()
		{
			using func_t = decltype(&ScreenSplatter::Clear);
			static REL::Relocation<func_t> func{ RELOCATION_ID(16175, 16407) };
			return func(this);
		}

		// members
		std::uint8_t               pad01;                                            // 01
		std::uint16_t              pad02;                                            // 02
		std::uint32_t              pad04;                                            // 04
		NiPointer<NiNode>          root;                                             // 08
		NiPointer<NiCamera>        camera;                                           // 10
		float                      wRadius;                                          // 18
		float                      hRadius;                                          // 1C
		bool                       enabled;                                          // 20
		bool                       pad21;                                            // 21
		std::uint16_t              pad22;                                            // 22
		std::uint32_t              uiCount;                                          // 24
		NiPointer<NiSourceTexture> textures[BSBloodSplatterShaderProperty::kTotal];  // 28
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ScreenSplatter) == 0x40);
}

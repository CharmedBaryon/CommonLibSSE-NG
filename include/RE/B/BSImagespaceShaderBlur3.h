#pragma once

#include "RE/B/BSImagespaceShader.h"

namespace RE
{
	class BSImagespaceShaderBlur3 : public BSImagespaceShader
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSImagespaceShaderBlur3;
		inline static constexpr auto VTABLE = VTABLE_BSImagespaceShaderBlur3;

		~BSImagespaceShaderBlur3() override;  // 00

		// override (BSImagespaceShader)
#if !defined(SKYRIM_CROSS_VR)
		void GetShaderMacros(ShaderMacro* a_macros) override;  // 0D, VR 0E
#endif

#ifdef SKYRIM_CROSS_VR
		void GetShaderMacros(ShaderMacro* a_macros)
		{
			REL::RelocateVirtual<decltype(&BSImagespaceShaderBlur3::GetShaderMacros)>(0x0D, 0x0E, this, a_macros);
		}
#endif
	};
	static_assert(sizeof(BSImagespaceShaderBlur3) == 0x1A8);
}

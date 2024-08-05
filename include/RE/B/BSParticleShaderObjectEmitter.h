#pragma once

#include "RE/B/BSParticleShaderEmitter.h"

namespace RE
{
	class BSParticleShaderObjectEmitter : public BSParticleShaderEmitter
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSParticleShaderObjectEmitter;
		inline static constexpr auto VTABLE = VTABLE_BSParticleShaderObjectEmitter;

		~BSParticleShaderObjectEmitter() override;  // 00

		// override (BSParticleShaderEmitter)
		NiAVObject* GetBoundsObject() override;  // 02

		// add
		virtual void          CollectObjects(NiAVObject* a_targetRoot, std::uint16_t a_depthLimit, std::uint16_t a_arg3, bool a_nodeFilterFunc(const BSFixedString&)) = 0;  // 03
		virtual std::uint32_t GetObjectCount() = 0;                                                                                                                         // 05
		virtual NiAVObject*   GetObjectAt(std::size_t a_index) = 0;                                                                                                         // 06

		// members
		NiPointer<NiAVObject> targetRoot;    // ED0
		NiAVObject*           boundsObject;  // ED8
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSParticleShaderObjectEmitter) == 0xEE0);
}

#pragma once

#include "RE/B/BSTHashMap.h"
#include "RE/N/NiAVObjectPalette.h"

namespace RE
{
	class NiDefaultAVObjectPalette : public NiAVObjectPalette
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiDefaultAVObjectPalette;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiDefaultAVObjectPalette;
		inline static constexpr auto VTABLE = VTABLE_NiDefaultAVObjectPalette;

		~NiDefaultAVObjectPalette() override;  // 00

		// override (NiAVObjectPalette)
		const NiRTTI* GetRTTI() const override;                                            // 02
		NiObject*     CreateClone([[maybe_unused]] NiCloningProcess& a_cloning) override;  // 17
		void          LoadBinary([[maybe_unused]] NiStream& a_stream) override;            // 18
		void          LinkObject([[maybe_unused]] NiStream& a_stream) override;            // 19
		bool          RegisterStreamables(NiStream& a_stream) override;                    // 1A
		void          SaveBinary([[maybe_unused]] NiStream& a_stream) override;            // 1B
		bool          IsEqual(NiObject* a_object) override;                                // 1C
		void          ProcessClone(NiCloningProcess& a_cloning) override;                  // 1D
		NiAVObject*   GetAVObject(BSFixedString& a_name) override;                         // 25
		void          SetAVObject(BSFixedString& a_name, NiAVObject* a_object) override;   // 26
		void          ResetAndFillFromScenegraph() override;                               // 27

		// add
		virtual void        SetScene(NiAVObject* a_scene) { scene = a_scene; }  // 28
		virtual NiAVObject* GetScene() { return scene; };                       // 29

		// members
		BSTHashMap<BSFixedString, NiAVObject*> paletteMap;  // 10
		NiAVObject*                            scene;       // 40
	};
	static_assert(sizeof(NiDefaultAVObjectPalette) == 0x48);
}
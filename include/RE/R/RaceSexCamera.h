#pragma once

#	include "RE/T/TESCamera.h"

namespace RE
{
	class RaceSexCamera : public TESCamera
	{
	public:
		inline static constexpr auto RTTI = RTTI_RaceSexCamera;
		inline static constexpr auto VTABLE = VTABLE_RaceSexCamera;

		~RaceSexCamera() override;  // 00

		// override (TESCamera)
		void SetCameraRoot(NiPointer<NiNode> a_root) override;  // 01
		void Update() override;                                 // 02

		// members
		std::uint64_t unk38;  // 38
		std::uint64_t unk40;  // 40
		std::uint64_t unk48;  // 48
		std::uint64_t unk50;  // 50
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(RaceSexCamera) == 0x58);
}


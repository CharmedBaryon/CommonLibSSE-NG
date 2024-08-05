#pragma once

namespace RE
{
	class IPostAnimationChannelUpdateFunctor;
	class NiPoint3;
	class TESObjectREFR;

	struct BSAnimationUpdateData
	{
	public:
		// members
		float                               deltaTime{ 0.0f };               // 00
		uint32_t                            pad04;                           // 04
		void*                               unkFunctionPtr{ nullptr };       // 08
		TESObjectREFR*                      refr{ nullptr };                 // 10
		NiPoint3*                           optionalEyePosition{ nullptr };  // 18
		IPostAnimationChannelUpdateFunctor* updateFunctor{ nullptr };        // 20
		uint16_t                            flags;                           // 28
		bool                                unk2A;                           // 2A
		bool                                unk2B;                           // 2B
		bool                                unk2C;                           // 2C
		bool                                unk2D;                           // 2D
		bool                                unk2E;                           // 2E
		bool                                unk2F;                           // 2F
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSAnimationUpdateData) == 0x30);
}

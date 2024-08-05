#pragma once

namespace RE
{
	class IPostAnimationChannelUpdateFunctor
	{
	public:
		inline static constexpr auto RTTI = RTTI_IPostAnimationChannelUpdateFunctor;
		inline static constexpr auto VTABLE = VTABLE_IPostAnimationChannelUpdateFunctor;

		virtual ~IPostAnimationChannelUpdateFunctor();  // 00

		// add
		virtual void Unk_01(void);  // 01
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(IPostAnimationChannelUpdateFunctor) == 0x8);
}

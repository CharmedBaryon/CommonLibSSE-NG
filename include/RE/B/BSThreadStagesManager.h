#pragma once

namespace RE
{
	class BSThreadStages : BSStaticArray<REX::W32::HANDLE>
	{};
	static_assert(sizeof(BSThreadStages) == 0x10);

	class BSThreadStagesManager :
		public BSTSingletonSDM<BSThreadStagesManager>,  // 00
		public BSStaticArray<BSThreadStages*>           // 08
	{
	public:
		static BSThreadStagesManager* GetSingleton()
		{
			static REL::Relocation<BSThreadStagesManager**> singleton{ RELOCATION_ID(516849, 403108) };
			return *singleton;
		}
	};
	static_assert(sizeof(BSThreadStagesManager) == 0x18);
}
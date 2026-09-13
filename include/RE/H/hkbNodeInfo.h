#pragma once

namespace RE
{
	class hkbBehaviorGraph;
	class hkbNode;

	struct hkbNodeInfo
	{
		void*             unk00;         // 00
		int64_t           unk08;         // 08
		int64_t           unk10;         // 10
		void*             unk18;         // 18
		char              unk20[48];     // 20
		hkbNode*          nodeTemplate;  // 50
		hkbNode*          nodeClone;     // 58
		hkbBehaviorGraph* behavior;      // 60
		int64_t           unk68;         // 68
		int64_t           unk70;         // 70
		int64_t           unk78;         // 78
		int64_t           unk80;         // 80
		bool              unk88;         // 88
	};
	static_assert(sizeof(hkbNodeInfo) == 0x90);

	using NodeList = hkArray<hkbNodeInfo>;
}

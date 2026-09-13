#pragma once

namespace RE
{
	class BSSoundMessage;

	class SoundMessageList
	{
	public:
		// members
		BSSoundMessage* head;  // 00
		BSSoundMessage* tail;  // 08
	};
	static_assert(sizeof(SoundMessageList) == 0x10);
}

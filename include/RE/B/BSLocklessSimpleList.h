#pragma once

namespace RE
{
	// Skyrim VR only (SE/AE use BSSimpleList for the same data). The head is a shared_ptr to a
	// sentinel node whose `next` is the first element; nodes are make_shared blocks and removal
	// only sets `removed`. The engine reads and CAS-stores every `next` under MSVC's global
	// shared_ptr spin lock, which a plugin cannot reliably take (its own CRT copy is a different
	// lock), so this is a layout description only: walk it with MagicTarget::VisitActiveEffects,
	// and do not copy or modify the links.
	template <class T>
	class BSLocklessSimpleList
	{
	public:
		struct Node
		{
			T                     item;      // 00
			std::shared_ptr<Node> next;      // 08
			bool                  removed;   // 18
			std::uint8_t          pad19[7];  // 19
		};
		static_assert(sizeof(Node) == 0x20);

		// members
		std::shared_ptr<Node> head;  // 00 - sentinel
	};
	static_assert(sizeof(BSLocklessSimpleList<void*>) == 0x10);
}

#pragma once

#include "RE/I/IOTask.h"

namespace RE
{
	// Adds no new POD fields beyond IOTask's own tail --
	// sizeof(QueuedFile) == sizeof(IOTask) in SE/AE/VR alike.
	class QueuedFile : public IOTask
	{
	public:
		inline static constexpr auto RTTI = RTTI_QueuedFile;
		inline static constexpr auto VTABLE = VTABLE_QueuedFile;

		~QueuedFile() override;  // 00

		// add (trivial stubs, shared/folded with unrelated classes' vtables)
		virtual void Unk_09() { return; }  // 09
		virtual void Unk_10() { return; }  // 10
		virtual void Unk_11() { return; }  // 11
	};
}

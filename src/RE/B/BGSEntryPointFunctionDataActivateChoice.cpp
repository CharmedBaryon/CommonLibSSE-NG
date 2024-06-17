#include "RE/B/BGSEntryPointFunctionDataActivateChoice.h"

namespace RE
{
	bool BGSEntryPointFunctionDataActivateChoice::ReplacesDefault() const
	{
		return flags.all(Flag::kReplaceDefault);
	}

	bool BGSEntryPointFunctionDataActivateChoice::RunsImmediately() const
	{
		return flags.all(Flag::kRunImmediately);
	}
}

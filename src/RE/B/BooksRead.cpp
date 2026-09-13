#include "RE/B/BooksRead.h"

namespace RE
{
	BSTEventSource<BooksRead::Event>* BooksRead::GetEventSource()
	{
		using func_t = decltype(&BooksRead::GetEventSource);
		static REL::Relocation<func_t> func{ RELOCATION_ID(17470, 17865) };
		return func();
	}
}

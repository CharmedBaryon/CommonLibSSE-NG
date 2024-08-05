#pragma once

#include "RE/N/NiRefObject.h"

namespace RE
{
	class BGSLoadGameBuffer;
	class BGSSaveGameBuffer;

	class CombatObject : public NiRefObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatObject;
		inline static constexpr auto VTABLE = VTABLE_CombatObject;

		~CombatObject() override;  // 00

		// add
		virtual std::uint32_t GetObjectType() = 0;                 // 02
		virtual void          SaveGame(BGSSaveGameBuffer* a_buf);  // 03 - { return }
		virtual void          LoadGame(BGSLoadGameBuffer* a_buf);  // 04 - { return }
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(CombatObject) == 0x10);
}

#pragma once

#include "RE/B/BGSDestructibleObjectForm.h"
#include "RE/B/BGSKeywordForm.h"
#include "RE/B/BGSMessageIcon.h"
#include "RE/B/BGSPickupPutdownSounds.h"
#include "RE/F/FormTypes.h"
#include "RE/T/TESBoundObject.h"
#include "RE/T/TESDescription.h"
#include "RE/T/TESFullName.h"
#include "RE/T/TESIcon.h"
#include "RE/T/TESModelTextureSwap.h"
#include "RE/T/TESValueForm.h"
#include "RE/T/TESWeightForm.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	struct AMMO_DATA  // DATA
	{
	public:
		enum class Flag
		{
			kNone = 0,
			kIgnoresNormalWeaponResistance = 1 << 0,
			kNonPlayable = 1 << 1,
			kNonBolt = 1 << 2
		};

		// members
		BGSProjectile*                   projectile;  // 00
		REX::EnumSet<Flag, std::uint8_t> flags;       // 08
		std::uint8_t                     pa09;        // 09
		std::uint16_t                    pa0A;        // 0A
		float                            damage;      // 0C
	};
	static_assert(sizeof(AMMO_DATA) == 0x10);

	class TESAmmo :
		public TESBoundObject,       // 000
		public TESFullName,          // 030
		public TESModelTextureSwap,  // 040
		public TESIcon,              // 078
		public BGSMessageIcon,       // 088
		public TESValueForm          // 0A0
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		,
		public TESWeightForm,              // 0B0
		public BGSDestructibleObjectForm,  // 0C0
		public BGSPickupPutdownSounds,     // 0D0
		public TESDescription,             // 0E8
		public BGSKeywordForm              // 0F8
#elif defined(EXCLUSIVE_SKYRIM_VR)
		,
		public BGSDestructibleObjectForm,  // 0B0
		public BGSPickupPutdownSounds,     // 0C0
		public TESDescription,             // 0D8
		public BGSKeywordForm              // 0E8
#endif
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESAmmo;
		inline static constexpr auto VTABLE = VTABLE_TESAmmo;
		inline static constexpr auto FORMTYPE = FormType::Ammo;

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kNonPlayable = 1 << 2,
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                 \
	AMMO_DATA     data;      /* 00 - DATA */ \
	BSFixedString shortDesc; /* 10 - ONAM */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x18);

		~TESAmmo() override;  // 00

		// override (TESBoundObject)
		void        InitializeData() override;                                           // 04
		bool        Load(TESFile* a_mod) override;                                       // 06
		void        SaveGame(BGSSaveFormBuffer* a_buf) override;                         // 0E
		void        LoadGame(BGSLoadFormBuffer* a_buf) override;                         // 0F
		void        InitItemImpl() override;                                             // 13
		bool        GetPlayable() const override;                                        // 19 - { return ~((data.flags >> 1) & 1); }
		NiAVObject* Clone3D(TESObjectREFR* a_ref, bool a_arg3) override;                 // 40
		void        HandleRemoveItemFromContainer(TESObjectREFR* a_container) override;  // 4E

#if defined(EXCLUSIVE_SKYRIM_FLAT)
		// override (BGSKeywordForm)
		[[nodiscard]] BGSKeyword* GetDefaultKeyword() const override;  // 05
#endif

		bool IgnoresNormalWeaponResistance();
		bool IsBolt();

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x110, 0x100);

		// Cast accessors for runtime-conditional base classes (see inheritance above)
		RUNTIME_CAST_ACCESSOR(BGSDestructibleObjectForm, AsDestructibleObjectForm, 0xC0, 0xB0);
		RUNTIME_CAST_ACCESSOR(BGSPickupPutdownSounds, AsPickupPutdownSoundsForm, 0xD0, 0xC0);
		RUNTIME_CAST_ACCESSOR(TESDescription, AsDescriptionForm, 0xE8, 0xD8);
		RUNTIME_CAST_ACCESSOR(BGSKeywordForm, AsKeywordForm, 0xF8, 0xE8);

		// members
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		RUNTIME_DATA_CONTENT;  // 110
#elif defined(EXCLUSIVE_SKYRIM_VR)
		RUNTIME_DATA_CONTENT;              // VR 100
#endif
	};
	STATIC_ASSERT_SIZE(TESAmmo, 0x128, 0x118);
}
#undef RUNTIME_DATA_CONTENT

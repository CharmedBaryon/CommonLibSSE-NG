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
		BGSProjectile*                       projectile;  // 00
		stl::enumeration<Flag, std::uint8_t> flags;       // 08
		std::uint8_t                         pa09;        // 09
		std::uint16_t                        pa0A;        // 0A
		float                                damage;      // 0C
	};
	static_assert(sizeof(AMMO_DATA) == 0x10);

	class TESAmmo :
		public TESBoundObject,             // 000
		public TESFullName,                // 030
		public TESModelTextureSwap,        // 040
		public TESIcon,                    // 078
		public BGSMessageIcon,             // 088
		public TESValueForm,               // 0A0
#ifndef ENABLE_SKYRIM_VR
		public TESWeightForm,              // 0B0
#endif
		public BGSDestructibleObjectForm,  // 0C0, 0B0
		public BGSPickupPutdownSounds,     // 0D0, 0C0,
		public TESDescription,             // 0E8, 0D8
		public BGSKeywordForm              // 0F8, 0E8
	{
	public:
		inline static auto           RTTI = RTTI_TESAmmo;
		inline static auto           VTABLE = VTABLE_TESAmmo;
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

		[[nodiscard]] inline float GetWeight() const noexcept {
			return REL::Module::get().IsVR() ? 0.0f : REL::RelocateMember<float>(this, 0xB8, 0);
		}

		// override (BGSKeywordForm)
		[[nodiscard]] BGSKeyword* GetDefaultKeyword() const override;  // 05

		bool IgnoresNormalWeaponResistance();
		bool IsBolt();

		// members
		AMMO_DATA     data;       // 110 - DATA
		BSFixedString shortDesc;  // 120 - ONAM
	};
#ifndef ENABLE_SKYRIM_VR
	static_assert(sizeof(TESAmmo) == 0x128);
#else
	static_assert(sizeof(TESAmmo) == 0x118);
#endif
}

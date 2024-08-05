#pragma once

#include "RE/F/FormTypes.h"
#include "RE/M/MagicItem.h"
#include "RE/M/MagicSystem.h"

namespace RE
{
	class EnchantmentItem : public MagicItem
	{
	public:
		inline static constexpr auto RTTI = RTTI_EnchantmentItem;
		inline static constexpr auto VTABLE = VTABLE_EnchantmentItem;
		inline static constexpr auto FORMTYPE = FormType::Enchantment;

		enum class EnchantmentFlag
		{
			kNone = 0,
			kCostOverride = 1 << 0,
			kFoodItem = 1 << 1,
			kExtendDuration = 1 << 3
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		class Data  // ENIT
		{
		public:
			// members
			std::int32_t                                     costOverride;      // 00
			stl::enumeration<EnchantmentFlag, std::uint32_t> flags;             // 04
			MagicSystem::CastingType                         castingType;       // 08
			std::int32_t                                     chargeOverride;    // 0C
			MagicSystem::Delivery                            delivery;          // 10
			MagicSystem::SpellType                           spellType;         // 14
			float                                            chargeTime;        // 18
			std::uint32_t                                    pad1C;             // 1C
			EnchantmentItem*                                 baseEnchantment;   // 20
			BGSListForm*                                     wornRestrictions;  // 28
		};
		static_assert(sizeof(Data) == 0x30);

		~EnchantmentItem() override;  // 00

		// override (MagicItem)
		void                                   InitializeData() override;                                 // 04
		void                                   ClearData() override;                                      // 05
		void                                   InitItemImpl() override;                                   // 13
		[[nodiscard]] MagicSystem::SpellType   GetSpellType() const override;                             // 53 - { return data.spellType; }
		void                                   SetCastingType(MagicSystem::CastingType a_type) override;  // 54 - { data.castingType = a_type; }
		[[nodiscard]] MagicSystem::CastingType GetCastingType() const override;                           // 55 - { return data.castingType; }
		void                                   SetDelivery(MagicSystem::Delivery a_type) override;        // 56 - { if (Unk_58()) { data.delivery = a_type; } }
		[[nodiscard]] MagicSystem::Delivery    GetDelivery() const override;                              // 57 - { return data.delivery; }
		[[nodiscard]] float                    GetChargeTime() const override;                            // 64
		[[nodiscard]] ActorValue               GetAssociatedSkill() const override;                       // 66 - { return ActorValue::kEnchanting; }
		[[nodiscard]] std::uint32_t            GetChunkID() override;                                     // 68 - { return 'ENIT'; }
		void                                   CopyMagicItemData(MagicItem* a_src) override;              // 69
		[[nodiscard]] const MagicItem::Data*   GetData1() const override;                                 // 6C - { return &data; }
		[[nodiscard]] MagicItem::Data*         GetData2() override;                                       // 6D - { return &data; }
		[[nodiscard]] std::uint32_t            GetDataSize() const override;                              // 6E - { return 0x30; }
		void                                   InitFromChunk(TESFile* a_mod) override;                    // 6F
		void                                   InitChunk() override;                                      // 70

		// members
		Data data;  // 90 - ENIT
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(EnchantmentItem) == 0xC0);
}

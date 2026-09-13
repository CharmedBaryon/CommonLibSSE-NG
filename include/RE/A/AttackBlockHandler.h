#pragma once

#include "REL/RuntimeDataAccessors.h"

#include "RE/B/BSTEvent.h"
#include "RE/I/InputEvent.h"

#include "RE/H/HeldStateHandler.h"

namespace RE
{
	struct AttackBlockHandler : public HeldStateHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_AttackBlockHandler;
		inline static constexpr auto VTABLE = VTABLE_AttackBlockHandler;

		enum class AttackType : std::uint8_t
		{
			kRight = 0,
			kLeft = 1,
			kDual = 2
		};

		~AttackBlockHandler() override;  // 00

		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;  // 01
#ifdef EXCLUSIVE_SKYRIM_VR
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_data) override;  // 04, 06 (AE 1.7.99)
		void UpdateHeldStateActive(const ButtonEvent* a_event) override;                // 05, 07 (AE 1.7.99)
		void SetHeldStateActive(bool a_flag) override;                                  // 06, 08 (AE 1.7.99)
#endif

#ifdef ENABLE_SKYRIM_AE
		struct RUNTIME_DATA
		{
			std::uint32_t heldTimeMs;                  // 18, 58
			std::uint32_t unk1C;                       // 1C, 5C
			BSFixedString controlID;                   // 20, 60
			AttackType    attackType;                  // 28, 68
			std::uint8_t  pad29;                       // 29, 69
			std::uint16_t pad2A;                       // 2A, 6A
			std::uint8_t  attackCount;                 // 2C, 6C
			float         initialPowerAttackDelay;     // 30, 70
			std::uint32_t pad34;                       // 34, 74
			float         subsequentPowerAttackDelay;  // 38, 78
			bool          ignore;                      // 3C, 7C
			bool          unk41;                       // 3D, 7D
			bool          heldLeft;                    // 3E, 7E
			bool          heldRight;                   // 3F, 7F
			std::uint32_t unk44;                       // 40, 80
		};

		RUNTIME_DATA_ACCESSOR_VERSIONED(RUNTIME_DATA, SKSE::RUNTIME_SSE_1_7_99, 0x18, 0x58);

	private:
		std::uint8_t _pad18[0xA8];  // 18
#else
	public:
		// members
		std::uint32_t heldTimeMs;                  // 18
		std::uint32_t unk1C;                       // 1C
		BSFixedString controlID;                   // 20
		AttackType    attackType;                  // 28
		std::uint8_t  pad29;                       // 29
		std::uint16_t pad2A;                       // 2A
		std::uint8_t  attackCount;                 // 2C
		float         initialPowerAttackDelay;     // 30
		std::uint32_t pad34;                       // 34
		float         subsequentPowerAttackDelay;  // 38
		bool          ignore;                      // 40
		bool          unk41;                       // 41
		bool          heldLeft;                    // 42
		bool          heldRight;                   // 43
		std::uint32_t unk44;                       // 44
#endif
	};
	STATIC_ASSERT_SIZE(AttackBlockHandler, 0x48, 0xC0, 0x60, SIZE_UNDEFINED, 0xC0);
}

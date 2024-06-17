#pragma once

namespace RE
{
	class TESObjectREFR;

	struct BGSEntryPointFunction
	{
		struct ENTRY_POINT_FUNCTIONS
		{
			enum ENTRY_POINT_FUNCTION
			{
				kNullFunction = 0,
				kSetValue = 1,
				kAddValue = 2,
				kMultiplyValue = 3,
				kAddRangeToValue = 4,
				kAddActorValueMult = 5,
				kAbsoluteValue = 6,
				kNegativeAbsoluteValue = 7,
				kAddLeveledList = 8,
				kAddActivateChoice = 9,
				kSelectSpell = 10,
				kSelectText = 11,
				kSetToActorValueMult = 12,
				kMultiplyActorValueMult = 13,
				kMultiplyOnePlusActorValueMult = 14,
				kSetText = 15,

				kTotal
			};
		};
		using ENTRY_POINT_FUNCTION = ENTRY_POINT_FUNCTIONS::ENTRY_POINT_FUNCTION;

		struct ENTRY_POINT_FUNCTION_TYPES
		{
			enum ENTRY_POINT_FUNCTION_TYPE
			{
				kValue = 0,
				kAddLeveledList = 1,
				kAddActivateChoice = 2,
				kNull = 3,
				kSelectSpell = 4,
				kSelectText = 5,
				kSetText = 6,

				kTotal
			};
		};
		using ENTRY_POINT_FUNCTION_TYPE = ENTRY_POINT_FUNCTION_TYPES::ENTRY_POINT_FUNCTION_TYPE;

		struct EntryPointFunction
		{
		public:
			using Function_t = void(TESObjectREFR*, ENTRY_POINT_FUNCTION_TYPE, std::uint8_t, void**, void*);

			// members
			const char*               name;      // 00
			ENTRY_POINT_FUNCTION_TYPE type;      // 08
			std::uint32_t             pad0C;     // 0C
			Function_t*               function;  // 10
		};
		static_assert(sizeof(EntryPointFunction) == 0x18);

		static std::uint32_t GetArgumentCount(ENTRY_POINT_FUNCTION_TYPE a_entryPointFunctionType)
		{
			if (a_entryPointFunctionType < ENTRY_POINT_FUNCTION_TYPE::kTotal) {
				REL::Relocation<std::uint32_t*> entryPointFunctionTypeArgumentCount{ RELOCATION_ID(369210, 0) };
				return entryPointFunctionTypeArgumentCount.get()[a_entryPointFunctionType];
			}

			return 0;
		}

		static EntryPointFunction* GetEntryPointFunction(ENTRY_POINT_FUNCTION a_entryPointFunction)
		{
			if (a_entryPointFunction < ENTRY_POINT_FUNCTION::kTotal) {
				REL::Relocation<EntryPointFunction*> entryPointFunctions{ RELOCATION_ID(369178, 0) };
				return &entryPointFunctions.get()[a_entryPointFunction];
			}

			return nullptr;
		}

	private:
		KEEP_FOR_RE()
	};
}

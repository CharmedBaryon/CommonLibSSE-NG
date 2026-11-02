#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTHashMap.h"
#include "RE/L/LinkerProcessor.h"
#include "RE/T/TypeInfo.h"
#include "RE/V/VirtualMachine.h"

namespace RE
{
	namespace BSScript
	{
		namespace ByteCode
		{
#pragma pack(push, 4)
			struct Argument
			{
				enum class Type : std::uint32_t
				{
					kNone,
					kIdentifier,  // Identifier of object variables (Forms, Actors, etc.)
					kString,
					kInt,
					kFloat,
					kBool,
					kLocalVarIdx,   // index of local variable in function
					kMemberVarIdx,  // index of member variable in script instance
				};
				static_assert(sizeof(Type) == 0x4);

				union Value
				{
					int           i;
					float         f;
					bool          b;
					std::uint32_t idx;
					BSFixedString string;

					~Value() {};
				};
				static_assert(sizeof(Value) == 0x8);

				~Argument()
				{
					if (type == Type::kIdentifier || type == Type::kString) {
						value.string.~BSFixedString();
					}
				};
				// members
				Type  type;   // 00
				Value value;  // 04
			};
			static_assert(sizeof(Argument) == 0xC);
#pragma pack(pop)

			struct InstructionDefinition
			{
			public:
				// members
				std::uint64_t unk00;         // 00
				const char*   opCodeName;    // 08 - ex: iadd
				const char*   opCodeArgs;    // 10 - ex: SII
				std::byte     majorVersion;  // 18 - Papyrus major version when opCode was made
				std::byte     minorVersion;  // 19 - Papyrus minor version when opCode was made
				std::uint16_t pad1A;         // 1A
				std::uint32_t pad1C;         // 1C
			};
			static_assert(sizeof(InstructionDefinition) == 0x20);
		}
		namespace UnlinkedTypes
		{
			class ConvertTypeFunctor
			{
			public:
				inline static constexpr auto RTTI = RTTI_BSScript__UnlinkedTypes__Function__ConvertTypeFunctor;
				inline static constexpr auto VTABLE = VTABLE_BSScript__UnlinkedTypes__Function__ConvertTypeFunctor;

				virtual ~ConvertTypeFunctor();  // 00

				virtual bool ConvertVariableType(BSFixedString* a_typeAsString, TypeInfo& a_typeOut) = 0;  // 01
			};
			static_assert(sizeof(ConvertTypeFunctor) == 0x8);

			class LinkerConvertTypeFunctor : public ConvertTypeFunctor
			{
			public:
				~LinkerConvertTypeFunctor() override;  // 00

				bool ConvertVariableType(BSFixedString* a_typeAsString, TypeInfo& a_typeOut) override;  // 01 - This just jumps to LinkerProcessor::ConvertVariableType

				// members
				LinkerProcessor* linker;  // 08
			};
			static_assert(sizeof(LinkerConvertTypeFunctor) == 0x10);

			class VMTypeResolveFunctor : public ConvertTypeFunctor
			{
			public:
				inline static constexpr auto RTTI = RTTI_BSScript____VMTypeResolveFunctor;
				inline static constexpr auto VTABLE = VTABLE_BSScript____VMTypeResolveFunctor;
				~VMTypeResolveFunctor() override;  // 00

				bool ConvertVariableType(BSFixedString* a_typeAsString, TypeInfo& a_typeOut) override;  // 01
				// members
				Internal::VirtualMachine* vm;  // 08
			};
			static_assert(sizeof(VMTypeResolveFunctor) == 0x10);

			class InstructionStream
			{
			public:
				// members
				ScrapHeap*    threadScrapHeap;   // 00
				std::uint32_t functionCodeSize;  // 08
				std::uint32_t unk0C;             // 0C
				std::uint32_t pad10;             // 10
				std::uint32_t unk14;             // 14
				void*         unk18;             // 18 - Holds arguments
				void*         unk20;             // 20
				void*         unk28;             // 28
				std::uint64_t unk30;             // 30
				void*         unk38;             // 38
				std::uint64_t unk40;             // 40
			};
			static_assert(sizeof(InstructionStream) == 0x48);

			class Function
			{
			public:
				// members
				BSFixedString               returnTypeName;      // 00
				BSFixedString               docString;           // 08
				bool                        isNative;            // 10
				bool                        isGlobal;            // 11
				std::uint16_t               pad12;               // 12
				std::uint32_t               isPropertyFunction;  // 14
				std::uint32_t               userFlags;           // 18
				BSScrapArray<BSFixedString> paramNameArray;      // 20 - index i holds the name of the parameter
				BSScrapArray<BSFixedString> paramTypeArray;      // 40 - index i holds the type of said parameter from above
				BSScrapArray<BSFixedString> localNameArray;      // 60 - index i holds the name of the local var
				BSScrapArray<BSFixedString> localTypeArray;      // 80 - index i holds the type of said local var from above
				InstructionStream           instructionStream;   // A0
			};
			static_assert(sizeof(Function) == 0xE8);

			struct FunctionDebugInfo
			{
			public:
				// members
				std::uint32_t               functionType;            // 00
				BSFixedString               className;               // 08
				BSFixedString               stateName;               // 10
				BSFixedString               functionName;            // 18
				BSScrapArray<std::uint16_t> instructionLineNumbers;  // 20
			};
			static_assert(sizeof(FunctionDebugInfo) == 0x40);

			struct Property
			{
			public:
				// members
				std::uint32_t flags;         // 00
				std::uint32_t pad04;         // 04
				BSFixedString typeName;      // 08
				Function*     readHandler;   // 10 - get() function for the property
				Function*     writeHandler;  // 18 - set() function for the property
				BSFixedString autoVarName;   // 20
				BSFixedString docString;     // 28 - Requires loadDocStrings in CompiledScriptLoader to be true
				std::uint32_t userFlags;     // 30
				std::uint32_t pad34;         // 34
			};
			static_assert(sizeof(Property) == 0x38);

			// Usage: Create an object with Create(), then pass to CompiledScriptLoader::GetClass() to fill it with information of a script class
			// See: https://en.uesp.net/wiki/Skyrim_Mod:Compiled_Script_File_Format
			// Note: This will only grab the raw unlinked data from the script, the game won't use the object when called like this
			class Object
			{
				struct VariableData
				{
				public:
					// members
					BSFixedString typeName;  // 00
					std::uint64_t flags;     // 08
				};
				static_assert(sizeof(VariableData) == 0x10);

			public:
				~Object();

				static Object* Create();

				TES_HEAP_REDEFINE_NEW();

				// members
				BSFixedString                                                              fileName;               // 00
				std::uint64_t                                                              compilationTime;        // 08
				BSFixedString                                                              userName;               // 10
				BSFixedString                                                              computerName;           // 18
				std::byte                                                                  loadDebugInformation;   // 20 - is set to loadDebugInfo from CompiledScriptLoader
				std::uint64_t                                                              modificationTime;       // 28
				RE::BSScrapArray<FunctionDebugInfo*>                                       functionDebugInfoList;  // 30 - requires loadDebugInfo in CompiledScriptLoader to be true
				BSTHashMap<BSFixedString, std::byte>                                       userFlagMap;            // 50
				BSFixedString                                                              className;              // 80
				BSFixedString                                                              parentClassName;        // 88
				BSFixedString                                                              docString;              // 90 - requires loadDocStrings in CompiledScriptLoader to be true
				std::uint32_t                                                              userFlags;              // 98
				std::uint32_t                                                              pad_9C;                 // 9C
				BSTScrapHashMap<BSFixedString, VariableData>                               variables;              // A0
				BSTScrapHashMap<BSFixedString, Property*>                                  properties;             // D0
				BSTScrapHashMap<BSFixedString, Function*>                                  staticFunctions;        // 100
				BSTScrapHashMap<BSFixedString, Function*>                                  memberFunctions;        // 130 - Only has functions in empty state
				BSTScrapHashMap<BSFixedString, BSTScrapHashMap<BSFixedString, Function*>*> stateMap;               // 160 - Does not include the empty state functions
				std::uint32_t                                                              totalFunctions;         // 190 - staticFunctions size + memberFunctions size + all the state function variants in stateMap
				std::uint32_t                                                              pad_194;                // 194
				BSTScrapHashMap<BSFixedString, ByteCode::Argument>                         initialVariableValues;  // 198
				BSFixedString                                                              autoStateName;          // 1C8 - Is blank if no auto state in script

			private:
				void    Dtor();
				Object* Ctor();
			};
			static_assert(sizeof(Object) == 0x1D0);
		}
	}
}

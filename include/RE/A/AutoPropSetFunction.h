#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/I/IFunction.h"
#include "RE/T/TypeInfo.h"

namespace RE
{
	namespace BSScript
	{
		class Variable;
		class ErrorLogger;
		class Stack;
		class StackFrame;
		namespace Internal
		{
			class VirtualMachine;

			class AutoPropSetFunction : public IFunction
			{
			public:
				inline static constexpr auto RTTI = RTTI_BSScript__Internal__AutoPropSetFunction;
				inline static constexpr auto VTABLE = VTABLE_BSScript__Internal__AutoPropSetFunction;

				AutoPropSetFunction(BSFixedString& a_parentName, BSFixedString& a_propertyName, TypeInfo& a_type, uint32_t a_autoVarIndex);

				~AutoPropSetFunction() override = default;  // 00

				// override (IFunction)
				const BSFixedString& GetName() const override;                                                                                                                 // 01
				const BSFixedString& GetObjectTypeName() const override;                                                                                                       // 02
				const BSFixedString& GetStateName() const override;                                                                                                            // 03
				TypeInfo             GetReturnType() const override;                                                                                                           // 04
				std::uint32_t        GetParamCount() const override;                                                                                                           // 05
				void                 GetParam(std::uint32_t a_idx, BSFixedString& a_nameOut, TypeInfo& a_typeOut) const override;                                              // 06
				std::uint32_t        GetStackFrameSize() const override;                                                                                                       // 07
				bool                 GetIsNative() const override;                                                                                                             // 08
				bool                 GetIsStatic() const override;                                                                                                             // 09
				bool                 GetIsEmpty() const override;                                                                                                              // 0A
				FunctionType         GetFunctionType() const override;                                                                                                         // 0B
				std::uint32_t        GetUserFlags() const override;                                                                                                            // 0C
				const BSFixedString& GetDocString() const override;                                                                                                            // 0D
				void                 InsertLocals(StackFrame* a_frame) override;                                                                                               // 0E
				CallResult           Call(const BSTSmartPointer<Stack>& a_stack, ErrorLogger* a_logger, Internal::VirtualMachine* a_vm, bool a_callingFromTasklets) override;  // 0F
				const BSFixedString& GetSourceFilename() const override;                                                                                                       // 10
				bool                 TranslateIPToLineNumber(std::uint32_t a_indexPtr, std::uint32_t& a_lineNumberOut) const override;                                         // 11
				bool                 GetVarNameForStackIndex(std::uint32_t a_idx, BSFixedString& a_nameOut) const override;                                                    // 12
				bool                 CanBeCalledFromTasklets() const override;                                                                                                 // 13
				void                 SetCallableFromTasklets(bool a_callable) override;                                                                                        // 14

				// members
				BSFixedString parentObjName;  // 10
				BSFixedString propertyName;   // 18
				TypeInfo      type;           // 20
				uint32_t      autoVarIndex;   // 28
			};

			static_assert(sizeof(AutoPropSetFunction) == 0x30);
		}
	}
}
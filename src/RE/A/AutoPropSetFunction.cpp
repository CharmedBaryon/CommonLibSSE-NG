#include "RE/A/AutoPropSetFunction.h"

#include "RE/E/ErrorLogger.h"
#include "RE/O/Object.h"
#include "RE/S/Stack.h"
#include "RE/S/StackFrame.h"

namespace RE
{
	namespace BSScript
	{
		namespace Internal
		{
			static auto EMPTY = BSFixedString();

			AutoPropSetFunction::AutoPropSetFunction(BSFixedString& a_parentName, BSFixedString& a_propertyName, TypeInfo& a_type, std::uint32_t a_autoVarIndex) :
				parentObjName(a_parentName), propertyName(a_propertyName), type(a_type), autoVarIndex(a_autoVarIndex) {}

			const BSFixedString& AutoPropSetFunction::GetName() const
			{
				return propertyName;
			}

			const BSFixedString& AutoPropSetFunction::GetObjectTypeName() const
			{
				return parentObjName;
			}

			const BSFixedString& AutoPropSetFunction::GetStateName() const
			{
				return EMPTY;
			}

			TypeInfo AutoPropSetFunction::GetReturnType() const
			{
				return {};
			};

			std::uint32_t AutoPropSetFunction::GetParamCount() const
			{
				return 1;
			}

			void AutoPropSetFunction::GetParam(std::uint32_t a_idx, BSFixedString& a_nameOut, TypeInfo& a_typeOut) const
			{
				if (a_idx == 0) {
					a_nameOut = "value";
					a_typeOut = type;
				} else {
					a_nameOut = "";
					a_typeOut = TypeInfo();
				}
			}

			std::uint32_t AutoPropSetFunction::GetStackFrameSize() const
			{
				return 1;
			}

			bool AutoPropSetFunction::GetIsNative() const
			{
				return true;
			}

			bool AutoPropSetFunction::GetIsStatic() const
			{
				return false;
			}

			bool AutoPropSetFunction::GetIsEmpty() const
			{
				return false;
			}

			IFunction::FunctionType AutoPropSetFunction::GetFunctionType() const
			{
				return FunctionType::kSetter;
			}

			std::uint32_t AutoPropSetFunction::GetUserFlags() const
			{
				return 0;
			}

			const BSFixedString& AutoPropSetFunction::GetDocString() const
			{
				return EMPTY;
			}

			void AutoPropSetFunction::InsertLocals([[maybe_unused]] StackFrame* a_frame) {}

			IFunction::CallResult AutoPropSetFunction::Call(const BSTSmartPointer<Stack>& a_stack, ErrorLogger* a_logger, [[maybe_unused]] Internal::VirtualMachine* a_vm, [[maybe_unused]] bool a_callingFromTasklets)
			{
				Variable& self = a_stack->top->self;

				if (self.IsObject() && self.GetObject() != nullptr) {
					const auto& value = a_stack->GetStackFrameVariable(a_stack->top, 0, 0);
					self.GetObject()->variables[autoVarIndex] = value;
				} else {
					a_logger->PostErrorImpl("Missing object for setting property", ErrorLogger::Severity::kError);
				}
				a_stack->returnValue = Variable();

				return CallResult::kCompleted;
			}

			const BSFixedString& AutoPropSetFunction::GetSourceFilename() const
			{
				static BSFixedString native("native");
				return native;
			}

			bool AutoPropSetFunction::TranslateIPToLineNumber([[maybe_unused]] std::uint32_t a_indexPtr, std::uint32_t& a_lineNumberOut) const
			{
				a_lineNumberOut = 0;
				return false;
			}

			bool AutoPropSetFunction::GetVarNameForStackIndex(std::uint32_t a_idx, BSFixedString& a_nameOut) const
			{
				// Skyrim does return "value" for non-zero indexes, which is an odd quirk since the value should be the first index (index 0)
				// Kept as-is
				if (a_idx != 0) {
					a_nameOut = "value";
					return true;
				}
				a_nameOut = "";
				return false;
			}

			bool AutoPropSetFunction::CanBeCalledFromTasklets() const
			{
				return true;
			}

			void AutoPropSetFunction::SetCallableFromTasklets([[maybe_unused]] bool a_callable) {}
		}
	}
}
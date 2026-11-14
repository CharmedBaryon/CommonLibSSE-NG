#include "RE/A/AutoPropGetFunction.h"

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

			AutoPropGetFunction::AutoPropGetFunction(BSFixedString& a_parentName, BSFixedString& a_propertyName, TypeInfo& a_type, uint32_t a_autoVarIndex) :
				parentObjName(a_parentName), propertyName(a_propertyName), type(a_type), autoVarIndex(a_autoVarIndex) {}

			const BSFixedString& AutoPropGetFunction::GetName() const
			{
				return propertyName;
			}

			const BSFixedString& AutoPropGetFunction::GetObjectTypeName() const
			{
				return parentObjName;
			}

			const BSFixedString& AutoPropGetFunction::GetStateName() const
			{
				return EMPTY;
			}

			TypeInfo AutoPropGetFunction::GetReturnType() const
			{
				return type;
			};

			std::uint32_t AutoPropGetFunction::GetParamCount() const
			{
				return 0;
			}

			void AutoPropGetFunction::GetParam([[maybe_unused]] std::uint32_t a_idx, BSFixedString& a_nameOut, TypeInfo& a_typeOut) const
			{
				a_nameOut = EMPTY;
				a_typeOut = TypeInfo();
			}

			std::uint32_t AutoPropGetFunction::GetStackFrameSize() const
			{
				return 0;
			}

			bool AutoPropGetFunction::GetIsNative() const
			{
				return true;
			}

			bool AutoPropGetFunction::GetIsStatic() const
			{
				return false;
			}

			bool AutoPropGetFunction::GetIsEmpty() const
			{
				return false;
			}

			IFunction::FunctionType AutoPropGetFunction::GetFunctionType() const
			{
				return FunctionType::kGetter;
			}

			std::uint32_t AutoPropGetFunction::GetUserFlags() const
			{
				return 0;
			}

			const BSFixedString& AutoPropGetFunction::GetDocString() const
			{
				return EMPTY;
			}

			void AutoPropGetFunction::InsertLocals([[maybe_unused]] StackFrame* a_frame) {}

			IFunction::CallResult AutoPropGetFunction::Call(const BSTSmartPointer<Stack>& a_stack, [[maybe_unused]] ErrorLogger* a_logger, [[maybe_unused]] Internal::VirtualMachine* a_vm, [[maybe_unused]] bool a_callingFromTasklets)
			{
				Variable& self = a_stack->top->self;

				if (self.IsObject() && self.GetObject() != nullptr) {
					a_stack->returnValue = self.GetObject()->variables[autoVarIndex];
				} else {
					a_stack->returnValue = Variable();
					a_logger->PostErrorImpl("Missing object for getting property", ErrorLogger::Severity::kError);
				}

				return CallResult::kCompleted;
			}

			const BSFixedString& AutoPropGetFunction::GetSourceFilename() const
			{
				static BSFixedString native("native");
				return native;
			}

			bool AutoPropGetFunction::TranslateIPToLineNumber([[maybe_unused]] std::uint32_t a_indexPtr, std::uint32_t& a_lineNumberOut) const
			{
				a_lineNumberOut = 0;
				return false;
			}

			bool AutoPropGetFunction::GetVarNameForStackIndex([[maybe_unused]] std::uint32_t a_idx, BSFixedString& a_nameOut) const
			{
				a_nameOut = "";
				return false;
			}

			bool AutoPropGetFunction::CanBeCalledFromTasklets() const
			{
				return true;
			}

			void AutoPropGetFunction::SetCallableFromTasklets([[maybe_unused]] bool a_callable) {}
		}
	}
}
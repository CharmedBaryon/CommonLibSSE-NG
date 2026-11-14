#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTSmartPointer.h"

namespace RE
{
	namespace BSScript
	{
		namespace Internal
		{
			class IFuncCallQuery;
		}

		class Variable;

		class IProfilePolicy
		{
		public:
			inline static constexpr auto RTTI = RTTI_BSScript__IProfilePolicy;
			inline static constexpr auto VTABLE = VTABLE_BSScript__IProfilePolicy;

			virtual ~IProfilePolicy();  // 00

			// add
			virtual void StackFramePushQueued(VMStackID a_stackID, std::uint32_t a_stackFrames, const BSTSmartPointer<Internal::IFuncCallQuery>& a_query) = 0;                                                                            // 01
			virtual void StackFramePushed(VMStackID a_stackID, std::uint32_t a_stackFrame, const Variable& a_selfObject, const BSFixedString& a_objectTypeName, const BSFixedString& a_stateName, const BSFixedString& a_fnName) = 0;     // 02
			virtual void StackFramePopQueued(VMStackID a_stackID, std::uint32_t a_stackFrame, const Variable& a_selfObject, const BSFixedString& a_objectTypeName, const BSFixedString& a_stateName, const BSFixedString& a_fnName) = 0;  // 03
			virtual void StackFramePopped(VMStackID a_stackID, std::uint32_t a_stackFrame, const Variable& a_selfObject, const BSFixedString& a_objectTypeName, const BSFixedString& a_stateName, const BSFixedString& a_fnName) = 0;     // 04
		};
		static_assert(sizeof(IProfilePolicy) == 0x8);
	}
}

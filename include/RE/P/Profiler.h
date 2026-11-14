#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSTHashMap.h"
#include "RE/I/IProfilePolicy.h"

namespace RE
{
	namespace SkyrimScript
	{
		class Profiler : public BSScript::IProfilePolicy
		{
		public:
			inline static constexpr auto RTTI = RTTI_SkyrimScript__Profiler;
			inline static constexpr auto VTABLE = VTABLE_SkyrimScript__Profiler;

			~Profiler() override;  // 00

			// override (BSScript::IProfilePolicy)
			void StackFramePushQueued(VMStackID a_stackID, std::uint32_t a_stackFrames, const BSTSmartPointer<BSScript::Internal::IFuncCallQuery>& a_query) override;                                                                            // 01
			void StackFramePushed(VMStackID a_stackID, std::uint32_t a_stackFrame, const BSScript::Variable& a_selfObject, const BSFixedString& a_objectTypeName, const BSFixedString& a_stateName, const BSFixedString& a_fnName) override;     // 02
			void StackFramePopQueued(VMStackID a_stackID, std::uint32_t a_stackFrame, const BSScript::Variable& a_selfObject, const BSFixedString& a_objectTypeName, const BSFixedString& a_stateName, const BSFixedString& a_fnName) override;  // 03
			void StackFramePopped(VMStackID a_stackID, std::uint32_t a_stackFrame, const BSScript::Variable& a_selfObject, const BSFixedString& a_objectTypeName, const BSFixedString& a_stateName, const BSFixedString& a_fnName) override;     // 04

			// members
			mutable BSSpinLock           unk08;  // 08
			BSTHashMap<UnkKey, UnkValue> unk10;  // 10
			BSTHashMap<UnkKey, UnkValue> unk40;  // 40
			BSTHashMap<UnkKey, UnkValue> unk70;  // 70
			std::uint64_t                unkA0;  // A0
			std::uint64_t                unkA8;  // A8
			std::uint64_t                unkB0;  // B0
			std::uint64_t                unkB8;  // B8
			std::uint64_t                unkC0;  // C0
			std::uint64_t                unkC8;  // C8
			std::uint64_t                unkD0;  // D0
			std::uint64_t                unkD8;  // D8
		};
		static_assert(sizeof(Profiler) == 0xE0);
	}
}

#pragma once

#include "RE/C/CombatBlackboardKeyBase.h"

namespace RE
{
	/*
	141DF3148 CombatKey_AcquireWeaponTimer
    141DF3010 CombatKey_CombatDisarmedTimeStamp
    141DF31B0 CombatKey_CoverSearchFailedTimeStamp
    141DF3158 CombatKey_FindAttackLocationFailedTimeStamp
    141DF3170 CombatKey_LastFleeDoor
    141DF2FA8 CombatKey_MagicDisarmRestrictionTimer
    141DF2FC8 CombatKey_MagicParalyzeRestrictionTimer
    141DF2FB8 CombatKey_MagicReanimateRestrictionTimer
    141DF2F88 CombatKey_MagicRestoreRestrictionTimer
    141DF2FD8 CombatKey_MagicScriptRestrictionTimer
    141DF2F98 CombatKey_MagicSummonRestrictionTimer
    141DF32B8 CombatKey_TargetUnreachableDistance
	*/

	struct AITimeStamp;
	struct AITimer;
	class TESObjectREFR;

	template <typename T, const std::array<REL::VariantID, 1>& vftableID = VTABLE_CombatBlackboardKeyBase>
	class CombatBlackboardKey : public CombatBlackboardKeyBase
	{
	public:
		inline static constexpr auto VTABLE = vftableID;

		CombatBlackboardKey()
		{
			stl::emplace_vtable<CombatBlackboardKey>(this);
		}
	};

	template <>
	class CombatBlackboardKey<float, VTABLE_CombatBlackboardKeyBase> : public CombatBlackboardKeyBase
	{
	public:
		inline static constexpr auto VTABLE = VTABLE_CombatBlackboardKey_float_;

		CombatBlackboardKey()
		{
			stl::emplace_vtable<CombatBlackboardKey>(this);
		}
	};

	template <>
	class CombatBlackboardKey<AITimer, VTABLE_CombatBlackboardKeyBase> : public CombatBlackboardKeyBase
	{
	public:
		inline static constexpr auto VTABLE = VTABLE_CombatBlackboardKey_AITimer_;

		CombatBlackboardKey()
		{
			stl::emplace_vtable<CombatBlackboardKey>(this);
		}
	};

	template <>
	class CombatBlackboardKey<AITimeStamp, VTABLE_CombatBlackboardKeyBase> : public CombatBlackboardKeyBase
	{
	public:
		inline static constexpr auto VTABLE = VTABLE_CombatBlackboardKey_AITimeStamp_;

		CombatBlackboardKey()
		{
			stl::emplace_vtable<CombatBlackboardKey>(this);
		}
	};

	template <>
	class CombatBlackboardKey<BSTTuple<TESObjectREFR*, AITimeStamp>, VTABLE_CombatBlackboardKeyBase> : public CombatBlackboardKeyBase
	{
	public:
		inline static constexpr auto VTABLE = VTABLE_CombatBlackboardKey_BSTTuple_TESObjectREFR___AITimeStamp__;

		CombatBlackboardKey()
		{
			stl::emplace_vtable<CombatBlackboardKey>(this);
		}
	};

	// Inherit from it to create new keys
	template <typename T>
	class CombatBlackboardKeyCustomBase : public CombatBlackboardKeyBase
	{
	public:
		CombatBlackboardKeyCustomBase() = default;
		~CombatBlackboardKeyCustomBase() = default;

		uint32_t GetObjectSize() override
		{
			return sizeof(T);
		}

		void CreateObject(void* obj) override
		{
			if (obj)
				new (obj) T();
		}

		void DestroyObject(void* obj) override
		{
			reinterpret_cast<T*>(obj)->~T();
		}

		const BSFixedString& GetName() const override
		{
			return name;
		}
	};
}

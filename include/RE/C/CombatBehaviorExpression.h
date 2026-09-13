#pragma once

#include "RE/C/CombatBehaviorController.h"
#include "RE/C/CombatBehaviorThread.h"
#include "RE/T/TLSData.h"

namespace RE
{
	namespace Impl
	{
		template <typename F>
		struct return_type;

		template <typename R, typename... Args>
		struct return_type<R (*)(Args...)>
		{
			using type = R;
		};

		template <typename C, typename R, typename... Args>
		struct return_type<R (C::*)(Args...)>
		{
			using type = R;
		};

		template <typename C, typename R, typename... Args>
		struct return_type<R (C::*)(Args...) const>
		{
			using type = R;
		};

		template <typename C, typename R, typename... Args>
		struct return_type<R (C::*)(Args...) noexcept>
		{
			using type = R;
		};

		template <typename C, typename R, typename... Args>
		struct return_type<R (C::*)(Args...) const noexcept>
		{
			using type = R;
		};
	}

	template <typename F, typename... Args>
	class CombatBehaviorFunc
	{
	public:
		template <typename T>
		explicit operator T()
		{
			return static_cast<T>(std::apply(f, args));
		}

		operator typename Impl::return_type<F>::type()
		{
			return std::apply(f, args);
		}

		// members
		F                   f;
		std::tuple<Args...> args;
	};

	template <typename F>
	class CombatBehaviorFunc<F>
	{
	public:
		template <typename T>
		explicit operator T()
		{
			return static_cast<T>(f());
		}

		operator typename Impl::return_type<F>::type()
		{
			return f();
		}

		// members
		F f;
	};

	template <typename E>
	class CombatBehaviorExpression
	{
	public:
		template <typename T>
		operator T()
		{
			return static_cast<T>(e);
		}

		// members
		E e;
	};

	struct OpNot
	{
		static bool apply(bool arg)
		{
			return !arg;
		}
	};

	template <typename F, typename Op>
	class CombatBehaviorUnaryExpression
	{
	public:
		template <typename T>
		operator T()
		{
			return Op::apply(f);
		}

		// members
		F f;
	};

	struct OpLessThan
	{
		static bool apply(auto&& arg1, auto&& arg2)
		{
			return arg1 < arg2;
		}
	};

	struct OpGreaterThan
	{
		static bool apply(auto&& arg1, auto&& arg2)
		{
			return arg1 > arg2;
		}
	};

	struct OpEquals
	{
		static bool apply(auto&& arg1, auto&& arg2)
		{
			return arg1 == arg2;
		}
	};

	struct OpNotEquals
	{
		static bool apply(auto&& arg1, auto&& arg2)
		{
			return arg1 != arg2;
		}
	};

	struct OpAnd
	{
		static bool apply(bool arg1, bool arg2)
		{
			return arg1 && arg2;
		}
	};

	struct OpOr
	{
		static bool apply(bool arg1, bool arg2)
		{
			return arg1 || arg2;
		}
	};

	template <typename F1, typename F2, typename Op>
	class CombatBehaviorBinaryExpression
	{
	public:
		template <typename T>
		operator T()
		{
			return Op::apply(f1, f2);
		}

		// members
		F1 f1;
		F2 f2;
	};

	template <typename T>
	T* CombatBehaviorMemberFunc__GetThis()
	{
		if constexpr (std::is_same_v<T, Actor>) {
			return CombatBehaviorController::GetCurrentAttacker();
		} else if constexpr (std::is_same_v<T, CombatGroup>) {
			return CombatBehaviorController::GetCurrentCombatGroup();
		} else if constexpr (std::is_same_v<T, CombatInventory>) {
			return CombatBehaviorController::GetCurrentCombatInventory();
		} else if constexpr (std::is_same_v<T, CombatState>) {
			return CombatBehaviorController::GetCurrentCombatState();
		} else {
			return GetStaticTLSData()->combatAIThread->template GetCurrentObject<T>();
		}
	}

	template <typename C, typename M, typename... Args>
	class CombatBehaviorMemberFunc
	{
	public:
		template <typename T>
		explicit operator T()
		{
			return static_cast<T>(this->operator typename RE::Impl::return_type<M>::type());
		}

		operator typename Impl::return_type<M>::type()
		{
			return std::apply([this](auto&&... args) { return (CombatBehaviorMemberFunc__GetThis<C>()->*f)(std::forward<decltype(args)>(args)...); }, args);
		}

		// members
		M                   f;
		std::tuple<Args...> args;
	};

	template <typename C, typename M>
	class CombatBehaviorMemberFunc<C, M>
	{
	public:
		template <typename T>
		explicit operator T()
		{
			return static_cast<T>(this->operator typename RE::Impl::return_type<M>::type());
		}

		operator typename Impl::return_type<M>::type()
		{
			return (CombatBehaviorMemberFunc__GetThis<C>()->*f)();
		}

		// members
		M f;
	};
}

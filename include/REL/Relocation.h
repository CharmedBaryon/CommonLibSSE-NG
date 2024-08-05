#pragma once

#include "REL/ID.h"
#include "REL/Module.h"

#include "SKSE/Trampoline.h"

#define REL_MAKE_MEMBER_FUNCTION_POD_TYPE_HELPER_IMPL(a_nopropQual, a_propQual, ...)              \
	template <                                                                                    \
		class R,                                                                                  \
		class Cls,                                                                                \
		class... Args>                                                                            \
	struct member_function_pod_type<R (Cls::*)(Args...) __VA_ARGS__ a_nopropQual a_propQual>      \
	{                                                                                             \
		using type = R(__VA_ARGS__ Cls*, Args...) a_propQual;                                     \
	};                                                                                            \
                                                                                                  \
	template <                                                                                    \
		class R,                                                                                  \
		class Cls,                                                                                \
		class... Args>                                                                            \
	struct member_function_pod_type<R (Cls::*)(Args..., ...) __VA_ARGS__ a_nopropQual a_propQual> \
	{                                                                                             \
		using type = R(__VA_ARGS__ Cls*, Args..., ...) a_propQual;                                \
	};

#define REL_MAKE_MEMBER_FUNCTION_POD_TYPE_HELPER(a_qualifer, ...)              \
	REL_MAKE_MEMBER_FUNCTION_POD_TYPE_HELPER_IMPL(a_qualifer, , ##__VA_ARGS__) \
	REL_MAKE_MEMBER_FUNCTION_POD_TYPE_HELPER_IMPL(a_qualifer, noexcept, ##__VA_ARGS__)

#define REL_MAKE_MEMBER_FUNCTION_POD_TYPE(...)                 \
	REL_MAKE_MEMBER_FUNCTION_POD_TYPE_HELPER(, __VA_ARGS__)    \
	REL_MAKE_MEMBER_FUNCTION_POD_TYPE_HELPER(&, ##__VA_ARGS__) \
	REL_MAKE_MEMBER_FUNCTION_POD_TYPE_HELPER(&&, ##__VA_ARGS__)

#define REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE_HELPER_IMPL(a_nopropQual, a_propQual, ...)              \
	template <                                                                                        \
		class R,                                                                                      \
		class Cls,                                                                                    \
		class... Args>                                                                                \
	struct member_function_non_pod_type<R (Cls::*)(Args...) __VA_ARGS__ a_nopropQual a_propQual>      \
	{                                                                                                 \
		using type = R&(__VA_ARGS__ Cls*, void*, Args...)a_propQual;                                  \
	};                                                                                                \
                                                                                                      \
	template <                                                                                        \
		class R,                                                                                      \
		class Cls,                                                                                    \
		class... Args>                                                                                \
	struct member_function_non_pod_type<R (Cls::*)(Args..., ...) __VA_ARGS__ a_nopropQual a_propQual> \
	{                                                                                                 \
		using type = R&(__VA_ARGS__ Cls*, void*, Args..., ...)a_propQual;                             \
	};

#define REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE_HELPER(a_qualifer, ...)              \
	REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE_HELPER_IMPL(a_qualifer, , ##__VA_ARGS__) \
	REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE_HELPER_IMPL(a_qualifer, noexcept, ##__VA_ARGS__)

#define REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE(...)                 \
	REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE_HELPER(, __VA_ARGS__)    \
	REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE_HELPER(&, ##__VA_ARGS__) \
	REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE_HELPER(&&, ##__VA_ARGS__)

namespace REL
{
	namespace detail
	{
		template <class>
		struct member_function_pod_type;

		REL_MAKE_MEMBER_FUNCTION_POD_TYPE();
		REL_MAKE_MEMBER_FUNCTION_POD_TYPE(const);
		REL_MAKE_MEMBER_FUNCTION_POD_TYPE(volatile);
		REL_MAKE_MEMBER_FUNCTION_POD_TYPE(const volatile);

		template <class F>
		using member_function_pod_type_t = typename member_function_pod_type<F>::type;

		template <class>
		struct member_function_non_pod_type;

		REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE();
		REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE(const);
		REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE(volatile);
		REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE(const volatile);

		template <class F>
		using member_function_non_pod_type_t = typename member_function_non_pod_type<F>::type;

		// https://docs.microsoft.com/en-us/cpp/build/x64-calling-convention

		template <class T>
		struct meets_length_req :
			std::disjunction<
				std::bool_constant<sizeof(T) == 1>,
				std::bool_constant<sizeof(T) == 2>,
				std::bool_constant<sizeof(T) == 4>,
				std::bool_constant<sizeof(T) == 8>>
		{};

		template <class T>
		struct meets_function_req :
			std::conjunction<
				std::is_trivially_constructible<T>,
				std::is_trivially_destructible<T>,
				std::is_trivially_copy_assignable<T>,
				std::negation<
					std::is_polymorphic<T>>>
		{};

		template <class T>
		struct meets_member_req : std::is_standard_layout<T>
		{};

		template <class T, class = void>
		struct is_x64_pod : std::true_type
		{};

		template <class T>
		struct is_x64_pod<
			T,
			std::enable_if_t<
				std::is_union_v<T>>> :
			std::false_type
		{};

		template <class T>
		struct is_x64_pod<
			T,
			std::enable_if_t<
				std::is_class_v<T>>> :
			std::conjunction<
				meets_length_req<T>,
				meets_function_req<T>,
				meets_member_req<T>>
		{};

		template <class T>
		inline constexpr bool is_x64_pod_v = is_x64_pod<T>::value;

		template <
			class F,
			class First,
			class... Rest>
		decltype(auto) invoke_member_function_non_pod(F&& a_func, First&& a_first, Rest&&... a_rest)  //
			noexcept(std::is_nothrow_invocable_v<F, First, Rest...>)
		{
			using result_t = std::invoke_result_t<F, First, Rest...>;
			std::aligned_storage_t<sizeof(result_t), alignof(result_t)> result;

			using func_t = member_function_non_pod_type_t<F>;
			auto func = stl::unrestricted_cast<func_t*>(std::forward<F>(a_func));

			return func(std::forward<First>(a_first), std::addressof(result), std::forward<Rest>(a_rest)...);
		}
	}

	inline constexpr std::uint8_t NOP = 0x90;
	inline constexpr std::uint8_t NOP2[] = { 0x66, 0x90 };
	inline constexpr std::uint8_t NOP3[] = { 0x0F, 0x1F, 0x00 };
	inline constexpr std::uint8_t NOP4[] = { 0x0F, 0x1F, 0x40, 0x00 };
	inline constexpr std::uint8_t NOP5[] = { 0x0F, 0x1F, 0x44, 0x00, 0x00 };
	inline constexpr std::uint8_t NOP6[] = { 0x66, 0x0F, 0x1F, 0x44, 0x00, 0x00 };
	inline constexpr std::uint8_t NOP7[] = { 0x0F, 0x1F, 0x80, 0x00, 0x00, 0x00, 0x00 };
	inline constexpr std::uint8_t NOP8[] = { 0x0F, 0x1F, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00 };
	inline constexpr std::uint8_t NOP9[] = { 0x66, 0x0F, 0x1F, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00 };

	inline constexpr std::uint8_t JMP8 = 0xEB;
	inline constexpr std::uint8_t JMP32 = 0xE9;
	inline constexpr std::uint8_t RET = 0xC3;
	inline constexpr std::uint8_t INT3 = 0xCC;

	template <class F, class... Args>
	std::invoke_result_t<F, Args...> invoke(F&& a_func, Args&&... a_args) noexcept(std::is_nothrow_invocable_v<F, Args...>)
		requires(std::invocable<F, Args...>)
	{
		if constexpr (std::is_member_function_pointer_v<std::decay_t<F>>) {
			if constexpr (detail::is_x64_pod_v<std::invoke_result_t<F, Args...>>) {  // member functions == free functions in x64
				using func_t = detail::member_function_pod_type_t<std::decay_t<F>>;
				auto func = stl::unrestricted_cast<func_t*>(std::forward<F>(a_func));
				return func(std::forward<Args>(a_args)...);
			} else {  // shift args to insert result
				return detail::invoke_member_function_non_pod(std::forward<F>(a_func), std::forward<Args>(a_args)...);
			}
		} else {
			return std::forward<F>(a_func)(std::forward<Args>(a_args)...);
		}
	}

	void safe_write(std::uintptr_t a_dst, const void* a_src, std::size_t a_count);

	template <std::integral T>
	void safe_write(std::uintptr_t a_dst, const T& a_data)
	{
		safe_write(a_dst, std::addressof(a_data), sizeof(T));
	}

	template <class T>
	void safe_write(std::uintptr_t a_dst, std::span<T> a_data)
	{
		safe_write(a_dst, a_data.data(), a_data.size_bytes());
	}

	void safe_fill(std::uintptr_t a_dst, std::uint8_t a_value, std::size_t a_count);

	template <class T = std::uintptr_t>
	class Relocation
	{
	public:
		using value_type =
			std::conditional_t<
				std::is_member_pointer_v<T> || std::is_function_v<std::remove_pointer_t<T>>,
				std::decay_t<T>,
				T>;

		constexpr Relocation() noexcept = default;

		explicit constexpr Relocation(std::uintptr_t a_address) noexcept :
			_impl{ a_address }
		{}

		explicit Relocation(Offset a_offset) :
			_impl{ a_offset.address() }
		{}

		explicit Relocation(VariantOffset a_offset) :
			_impl{ a_offset.address() }
		{}

		explicit Relocation(ID a_id) :
			_impl{ a_id.address() }
		{}

		explicit Relocation(ID a_id, std::ptrdiff_t a_offset) :
			_impl{ a_id.address() + a_offset }
		{}

		explicit Relocation(ID a_id, Offset a_offset) :
			_impl{ a_id.address() + a_offset.offset() }
		{}

		explicit Relocation(ID a_id, VariantOffset a_offset) :
			_impl{ a_id.address() + a_offset.offset() }
		{}

		explicit Relocation(RelocationID a_id) :
			_impl{ a_id.address() }
		{}

		explicit Relocation(RelocationID a_id, std::ptrdiff_t a_offset) :
			_impl{ a_id.address() + a_offset }
		{}

		explicit Relocation(RelocationID a_id, Offset a_offset) :
			_impl{ a_id.address() + a_offset.offset() }
		{}

		explicit Relocation(RelocationID a_id, VariantOffset a_offset) :
			_impl{ a_id.address() + a_offset.offset() }
		{}

		explicit Relocation(VariantID a_id) :
			_impl{ a_id.address() }
		{}

		explicit Relocation(VariantID a_id, std::ptrdiff_t a_offset) :
			_impl{ a_id.address() + a_offset }
		{}

		explicit Relocation(VariantID a_id, Offset a_offset) :
			_impl{ a_id.address() + a_offset.offset() }
		{}

		explicit Relocation(VariantID a_id, VariantOffset a_offset) :
			_impl{ a_id.address() + a_offset.offset() }
		{}

		constexpr Relocation& operator=(std::uintptr_t a_address) noexcept
		{
			_impl = a_address;
			return *this;
		}

		Relocation& operator=(Offset a_offset)
		{
			_impl = a_offset.address();
			return *this;
		}

		Relocation& operator=(VariantOffset a_offset)
		{
			_impl = a_offset.address();
			return *this;
		}

		Relocation& operator=(ID a_id)
		{
			_impl = a_id.address();
			return *this;
		}

		Relocation& operator=(RelocationID a_id)
		{
			_impl = a_id.address();
			return *this;
		}

		Relocation& operator=(VariantID a_id)
		{
			_impl = a_id.address();
			return *this;
		}

		template <class U = value_type>
		[[nodiscard]] decltype(auto) operator*() const noexcept
			requires(std::is_pointer_v<U>)
		{
			return *get();
		}

		template <class U = value_type>
		[[nodiscard]] auto operator->() const noexcept
			requires(std::is_pointer_v<U>)
		{
			return get();
		}

		template <class... Args>
		std::invoke_result_t<const value_type&, Args...> operator()(Args&&... a_args) const
			noexcept(std::is_nothrow_invocable_v<const value_type&, Args...>)
			requires(std::invocable<const value_type&, Args...>)
		{
			return REL::invoke(get(), std::forward<Args>(a_args)...);
		}

		[[nodiscard]] constexpr std::uintptr_t address() const noexcept { return _impl; }

		[[nodiscard]] std::size_t offset() const { return _impl - base(); }

		[[nodiscard]] value_type get() const
			noexcept(std::is_nothrow_copy_constructible_v<value_type>)
		{
			assert(_impl != 0);
			return stl::unrestricted_cast<value_type>(_impl);
		}

		template <std::integral U>
		void write(const U& a_data)
			requires(std::same_as<value_type, std::uintptr_t>)
		{
			safe_write(address(), std::addressof(a_data), sizeof(T));
		}

		template <class U>
		void write(const std::span<U> a_data)
			requires(std::same_as<value_type, std::uintptr_t>)
		{
			safe_write(address(), a_data.data(), a_data.size_bytes());
		}

		template <std::size_t N>
		std::uintptr_t write_branch(const std::uintptr_t a_dst)
			requires(std::same_as<value_type, std::uintptr_t>)
		{
			return SKSE::GetTrampoline().write_branch<N>(address(), a_dst);
		}

		template <std::size_t N, class F>
		std::uintptr_t write_branch(const F a_dst)
			requires(std::same_as<value_type, std::uintptr_t>)
		{
			return SKSE::GetTrampoline().write_branch<N>(address(), stl::unrestricted_cast<std::uintptr_t>(a_dst));
		}

		template <std::size_t N>
		std::uintptr_t write_call(const std::uintptr_t a_dst)
			requires(std::same_as<value_type, std::uintptr_t>)
		{
			return SKSE::GetTrampoline().write_call<N>(address(), a_dst);
		}

		template <std::size_t N, class F>
		std::uintptr_t write_call(const F a_dst)
			requires(std::same_as<value_type, std::uintptr_t>)
		{
			return SKSE::GetTrampoline().write_call<N>(address(), stl::unrestricted_cast<std::uintptr_t>(a_dst));
		}

		void write_fill(const std::uint8_t a_value, const std::size_t a_count)
			requires(std::same_as<value_type, std::uintptr_t>)
		{
			safe_fill(address(), a_value, a_count);
		}

		template <class U = value_type>
		std::uintptr_t write_vfunc(const std::size_t a_idx, const std::uintptr_t a_newFunc)
			requires(std::same_as<U, std::uintptr_t>)
		{
			const auto addr = address() + (sizeof(void*) * a_idx);
			const auto result = *reinterpret_cast<std::uintptr_t*>(addr);
			safe_write(addr, a_newFunc);
			return result;
		}

		template <class F>
		std::uintptr_t write_vfunc(std::size_t a_idx, F a_newFunc)
			requires(std::same_as<value_type, std::uintptr_t>)
		{
			return write_vfunc(a_idx, stl::unrestricted_cast<std::uintptr_t>(a_newFunc));
		}

	private:
		// clang-format off
        [[nodiscard]] static std::uintptr_t base() { return Module::get().base(); }
		// clang-format on

		std::uintptr_t _impl{ 0 };
	};

	/**
	 * Return the correct value of two choices between SE/VR, and AE versions of Skyrim.
	 *
	 * <p>
	 * This is commonly used to select between relative offsets within a function, when hooking a call instruction.
	 * In such cases the function can be identified by its Address Library ID, but the offset within the function
	 * may vary between Skyrim versions. This selection is made at runtime, allowing the same compiled code to run
	 * in multiple versions of Skyrim.
	 * </p>
	 *
	 * @tparam T the type of value to return.
	 * @param a_seAndVR the value to use for SE and VR.
	 * @param a_ae the value to use for AE.
	 * @return Either <code>a_seAndVR</code> if the current runtime is Skyrim SE or VR, or <code>a_ae</code> if the runtime is AE.
	 */
	template <class T>
	[[nodiscard]] SKYRIM_ADDR T Relocate(
		[[maybe_unused]] T&& a_seAndVR,
		[[maybe_unused]] T&& a_ae) noexcept
	{
#ifndef ENABLE_SKYRIM_AE
		return a_seAndVR;
#elif !defined(ENABLE_SKYRIM_SE) && !defined(ENABLE_SKYRIM_VR)
		return a_ae;
#else
		return Module::IsAE() ? a_ae : a_seAndVR;
#endif
	}

	/**
	 * Return the correct value of two choices between SE, AE, and VR versions of Skyrim.
	 *
	 * <p>
	 * This is commonly used to select between relative offsets within a function, when hooking a call instruction.
	 * In such cases the function can be identified by its Address Library ID, but the offset within the function
	 * may vary between Skyrim versions. This selection is made at runtime, allowing the same compiled code to run
	 * in multiple versions of Skyrim.
	 * </p>
	 *
	 * @tparam T the type of value to return.
	 * @param a_se the value to use for SE.
	 * @param a_ae the value to use for AE.
	 * @param a_vr the value to use for VR.
	 * @return Either <code>a_se</code> if the current runtime is Skyrim SE, or <code>a_ae</code> if the runtime is AE, or
	 * <code>a_vr</code> if running Skyrim VR.
	 */
	template <class T>
	[[nodiscard]] SKYRIM_REL T Relocate(
		[[maybe_unused]] T a_se,
		[[maybe_unused]] T a_ae,
		[[maybe_unused]] T a_vr) noexcept
	{
#if defined(EXCLUSIVE_SKYRIM_SE)
		return a_se;
#elif !defined(ENABLE_SKYRIM_SE) && !defined(ENABLE_SKYRIM_VR)
		return a_ae;
#elif defined(EXCLUSIVE_SKYRIM_VR)
		return a_vr;
#else
		switch (Module::get().GetRuntime()) {
		case Module::Runtime::AE:
			return a_ae;
		case Module::Runtime::VR:
			return a_vr;
		default:
			return a_se;
		}
#endif
	}

	namespace detail
	{
		template <class T>
		struct RelocateVirtualHelper
		{};

		template <class Ret, class This>
		struct RelocateVirtualHelper<Ret(This*)>
		{
			using this_type = This;
			using return_type = Ret;
			using function_type = Ret(This*);
		};

		template <class Ret, class This, class... Args>
		struct RelocateVirtualHelper<Ret(This*, Args...)>
		{
			using this_type = This;
			using return_type = Ret;
			using function_type = Ret(This*, Args...);
		};

		template <class Ret, class This>
		struct RelocateVirtualHelper<Ret (This::*)()>
		{
			using this_type = This;
			using return_type = Ret;
			using function_type = Ret(This*);
		};

		template <class Ret, class This, class... Args>
		struct RelocateVirtualHelper<Ret (This::*)(Args...)>
		{
			using this_type = This;
			using return_type = Ret;
			using function_type = Ret(This*, Args...);
		};

		template <class Ret, class This>
		struct RelocateVirtualHelper<Ret (This::*)() const>
		{
			using this_type = const This;
			using return_type = Ret;
			using function_type = Ret(const This*);
		};

		template <class Ret, class This, class... Args>
		struct RelocateVirtualHelper<Ret (This::*)(Args...) const>
		{
			using this_type = const This;
			using return_type = Ret;
			using function_type = Ret(const This*, Args...);
		};
	}

	/**
	 * Invokes a virtual function in a cross-platform way where the vtable structure is variant across AE/SE and VR runtimes.
	 *
	 * <p>
	 * Some classes in Skyrim VR add new virtual functions in the middle of the vtable structure, which makes it ABI-incompatible with AE/SE.
	 * A naive virtual function call, therefore, cannot work across all runtimes without the plugin being recompiled specifically for VR.
	 * This call works with types which have variant vtables to allow a non-virtual function definition to be created in the virtual function's
	 * place, and to have that call dynamically lookup the correct function based on the vtable structure expected in the current runtime.
	 * </p>
	 *
	 * @tparam Fn the type of the function being called.
	 * @tparam Args the types of the arguments being passed.
	 * @param a_seAndAEVtableOffset the offset from the <code>this</code> pointer to the vtable with the virtual function in SE/AE.
	 * @param a_vrVtableIndex the offset from the <code>this</code> pointer to the vtable with the virtual function in VR.
	 * @param a_seAndAEVtableIndex the index of the function in the class' vtable in SE and AE.
	 * @param a_vrVtableIndex the index of the function in the class' vtable in VR.
	 * @param a_self the <code>this</code> argument for the call.
	 * @param a_args the remaining arguments for the call, if any.
	 * @return The result of the function call.
	 */
	template <class Fn, class... Args>
	[[nodiscard]] inline typename detail::RelocateVirtualHelper<Fn>::return_type RelocateVirtual(
		[[maybe_unused]] std::ptrdiff_t                        a_seAndAEVtableOffset,
		[[maybe_unused]] std::ptrdiff_t                        a_vrVtableOffset,
		[[maybe_unused]] std::ptrdiff_t                        a_seAndAEVtableIndex,
		[[maybe_unused]] std::ptrdiff_t                        a_vrVtableIndex,
		typename detail::RelocateVirtualHelper<Fn>::this_type* a_self, Args&&... a_args)
	{
		return (*reinterpret_cast<typename detail::RelocateVirtualHelper<Fn>::function_type**>(
			*reinterpret_cast<const uintptr_t*>(reinterpret_cast<uintptr_t>(a_self) +
#ifndef ENABLE_SKYRIM_VR
												a_seAndAEVtableOffset) +
			a_seAndAEVtableIndex
#elif defined(EXCLUSIVE_SKYRIM_VR)
												a_vrVtableOffset) +
			a_vrVtableIndex
#else
												(Module::IsVR() ? a_vrVtableOffset : a_seAndAEVtableOffset)) +
			(Module::IsVR() ? a_vrVtableIndex : a_seAndAEVtableIndex)
#endif
				* sizeof(uintptr_t)))(a_self, std::forward<Args>(a_args)...);
	}

	/**
	 * Invokes a virtual function in a cross-platform way where the vtable structure is variant across AE/SE and VR runtimes.
	 *
	 * <p>
	 * Some classes in Skyrim VR add new virtual functions in the middle of the vtable structure, which makes it ABI-incompatible with AE/SE.
	 * A naive virtual function call, therefore, cannot work across all runtimes without the plugin being recompiled specifically for VR.
	 * This call works with types which have variant vtables to allow a non-virtual function definition to be created in the virtual function's
	 * place, and to have that call dynamically lookup the correct function based on the vtable structure expected in the current runtime.
	 * </p>
	 *
	 * <p>
	 * This call assumes the vtable to be used is the one at offset 0, i.e. it invokes a virtual function either on the first parent class
	 * or the current class.
	 * </p>
	 *
	 * @tparam Fn the type of the function being called.
	 * @tparam Args the types of the arguments being passed.
	 * @param a_seAndAEVtableIndex the index of the function in the class' vtable in SE and AE.
	 * @param a_vrVtableIndex the index of the function in the class' vtable in VR.
	 * @param a_self the <code>this</code> argument for the call.
	 * @param a_args the remaining arguments for the call, if any.
	 * @return The result of the function call.
	 */
	template <class Fn, class... Args>
	[[nodiscard]] inline typename detail::RelocateVirtualHelper<Fn>::return_type RelocateVirtual(
		std::ptrdiff_t                                         a_seAndAEVtableIndex,
		std::ptrdiff_t                                         a_vrVtableIndex,
		typename detail::RelocateVirtualHelper<Fn>::this_type* a_self, Args&&... a_args)
	{
		return RelocateVirtual<Fn, Args...>(0, 0, a_seAndAEVtableIndex, a_vrVtableIndex, a_self, std::forward<Args>(a_args)...);
	}

	/**
	 * Gets a member variable in a cross-platform way, using runtime-specific memory offsets.
	 *
	 * <p>
	 * This function handles the variant memory structures used in Skyrim VR as compared to versions of SE.
	 * It allows a memory offset relative to the object's base address for SE (and AE) and a separate one for
	 * VR. This simplifies the process of creating functions to get member variables that are at different
	 * offsets in different runtimes from a single build.
	 * </p>
	 *
	 * @tparam T the type of the member being accessed.
	 * @tparam This the type of the target object that has the member.
	 * @param a_self the target object that has the member.
	 * @param a_seAndAE the memory offset of the member in Skyrim SE and AE.
	 * @param a_vr the memory offset of the member in Skyrim VR.
	 * @return A reference to the member.
	 */
	template <class T, class This>
	[[nodiscard]] inline T& RelocateMember(This* a_self, std::ptrdiff_t a_seAndAE, std::ptrdiff_t a_vr)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(a_self) + Relocate(a_seAndAE, a_seAndAE, a_vr));
	}

	template <class T, class This>
	[[nodiscard]] inline T& RelocateMember(This* a_self, std::ptrdiff_t offset)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(a_self) + offset);
	}

	template <class T, class This>
	[[nodiscard]] inline T& RelocateMemberIf(bool condition, This* a_self, std::ptrdiff_t a, std::ptrdiff_t b)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(a_self) + (condition ? a : b));
	}

	template <class T, class This>
	[[nodiscard]] inline T& RelocateMemberIfNewer(Version v, This* a_self, std::ptrdiff_t older, std::ptrdiff_t newer)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(a_self) +
									 (REL::Module::get().version().compare(v) == std::strong_ordering::less ? older : newer));
	}
}

#undef REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE
#undef REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE_HELPER
#undef REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE_HELPER_IMPL

#undef REL_MAKE_MEMBER_FUNCTION_POD_TYPE
#undef REL_MAKE_MEMBER_FUNCTION_POD_TYPE_HELPER
#undef REL_MAKE_MEMBER_FUNCTION_POD_TYPE_HELPER_IMPL

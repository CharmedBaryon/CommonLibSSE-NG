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

	/**
	 * @brief Write data to memory safely (without verification).
	 * 
	 * Temporarily changes memory protection to PAGE_EXECUTE_READWRITE, performs the write,
	 * then restores the original protection.
	 * 
	 * @param a_dst The destination memory address
	 * @param a_src Pointer to the source data
	 * @param a_count Number of bytes to write
	 * 
	 * @warning This function does NOT verify memory contents before writing.
	 *          Consider using safe_write with verification for production code.
	 * @note Define REL_AUDIT_UNVERIFIED_PATCHES to log unverified patch locations.
	 */
#ifdef REL_AUDIT_UNVERIFIED_PATCHES
	[[deprecated("Consider using safe_write with verification - define REL_AUDIT_UNVERIFIED_PATCHES to track usage")]]
#endif
	void safe_write(std::uintptr_t a_dst, const void* a_src, std::size_t a_count);

	/**
	 * @brief Write data to memory with optional code verification.
	 * 
	 * First verifies that the target memory contains expected bytes (if provided),
	 * then performs the write operation if verification passes. Uses safe_write internally.
	 * 
	 * @param a_dst The destination memory address
	 * @param a_src Pointer to the source data
	 * @param a_count Number of bytes to write
	 * @param a_expected Pointer to expected bytes at the destination (optional)
	 * @param a_expected_count Number of expected bytes to verify (optional)
	 * @return true if verification passed and write was successful, false otherwise
	 * 
	 * @note If a_expected is nullptr or a_expected_count is 0, no verification is performed.
	 * @note If a_expected_count > a_count, verification fails and logs a warning (safety check).
	 * @note If a_expected_count < a_count, partial verification is performed with a debug log.
	 */
	bool safe_write(std::uintptr_t a_dst, const void* a_src, std::size_t a_count, const void* a_expected, std::size_t a_expected_count);

	/**
	 * @brief Write data to memory with verification using a byte array.
	 * 
	 * Template overload that automatically calculates the expected size from the array.
	 * 
	 * @tparam N Size of the expected byte array (automatically deduced)
	 * @param a_dst The destination memory address
	 * @param a_src Pointer to the source data
	 * @param a_count Number of bytes to write
	 * @param a_expected Reference to expected byte array
	 * @return true if verification passed and write was successful, false otherwise
	 */
	template <std::size_t N>
	bool safe_write(std::uintptr_t a_dst, const void* a_src, std::size_t a_count, const std::uint8_t (&a_expected)[N])
	{
		return safe_write(a_dst, a_src, a_count, a_expected, N);
	}

	template <std::size_t N>
	bool safe_write(std::uintptr_t a_dst, const void* a_src, std::size_t a_count, const std::array<std::uint8_t, N>& a_expected)
	{
		return safe_write(a_dst, a_src, a_count, a_expected.data(), N);
	}

	template <std::integral T>
	void safe_write(std::uintptr_t a_dst, const T& a_data)
	{
		safe_write(a_dst, std::addressof(a_data), sizeof(T));
	}

	template <std::integral T, std::size_t N>
	bool safe_write(std::uintptr_t a_dst, const T& a_data, const std::uint8_t (&a_expected)[N])
	{
		return safe_write(a_dst, std::addressof(a_data), sizeof(T), a_expected, N);
	}

	template <std::integral T, std::size_t N>
	bool safe_write(std::uintptr_t a_dst, const T& a_data, const std::array<std::uint8_t, N>& a_expected)
	{
		return safe_write(a_dst, std::addressof(a_data), sizeof(T), a_expected.data(), N);
	}

	template <std::ranges::contiguous_range R>
	void safe_write(std::uintptr_t a_dst, R&& a_data)
	{
		safe_write(
			a_dst,
			std::ranges::data(a_data),
			std::ranges::size(a_data) * sizeof(std::ranges::range_value_t<R>));
	}

	template <class T>
	void safe_write(std::uintptr_t a_dst, std::span<T> a_data)
	{
		safe_write(a_dst, a_data.data(), a_data.size_bytes());
	}

	template <class T, std::size_t N>
	bool safe_write(std::uintptr_t a_dst, std::span<T> a_data, const std::uint8_t (&a_expected)[N])
	{
		return safe_write(a_dst, a_data.data(), a_data.size_bytes(), a_expected, N);
	}

	template <class T, std::size_t N>
	bool safe_write(std::uintptr_t a_dst, std::span<T> a_data, const std::array<std::uint8_t, N>& a_expected)
	{
		return safe_write(a_dst, a_data.data(), a_data.size_bytes(), a_expected.data(), N);
	}

	/**
	 * @brief Fill memory with a specified value (without verification).
	 * 
	 * Temporarily changes memory protection to PAGE_EXECUTE_READWRITE, performs the fill,
	 * then restores the original protection.
	 * 
	 * @param a_dst The destination memory address
	 * @param a_value The byte value to fill the memory with
	 * @param a_count Number of bytes to fill
	 * 
	 * @warning This function does NOT verify memory contents before filling.
	 *          Consider using safe_fill with verification for production code.
	 * @note Define REL_AUDIT_UNVERIFIED_PATCHES to log unverified patch locations.
	 */
#ifdef REL_AUDIT_UNVERIFIED_PATCHES
	[[deprecated("Consider using safe_fill with verification - define REL_AUDIT_UNVERIFIED_PATCHES to track usage")]]
#endif
	void safe_fill(std::uintptr_t a_dst, std::uint8_t a_value, std::size_t a_count);

	/**
	 * @brief Fill memory with a value with optional code verification.
	 * 
	 * First verifies that the target memory contains expected bytes (if provided),
	 * then performs the fill operation if verification passes. Uses safe_fill internally.
	 * 
	 * @param a_dst The destination memory address
	 * @param a_value The value to fill the memory with
	 * @param a_count Number of bytes to fill
	 * @param a_expected Pointer to expected bytes at the destination (optional)
	 * @param a_expected_count Number of expected bytes to verify (optional)
	 * @return true if verification passed and fill was successful, false otherwise
	 * 
	 * @note If a_expected is nullptr or a_expected_count is 0, no verification is performed.
	 * @note If a_expected_count > a_count, verification fails and logs a warning (safety check).
	 * @note If a_expected_count < a_count, partial verification is performed with a debug log.
	 */
	bool safe_fill(std::uintptr_t a_dst, std::uint8_t a_value, std::size_t a_count, const void* a_expected, std::size_t a_expected_count);

	// Template overloads that automatically calculate expected size
	template <std::size_t N>
	bool safe_fill(std::uintptr_t a_dst, std::uint8_t a_value, std::size_t a_count, const std::uint8_t (&a_expected)[N])
	{
		return safe_fill(a_dst, a_value, a_count, a_expected, N);
	}

	template <std::size_t N>
	bool safe_fill(std::uintptr_t a_dst, std::uint8_t a_value, std::size_t a_count, const std::array<std::uint8_t, N>& a_expected)
	{
		return safe_fill(a_dst, a_value, a_count, a_expected.data(), N);
	}

	/**
	 * @brief Verify that memory contains expected bytes.
	 * 
	 * Performs a byte-by-byte comparison using memcmp.
	 * 
	 * @param a_address The memory address to verify
	 * @param a_expected Pointer to expected bytes
	 * @param a_count Number of bytes to compare
	 * @return true if the memory matches the expected bytes, false otherwise
	 * 
	 * @note If a_expected is nullptr or a_count is 0, the function returns true (no verification needed).
	 */
	bool verify_code(std::uintptr_t a_address, const void* a_expected, std::size_t a_count);

	template <std::size_t N>
	bool verify_code(std::uintptr_t a_address, const std::array<std::uint8_t, N>& a_expected)
	{
		return verify_code(a_address, a_expected.data(), N);
	}

	template <std::size_t N>
	bool verify_code(std::uintptr_t a_address, const std::uint8_t (&a_expected)[N])
	{
		return verify_code(a_address, a_expected, N);
	}

	/**
	 * @brief Verify memory using a PatternMatcher.
	 * 
	 * This function uses CommonLibSSE-NG's PatternMatcher to verify memory contents.
	 * 
	 * @param a_address The memory address to verify
	 * @param a_pattern The PatternMatcher object to use for verification
	 * @return true if the memory matches the pattern, false otherwise
	 */
	template <typename Pattern>
	bool verify_code(std::uintptr_t a_address, const Pattern& a_pattern)
	{
		return a_pattern.match(a_address);
	}

	/**
	 * @brief Write data to memory with PatternMatcher verification.
	 * 
	 * This function verifies memory using a PatternMatcher before writing data.
	 * 
	 * @param a_dst The destination memory address
	 * @param a_src Pointer to the source data
	 * @param a_count Number of bytes to write
	 * @param a_pattern The PatternMatcher object to use for verification
	 * @return true if verification passed and write was successful, false otherwise
	 */
	template <typename Pattern>
	bool safe_write(std::uintptr_t a_dst, const void* a_src, std::size_t a_count, const Pattern& a_pattern)
	{
		if (!verify_code(a_dst, a_pattern)) {
			return false;  // Pattern verification failed
		}

		// Perform the safe write
		safe_write(a_dst, a_src, a_count);
		return true;
	}

	/**
	 * @brief Fill memory with PatternMatcher verification.
	 * 
	 * This function verifies memory using a PatternMatcher before filling.
	 * 
	 * @param a_dst The destination memory address
	 * @param a_value The value to fill with
	 * @param a_count Number of bytes to fill
	 * @param a_pattern The PatternMatcher object to use for verification
	 * @return true if verification passed and fill was successful, false otherwise
	 */
	template <typename Pattern>
	bool safe_fill(std::uintptr_t a_dst, std::uint8_t a_value, std::size_t a_count, const Pattern& a_pattern)
	{
		if (!verify_code(a_dst, a_pattern)) {
			return false;  // Pattern verification failed
		}

		// Perform the safe fill
		safe_fill(a_dst, a_value, a_count);
		return true;
	}

	/**
	 * @brief Write data to memory with optional verification (legacy function).
	 * 
	 * This is a legacy wrapper that calls the newer safe_write with verification.
	 * Consider using safe_write(dst, src, count, expected, expected_count) directly.
	 * 
	 * @param a_dst The destination memory address
	 * @param a_src Pointer to the source data
	 * @param a_count Number of bytes to write
	 * @param a_expected Pointer to expected bytes (optional, defaults to nullptr)
	 * @param a_expected_count Number of expected bytes (optional, defaults to 0)
	 * @return true if verification passed and write was successful, false otherwise
	 */
	bool safe_write_verify(std::uintptr_t a_dst, const void* a_src, std::size_t a_count, const void* a_expected = nullptr, std::size_t a_expected_count = 0);

	template <std::integral T>
	bool safe_write_verify(std::uintptr_t a_dst, const T& a_data, const void* a_expected = nullptr, std::size_t a_expected_count = 0)
	{
		return safe_write_verify(a_dst, std::addressof(a_data), sizeof(T), a_expected, a_expected_count);
	}

	template <class T>
	bool safe_write_verify(std::uintptr_t a_dst, std::span<T> a_data, const void* a_expected = nullptr, std::size_t a_expected_count = 0)
	{
		return safe_write_verify(a_dst, a_data.data(), a_data.size_bytes(), a_expected, a_expected_count);
	}

	/**
	 * @brief Fill memory with optional verification (legacy function).
	 * 
	 * This is a legacy wrapper that calls the newer safe_fill with verification.
	 * Consider using safe_fill(dst, value, count, expected, expected_count) directly.
	 * 
	 * @param a_dst The destination memory address
	 * @param a_value The value to fill with
	 * @param a_count Number of bytes to fill
	 * @param a_expected Pointer to expected bytes (optional, defaults to nullptr)
	 * @param a_expected_count Number of expected bytes (optional, defaults to 0)
	 * @return true if verification passed and fill was successful, false otherwise
	 */
	bool safe_fill_verify(std::uintptr_t a_dst, std::uint8_t a_value, std::size_t a_count, const void* a_expected = nullptr, std::size_t a_expected_count = 0);

	/**
	 * @brief Code verification utilities for memory patching using PatternMatcher.
	 * 
	 * This namespace provides utility macros for safely verifying memory contents
	 * before applying patches using CommonLibSSE-NG's PatternMatcher system.
	 */
	namespace CodeVerification
	{
		/**
		 * @brief Helper function to verify multiple patch points using PatternMatcher.
		 * 
		 * Uses fold expressions to check that all verification operations succeed.
		 * 
		 * @tparam Args The types of the verification results
		 * @param args The verification results (should be bool values)
		 * @return true if all verifications passed, false if any failed
		 */
		template <typename... Args>
		bool verify_multiple_patches(Args&&... args)
		{
			return (args && ...);
		}
	}

/**
	 * @brief Macro to verify and patch using PatternMatcher.
	 * 
	 * Verifies expected pattern at the target address using PatternMatcher, then applies the patch.
	 * Returns false from the calling function if verification fails.
	 * 
	 * @param address The target memory address
	 * @param patch_data The data to write
	 * @param pattern The PatternMatcher object
	 * @param description Human-readable description (currently unused)
	 * 
	 * @warning This macro contains a 'return false' statement. Use only in functions returning bool.
	 * @note No logging is performed. Add manual logging if needed.
	 * 
	 * @example
	 * @code
	 * auto pattern = make_pattern<"48 8B 05 F9 AA 10 00">();
	 * VERIFY_AND_PATCH(address, patch_data, pattern, "CopyResource hook");
	 * @endcode
	 */
#define VERIFY_AND_PATCH(address, patch_data, pattern, description)               \
	do {                                                                          \
		if (!REL::safe_write(address, patch_data, sizeof(patch_data), pattern)) { \
			/* Note: Requires logger to be available in calling scope */          \
			return false;                                                         \
		}                                                                         \
	} while (0)

/**
	 * @brief Macro to verify and fill using PatternMatcher.
	 * 
	 * Verifies expected pattern at the target address using PatternMatcher, then fills with the specified value.
	 * Returns false from the calling function if verification fails.
	 * 
	 * @param address The target memory address
	 * @param fill_value The value to fill with
	 * @param fill_size Number of bytes to fill
	 * @param pattern The PatternMatcher object
	 * @param description Human-readable description (currently unused)
	 * 
	 * @warning This macro contains a 'return false' statement. Use only in functions returning bool.
	 * @note No logging is performed. Add manual logging if needed.
	 * 
	 * @example
	 * @code
	 * auto pattern = make_pattern<"48 8B 05 F9 AA 10 00">();
	 * VERIFY_AND_FILL(address, REL::NOP, 7, pattern, "CopyResource hook");
	 * @endcode
	 */
#define VERIFY_AND_FILL(address, fill_value, fill_size, pattern, description) \
	do {                                                                      \
		if (!REL::safe_fill(address, fill_value, fill_size, pattern)) {       \
			/* Note: Requires logger to be available in calling scope */      \
			return false;                                                     \
		}                                                                     \
	} while (0)

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

		template <std::ptrdiff_t O = 0>
		void replace_func(const std::size_t a_count, const std::uintptr_t a_dst)
			requires(std::same_as<value_type, std::uintptr_t>)
		{
#pragma pack(push, 1)
			struct Assembly
			{
				std::uint8_t  jmp;
				std::uint8_t  modrm;
				std::int32_t  disp;
				std::uint64_t addr;
			};
			static_assert(sizeof(Assembly) == 0xE);
#pragma pack(pop)

			Assembly assembly{
				.jmp = static_cast<std::uint8_t>(0xFF),
				.modrm = static_cast<std::uint8_t>(0x25),
				.disp = static_cast<std::int32_t>(0),
				.addr = static_cast<std::uint64_t>(a_dst),
			};

			safe_fill(address() + O, INT3, a_count);
			safe_write(address() + O, &assembly, sizeof(assembly));
		}

		template <std::ptrdiff_t O = 0, class F>
		void replace_func(const std::size_t a_count, const F a_dst)
			requires(std::same_as<value_type, std::uintptr_t>)
		{
			replace_func<O>(a_count, stl::unrestricted_cast<std::uintptr_t>(a_dst));
		}

		template <std::integral U>
		void write(const U& a_data)
			requires(std::same_as<value_type, std::uintptr_t>)
		{
			safe_write(address(), std::addressof(a_data), sizeof(U));
		}

		template <class U>
		void write(const std::span<U> a_data)
			requires(std::same_as<value_type, std::uintptr_t>)
		{
			safe_write(address(), a_data.data(), a_data.size_bytes());
		}

		// a_skipSafetyCheck/a_expectedPatchHash/a_loc: see SKSE::Trampoline::write_branch.
		template <std::size_t N>
		std::uintptr_t write_branch(const std::uintptr_t a_dst, bool a_skipSafetyCheck = false, std::uint64_t a_expectedPatchHash = 0, std::source_location a_loc = std::source_location::current())
			requires(std::same_as<value_type, std::uintptr_t>)
		{
			return SKSE::GetTrampoline().write_branch<N>(address(), a_dst, a_skipSafetyCheck, a_expectedPatchHash, a_loc);
		}

		template <std::size_t N, class F>
		std::uintptr_t write_branch(const F a_dst, bool a_skipSafetyCheck = false, std::uint64_t a_expectedPatchHash = 0, std::source_location a_loc = std::source_location::current())
			requires(std::same_as<value_type, std::uintptr_t>)
		{
			return SKSE::GetTrampoline().write_branch<N>(address(), stl::unrestricted_cast<std::uintptr_t>(a_dst), a_skipSafetyCheck, a_expectedPatchHash, a_loc);
		}

		template <std::size_t N>
		std::uintptr_t write_call(const std::uintptr_t a_dst, bool a_skipSafetyCheck = false, std::uint64_t a_expectedPatchHash = 0, std::source_location a_loc = std::source_location::current())
			requires(std::same_as<value_type, std::uintptr_t>)
		{
			return SKSE::GetTrampoline().write_call<N>(address(), a_dst, a_skipSafetyCheck, a_expectedPatchHash, a_loc);
		}

		template <std::size_t N, class F>
		std::uintptr_t write_call(const F a_dst, bool a_skipSafetyCheck = false, std::uint64_t a_expectedPatchHash = 0, std::source_location a_loc = std::source_location::current())
			requires(std::same_as<value_type, std::uintptr_t>)
		{
			return SKSE::GetTrampoline().write_call<N>(address(), stl::unrestricted_cast<std::uintptr_t>(a_dst), a_skipSafetyCheck, a_expectedPatchHash, a_loc);
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
		std::uintptr_t write_vfunc(const std::size_t a_idx, const F a_newFunc)
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
#	pragma warning(push)
#	pragma warning(disable: 4702)  // unreachable code in single-runtime builds
		switch (Module::get().GetRuntime()) {
		case Module::Runtime::AE:
			return a_ae;
		case Module::Runtime::VR:
			return a_vr;
		default:
			return a_se;
		}
#	pragma warning(pop)
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
#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable: 4702)  // unreachable code
#endif
	template <class T, class This>
	[[nodiscard]] inline T& RelocateMember(This* a_self, std::ptrdiff_t a_seAndAE, std::ptrdiff_t a_vr)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(a_self) + Relocate(a_seAndAE, a_seAndAE, a_vr));
	}
#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

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

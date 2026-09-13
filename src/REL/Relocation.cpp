#include "REL/Relocation.h"

#include "REX/W32/KERNEL32.h"
#include "SKSE/Logger.h"

namespace REL
{
	void safe_write(std::uintptr_t a_dst, const void* a_src, std::size_t a_count)
	{
#ifdef REL_AUDIT_UNVERIFIED_PATCHES
		SKSE::log::warn("AUDIT: Unverified safe_write at address {:x} ({} bytes) - consider adding verification", a_dst, a_count);
#endif

		std::uint32_t old{ 0 };
		bool          success = REX::W32::VirtualProtect(
            reinterpret_cast<void*>(a_dst), a_count, REX::W32::PAGE_EXECUTE_READWRITE, std::addressof(old));
		if (success) {
			std::memcpy(reinterpret_cast<void*>(a_dst), a_src, a_count);
			success = REX::W32::VirtualProtect(
				reinterpret_cast<void*>(a_dst), a_count, old, std::addressof(old));
		}

		assert(success);
	}

	void safe_fill(std::uintptr_t a_dst, std::uint8_t a_value, std::size_t a_count)
	{
#ifdef REL_AUDIT_UNVERIFIED_PATCHES
		SKSE::log::warn("AUDIT: Unverified safe_fill at address {:x} ({} bytes, value {:02x}) - consider adding verification", a_dst, a_count, a_value);
#endif

		std::uint32_t old{ 0 };
		bool          success = REX::W32::VirtualProtect(
            reinterpret_cast<void*>(a_dst), a_count, REX::W32::PAGE_EXECUTE_READWRITE, std::addressof(old));
		if (success) {
			std::fill_n(reinterpret_cast<std::uint8_t*>(a_dst), a_count, a_value);
			success = REX::W32::VirtualProtect(
				reinterpret_cast<void*>(a_dst), a_count, old, std::addressof(old));
		}

		assert(success);
	}

	bool verify_code(std::uintptr_t a_address, const void* a_expected, std::size_t a_count)
	{
		if (!a_expected || a_count == 0) {
			return true;  // No verification needed
		}

		return std::memcmp(reinterpret_cast<const void*>(a_address), a_expected, a_count) == 0;
	}

	bool safe_write(std::uintptr_t a_dst, const void* a_src, std::size_t a_count, const void* a_expected, std::size_t a_expected_count)
	{
		// Verify expected code if provided
		if (a_expected && a_expected_count > 0) {
			// Safety check: don't verify more bytes than we're replacing
			if (a_expected_count > a_count) {
				// This is a safety issue - we're trying to verify more than we're replacing
				SKSE::log::warn("Code verification size mismatch: verifying {} bytes but only replacing {} bytes at {:x}",
					a_expected_count, a_count, a_dst);
				return false;
			}

			// Warn if we're replacing more than we're verifying (but continue)
			if (a_expected_count < a_count) {
				// This is acceptable but worth noting for debugging
				SKSE::log::debug("Code verification partial: verifying {} bytes but replacing {} bytes at {:x}",
					a_expected_count, a_count, a_dst);
			}

			if (!verify_code(a_dst, a_expected, a_expected_count)) {
				return false;  // Code verification failed
			}
		}

		// Perform the safe write
		safe_write(a_dst, a_src, a_count);
		return true;
	}

	bool safe_fill(std::uintptr_t a_dst, std::uint8_t a_value, std::size_t a_count, const void* a_expected, std::size_t a_expected_count)
	{
		// Verify expected code if provided
		if (a_expected && a_expected_count > 0) {
			// Safety check: don't verify more bytes than we're replacing
			if (a_expected_count > a_count) {
				// This is a safety issue - we're trying to verify more than we're replacing
				SKSE::log::warn("Code verification size mismatch: verifying {} bytes but only replacing {} bytes at {:x}",
					a_expected_count, a_count, a_dst);
				return false;
			}

			// Warn if we're replacing more than we're verifying (but continue)
			if (a_expected_count < a_count) {
				// This is acceptable but worth noting for debugging
				SKSE::log::debug("Code verification partial: verifying {} bytes but replacing {} bytes at {:x}",
					a_expected_count, a_count, a_dst);
			}

			if (!verify_code(a_dst, a_expected, a_expected_count)) {
				return false;  // Code verification failed
			}
		}

		// Perform the safe fill
		safe_fill(a_dst, a_value, a_count);
		return true;
	}
}

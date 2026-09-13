#include "REL/Verify.h"

#include "SKSE/Logger.h"

namespace REL
{
	std::uint64_t HashBytes(std::uintptr_t a_addr, std::size_t a_len) noexcept
	{
		constexpr std::uint64_t offsetBasis = 0xCBF29CE484222325ULL;
		constexpr std::uint64_t prime = 0x00000100000001B3ULL;

		auto       hash = offsetBasis;
		const auto bytes = reinterpret_cast<const std::uint8_t*>(a_addr);
		for (std::size_t i = 0; i < a_len; ++i) {
			hash ^= bytes[i];
			hash *= prime;
		}
		return hash;
	}

	VerifyResult VerifyBytes(std::uintptr_t a_addr, std::size_t a_len, std::uint64_t a_expectedHash,
		std::string_view a_context, std::source_location a_loc)
	{
		const auto file = detail::basename(a_loc);
		const auto hash = HashBytes(a_addr, a_len);

		if (a_expectedHash == 0) {
			SKSE::log::debug(
				"hook verification [{}:{}]: {} at 0x{:X} ({} bytes) hash 0x{:X} -- pass "
				"a_expectedHash=0x{:X} to pin this state (re-checked every launch)."sv,
				file, a_loc.line(), a_context, a_addr, a_len, hash, hash);
			return VerifyResult::kUnset;
		}

		if (a_expectedHash == hash) {
			SKSE::log::trace(
				"hook verification [{}:{}]: {} at 0x{:X} matches its pinned hash 0x{:X} -- "
				"already verified, nothing changed."sv,
				file, a_loc.line(), a_context, a_addr, hash);
			return VerifyResult::kMatch;
		}

		SKSE::log::warn(
			"hook verification [{}:{}]: {} at 0x{:X} pinned hash 0x{:X} no longer matches the "
			"live bytes (now 0x{:X}) -- the verification this relied on may no longer hold (a "
			"different game binary, or another patch now overlapping this range)."sv,
			file, a_loc.line(), a_context, a_addr, a_expectedHash, hash);
		return VerifyResult::kMismatch;
	}
}

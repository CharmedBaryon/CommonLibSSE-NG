#pragma once

#include "REL/Module.h"

namespace REL
{
	class Offset
	{
	public:
		constexpr Offset() noexcept = default;

		explicit constexpr Offset(std::size_t a_offset) noexcept :
			_offset(a_offset)
		{}

		constexpr Offset& operator=(std::size_t a_offset) noexcept
		{
			_offset = a_offset;
			return *this;
		}

		[[nodiscard]] std::uintptr_t address() const { return base() + offset(); }

		[[nodiscard]] constexpr std::size_t offset() const noexcept { return _offset; }

	private:
		[[nodiscard]] static std::uintptr_t base() { return Module::get().base(); }

		std::size_t _offset{ 0 };
	};

	class VariantOffset
	{
	public:
		constexpr VariantOffset() noexcept = default;

		explicit constexpr VariantOffset(
			[[maybe_unused]] std::size_t a_seOffset,
			[[maybe_unused]] std::size_t a_aeOffset,
			[[maybe_unused]] std::size_t a_vrOffset) noexcept
		{
#ifdef ENABLE_SKYRIM_SE
			_seOffset = a_seOffset;
#endif
#ifdef ENABLE_SKYRIM_AE
			_aeOffset = a_aeOffset;
#endif
#ifdef ENABLE_SKYRIM_VR
			_vrOffset = a_vrOffset;
#endif
		}

		[[nodiscard]] std::uintptr_t address() const
		{
			auto thisOffset = offset();
			return thisOffset ? base() + thisOffset : 0;
		}

		[[nodiscard]] SKYRIM_REL std::size_t offset() const noexcept
		{
			switch (Module::GetRuntime()) {
#ifdef ENABLE_SKYRIM_AE
			case Module::Runtime::AE:
				return _aeOffset;
#endif
#ifdef ENABLE_SKYRIM_SE
			case Module::Runtime::SE:
				return _seOffset;
#endif
#ifdef ENABLE_SKYRIM_VR
			case Module::Runtime::VR:
				return _vrOffset;
#endif
			default:
				return 0;
			}
		}

		[[nodiscard]] SKYRIM_REL explicit operator Offset() const noexcept { return Offset(offset()); }

	private:
		[[nodiscard]] static std::uintptr_t base() { return Module::get().base(); }

#ifdef ENABLE_SKYRIM_SE
		std::size_t _seOffset{ 0 };
#endif
#ifdef ENABLE_SKYRIM_AE
		std::size_t _aeOffset{ 0 };
#endif
#ifdef ENABLE_SKYRIM_VR
		std::size_t _vrOffset{ 0 };
#endif
	};
}

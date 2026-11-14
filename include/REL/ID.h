#pragma once

#include "REL/IDDB.h"
#include "REL/Module.h"

namespace REL
{
	class ID
	{
	public:
		constexpr ID() noexcept = default;

		explicit constexpr ID(std::uint64_t a_id) noexcept :
			_id(a_id)
		{}

		constexpr ID& operator=(std::uint64_t a_id) noexcept
		{
			_id = a_id;
			return *this;
		}

		[[nodiscard]] std::uintptr_t address() const { return base() + offset(); }

		[[nodiscard]] constexpr std::uint64_t id() const noexcept { return _id; }

		[[nodiscard]] std::size_t offset() const { return IDDB::get().id2offset(_id); }

	private:
		[[nodiscard]] static std::uintptr_t base() { return Module::get().base(); }

		std::uint64_t _id{ 0 };
	};

	class RelocationID
	{
	public:
		constexpr RelocationID() noexcept = default;

		explicit constexpr RelocationID(
			[[maybe_unused]] std::uint64_t a_seID,
			[[maybe_unused]] std::uint64_t a_aeID) noexcept
		{
#ifdef ENABLE_SKYRIM_SE
			_seID = a_seID;
#endif
#ifdef ENABLE_SKYRIM_AE
			_aeID = a_aeID;
#endif
#ifdef ENABLE_SKYRIM_VR
			_vrID = a_seID;
#endif
		}

		explicit constexpr RelocationID(
			[[maybe_unused]] std::uint64_t a_seID,
			[[maybe_unused]] std::uint64_t a_aeID,
			[[maybe_unused]] std::uint64_t a_vrID) noexcept
		{
#ifdef ENABLE_SKYRIM_SE
			_seID = a_seID;
#endif
#ifdef ENABLE_SKYRIM_AE
			_aeID = a_aeID;
#endif
#ifdef ENABLE_SKYRIM_VR
			_vrID = a_vrID;
#endif
		}

		[[nodiscard]] std::uintptr_t address() const
		{
			auto thisOffset = offset();
			return thisOffset ? base() + thisOffset : 0;
		}

		[[nodiscard]] std::size_t offset() const
		{
			auto thisID = id();
			return thisID ? IDDB::get().id2offset(thisID) : 0;
		}

		[[nodiscard]] SKYRIM_REL std::uint64_t id() const noexcept
		{
			switch (Module::GetRuntime()) {
#ifdef ENABLE_SKYRIM_AE
			case Module::Runtime::AE:
				return _aeID;
#endif
#ifdef ENABLE_SKYRIM_SE
			case Module::Runtime::SE:
				return _seID;
#endif
#ifdef ENABLE_SKYRIM_VR
			case Module::Runtime::VR:
				return _vrID;
#endif
			default:
				return 0;
			}
		}

		[[nodiscard]] SKYRIM_REL explicit operator ID() const noexcept
		{
			return ID(id());
		}

	private:
		[[nodiscard]] static std::uintptr_t base() { return Module::get().base(); }

#ifdef ENABLE_SKYRIM_SE
		std::uint64_t _seID{ 0 };
#endif
#ifdef ENABLE_SKYRIM_AE
		std::uint64_t _aeID{ 0 };
#endif
#ifdef ENABLE_SKYRIM_VR
		std::uint64_t _vrID{ 0 };
#endif
	};

	class VariantID
	{
	public:
		constexpr VariantID() noexcept = default;

		explicit constexpr VariantID(
			[[maybe_unused]] std::uint64_t a_seID,
			[[maybe_unused]] std::uint64_t a_aeID,
			[[maybe_unused]] std::uint64_t a_vrOffset) noexcept
		{
#ifdef ENABLE_SKYRIM_SE
			_seID = a_seID;
#endif
#ifdef ENABLE_SKYRIM_AE
			_aeID = a_aeID;
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

		[[nodiscard]] std::size_t offset() const
		{
			switch (Module::GetRuntime()) {
#ifdef ENABLE_SKYRIM_AE
			case Module::Runtime::AE:
				return _aeID ? IDDB::get().id2offset(_aeID) : 0;
#endif
#ifdef ENABLE_SKYRIM_SE
			case Module::Runtime::SE:
				return _seID ? IDDB::get().id2offset(_seID) : 0;
#endif
#ifdef ENABLE_SKYRIM_VR
			case Module::Runtime::VR:
				return _vrOffset;
#endif
			default:
				return 0;
			}
		}

	private:
		[[nodiscard]] static std::uintptr_t base() { return Module::get().base(); }

#ifdef ENABLE_SKYRIM_SE
		std::uint64_t _seID{ 0 };
#endif
#ifdef ENABLE_SKYRIM_AE
		std::uint64_t _aeID{ 0 };
#endif
#ifdef ENABLE_SKYRIM_VR
		std::uint64_t _vrOffset{ 0 };
#endif
	};
}

#pragma once

#include "RE/E/ErrorCodes.h"
#include "RE/M/MemoryManager.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	namespace BSResource
	{
		struct Info;

		class StreamBase
		{
		public:
			inline static constexpr auto RTTI = RTTI_BSResource__StreamBase;
			inline static constexpr auto VTABLE = VTABLE_BSResource__StreamBase;

			enum : std::uint32_t
			{
				kWritable = 1 << 0,
				kRefCountBeg = 0x1000,
				kRefCountMask = (std::uint32_t)0xFFFFF000
			};

			StreamBase();
			StreamBase(const StreamBase& a_rhs);
			StreamBase(StreamBase&& a_rhs);
			StreamBase(std::uint32_t a_totalSize);
			virtual ~StreamBase() = default;  // 00

			// add
			virtual ErrorCode                   DoOpen() = 0;             // 01
			virtual void                        DoClose() = 0;            // 02
			[[nodiscard]] virtual std::uint64_t DoGetKey() const;         // 03 - { return 0; }
			virtual ErrorCode                   DoGetInfo(Info& a_info);  // 04 - { return ErrorCode::kUnsupported; }

			TES_HEAP_REDEFINE_NEW();

			std::uint32_t      DecRef();
			std::uint32_t      IncRef();
			[[nodiscard]] bool IsWritable() const;

			// AE-only; compiler-widened zero padding from totalSize's store, not
			// real data, but still shifts the ref-count field's offset below.
			struct AE_RUNTIME_DATA
			{
#define AE_RUNTIME_DATA_CONTENT \
	std::uint32_t pad0C;  // 0C - confirmed always-zero, not real data
				AE_RUNTIME_DATA_CONTENT
			};
			static_assert(sizeof(AE_RUNTIME_DATA) == 0x4);

			AE_ONLY_POINTER_ACCESSOR(AE_RUNTIME_DATA, GetAERuntimeData, 0xC);

			// AE's pad0C shifts flags's real offset from 0xC (SE/VR) to 0x10 (AE);
			// use GetFlags(), not the bare member, so cross-runtime builds resolve correctly.
			[[nodiscard]] inline std::uint32_t& GetFlags() noexcept
			{
				if SKYRIM_REL_CONSTEXPR (REL::Module::IsAE()) {
					return *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this) + 0x10);
				} else {
					return *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this) + 0xC);
				}
			}

			[[nodiscard]] inline const std::uint32_t& GetFlags() const noexcept
			{
				if SKYRIM_REL_CONSTEXPR (REL::Module::IsAE()) {
					return *reinterpret_cast<const std::uint32_t*>(reinterpret_cast<const std::uint8_t*>(this) + 0x10);
				} else {
					return *reinterpret_cast<const std::uint32_t*>(reinterpret_cast<const std::uint8_t*>(this) + 0xC);
				}
			}

			// members
			std::uint32_t totalSize;  // 08
#ifdef ENABLE_SKYRIM_AE
			AE_RUNTIME_DATA_CONTENT;
#endif
#if defined(ENABLE_SKYRIM_AE) && !defined(EXCLUSIVE_SKYRIM_AE)
			// This build mixes AE with SE and/or VR, so a single fixed offset for
			// this field can't be correct for every runtime -- direct access is
			// disabled here; only GetFlags() resolves the real per-runtime offset.
		private:
#endif
			std::uint32_t flags;  // 10 (0xC on SE/VR; see GetFlags())
		};
#undef AE_RUNTIME_DATA_CONTENT
#ifdef ENABLE_SKYRIM_AE
		static_assert(sizeof(StreamBase) == 0x18);
#else
		static_assert(sizeof(StreamBase) == 0x10);
#endif
	}
}

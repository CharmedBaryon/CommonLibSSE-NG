#pragma once

namespace RE
{
	class BSTask
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSTask;
		inline static constexpr auto VTABLE = VTABLE_BSTask;

		virtual ~BSTask() = default;  // 00

		// add
		virtual void Run() = 0;                                                                               // 01
		virtual void Finish() = 0;                                                                            // 02
		virtual void Cancel([[maybe_unused]] std::uint32_t a_previousState, [[maybe_unused]] void* a_unk) {}  // 03
		virtual bool GetDescription(char* a_dest, std::uint32_t a_maxCount);                                  // 04 - writes "Unnamed", returns false

		void IncRefCount()
		{
			stl::atomic_ref myRefCount{ refCount };
			++myRefCount;
		}

		void DecRefCount()
		{
			stl::atomic_ref myRefCount{ refCount };
			if (--myRefCount == 0) {
				delete this;
			}
		}

		// members
		volatile std::int32_t refCount;  // 08
		std::uint32_t         unk0C;     // 0C
		std::uint8_t          unk10[2];  // 10
		std::uint8_t          priority;  // 12 - task priority/type byte
		std::uint8_t          unk13[5];  // 13
#if defined(EXCLUSIVE_SKYRIM_VR)
		std::uint8_t unk18[8];  // 18 - VR only; byte 0 is zeroed at construction
#endif
	};
	STATIC_ASSERT_SIZE(BSTask, 0x18, 0x20);
}

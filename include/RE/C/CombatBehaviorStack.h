#pragma once

#include "RE/B/BSTArray.h"

namespace RE
{
	class CombatBehaviorStack
	{
	public:
		class ObjectPtr
		{
		public:
			template <typename T>
			T* GetObject()
			{
				return stack ? &stack->Access<T>(frame) : nullptr;
			}

			template <typename T>
			const T* GetObject() const
			{
				return stack ? &stack->Access<T>(frame) : nullptr;
			}

			// members
			CombatBehaviorStack* stack;  // 00
			std::uint32_t        frame;  // 08 - Stack frame offset
			std::uint32_t        pad0C;  // 0C
		};
		static_assert(sizeof(ObjectPtr) == 0x10);

		template <typename T, typename... Args>
		ObjectPtr Allocate(Args&&... args)
		{
			ObjectPtr result{ this, size, 0 };

			std::uint32_t newSize = size + sizeof(T);
			CheckBuffer(newSize);
			std::uint32_t oldSize = size;
			size = newSize;
			new (&buffer[oldSize]) T(std::forward<Args>(args)...);
			return result;
		}

		template <typename T>
		void Deallocate()
		{
			size -= sizeof(T);
			reinterpret_cast<T*>(&buffer[size])->~T();
		}

		template <typename T>
		void StoreData(const T& a_obj)
		{
			std::uint32_t oldSize = size;
			std::uint32_t newSize = size + sizeof(T);
			CheckBuffer(newSize);
			size = newSize;
			new (&buffer[oldSize]) T(a_obj);
		}

		template <typename T>
		T& Access(std::uint32_t a_offset)
		{
			return *reinterpret_cast<T*>(&buffer[a_offset]);
		}

		template <typename T>
		const T& Access(std::uint32_t a_offset) const
		{
			return *reinterpret_cast<const T*>(&buffer[a_offset]);
		}

		void CheckBuffer(std::uint32_t a_size);

		// members
		char*         buffer;      // 00
		std::uint32_t bufferSize;  // 08
		std::uint32_t size;        // 0C
	};
	static_assert(sizeof(CombatBehaviorStack) == 0x10);
}

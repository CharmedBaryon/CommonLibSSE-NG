#pragma once

namespace REX
{
	template <class T>
	class Singleton
	{
	public:
		static T* GetSingleton()
		{
			static T singleton;
			return std::addressof(singleton);
		}

	protected:
		Singleton() = default;
		~Singleton() = default;

		Singleton(const Singleton&) = delete;
		Singleton(Singleton&&) = delete;

		Singleton& operator=(const Singleton&) = delete;
		Singleton& operator=(Singleton&&) = delete;
	};
}

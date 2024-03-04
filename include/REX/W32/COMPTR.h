#pragma once

#include "REX/W32/BASE.h"

namespace REX::W32
{
	// based on Microsoft::WRL::ComPtr
	template <class T>
	struct ComPtr
	{
		constexpr ComPtr() noexcept = default;
		constexpr ComPtr(std::nullptr_t) noexcept {}

		ComPtr(const ComPtr& a_other) noexcept :
			_ptr(a_other._ptr)
		{
			TryAddRef();
		}

		template <class U>
		ComPtr(U* a_other) noexcept :
			_ptr(a_other)
		{
			TryAddRef();
		}

		~ComPtr() noexcept
		{
			TryRelease();
		}

		ComPtr& operator=(std::nullptr_t) noexcept
		{
			TryRelease();
			return *this;
		}

		ComPtr& operator=(T* a_other) noexcept
		{
			if (_ptr != a_other)
				ComPtr(a_other).Swap(*this);

			return *this;
		}

		template <class U>
		ComPtr& operator=(U* a_other) noexcept
		{
			ComPtr(a_other).Swap(*this);
			return *this;
		}

		ComPtr& operator=(const ComPtr& a_other) noexcept
		{
			if (_ptr != a_other._ptr)
				ComPtr(a_other).Swap(*this);

			return *this;
		}

		template <class U>
		ComPtr& operator=(const ComPtr<U>& a_other) noexcept
		{
			ComPtr(a_other).Swap(*this);
			return *this;
		}

		ComPtr& operator=(ComPtr&& a_other) noexcept
		{
			ComPtr(static_cast<ComPtr&&>(a_other)).Swap(*this);
			return *this;
		}

		template <class U>
		ComPtr& operator=(ComPtr<U>&& a_other) noexcept
		{
			ComPtr(static_cast<ComPtr<U>&&>(a_other)).Swap(*this);
			return *this;
		}

		T* operator->() const noexcept
		{
			return _ptr;
		}

		void Attach(T* a_other) noexcept
		{
			if (_ptr != nullptr) {
				[[maybe_unused]] auto ref = _ptr->Release();
				assert((ref != 0) || (_ptr != a_other));
			}

			_ptr = a_other;
		}

		T* Detach() noexcept
		{
			T* ptr = _ptr;
			_ptr = nullptr;
			return ptr;
		}

		T* Get() const noexcept
		{
			return _ptr;
		}

		T** GetAddressOf() noexcept
		{
			return &_ptr;
		}

		T* const* GetAddressOf() const noexcept
		{
			return &_ptr;
		}

		T** ReleaseAndGetAddressOf() noexcept
		{
			TryRelease();
			return &_ptr;
		}

		std::uint32_t Reset() noexcept
		{
			return TryRelease();
		}

		void Swap(ComPtr& a_other) noexcept
		{
			T* ptr = _ptr;
			_ptr = a_other._ptr;
			a_other._ptr = ptr;
		}

		void Swap(ComPtr&& a_other) noexcept
		{
			T* ptr = _ptr;
			_ptr = a_other._ptr;
			a_other._ptr = ptr;
		}

		template <class U>
		HRESULT As(ComPtr<U>* a_ptr) const noexcept
		{
			return _ptr->QueryInterface(__uuidof(U), reinterpret_cast<void**>(a_ptr->ReleaseAndGetAddressOf()));
		}

		template <class U>
		HRESULT AsIID(const IID& a_iid, ComPtr<U>* a_ptr) const noexcept
		{
			return _ptr->QueryInterface(a_iid, reinterpret_cast<void**>(a_ptr->ReleaseAndGetAddressOf()));
		}

		HRESULT CopyTo(const IID& a_iid, void** a_ptr) const noexcept
		{
			return _ptr->QueryInterface(a_iid, a_ptr);
		}

		HRESULT CopyTo(T** a_ptr) const noexcept
		{
			TryAddRef();
			*a_ptr = _ptr;
			return 0;
		}

		template <class U>
		HRESULT CopyTo(U** a_ptr) const noexcept
		{
			return _ptr->QueryInterface(__uuidof(U), reinterpret_cast<void**>(a_ptr));
		}

	protected:
		template <class U>
		friend struct ComPtr;

		void TryAddRef() const noexcept
		{
			if (_ptr)
				_ptr->AddRef();
		}

		std::uint32_t TryRelease() noexcept
		{
			T* ptr = _ptr;
			if (ptr) {
				_ptr = nullptr;
				return ptr->Release();
			}

			return 0;
		}

		T* _ptr{ nullptr };
	};
}

#include "RE/H/hkStringPtr.h"

namespace RE
{
	hkStringPtr::hkStringPtr(const char* a_data) :
		_data(nullptr)
	{
		using func_t = std::add_pointer_t<void(hkStringPtr&, const char*)>;
		static REL::Relocation<func_t> func{ RELOCATION_ID(56801, 57231) };
		func(*this, a_data);
	}

	const char* hkStringPtr::data() const noexcept
	{
		return reinterpret_cast<const char*>(reinterpret_cast<std::uintptr_t>(_data) & ~kManaged);
	}

	const char* hkStringPtr::c_str() const noexcept
	{
		return data();
	}

	bool hkStringPtr::empty() const noexcept
	{
		return !_data || _data[0] == '\0';
	}

	auto hkStringPtr::size() const
		-> size_type
	{
		return static_cast<size_type>(std::strlen(data()));
	}

	auto hkStringPtr::length() const
		-> size_type
	{
		return size();
	}
}

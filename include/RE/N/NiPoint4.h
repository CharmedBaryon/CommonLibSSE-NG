#pragma once

namespace RE
{
	class NiPoint4
	{
	public:
		constexpr NiPoint4() noexcept = default;

		constexpr NiPoint4(float a_x, float a_y, float a_z, float a_w) noexcept :
			x(a_x),
			y(a_y),
			z(a_z),
			w(a_w) {}

		float x{ 0.0F };  // 0
		float y{ 0.0F };  // 4
		float z{ 0.0F };  // 8
		float w{ 0.0F };  // C
	};
	static_assert(sizeof(NiPoint4) == 0x10);
}

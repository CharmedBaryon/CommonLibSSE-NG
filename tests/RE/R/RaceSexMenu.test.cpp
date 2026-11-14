#include "catch2/catch_all.hpp"

#include "RE/R/RaceSexMenu.h"

#include <cstddef>

namespace
{
	template <class T>
	concept HasEmbeddedCamera = requires(T& a_menu) { a_menu.camera; };

	template <class T>
	concept HasHeadParts = requires(T& a_menu) { a_menu.headParts; };

	template <class T>
	concept HasSliderData = requires(T& a_menu) { a_menu.sliderData; };
}

TEST_CASE("RaceSexMenu/RuntimeDataLayouts", "[unit][race-sex-menu]")
{
	using FlatData = RE::RaceSexMenu::RUNTIME_DATA;
	using VRData = RE::RaceSexMenu::VR_RUNTIME_DATA;

	CHECK(sizeof(FlatData) == 0x168);
	CHECK(offsetof(FlatData, headParts) == 0x0);
	CHECK(offsetof(FlatData, camera) == 0xA8);
	CHECK(offsetof(FlatData, sliderData) == 0x100);
	CHECK(offsetof(FlatData, unk170) == 0x130);
	CHECK(offsetof(FlatData, raceIndex) == 0x148);
	CHECK(offsetof(FlatData, sex) == 0x158);
	CHECK(offsetof(FlatData, unk1A4) == 0x164);

	CHECK(sizeof(VRData) == 0x110);
	CHECK(offsetof(VRData, headParts) == 0x0);
	CHECK(offsetof(VRData, sliderData) == 0xA8);
	CHECK(offsetof(VRData, unk170) == 0xD8);
	CHECK(offsetof(VRData, raceIndex) == 0xF0);
	CHECK(offsetof(VRData, sex) == 0x100);
	CHECK(offsetof(VRData, unk1A4) == 0x10C);
	CHECK_FALSE(HasEmbeddedCamera<VRData>);
}

TEST_CASE("RaceSexMenu/DirectMemberLayout", "[unit][race-sex-menu]")
{
	using Menu = RE::RaceSexMenu;
#ifdef SKYRIM_CROSS_VR
	CHECK(sizeof(Menu) == 0x30);
	CHECK_FALSE(HasEmbeddedCamera<Menu>);
	CHECK_FALSE(HasHeadParts<Menu>);
	CHECK_FALSE(HasSliderData<Menu>);
#else
#	ifdef EXCLUSIVE_SKYRIM_VR
	using Data = Menu::VR_RUNTIME_DATA;
	constexpr std::size_t runtimeDataOffset = 0x50;
	CHECK_FALSE(HasEmbeddedCamera<Menu>);
#	else
	using Data = Menu::RUNTIME_DATA;
	constexpr std::size_t runtimeDataOffset = 0x40;
	CHECK(offsetof(Menu, camera) == runtimeDataOffset + offsetof(Data, camera));
#	endif
	CHECK(sizeof(Menu) == runtimeDataOffset + sizeof(Data));
	CHECK(offsetof(Menu, headParts) == runtimeDataOffset);
	CHECK(offsetof(Menu, sliderData) == runtimeDataOffset + offsetof(Data, sliderData));
	CHECK(offsetof(Menu, unk170) == runtimeDataOffset + offsetof(Data, unk170));
	CHECK(offsetof(Menu, raceIndex) == runtimeDataOffset + offsetof(Data, raceIndex));
	CHECK(offsetof(Menu, sex) == runtimeDataOffset + offsetof(Data, sex));
	CHECK(offsetof(Menu, unk1A4) == runtimeDataOffset + offsetof(Data, unk1A4));
#endif
}

#include "catch2/catch_all.hpp"

#include "RE/B/BSInputEventQueue.h"
#include "REL/REL.h"
#include "SKSE/SKSE.h"

#include <array>
#include <cstdint>
#include <cstring>
#include <tuple>

#if defined(SKYRIM_CROSS_VR)
namespace
{
	void ReleaseEmptyString(const char*& a_string)
	{
		CHECK(a_string == nullptr);
		a_string = nullptr;
	}

	struct QueueFixture
	{
		QueueFixture(REL::Version a_version, REL::Module::Runtime a_runtime)
		{
			const auto base = reinterpret_cast<std::uintptr_t>(&ReleaseEmptyString) - 0x1000;
			REQUIRE(REL::Module::mock(a_version, a_runtime, L"InputQueueTest.exe", base));
			// Keep the stub table separate from a running game's shared mapping.
			REQUIRE(REL::IDDB::inject(L"Data\\SKSE\\Plugins\\input-queue.csv", REL::IDDB::Format::VR, REL::Version{}));
		}

		~QueueFixture()
		{
			REL::IDDB::reset();
			REL::Module::reset();
		}

		alignas(8) std::array<std::byte, 0x580> storage{};
	};
}

TEST_CASE("BSInputEventQueue/ButtonCache", "[unit][input-queue]")
{
	using Runtime = REL::Module::Runtime;
	const auto [version, runtime, first, stride, head] = GENERATE(
		std::tuple{ SKSE::RUNTIME_SSE_1_5_97, Runtime::SE, 0x20, 0x30, 0x380 },
		std::tuple{ SKSE::RUNTIME_SSE_1_6_1170, Runtime::AE, 0x20, 0x30, 0x380 },
		std::tuple{ SKSE::RUNTIME_SSE_1_6_1179, Runtime::AE, 0x20, 0x30, 0x380 },
		std::tuple{ SKSE::RUNTIME_SSE_1_7_99, Runtime::AE, 0x28, 0x30, 0x558 },
		std::tuple{ REL::Version{ 1, 7, 104, 0 }, Runtime::AE, 0x28, 0x30, 0x558 },
		std::tuple{ SKSE::RUNTIME_VR_1_4_15, Runtime::VR, 0x28, 0x38, 0x570 });
	CAPTURE(version.string());
	QueueFixture fixture(version, runtime);
	auto*        queue = reinterpret_cast<RE::BSInputEventQueue*>(fixture.storage.data());
	auto**       expectedHead = reinterpret_cast<RE::InputEvent**>(fixture.storage.data() + head);
	auto**       expectedTail = expectedHead + 1;
	REQUIRE(&queue->GetQueueHead() == expectedHead);
	REQUIRE(&queue->GetQueueTail() == expectedTail);

	RE::InputEvent* previous = nullptr;
	for (int i = 0; i < 10; ++i) {
		auto*      expected = reinterpret_cast<RE::ButtonEvent*>(fixture.storage.data() + first + i * stride);
		const auto duration = static_cast<float>(i) / 10.0F;
		queue->AddButtonEvent(RE::INPUT_DEVICE::kKeyboard, i + 17, 1.0F, duration);
		REQUIRE(queue->buttonEventCount == static_cast<std::uint32_t>(i + 1));
		REQUIRE(*expectedTail == expected);
		REQUIRE(*expectedHead == reinterpret_cast<RE::InputEvent*>(fixture.storage.data() + first));
		if (previous) {
			CHECK(previous->next == expected);
		}
		CHECK(expected->next == nullptr);
		CHECK(expected->device == RE::INPUT_DEVICE::kKeyboard);
		CHECK(expected->GetIDCode() == static_cast<std::uint32_t>(i + 17));
		CHECK(expected->Value() == 1.0F);
		CHECK(expected->HeldDuration() == duration);
		std::uint32_t id;
		float         value;
		float         held;
		const auto*   bytes = fixture.storage.data() + first + i * stride;
		std::memcpy(&id, bytes + 0x20, sizeof(id));
		std::memcpy(&value, bytes + stride - 8, sizeof(value));
		std::memcpy(&held, bytes + stride - 4, sizeof(held));
		CHECK(id == static_cast<std::uint32_t>(i + 17));
		CHECK(value == 1.0F);
		CHECK(held == duration);
		previous = expected;
	}

	const auto full = fixture.storage;
	queue->AddButtonEvent(RE::INPUT_DEVICE::kKeyboard, 99, 0.0F, 1.0F);
	CHECK(fixture.storage == full);
	queue->ClearInputQueue();
	CHECK(queue->buttonEventCount == 0);
	CHECK(*expectedHead == nullptr);
	CHECK(*expectedTail == nullptr);
	queue->AddButtonEvent(RE::INPUT_DEVICE::kKeyboard, 7, std::uint16_t{ 17 }, 0.0F, 0.5F);
	REQUIRE(queue->buttonEventCount == 1);
	REQUIRE(*expectedHead == reinterpret_cast<RE::InputEvent*>(fixture.storage.data() + first));
	CHECK(*expectedTail == *expectedHead);
	CHECK(static_cast<RE::ButtonEvent*>(*expectedHead)->IsUp());
	CHECK(static_cast<RE::ButtonEvent*>(*expectedHead)->GetIDCode() == 17);
	CHECK((*expectedHead)->next == nullptr);
	if (runtime == Runtime::VR) {
		CHECK(static_cast<RE::ButtonEvent*>(*expectedHead)->AsVRWandEvent()->unkVR28 == 7);
	}
}

TEST_CASE("BSInputEventQueue/SiblingCaches", "[unit][input-queue]")
{
	using Runtime = REL::Module::Runtime;
	const auto [version, runtime, charBase, charStride, mouseBase, thumbBase, thumbStride, connectBase] = GENERATE(
		std::tuple{ SKSE::RUNTIME_SSE_1_5_97, Runtime::SE, 0x200, 0x20, 0x2A0, 0x2D0, 0x30, 0x330 },
		std::tuple{ SKSE::RUNTIME_SSE_1_6_1170, Runtime::AE, 0x200, 0x20, 0x2A0, 0x2D0, 0x30, 0x330 },
		std::tuple{ REL::Version{ 1, 7, 104, 0 }, Runtime::AE, 0x208, 0x20, 0x2A8, 0x2D8, 0x30, 0x338 },
		std::tuple{ SKSE::RUNTIME_VR_1_4_15, Runtime::VR, 0x258, 0x20, 0x2F8, 0x328, 0x30, 0x388 });
	CAPTURE(version.string());
	QueueFixture fixture(version, runtime);
	auto*        queue = reinterpret_cast<RE::BSInputEventQueue*>(fixture.storage.data());
	auto**       tail = &queue->GetQueueTail();

	for (int i = 0; i < 5; ++i) {
		auto* expected = reinterpret_cast<RE::InputEvent*>(fixture.storage.data() + charBase + i * charStride);
		queue->AddCharEvent(static_cast<std::uint32_t>('a' + i));
		REQUIRE(queue->charEventCount == static_cast<std::uint32_t>(i + 1));
		CHECK(*tail == expected);
	}

	for (int i = 0; i < 2; ++i) {
		auto* expected = reinterpret_cast<RE::InputEvent*>(fixture.storage.data() + thumbBase + i * thumbStride);
		queue->AddThumbstickEvent(RE::ThumbstickEvent::InputTypes::kLeftThumbstick, 0.5F, 0.25F);
		REQUIRE(queue->thumbstickEventCount == static_cast<std::uint32_t>(i + 1));
		CHECK(*tail == expected);
	}

	{
		auto* expected = reinterpret_cast<RE::InputEvent*>(fixture.storage.data() + mouseBase);
		queue->AddMouseMoveEvent(1, 2);
		REQUIRE(queue->mouseEventCount == 1);
		CHECK(*tail == expected);
	}

	{
		auto* expected = reinterpret_cast<RE::InputEvent*>(fixture.storage.data() + connectBase);
		queue->AddConnectEvent(RE::INPUT_DEVICE::kKeyboard, true);
		REQUIRE(queue->connectEventCount == 1);
		CHECK(*tail == expected);
	}
}

TEST_CASE("BSInputEventQueue/KinectAndTouchpad", "[unit][input-queue]")
{
	using Runtime = REL::Module::Runtime;
	const auto [version, runtime, kinectBase, touchpadBase] = GENERATE(
		std::tuple{ SKSE::RUNTIME_SSE_1_5_97, Runtime::SE, 0x350, 0 },
		std::tuple{ SKSE::RUNTIME_SSE_1_6_1170, Runtime::AE, 0x350, 0 },
		std::tuple{ REL::Version{ 1, 7, 104, 0 }, Runtime::AE, 0x358, 0 },
		std::tuple{ SKSE::RUNTIME_VR_1_4_15, Runtime::VR, 0x3A8, 0x3D8 });
	CAPTURE(version.string());
	QueueFixture fixture(version, runtime);
	auto*        queue = reinterpret_cast<RE::BSInputEventQueue*>(fixture.storage.data());
	auto**       tail = &queue->GetQueueTail();

	auto* expected = reinterpret_cast<RE::InputEvent*>(fixture.storage.data() + kinectBase);
	queue->AddKinectEvent(RE::BSFixedString{ "userEvent" }, RE::BSFixedString{ "heard" });
	REQUIRE(queue->kinectEventCount == 1);
	CHECK(*tail == expected);

	if (runtime == Runtime::VR) {
		CHECK(reinterpret_cast<std::byte*>(queue->GetVRTouchpadEventData()) ==
			  fixture.storage.data() + touchpadBase);
	} else {
		CHECK(queue->GetVRTouchpadEventData() == nullptr);
	}
}
#endif

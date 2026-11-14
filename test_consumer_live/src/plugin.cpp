#include <spdlog/sinks/basic_file_sink.h>

#include <utility>
#include <vector>

// Live-verification harness for RE::detail::VtableShimBase-style adapters
// (currently: RE::MenuEventHandlerEx). See README.md.

#ifndef RUN_BROKEN_COMPARISON
// Off by default: reproducing the broken path deliberately crashes the
// game. Set to 1 (or pass -DRUN_BROKEN_COMPARISON=1) to also run it.
#	define RUN_BROKEN_COMPARISON 0
#endif

namespace
{
	void SetupLog()
	{
		auto logsFolder = SKSE::log::log_directory();
		if (!logsFolder) {
			SKSE::stl::report_and_fail("no log dir");
		}
		auto path = *logsFolder / "CommonLibSSELiveVerify.log";
		auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path.string(), true);
		auto logger = std::make_shared<spdlog::logger>("log", std::move(fileSink));
		spdlog::set_default_logger(std::move(logger));
		spdlog::set_level(spdlog::level::trace);
		spdlog::flush_on(spdlog::level::trace);
	}

	// The fixed path: a real, genuinely overridable derived class.
	class TestHandler : public RE::MenuEventHandlerEx
	{
	public:
		bool sawCanProcess = false;
		bool sawProcessButton = false;

		bool CanProcess(RE::InputEvent*) override
		{
			sawCanProcess = true;
			SKSE::log::info("TestHandler::CanProcess called (typed dispatch through shim vtable)");
			return true;
		}

		bool ProcessButton(RE::ButtonEvent*) override
		{
			sawProcessButton = true;
			SKSE::log::info("TestHandler::ProcessButton called");
			return true;
		}
	};

#if RUN_BROKEN_COMPARISON
	// The broken path this harness exists to catch: CanProcess is still a real
	// pure virtual and overrides normally, but ProcessButton is not, so this
	// can only be a same-named non-virtual method -- what a plugin author
	// forced to drop `override` ends up writing.
	class BrokenHandler : public RE::MenuEventHandler
	{
	public:
		bool sawProcessButton = false;

		bool CanProcess(RE::InputEvent*) override { return true; }

		bool ProcessButton(RE::ButtonEvent*)
		{
			sawProcessButton = true;
			SKSE::log::info("BrokenHandler::ProcessButton called (should be unreachable via real dispatch)");
			return true;
		}
	};
#endif

	HMODULE ModuleOf(void* a_addr)
	{
		HMODULE hm = nullptr;
		GetModuleHandleExA(
			GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
			reinterpret_cast<LPCSTR>(a_addr), &hm);
		return hm;
	}

	// The real engine's fixed vtable slot for ProcessButton on the current
	// runtime, mirroring MenuEventHandlerEx's own runtime detection.
	int RealProcessButtonSlot()
	{
		if SKYRIM_REL_VR_CONSTEXPR (REL::Module::IsVR()) {
			return 8;
		}
#ifdef ENABLE_SKYRIM_AE
		if (REL::Module::IsAtLeast(SKSE::RUNTIME_SSE_1_7_99)) {
			return 7;
		}
#endif
		return 5;
	}

	// Every other real slot patched by MenuEventHandlerEx on this runtime,
	// none of which TestHandler overrides -- must fall through to its
	// default `{ return false; }` bodies rather than crash or return garbage.
	std::vector<std::pair<const char*, int>> RealNonButtonSlots()
	{
		if SKYRIM_REL_VR_CONSTEXPR (REL::Module::IsVR()) {
			// slot 4 (Unk_04) intentionally excluded -- not exposed as an override point.
			return { { "ProcessVrWandTouchpadSwipe", 2 }, { "ProcessVrWandTouchpadPosition", 3 },
				{ "ProcessKinect", 5 }, { "ProcessThumbstick", 6 }, { "ProcessMouseMove", 7 } };
		}
#ifdef ENABLE_SKYRIM_AE
		if (REL::Module::IsAtLeast(SKSE::RUNTIME_SSE_1_7_99)) {
			return { { "ProcessMotionGesture", 2 }, { "ProcessSixaxis", 3 }, { "ProcessKinect", 4 },
				{ "ProcessThumbstick", 5 }, { "ProcessMouseMove", 6 } };
		}
#endif
		return { { "ProcessKinect", 2 }, { "ProcessThumbstick", 3 }, { "ProcessMouseMove", 4 } };
	}

	void RunSelfTest()
	{
		SKSE::log::info("=== MenuEventHandlerEx live self-test starting ===");

		TestHandler           handler;
		RE::MenuEventHandler* h = handler.Handler();
		SKSE::log::info("Handler() = {:x}", reinterpret_cast<std::uintptr_t>(h));

		auto vtbl = *reinterpret_cast<void***>(h);
		SKSE::log::info("shim vtbl = {:x}", reinterpret_cast<std::uintptr_t>(vtbl));

		HMODULE gameModule = GetModuleHandleA(nullptr);
		HMODULE pluginModule = ModuleOf(reinterpret_cast<void*>(&RunSelfTest));
		SKSE::log::info("game module = {:x}, plugin module = {:x}",
			reinterpret_cast<std::uintptr_t>(gameModule), reinterpret_cast<std::uintptr_t>(pluginModule));

		int realSlotCount;
		if SKYRIM_REL_VR_CONSTEXPR (REL::Module::IsVR()) {
			realSlotCount = 9;
		}
#ifdef ENABLE_SKYRIM_AE
		else if (REL::Module::IsAtLeast(SKSE::RUNTIME_SSE_1_7_99)) {
			realSlotCount = 8;
		}
#endif
		else {
			realSlotCount = 6;
		}
		for (int i = 0; i < realSlotCount; ++i) {
			void*       slot = vtbl[i];
			HMODULE     owner = ModuleOf(slot);
			const char* which = owner == gameModule ? "GAME" : (owner == pluginModule ? "PLUGIN" : "UNKNOWN");
			SKSE::log::info("slot[{}] = {:x} ({})", i, reinterpret_cast<std::uintptr_t>(slot), which);
		}

		bool typedCanProcess = h->CanProcess(nullptr);
		SKSE::log::info("typed h->CanProcess(nullptr) = {}, sawCanProcess = {}", typedCanProcess, handler.sawCanProcess);

		handler.sawProcessButton = false;
		int buttonSlot = RealProcessButtonSlot();
		using RawFn = bool (*)(void*, RE::ButtonEvent*);
		auto rawSlotFn = reinterpret_cast<RawFn>(vtbl[buttonSlot]);
		bool rawResult = rawSlotFn(h, nullptr);
		bool sawRawProcessButton = handler.sawProcessButton;
		SKSE::log::info(
			"raw vtbl[{}](h, nullptr) [simulating real engine dispatch] = {}, sawProcessButton = {}",
			buttonSlot, rawResult, sawRawProcessButton);

		handler.sawProcessButton = false;
		bool typedButtonResult = h->ProcessButton(nullptr);
		bool sawTypedProcessButton = handler.sawProcessButton;
		SKSE::log::info("typed h->ProcessButton(nullptr) = {}, sawProcessButton = {}",
			typedButtonResult, sawTypedProcessButton);

		bool nonButtonOk = true;
		using RawFn2 = bool (*)(void*, void*);
		for (auto [name, slot] : RealNonButtonSlots()) {
			auto rawFn = reinterpret_cast<RawFn2>(vtbl[slot]);
			bool result = rawFn(h, nullptr);
			SKSE::log::info("raw vtbl[{}] ({}, unoverridden) = {}", slot, name, result);
			nonButtonOk = nonButtonOk && !result;
		}
		bool typedKinect = h->ProcessKinect(nullptr);
		bool typedThumbstick = h->ProcessThumbstick(nullptr);
		bool typedMouseMove = h->ProcessMouseMove(nullptr);
		SKSE::log::info("typed h->ProcessKinect/Thumbstick/MouseMove(nullptr) = {}/{}/{}",
			typedKinect, typedThumbstick, typedMouseMove);
		nonButtonOk = nonButtonOk && !typedKinect && !typedThumbstick && !typedMouseMove;
#ifdef ENABLE_SKYRIM_AE
		if (REL::Module::IsAtLeast(SKSE::RUNTIME_SSE_1_7_99)) {
			bool typedMotionGesture = h->ProcessMotionGesture(nullptr);
			bool typedSixaxis = h->ProcessSixaxis(nullptr);
			SKSE::log::info("typed h->ProcessMotionGesture/ProcessSixaxis(nullptr) = {}/{}",
				typedMotionGesture, typedSixaxis);
			nonButtonOk = nonButtonOk && !typedMotionGesture && !typedSixaxis;
		}
#endif
		if SKYRIM_REL_VR_CONSTEXPR (REL::Module::IsVR()) {
			bool typedSwipe = h->ProcessVrWandTouchpadSwipe(nullptr);
			bool typedPosition = h->ProcessVrWandTouchpadPosition(nullptr);
			SKSE::log::info("typed h->ProcessVrWandTouchpadSwipe/Position(nullptr) = {}/{}",
				typedSwipe, typedPosition);
			nonButtonOk = nonButtonOk && !typedSwipe && !typedPosition;
		}

		const auto& ti = typeid(*h);
		SKSE::log::info("typeid(*h).name() = {}", ti.name());

		bool pass = handler.sawCanProcess && typedCanProcess && rawResult && sawRawProcessButton &&
		            typedButtonResult && sawTypedProcessButton && nonButtonOk;
		SKSE::log::info("=== MenuEventHandlerEx live self-test {} ===", pass ? "PASSED" : "FAILED");
	}

	// Registers with the real MenuControls and injects a real RE::ButtonEvent
	// through RE::BSInputDeviceManager::SendEvent, the same entry point real
	// hardware input uses. The nonsense user-event name keeps this inert to
	// every other real handler on MenuControls's list.
	void RunEndToEndTest()
	{
		SKSE::log::info("=== MenuEventHandlerEx end-to-end (real MenuControls + real InputEvent) starting ===");

		auto* mc = RE::MenuControls::GetSingleton();
		auto* idm = RE::BSInputDeviceManager::GetSingleton();
		if (!mc || !idm) {
			SKSE::log::info("=== end-to-end SKIPPED: MenuControls/BSInputDeviceManager not ready ({}/{}) ===",
				reinterpret_cast<std::uintptr_t>(mc), reinterpret_cast<std::uintptr_t>(idm));
			return;
		}

		TestHandler handler;
		mc->RegisterHandler(handler.Handler());

		auto* buttonEvent = RE::ButtonEvent::Create(
			RE::INPUT_DEVICE::kKeyboard, "zzCommonLibSSELiveVerify_unbound", 0, 1.0F, 0.0F);
		if (!buttonEvent) {
			SKSE::log::info("=== end-to-end FAILED: ButtonEvent::Create returned null ===");
			mc->RemoveHandler(handler.Handler());
			return;
		}

		RE::InputEvent* events = buttonEvent;
		idm->SendEvent(&events);

		mc->RemoveHandler(handler.Handler());

		SKSE::log::info("=== MenuEventHandlerEx end-to-end {} === (sawCanProcess={}, sawProcessButton={})",
			(handler.sawCanProcess && handler.sawProcessButton) ? "PASSED" : "FAILED",
			handler.sawCanProcess, handler.sawProcessButton);
	}

#if RUN_BROKEN_COMPARISON
	// Reproduces the original crash for a controlled before/after: the real
	// engine's fixed-slot dispatch (simulated exactly as above) against a
	// plugin's shortened, compiler-generated vtable. This WILL crash the
	// game -- that's the point.
	void RunBrokenComparison()
	{
		SKSE::log::info("=== broken (pre-MenuEventHandlerEx) comparison starting ===");

		BrokenHandler broken;
		auto          vtbl = *reinterpret_cast<void***>(&broken);
		SKSE::log::info("BrokenHandler vtbl = {:x}", reinterpret_cast<std::uintptr_t>(vtbl));

		HMODULE gameModule = GetModuleHandleA(nullptr);
		HMODULE pluginModule = ModuleOf(reinterpret_cast<void*>(&RunBrokenComparison));
		for (int i = 0; i < 2; ++i) {
			void*       slot = vtbl[i];
			HMODULE     owner = ModuleOf(slot);
			const char* which = owner == gameModule ? "GAME" : (owner == pluginModule ? "PLUGIN" : "UNKNOWN");
			SKSE::log::info("BrokenHandler slot[{}] = {:x} ({})", i, reinterpret_cast<std::uintptr_t>(slot), which);
		}

		int         buttonSlot = RealProcessButtonSlot();
		void*       overrunSlot = vtbl[buttonSlot];
		HMODULE     owner = ModuleOf(overrunSlot);
		const char* which = owner == gameModule ? "GAME" : (owner == pluginModule ? "PLUGIN" : "UNKNOWN");
		SKSE::log::info(
			"BrokenHandler vtbl[{}] (real ProcessButton slot the engine would call) = {:x} ({}) -- reading {} bytes past a 2-slot vtable",
			buttonSlot, reinterpret_cast<std::uintptr_t>(overrunSlot), which, (buttonSlot - 1) * 8);

		SKSE::log::info("calling it now, simulating the real engine's blind dispatch -- expect a crash if #324's mechanism is real");
		using RawFn = bool (*)(void*, RE::ButtonEvent*);
		auto rawSlotFn = reinterpret_cast<RawFn>(overrunSlot);
		bool result = rawSlotFn(&broken, nullptr);
		SKSE::log::info("did NOT crash: vtbl[{}](&broken, nullptr) = {}, sawProcessButton = {}",
			buttonSlot, result, broken.sawProcessButton);
	}
#endif

	void OnMessage(SKSE::MessagingInterface::Message* a_msg)
	{
		if (a_msg->type == SKSE::MessagingInterface::kDataLoaded) {
			SKSE::log::info("kDataLoaded received");
			RunSelfTest();
			RunEndToEndTest();
#if RUN_BROKEN_COMPARISON
			RunBrokenComparison();
#endif
		}
	}
}

SKSEPluginLoad(const SKSE::LoadInterface* a_skse)
{
	SetupLog();
	SKSE::Init(a_skse);
	if (!SKSE::GetMessagingInterface()->RegisterListener(OnMessage)) {
		SKSE::stl::report_and_fail("Failed to register message listener");
		return false;
	}
	SKSE::log::info("CommonLibSSELiveVerify loaded (RUN_BROKEN_COMPARISON={})", RUN_BROKEN_COMPARISON);
	return true;
}

#include "catch2/catch_all.hpp"

#include "REL/REL.h"
#include "SKSE/SKSE.h"

namespace
{
	class TrampolineFixture
	{
	public:
		static constexpr std::size_t TrampolineSize = 64;

		TrampolineFixture()
		{
			_successPtr = &_success;
            REQUIRE(REL::Module::inject(REL::Module::Runtime::Unknown));
		}

		~TrampolineFixture()
		{
			_successPtr = nullptr;
			REL::Module::reset();
		}

	protected:
		void TestTrampoline(SKSE::Trampoline& trampoline)
		{
			// Not necessarily the same function in each runtime, but bit-for-bit identical.
			REL::VariantID FunctionID(102625, 110073, 0x0);
			REL::Relocation<std::uint64_t(void*)> Function(FunctionID);
			REL::Relocation<void(void*)> Call(FunctionID, 0x4);
			trampoline.write_call<6>(Call.address(), &TestHook);
			Function(nullptr);
			REQUIRE(_success);
		}

	private:
		static void TestHook(void*)
		{
			*_successPtr = true;
		}

		static inline bool* _successPtr{ nullptr };
		bool _success{ false };
	};
}

TEST_CASE_METHOD(TrampolineFixture, "Trampoline/DefaultTrampoline", "[.][integration]")
{
	auto& trampoline = SKSE::GetTrampoline();
	trampoline.create(TrampolineSize);
	TestTrampoline(trampoline);
}

TEST_CASE_METHOD(TrampolineFixture, "Trampoline/CustomTrampoline", "[.][integration]")
{
	SKSE::Trampoline trampoline;
	trampoline.create(TrampolineSize);
	TestTrampoline(trampoline);
}

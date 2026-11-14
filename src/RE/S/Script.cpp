#include "RE/S/Script.h"

#include "RE/M/MemoryManager.h"
#include "SKSE/Version.h"

namespace RE
{
	bool Script::GetProcessScripts()
	{
		using func_t = decltype(&Script::GetProcessScripts);
		static REL::Relocation<func_t> func{ RELOCATION_ID(21436, 21921) };
		return func();
	}

	void Script::SetProcessScripts(bool a_ProcessScripts)
	{
		using func_t = decltype(&Script::SetProcessScripts);
		static REL::Relocation<func_t> func{ RELOCATION_ID(21435, 21920) };
		return func(a_ProcessScripts);
	}

	void Script::ClearCommand()
	{
		if (text) {
			free(text);
			text = nullptr;
		}
	}

	void Script::CompileAndRun(TESObjectREFR* a_targetRef, COMPILER_NAME a_name)
	{
		ScriptCompiler compiler;
		CompileAndRun_Impl(&compiler, a_name, a_targetRef);
	}

	void Script::CompileAndRun(ScriptCompiler* a_compiler, TESObjectREFR* a_targetRef, COMPILER_NAME a_name)
	{
		CompileAndRun_Impl(a_compiler, a_name, a_targetRef);
	}

	std::string Script::GetCommand() const
	{
		return text ? text : "";
	}

	void Script::SetCommand(std::string_view a_command)
	{
		if (text) {
			free(text);
		}

		text = malloc<char>(a_command.length() + 1);
		std::memcpy(text, a_command.data(), a_command.length());
		text[a_command.length()] = '\0';
	}

	void Script::CompileAndRun_Impl(ScriptCompiler* a_compiler, COMPILER_NAME a_name, TESObjectREFR* a_targetRef)
	{
		using func_t = decltype(&Script::CompileAndRun_Impl);
		static REL::Relocation<func_t> func{ RELOCATION_ID(21416, AE_CHECK(SKSE::RUNTIME_SSE_1_6_1130, 21890, 441582)) };
		return func(this, a_compiler, a_name, a_targetRef);
	}
}

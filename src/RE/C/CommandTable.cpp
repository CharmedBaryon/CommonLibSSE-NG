#include "RE/C/CommandTable.h"

namespace RE
{
	auto SCRIPT_FUNCTION::Chunk::AsString()
		-> StringChunk*
	{
		return static_cast<StringChunk*>(this);
	}

	auto SCRIPT_FUNCTION::Chunk::AsInteger()
		-> IntegerChunk*
	{
		return static_cast<IntegerChunk*>(this);
	}

	std::string SCRIPT_FUNCTION::StringChunk::GetString() const
	{
		return length ? std::string(str, length) : "";
	}

	auto SCRIPT_FUNCTION::StringChunk::GetNext()
		-> Chunk*
	{
		return reinterpret_cast<Chunk*>(str + length);
	}

	int SCRIPT_FUNCTION::IntegerChunk::GetInteger() const
	{
		return *(int*)((std::uintptr_t)this + 1);
	}

	auto SCRIPT_FUNCTION::IntegerChunk::GetNext()
		-> Chunk*
	{
		return reinterpret_cast<Chunk*>(this + 1);
	}

	auto SCRIPT_FUNCTION::ScriptData::GetChunk()
		-> Chunk*
	{
		return reinterpret_cast<Chunk*>(this + 1);
	}

	auto SCRIPT_FUNCTION::ScriptData::GetStringChunk()
		-> StringChunk*
	{
		return static_cast<StringChunk*>(GetChunk());
	}

	auto SCRIPT_FUNCTION::ScriptData::GetIntegerChunk()
		-> IntegerChunk*
	{
		return static_cast<IntegerChunk*>(GetChunk());
	}

	SCRIPT_FUNCTION* SCRIPT_FUNCTION::GetFirstScriptCommand()
	{
		REL::Relocation<SCRIPT_FUNCTION*> ptr{ RELOCATION_ID(501789, 361120) };
		return ptr.get();
	}

	SCRIPT_FUNCTION* SCRIPT_FUNCTION::LocateScriptCommand(std::string_view a_longName)
	{
		auto scriptCommands = GetFirstScriptCommand();
		for (std::uint16_t i = 0; i < Commands::kScriptCommandsEnd; ++i) {
			if (a_longName.size() == strlen(scriptCommands[i].functionName) &&
				_strnicmp(scriptCommands[i].functionName, a_longName.data(), a_longName.size()) == 0) {
				return &scriptCommands[i];
			}
		}
		return nullptr;
	}

	SCRIPT_FUNCTION* SCRIPT_FUNCTION::GetFirstConsoleCommand()
	{
		REL::Relocation<SCRIPT_FUNCTION*> ptr{ RELOCATION_ID(501797, 365650) };
		return ptr.get();
	}

	SCRIPT_FUNCTION* SCRIPT_FUNCTION::LocateConsoleCommand(std::string_view a_longName)
	{
		auto consoleCommands = GetFirstConsoleCommand();
		for (std::uint16_t i = 0; i < Commands::kConsoleCommandsEnd; ++i) {
			if (a_longName.size() == strlen(consoleCommands[i].functionName) &&
				_strnicmp(consoleCommands[i].functionName, a_longName.data(), a_longName.size()) == 0) {
				return &consoleCommands[i];
			}
		}
		return nullptr;
	}

	void SCRIPT_FUNCTION::SetParameters()
	{
		numParams = 0;
		params = nullptr;
	}
}

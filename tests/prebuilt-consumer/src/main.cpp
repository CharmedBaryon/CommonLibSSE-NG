#include <cstdint>

#include <SKSE/SKSE.h>

// The commonlibsse-ng.plugin rule adds the generated SKSE plugin declaration; this
// translation unit additionally forces the linker to resolve an out-of-line symbol
// from the prebuilt static library, so a successful build proves real linkage (not
// merely that the headers parse). Never executed.
extern "C" __declspec(dllexport) std::uint32_t commonlib_link_probe()
{
	return static_cast<std::uint32_t>(SKSE::GetPluginHandle());
}

extern "C" __declspec(dllexport) void commonlib_trampoline_link_probe(SKSE::Trampoline& trampoline, std::uintptr_t src, std::uintptr_t dst)
{
	trampoline.write_branch<5>(src, dst);
}

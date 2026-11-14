#include "RE/B/BSAudioManager.h"

#include "RE/B/BGSSoundDescriptorForm.h"
#include "RE/B/BSAudio.h"
#include "RE/B/BSGameSound.h"
#include "RE/B/BSSoundHandle.h"
#include "RE/F/FormTraits.h"
#include "RE/N/NiAVObject.h"
#include "RE/T/TESForm.h"

namespace RE
{
	BSAudioManager* BSAudioManager::GetSingleton()
	{
		using func_t = decltype(&BSAudioManager::GetSingleton);
		static REL::Relocation<func_t> func{ RELOCATION_ID(66391, 67652) };
		return func();
	}

	BSAudio* BSAudioManager::QPlatformInstance()
	{
		using func_t = decltype(&BSAudioManager::QPlatformInstance);
		static REL::Relocation<func_t> func{ RELOCATION_ID(66392, 67653) };
		return func();
	}

	void BSAudioManager::ClearCache()
	{
		static REL::Relocation<BSSpinLock*> cacheSpinLock{ RELOCATION_ID(523579, 410115) };
		BSSpinLockGuard                     locker{ *cacheSpinLock };

		for (auto it = audioCache.begin(); it != audioCache.end();) {
			const auto gameSound = *it;
			it = audioCache.erase(it);
			QPlatformInstance()->ReleaseGameSound(gameSound);
		}

		audioCacheSize = 0;
	}

	void BSAudioManager::ComposeMessage(SOUND_MSG a_message, std::uint32_t a_id, std::int32_t a_iData, void* a_pData, NiPointer<NiAVObject> a_spData, const NiPoint3& a_vector3)
	{
		using func_t = decltype(&BSAudioManager::ComposeMessage);
		static REL::Relocation<func_t> func{ RELOCATION_ID(66453, 67717) };
		return func(this, a_message, a_id, a_iData, a_pData, a_spData, a_vector3);
	}

	bool BSAudioManager::GetSoundHandle(BSSoundHandle& a_soundHandle, BSISoundDescriptor* a_descriptor, std::uint32_t a_flags)
	{
		using func_t = decltype(&BSAudioManager::GetSoundHandle);
		static REL::Relocation<func_t> func{ RELOCATION_ID(66404, 67666) };
		return func(this, a_soundHandle, a_descriptor, a_flags);
	}

	void BSAudioManager::GetSoundHandleByFile(BSSoundHandle& a_soundHandle, const BSResource::ID& a_file, std::uint32_t a_flags, std::uint32_t a_priority)
	{
		using func_t = decltype(&BSAudioManager::GetSoundHandleByFile);
		static REL::Relocation<func_t> func{ RELOCATION_ID(66402, 67664) };
		return func(this, a_soundHandle, a_file, a_flags, a_priority);
	}

	void BSAudioManager::GetSoundHandleByName(BSSoundHandle& a_soundHandle, const char* a_editorID, std::uint32_t a_flags)
	{
		using func_t = decltype(&BSAudioManager::GetSoundHandleByName);
		static REL::Relocation<func_t> func{ RELOCATION_ID(66403, 67665) };
		return func(this, a_soundHandle, a_editorID, a_flags);
	}

	void BSAudioManager::KillAll(bool a_waitForCompletion, std::uint32_t a_waitTicks)
	{
		using func_t = decltype(&BSAudioManager::KillAll);
		static REL::Relocation<func_t> func{ RELOCATION_ID(66405, 67668) };
		return func(this, a_waitForCompletion, a_waitTicks);
	}

	bool BSAudioManager::Play(RE::FormID a_soundFormID)
	{
		auto descriptor = TESForm::LookupByID<BGSSoundDescriptorForm>(a_soundFormID);
		return descriptor && Play(descriptor);
	}

	bool BSAudioManager::Play(BSISoundDescriptor* a_descriptor)
	{
		BSSoundHandle sound;
		return GetSoundHandle(sound, a_descriptor) && sound.Play();
	}

	void BSAudioManager::PrecacheDescriptor(const BSISoundDescriptor* a_descriptor, std::uint32_t a_flags)
	{
		using func_t = decltype(&BSAudioManager::PrecacheDescriptor);
		static REL::Relocation<func_t> func{ RELOCATION_ID(66456, 67720) };
		return func(this, a_descriptor, a_flags);
	}

	void BSAudioManager::SetCacheEnabled(bool a_enabled)
	{
		if (a_enabled) {
			flags.set(Flags::CacheEnabled);
		} else {
			flags.reset(Flags::CacheEnabled);
			ClearCache();
		}
	}

	void BSAudioManager::ReleaseAllSounds()
	{
		using func_t = void (*)(BSAudioManager*);
		static REL::Relocation<func_t> func{ RELOCATION_ID(66472, 67736) };
		func(this);
	}

	void BSAudioManager::StopAllSounds()
	{
#if defined(HAS_SKYRIM_MULTI_TARGETING) && defined(ENABLE_SKYRIM_SE) && defined(ENABLE_SKYRIM_AE)
		// Both runtimes are compiled in: dispatch by REL::Module::IsAE(), not #ifdef.
		if (REL::Module::IsAE()) {
			using func_t = void (*)(BSTHashMap<std::uint32_t, BSGameSound*>*);
			static REL::Relocation<func_t> func{ REL::ID(67749) };
			func(&activeSounds);
			return;
		}
		for (auto& entry : activeSounds) {
			const auto sound = entry.second;
			if (sound) {
				sound->StopImpl();
				sound->flags = static_cast<BSGameSound::Flags>(sound->flags.underlying() & ~0x200u);
				sound->SetSoundFinished(true);
			}
		}
#elif defined(ENABLE_SKYRIM_AE)
		using func_t = void (*)(BSTHashMap<std::uint32_t, BSGameSound*>*);
		static REL::Relocation<func_t> func{ REL::ID(67749) };
		func(&activeSounds);
#else
		for (auto& entry : activeSounds) {
			const auto sound = entry.second;
			if (sound) {
				sound->StopImpl();
				sound->flags = static_cast<BSGameSound::Flags>(sound->flags.underlying() & ~0x200u);
				sound->SetSoundFinished(true);
			}
		}
#endif
	}
}

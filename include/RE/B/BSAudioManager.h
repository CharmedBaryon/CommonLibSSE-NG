#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSAudioInit.h"
#include "RE/B/BSSoundMessage.h"
#include "RE/B/BSTHashMap.h"
#include "RE/B/BSTList.h"
#include "RE/N/NiAVObject.h"

namespace RE
{
	class BSAudio;
	class BSAudioManagerThread;
	class BSGameSound;
	class BSISoundDescriptor;
	class BSISoundOutputModel;
	class BSSoundInfo;
	class SoundMessageList;
	class SoundMessageStack;
	struct BSSoundHandle;

	namespace BSResource
	{
		struct ID;
	}

	class BSAudioManager
	{
	public:
		enum class Flags : std::uint32_t
		{
			ManagerInitialized = 1 << 0,
			PlatformInitialized = 1 << 1,
			PlatformInitFailed = 1 << 2,
			CacheEnabled = 1 << 3,
			ShuttingDown = 1 << 4,
			RunDisabled = 1 << 5
		};

		[[nodiscard]] static BSAudioManager* GetSingleton();
		[[nodiscard]] static BSAudio*        QPlatformInstance();

		void ClearCache();
		void ComposeMessage(SOUND_MSG a_message, std::uint32_t a_id = 0, std::int32_t a_iData = 0, void* a_pData = nullptr, NiPointer<NiAVObject> a_spData = nullptr, const NiPoint3& a_vector3 = {});
		bool GetSoundHandle(BSSoundHandle& a_soundHandle, BSISoundDescriptor* a_descriptor, std::uint32_t a_flags = 0x1A);
		void GetSoundHandleByFile(BSSoundHandle& a_soundHandle, const BSResource::ID& a_file, std::uint32_t a_flags, std::uint32_t a_priority);
		void GetSoundHandleByName(BSSoundHandle& a_soundHandle, const char* a_editorID, std::uint32_t a_flags);
		void KillAll(bool a_waitForCompletion = false, std::uint32_t a_waitTicks = 1000);
		bool Play(FormID a_soundFormID);
		bool Play(BSISoundDescriptor* a_descriptor);
		void PrecacheDescriptor(const BSISoundDescriptor* a_descriptor, std::uint32_t a_flags);
		void SetCacheEnabled(bool a_enabled);

		void ReleaseAllSounds();
		void StopAllSounds();

		[[nodiscard]] constexpr bool GetCacheEnabled() const noexcept { return flags.all(Flags::CacheEnabled); }

		// members

		std::uint32_t                                             frontQueue;                  // 000
		std::uint32_t                                             backQueue;                   // 004
		SoundMessageList*                                         messageQueues[2];            // 008
		SoundMessageStack*                                        freeMessages;                // 018
		SoundMessageStack*                                        processedMessages;           // 020
		BSTHashMap<std::uint32_t, BSGameSound*>                   activeSounds;                // 028
		BSTHashMap<std::uint32_t, BSSoundInfo*>                   stateMap;                    // 058
		BSTHashMap<std::uint32_t, NiPointer<NiAVObject>>          movingSounds;                // 088
		BSTHashMap<const NiAVObject*, const BSISoundOutputModel*> objectOutputOverrides;       // 0B8
		BSTList<BSGameSound*>                                     audioCache;                  // 0E8
		std::uint32_t                                             audioCacheSize;              // 0F0
		std::uint32_t                                             ownerThreadID;               // 0F4
		BSAudioManagerThread*                                     ownerThread;                 // 0F8
		std::uint32_t                                             unk100;                      // 100
		std::uint32_t                                             audioHWThread;               // 104
		BSAudioInit                                               initSettings;                // 108
		std::uint32_t                                             maxCacheSize;                // 160
		std::uint32_t                                             maxAudioCacheSize;           // 164
		std::uint32_t                                             maxSizeForCachedSound;       // 168
		REX::EnumSet<Flags, std::uint32_t>                        flags;                       // 16C
		float                                                     masterVolume;                // 170
		std::uint32_t                                             asyncReadPriorityThreshold;  // 174
		BSAudioCallbacks                                          audioCallbacks;              // 178
	};
	static_assert(sizeof(BSAudioManager) == 0x190);
}

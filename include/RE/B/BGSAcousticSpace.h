#pragma once

#include "RE/F/FormTypes.h"
#include "RE/T/TESBoundObject.h"

namespace RE
{
	class BGSAcousticSpace : public TESBoundObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSAcousticSpace;
		inline static constexpr auto VTABLE = VTABLE_BGSAcousticSpace;
		inline static constexpr auto FORMTYPE = FormType::AcousticSpace;

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		~BGSAcousticSpace() override;  // 00

		// override (TESBoundObject)
		void        InitializeData() override;                 // 04
		bool        Load(TESFile* a_mod) override;             // 06
		void        InitItemImpl() override;                   // 13
		void        UnClone3D(TESObjectREFR* a_ref) override;  // 41
		NiAVObject* Clone3D(TESObjectREFR* a_ref) override;    // 4A - { return 0; }

		// add

		// Switches away from this acoustic space: fades out its looping sound (or stops it
		// outright if the game is paused), transitions any active reverb, and clears the
		// process-wide "current acoustic space" pointer. A no-op if this isn't the currently
		// active acoustic space.
		void Deactivate();

		// members
		BGSSoundDescriptorForm* loopingSound;  // 30 - SNAM
		TESRegion*              soundRegion;   // 38 - RDAT - interiors only
		BGSReverbParameters*    reverbType;    // 40 - BNAM
	};
	static_assert(sizeof(BGSAcousticSpace) == 0x48);
}

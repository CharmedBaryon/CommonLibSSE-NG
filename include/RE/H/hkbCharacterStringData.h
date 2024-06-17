#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkStringPtr.h"

namespace RE
{
	struct hkbAssetBundleStringData;

	class hkbCharacterStringData : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbCharacterStringData;
		inline static constexpr auto VTABLE = VTABLE_hkbCharacterStringData;

		struct FileNameMeshNamePair
		{
			hkStringPtr fileName;
			hkStringPtr meshName;
		};

		// members
		hkArray<FileNameMeshNamePair>     deformableSkinNames;                 // 10
		hkArray<FileNameMeshNamePair>     rigidSkinNames;                      // 20
		hkArray<hkStringPtr>              animationNames;                      // 30
		hkArray<hkbAssetBundleStringData> animationBundleFilenameData;         // 40 - unused by Skyrim?
		hkArray<hkStringPtr>              characterPropertyNames;              // 50
		hkArray<hkStringPtr>              retargetingSkeletonMapperFilenames;  // 60
		hkArray<hkStringPtr>              lodNames;                            // 70
		hkArray<hkStringPtr>              mirroredSyncPointSubstringsA;        // 80
		hkArray<hkStringPtr>              mirroredSyncPointSubstringsB;        // 90
		hkStringPtr                       name;                                // A0
		hkStringPtr                       rigName;                             // A8
		hkStringPtr                       ragdollName;                         // B0
		hkStringPtr                       behaviorFilename;                    // B8
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkbCharacterStringData) == 0xC0);
}

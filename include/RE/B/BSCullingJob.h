#pragma once
#include "BSCullingProcess.h"

namespace RE
{
	class NiFrustum;
	class BSPortalGraphEntry;
	class BSCullingProcess;

	class BSCullingJob
	{
	public:
		// members
		NiPointer<BSShaderAccumulator>               accumulator;                 // 00
		NiPointer<BSShaderAccumulator>               secondAccumulator;           // 08
		NiPointer<NiCamera>                          camera;                      // 10
		BSCompoundFrustum*                           compoundFrustum;             // 18
		NiFrustum*                                   frustum;                     // 20
		BSPortalGraphEntry*                          portalGraphEntry;            // 28
		BSCullingProcess*                            cullingProcess;              // 30
		NiFrustumPlanes*                             frustumPlanes;               // 38
		NiPointer<NiAVObject>                        scene;                       // 40
		BSTArray<NiAVObject*>*                       accumulatedObjectArray;      // 48
		REX::Enum<BSCullingProcess::BSCPCullingType> cullMode;                    // 50
		std::uint32_t                                unk54;                       // 54
		std::uint32_t                                jobIndex;                    // 58
		bool                                         unk5C;                       // 5C
		bool                                         processingDirectionalLight;  // 5D
		bool                                         ignorePreprocess;            // 5E
		bool                                         usingCustomCullPlanes;       // 5F
		bool                                         unk60;                       // 60
		bool                                         respectHidden;               // 61
		bool                                         unk62;                       // 62
		std::byte                                    pad63[5];                    // 63
	};
	static_assert(sizeof(BSCullingJob) == 0x68);
}

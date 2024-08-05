#pragma once

#include "RE/B/BSTSmartPointer.h"
#include "RE/N/NiRefObject.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BSFaceGenMorphData;
	class BSFaceGenNiNode;
	class BSTriShape;

	class BSFaceGenModelMeshData
	{
	public:
		// members
		std::uint32_t                 unk00;      // 00
		std::uint32_t                 pad04;      // 04
		NiPointer<BSFaceGenNiNode>    faceNode;   // 08
		NiPointer<BSTriShape>         faceShape;  // 10
		void*                         triData;    // 18
		NiPointer<BSFaceGenMorphData> morphData;  // 20
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSFaceGenModelMeshData) == 0x28);

	class BSFaceGenModel : public NiRefObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSFaceGenModel;
		inline static constexpr auto VTABLE = VTABLE_BSFaceGenModel;

		~BSFaceGenModel() override;  // 00

		// members
		BSTSmartPointer<BSFaceGenModelMeshData> modelMeshData;  // 10
		std::uint32_t                           unk18;          // 18
		std::uint32_t                           pad1C;          // 1C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSFaceGenModel) == 0x20);
}

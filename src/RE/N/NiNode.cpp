#include "RE/N/NiNode.h"

#include "RE/M/MemoryManager.h"

namespace RE
{
	NiNode* NiNode::Create(std::uint16_t a_arrBufLen)
	{
		auto node = malloc<NiNode>();
		std::memset(reinterpret_cast<void*>(node), 0, sizeof(NiNode));
		node->Ctor(a_arrBufLen);
		return node;
	}

	void NiNode::DetachChild(NiAVObject* a_child)
	{
		return DetachChild2(a_child);
	}

	void NiNode::DetachChild(NiAVObject* a_child, NiPointer<NiAVObject>& a_childOut)
	{
		return DetachChild1(a_child, a_childOut);
	}

	void NiNode::DetachChildAt(std::uint32_t a_idx)
	{
		return DetachChildAt2(a_idx);
	}

	void NiNode::DetachChildAt(std::uint32_t a_idx, NiPointer<NiAVObject>& a_childOut)
	{
		return DetachChildAt1(a_idx, a_childOut);
	}

	void NiNode::SetAt(std::uint32_t a_idx, NiAVObject* a_child)
	{
		return SetAt2(a_idx, a_child);
	}

	void NiNode::SetAt(std::uint32_t a_idx, NiAVObject* a_child, NiPointer<NiAVObject>& a_childOut)
	{
		return SetAt1(a_idx, a_child, a_childOut);
	}

	NiNode* NiNode::Ctor(std::uint16_t a_arrBuffLen)
	{
		using func_t = decltype(&NiNode::Ctor);
		static REL::Relocation<func_t> func{ RELOCATION_ID(68936, 70287) };
		return func(this, a_arrBuffLen);
	}

#ifdef SKYRIM_CROSS_VR
	void NiNode::AttachChild(NiAVObject* a_child, bool a_firstAvail)
	{
		REL::RelocateVirtual<decltype(&NiNode::AttachChild)>(0x35, 0x36, this, a_child, a_firstAvail);
	}

	void NiNode::InsertChildAt(std::uint32_t a_idx, NiAVObject* a_child)
	{
		REL::RelocateVirtual<decltype(&NiNode::InsertChildAt)>(0x36, 0x37, this, a_idx, a_child);
	}

	void NiNode::DetachChild1(NiAVObject* a_child, NiPointer<NiAVObject>& a_childOut)
	{
		REL::RelocateVirtual<decltype(&NiNode::DetachChild1)>(0x37, 0x38, this, a_child, a_childOut);
	}

	void NiNode::DetachChild2(NiAVObject* a_child)
	{
		REL::RelocateVirtual<decltype(&NiNode::DetachChild2)>(0x38, 0x39, this, a_child);
	}

	void NiNode::DetachChildAt1(std::uint32_t a_idx, NiPointer<NiAVObject>& a_childOut)
	{
		REL::RelocateVirtual<decltype(&NiNode::DetachChildAt1)>(0x39, 0x3A, this, a_idx, a_childOut);
	}

	void NiNode::DetachChildAt2(std::uint32_t a_idx)
	{
		REL::RelocateVirtual<decltype(&NiNode::DetachChildAt2)>(0x3A, 0x3B, this, a_idx);
	}

	void NiNode::SetAt1(std::uint32_t a_idx, NiAVObject* a_child, NiPointer<NiAVObject>& a_childOut)
	{
		REL::RelocateVirtual<decltype(&NiNode::SetAt1)>(0x3B, 0x3C, this, a_idx, a_child, a_childOut);
	}

	void NiNode::SetAt2(std::uint32_t a_idx, NiAVObject* a_child)
	{
		REL::RelocateVirtual<decltype(&NiNode::SetAt2)>(0x3C, 0x3D, this, a_idx, a_child);
	}

	void NiNode::UpdateUpwardPass(NiUpdateData& a_data)
	{
		REL::RelocateVirtual<decltype(&NiNode::UpdateUpwardPass)>(0x3D, 0x3E, this, a_data);
	}
#endif
}

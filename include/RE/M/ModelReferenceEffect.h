#pragma once

#include "RE/B/BGSLoadGameSubBuffer.h"
#include "RE/B/BSTEvent.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/R/RefAttachTechniqueInput.h"
#include "RE/R/ReferenceEffect.h"
#include "RE/S/SimpleAnimationGraphManagerHolder.h"

namespace RE
{
	class BGSArtObjectCloneTask;
	class NiAVObject;
	struct BSAnimationGraphEvent;

	class ModelReferenceEffect :
		public ReferenceEffect,                     // 00
		public SimpleAnimationGraphManagerHolder,   // 48
		public BSTEventSink<BSAnimationGraphEvent>  // 60
	{
	public:
		inline static constexpr auto RTTI = RTTI_ModelReferenceEffect;
		inline static constexpr auto Ni_RTTI = NiRTTI_ModelReferenceEffect;
		inline static constexpr auto VTABLE = VTABLE_ModelReferenceEffect;
		inline static constexpr auto TYPE = TEMP_EFFECT_TYPE::kRefModel;

		enum class Flags
		{
			kNone = 0,
			kAttached = 1 << 0,
			k3rdPersonVisible = 1 << 1
		};

		~ModelReferenceEffect() override;  // 00

		// override (ReferenceEffect)
		const NiRTTI*    GetRTTI() const override;                         // 02
		bool             Update(float a_arg1) override;                    // 28
		NiAVObject*      Get3D() const override;                           // 29 - { return artObject3D; }
		TEMP_EFFECT_TYPE GetType() const override;                         // 2C - { return 9; }
		void             SaveGame(BGSSaveGameBuffer* a_buf) override;      // 2D
		void             LoadGame(BGSLoadGameBuffer* a_buf) override;      // 2E
		void             Init() override;                                  // 36
		void             UpdateParentCell(NiAVObject* a_object) override;  // 3A
		void             UpdatePosition() override;                        // 3B
		NiAVObject*      GetAttachRoot() override;                         // 3C
		bool             GetAttached() override;                           // 3D - { return flags & 1; }
		void             DetachImpl() override;                            // 3E

		// override (SimpleAnimationGraphManagerHolder)
		bool SetupAnimEventSinks(const BSTSmartPointer<BShkbAnimationGraph>& a_animGraph) override;                                                        // 08
		bool CreateAnimationChannels(BSScrapArray<BSTSmartPointer<BSAnimationGraphChannel>>& animGraphChannels) override;                                  // 0A
		void PostChangeAnimationManager(const BSTSmartPointer<BShkbAnimationGraph>& a_arg1, const BSTSmartPointer<BShkbAnimationGraph>& a_arg2) override;  // 0D

		// override (BSTEventSink<BSAnimationGraphEvent>)
		BSEventNotifyControl ProcessEvent(const BSAnimationGraphEvent* a_event, BSTEventSource<BSAnimationGraphEvent>* a_eventSource) override;  // 01

		// members
		RefAttachTechniqueInput                hitEffectArtData;   // 68
		BGSLoadGameSubBuffer                   loadGameSubBuffer;  // B0
		BGSArtObject*                          artObject;          // B8
		BSTSmartPointer<BGSArtObjectCloneTask> cloneTask;          // C0
		NiPointer<NiAVObject>                  artObject3D;        // C8
		stl::enumeration<Flags, std::uint32_t> flags;              // D0
		std::uint32_t                          padD4;              // D4
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ModelReferenceEffect) == 0xD8);
}

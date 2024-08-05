#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSIRagdollDriver.h"
#include "RE/B/BSIntrusiveRefCounted.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/H/hkbCharacter.h"

namespace RE
{
	class bhkWorld;
	class BSFadeNode;
	class BShkFloatController;
	class BSTransformDeltaEvent;
	class hkbBehaviorGraph;
	struct BSAnimationGraphEvent;
	struct hkbGeneratorOutput;

	namespace BSResource
	{
		struct ID;
	}

	BSSmartPointer(BShkbAnimationGraph);

	class BShkbAnimationGraph :
		public BSIRagdollDriver,                       // 000
		public BSIntrusiveRefCounted,                  // 008
		public BSTEventSource<BSTransformDeltaEvent>,  // 010
		public BSTEventSource<BSAnimationGraphEvent>   // 068
	{
	public:
		inline static constexpr auto RTTI = RTTI_BShkbAnimationGraph;
		inline static constexpr auto VTABLE = VTABLE_BShkbAnimationGraph;

		struct BoneNodeEntry
		{
			NiNode*  node;  // 00
			uint32_t unk08;
			uint32_t unk0C;
		};

		~BShkbAnimationGraph() override;  // 00

		// override (BSIRagdollDriver)
		bool HasRagdoll() override;                                       // 01
		bool AddRagdollToWorld() override;                                // 02
		bool RemoveRagdollFromWorld() override;                           // 03
		void SetWorld(bhkWorld* a_world) override;                        // 04 - { world = a_world; }
		void ResetRagdoll(void) override;                                 // 05
		void Unk_06(void) override;                                       // 06
		void SetRagdollConstraintsFromBhkConstraints() override;          // 07
		void SetMotionType(hkpMotion::MotionType a_motionType) override;  // 08
		void Unk_09(void) override;                                       // 09
		void ToggleSyncOnUpdate(bool a_disable) override;                 // 0A
		void Unk_0B(void) override;                                       // 0B
		void ToggleConstraints(bool a_disable) override;                  // 0C
		void Unk_0D(void) override;                                       // 0D

		template <class T>
		[[nodiscard]] inline BSTEventSource<T>* GetEventSource()
		{
			return static_cast<BSTEventSource<T>*>(this);
		}

		template <class T>
		inline void AddEventSink(BSTEventSink<T>* a_eventSink)
		{
			GetEventSource<T>()->AddEventSink(a_eventSink);
		}

		template <class T>
		inline void RemoveEventSink(BSTEventSink<T>* a_eventSink)
		{
			GetEventSource<T>()->RemoveEventSink(a_eventSink);
		}

		bool GetGraphVariableBool(const BSFixedString& a_variableName, bool& a_out) const
		{
			using func_t = decltype(&BShkbAnimationGraph::GetGraphVariableBool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(62696, 63613) };
			return func(this, a_variableName, a_out);
		}

		bool GetGraphVariableFloat(const BSFixedString& a_variableName, float& a_out) const
		{
			using func_t = decltype(&BShkbAnimationGraph::GetGraphVariableFloat);
			static REL::Relocation<func_t> func{ RELOCATION_ID(62695, 63614) };
			return func(this, a_variableName, a_out);
		}

		bool GetGraphVariableInt(const BSFixedString& a_variableName, int& a_out) const
		{
			using func_t = decltype(&BShkbAnimationGraph::GetGraphVariableInt);
			static REL::Relocation<func_t> func{ RELOCATION_ID(62694, 63615) };
			return func(this, a_variableName, a_out);
		}

		bool SetGraphVariableBool(const BSFixedString& a_variableName, const bool a_in)
		{
			using func_t = decltype(&BShkbAnimationGraph::SetGraphVariableBool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(63609, 62708) };
			return func(this, a_variableName, a_in);
		}

		bool SetGraphVariableFloat(const BSFixedString& a_variableName, const float a_in)
		{
			using func_t = decltype(&BShkbAnimationGraph::SetGraphVariableFloat);
			static REL::Relocation<func_t> func{ RELOCATION_ID(63608, 62709) };
			return func(this, a_variableName, a_in);
		}

		bool SetGraphVariableInt(const BSFixedString& a_variableName, const int a_in)
		{
			using func_t = decltype(&BShkbAnimationGraph::SetGraphVariableInt);
			static REL::Relocation<func_t> func{ RELOCATION_ID(63607, 62710) };
			return func(this, a_variableName, a_in);
		}

		// members
		hkbCharacter                   characterInstance;            // 0C0
		BSTArray<BoneNodeEntry>        boneNodes;                    // 160
		BSTArray<BShkFloatController*> fadeControllers;              // 178
		BSTArray<void*>                unk190;                       // 190
		BSTSmallArray<void*>           unk1A8;                       // 1A8
		BSTSmallArray<std::uint8_t>    unk1C0;                       // 1C0
		std::uint64_t                  unk1D8;                       // 1D8
		std::uint64_t                  unk1E0;                       // 1E0
		float                          interpolationTimeOffsets[2];  // 1E8
		BSFixedString                  projectName;                  // 1F0
		BSResource::ID*                unk1F8;                       // 1F8
		void*                          projectDBData;                // 200 - BShkbHkxDB::ProjectDBData*
		hkbBehaviorGraph*              behaviorGraph;                // 208
		Actor*                         holder;                       // 210
		BSFadeNode*                    rootNode;                     // 218
		hkbGeneratorOutput*            generatorOutputs[2];          // 220
		float                          interpolationAmounts[2];      // 230
		bhkWorld*                      physicsWorld;                 // 238
		std::uint16_t                  numAnimBones;                 // 240
		std::uint8_t                   unk242;                       // 242
		std::uint8_t                   unk243;                       // 243
		std::uint16_t                  unk244;                       // 244
		std::uint8_t                   unk246;                       // 246
		std::uint8_t                   unk247;                       // 247
		std::uint8_t                   unk248;                       // 248
		std::uint8_t                   doFootIK;                     // 249
		std::uint16_t                  unk24A;                       // 24A
		std::uint32_t                  unk24C;                       // 24C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BShkbAnimationGraph) == 0x250);
}

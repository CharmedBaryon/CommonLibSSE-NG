#pragma once

#include "RE/B/BSIntrusiveRefCounted.h"
#include "RE/I/IMovementControllerRegisterInterface.h"

namespace RE
{
	class BSPathingStreamRead;
	class BSPathingStreamWrite;
	class IMovementDebugRenderingInterface;
	class IMovementState;
	struct IPipelineStageInterface;
	struct MovementUpdateDataSmallDelta;
	struct MovementUpdateDataLargeDelta;

	class MovementAgent : public BSIntrusiveRefCounted
	{
	public:
		virtual ~MovementAgent();  // 00

		virtual const BSFixedString&              GetAgentType() const;                                           // 01
		virtual uint8_t                           GetAgentSaveType() const;                                       // 02
		virtual IPipelineStageInterface*          GetPipelineStageInterface(const BSFixedString&);                // 03
		virtual void                              RegisterWithController(IMovementControllerRegisterInterface&);  // 04
		virtual IMovementDebugRenderingInterface* GetDebugRenderingInterface();                                   // 05
		virtual bool                              Activate();                                                     // 06
		virtual void                              Init(BSPathingStreamRead&);                                     // 07
		virtual void                              Kill();                                                         // 08
		virtual void                              Deactivate();                                                   // 09
		virtual void                              UnregisterWithController();                                     // 0A
		virtual void                              SaveGame(BSPathingStreamWrite&);                                // 0B
		virtual void                              LoadGame(BSPathingStreamRead&);                                 // 0C
		virtual void                              FinishLoadGame();                                               // 0D

		// members
		IMovementState* movementState;  // 10
	};
	static_assert(sizeof(MovementAgent) == 0x18);

	class MovementArbiter : public BSIntrusiveRefCounted
	{
	public:
		virtual ~MovementArbiter();  // 00

		virtual const BSFixedString&              GetPipelineStage() const;                                       // 01
		virtual const BSFixedString&              GetArbiterType() const;                                         // 02
		virtual uint8_t                           GetArbiterSaveType() const;                                     // 03
		virtual void                              RegisterWithController(IMovementControllerRegisterInterface&);  // 04
		virtual IMovementDebugRenderingInterface* GetDebugRenderingInterface();                                   // 05
		virtual void                              Activate();                                                     // 06
		virtual void                              Init(BSPathingStreamRead&);                                     // 07
		virtual void                              UpdateSmallDelta(MovementUpdateDataSmallDelta&);                // 08
		virtual void                              UpdateLargeDelta(MovementUpdateDataLargeDelta&);                // 09
		virtual void                              Kill();                                                         // 0A
		virtual void                              Deactivate();                                                   // 0B
		virtual void                              UnregisterWithController();                                     // 0C
		virtual void                              SaveGame(BSPathingStreamWrite&);                                // 0D
		virtual void                              LoadGame(BSPathingStreamRead&);                                 // 0E
		virtual bool                              AddAgent(const BSTSmartPointer<MovementAgent>&);                // 0F
		virtual bool                              RemoveAgent(const BSTSmartPointer<MovementAgent>&);             // 10
		virtual void                              RemoveAllAgents();                                              // 11

		// members
		IMovementState* movementState;  // 10
	};
	static_assert(sizeof(MovementArbiter) == 0x18);

	class MovementControllerAI :
		public IMovementControllerRegisterInterface  // 000
	{
		template <typename T>
		class ActiveSmartPtr
		{
		public:
			ActiveSmartPtr(const BSTSmartPointer<T>& a_ptr, bool active) :
				ptr(a_ptr)
			{
				SetActive(active);
			}

			ActiveSmartPtr(const ActiveSmartPtr& other) :
				ptr(other.Qptr())
			{
				SetActive(other.QActive());
			}

			~ActiveSmartPtr()
			{
				clear();
			}

			void SetActive(bool val)
			{
				clear();
				*reinterpret_cast<uint64_t*>(&ptr) |= static_cast<uint64_t>(val);
			}

			bool QActive() const
			{
				return *reinterpret_cast<const uint64_t*>(&ptr) & 1;
			}

			BSTSmartPointer<T> Qptr() const
			{
				auto ptr1 = reinterpret_cast<const uint64_t*>(&ptr);
				auto tmp1 = *ptr1 & static_cast<uint64_t>(-2);
				return *reinterpret_cast<BSTSmartPointer<T>*>(&tmp1);
			}

		private:
			void clear()
			{
				*reinterpret_cast<uint64_t*>(&ptr) &= static_cast<uint64_t>(-2);
			}

			// members
			BSTSmartPointer<T> ptr;  // 00
		};

	public:
		inline static constexpr auto RTTI = RTTI_MovementControllerAI;
		inline static constexpr auto VTABLE = VTABLE_MovementControllerAI;

		using ActiveArbiterSmartPtr = ActiveSmartPtr<MovementArbiter>;
		static_assert(sizeof(ActiveArbiterSmartPtr) == 0x8);

		using ActiveAgentSmartPtr = ActiveSmartPtr<MovementAgent>;
		static_assert(sizeof(ActiveAgentSmartPtr) == 0x8);

		~MovementControllerAI() override;  // 00

		// add
		virtual void Unk_05(void);                                                   // 05
		virtual void Unk_06(void);                                                   // 06 - { return; }
		virtual void GetMoveDirection(float a_delta, NiPoint3& a_outMoveDirection);  // 07
		virtual void Unk_08(void);                                                   // 08
		virtual void Unk_09(void);                                                   // 09 - { return 1; }

		// members
		mutable volatile std::uint32_t          _refCount{ 0 };  // 008
		std::uint32_t                           pad00C;          // 00C
		BSTSmallArray<ActiveArbiterSmartPtr, 2> arbiters;        // 010
		BSTSmallArray<ActiveAgentSmartPtr, 1>   agents;          // 030
		std::uint64_t                           unk048;          // 048
		std::uint64_t                           unk050;          // 050
		std::uint64_t                           unk058;          // 058
		std::uint64_t                           unk060;          // 060
		std::uint64_t                           unk068;          // 068
		std::uint64_t                           unk070;          // 070
		std::uint64_t                           unk078;          // 078
		std::uint64_t                           unk080;          // 080
		std::uint64_t                           unk088;          // 088
		std::uint64_t                           unk090;          // 090
		std::uint64_t                           unk098;          // 098
		std::uint64_t                           unk0A0;          // 0A0
		std::uint64_t                           unk0A8;          // 0A8
		std::uint64_t                           unk0B0;          // 0B0
		std::uint64_t                           unk0B8;          // 0B8
		std::uint64_t                           unk0C0;          // 0C0
		std::uint64_t                           unk0C8;          // 0C8
		std::uint64_t                           unk0D0;          // 0D0
		std::uint64_t                           unk0D8;          // 0D8
		std::uint64_t                           unk0E0;          // 0E0
		std::uint64_t                           unk0E8;          // 0E8
		std::uint64_t                           unk0F0;          // 0F0
		std::uint64_t                           unk0F8;          // 0F8
		std::uint64_t                           unk100;          // 100
		std::uint64_t                           unk108;          // 108
		std::uint64_t                           unk110;          // 110
		std::uint64_t                           unk118;          // 118
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(MovementControllerAI) == 0x120);
#endif
}

#pragma once

#include "RE/B/BSMultiBoundShape.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class BSMultiBoundAABB : public BSMultiBoundShape
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSMultiBoundAABB;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSMultiBoundAABB;
		inline static constexpr auto VTABLE = VTABLE_BSMultiBoundAABB;

		~BSMultiBoundAABB() override;  // 00

		// override (NiObject)
		const NiRTTI* GetRTTI() const override;                                  // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;         // 17
		void          LoadBinary(NiStream& a_stream) override;                   // 18
		void          LinkObject(NiStream& a_stream) override;                   // 19
		bool          RegisterStreamables(NiStream& a_stream) override;          // 1A
		void          SaveBinary(NiStream& a_stream) override;                   // 1B
		bool          IsEqual(NiObject* a_object) override;                      // 1C
		std::uint32_t GetType() override;                                        // 25 - { return 1; }
		float         GetLength() override;                                      // 26
		bool          CheckBound(BSMultiBound const&) override;                  // 27
		bool          CheckBound(NiBound const&) override;                       // 28
		bool          WithinFrustum(NiFrustumPlanes const&) override;            // 29
		bool          CompletelyWithinFrustum(NiFrustumPlanes const&) override;  // 2A
		void          GetNiBound(NiBound*) override;                             // 2B
		bool          GetWithinPoint(const NiPoint3& a_pos) override;            // 2C
		void          SetCenter(const NiPoint3& a_center) override;              // 2D
		void          MoveToWorld(NiTransform const&) override;                  // 2E

		// members
		std::uint32_t pad18;   // 18
		NiPoint3      center;  // 1C - world coordinates
		std::uint32_t pad28;   // 28
		NiPoint3      size;    // 2C
		std::uint32_t pad38;   // 38
		std::uint32_t pad3C;   // 3C
	};
	static_assert(sizeof(BSMultiBoundAABB) == 0x40);
}

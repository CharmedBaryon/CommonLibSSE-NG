#pragma once

#include "RE/N/NiObject.h"

namespace RE
{
	class BSMultiBound;
	class NiFrustumPlanes;

	class BSMultiBoundShape : public NiObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSMultiBoundShape;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSMultiBoundShape;
		inline static constexpr auto VTABLE = VTABLE_BSMultiBoundShape;

		enum class BSMBCullResult
		{
			kCullUntested = 0,
			kCullVisible,
			kCullCulled,
			kCullOccluded
		};

		~BSMultiBoundShape() override;  // 00

		// override (NiObject)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void          LoadBinary(NiStream& a_stream) override;            // 18
		void          LinkObject(NiStream& a_stream) override;            // 19
		bool          RegisterStreamables(NiStream& a_stream) override;   // 1A
		void          SaveBinary(NiStream& a_stream) override;            // 1B
		bool          IsEqual(NiObject* a_object) override;               // 1C

		// add
		virtual std::uint32_t GetType() = 0;                                        // 25
		virtual float         GetLength() = 0;                                      // 26
		virtual bool          CheckBound(BSMultiBound const&) = 0;                  // 27
		virtual bool          CheckBound(NiBound const&) = 0;                       // 28
		virtual bool          WithinFrustum(NiFrustumPlanes const&) = 0;            // 29
		virtual bool          CompletelyWithinFrustum(NiFrustumPlanes const&) = 0;  // 2A
		virtual void          GetNiBound(NiBound*) = 0;                             // 2B
		virtual bool          GetWithinPoint(const NiPoint3& a_pos);                // 2C
		virtual void          SetCenter(const NiPoint3& a_center);                  // 2D
		virtual void          MoveToWorld(NiTransform const&);                      // 2E

		// members
		std::uint32_t unk10;  // 10
		std::uint32_t pad14;  // 14
	};
	static_assert(sizeof(BSMultiBoundShape) == 0x18);
}

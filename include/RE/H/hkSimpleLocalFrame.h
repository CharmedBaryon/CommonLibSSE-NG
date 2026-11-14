#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkLocalFrame.h"
#include "RE/H/hkRefPtr.h"
#include "RE/H/hkStringPtr.h"
#include "RE/H/hkTransform.h"

namespace RE
{
	class hkLocalFrameGroup;

	class hkSimpleLocalFrame : public hkLocalFrame
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkSimpleLocalFrame;
		inline static constexpr auto VTABLE = VTABLE_hkSimpleLocalFrame;

		~hkSimpleLocalFrame() override;  // 00

		// override
		void               GetTransform(hkTransform& a_transform) const override;  // 03
		void               SetTransform(const hkTransform& a_transform) override;  // 04
		void               GetOrigin(hkVector4& a_origin) const override;          // 05
		hkStringPtr        GetName() const override;                               // 06
		hkLocalFrameGroup* GetGroup() const override;                              // 07
		hkLocalFrame*      GetParentFrame() const override;                        // 08

		// members
		hkTransform                     transform;    // 10
		hkArray<hkRefPtr<hkLocalFrame>> children;     // 50
		hkLocalFrameGroup*              group;        // 60 - non-owning
		hkRefPtr<hkLocalFrame>          parentFrame;  // 68
		hkStringPtr                     name;         // 70
		std::uint64_t                   pad78;        // 78
	};
	static_assert(sizeof(hkSimpleLocalFrame) == 0x80);
}
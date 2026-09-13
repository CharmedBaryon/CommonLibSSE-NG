#pragma once

#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkStringPtr.h"
#include "RE/H/hkTransform.h"
#include "RE/H/hkVector4.h"

namespace RE
{
	class hkLocalFrameGroup;

	class hkLocalFrame : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkLocalFrame;
		inline static constexpr auto VTABLE = VTABLE_hkLocalFrame;

		~hkLocalFrame() override;  // 00

		virtual void               GetTransform(hkTransform& a_transform) const = 0;  // 03
		virtual void               SetTransform(const hkTransform& a_transform) = 0;  // 04
		virtual void               GetOrigin(hkVector4& a_origin) const = 0;          // 05
		virtual hkStringPtr        GetName() const = 0;                               // 06
		virtual hkLocalFrameGroup* GetGroup() const = 0;                              // 07
		virtual hkLocalFrame*      GetParentFrame() const = 0;                        // 08
	};
	static_assert(sizeof(hkLocalFrame) == 0x10);
}

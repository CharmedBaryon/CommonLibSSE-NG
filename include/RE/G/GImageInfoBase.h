#pragma once

#include "RE/G/GMemory.h"
#include "RE/G/GRect.h"
#include "RE/G/GRefCountBaseNTS.h"
#include "RE/G/GStats.h"
#include "RE/G/GTexture.h"

namespace RE
{
	class GRenderer;

	class GImageInfoBase :
		public GRefCountBaseNTS<GImageInfoBase, GStatGroups::kGStat_Default_Mem>,  // 00
		public GTexture::ChangeHandler                                             // 10
	{
	public:
		enum class ImageInfoType
		{
			kImageInfo,
			kSubImageInfo,
			kOther
		};

		virtual ~GImageInfoBase();  // 00

		// add
		virtual std::uint32_t       GetWidth() const = 0;                                                                               // 01
		virtual std::uint32_t       GetHeight() const = 0;                                                                              // 02
		virtual GTexture*           GetTexture(GRenderer* a_renderer) = 0;                                                              // 03
		virtual GImageInfoBase*     CreateSubImage(const GRect<std::int32_t>& a_rect, GMemoryHeap* a_heap = GMemory::GetGlobalHeap());  // 04
		virtual GRect<std::int32_t> GetRect() const;                                                                                    // 05
		virtual std::uint32_t       GetImageInfoType() const;                                                                           // 06
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(GImageInfoBase) == 0x18);
}

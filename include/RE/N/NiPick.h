#pragma once

#include "RE/N/NiPoint3.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/N/NiTArray.h"
#include "RE/N/NiTCollection.h"

namespace RE
{
	class NiAVObject;

	class NiPick
	{
	public:
		class Record
		{
		public:
			// members
			NiPointer<NiAVObject> object;     // 00
			NiPoint3              intersect;  // 08
			NiPoint3              normal;     // 14
			float                 distance;   // 20
			std::uint32_t         pad24;      // 24
		};
		static_assert(sizeof(Record) == 0x28);

		enum class PickType : std::uint32_t
		{
			FIND_ALL = 0,
			FIND_FIRST = 1
		};

		enum class SortType : std::uint32_t
		{
			SORT = 0,
			NO_SORT = 1
		};

		enum class IntersectType : std::uint32_t
		{
			BOUND_INTERSECT = 0,
			TRIANGLE_INTERSECT = 1
		};

		enum class CoordinateType : std::uint32_t
		{
			MODEL_COORDINATES = 0,
			WORLD_COORDINATES = 1
		};

		struct Deleter
		{
			void operator()(NiPick* a_pick) const
			{
				if (a_pick) {
					a_pick->Destroy();
				}
			}
		};

		using Ptr = std::unique_ptr<NiPick, Deleter>;

		[[nodiscard]] static Ptr Create(std::uint32_t a_initialSize = 0, std::uint32_t a_growBy = 1);
		void                     Destroy();

		bool PickObjects(const NiPoint3& a_origin, const NiPoint3& a_direction, bool a_append = false);

		class Results : public NiTScrapArray<Record*>
		{
		public:
			virtual ~Results();  // 00
			// members
			std::uint32_t resultsCount;  // 18
			std::uint32_t pad1C;         // 1C
		};
		static_assert(sizeof(Results) == 0x20);

		// members
		REX::EnumSet<PickType, std::uint32_t>       pickType;            // 00
		REX::EnumSet<SortType, std::uint32_t>       sortType;            // 04
		REX::EnumSet<IntersectType, std::uint32_t>  intersectType;       // 08
		REX::EnumSet<CoordinateType, std::uint32_t> coordinateType;      // 0C
		bool                                        frontOnly;           // 10 - If true, the triangle logic performs a dot product between the triangle's normal and the ray's direction. If the triangle is facing away from the ray, it discards the hit
		bool                                        observeAppCullFlag;  // 11 - If true, the raycast will ignore objects that are marked as invisible/hidden
		bool                                        returnNormal;        // 12 - If true, it calculates the crossproduct of the triangle's edges and writes it to Record::normal. If false, it leaves the normal field as 0
		bool                                        returnSmoothNormal;  // 13 - If true, instead of just using the flat triangle normal, it looks at the 3 vertices of the triangle, reads their individual normals, and interpolates them using barycentric coordinates to give a smooth, rounded normal for the hit location
		bool                                        returnTexture;       // 14 - Dead code, not used it appears
		bool                                        returnColor;         // 15 - Dead code, not used it appears
		std::uint16_t                               pad16;               // 16
		NiPointer<NiAVObject>                       root;                // 18 - What the raycast is performed against
		Results                                     pickResults;         // 20
		NiPoint3                                    origin;              // 40 - Dead code, not used it appears
		std::uint32_t                               pad4C;               // 4C

	private:
		NiPick() = delete;
		~NiPick() = delete;

		NiPick* ctor(std::uint32_t a_initialSize, std::uint32_t a_growBy);
		void    dtor();
	};
	static_assert(sizeof(NiPick) == 0x50);
}

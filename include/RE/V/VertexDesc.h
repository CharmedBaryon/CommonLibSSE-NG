#pragma once

namespace RE
{
	//https://github.com/hexabits/nifskope/blob/develop/src/data/niftypes.h

	namespace BSGraphics
	{
		struct Vertex
		{
			enum Attribute : std::uint8_t
			{
				VA_POSITION = 0x0,
				VA_TEXCOORD0 = 0x1,
				VA_TEXCOORD1 = 0x2,
				VA_NORMAL = 0x3,
				VA_BINORMAL = 0x4,
				VA_COLOR = 0x5,
				VA_SKINNING = 0x6,
				VA_LANDDATA = 0x7,
				VA_EYEDATA = 0x8,
				VA_INSTANCEDATA = 0x9,

				VA_COUNT = 10
			};

			enum Flags : std::uint16_t
			{
				VF_VERTEX = 1 << VA_POSITION,
				VF_UV = 1 << VA_TEXCOORD0,
				VF_UV_2 = 1 << VA_TEXCOORD1,
				VF_NORMAL = 1 << VA_NORMAL,
				VF_TANGENT = 1 << VA_BINORMAL,
				VF_COLORS = 1 << VA_COLOR,
				VF_SKINNED = 1 << VA_SKINNING,
				VF_LANDDATA = 1 << VA_LANDDATA,
				VF_EYEDATA = 1 << VA_EYEDATA,
				VF_INSTANCEDATA = 1 << VA_INSTANCEDATA,
				VF_FULLPREC = 0x400
			};

			enum Masks : std::uint64_t
			{
				DESC_MASK_VERT = 0xFFFFFFFFFFFFFFF0,
				DESC_MASK_UVS = 0xFFFFFFFFFFFFFF0F,
				DESC_MASK_NBT = 0xFFFFFFFFFFFFF0FF,
				DESC_MASK_SKCOL = 0xFFFFFFFFFFFF0FFF,
				DESC_MASK_DATA = 0xFFFFFFFFFFF0FFFF,
				DESC_MASK_OFFSET = 0xFFFFFF0000000000,
				DESC_MASK_FLAGS = ~(DESC_MASK_OFFSET)
			};
		};

		class VertexDesc
		{
		public:
			[[nodiscard]] bool HasFlag(Vertex::Flags a_flag) const
			{
				return ((desc >> 44) & a_flag) != 0;
			}
			void SetFlag(Vertex::Flags a_flag)
			{
				desc |= (static_cast<uint64_t>(a_flag) << 44);
			}
			void ClearFlag(Vertex::Flags a_flag)
			{
				desc &= ~(static_cast<uint64_t>(a_flag) << 44);
			}

			[[nodiscard]] std::uint32_t GetAttributeOffset(Vertex::Attribute a_attribute) const
			{
				return (desc >> (4 * static_cast<uint8_t>(a_attribute) + 2)) & 0x3C;
			}
			void SetAttributeOffset(Vertex::Attribute a_attribute, std::uint32_t a_offset)
			{
				if (a_attribute != Vertex::Attribute::VA_POSITION) {
					const uint64_t lhs = static_cast<uint64_t>(a_offset) << (4 * static_cast<uint8_t>(a_attribute) + 2);
					const uint64_t rhs = desc & ~static_cast<uint64_t>(15 << (4 * static_cast<uint8_t>(a_attribute) + 4));

					desc = lhs | rhs;
				}
			}
			void ClearAttributeOffsets()
			{
				desc &= Vertex::Masks::DESC_MASK_OFFSET;
			}

			[[nodiscard]] Vertex::Flags GetFlags() const
			{
				return static_cast<Vertex::Flags>((desc & Vertex::Masks::DESC_MASK_OFFSET) >> 44);
			}
			void SetFlags(Vertex::Flags a_flags)
			{
				desc |= (static_cast<uint64_t>(a_flags) << 44) | (desc & Vertex::Masks::DESC_MASK_FLAGS);
			}

			[[nodiscard]] std::uint32_t GetSize()
			{
				std::uint32_t vertexSize = 0;
				auto          flags = GetFlags();

				if (flags & Vertex::VF_VERTEX) {
					vertexSize += sizeof(float) * 4;
				}
				if (flags & Vertex::VF_UV) {
					vertexSize += sizeof(std::uint16_t) * 2;
				}
				if (flags & Vertex::VF_UV_2) {
					vertexSize += sizeof(std::uint16_t) * 2;
				}
				if (flags & Vertex::VF_NORMAL) {
					vertexSize += sizeof(std::uint16_t) * 2;
					if (flags & Vertex::VF_TANGENT) {
						vertexSize += sizeof(std::uint16_t) * 2;
					}
				}
				if (flags & Vertex::VF_COLORS) {
					vertexSize += sizeof(std::uint8_t) * 4;
				}
				if (flags & Vertex::VF_SKINNED) {
					vertexSize += sizeof(std::uint16_t) * 4 + sizeof(std::uint8_t) * 4;
				}
				if (flags & Vertex::VF_EYEDATA) {
					vertexSize += sizeof(float);
				}

				return vertexSize;
			}

		private:
			// members
			std::uint64_t desc;  // 00
		};
		static_assert(sizeof(VertexDesc) == 0x8);
	}
}

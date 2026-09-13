#pragma once

namespace RE
{
	class hkCustomAttributes;
	class hkClass;
	class hkClassEnum;

	/// Reflection information for a data member of a type.
	class hkClassMember
	{
	public:
		enum Type
		{
			/// No type
			TYPE_VOID = 0,
			/// hkBool,  boolean type
			TYPE_BOOL,
			/// hkChar, signed char type
			TYPE_CHAR,
			/// hkInt8, 8 bit signed integer type
			TYPE_INT8,
			/// std::uint8_t, 8 bit unsigned integer type
			TYPE_UINT8,
			/// hkInt16, 16 bit signed integer type
			TYPE_INT16,
			/// hkUint16, 16 bit unsigned integer type
			TYPE_UINT16,
			/// hkInt32, 32 bit signed integer type
			TYPE_INT32,
			/// hkUint32, 32 bit unsigned integer type
			TYPE_UINT32,
			/// hkInt64, 64 bit signed integer type
			TYPE_INT64,
			/// hkUint64, 64 bit unsigned integer type
			TYPE_UINT64,
			/// hkReal, float type
			TYPE_REAL,
			/// hkVector4 type
			TYPE_VECTOR4,
			/// hkQuaternion type
			TYPE_QUATERNION,
			/// hkMatrix3 type
			TYPE_MATRIX3,
			/// hkRotation type
			TYPE_ROTATION,
			/// hkQsTransform type
			TYPE_QSTRANSFORM,
			/// hkMatrix4 type
			TYPE_MATRIX4,
			/// hkTransform type
			TYPE_TRANSFORM,
			/// Serialize as zero - deprecated.
			TYPE_ZERO,
			/// Generic pointer, see member flags for more info
			TYPE_POINTER,
			/// Function pointer
			TYPE_FUNCTIONPOINTER,
			/// hkArray<T>, array of items of type T
			TYPE_ARRAY,
			/// hkInplaceArray<T,N> or hkInplaceArrayAligned16<T,N>, array of N items of type T
			TYPE_INPLACEARRAY,
			/// hkEnum<ENUM,STORAGE> - enumerated values
			TYPE_ENUM,
			/// Object
			TYPE_STRUCT,
			/// Simple array (ptr(typed) and size only)
			TYPE_SIMPLEARRAY,
			/// Simple array of homogeneous types, so is a class id followed by a void* ptr and size
			TYPE_HOMOGENEOUSARRAY,
			/// hkVariant (void* and hkClass*) type
			TYPE_VARIANT,
			/// char*, null terminated string
			TYPE_CSTRING,
			/// hkUlong, unsigned long, defined to always be the same size as a pointer
			TYPE_ULONG,
			/// hkFlags<ENUM,STORAGE> - 8,16,32 bits of named values.
			TYPE_FLAGS,
			/// hkHalf, 16-bit float value
			TYPE_HALF,
			/// hkStringPtr, c-string
			TYPE_STRINGPTR,
			TYPE_MAX
		};

		/// Special member properties.
		enum FlagValues
		{
			FLAGS_NONE = 0,
			/// Member has forced 8 byte alignment.
			ALIGN_8 = 128,
			/// Member has forced 16 byte alignment.
			ALIGN_16 = 256,
			/// The members memory contents is not owned by this object
			NOT_OWNED = 512,
			/// This member should not be written when serializing
			SERIALIZE_IGNORED = 1024
		};

		enum DeprecatedFlagValues
		{
			DEPRECATED_SIZE_8 = 8,
			DEPRECATED_ENUM_8 = 8,
			DEPRECATED_SIZE_16 = 16,
			DEPRECATED_ENUM_16 = 16,
			DEPRECATED_SIZE_32 = 32,
			DEPRECATED_ENUM_32 = 32
		};

		/// Properties of the builtin types.
		struct TypeProperties
		{
			/// The type associated with this
			stl::enumeration<Type, std::uint8_t> m_type;
			/// Zero terminated name
			const char* m_name;
			/// Size of the type in bytes <=0 it is not defined
			short m_size;
			/// Alignment in bytes, if <=0 it is not defined
			short m_align;
		};

		const char*                                 m_name;        // 00
		const hkClass*                              m_class;       // 08
		const hkClassEnum*                          m_enum;        // 10
		stl::enumeration<Type, std::uint8_t>        m_type;        // 18
		stl::enumeration<Type, std::uint8_t>        m_subtype;     // 19
		std::int16_t                                m_cArraySize;  // 1A
		stl::enumeration<FlagValues, std::uint16_t> m_flags;       // 1C
		std::uint16_t                               m_offset;      // 1E
		const hkCustomAttributes*                   m_attributes;  // 20
	};
	static_assert(sizeof(hkClassMember) == 0x28);
}

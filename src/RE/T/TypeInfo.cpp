#include "RE/T/TypeInfo.h"
#include "RE/O/ObjectTypeInfo.h"

namespace RE
{
	namespace BSScript
	{
		TypeInfo::TypeInfo() :
			_rawType(RawType::kNone)
		{}

		TypeInfo::TypeInfo(RawType a_type) :
			_rawType(a_type)
		{}

		TypeInfo::TypeInfo(const TypeInfo& a_rhs) :
			_rawType(a_rhs._rawType)
		{}

		TypeInfo::TypeInfo(TypeInfo&& a_rhs) :
			_rawType(std::move(a_rhs._rawType))
		{
			a_rhs._rawType = RawType::kNone;
		}

		TypeInfo& TypeInfo::operator=(const TypeInfo& a_rhs)
		{
			_rawType = a_rhs._rawType;
			return *this;
		}

		TypeInfo& TypeInfo::operator=(TypeInfo&& a_rhs)
		{
			_rawType = std::move(a_rhs._rawType);
			a_rhs._rawType = RawType::kNone;
			return *this;
		}

		TypeInfo& TypeInfo::operator=(RawType a_rhs)
		{
			_rawType = a_rhs;
			return *this;
		}

		bool operator==(const TypeInfo& a_lhs, const TypeInfo& a_rhs)
		{
			return a_lhs.GetRawType() == a_rhs.GetRawType();
		}

		bool operator!=(const TypeInfo& a_lhs, const TypeInfo& a_rhs)
		{
			return !(a_lhs == a_rhs);
		}

		bool operator<(const TypeInfo& a_lhs, const TypeInfo& a_rhs)
		{
			return a_lhs.GetRawType() < a_rhs.GetRawType();
		}

		bool operator<=(const TypeInfo& a_lhs, const TypeInfo& a_rhs)
		{
			return !(a_lhs > a_rhs);
		}

		bool operator>(const TypeInfo& a_lhs, const TypeInfo& a_rhs)
		{
			return a_rhs < a_lhs;
		}

		bool operator>=(const TypeInfo& a_lhs, const TypeInfo& a_rhs)
		{
			return !(a_lhs < a_rhs);
		}

		auto TypeInfo::GetRawType() const
			-> RawType
		{
			return *_rawType;
		}

		ObjectTypeInfo* TypeInfo::GetTypeInfo() const
		{
			assert(IsObject() || IsObjectArray());
			if (IsObject()) {
				return reinterpret_cast<ObjectTypeInfo*>(std::to_underlying(GetRawType()) & ~std::to_underlying(RawType::kObject));
			} else {
				return reinterpret_cast<ObjectTypeInfo*>(std::to_underlying(GetRawType()) & ~std::to_underlying(RawType::kObjectArray));
			}
		}

		auto TypeInfo::GetUnmangledRawType() const
			-> RawType
		{
			if (_rawType < RawType::kArraysEnd) {
				return GetRawType();
			} else {
				return _rawType.all(RawType::kObject) ? RawType::kObjectArray : RawType::kObject;
			}
		}

		bool TypeInfo::IsArray() const
		{
			return IsLiteralArray() || IsObjectArray();
		}

		bool TypeInfo::IsBool() const
		{
			return _rawType == RawType::kBool;
		}

		bool TypeInfo::IsFloat() const
		{
			return _rawType == RawType::kFloat;
		}

		bool TypeInfo::IsInt() const
		{
			return _rawType == RawType::kInt;
		}

		bool TypeInfo::IsLiteralArray() const
		{
			switch (*_rawType) {
			case RawType::kStringArray:
			case RawType::kIntArray:
			case RawType::kFloatArray:
			case RawType::kBoolArray:
				return true;
			default:
				return false;
			}
		}

		bool TypeInfo::IsNoneArray() const
		{
			return _rawType == RawType::kNoneArray;
		}

		bool TypeInfo::IsNoneObject() const
		{
			return _rawType == RawType::kNone;
		}

		bool TypeInfo::IsObject() const
		{
			return GetUnmangledRawType() == RawType::kObject;
		}

		bool TypeInfo::IsObjectArray() const
		{
			return (_rawType >= RawType::kArraysEnd) && _rawType.all(RawType::kObject);
		}

		bool TypeInfo::IsString() const
		{
			return _rawType == RawType::kString;
		}

		std::string TypeInfo::TypeAsString() const
		{
			switch (GetUnmangledRawType()) {
			case RawType::kNone:
				return "none";
			case RawType::kString:
				return "string";
			case RawType::kInt:
				return "int";
			case RawType::kFloat:
				return "float";
			case RawType::kBool:
				return "bool";
			case RawType::kObject:
				{
					auto info = GetTypeInfo();
					return info ? info->name.c_str() : "none";
				}
			case RawType::kNoneArray:
				return "none";
			case RawType::kObjectArray:
				{
					auto info = GetTypeInfo();
					return info ? std::string(info->name.c_str()) + "[]" : "none";
				}
			case RawType::kStringArray:
				return "string[]";
			case RawType::kIntArray:
				return "int[]";
			case RawType::kFloatArray:
				return "float[]";
			case RawType::kBoolArray:
				return "bool[]";
			default:
				return "";
			}
		}

		void TypeInfo::SetType(RawType a_type)
		{
			_rawType = a_type;
		}
	}
}

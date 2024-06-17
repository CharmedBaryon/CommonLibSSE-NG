#pragma once

#include "RE/N/NiProperty.h"

namespace RE
{
	class NiAlphaProperty : public NiProperty
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiAlphaProperty;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiAlphaProperty;
		inline static constexpr auto VTABLE = VTABLE_NiAlphaProperty;

		enum class AlphaFunction
		{
			kOne,
			kZero,
			kSrcColor,
			kInvSrcColor,
			kDestColor,
			kInvDestColor,
			kSrcAlpha,
			kInvSrcAlpha,
			kDestAlpha,
			kInvDestAlpha,
			kSrcAlphaSat
		};

		enum class TestFunction
		{
			kAlways,
			kLess,
			kEqual,
			kLessEqual,
			kGreater,
			kNotEqual,
			kGreaterEqual,
			kNever
		};

		~NiAlphaProperty() override;  // 00

		// override (NiProperty)
		const NiRTTI*      GetRTTI() const override;                           // 02
		NiObject*          CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void               LoadBinary(NiStream& a_stream) override;            // 18
		void               LinkObject(NiStream& a_stream) override;            // 19 - { NiProperty::LinkObject(a_stream); }
		bool               RegisterStreamables(NiStream& a_stream) override;   // 1A - { return NiProperty::RegisterStreamables(a_stream); }
		void               SaveBinary(NiStream& a_stream) override;            // 1B
		bool               IsEqual(NiObject* a_object) override;               // 1C
		[[nodiscard]] Type GetType() const override;                           // 25 - { return Type::kAlpha; }

		[[nodiscard]] bool          GetAlphaBlending() const;
		[[nodiscard]] bool          GetAlphaTesting() const;
		[[nodiscard]] AlphaFunction GetDestBlendMode() const;
		[[nodiscard]] AlphaFunction GetSrcBlendMode() const;
		void                        SetAlphaBlending(bool a_enable);
		void                        SetAlphaTesting(bool a_enable);
		void                        SetDestBlendMode(AlphaFunction a_mode);
		void                        SetSrcBlendMode(AlphaFunction a_mode);

		// members
		std::uint16_t alphaFlags;      // 30
		std::uint8_t  alphaThreshold;  // 32
		std::uint8_t  pad33;           // 33
		std::uint32_t pad34;           // 34
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(NiAlphaProperty) == 0x38);
}

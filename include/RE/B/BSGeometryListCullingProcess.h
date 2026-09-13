#pragma once

namespace RE
{
	class BSGeometryListCullingProcess : public BSCullingProcess
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSGeometryListCullingProcess;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSGeometryListCullingProcess;
		inline static constexpr auto VTABLE = VTABLE_BSGeometryListCullingProcess;

		// override (BSCullingProcess)
		const NiRTTI* GetRTTI() const override;  // 00

		~BSGeometryListCullingProcess() override;  // 15

		void AppendNonAccum(NiAVObject& a_object, std::int32_t a_alphaGroupIndex) override;  // 19

		// members
		std::uint32_t unk301F8;  // 301F8
	};
	static_assert(sizeof(BSGeometryListCullingProcess) == 0x30200);
}
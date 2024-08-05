#pragma once

#	include "RE/B/BSTSmartPointer.h"
#	include "RE/T/TESCamera.h"

namespace RE
{
	namespace MapCameraStates
	{
		class Exit : public TESCameraState
		{
		public:
			inline static constexpr auto RTTI = RTTI_MapCameraStates__Exit;
			inline static constexpr auto VTABLE = VTABLE_MapCameraStates__Exit;
		};

		class Transition : public TESCameraState
		{
		public:
			inline static constexpr auto RTTI = RTTI_MapCameraStates__Transition;
			inline static constexpr auto VTABLE = VTABLE_MapCameraStates__Transition;

			std::uint32_t unk20;
			std::uint32_t unk24;
			std::uint32_t unk28;
			std::uint32_t unk2C;
			std::uint32_t unk30;
			std::uint32_t unk34;
			std::uint32_t unk38;
			std::uint32_t unk3C;
			NiPoint3      currentPosition;  // 40
			NiPoint3      zoomDestination;  // 4C
			std::uint32_t unk58;
			std::uint32_t unk5C;
			NiPoint3      zoomOrigin;  // 60
		};
		static_assert(sizeof(Transition) == 0x70);

		class World : public TESCameraState
		{
		public:
			inline static constexpr auto RTTI = RTTI_MapCameraStates__World;
			inline static constexpr auto VTABLE = VTABLE_MapCameraStates__World;

			struct MapData
			{
				void*         unk00;
				void*         unk08;
				std::uint32_t unk10;
				std::uint32_t unk14;
				std::uint32_t unk18;
				NiPoint2      minimumCoordinates;
				NiPoint2      maximumCoordinates;
			};

			NiPoint3      currentPosition;              // 20
			NiPoint3      currentPositionScrollOffset;  // 2C
			NiPoint3      unk38;                        // 38
			NiPoint3      unk44;                        // 44
			std::uint32_t unk50;                        // 50
			std::uint32_t unk54;                        // 54
			std::float_t  multiplierOfUnk44;            // 58
			std::uint32_t unk5C;
			std::uint32_t unk60;
			std::uint32_t unk64;
			MapData*      mapData;  // 68
		};
		static_assert(sizeof(World) == 0x70);
	}

	class TESWorldSpace;
	struct IMapCameraCallbacks;

	class MapCamera : public TESCamera
	{
	public:
		inline static constexpr auto RTTI = RTTI_MapCamera;
		inline static constexpr auto VTABLE = VTABLE_MapCamera;

		~MapCamera() override;  // 00

		// add
		virtual void Unk_03(void);  // 03

		// members
		float                                        unk38;       // 38
		float                                        unk3C;       // 3C
		float                                        unk40;       // 40
		float                                        unk44;       // 44
		float                                        unk48;       // 48
		std::uint32_t                                unk4C;       // 4C
		TESWorldSpace*                               worldSpace;  // 50
		IMapCameraCallbacks*                         unk58;       // 58
		std::uint32_t                                unk60;       // 60
		std::uint32_t                                unk64;       // 64
		BSTSmartPointer<MapCameraStates::World>      unk68[2];    // 68
		BSTSmartPointer<MapCameraStates::Exit>       unk78;       // 78
		BSTSmartPointer<MapCameraStates::Transition> unk80;       // 80
		std::uint8_t                                 unk88;       // 88
		std::uint8_t                                 pad89;       // 89
		std::uint16_t                                pad8A;       // 8A
		std::uint32_t                                pad8C;       // 8C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(MapCamera) == 0x90);
}

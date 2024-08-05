#pragma once

#include "REL/ID.h"

namespace RE::Offset
{
	namespace Actor
	{
		constexpr auto AddSpell = RELOCATION_ID(37771, 38716);
		constexpr auto DispelWornItemEnchantments = RELOCATION_ID(33828, 34620);
		constexpr auto DoReset3D = RELOCATION_ID(39181, 40255);
		constexpr auto GetGhost = RELOCATION_ID(36286, 37275);
		constexpr auto GetHostileToActor = RELOCATION_ID(36537, 37537);
		constexpr auto GetLevel = RELOCATION_ID(36344, 37334);
		constexpr auto HasPerk = RELOCATION_ID(36690, 37698);
		constexpr auto IsRunning = RELOCATION_ID(36252, 37234);
		constexpr auto RequestDetectionLevel = RELOCATION_ID(36748, 37764);
		constexpr auto SwitchRace = RELOCATION_ID(36901, 37925);
		constexpr auto UpdateArmorAbility = RELOCATION_ID(37802, 38751);
		constexpr auto UpdateWeaponAbility = RELOCATION_ID(37803, 38752);
	}

	namespace ActorEquipManager
	{
		constexpr auto EquipObject = RELOCATION_ID(37938, 38894);
		constexpr auto Singleton = RELOCATION_ID(514494, 400636);
		constexpr auto UnequipObject = RELOCATION_ID(37945, 38901);
	}

	namespace ActorValueOwner
	{
		constexpr auto GetClampedActorValue = RELOCATION_ID(26616, 27284);
	}

	namespace AIProcess
	{
		constexpr auto SetBaseScale = RELOCATION_ID(38568, 39588);
		constexpr auto Update3DModel = RELOCATION_ID(38404, 39395);
	}

	namespace BGSFootstepManager
	{
		constexpr auto Singleton = RELOCATION_ID(517045, 403553);
	}

	namespace BGSListForm
	{
		constexpr auto AddForm = RELOCATION_ID(20470, 20913);
	}

	namespace BGSSaveLoadManager
	{
		constexpr auto Save = RELOCATION_ID(34818, 35727);
		constexpr auto Singleton = RELOCATION_ID(516860, 403340);
		constexpr auto Load = RELOCATION_ID(34819, 35728);
	}

	namespace BGSSkillPerkTreeNode
	{
		constexpr auto Ctor = RELOCATION_ID(26592, 27263);
	}

	namespace BGSStoryEventManager
	{
		constexpr auto AddEvent = RELOCATION_ID(31576, 32359);
		constexpr auto GetSingleton = RELOCATION_ID(22317, 22790);
	}

	namespace BGSStoryTeller
	{
		constexpr auto BeginShutDownQuest = RELOCATION_ID(31718, 32486);
		constexpr auto BeginStartUpQuest = RELOCATION_ID(31717, 32485);
		constexpr auto Singleton = RELOCATION_ID(514316, 400476);
	}

	namespace BipedAnim
	{
		constexpr auto Dtor = RELOCATION_ID(15491, 15656);
		constexpr auto RemoveAllParts = RELOCATION_ID(15494, 15659);
	}

	namespace BSAudioManager
	{
		constexpr auto GetSingleton = RELOCATION_ID(66391, 67652);
		constexpr auto BuildSoundDataFromDescriptor = RELOCATION_ID(66404, 67666);
	}

	namespace BSInputDeviceManager
	{
		constexpr auto Singleton = RELOCATION_ID(516574, 402776);
	}

	namespace BSLightingShaderMaterialBase
	{
		constexpr auto CreateMaterial = RELOCATION_ID(100016, 106723);
	}

	namespace BSReadWriteLock
	{
		constexpr auto LockForRead = RELOCATION_ID(66976, 68233);
		constexpr auto LockForWrite = RELOCATION_ID(66977, 68234);
		constexpr auto UnlockForRead = RELOCATION_ID(66982, 68239);
		constexpr auto UnlockForWrite = RELOCATION_ID(66983, 68240);
	}

	namespace BSResourceNiBinaryStream
	{
		constexpr auto Ctor = RELOCATION_ID(69636, 71014);
		constexpr auto Dtor = RELOCATION_ID(69638, 71016);
		constexpr auto Seek = RELOCATION_ID(69640, 71018);
		constexpr auto SetEndianSwap = RELOCATION_ID(69643, 71021);
	}

	namespace BSScript
	{
		namespace ObjectBindPolicy
		{
			constexpr auto BindObject = RELOCATION_ID(97379, 104184);
		}

		namespace NF_util
		{
			namespace NativeFunctionBase
			{
				constexpr auto Call = RELOCATION_ID(97923, 104651);
			}
		}

		namespace Stack
		{
			constexpr auto Dtor = RELOCATION_ID(97742, 104480);
		}
	}

	namespace BSSoundHandle
	{
		constexpr auto IsValid = RELOCATION_ID(66360, 67621);
		constexpr auto Pause = RELOCATION_ID(66357, 67618);
		constexpr auto Play = RELOCATION_ID(66355, 67616);
		constexpr auto SetObjectToFollow = RELOCATION_ID(66375, 67636);
		constexpr auto SetPosition = RELOCATION_ID(66370, 67631);
		constexpr auto Stop = RELOCATION_ID(66358, 67619);
	}

	namespace BSString
	{
		constexpr auto Set_CStr = RELOCATION_ID(10979, 11044);
	}

	namespace BucketTable
	{
		constexpr auto GetSingleton = RELOCATION_ID(67855, 69200);
	}

	namespace BSWin32SaveDataSystemUtility
	{
		constexpr auto GetSingleton = RELOCATION_ID(101884, 109278);
	}

	namespace Calendar
	{
		constexpr auto Singleton = RELOCATION_ID(514287, 400447);
	}

	namespace Console
	{
		constexpr auto SetSelectedRef = RELOCATION_ID(50164, 51093);
	}

	namespace ConsoleLog
	{
		constexpr auto Singleton = RELOCATION_ID(515064, 401203);
		constexpr auto VPrint = RELOCATION_ID(50180, 51110);
	}

	namespace ControlMap
	{
		constexpr auto Singleton = RELOCATION_ID(514705, 400863);
	}

	namespace CraftingSubMenus
	{
		namespace EnchantConstructMenu
		{
			constexpr auto RenameItem = RELOCATION_ID(50530, 51415);
			constexpr auto UpdateInterface = RELOCATION_ID(50567, 51459);
		}
	}

	namespace CRC32Calculator
	{
		constexpr auto SizeOf32 = RELOCATION_ID(66963, 12141);
		constexpr auto SizeOf64 = RELOCATION_ID(66964, 68221);
		constexpr auto SizeOfSize = RELOCATION_ID(66962, 68219);
	}

	namespace ExtraDataList
	{
		constexpr auto Add = RELOCATION_ID(12176, 12315);
		constexpr auto SetCount = RELOCATION_ID(11471, 11617);
		constexpr auto SetExtraFlags = RELOCATION_ID(11903, 12042);
		constexpr auto SetInventoryChanges = RELOCATION_ID(11483, 11600);
	}

	namespace GameSettingCollection
	{
		constexpr auto Singleton = RELOCATION_ID(514622, 400782);
	}

#if defined(EXCLUSIVE_SKYRIM_AE)
	namespace GASActionBufferData
	{
		constexpr auto Vtbl = RELOCATION_ID(0, 242366);
	}

	namespace GASDoAction
	{
		constexpr auto Vtbl = RELOCATION_ID(0, 242413);
	}

	namespace GASDoInitAction
	{
		constexpr auto Vtbl = RELOCATION_ID(0, 242414);
	}

	namespace GFxInitImportActions
	{
		constexpr auto Vtbl = RELOCATION_ID(0, 244866);
	}
#endif

	namespace GFxLoader
	{
		constexpr auto CreateMovie = RELOCATION_ID(80620, 84640);
	}

	namespace GFxMovieView
	{
		constexpr auto InvokeNoReturn = RELOCATION_ID(80547, 82665);
	}

#if defined(EXCLUSIVE_SKYRIM_AE)
	namespace GFxPlaceObject2
	{
		constexpr auto Vtbl = RELOCATION_ID(0, 242592);
	}

	namespace GFxPlaceObject3
	{
		constexpr auto Vtbl = RELOCATION_ID(0, 242593);
	}

	namespace GFxRemoveObject
	{
		constexpr auto Vtbl = RELOCATION_ID(0, 244863);
	}

	namespace GFxRemoveObject2
	{
		constexpr auto Vtbl = RELOCATION_ID(0, 244864);
	}

	namespace GFxSetBackgroundColor
	{
		constexpr auto Vtbl = RELOCATION_ID(0, 244865);
	}
#endif

	namespace GFxValue
	{
		namespace ObjectInterface
		{
			constexpr auto AttachMovie = RELOCATION_ID(80197, 82219);
			constexpr auto DeleteMember = RELOCATION_ID(80207, 82230);
			constexpr auto GetArraySize = RELOCATION_ID(80214, 82237);
			constexpr auto GetCxform = RELOCATION_ID(80215, 82238);
			constexpr auto GetDisplayInfo = RELOCATION_ID(80216, 82239);
			constexpr auto GetDisplayMatrix = RELOCATION_ID(80217, 82240);
			constexpr auto GetElement = RELOCATION_ID(80218, 82241);
			constexpr auto GetMember = RELOCATION_ID(80222, 82245);
			constexpr auto GotoAndPlay = RELOCATION_ID(80230, 82253);
			constexpr auto HasMember = RELOCATION_ID(80231, 82254);
			constexpr auto Invoke = RELOCATION_ID(80233, 82256);
			constexpr auto ObjectAddRef = RELOCATION_ID(80244, 82269);
			constexpr auto ObjectRelease = RELOCATION_ID(80245, 82270);
			constexpr auto PushBack = RELOCATION_ID(80248, 82273);
			constexpr auto RemoveElements = RELOCATION_ID(80252, 82280);
			constexpr auto SetArraySize = RELOCATION_ID(80261, 82285);
			constexpr auto SetCxform = RELOCATION_ID(80262, 82286);
			constexpr auto SetDisplayInfo = RELOCATION_ID(80263, 82287);
			constexpr auto SetDisplayMatrix = RELOCATION_ID(80264, 82288);
			constexpr auto SetElement = RELOCATION_ID(80265, 82289);
			constexpr auto SetMember = RELOCATION_ID(80268, 82292);
			constexpr auto SetText = RELOCATION_ID(80270, 82293);
			constexpr auto VisitMembers = RELOCATION_ID(80279, 82302);
		}
	}

	namespace GMemory
	{
		constexpr auto GlobalHeap = RELOCATION_ID(525584, 412058);
	}

	namespace hkReferencedObject
	{
		constexpr auto AddReference = RELOCATION_ID(56606, 57010);
		constexpr auto RemoveReference = RELOCATION_ID(56607, 57011);
	}

	namespace INIPrefSettingCollection
	{
		constexpr auto Singleton = RELOCATION_ID(523673, 410219);
	}

	namespace INISettingCollection
	{
		constexpr auto Singleton = RELOCATION_ID(524557, 411155);
	}

	namespace InterfaceStrings
	{
		constexpr auto Singleton = RELOCATION_ID(514286, 400446);
	}

	namespace Inventory
	{
		constexpr auto GetEventSource = RELOCATION_ID(15980, 16225);
	}

	namespace InventoryChanges
	{
		constexpr auto GetNextUniqueID = RELOCATION_ID(15908, 16148);
		constexpr auto SendContainerChangedEvent = RELOCATION_ID(15909, 16149);
		constexpr auto SetUniqueID = RELOCATION_ID(15907, 16149);
		constexpr auto TransferItemUID = RELOCATION_ID(15909, 16149);
	}

	namespace ItemCrafted
	{
		constexpr auto GetEventSource = RELOCATION_ID(50515, 51403);
	}

	namespace ItemList
	{
		constexpr auto Update = RELOCATION_ID(50099, 51031);
	}

	namespace ItemsPickpocketed
	{
		constexpr auto GetEventSource = RELOCATION_ID(50258, 51183);
	}

	namespace LocalMapCamera
	{
		constexpr auto Ctor = RELOCATION_ID(16084, 16325);
		constexpr auto SetNorthRotation = RELOCATION_ID(16089, 16330);
	}

	namespace MagicFavorites
	{
		constexpr auto Singleton = RELOCATION_ID(516858, 403337);
	}

	namespace MagicItem
	{
		constexpr auto CalculateCost = RELOCATION_ID(11213, 11321);
		constexpr auto GetCostliestEffectItem = RELOCATION_ID(11216, 11335);
	}

	namespace MagicTarget
	{
		constexpr auto HasMagicEffect = RELOCATION_ID(33733, 34517);
	}

	namespace Main
	{
		constexpr auto Singleton = RELOCATION_ID(516943, 403449);
	}

	namespace MenuControls
	{
		constexpr auto Singleton = RELOCATION_ID(515124, 401263);
	}

	namespace MessageDataFactoryManager
	{
		constexpr auto GetSingleton = RELOCATION_ID(22843, 52875);
	}

	namespace NiAVObject
	{
		constexpr auto SetMotionType = RELOCATION_ID(76033, 77866);
		constexpr auto Update = RELOCATION_ID(68900, 70251);
	}

	namespace NiCamera
	{
		constexpr auto WorldPtToScreenPt3 = RELOCATION_ID(69270, 70640);
	}

	namespace NiMemManager
	{
		constexpr auto Singleton = RELOCATION_ID(523759, 410319);
	}

	namespace NiNode
	{
		constexpr auto Ctor = RELOCATION_ID(68936, 70287);
	}

	namespace NiPoint3
	{
		constexpr auto Zero = RELOCATION_ID(523887, 410468);
	}

	namespace NiRefObject
	{
		constexpr auto TotalObjectCount = RELOCATION_ID(523912, 410493);
	}

	namespace NiSkinInstance
	{
		constexpr auto Ctor = RELOCATION_ID(69804, 71227);
	}

	namespace PlayerCamera
	{
		constexpr auto Singleton = RELOCATION_ID(514642, 400802);
		constexpr auto UpdateThirdPerson = RELOCATION_ID(49908, 50841);
	}

	namespace PlayerCharacter
	{
		namespace PlayerSkills
		{
			constexpr auto AdvanceLevel = RELOCATION_ID(40560, 41567);
		}

		constexpr auto ActivatePickRef = RELOCATION_ID(39471, 40548);
		constexpr auto GetArmorValue = RELOCATION_ID(39175, 40249);
		constexpr auto GetDamage = RELOCATION_ID(39179, 40253);
		constexpr auto GetNumTints = RELOCATION_ID(39614, 40700);
		constexpr auto GetTintMask = RELOCATION_ID(39612, 40698);
		constexpr auto PlayPickupEvent = RELOCATION_ID(39384, 40456);
		constexpr auto Singleton = RELOCATION_ID(517014, 403521);
		constexpr auto StartGrabObject = RELOCATION_ID(39475, 40552);
	}

	namespace PlayerControls
	{
		constexpr auto Ctor = RELOCATION_ID(41257, 42336);
		constexpr auto Singleton = RELOCATION_ID(514706, 400864);
	}

	namespace RaceSexMenu
	{
		constexpr auto ChangeName = RELOCATION_ID(51540, 52415);
	}

	namespace ReferenceEffectController
	{
		constexpr auto Start = RELOCATION_ID(33961, 34761);
	}

	namespace Script
	{
		constexpr auto GetProcessScripts = RELOCATION_ID(21436, 21921);
		constexpr auto SetProcessScripts = RELOCATION_ID(21435, 21920);
	}

	namespace SCRIPT_FUNCTION
	{
		constexpr auto FirstConsoleCommand = RELOCATION_ID(501797, 365650);
		constexpr auto FirstScriptCommand = RELOCATION_ID(501789, 361120);
	}

	namespace Sky
	{
		constexpr auto GetSingleton = RELOCATION_ID(13789, 13878);
		constexpr auto SetWeather = RELOCATION_ID(25694, 26241);
		constexpr auto ForceWeather = RELOCATION_ID(25696, 26243);
		constexpr auto ResetWeather = RELOCATION_ID(25695, 26242);
	}

	namespace SkyrimVM
	{
		constexpr auto QueuePostRenderCall = RELOCATION_ID(53144, 53955);
		constexpr auto RelayEvent = RELOCATION_ID(53221, 54033);
		constexpr auto Singleton = RELOCATION_ID(514315, 400475);
	}

	namespace TES
	{
		constexpr auto Singleton = RELOCATION_ID(516923, 403450);
	}

	namespace TESCamera
	{
		constexpr auto SetState = RELOCATION_ID(32290, 33026);
	}

	namespace TESDataHandler
	{
		constexpr auto LoadScripts = RELOCATION_ID(13657, 13766);
		constexpr auto Singleton = RELOCATION_ID(514141, 400269);
	}

	namespace TESDescription
	{
		constexpr auto GetDescription = RELOCATION_ID(14399, 14552);
	}

	namespace TESFile
	{
		constexpr auto Duplicate = RELOCATION_ID(13923, 14018);
		constexpr auto GetCurrentSubRecordType = RELOCATION_ID(13902, 13988);
		constexpr auto GetFormType = RELOCATION_ID(13897, 13982);
		constexpr auto ReadData = RELOCATION_ID(13904, 13991);
		constexpr auto Seek = RELOCATION_ID(13898, 13984);
		constexpr auto SeekNextSubrecord = RELOCATION_ID(13903, 13990);
	}

	namespace TESHavokUtilities
	{
		constexpr auto FindCollidableRef = RELOCATION_ID(25466, 26003);
	}

	namespace TESNPC
	{
		constexpr auto ChangeHeadPart = RELOCATION_ID(24246, 24750);
		constexpr auto GetBaseOverlays = RELOCATION_ID(24275, 24791);
		constexpr auto GetNumBaseOverlays = RELOCATION_ID(24276, 24792);
		constexpr auto HasOverlays = RELOCATION_ID(24274, 24790);
		constexpr auto SetSkinFromTint = RELOCATION_ID(24206, 24710);
		constexpr auto UpdateNeck = RELOCATION_ID(24207, 24711);
	}

	namespace TESObjectREFR
	{
		constexpr auto FindReferenceFor3D = RELOCATION_ID(19323, 19750);
		constexpr auto GetDisplayFullName = RELOCATION_ID(19354, 19781);
		constexpr auto GetLock = RELOCATION_ID(19818, 20223);
		constexpr auto GetOwner = RELOCATION_ID(19789, 20194);
		constexpr auto GetStealValue = RELOCATION_ID(15807, 16045);
		constexpr auto InitInventoryIfRequired = RELOCATION_ID(15800, 16038);
		constexpr auto MoveTo = RELOCATION_ID(56227, 56626);
		constexpr auto PlayAnimation = RELOCATION_ID(14189, 14297);
	}

	namespace TESQuest
	{
		constexpr auto EnsureQuestStarted = RELOCATION_ID(24481, 25003);
		constexpr auto ResetQuest = RELOCATION_ID(24486, 25014);
	}

	namespace UI
	{
		constexpr auto Singleton = RELOCATION_ID(514178, 400327);
	}

	namespace UIBlurManager
	{
		constexpr auto DecrementBlurCount = RELOCATION_ID(51900, 52777);
		constexpr auto IncrementBlurCount = RELOCATION_ID(51899, 52776);
		constexpr auto Singleton = RELOCATION_ID(516871, 403350);
	}

	namespace UIMessageQueue
	{
		constexpr auto AddMessage = RELOCATION_ID(13530, 13631);
		constexpr auto CreateUIMessageData = RELOCATION_ID(80061, 82169);
		constexpr auto ProcessCommands = RELOCATION_ID(80059, 82167);
		constexpr auto Singleton = RELOCATION_ID(514285, 400445);
	}

	namespace UserEvents
	{
		constexpr auto Singleton = RELOCATION_ID(516458, 402638);
	}

	constexpr auto CreateRefHandle = RELOCATION_ID(12193, 12326);
	constexpr auto D3D11Device = RELOCATION_ID(524729, 411348);
	constexpr auto DebugNotification = RELOCATION_ID(52050, 52933);
	constexpr auto LookupReferenceByHandle = RELOCATION_ID(12204, 12332);
	constexpr auto PlaySound = RELOCATION_ID(52054, 52939);
	constexpr auto RendererShadowStateInstance = RELOCATION_ID(524773, 388819);
	constexpr auto TlsIndex = RELOCATION_ID(528600, 415542);
	constexpr auto GlobalStateCounter = RELOCATION_ID(514157, 400305);
}

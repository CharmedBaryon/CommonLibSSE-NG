#pragma once

#include "REL/Relocation.h"

namespace RE
{
	namespace Offset
	{
		namespace Actor
		{
			inline REL::ID AddSpell(REL::RelocationID(37771, 38716));
			inline REL::ID DispelWornItemEnchantments(REL::RelocationID(33828, 34620));
			inline REL::ID DoReset3D(REL::RelocationID(39181, 40255));
			inline REL::ID GetGhost(REL::RelocationID(36286, 37275));
			inline REL::ID GetHostileToActor(REL::RelocationID(36537, 37537));
			inline REL::ID GetLevel(REL::RelocationID(36344, 37334));
			inline REL::ID HasPerk(REL::RelocationID(36690, 37698));
			inline REL::ID IsRunning(REL::RelocationID(36252, 37234));
			inline REL::ID RequestDetectionLevel(REL::RelocationID(36748, 37764));
			inline REL::ID SwitchRace(REL::RelocationID(36901, 37925));
			inline REL::ID UpdateArmorAbility(REL::RelocationID(37802, 38751));
			inline REL::ID UpdateWeaponAbility(REL::RelocationID(37803, 38752));
		}

		namespace ActorEquipManager
		{
			inline REL::ID EquipObject(REL::RelocationID(37938, 38894));
			inline REL::ID Singleton(REL::RelocationID(514494, 400636));
			inline REL::ID UnequipObject(REL::RelocationID(37945, 38901));
		}

		namespace ActorValueOwner
		{
			inline REL::ID GetClampedActorValue(REL::RelocationID(26616, 27284));
		}

		namespace AIProcess
		{
			inline REL::ID SetBaseScale(REL::RelocationID(38568, 39588));
			inline REL::ID Update3DModel(REL::RelocationID(38404, 39395));
		}

		namespace BGSFootstepManager
		{
			inline REL::ID Singleton(REL::RelocationID(517045, 401262));
		}

		namespace BGSListForm
		{
			inline REL::ID AddForm(REL::RelocationID(20470, 20913));
		}

		namespace BGSSaveLoadManager
		{
			inline REL::ID Save(REL::RelocationID(34818, 35727));
			inline REL::ID Singleton(REL::RelocationID(516860, 403340));
			inline REL::ID Load(REL::RelocationID(34819, 35728));
		}

		namespace BGSStoryTeller
		{
			inline REL::ID BeginShutDownQuest(REL::RelocationID(31718, 32486));
			inline REL::ID BeginStartUpQuest(REL::RelocationID(31717, 32485));
			inline REL::ID Singleton(REL::RelocationID(514316, 400476));
		}

		namespace BipedAnim
		{
			inline REL::ID Dtor(REL::RelocationID(15491, 15656));
			inline REL::ID RemoveAllParts(REL::RelocationID(15494, 15659));
		}

		namespace BSAudioManager
		{
			inline REL::ID GetSingleton(REL::RelocationID(66391, 67652));
			inline REL::ID BuildSoundDataFromDescriptor(REL::RelocationID(66404, 67666));
		}

		namespace BSInputDeviceManager
		{
			inline REL::ID Singleton(REL::RelocationID(516574, 402776));
		}

		namespace BSLightingShaderMaterialBase
		{
			inline REL::ID CreateMaterial(REL::RelocationID(100016, 106723));
		}

		namespace BSReadWriteLock
		{
			inline REL::ID LockForRead(REL::RelocationID(66976, 68233));
			inline REL::ID LockForWrite(REL::RelocationID(66977, 68234));
			inline REL::ID UnlockForRead(REL::RelocationID(66982, 68239));
			inline REL::ID UnlockForWrite(REL::RelocationID(66983, 68240));
		}

		namespace BSResourceNiBinaryStream
		{
			inline REL::ID Ctor(REL::RelocationID(69636, 71014));
			inline REL::ID Dtor(REL::RelocationID(69638, 71016));
			inline REL::ID Seek(REL::RelocationID(69640, 71018));
			inline REL::ID SetEndianSwap(REL::RelocationID(69643, 71021));
		}

		namespace BSScript
		{
			namespace ObjectBindPolicy
			{
				inline REL::ID BindObject(REL::RelocationID(97379, 104184));
			}

			namespace NF_util
			{
				namespace NativeFunctionBase
				{
					inline REL::ID Call(REL::RelocationID(97923, 104651));
				}
			}

			namespace Stack
			{
				inline REL::ID Dtor(REL::RelocationID(97742, 104480));
			}
		}

		namespace BSSoundHandle
		{
			inline REL::ID IsValid(REL::RelocationID(66360, 67621));
			inline REL::ID Play(REL::RelocationID(66355, 67616));
			inline REL::ID SetObjectToFollow(REL::RelocationID(66375, 67636));
			inline REL::ID SetPosition(REL::RelocationID(66370, 67631));
			inline REL::ID Stop(REL::RelocationID(66358, 67619));
		}

		namespace BSString
		{
			inline REL::ID Set_CStr(REL::RelocationID(10979, 11044));
		}

		namespace BucketTable
		{
			inline REL::ID GetSingleton(REL::RelocationID(67855, 69200));
		}

		namespace BSWin32SaveDataSystemUtility
		{
			inline REL::ID GetSingleton(REL::RelocationID(101884, 109278));
		}

		namespace Calendar
		{
			inline REL::ID Singleton(REL::RelocationID(514287, 400447));
		}

		namespace Console
		{
			inline REL::ID SelectedRef(REL::RelocationID(519394, 405935));
			inline REL::ID SetSelectedRef(REL::RelocationID(50164, 51093));
		}

		namespace ConsoleLog
		{
			inline REL::ID Singleton(REL::RelocationID(515064, 401203));
			inline REL::ID VPrint(REL::RelocationID(50180, 51110));
		}

		namespace ControlMap
		{
			inline REL::ID Singleton(REL::RelocationID(514705, 400863));
		}

		namespace CRC32Calculator
		{
			inline REL::ID SizeOf32(REL::RelocationID(66963, 12141));
			inline REL::ID SizeOf64(REL::RelocationID(66964, 68221));
			inline REL::ID SizeOfSize(REL::RelocationID(66962, 68219));
		}

		namespace ExtraDataList
		{
			inline REL::ID Add(REL::RelocationID(12176, 12315));
			inline REL::ID SetExtraFlags(REL::RelocationID(11903, 12042));
			inline REL::ID SetInventoryChanges(REL::RelocationID(11483, 11600));
		}

		namespace GameSettingCollection
		{
			inline REL::ID Singleton(REL::RelocationID(514622, 400782));
		}

		namespace GFxLoader
		{
			inline REL::ID CreateMovie(REL::RelocationID(80620, 84640));
		}

		namespace GFxMovieView
		{
			inline REL::ID InvokeNoReturn(REL::RelocationID(80547, 82665));
		}

		namespace GFxValue
		{
			namespace ObjectInterface
			{
				inline REL::ID AttachMovie(REL::RelocationID(80197, 82219));
				inline REL::ID DeleteMember(REL::RelocationID(80207, 82230));
				inline REL::ID GetArraySize(REL::RelocationID(80214, 82237));
				inline REL::ID GetDisplayInfo(REL::RelocationID(80216, 82239));
				inline REL::ID GetElement(REL::RelocationID(80218, 82241));
				inline REL::ID GetMember(REL::RelocationID(80222, 82245));
				inline REL::ID GotoAndPlay(REL::RelocationID(80230, 82253));
				inline REL::ID HasMember(REL::RelocationID(80231, 82254));
				inline REL::ID Invoke(REL::RelocationID(80233, 82256));
				inline REL::ID ObjectAddRef(REL::RelocationID(80244, 82269));
				inline REL::ID ObjectRelease(REL::RelocationID(80245, 82270));
				inline REL::ID PushBack(REL::RelocationID(80248, 82273));
				inline REL::ID RemoveElements(REL::RelocationID(80252, 82280));
				inline REL::ID SetArraySize(REL::RelocationID(80261, 82285));
				inline REL::ID SetDisplayInfo(REL::RelocationID(80263, 82287));
				inline REL::ID SetElement(REL::RelocationID(80265, 82289));
				inline REL::ID SetMember(REL::RelocationID(80268, 82292));
				inline REL::ID SetText(REL::RelocationID(80270, 82293));
			}
		}

		namespace GMemory
		{
			inline REL::ID GlobalHeap(REL::RelocationID(525584, 412058));
		}

		namespace hkReferencedObject
		{
			inline REL::ID AddReference(REL::RelocationID(56606, 57010));
			inline REL::ID RemoveReference(REL::RelocationID(56607, 57011));
		}

		namespace INIPrefSettingCollection
		{
			inline REL::ID Singleton(REL::RelocationID(523673, 410219));
		}

		namespace INISettingCollection
		{
			inline REL::ID Singleton(REL::RelocationID(524557, 411155));
		}

		namespace InterfaceStrings
		{
			inline REL::ID Singleton(REL::RelocationID(514286, 400446));
		}

		namespace Inventory
		{
			inline REL::ID GetEventSource(REL::RelocationID(15980, 16225));
		}

		namespace InventoryChanges
		{
			inline REL::ID GetNextUniqueID(REL::RelocationID(15908, 16148));
			inline REL::ID SendContainerChangedEvent(REL::RelocationID(15909, 16149));
			inline REL::ID SetUniqueID(REL::RelocationID(15907, 16149));
			inline REL::ID TransferItemUID(REL::RelocationID(15909, 16149));
		}

		namespace ItemCrafted
		{
			inline REL::ID GetEventSource(REL::RelocationID(50515, 51403));
		}

		namespace ItemList
		{
			inline REL::ID Update(REL::RelocationID(50099, 51031));
		}

		namespace ItemsPickpocketed
		{
			inline REL::ID GetEventSource(REL::RelocationID(50258, 51183));
		}

		namespace LocalMapCamera
		{
			inline REL::ID Ctor(REL::RelocationID(16084, 16325));
			inline REL::ID SetNorthRotation(REL::RelocationID(16089, 16330));
		}

		namespace MagicFavorites
		{
			inline REL::ID Singleton(REL::RelocationID(516858, 403337));
		}

		namespace MagicItem
		{
			inline REL::ID CalculateCost(REL::RelocationID(11213, 11321));
			inline REL::ID GetCostliestEffectItem(REL::RelocationID(11216, 11335));
		}

		namespace MagicTarget
		{
			inline REL::ID HasMagicEffect(REL::RelocationID(33733, 34517));
		}

		namespace Main
		{
			inline REL::ID Singleton(REL::RelocationID(516943, 403449));
		}

		namespace MenuControls
		{
			inline REL::ID Singleton(REL::RelocationID(515124, 401263));
		}

		namespace MessageDataFactoryManager
		{
			inline REL::ID GetSingleton(REL::RelocationID(22843, 52875));
		}

		namespace NiAVObject
		{
			inline REL::ID SetMotionType(REL::RelocationID(76033, 77866));
			inline REL::ID Update(REL::RelocationID(68900, 70251));
		}

		namespace NiCamera
		{
			inline REL::ID WorldPtToScreenPt3(REL::RelocationID(69270, 70640));
		}

		namespace NiMemManager
		{
			inline REL::ID Singleton(REL::RelocationID(523759, 410319));
		}

		namespace NiNode
		{
			inline REL::ID Ctor(REL::RelocationID(68936, 70287));
		}

		namespace NiRefObject
		{
			inline REL::ID TotalObjectCount(REL::RelocationID(523912, 410493));
		}

		namespace NiSkinInstance
		{
			inline REL::ID Ctor(REL::RelocationID(69804, 71227));
		}

		namespace PlayerCamera
		{
			inline REL::ID Singleton(REL::RelocationID(514642, 400802));
			inline REL::ID UpdateThirdPerson(REL::RelocationID(49908, 50841));
		}

		namespace PlayerCharacter
		{
			namespace PlayerSkills
			{
				inline REL::ID AdvanceLevel(REL::RelocationID(40560, 41567));
			}

			inline REL::ID ActivatePickRef(REL::RelocationID(39471, 40548));
			inline REL::ID GetArmorValue(REL::RelocationID(39175, 40249));
			inline REL::ID GetDamage(REL::RelocationID(39179, 40253));
			inline REL::ID GetNumTints(REL::RelocationID(39614, 40700));
			inline REL::ID GetTintMask(REL::RelocationID(39612, 40698));
			inline REL::ID PlayPickupEvent(REL::RelocationID(39384, 40456));
			inline REL::ID Singleton(REL::RelocationID(517014, 403521));
			inline REL::ID StartGrabObject(REL::RelocationID(39475, 40552));
		}

		namespace PlayerControls
		{
			inline REL::ID Ctor(REL::RelocationID(41257, 42336));
			inline REL::ID Singleton(REL::RelocationID(514706, 400864));
		}

		namespace Script
		{
			inline REL::ID CompileAndRun(REL::RelocationID(21416, 21890));
		}

		namespace SCRIPT_FUNCTION
		{
			inline REL::ID FirstConsoleCommand(REL::RelocationID(501797, 365650));
			inline REL::ID FirstScriptCommand(REL::RelocationID(501789, 361120));
		}

		namespace Sky
		{
			inline REL::ID GetSingleton(REL::RelocationID(13789, 13878));
		}

		namespace SkyrimVM
		{
			inline REL::ID QueuePostRenderCall(REL::RelocationID(53144, 53955));
			inline REL::ID Singleton(REL::RelocationID(514315, 400475));
		}

		namespace TES
		{
			inline REL::ID Singleton(REL::RelocationID(516923, 403450));
		}

		namespace TESCamera
		{
			inline REL::ID SetState(REL::RelocationID(32290, 33026));
		}

		namespace TESDataHandler
		{
			inline REL::ID LoadScripts(REL::RelocationID(13657, 13766));
			inline REL::ID Singleton(REL::RelocationID(514141, 400269));
		}

		namespace TESDescription
		{
			inline REL::ID GetDescription(REL::RelocationID(14399, 14552));
		}

		namespace TESFile
		{
			inline REL::ID Duplicate(REL::RelocationID(13923, 14018));
			inline REL::ID GetCurrentSubRecordType(REL::RelocationID(13902, 13988));
			inline REL::ID GetFormType(REL::RelocationID(13897, 13982));
			inline REL::ID ReadData(REL::RelocationID(13904, 13991));
			inline REL::ID Seek(REL::RelocationID(13898, 13984));
			inline REL::ID SeekNextSubrecord(REL::RelocationID(13903, 13990));
		}

		namespace TESHavokUtilities
		{
			inline REL::ID FindCollidableRef(REL::RelocationID(25466, 26003));
		}

		namespace TESNPC
		{
			inline REL::ID ChangeHeadPart(REL::RelocationID(24246, 24750));
			inline REL::ID GetBaseOverlays(REL::RelocationID(24275, 24791));
			inline REL::ID GetNumBaseOverlays(REL::RelocationID(24276, 24792));
			inline REL::ID HasOverlays(REL::RelocationID(24274, 24790));
			inline REL::ID SetSkinFromTint(REL::RelocationID(24206, 24710));
			inline REL::ID UpdateNeck(REL::RelocationID(24207, 24711));
		}

		namespace TESObjectREFR
		{
			inline REL::ID GetDisplayFullName(REL::RelocationID(19354, 19781));
			inline REL::ID GetLock(REL::RelocationID(19818, 20223));
			inline REL::ID GetOwner(REL::RelocationID(19789, 20194));
			inline REL::ID GetStealValue(REL::RelocationID(15807, 16045));
			inline REL::ID FindReferenceFor3D(REL::RelocationID(19323, 19750));
			inline REL::ID InitInventoryIfRequired(REL::RelocationID(15800, 16038));
			inline REL::ID MoveTo(REL::RelocationID(56227, 56626));
			inline REL::ID PlayAnimation(REL::RelocationID(14189, 14297));
		}

		namespace TESQuest
		{
			inline REL::ID EnsureQuestStarted(REL::RelocationID(24481, 25003));
			inline REL::ID ResetQuest(REL::RelocationID(24486, 25014));
		}

		namespace UI
		{
			inline REL::ID Singleton(REL::RelocationID(514178, 400327));
		}

		namespace UIBlurManager
		{
			inline REL::ID DecrementBlurCount(REL::RelocationID(51900, 52777));
			inline REL::ID IncrementBlurCount(REL::RelocationID(51899, 52776));
			inline REL::ID Singleton(REL::RelocationID(516871, 403350));
		}

		namespace UIMessageQueue
		{
			inline REL::ID AddMessage(REL::RelocationID(13530, 13631));
			inline REL::ID CreateUIMessageData(REL::RelocationID(80061, 82169));
			inline REL::ID ProcessCommands(REL::RelocationID(80059, 82167));
			inline REL::ID Singleton(REL::RelocationID(514285, 400445));
		}

		namespace UserEvents
		{
			inline REL::ID Singleton(REL::RelocationID(516458, 402638));
		}

		inline REL::ID CreateRefHandle(REL::RelocationID(12193, 12326));
		inline REL::ID DebugNotification(REL::RelocationID(52050, 52933));
		inline REL::ID LookupReferenceByHandle(REL::RelocationID(12204, 12332));
		inline REL::ID PlaySound(REL::RelocationID(52054, 52939));
		inline REL::ID TlsIndex(REL::RelocationID(528600, 415542));
	}
}

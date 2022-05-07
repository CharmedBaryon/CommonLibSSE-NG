#pragma once

#include "REL/Relocation.h"

namespace RE
{
	namespace Offset
	{
		namespace Actor
		{
			inline REL::ID AddSpell(RELOCATION_ID(37771, 38716));
			inline REL::ID DispelWornItemEnchantments(RELOCATION_ID(33828, 34620));
			inline REL::ID DoReset3D(RELOCATION_ID(39181, 40255));
			inline REL::ID GetGhost(RELOCATION_ID(36286, 37275));
			inline REL::ID GetHostileToActor(RELOCATION_ID(36537, 37537));
			inline REL::ID GetLevel(RELOCATION_ID(36344, 37334));
			inline REL::ID HasPerk(RELOCATION_ID(36690, 37698));
			inline REL::ID IsRunning(RELOCATION_ID(36252, 37234));
			inline REL::ID RequestDetectionLevel(RELOCATION_ID(36748, 37764));
			inline REL::ID SwitchRace(RELOCATION_ID(36901, 37925));
			inline REL::ID UpdateArmorAbility(RELOCATION_ID(37802, 38751));
			inline REL::ID UpdateWeaponAbility(RELOCATION_ID(37803, 38752));
		}

		namespace ActorEquipManager
		{
			inline REL::ID EquipObject(RELOCATION_ID(37938, 38894));
			inline REL::ID Singleton(RELOCATION_ID(514494, 400636));
			inline REL::ID UnequipObject(RELOCATION_ID(37945, 38901));
		}

		namespace ActorValueOwner
		{
			inline REL::ID GetClampedActorValue(RELOCATION_ID(26616, 27284));
		}

		namespace AIProcess
		{
			inline REL::ID SetBaseScale(RELOCATION_ID(38568, 39588));
			inline REL::ID Update3DModel(RELOCATION_ID(38404, 39395));
		}

		namespace BGSFootstepManager
		{
			inline REL::ID Singleton(RELOCATION_ID(517045, 401262));
		}

		namespace BGSListForm
		{
			inline REL::ID AddForm(RELOCATION_ID(20470, 20913));
		}

		namespace BGSSaveLoadManager
		{
			inline REL::ID Save(RELOCATION_ID(34818, 35727));
			inline REL::ID Singleton(RELOCATION_ID(516860, 403340));
			inline REL::ID Load(RELOCATION_ID(34819, 35728));
		}

		namespace BGSStoryTeller
		{
			inline REL::ID BeginShutDownQuest(RELOCATION_ID(31718, 32486));
			inline REL::ID BeginStartUpQuest(RELOCATION_ID(31717, 32485));
			inline REL::ID Singleton(RELOCATION_ID(514316, 400476));
		}

		namespace BipedAnim
		{
			inline REL::ID Dtor(RELOCATION_ID(15491, 15656));
			inline REL::ID RemoveAllParts(RELOCATION_ID(15494, 15659));
		}

		namespace BSAudioManager
		{
			inline REL::ID GetSingleton(RELOCATION_ID(66391, 67652));
			inline REL::ID BuildSoundDataFromDescriptor(RELOCATION_ID(66404, 67666));
		}

		namespace BSInputDeviceManager
		{
			inline REL::ID Singleton(RELOCATION_ID(516574, 402776));
		}

		namespace BSLightingShaderMaterialBase
		{
			inline REL::ID CreateMaterial(RELOCATION_ID(100016, 106723));
		}

		namespace BSReadWriteLock
		{
			inline REL::ID LockForRead(RELOCATION_ID(66976, 68233));
			inline REL::ID LockForWrite(RELOCATION_ID(66977, 68234));
			inline REL::ID UnlockForRead(RELOCATION_ID(66982, 68239));
			inline REL::ID UnlockForWrite(RELOCATION_ID(66983, 68240));
		}

		namespace BSResourceNiBinaryStream
		{
			inline REL::ID Ctor(RELOCATION_ID(69636, 71014));
			inline REL::ID Dtor(RELOCATION_ID(69638, 71016));
			inline REL::ID Seek(RELOCATION_ID(69640, 71018));
			inline REL::ID SetEndianSwap(RELOCATION_ID(69643, 71021));
		}

		namespace BSScript
		{
			namespace ObjectBindPolicy
			{
				inline REL::ID BindObject(RELOCATION_ID(97379, 104184));
			}

			namespace NF_util
			{
				namespace NativeFunctionBase
				{
					inline REL::ID Call(RELOCATION_ID(97923, 104651));
				}
			}

			namespace Stack
			{
				inline REL::ID Dtor(RELOCATION_ID(97742, 104480));
			}
		}

		namespace BSSoundHandle
		{
			inline REL::ID IsValid(RELOCATION_ID(66360, 67621));
			inline REL::ID Play(RELOCATION_ID(66355, 67616));
			inline REL::ID SetObjectToFollow(RELOCATION_ID(66375, 67636));
			inline REL::ID SetPosition(RELOCATION_ID(66370, 67631));
			inline REL::ID Stop(RELOCATION_ID(66358, 67619));
		}

		namespace BSString
		{
			inline REL::ID Set_CStr(RELOCATION_ID(10979, 11044));
		}

		namespace BucketTable
		{
			inline REL::ID GetSingleton(RELOCATION_ID(67855, 69200));
		}

		namespace BSWin32SaveDataSystemUtility
		{
			inline REL::ID GetSingleton(RELOCATION_ID(101884, 109278));
		}

		namespace Calendar
		{
			inline REL::ID Singleton(RELOCATION_ID(514287, 400447));
		}

		namespace Console
		{
			inline REL::ID SelectedRef(RELOCATION_ID(519394, 405935));
			inline REL::ID SetSelectedRef(RELOCATION_ID(50164, 51093));
		}

		namespace ConsoleLog
		{
			inline REL::ID Singleton(RELOCATION_ID(515064, 401203));
			inline REL::ID VPrint(RELOCATION_ID(50180, 51110));
		}

		namespace ControlMap
		{
			inline REL::ID Singleton(RELOCATION_ID(514705, 400863));
		}

		namespace CRC32Calculator
		{
			inline REL::ID SizeOf32(RELOCATION_ID(66963, 12141));
			inline REL::ID SizeOf64(RELOCATION_ID(66964, 68221));
			inline REL::ID SizeOfSize(RELOCATION_ID(66962, 68219));
		}

		namespace ExtraDataList
		{
			inline REL::ID Add(RELOCATION_ID(12176, 12315));
			inline REL::ID SetExtraFlags(RELOCATION_ID(11903, 12042));
			inline REL::ID SetInventoryChanges(RELOCATION_ID(11483, 11600));
		}

		namespace GameSettingCollection
		{
			inline REL::ID Singleton(RELOCATION_ID(514622, 400782));
		}

		namespace GFxLoader
		{
			inline REL::ID CreateMovie(RELOCATION_ID(80620, 84640));
		}

		namespace GFxMovieView
		{
			inline REL::ID InvokeNoReturn(RELOCATION_ID(80547, 82665));
		}

		namespace GFxValue
		{
			namespace ObjectInterface
			{
				inline REL::ID AttachMovie(RELOCATION_ID(80197, 82219));
				inline REL::ID DeleteMember(RELOCATION_ID(80207, 82230));
				inline REL::ID GetArraySize(RELOCATION_ID(80214, 82237));
				inline REL::ID GetDisplayInfo(RELOCATION_ID(80216, 82239));
				inline REL::ID GetElement(RELOCATION_ID(80218, 82241));
				inline REL::ID GetMember(RELOCATION_ID(80222, 82245));
				inline REL::ID GotoAndPlay(RELOCATION_ID(80230, 82253));
				inline REL::ID HasMember(RELOCATION_ID(80231, 82254));
				inline REL::ID Invoke(RELOCATION_ID(80233, 82256));
				inline REL::ID ObjectAddRef(RELOCATION_ID(80244, 82269));
				inline REL::ID ObjectRelease(RELOCATION_ID(80245, 82270));
				inline REL::ID PushBack(RELOCATION_ID(80248, 82273));
				inline REL::ID RemoveElements(RELOCATION_ID(80252, 82280));
				inline REL::ID SetArraySize(RELOCATION_ID(80261, 82285));
				inline REL::ID SetDisplayInfo(RELOCATION_ID(80263, 82287));
				inline REL::ID SetElement(RELOCATION_ID(80265, 82289));
				inline REL::ID SetMember(RELOCATION_ID(80268, 82292));
				inline REL::ID SetText(RELOCATION_ID(80270, 82293));
			}
		}

		namespace GMemory
		{
			inline REL::ID GlobalHeap(RELOCATION_ID(525584, 412058));
		}

		namespace hkReferencedObject
		{
			inline REL::ID AddReference(RELOCATION_ID(56606, 57010));
			inline REL::ID RemoveReference(RELOCATION_ID(56607, 57011));
		}

		namespace INIPrefSettingCollection
		{
			inline REL::ID Singleton(RELOCATION_ID(523673, 410219));
		}

		namespace INISettingCollection
		{
			inline REL::ID Singleton(RELOCATION_ID(524557, 411155));
		}

		namespace InterfaceStrings
		{
			inline REL::ID Singleton(RELOCATION_ID(514286, 400446));
		}

		namespace Inventory
		{
			inline REL::ID GetEventSource(RELOCATION_ID(15980, 16225));
		}

		namespace InventoryChanges
		{
			inline REL::ID GetNextUniqueID(RELOCATION_ID(15908, 16148));
			inline REL::ID SendContainerChangedEvent(RELOCATION_ID(15909, 16149));
			inline REL::ID SetUniqueID(RELOCATION_ID(15907, 16149));
			inline REL::ID TransferItemUID(RELOCATION_ID(15909, 16149));
		}

		namespace ItemCrafted
		{
			inline REL::ID GetEventSource(RELOCATION_ID(50515, 51403));
		}

		namespace ItemList
		{
			inline REL::ID Update(RELOCATION_ID(50099, 51031));
		}

		namespace ItemsPickpocketed
		{
			inline REL::ID GetEventSource(RELOCATION_ID(50258, 51183));
		}

		namespace LocalMapCamera
		{
			inline REL::ID Ctor(RELOCATION_ID(16084, 16325));
			inline REL::ID SetNorthRotation(RELOCATION_ID(16089, 16330));
		}

		namespace MagicFavorites
		{
			inline REL::ID Singleton(RELOCATION_ID(516858, 403337));
		}

		namespace MagicItem
		{
			inline REL::ID CalculateCost(RELOCATION_ID(11213, 11321));
			inline REL::ID GetCostliestEffectItem(RELOCATION_ID(11216, 11335));
		}

		namespace MagicTarget
		{
			inline REL::ID HasMagicEffect(RELOCATION_ID(33733, 34517));
		}

		namespace Main
		{
			inline REL::ID Singleton(RELOCATION_ID(516943, 403449));
		}

		namespace MenuControls
		{
			inline REL::ID Singleton(RELOCATION_ID(515124, 401263));
		}

		namespace MessageDataFactoryManager
		{
			inline REL::ID GetSingleton(RELOCATION_ID(22843, 52875));
		}

		namespace NiAVObject
		{
			inline REL::ID SetMotionType(RELOCATION_ID(76033, 77866));
			inline REL::ID Update(RELOCATION_ID(68900, 70251));
		}

		namespace NiCamera
		{
			inline REL::ID WorldPtToScreenPt3(RELOCATION_ID(69270, 70640));
		}

		namespace NiMemManager
		{
			inline REL::ID Singleton(RELOCATION_ID(523759, 410319));
		}

		namespace NiNode
		{
			inline REL::ID Ctor(RELOCATION_ID(68936, 70287));
		}

		namespace NiRefObject
		{
			inline REL::ID TotalObjectCount(RELOCATION_ID(523912, 410493));
		}

		namespace NiSkinInstance
		{
			inline REL::ID Ctor(RELOCATION_ID(69804, 71227));
		}

		namespace PlayerCamera
		{
			inline REL::ID Singleton(RELOCATION_ID(514642, 400802));
			inline REL::ID UpdateThirdPerson(RELOCATION_ID(49908, 50841));
		}

		namespace PlayerCharacter
		{
			namespace PlayerSkills
			{
				inline REL::ID AdvanceLevel(RELOCATION_ID(40560, 41567));
			}

			inline REL::ID ActivatePickRef(RELOCATION_ID(39471, 40548));
			inline REL::ID GetArmorValue(RELOCATION_ID(39175, 40249));
			inline REL::ID GetDamage(RELOCATION_ID(39179, 40253));
			inline REL::ID GetNumTints(RELOCATION_ID(39614, 40700));
			inline REL::ID GetTintMask(RELOCATION_ID(39612, 40698));
			inline REL::ID PlayPickupEvent(RELOCATION_ID(39384, 40456));
			inline REL::ID Singleton(RELOCATION_ID(517014, 403521));
			inline REL::ID StartGrabObject(RELOCATION_ID(39475, 40552));
		}

		namespace PlayerControls
		{
			inline REL::ID Ctor(RELOCATION_ID(41257, 42336));
			inline REL::ID Singleton(RELOCATION_ID(514706, 400864));
		}

		namespace Script
		{
			inline REL::ID CompileAndRun(RELOCATION_ID(21416, 21890));
		}

		namespace SCRIPT_FUNCTION
		{
			inline REL::ID FirstConsoleCommand(RELOCATION_ID(501797, 365650));
			inline REL::ID FirstScriptCommand(RELOCATION_ID(501789, 361120));
		}

		namespace Sky
		{
			inline REL::ID GetSingleton(RELOCATION_ID(13789, 13878));
		}

		namespace SkyrimVM
		{
			inline REL::ID QueuePostRenderCall(RELOCATION_ID(53144, 53955));
			inline REL::ID Singleton(RELOCATION_ID(514315, 400475));
		}

		namespace TES
		{
			inline REL::ID Singleton(RELOCATION_ID(516923, 403450));
		}

		namespace TESCamera
		{
			inline REL::ID SetState(RELOCATION_ID(32290, 33026));
		}

		namespace TESDataHandler
		{
			inline REL::ID LoadScripts(RELOCATION_ID(13657, 13766));
			inline REL::ID Singleton(RELOCATION_ID(514141, 400269));
		}

		namespace TESDescription
		{
			inline REL::ID GetDescription(RELOCATION_ID(14399, 14552));
		}

		namespace TESFile
		{
			inline REL::ID Duplicate(RELOCATION_ID(13923, 14018));
			inline REL::ID GetCurrentSubRecordType(RELOCATION_ID(13902, 13988));
			inline REL::ID GetFormType(RELOCATION_ID(13897, 13982));
			inline REL::ID ReadData(RELOCATION_ID(13904, 13991));
			inline REL::ID Seek(RELOCATION_ID(13898, 13984));
			inline REL::ID SeekNextSubrecord(RELOCATION_ID(13903, 13990));
		}

		namespace TESHavokUtilities
		{
			inline REL::ID FindCollidableRef(RELOCATION_ID(25466, 26003));
		}

		namespace TESNPC
		{
			inline REL::ID ChangeHeadPart(RELOCATION_ID(24246, 24750));
			inline REL::ID GetBaseOverlays(RELOCATION_ID(24275, 24791));
			inline REL::ID GetNumBaseOverlays(RELOCATION_ID(24276, 24792));
			inline REL::ID HasOverlays(RELOCATION_ID(24274, 24790));
			inline REL::ID SetSkinFromTint(RELOCATION_ID(24206, 24710));
			inline REL::ID UpdateNeck(RELOCATION_ID(24207, 24711));
		}

		namespace TESObjectREFR
		{
			inline REL::ID GetDisplayFullName(RELOCATION_ID(19354, 19781));
			inline REL::ID GetLock(RELOCATION_ID(19818, 20223));
			inline REL::ID GetOwner(RELOCATION_ID(19789, 20194));
			inline REL::ID GetStealValue(RELOCATION_ID(15807, 16045));
			inline REL::ID FindReferenceFor3D(RELOCATION_ID(19323, 19750));
			inline REL::ID InitInventoryIfRequired(RELOCATION_ID(15800, 16038));
			inline REL::ID MoveTo(RELOCATION_ID(56227, 56626));
			inline REL::ID PlayAnimation(RELOCATION_ID(14189, 14297));
		}

		namespace TESQuest
		{
			inline REL::ID EnsureQuestStarted(RELOCATION_ID(24481, 25003));
			inline REL::ID ResetQuest(RELOCATION_ID(24486, 25014));
		}

		namespace UI
		{
			inline REL::ID Singleton(RELOCATION_ID(514178, 400327));
		}

		namespace UIBlurManager
		{
			inline REL::ID DecrementBlurCount(RELOCATION_ID(51900, 52777));
			inline REL::ID IncrementBlurCount(RELOCATION_ID(51899, 52776));
			inline REL::ID Singleton(RELOCATION_ID(516871, 403350));
		}

		namespace UIMessageQueue
		{
			inline REL::ID AddMessage(RELOCATION_ID(13530, 13631));
			inline REL::ID CreateUIMessageData(RELOCATION_ID(80061, 82169));
			inline REL::ID ProcessCommands(RELOCATION_ID(80059, 82167));
			inline REL::ID Singleton(RELOCATION_ID(514285, 400445));
		}

		namespace UserEvents
		{
			inline REL::ID Singleton(RELOCATION_ID(516458, 402638));
		}

		inline REL::ID CreateRefHandle(RELOCATION_ID(12193, 12326));
		inline REL::ID DebugNotification(RELOCATION_ID(52050, 52933));
		inline REL::ID GetActorValueIdFromName(RELOCATION_ID(26570, 27203));
		inline REL::ID LookupReferenceByHandle(RELOCATION_ID(12204, 12332));
		inline REL::ID PlaySound(RELOCATION_ID(52054, 52939));
		inline REL::ID TlsIndex(RELOCATION_ID(528600, 415542));
	}
}

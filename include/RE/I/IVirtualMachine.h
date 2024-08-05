#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSIntrusiveRefCounted.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/E/ErrorLogger.h"
#include "RE/I/IStackCallbackFunctor.h"
#include "RE/T/TypeInfo.h"
#include "RE/T/TypeTraits.h"
#include "RE/V/Variable.h"

namespace RE
{
	namespace BSJobs
	{
		class JobList;
	}

	class TESForm;

	namespace BSScript
	{
		class Array;
		class ErrorLogger;
		class IForEachScriptObjectFunctor;
		class IFunction;
		class IFunctionArguments;
		class ISavePatcherInterface;
		class ITypeLinkedCallback;
		class Object;
		class ObjectBindPolicy;
		class ObjectTypeInfo;
		class Variable;
		struct IObjectHandlePolicy;
		struct LogEvent;
		struct StatsEvent;

		class IVirtualMachine : public BSIntrusiveRefCounted
		{
		public:
			inline static constexpr auto RTTI = RTTI_BSScript__IVirtualMachine;
			inline static constexpr auto VTABLE = VTABLE_BSScript__IVirtualMachine;

			using Severity = BSScript::ErrorLogger::Severity;
			struct Awaitable
			{
				struct CallbackFunctor : public IStackCallbackFunctor
				{
					void operator()(Variable a_result) override;
					void SetObject(const BSTSmartPointer<Object>&) override {}

					bool                    pending{ false };
					Variable                result;
					std::coroutine_handle<> continuation;
				};

				Awaitable();
				void     SetPending(bool a_pending = true);
				bool     await_ready() const;
				void     await_suspend(std::coroutine_handle<> a_handle);
				Variable await_resume() const;

				BSTSmartPointer<IStackCallbackFunctor> callback;
			};

			virtual ~IVirtualMachine();  // 00

			// add
			virtual void SetLinkedCallback(ITypeLinkedCallback* a_callback) = 0;                                                                                    // 01
			virtual void TraceStack(const char* a_str, VMStackID a_stackID, Severity a_severity = Severity::kError) = 0;                                            // 02
			virtual void FormatAndPostMessage(const char* a_message, Severity a_severity) = 0;                                                                      // 03
			virtual void Update(float a_budget) = 0;                                                                                                                // 04
			virtual void UpdateTasklets(float a_budget) = 0;                                                                                                        // 05
			virtual void SetOverstressed(bool a_set) = 0;                                                                                                           // 06
			virtual bool IsCompletelyFrozen() const = 0;                                                                                                            // 07
			virtual bool RegisterObjectType(VMTypeID a_typeID, const char* a_className) = 0;                                                                        // 08
			virtual bool GetScriptObjectType1(const BSFixedString& a_className, BSTSmartPointer<ObjectTypeInfo>& a_outTypeInfoPtr) = 0;                             // 09
			virtual bool GetScriptObjectType2(VMTypeID a_typeID, BSTSmartPointer<ObjectTypeInfo>& a_outTypeInfoPtr) = 0;                                            // 0A
			virtual bool GetScriptObjectTypeNoLoad1(const BSFixedString& a_className, BSTSmartPointer<ObjectTypeInfo>& a_typeInfoPtr) const = 0;                    // 0B
			virtual bool GetScriptObjectTypeNoLoad2(VMTypeID a_typeID, BSTSmartPointer<ObjectTypeInfo>& a_outTypeInfoPtr) const = 0;                                // 0C
			virtual bool GetTypeIDForScriptObject(const BSFixedString& a_className, VMTypeID& a_typeID) const = 0;                                                  // 0D
			virtual void GetScriptObjectsWithATypeID(BSScrapArray<BSFixedString>& a_classes) const = 0;                                                             // 0E
			virtual bool GetParentNativeType(const BSFixedString& a_className, BSTSmartPointer<ObjectTypeInfo>& a_typeInfoPtr) = 0;                                 // 0F
			virtual bool TypeIsValid(const BSFixedString& a_className) = 0;                                                                                         // 10
			virtual bool ReloadType(const char* a_className) = 0;                                                                                                   // 11
			virtual void TasksToJobs(BSJobs::JobList& a_jobList) = 0;                                                                                               // 12
			virtual void CalculateFullReloadList(void) const = 0;                                                                                                   // 13
			virtual bool CreateObject1(const BSFixedString& a_className, void* a_property, BSTSmartPointer<Object>& a_objPtr) = 0;                                  // 14
			virtual bool CreateObject2(const BSFixedString& a_className, BSTSmartPointer<Object>& a_result) = 0;                                                    // 15
			virtual bool CreateArray1(const TypeInfo& a_typeInfo, std::uint32_t a_size, BSTSmartPointer<Array>& a_arrayPtr) = 0;                                    // 16
			virtual bool CreateArray2(TypeInfo::RawType a_typeID, const BSFixedString& a_className, std::uint32_t a_size, BSTSmartPointer<Array>& a_arrayPtr) = 0;  // 17
			virtual bool BindNativeMethod(IFunction* a_fn) = 0;                                                                                                     // 18
			virtual void SetCallableFromTasklets1(const char* a_className, const char* a_stateName, const char* a_fnName, bool a_callable) = 0;                     // 19
			virtual void SetCallableFromTasklets2(const char* a_className, const char* a_fnName, bool a_callable) = 0;                                              // 1A
#if defined(EXCLUSIVE_SKYRIM_VR)
			virtual void New_1B(void) = 0;
#endif
			SKYRIM_REL_VR_VIRTUAL void ForEachBoundObject(VMHandle a_handle, IForEachScriptObjectFunctor* a_functor);  // 1B, 1C
#if defined(EXCLUSIVE_SKYRIM_VR)
			virtual void New_1D(void) = 0;
#endif
			SKYRIM_REL_VR_VIRTUAL bool                       FindBoundObject(VMHandle a_handle, const char* a_className, BSTSmartPointer<Object>& a_result) const;                                                                                   // 1C
			SKYRIM_REL_VR_VIRTUAL void                       MoveBoundObjects(VMHandle a_from, VMHandle a_to);                                                                                                                                       // 1D
			SKYRIM_REL_VR_VIRTUAL void                       ResetAllBoundObjects(VMHandle a_handle);                                                                                                                                                // 1E
			SKYRIM_REL_VR_VIRTUAL bool                       CastObject(const BSTSmartPointer<Object>& a_fromObjPtr, const BSTSmartPointer<ObjectTypeInfo>& a_toTypeInfoPtr, BSTSmartPointer<Object>& a_toObjPtr);                                   // 1F
			SKYRIM_REL_VR_VIRTUAL bool                       SetPropertyValue(BSTSmartPointer<Object>& a_obj, const char* a_propertyName, Variable& a_setVal);                                                                                       // 20
			SKYRIM_REL_VR_VIRTUAL bool                       GetPropertyValue(BSTSmartPointer<Object>& a_obj, const char* a_propertyName, Variable& a_getVal);                                                                                       // 21
			SKYRIM_REL_VR_VIRTUAL bool                       GetVariableValue1(const BSTSmartPointer<Object>& a_objPtr, std::uint32_t a_index, Variable& a_out) const;                                                                               // 22
			SKYRIM_REL_VR_VIRTUAL bool                       GetVariableValue2(VMHandle a_handle, const BSFixedString& a_className, std::int32_t a_variableIndex, Variable& a_out) const;                                                            // 23
			SKYRIM_REL_VR_VIRTUAL void                       SendEvent(VMHandle a_handle, const BSFixedString& a_eventName, IFunctionArguments* a_args);                                                                                             // 24
			SKYRIM_REL_VR_VIRTUAL void                       SendEventAll(const BSFixedString& a_eventName, IFunctionArguments* a_args);                                                                                                             // 25
			SKYRIM_REL_VR_VIRTUAL bool                       DispatchStaticCall(const BSFixedString& a_className, const BSFixedString& a_fnName, IFunctionArguments* a_args, BSTSmartPointer<IStackCallbackFunctor>& a_result);                      // 26
			SKYRIM_REL_VR_VIRTUAL bool                       DispatchMethodCall1(BSTSmartPointer<Object>& a_obj, const BSFixedString& a_fnName, IFunctionArguments* a_args, BSTSmartPointer<IStackCallbackFunctor>& a_result);                       // 27
			SKYRIM_REL_VR_VIRTUAL bool                       DispatchMethodCall2(VMHandle a_handle, const BSFixedString& a_className, const BSFixedString& a_fnName, IFunctionArguments* a_args, BSTSmartPointer<IStackCallbackFunctor>& a_result);  // 28
			SKYRIM_REL_VR_VIRTUAL bool                       DispatchUnboundMethodCall(void);                                                                                                                                                        // 29
			SKYRIM_REL_VR_VIRTUAL bool                       IsWaitingOnLatent(VMStackID a_stackID) const;                                                                                                                                           // 2A
			SKYRIM_REL_VR_VIRTUAL void                       ReturnFromLatent(VMStackID a_stackID, const Variable& a_val);                                                                                                                           // 2B
			SKYRIM_REL_VR_VIRTUAL ErrorLogger*               GetErrorLogger();                                                                                                                                                                       // 2C
			SKYRIM_REL_VR_VIRTUAL IObjectHandlePolicy*       GetObjectHandlePolicy1();                                                                                                                                                               // 2D
			SKYRIM_REL_VR_VIRTUAL const IObjectHandlePolicy* GetObjectHandlePolicy2() const;                                                                                                                                                         // 2E
			SKYRIM_REL_VR_VIRTUAL ObjectBindPolicy*          GetObjectBindPolicy1();                                                                                                                                                                 // 2F
			SKYRIM_REL_VR_VIRTUAL const ObjectBindPolicy*    GetObjectBindPolicy2() const;                                                                                                                                                           // 30
			SKYRIM_REL_VR_VIRTUAL ISavePatcherInterface*     GetSavePatcherInterface();                                                                                                                                                              // 31
			SKYRIM_REL_VR_VIRTUAL void                       RegisterForLogEvent(BSTEventSink<LogEvent>* a_sink);                                                                                                                                    // 32
			SKYRIM_REL_VR_VIRTUAL void                       UnregisterForLogEvent(BSTEventSink<LogEvent>* a_sink);                                                                                                                                  // 33
			SKYRIM_REL_VR_VIRTUAL void                       RegisterForStatsEvent(BSTEventSink<StatsEvent>* a_sink);                                                                                                                                // 34
			SKYRIM_REL_VR_VIRTUAL void                       UnregisterForStatsEvent(BSTEventSink<StatsEvent>* a_sink);                                                                                                                              // 35

			bool                       CreateArray(const TypeInfo& a_typeInfo, std::uint32_t a_size, BSTSmartPointer<Array>& a_arrayPtr);
			bool                       CreateArray(TypeInfo::RawType a_typeID, const BSFixedString& a_className, std::uint32_t a_size, BSTSmartPointer<Array>& a_arrayPtr);
			bool                       CreateObject(const BSFixedString& a_className, void* a_property, BSTSmartPointer<Object>& a_objPtr);
			bool                       CreateObject(const BSFixedString& a_className, BSTSmartPointer<Object>& a_result);
			bool                       DispatchMethodCall(BSTSmartPointer<Object>& a_obj, const BSFixedString& a_fnName, IFunctionArguments* a_args, BSTSmartPointer<IStackCallbackFunctor>& a_result);
			Awaitable                  ADispatchMethodCall(BSTSmartPointer<Object>& a_obj, const BSFixedString& a_fnName, IFunctionArguments* a_args);
			bool                       DispatchMethodCall(VMHandle a_handle, const BSFixedString& a_className, const BSFixedString& a_fnName, IFunctionArguments* a_args, BSTSmartPointer<IStackCallbackFunctor>& a_result);
			Awaitable                  ADispatchMethodCall(VMHandle a_handle, const BSFixedString& a_className, const BSFixedString& a_fnName, IFunctionArguments* a_args);
			Awaitable                  ADispatchStaticCall(const BSFixedString& a_className, const BSFixedString& a_fnName, IFunctionArguments* a_args);
			ObjectBindPolicy*          GetObjectBindPolicy();
			const ObjectBindPolicy*    GetObjectBindPolicy() const;
			IObjectHandlePolicy*       GetObjectHandlePolicy();
			const IObjectHandlePolicy* GetObjectHandlePolicy() const;
			bool                       GetScriptObjectType(const BSFixedString& a_className, BSTSmartPointer<ObjectTypeInfo>& a_outTypeInfoPtr);
			bool                       GetScriptObjectType(VMTypeID a_typeID, BSTSmartPointer<ObjectTypeInfo>& a_outTypeInfoPtr);
			bool                       GetScriptObjectTypeNoLoad(const BSFixedString& a_className, BSTSmartPointer<ObjectTypeInfo>& a_typeInfoPtr) const;
			bool                       GetScriptObjectTypeNoLoad(VMTypeID a_typeID, BSTSmartPointer<ObjectTypeInfo>& a_outTypeInfoPtr) const;
			bool                       GetVariableValue(const BSTSmartPointer<Object>& a_objPtr, std::uint32_t a_index, Variable& a_out) const;
			bool                       GetVariableValue(VMHandle a_handle, const BSFixedString& a_className, std::int32_t a_variableIndex, Variable& a_out) const;

			template <class F>
			void RegisterFunction(std::string_view a_fnName, std::string_view a_className, F a_callback, bool a_callableFromTasklets = false);

			template <class R, class F>
			void RegisterLatentFunction(std::string_view a_fnName, std::string_view a_className, F a_callback, bool a_callableFromTasklets = false);

			template <class V>
				requires is_return_convertible_v<V>
			void ReturnLatentResult(VMStackID a_stackID, V result);

			void SetCallableFromTasklets(const char* a_className, const char* a_stateName, const char* a_fnName, bool a_callable);
			void SetCallableFromTasklets(const char* a_className, const char* a_fnName, bool a_callable);
			void TraceForm(TESForm* a_form, const char* a_str, VMStackID a_stackID, Severity a_severity = Severity::kError);
			void VTraceStack(VMStackID a_stackID, Severity a_severity, const char* a_fmt, ...);

			// members
			std::uint32_t pad0C;  // 0C
		};
		static_assert(sizeof(IVirtualMachine) == 0x10);
	}
}

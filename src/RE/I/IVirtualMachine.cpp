#include "RE/I/IVirtualMachine.h"

#include "RE/B/BSFixedString.h"
#include "RE/I/IObjectHandlePolicy.h"
#include "RE/T/TESForm.h"

namespace RE
{
	namespace BSScript
	{

		void IVirtualMachine::Awaitable::CallbackFunctor::operator()(Variable a_result)
		{
			pending = false;
			result = a_result;

			if (continuation) {
				continuation.resume();
			}
		}

		IVirtualMachine::Awaitable::Awaitable() :
			callback(new CallbackFunctor())
		{
		}

		void IVirtualMachine::Awaitable::SetPending(bool a_pending)
		{
			if (callback) {
				static_cast<CallbackFunctor*>(callback.get())->pending = a_pending;
			}
		}

		bool IVirtualMachine::Awaitable::await_ready() const
		{
			if (!callback)
				return true;

			return static_cast<CallbackFunctor*>(callback.get())->pending == false;
		}

		void IVirtualMachine::Awaitable::await_suspend(std::coroutine_handle<> a_handle)
		{
			if (!callback) {
				a_handle.resume();
				return;
			}

			auto& continuation = static_cast<CallbackFunctor*>(callback.get())->continuation;

			if (continuation) {
				continuation.destroy();
			}

			continuation = a_handle;
		}

		Variable IVirtualMachine::Awaitable::await_resume() const
		{
			return static_cast<CallbackFunctor*>(callback.get())->result;
		}

		bool IVirtualMachine::CreateArray(const TypeInfo& a_typeInfo, std::uint32_t a_size, BSTSmartPointer<Array>& a_arrayPtr)
		{
			return CreateArray1(a_typeInfo, a_size, a_arrayPtr);
		}

		bool IVirtualMachine::CreateArray(TypeInfo::RawType a_typeID, const BSFixedString& a_className, std::uint32_t a_size, BSTSmartPointer<Array>& a_arrayPtr)
		{
			return CreateArray2(a_typeID, a_className, a_size, a_arrayPtr);
		}

		bool IVirtualMachine::CreateObject(const BSFixedString& a_className, void* a_property, BSTSmartPointer<Object>& a_objPtr)
		{
			return CreateObject1(a_className, a_property, a_objPtr);
		}

		bool IVirtualMachine::CreateObject(const BSFixedString& a_className, BSTSmartPointer<Object>& a_result)
		{
			return CreateObject2(a_className, a_result);
		}

		bool IVirtualMachine::DispatchMethodCall(BSTSmartPointer<Object>& a_obj, const BSFixedString& a_fnName, IFunctionArguments* a_args, BSTSmartPointer<IStackCallbackFunctor>& a_result)
		{
			return DispatchMethodCall1(a_obj, a_fnName, a_args, a_result);
		}

		IVirtualMachine::Awaitable IVirtualMachine::ADispatchMethodCall(BSTSmartPointer<Object>& a_obj, const BSFixedString& a_fnName, IFunctionArguments* a_args)
		{
			Awaitable awaitable;
			awaitable.SetPending(true);

			if (!DispatchMethodCall1(a_obj, a_fnName, a_args, awaitable.callback)) {
				awaitable.SetPending(false);
			}

			return awaitable;
		}

		bool IVirtualMachine::DispatchMethodCall(VMHandle a_handle, const BSFixedString& a_className, const BSFixedString& a_fnName, IFunctionArguments* a_args, BSTSmartPointer<IStackCallbackFunctor>& a_result)
		{
			return DispatchMethodCall2(a_handle, a_className, a_fnName, a_args, a_result);
		}

		IVirtualMachine::Awaitable IVirtualMachine::ADispatchMethodCall(VMHandle a_handle, const BSFixedString& a_className, const BSFixedString& a_fnName, IFunctionArguments* a_args)
		{
			Awaitable awaitable;
			awaitable.SetPending(true);

			if (!DispatchMethodCall2(a_handle, a_className, a_fnName, a_args, awaitable.callback)) {
				awaitable.SetPending(false);
			}

			return awaitable;
		}

		IVirtualMachine::Awaitable IVirtualMachine::ADispatchStaticCall(const BSFixedString& a_className, const BSFixedString& a_fnName, IFunctionArguments* a_args)
		{
			Awaitable awaitable;
			awaitable.SetPending(true);

			if (!DispatchStaticCall(a_className, a_fnName, a_args, awaitable.callback)) {
				awaitable.SetPending(false);
			}

			return awaitable;
		}

		ObjectBindPolicy* IVirtualMachine::GetObjectBindPolicy()
		{
			return GetObjectBindPolicy1();
		}

		const ObjectBindPolicy* IVirtualMachine::GetObjectBindPolicy() const
		{
			return GetObjectBindPolicy2();
		}

		IObjectHandlePolicy* IVirtualMachine::GetObjectHandlePolicy()
		{
			return GetObjectHandlePolicy1();
		}

		const IObjectHandlePolicy* IVirtualMachine::GetObjectHandlePolicy() const
		{
			return GetObjectHandlePolicy2();
		}

		bool IVirtualMachine::GetScriptObjectType(const BSFixedString& a_className, BSTSmartPointer<ObjectTypeInfo>& a_outTypeInfoPtr)
		{
			return GetScriptObjectType1(a_className, a_outTypeInfoPtr);
		}

		bool IVirtualMachine::GetScriptObjectType(VMTypeID a_typeID, BSTSmartPointer<ObjectTypeInfo>& a_outTypeInfoPtr)
		{
			return GetScriptObjectType2(a_typeID, a_outTypeInfoPtr);
		}

		bool IVirtualMachine::GetScriptObjectTypeNoLoad(const BSFixedString& a_className, BSTSmartPointer<ObjectTypeInfo>& a_typeInfoPtr) const
		{
			return GetScriptObjectTypeNoLoad1(a_className, a_typeInfoPtr);
		}

		bool IVirtualMachine::GetScriptObjectTypeNoLoad(VMTypeID a_typeID, BSTSmartPointer<ObjectTypeInfo>& a_outTypeInfoPtr) const
		{
			return GetScriptObjectTypeNoLoad2(a_typeID, a_outTypeInfoPtr);
		}

		bool IVirtualMachine::GetVariableValue(const BSTSmartPointer<Object>& a_objPtr, std::uint32_t a_index, Variable& a_out) const
		{
			return GetVariableValue1(a_objPtr, a_index, a_out);
		}

		bool IVirtualMachine::GetVariableValue(VMHandle a_handle, const BSFixedString& a_className, std::int32_t a_variableIndex, Variable& a_out) const
		{
			return GetVariableValue2(a_handle, a_className, a_variableIndex, a_out);
		}

		void IVirtualMachine::SetCallableFromTasklets(const char* a_className, const char* a_stateName, const char* a_fnName, bool a_callable)
		{
			return SetCallableFromTasklets1(a_className, a_stateName, a_fnName, a_callable);
		}

		void IVirtualMachine::SetCallableFromTasklets(const char* a_className, const char* a_fnName, bool a_callable)
		{
			return SetCallableFromTasklets2(a_className, a_fnName, a_callable);
		}

		void IVirtualMachine::TraceForm(TESForm* a_form, const char* a_str, VMStackID a_stackID, Severity a_severity)
		{
			assert(a_str);

			BSFixedString name;
			if (a_form) {
				auto policy = GetObjectHandlePolicy();
				if (policy) {
					auto handle = policy->GetHandleForObject(a_form->GetFormType(), a_form);
					policy->ConvertHandleToString(handle, name);
				}
			}

			if (name.empty()) {
				name = "None";
			}

			std::string_view str(a_str);
			std::string      message;
			message.reserve(name.length() + 2 + str.length());
			message += name;
			message += ": ";
			message += str;

			TraceStack(message.c_str(), a_stackID, a_severity);
		}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wvarargs"
		void IVirtualMachine::VTraceStack(VMStackID a_stackID, Severity a_severity, const char* a_fmt, ...)
		{
			assert(a_fmt);

			std::va_list args1;
			va_start(args1, a_fmt);
			std::va_list args2;
			va_copy(args2, args1);

			std::vector<char> buf(std::vsnprintf(nullptr, 0, a_fmt, args1) + 1);
			va_end(args1);

			std::vsnprintf(buf.data(), buf.size(), a_fmt, args2);
			va_end(args2);

			TraceStack(buf.data(), a_stackID, a_severity);
		}
#pragma clang diagnostic pop

#ifdef SKYRIM_CROSS_VR
		void IVirtualMachine::ForEachBoundObject(VMHandle a_handle, IForEachScriptObjectFunctor* a_functor)
		{
			return REL::RelocateVirtual<decltype(&IVirtualMachine::ForEachBoundObject)>(0x1B, 0x1C, this, a_handle, a_functor);
		}

		bool IVirtualMachine::FindBoundObject(VMHandle a_handle, const char* a_className, BSTSmartPointer<Object>& a_result) const
		{
			return REL::RelocateVirtual<decltype(&IVirtualMachine::FindBoundObject)>(0x1C, 0x1E, this, a_handle, a_className, a_result);
		}

		void IVirtualMachine::MoveBoundObjects(VMHandle a_from, VMHandle a_to)
		{
			REL::RelocateVirtual<decltype(&IVirtualMachine::MoveBoundObjects)>(0x1D, 0x1F, this, a_from, a_to);
		}

		void IVirtualMachine::ResetAllBoundObjects(VMHandle a_handle)
		{
			REL::RelocateVirtual<decltype(&IVirtualMachine::ResetAllBoundObjects)>(0x1E, 0x20, this, a_handle);
		}

		bool IVirtualMachine::CastObject(const BSTSmartPointer<Object>& a_fromObjPtr, const BSTSmartPointer<ObjectTypeInfo>& a_toTypeInfoPtr, BSTSmartPointer<Object>& a_toObjPtr)
		{
			return REL::RelocateVirtual<decltype(&IVirtualMachine::CastObject)>(0x1F, 0x21, this, a_fromObjPtr, a_toTypeInfoPtr, a_toObjPtr);
		}

		bool IVirtualMachine::SetPropertyValue(BSTSmartPointer<Object>& a_obj, const char* a_propertyName, Variable& a_setVal)
		{
			return REL::RelocateVirtual<decltype(&IVirtualMachine::SetPropertyValue)>(0x20, 0x22, this, a_obj, a_propertyName, a_setVal);
		}

		bool IVirtualMachine::GetPropertyValue(BSTSmartPointer<Object>& a_obj, const char* a_propertyName, Variable& a_getVal)
		{
			return REL::RelocateVirtual<decltype(&IVirtualMachine::GetPropertyValue)>(0x21, 0x23, this, a_obj, a_propertyName, a_getVal);
		}

		bool IVirtualMachine::GetVariableValue1(const BSTSmartPointer<Object>& a_objPtr, std::uint32_t a_index, Variable& a_out) const
		{
			return REL::RelocateVirtual<decltype(&IVirtualMachine::GetVariableValue1)>(0x22, 0x24, this, a_objPtr, a_index, a_out);
		}

		bool IVirtualMachine::GetVariableValue2(VMHandle a_handle, const BSFixedString& a_className, std::int32_t a_variableIndex, Variable& a_out) const
		{
			return REL::RelocateVirtual<decltype(&IVirtualMachine::GetVariableValue2)>(0x23, 0x25, this, a_handle, a_className, a_variableIndex, a_out);
		}

		void IVirtualMachine::SendEvent(VMHandle a_handle, const BSFixedString& a_eventName, IFunctionArguments* a_args)
		{
			REL::RelocateVirtual<decltype(&IVirtualMachine::SendEvent)>(0x24, 0x26, this, a_handle, a_eventName, a_args);
		}

		void IVirtualMachine::SendEventAll(const BSFixedString& a_eventName, IFunctionArguments* a_args)
		{
			REL::RelocateVirtual<decltype(&IVirtualMachine::SendEventAll)>(0x25, 0x27, this, a_eventName, a_args);
		}

		bool IVirtualMachine::DispatchStaticCall(const BSFixedString& a_className, const BSFixedString& a_fnName, IFunctionArguments* a_args, BSTSmartPointer<IStackCallbackFunctor>& a_result)
		{
			return REL::RelocateVirtual<decltype(&IVirtualMachine::DispatchStaticCall)>(0x26, 0x28, this, a_className, a_fnName, a_args, a_result);
		}

		bool IVirtualMachine::DispatchMethodCall1(BSTSmartPointer<Object>& a_obj, const BSFixedString& a_fnName, IFunctionArguments* a_args, BSTSmartPointer<IStackCallbackFunctor>& a_result)
		{
			return REL::RelocateVirtual<decltype(&IVirtualMachine::DispatchMethodCall1)>(0x27, 0x29, this, a_obj, a_fnName, a_args, a_result);
		}

		bool IVirtualMachine::DispatchMethodCall2(VMHandle a_handle, const BSFixedString& a_className, const BSFixedString& a_fnName, IFunctionArguments* a_args, BSTSmartPointer<IStackCallbackFunctor>& a_result)
		{
			return REL::RelocateVirtual<decltype(&IVirtualMachine::DispatchMethodCall2)>(0x28, 0x2A, this, a_handle, a_className, a_fnName, a_args, a_result);
		}

		bool IVirtualMachine::DispatchUnboundMethodCall()
		{
			return REL::RelocateVirtual<decltype(&IVirtualMachine::DispatchUnboundMethodCall)>(0x29, 0x2B, this);
		}

		bool IVirtualMachine::IsWaitingOnLatent(VMStackID a_stackID) const
		{
			return REL::RelocateVirtual<decltype(&IVirtualMachine::IsWaitingOnLatent)>(0x2A, 0x2C, this, a_stackID);
		}

		void IVirtualMachine::ReturnFromLatent(VMStackID a_stackID, const Variable& a_val)
		{
			REL::RelocateVirtual<decltype(&IVirtualMachine::ReturnFromLatent)>(0x2B, 0x2D, this, a_stackID, a_val);
		}

		ErrorLogger* IVirtualMachine::GetErrorLogger()
		{
			return REL::RelocateVirtual<decltype(&IVirtualMachine::GetErrorLogger)>(0x2C, 0x2E, this);
		}

		IObjectHandlePolicy* IVirtualMachine::GetObjectHandlePolicy1()
		{
			return REL::RelocateVirtual<decltype(&IVirtualMachine::GetObjectHandlePolicy1)>(0x2D, 0x2F, this);
		}

		const IObjectHandlePolicy* IVirtualMachine::GetObjectHandlePolicy2() const
		{
			return REL::RelocateVirtual<decltype(&IVirtualMachine::GetObjectHandlePolicy2)>(0x2E, 0x30, this);
		}

		ObjectBindPolicy* IVirtualMachine::GetObjectBindPolicy1()
		{
			return REL::RelocateVirtual<decltype(&IVirtualMachine::GetObjectBindPolicy1)>(0x2F, 0x31, this);
		}

		const ObjectBindPolicy* IVirtualMachine::GetObjectBindPolicy2() const
		{
			return REL::RelocateVirtual<decltype(&IVirtualMachine::GetObjectBindPolicy2)>(0x30, 0x32, this);
		}

		ISavePatcherInterface* IVirtualMachine::GetSavePatcherInterface()
		{
			return REL::RelocateVirtual<decltype(&IVirtualMachine::GetSavePatcherInterface)>(0x31, 0x33, this);
		}

		void IVirtualMachine::RegisterForLogEvent(BSTEventSink<LogEvent>* a_sink)
		{
			REL::RelocateVirtual<decltype(&IVirtualMachine::RegisterForLogEvent)>(0x32, 0x34, this, a_sink);
		}

		void IVirtualMachine::UnregisterForLogEvent(BSTEventSink<LogEvent>* a_sink)
		{
			REL::RelocateVirtual<decltype(&IVirtualMachine::UnregisterForLogEvent)>(0x33, 0x35, this, a_sink);
		}

		void IVirtualMachine::RegisterForStatsEvent(BSTEventSink<StatsEvent>* a_sink)
		{
			REL::RelocateVirtual<decltype(&IVirtualMachine::RegisterForStatsEvent)>(0x34, 0x36, this, a_sink);
		}

		void IVirtualMachine::UnregisterForStatsEvent(BSTEventSink<StatsEvent>* a_sink)
		{
			REL::RelocateVirtual<decltype(&IVirtualMachine::UnregisterForStatsEvent)>(0x35, 0x37, this, a_sink);
		}
#endif
	}
}

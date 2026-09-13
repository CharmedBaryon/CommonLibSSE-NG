#pragma once

#include "RE/B/BSTSmartPointer.h"
#include "RE/I/IObjectHandlePolicy.h"
#include "RE/I/IVirtualMachine.h"
#include "RE/N/NativeFunction.h"
#include "RE/P/PackUnpack.h"
#include "RE/T/TypeTraits.h"
#include "RE/V/Variable.h"
#include "RE/V/VirtualMachine.h"

namespace RE
{
	namespace BSScript
	{
		template <bool IS_LONG, class F, class callbackR, class latentR, class Base, class... Args>
		class NativeLatentFunction : public NativeFunction<IS_LONG, F, std::underlying_type_t<callbackR>, Base, Args...>
		{
		public:
			using result_type = callbackR;
			using base_type = Base;
			using function_type = F;

			NativeLatentFunction() = delete;
			NativeLatentFunction(const NativeLatentFunction&) = delete;
			NativeLatentFunction(NativeLatentFunction&&) = delete;

			NativeLatentFunction(std::string_view a_fnName, std::string_view a_className, function_type a_callback) :
				NativeFunction<IS_LONG, F, std::underlying_type_t<callbackR>, Base, Args...>(a_fnName, a_className, a_callback)
			{
				this->_retType = GetRawType<latentR>();
				this->_isLatent = true;
			}

			~NativeLatentFunction() override = default;  // 00
		};
	}

	template <class R, class F, class = void>
	class NativeLatentFunction;

	template <class R, class Int, class F, class Cls, class... Args>
	class NativeLatentFunction<R, F(BSScript::Internal::VirtualMachine*, Int, Cls, Args...), std::enable_if_t<BSScript::is_valid_latent_long_sig_v<R, Int, F, Cls, Args...>>> :
		public BSScript::NativeLatentFunction<true, F(BSScript::Internal::VirtualMachine*, Int, Cls, Args...), F, R, Cls, Args...>
	{
	private:
		using super = BSScript::NativeLatentFunction<true, F(BSScript::Internal::VirtualMachine*, Int, Cls, Args...), F, R, Cls, Args...>;

	public:
		using result_type = typename super::result_type;
		using base_type = typename super::base_type;
		using function_type = typename super::function_type;

		using super::super;
	};

	namespace BSScript
	{
		enum LatentStatus : bool
		{
			kFailed,   // Failed to start latent funciton, return NONE and log error
			kStarted,  // Latent function started, script will pause until latent function finishes
		};

		/**
		@brief Registers a latent function. Unlike normal native functions, latent functions do not return a result to the script immediately.
		
		@details A latent function is intended for any native functions that take significant amount of time to execute (Utility.Wait(X) as an example). A latent function will block a script event until the latent function finishes
		Setup: A latent function is setup with three pieces: 
		1. The initial callback. This will setup the necessary logic for the latent execution, and returns a BSScript::LatentStatus for if the setup is successful. Note this callback must return as soon as possible to unblock the game.
		2. The latent logic. This can be a timer waiting X amount of time, a wait for some event, some crazy number crunching or anything inbetween. It is very important this logic is not executed in the callback
		3. The return. This will be any code that returns the result back to the script. It is important to store the stackID from the callback somewhere to identify which script event to return the result to.

		Notes:
		1. Since latent functions do not execute their logic while blocking the game, the player can save during a latent function execution. 
		Care must be taken to store the stackID as well as necessary relevant data for the latent function in the cosave, to resume execution when loading up the save. Otherwise, the script event will be permanently blocked without a call to return a result to it
		2. When returning a value, the value type must exactly match the result type specified here. As an example, if the result type in the registration is TESForm*, and the actual value is Actor* (which inherits TESForm), the actor MUST be casted to TESForm with myActor->As<TESForm>() before being returned;

		@tparam R The result type to return with IVirtualMachine::ReturnLatentResult
		@param a_fnName name of the latent function
		@param a_className name of the class holding the latent function
		@param a_callback initial callback. This must be setup as BSScript::LatentStatus callback(BSScript::Internal::VirtualMachine*, VMStackID, Cls, Args...)
		@param a_callableFromTasklets Whether the function can be invoked immediately from a script (not thread safe!) or wait for the next frame to invoke (thread safe!)
		@see IVirtualMachine::ReturnLatentResult
		@see https://www.creationkit.com/index.php?title=Category:Latent_Functions
		*/
		template <class R, class F>
		void IVirtualMachine::RegisterLatentFunction(std::string_view a_fnName, std::string_view a_className, F a_callback, bool a_callableFromTasklets)
		{
			BindNativeMethod(new RE::NativeLatentFunction<R, std::remove_pointer_t<F>>(a_fnName, a_className, a_callback));
			if (a_callableFromTasklets) {
				SetCallableFromTasklets(a_className.data(), a_fnName.data(), true);
			}
		}

		/**
		@brief Returns a result to the stack if it is waiting for a latent function to return. This is a wrapper over ReturnFromLatent.
		
		@param a_stackID ID of the stack waiting for the latent result
		@param a_result result to return to the stack

		*/
		template <class V>
			requires is_return_convertible_v<V>
		void IVirtualMachine::ReturnLatentResult(VMStackID a_stackID, V a_result)
		{
			RE::BSScript::Variable var;
			var.Pack(a_result);
			ReturnFromLatent(a_stackID, var);
		}
	}
}

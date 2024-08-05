#include "RE/B/BSAtomic.h"

#include "REX/W32/KERNEL32.h"

namespace RE
{
	BSSemaphoreBase::BSSemaphoreBase() :
		semaphore()
	{
		stl::memzero(&semaphore);
		semaphore = REX::W32::CreateSemaphoreA(nullptr, 0, 40, nullptr);
	}

	BSSemaphoreBase::~BSSemaphoreBase()
	{
		REX::W32::CloseHandle(semaphore);
		stl::memzero(&semaphore);
	}

	BSSpinLock::BSSpinLock() :
		_owningThread(0),
		_lockCount(0)
	{}

	void BSSpinLock::Lock(std::uint32_t a_pauseAttempts)
	{
		std::uint32_t myThreadID = REX::W32::GetCurrentThreadId();

		_mm_lfence();
		if (_owningThread == myThreadID) {
			REX::W32::InterlockedIncrement(&_lockCount);
		} else {
			std::uint32_t attempts = 0;
			if (REX::W32::InterlockedCompareExchange(&_lockCount, 1, 0)) {
				do {
					++attempts;
					_mm_pause();
					if (attempts >= a_pauseAttempts) {
						std::uint32_t spinCount = 0;
						while (REX::W32::InterlockedCompareExchange(&_lockCount, 1, 0)) {
							REX::W32::Sleep(++spinCount < kFastSpinThreshold ? 0 : 1);
						}
						break;
					}
				} while (REX::W32::InterlockedCompareExchange(&_lockCount, 1, 0));
				_mm_lfence();
			}

			_owningThread = myThreadID;
			_mm_sfence();
		}
	}

	void BSSpinLock::Unlock()
	{
		std::uint32_t myThreadID = REX::W32::GetCurrentThreadId();

		_mm_lfence();
		if (_owningThread == myThreadID) {
			if (_lockCount == 1) {
				_owningThread = 0;
				_mm_mfence();
				REX::W32::InterlockedCompareExchange(&_lockCount, 0, 1);
			} else {
				REX::W32::InterlockedDecrement(&_lockCount);
			}
		}
	}

	BSReadWriteLock::BSReadWriteLock() :
		_writerThread(0),
		_lock(0)
	{}

	void BSReadWriteLock::LockForRead()
	{
		using func_t = decltype(&BSReadWriteLock::LockForRead);
		static REL::Relocation<func_t> func{ RELOCATION_ID(66976, 68233) };
		func(this);
	}

	void BSReadWriteLock::UnlockForRead()
	{
		using func_t = decltype(&BSReadWriteLock::UnlockForRead);
		static REL::Relocation<func_t> func{ RELOCATION_ID(66982, 68239) };
		func(this);
	}

	void BSReadWriteLock::LockForWrite()
	{
		using func_t = decltype(&BSReadWriteLock::LockForWrite);
		static REL::Relocation<func_t> func{ RELOCATION_ID(66977, 68234) };
		func(this);
	}

	void BSReadWriteLock::UnlockForWrite()
	{
		using func_t = decltype(&BSReadWriteLock::UnlockForWrite);
		static REL::Relocation<func_t> func{ RELOCATION_ID(66983, 68240) };
		func(this);
	}

	BSSpinLockGuard::BSSpinLockGuard(BSSpinLock& a_lock) :
		_lock(a_lock)
	{
		_lock.Lock();
	}

	BSSpinLockGuard::~BSSpinLockGuard()
	{
		_lock.Unlock();
	}

	BSReadLockGuard::BSReadLockGuard(BSReadWriteLock& a_lock) :
		_lock(a_lock)
	{
		_lock.LockForRead();
	}

	BSReadLockGuard::~BSReadLockGuard()
	{
		_lock.UnlockForRead();
	}

	BSWriteLockGuard::BSWriteLockGuard(BSReadWriteLock& a_lock) :
		_lock(a_lock)
	{
		_lock.LockForWrite();
	}

	BSWriteLockGuard::~BSWriteLockGuard()
	{
		_lock.UnlockForWrite();
	}
}

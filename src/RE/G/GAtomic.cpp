#include "RE/G/GAtomic.h"

#include "REX/W32/KERNEL32.h"

namespace RE
{
	GLock::Locker::Locker(GLock* a_lock)
	{
		lock = a_lock;
		lock->Lock();
	}

	GLock::Locker::~Locker()
	{
		lock->Unlock();
	}

	GLock::GLock(std::uint32_t a_spinCount)
	{
		REX::W32::InitializeCriticalSectionAndSpinCount(&cs, a_spinCount);
	}

	GLock::~GLock()
	{
		REX::W32::DeleteCriticalSection(&cs);
	}

	void GLock::Lock()
	{
		REX::W32::EnterCriticalSection(&cs);
	}

	void GLock::Unlock()
	{
		REX::W32::LeaveCriticalSection(&cs);
	}
}

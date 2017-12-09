//////////////////////////////////////////////////////////////////////////
#include "Threading/Semaphore.hpp"

using namespace Cpf;
using namespace Threading;

Semaphore::Semaphore(int initCount)
{
	m_Handle.m_Count = initCount;
	pthread_mutex_init( &m_Handle.m_Mutex, NULL );
	pthread_cond_init( &m_Handle.m_Condition, NULL );
}


Semaphore::~Semaphore()
{
	pthread_mutex_destroy( &m_Handle.m_Mutex );
	pthread_cond_destroy( &m_Handle.m_Condition );
}


void Semaphore::Acquire()
{
	if( pthread_mutex_lock( &m_Handle.m_Mutex ) == 0 )
	{
		for( ;; )
		{
			if( m_Handle.m_Count > 0 )
			{
				m_Handle.m_Count--;
				if( pthread_mutex_unlock( &m_Handle.m_Mutex )==0 )
					return;
				// error case..
				return;
			}
			if( pthread_cond_wait( &m_Handle.m_Condition, &m_Handle.m_Mutex )!=0 )
				break;
		}
	}
}


void Semaphore::Release(int count)
{
	if( pthread_mutex_lock( &m_Handle.m_Mutex )==0 )
	{
		// Check for overflow.
		if( m_Handle.m_Count&0x80000000 )
		{
			pthread_mutex_unlock( &m_Handle.m_Mutex );
			// error case.
			return;
		}

		m_Handle.m_Count += count;
		if( pthread_mutex_unlock( &m_Handle.m_Mutex )==0 )
			if( pthread_cond_broadcast( &m_Handle.m_Condition )==0 )
				return;
	}

	// error case.
}

//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Threading/Threading.hpp"
#include "Platform/Threading/Types.hpp"
#include "Time/Value.hpp"
#include "Functional.hpp"
#include "Move.hpp"


namespace Cpf
{
	namespace Platform
	{
		namespace Threading
		{
			//////////////////////////////////////////////////////////////////////////
			/// A basic thread wrapper class.
			//////////////////////////////////////////////////////////////////////////
			class CPF_EXPORT_THREADING Thread
			{
			public:
				//////////////////////////////////////////////////////////////////////////
				class Group;

				//////////////////////////////////////////////////////////////////////////
				Thread();
				~Thread();

				//////////////////////////////////////////////////////////////////////////
				template<typename tFunction, typename... tArgs>
				explicit Thread(tFunction&& func, tArgs&&... args);

				template<typename tFunction, typename... tArgs>
				void operator ()(tFunction&& func, tArgs&&... args);

				//////////////////////////////////////////////////////////////////////////
				void Join();

				//////////////////////////////////////////////////////////////////////////
				static void Sleep(const Time::Value&);
				static void Pause();
				static void GetThreadTimes(Time::Value& userTime, Time::Value& kernelTime);
				static void SetName(const char*);
				static int GetHardwareThreadCount();

				//////////////////////////////////////////////////////////////////////////
				Thread_t& NativeHandle();

			private:
				//////////////////////////////////////////////////////////////////////////
				Thread(const Thread&) = delete;
				Thread(Thread&&) = delete;
				const Thread& operator =(const Thread&) = delete;
				Thread& operator =(Thread&&) = delete;

				//////////////////////////////////////////////////////////////////////////
				void _Start(Function<void(void)>&&);

				//////////////////////////////////////////////////////////////////////////
				Thread_t m_Handle;
			};


			//////////////////////////////////////////////////////////////////////////
			/**
			 * @brief A container for a group of threads.
			 */
			class CPF_EXPORT_THREADING Thread::Group
			{
			public:
				Group();
				Group(size_t count);
				explicit Group(Group&&);
				~Group();

				Group& operator =(Group&&);

				bool Initialize(size_t count);

				template<typename tFunction>
				void operator ()(tFunction&& func);

				template<typename tFunction>
				void operator ()(size_t index, tFunction&& func);

				void Join();

				explicit operator bool() const;

				size_t Size() const;

			private:
				Group(const Group&) = delete;
				const Group& operator =(const Group&) = delete;

				void _Start(size_t index, Function<void(void)>);
				void _Start(Function<void(void)>);

				size_t mCount;
				Thread* mpThreads;
			};


			/**
			 * @brief Thread constructor which takes the function and arguments to call.
			 * @param func The thread function to run.
			 * @param args The arguments sent to the thread function.
			 */
			template<typename tFunction, typename... tArgs>
			Thread::Thread(tFunction&& func, tArgs&&... args)
			{
				_Start(Cpf::Move(std::bind(func, args...)));
			}


			/**
			 * @brief Command operator to start a function and arguments as a thread.
			 * @param func The thread function to run.
			 * @param args The arguments sent to the thread function.
			 */
			template<typename tFunction, typename... tArgs>
			void Thread::operator ()(tFunction&& func, tArgs&&... args)
			{
				_Start(Cpf::Move(std::bind(func, args...)));
			}


			template<typename tFunction>
			void Thread::Group::operator ()(tFunction&& func)
			{
				_Start(Cpf::Move(func));
			};


			template<typename tFunction>
			void Thread::Group::operator ()(size_t index, tFunction&& func)
			{
				_Start(index, Cpf::Move(func));
			};
		}
	}
}

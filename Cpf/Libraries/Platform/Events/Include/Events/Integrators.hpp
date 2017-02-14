//////////////////////////////////////////////////////////////////////////
#pragma once


//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	namespace Platform
	{
		namespace Events
		{
			namespace Integrators
			{
				//////////////////////////////////////////////////////////////////////////
				template<typename RESULTTYPE>
				class LastOf
				{
				public:
					typedef RESULTTYPE ResultType_t;

					LastOf() : mResult() {}

					template<typename FUNCTION, typename... ARGS>
					void operator ()(FUNCTION func, ARGS... args)
					{
						mResult = func(args...);
					}
					RESULTTYPE operator ()() const { return RESULTTYPE(0); }

				private:
					RESULTTYPE mResult;
				};


				template<>
				class LastOf < void >
				{
				public:
					typedef void ResultType_t;

					template<typename FUNCTION, typename... ARGS>
					void operator ()(FUNCTION func, ARGS... args)
					{
						func(args...);
					}
					void operator ()() const {}
				};
			}


			//////////////////////////////////////////////////////////////////////////
			template<typename RESULTTYPE, const RESULTTYPE VALUE, const RESULTTYPE PASS_VALUE, const RESULTTYPE FAIL_VALUE>
			class AnyNotEqual
			{
			public:
				typedef RESULTTYPE ResultType_t;

				AnyNotEqual() : mResult(PASS_VALUE) {}

				template<typename FUNCTION, typename... ARGS>
				void operator ()(FUNCTION func, ARGS... args)
				{
					RESULTTYPE value = func(args...);
					if (value != VALUE)
						mResult = FAIL_VALUE;
				}
				RESULTTYPE operator ()() const { return mResult; }

			private:
				RESULTTYPE mResult;
			};
		}
	}
}

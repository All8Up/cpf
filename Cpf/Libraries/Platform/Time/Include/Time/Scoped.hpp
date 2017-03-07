//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Time.hpp"
#include "Time/Value.hpp"


//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	namespace Time
	{
		//////////////////////////////////////////////////////////////////////////
		/// Scoped is a timer encapsulation for scoped delta time measurements.
		//////////////////////////////////////////////////////////////////////////
		template<typename ACTION>
		class Scoped
		{
		public:
			Scoped(Value& value);
			~Scoped();

			Value& Start();

		private:
			Value mStart;
			ACTION mAction;
		};


		//////////////////////////////////////////////////////////////////////////
		/// ScopedNull is a do nothing variation when internal profiling is disabled.
		//////////////////////////////////////////////////////////////////////////
		class CPF_EXPORT_TIME ScopedNull
		{
		public:
			ScopedNull(Value& value);

			Value& Start();
		};


		namespace Action
		{
			//////////////////////////////////////////////////////////////////////////
			/// Store stores the final delta value in the referenced value.
			//////////////////////////////////////////////////////////////////////////
			class CPF_EXPORT_TIME Store
			{
			public:
				Store(Value& value);
				void operator ()(const Value& duration);

			private:
				Value& mValue;
			};


			//////////////////////////////////////////////////////////////////////////
			/// Add adds the delta value to the referenced value.
			//////////////////////////////////////////////////////////////////////////
			class CPF_EXPORT_TIME Add
			{
			public:
				Add(Value& value);
				void operator ()(const Value& duration);

			private:
				Value& mValue;
			};


			//////////////////////////////////////////////////////////////////////////
			/// Average the delta time value over a given number of samples.
			//////////////////////////////////////////////////////////////////////////
			template<const int SAMPLES = 10>
			class Average
			{
			public:
				Average(Value& value);
				void operator ()(const Value& duration);

			private:
				Value& mValue;
				Value mTotal;
				int mIndex;
				Value mSamples[SAMPLES];
			};
		}


		//////////////////////////////////////////////////////////////////////////
		using ScopedAdd = Scoped<Action::Add>;
		using ScopedStore = Scoped<Action::Store>;
		using ScopedAverage10 = Scoped<Action::Average<10>>;


		//////////////////////////////////////////////////////////////////////////
		template<typename ACTION>
		Scoped<ACTION>::Scoped(Value& value)
			: mAction(value)
		{
			mStart = Value::Now();
		}
		template<typename ACTION>
		Scoped<ACTION>::~Scoped()
		{
			Value delta = Value::Now() - mStart;
			mAction(delta);
		}

		template<typename ACTION>
		Value& Scoped<ACTION>::Start()
		{
			return mStart;
		}


		namespace Action
		{
			//////////////////////////////////////////////////////////////////////////
			template<const int SAMPLES>
			Average<SAMPLES>::Average(Value& value)
				: mValue(value)
				, mIndex(0)
			{
			}

			template<const int SAMPLES>
			void Average<SAMPLES>::operator ()(const Value& duration)
			{
				// Remove and overwrite the old sample.
				mTotal -= mSamples[mIndex];
				mTotal += duration;
				mSamples[mIndex++] = duration;

				// Loop the index.
				mIndex = mIndex % SAMPLES;

				// Store the new average.
				mValue = mTotal / SAMPLES;
			}
		}
	}
}

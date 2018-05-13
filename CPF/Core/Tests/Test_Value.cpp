#include "CPF/Time.hpp"
#include "TimeTestFixture.hpp"

TEST_F(TimeTestFixture, InitializationValue)
{
	using namespace CPF::Time;
	{
		// A note about the use of 'near'.
		// Working in Us/Ms is very prone to rounding error, as such
		// we make sure things are within 1/10th and 1/1000th
		// Us/Ms respective unit and don't try to be picky.
		// In the real world, the precision loss is avoided
		// by keeping everything in specific units or in the
		// OS native unit and only converting at the end.
		Value tpUs(Us(1));
		EXPECT_NEAR(1.0e-6, Seconds(tpUs).Cast<double>(), 0.000001);

		Value tpMs(Ms(1));
		EXPECT_NEAR(1.0e-3, Seconds(tpMs).Cast<double>(), 1.0e-6);

		Value tpSeconds(Seconds(1));
		EXPECT_DOUBLE_EQ(1.0, Seconds(tpSeconds).Cast<double>());

		Value tpMinutes(Minutes(1));
		EXPECT_DOUBLE_EQ(60.0, Seconds(tpMinutes).Cast<double>());

		Value tpHours(Hours(1));
		EXPECT_DOUBLE_EQ(60.0*60.0, Seconds(tpHours).Cast<double>());

		Value tpDays(Days(1));
		EXPECT_DOUBLE_EQ(60.0*60.0*24.0, Seconds(tpDays).Cast<double>());

		Value tpYears(Years(1));
		EXPECT_DOUBLE_EQ(60.0*60.0*24.0*365.0, Seconds(tpYears).Cast<double>());
	}
}


TEST_F(TimeTestFixture, ComparisonsValue)
{
	using namespace CPF::Time;
	{
		Value tpOneMicrosecond(Us(1));
		Value tpOneMillisecond(Ms(1));
		Value tpOneSecond(Seconds(1));
		Value tpOneHour(Hours(1));

		EXPECT_TRUE(tpOneMillisecond > tpOneMicrosecond);
		EXPECT_TRUE(tpOneSecond > tpOneMicrosecond);
		EXPECT_TRUE(tpOneHour > tpOneMicrosecond);

		EXPECT_TRUE(tpOneMicrosecond < tpOneMillisecond);
		EXPECT_TRUE(tpOneMicrosecond < tpOneSecond);
		EXPECT_TRUE(tpOneMicrosecond < tpOneHour);

		EXPECT_TRUE(tpOneMillisecond >= tpOneMicrosecond);
		EXPECT_TRUE(tpOneSecond >= tpOneMicrosecond);
		EXPECT_TRUE(tpOneHour >= tpOneMicrosecond);
		EXPECT_TRUE(tpOneMillisecond >= tpOneMillisecond);

		EXPECT_TRUE(tpOneMicrosecond <= tpOneMillisecond);
		EXPECT_TRUE(tpOneMicrosecond <= tpOneSecond);
		EXPECT_TRUE(tpOneMicrosecond <= tpOneHour);
		EXPECT_TRUE(tpOneMicrosecond <= tpOneMicrosecond);

		EXPECT_TRUE(tpOneMicrosecond == tpOneMicrosecond);
		EXPECT_TRUE(tpOneMicrosecond != tpOneHour);
	}
}


TEST_F(TimeTestFixture, MathValue)
{
	using namespace CPF::Time;
	{
		Value tpFiveHundredMicroseconds(Us(500));
		Value tpOneThousandMicroseconds(tpFiveHundredMicroseconds + tpFiveHundredMicroseconds);

		EXPECT_NEAR(1000.0, Us(tpOneThousandMicroseconds).Cast<double>(), 1.0);
	}
}


TEST_F(TimeTestFixture, CommonUsageValue)
{
	// NOTE: This is not a proper test, this is currently just a run through of the common
	// API usage requirements.
	using namespace CPF::Time;
	{
		// The standard usage of this system is to build delta time.
		// We'll fake a last frame time.
		Value lastFrame(Now()-Ms(12));


		// And we will get the current frame time.
		Value now(Now());
		float deltaFloat = float(Seconds(now-lastFrame));


        // A variation of delta time calculation is to designate a point in the future.
        Value nextSimTime = Now()+Seconds(0.5f);
		(void)nextSimTime;


        // A variation using countdown timing, execute every half second based on delta time elapsed.
        Value lastSim = Now();
        lastSim -= Seconds(deltaFloat);
        if(lastSim<=Value::Zero())
        {
            lastSim += Seconds(0.5f);
        }
	}
}

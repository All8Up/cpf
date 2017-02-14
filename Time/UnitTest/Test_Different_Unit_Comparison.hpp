//////////////////////////////////////////////////////////////////////////
#include "Time/Unit.hpp"


TEST_F(TimeLibrary, UnitComparison)
{
	using namespace Cpf::Platform::Time;

	EXPECT_TRUE(oneNs < oneUs);
	EXPECT_TRUE(oneUs < oneMs);
	EXPECT_TRUE(oneMs < oneSecond);
	EXPECT_TRUE(oneSecond < oneMinute);
	EXPECT_TRUE(oneMinute < oneHour);
	EXPECT_TRUE(oneHour < oneDay);
	EXPECT_TRUE(oneDay < oneYear);

	EXPECT_TRUE(oneNs <= oneUs);
	EXPECT_TRUE(oneUs <= oneMs);
	EXPECT_TRUE(oneMs <= oneSecond);
	EXPECT_TRUE(oneSecond <= oneMinute);
	EXPECT_TRUE(oneMinute <= oneHour);
	EXPECT_TRUE(oneHour <= oneDay);
	EXPECT_TRUE(oneDay <= oneYear);

	Us oneNs_Us(oneUs);
	EXPECT_TRUE(oneNs <= oneNs_Us);
	Ms oneUs_Ms(oneMs);
	EXPECT_TRUE(oneUs <= oneUs_Ms);
	Seconds oneMs_Second(oneSecond);
	EXPECT_TRUE(oneMs <= oneMs_Second);

	EXPECT_TRUE(oneUs > oneNs);
	EXPECT_TRUE(oneMs > oneUs);
	EXPECT_TRUE(oneSecond > oneMs);
	EXPECT_TRUE(oneMinute > oneSecond);
	EXPECT_TRUE(oneHour > oneMinute);
	EXPECT_TRUE(oneDay > oneHour);
	EXPECT_TRUE(oneYear > oneDay);

	EXPECT_TRUE(oneUs >= oneNs);
	EXPECT_TRUE(oneMs >= oneUs);
	EXPECT_TRUE(oneSecond >= oneMs);
	EXPECT_TRUE(oneMinute >= oneSecond);
	EXPECT_TRUE(oneHour >= oneMinute);
	EXPECT_TRUE(oneDay >= oneHour);
	EXPECT_TRUE(oneYear >= oneDay);

	EXPECT_TRUE(oneNs_Us >= oneNs);
	EXPECT_TRUE(oneUs_Ms >= oneUs);
	EXPECT_TRUE(oneMs_Second >= oneMs);
}

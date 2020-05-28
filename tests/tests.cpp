#include "gtest/gtest.h"
#include "../include/utils/LocationUtils.hpp"
#include "../include/utils/TimeUtils.hpp"
#include <ctime>

TEST(IPLocation, TestExampleLocation) 
{
    EXPECT_EQ(locationFromIP("82.44.92.211"), "United Kingdom");
}

TEST(IPLocation, TestInvalidIp) 
{
    EXPECT_EQ(locationFromIP("Invalid"), "WRONG INPUT");
}

TEST(IPLocation, TestPrivateLocation) 
{
    EXPECT_EQ(locationFromIP("10.0.0.65"), TCPDP_NETWORK::PRIVATE_IP_LABEL);
}

TEST(IPLocation, TestPrivate) 
{
    EXPECT_EQ(isPrivateIPAddress("192.168.0.1"), true);
}

TEST(IPLocation, TestPrivate9) 
{
    EXPECT_EQ(isPrivateIPAddress("192.10.0.1"), false);
}

TEST(IPLocation, TestPrivate2) 
{
    EXPECT_EQ(isPrivateIPAddress("10.0.0.1"), true);
}

TEST(IPLocation, TestPrivate3) 
{
    EXPECT_EQ(isPrivateIPAddress("172.16.0.1"), true);
}

TEST(IPLocation, TestPrivate4) 
{
    EXPECT_EQ(isPrivateIPAddress("172.17.0.1"), true);
}

TEST(IPLocation, TestPrivate5) 
{
    EXPECT_EQ(isPrivateIPAddress("172.20.0.1"), true);
}

TEST(IPLocation, TestPrivate6) 
{
    EXPECT_EQ(isPrivateIPAddress("172.31.0.1"), true);
}

TEST(IPLocation, TestPrivate7) 
{
    EXPECT_EQ(isPrivateIPAddress("172.32.0.1"), false);
}

TEST(IPLocation, TestPrivate8) 
{
    EXPECT_EQ(isPrivateIPAddress("11.0.0.1"), false);
}

TEST(Time, TestExampleTime) 
{
    std::string months[] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
    time_t now = time(0);
    struct tm * final_tm = localtime(&now);
    std::ostringstream expcted;
    expcted << final_tm->tm_mday << " " << months[final_tm->tm_mon] << " " << (final_tm->tm_year+1900) << ", 13:18";
    EXPECT_EQ(convertTimestamp("13:18:11.863706"), expcted.str());
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
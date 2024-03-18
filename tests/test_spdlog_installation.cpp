#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <gtest/gtest.h>

// Test case for spdlog initialization and logging
TEST(SpdlogTest, InitializationAndLoggingTest) {
    // Create a test logger
    auto test_logger = spdlog::create<spdlog::sinks::stdout_sink_mt>("test_logger");

    // Log a message
    test_logger->info("This is a test message");

    // Check if the logging was successful
    EXPECT_TRUE(test_logger->should_log(spdlog::level::info));
}

// Entry point for the test
int main(int argc, char** argv) {
    // Initialize Google Test
    ::testing::InitGoogleTest(&argc, argv);

    // Run the tests
    return RUN_ALL_TESTS();
}
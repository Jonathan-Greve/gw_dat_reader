#include <gtest/gtest.h>
#include <flatbuffers/flatbuffers.h>

// Test case for FlatBuffers initialization
TEST(FlatBuffersTest, InitializationTest) {
    // Create a FlatBufferBuilder
    flatbuffers::FlatBufferBuilder builder;

    // Create a simple string using FlatBuffers
    auto str = builder.CreateString("Hello, FlatBuffers!");

    // Finish the buffer
    builder.Finish(str);

    // Check if the buffer was created successfully
    EXPECT_TRUE(builder.GetSize() > 0);
}

// Entry point for the test
int main(int argc, char** argv) {
    // Initialize Google Test
    ::testing::InitGoogleTest(&argc, argv);

    // Run the tests
    return RUN_ALL_TESTS();
}
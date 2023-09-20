extern "C" {
    #include "handlers.h"  // Ensure your header files are wrapped in extern "C" when included in C++
    #include "mock_evhttp.h"
}

#include <gtest/gtest.h>


TEST(ServerTest, RootCallbackTest) {
    struct evhttp_request mock_request;
    mock_request.input_buffer = mock_evbuffer_new();
    mock_request.output_buffer = mock_evbuffer_new();
    mock_request.response_code = 0; // Not yet set
    mock_request.uri = "/";

    // Set up other fields as needed for your test scenario.

    root_callback(&mock_request, NULL); // Assuming arg isn't used

    // Assert the expected outcomes.
    // For example, check if the response code is set correctly, or if the output_buffer has the expected data.
    EXPECT_EQ(mock_request.response_code, 200); // Example assertion

    // Cleanup
    mock_evbuffer_free(mock_request.input_buffer);
    mock_evbuffer_free(mock_request.output_buffer);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

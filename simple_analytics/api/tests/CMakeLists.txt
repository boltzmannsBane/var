# In tests/CMakeLists.txt
add_executable(handlers_test handlers_test.cpp) # Using test_app to avoid conflicts
target_link_libraries(handlers_test gtest gtest_main gmock event event_core event_extra pthread)


target_include_directories(handlers_test PRIVATE ${CMAKE_SOURCE_DIR}/)


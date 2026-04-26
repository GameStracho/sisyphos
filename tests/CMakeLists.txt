include(GoogleTest)

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_executable(sisyphos_tests ${TEST_SOURCES})

target_link_libraries(sisyphos_tests
    PRIVATE
        sisyphos_engine
        GTest::gtest_main
)

# Automatically registers each TEST() as a CTest case.
gtest_discover_tests(sisyphos_tests DISCOVERY_MODE PRE_TEST)

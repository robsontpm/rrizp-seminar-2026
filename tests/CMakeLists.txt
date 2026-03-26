find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(test_roessler test_roessler.cpp)
target_link_libraries(test_roessler roessler_lib capd Boost::unit_test_framework)

add_test(NAME test_roessler COMMAND test_roessler)

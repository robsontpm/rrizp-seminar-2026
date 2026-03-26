find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(test_roessler test_roessler.cpp)
target_link_libraries(test_roessler roessler_lib capd Boost::unit_test_framework)

add_test(NAME test_roessler COMMAND test_roessler)

add_executable(test_biffurcation test_biffurcation.cpp)
target_link_libraries(test_biffurcation biffurcation_lib capd Boost::unit_test_framework)

add_test(NAME test_biffurcation COMMAND test_biffurcation)

#define BOOST_TEST_MODULE BiffurcationTest
#include <boost/test/unit_test.hpp>
#include "biffurcation.h"
#include <fstream>
#include <string>
#include <cstdio>
#include <iostream>

BOOST_AUTO_TEST_CASE(test_generate_biffurcation_files_exist) {
    BiffurcationParams params;
    params.S = 1;
    params.n = 1;
    // narrow interval and single value of c to test execution without timing out
    params.c_min = 2.0;
    params.c_max = 2.0;
    params.prefix = "test_biff";

    // Clean up before test
    std::remove("test_biff.dat");
    std::remove("test_biff.gp");
    std::remove("test_biff.png");

    generate_biffurcation_diagram(params);

    // Verify .dat exists
    std::ifstream datFile("test_biff.dat");
    BOOST_TEST(datFile.good());

    // Check it's not empty
    std::string line;
    std::getline(datFile, line);
    BOOST_TEST(!line.empty());
    datFile.close();

    // Verify .gp exists
    std::ifstream gpFile("test_biff.gp");
    BOOST_TEST(gpFile.good());
    gpFile.close();

    // Verify .png exists
    std::ifstream pngFile("test_biff.png");
    BOOST_TEST(pngFile.good());
    pngFile.close();

    // Clean up after test
    std::remove("test_biff.dat");
    std::remove("test_biff.gp");
    std::remove("test_biff.png");
}

BOOST_AUTO_TEST_CASE(test_biffurcation_invalid_file_location) {
    BiffurcationParams params;
    params.S = 1;
    params.n = 1;
    params.c_min = 2.0;
    params.c_max = 2.0;
    params.prefix = "/invalid/path/to/biff";

    BOOST_CHECK_THROW(generate_biffurcation_diagram(params), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(test_biffurcation_invalid_range) {
    BiffurcationParams params;
    params.c_min = 6.0;
    params.c_max = 2.0;
    params.prefix = "test_biff_invalid_range";

    BOOST_CHECK_THROW(generate_biffurcation_diagram(params), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(test_biffurcation_zero_n) {
    BiffurcationParams params;
    params.S = 1;
    params.n = 0;
    params.c_min = 2.0;
    params.c_max = 2.0;
    params.prefix = "test_biff_zero";

    // Clean up before test
    std::remove("test_biff_zero.dat");

    generate_biffurcation_diagram(params);

    std::ifstream datFile("test_biff_zero.dat");
    BOOST_TEST(datFile.good());
    std::string line;
    std::getline(datFile, line);
    BOOST_TEST(line.empty()); // The file should be empty since n=0
    datFile.close();

    std::remove("test_biff_zero.dat");
    std::remove("test_biff_zero.gp");
    std::remove("test_biff_zero.png");
}

#define BOOST_TEST_MODULE RoesslerTest
#include <boost/test/included/unit_test.hpp>
#include "roessler.h"
#include <fstream>
#include <string>
#include <cstdio>
#include <iostream>

BOOST_AUTO_TEST_CASE(test_generate_roessler_files_exist) {
    RoesslerParams params;
    params.S = 1.0;
    params.T = 1.0;
    params.prefix = "test_roessler";

    // Clean up before test
    std::remove("test_roessler.dat");
    std::remove("test_roessler.gp");
    std::remove("test_roessler.png");

    generate_roessler_data(params);

    // Verify .dat exists
    std::ifstream datFile("test_roessler.dat");
    BOOST_TEST(datFile.good());

    // Check it's not empty
    std::string line;
    std::getline(datFile, line);
    BOOST_TEST(!line.empty());
    datFile.close();

    // Verify .gp exists
    std::ifstream gpFile("test_roessler.gp");
    BOOST_TEST(gpFile.good());
    gpFile.close();

    // Verify .png exists
    std::ifstream pngFile("test_roessler.png");
    BOOST_TEST(pngFile.good());
    pngFile.close();

    // Clean up after test
    std::remove("test_roessler.dat");
    std::remove("test_roessler.gp");
    std::remove("test_roessler.png");
}

BOOST_AUTO_TEST_CASE(test_roessler_invalid_file_location) {
    RoesslerParams params;
    params.S = 1.0;
    params.T = 1.0;
    params.prefix = "/invalid/path/to/roessler";

    BOOST_CHECK_THROW(generate_roessler_data(params), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(test_roessler_zero_t) {
    RoesslerParams params;
    params.S = 1.0;
    params.T = 0.0;
    params.prefix = "test_roessler_zero";

    // Clean up before test
    std::remove("test_roessler_zero.dat");

    generate_roessler_data(params);

    std::ifstream datFile("test_roessler_zero.dat");
    BOOST_TEST(datFile.good());
    std::string line;
    std::getline(datFile, line);
    BOOST_TEST(line.empty()); // The file should be empty since T=0
    datFile.close();

    std::remove("test_roessler_zero.dat");
    std::remove("test_roessler_zero.gp");
    std::remove("test_roessler_zero.png");
}

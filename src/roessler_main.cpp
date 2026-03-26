#include "roessler.h"
#include <iostream>
#include <string>
#include <vector>
#include <getopt.h>

void print_help() {
    std::cout << "Roessler System Generator\n";
    std::cout << "Usage: ./roessler [options]\n";
    std::cout << "Options:\n";
    std::cout << "  --x0=<val>      Initial x value (default: 1.0)\n";
    std::cout << "  --y0=<val>      Initial y value (default: 1.0)\n";
    std::cout << "  --z0=<val>      Initial z value (default: 1.0)\n";
    std::cout << "  --S=<val>       Discard trajectory length (default: 100.0)\n";
    std::cout << "  --T=<val>       Trajectory length to draw (default: 100.0)\n";
    std::cout << "  --a=<val>       Parameter 'a' (default: 0.2)\n";
    std::cout << "  --b=<val>       Parameter 'b' (default: 0.2)\n";
    std::cout << "  --c=<val>       Parameter 'c' (default: 5.7)\n";
    std::cout << "  --prefix=<val>  Prefix for output files (default: roessler)\n";
    std::cout << "  --help          Print this help message\n";
}

bool parse_args(int argc, char** argv, RoesslerParams& params) {
    const char* const short_opts = "h";
    const option long_opts[] = {
        {"x0", required_argument, nullptr, 1},
        {"y0", required_argument, nullptr, 2},
        {"z0", required_argument, nullptr, 3},
        {"S", required_argument, nullptr, 4},
        {"T", required_argument, nullptr, 5},
        {"a", required_argument, nullptr, 6},
        {"b", required_argument, nullptr, 7},
        {"c", required_argument, nullptr, 8},
        {"prefix", required_argument, nullptr, 9},
        {"help", no_argument, nullptr, 'h'},
        {nullptr, no_argument, nullptr, 0}
    };

    while (true) {
        const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);
        if (-1 == opt)
            break;

        switch (opt) {
            case 1: params.x0 = std::stod(optarg); break;
            case 2: params.y0 = std::stod(optarg); break;
            case 3: params.z0 = std::stod(optarg); break;
            case 4: params.S = std::stod(optarg); break;
            case 5: params.T = std::stod(optarg); break;
            case 6: params.a = std::stod(optarg); break;
            case 7: params.b = std::stod(optarg); break;
            case 8: params.c = std::stod(optarg); break;
            case 9: params.prefix = optarg; break;
            case 'h':
                print_help();
                return false;
            case '?': // Unrecognized option
            default:
                print_help();
                return false;
        }
    }
    return true;
}

int main(int argc, char** argv) {
    RoesslerParams params;

    if (!parse_args(argc, argv, params)) {
        return 1;
    }

    try {
        std::cout << "Generating Roessler system...\n";
        generate_roessler_data(params);
        std::cout << "Data written to " << params.prefix << ".dat\n";
        std::cout << "Run 'gnuplot " << params.prefix << ".gp' to manually generate image.\n";
        std::cout << "Image generated at " << params.prefix << ".png (if gnuplot is available)\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}

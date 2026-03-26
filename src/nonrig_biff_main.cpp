#include "biffurcation.h"
#include <iostream>
#include <string>
#include <vector>
#include <getopt.h>

void print_help() {
    std::cout << "Roessler Bifurcation Diagram Generator\n";
    std::cout << "Usage: ./nonrig-biff [options]\n";
    std::cout << "Options:\n";
    std::cout << "  --x0=<val>      Initial x value (default: 0.0)\n";
    std::cout << "  --y0=<val>      Initial y value (default: -5.0)\n";
    std::cout << "  --z0=<val>      Initial z value (default: 0.1)\n";
    std::cout << "  --a=<val>       Parameter 'a' (default: 0.2)\n";
    std::cout << "  --b=<val>       Parameter 'b' (default: 0.2)\n";
    std::cout << "  --c_min=<val>   Minimum value of 'c' (default: 2.0)\n";
    std::cout << "  --c_max=<val>   Maximum value of 'c' (default: 6.0)\n";
    std::cout << "  --S=<val>       Discard trajectory length / number of iterations (default: 100)\n";
    std::cout << "  --n=<val>       Number of points to plot per 'c' value (default: 200)\n";
    std::cout << "  --prefix=<val>  Prefix for output files (default: biff)\n";
    std::cout << "  --help          Print this help message\n";
}

bool parse_args(int argc, char** argv, BiffurcationParams& params) {
    const char* const short_opts = "h";
    const option long_opts[] = {
        {"x0", required_argument, nullptr, 1},
        {"y0", required_argument, nullptr, 2},
        {"z0", required_argument, nullptr, 3},
        {"a", required_argument, nullptr, 4},
        {"b", required_argument, nullptr, 5},
        {"c_min", required_argument, nullptr, 6},
        {"c_max", required_argument, nullptr, 7},
        {"S", required_argument, nullptr, 8},
        {"n", required_argument, nullptr, 9},
        {"prefix", required_argument, nullptr, 10},
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
            case 4: params.a = std::stod(optarg); break;
            case 5: params.b = std::stod(optarg); break;
            case 6: params.c_min = std::stod(optarg); break;
            case 7: params.c_max = std::stod(optarg); break;
            case 8: params.S = std::stoi(optarg); break;
            case 9: params.n = std::stoi(optarg); break;
            case 10: params.prefix = optarg; break;
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
    BiffurcationParams params;

    if (!parse_args(argc, argv, params)) {
        return 1;
    }

    try {
        std::cout << "Generating Roessler bifurcation diagram...\n";
        generate_biffurcation_diagram(params);
        std::cout << "Data written to " << params.prefix << ".dat\n";
        std::cout << "Run 'gnuplot " << params.prefix << ".gp' to manually generate image.\n";
        std::cout << "Image generated at " << params.prefix << ".png (if gnuplot is available)\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}

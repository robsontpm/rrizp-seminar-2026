#include "roessler.h"
#include "capd/capdlib.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>

using namespace capd;

void generate_roessler_data(const RoesslerParams& params) {
    // Define Roessler vector field using DMap
    // dx/dt = -y - z
    // dy/dt = x + a*y
    // dz/dt = b + z*(x - c)
    std::stringstream ss;
    ss << "par: a, b, c;\n";
    ss << "var: x, y, z;\n";
    ss << "fun: \n";
    ss << " -y - z, \n";
    ss << " x + a*y, \n";
    ss << " b + z*(x - c); \n";

    DMap f(ss.str());
    f.setParameter("a", params.a);
    f.setParameter("b", params.b);
    f.setParameter("c", params.c);

    // Initial point
    DVector pt(3);
    pt[0] = params.x0;
    pt[1] = params.y0;
    pt[2] = params.z0;

    // Use DOdeSolver
    int order = 20;
    DOdeSolver solver(f, order);

    double t = 0;
    double step = 0.01;
    solver.setStep(step);

    try {
        // Discard initial trajectory S
        while(t < params.S) {
            pt = solver(step, pt);
            t += step;
        }

        // Generate output data
        std::ofstream out(params.prefix + ".dat");
        if (!out) {
            throw std::runtime_error("generate_roessler_data(): Failed to open output data file.");
        }

        t = 0;
        while(t < params.T) {
            out << pt[0] << " " << pt[1] << " " << pt[2] << "\n";
            pt = solver(step, pt);
            t += step;
        }
        out.close();

        // Generate gnuplot script
        std::ofstream gp(params.prefix + ".gp");
        if (!gp) {
            throw std::runtime_error("generate_roessler_data(): Failed to open output script file.");
        }

        gp << "set terminal png size 800,600\n";
        gp << "set output '" << params.prefix << ".png'\n";
        gp << "splot '" << params.prefix << ".dat' with lines title 'Roessler Attractor'\n";
        gp.close();

        // Run gnuplot to generate the image
        std::string command = "gnuplot " + params.prefix + ".gp";
        int ret = std::system(command.c_str());
        if (ret != 0) {
            std::cerr << "generate_roessler_data(): Warning: gnuplot failed with code " << ret << "\n";
        }
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("generate_roessler_data(): Integration failed: ") + e.what());
    }
}

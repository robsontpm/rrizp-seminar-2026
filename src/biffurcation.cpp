#include "biffurcation.h"
#include "capd/capdlib.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>

using namespace capd;

void generate_biffurcation_diagram(const BiffurcationParams& params) {
    if (params.c_min > params.c_max) {
        throw std::runtime_error("generate_biffurcation_diagram(): Invalid range: c_min must be less than or equal to c_max.");
    }

    // Sanitize prefix to prevent OS command injection
    for (char c : params.prefix) {
        if (!std::isalnum(c) && c != '_' && c != '-') {
            throw std::runtime_error("generate_biffurcation_diagram(): Invalid prefix. Only alphanumeric characters, dashes, and underscores are allowed.");
        }
    }

    // We will evaluate at 500 points across the c parameter range
    int c_steps = 500;

    try {
        std::ofstream out(params.prefix + ".dat");
        if (!out) {
            throw std::runtime_error("generate_biffurcation_diagram(): Failed to open output data file.");
        }

        // Define Roessler vector field using DMap
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

        int order = 20;
        double step = 0.01;

        // Using a section y = 0
        DCoordinateSection sec(3, 1);

        for (int i = 0; i <= c_steps; ++i) {
            double c = params.c_min;
            if (c_steps > 0) {
                c += (params.c_max - params.c_min) * i / c_steps;
            }

            f.setParameter("c", c);

            DOdeSolver solver(f, order);
            solver.setStep(step);

            DPoincareMap pmap(solver, sec);

            DVector pt(3);
            pt[0] = params.x0;
            pt[1] = params.y0;
            pt[2] = params.z0;

            try {
                // Discard transient
                for (int j = 0; j < params.S; ++j) {
                    pt = pmap(pt);
                }

                // Record diagram points
                for (int j = 0; j < params.n; ++j) {
                    pt = pmap(pt);
                    out << c << " " << pt[0] << "\n";
                }
            } catch (const std::exception& e) {
                // If the integration fails for a specific parameter c, we print a warning and continue
                std::cerr << "generate_biffurcation_diagram(): Warning: integration failed for c=" << c << ": " << e.what() << "\n";
            }
        }

        out.close();

        // Generate gnuplot script
        std::ofstream gp(params.prefix + ".gp");
        if (!gp) {
            throw std::runtime_error("generate_biffurcation_diagram(): Failed to open output script file.");
        }

        gp << "set terminal png size 800,600\n";
        gp << "set output '" << params.prefix << ".png'\n";
        gp << "set xlabel 'c'\n";
        gp << "set ylabel 'x'\n";
        gp << "plot '" << params.prefix << ".dat' with dots title 'Roessler Bifurcation Diagram'\n";
        gp.close();

        // Run gnuplot to generate the image
        std::string command = "gnuplot " + params.prefix + ".gp";
        int ret = std::system(command.c_str());
        if (ret != 0) {
            std::cerr << "generate_biffurcation_diagram(): Warning: gnuplot failed with code " << ret << "\n";
        }
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("generate_biffurcation_diagram(): ") + e.what());
    }
}

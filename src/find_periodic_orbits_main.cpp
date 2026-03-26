#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <getopt.h>

#include "capd/capdlib.h"

using namespace capd;
using namespace std;

struct OrbitParams {
    double a = 0.2;
    double b = 0.2;
    double c = 2.5;
    double x0 = 5.0;
    double y0 = 0.0;
    double z0 = 0.0;
    int iter = 100;
    int period = 1;
};

OrbitParams parse_arguments(int argc, char* argv[]) {
    OrbitParams params;
    static struct option long_options[] = {
        {"a", required_argument, 0, 'a'},
        {"b", required_argument, 0, 'b'},
        {"c", required_argument, 0, 'c'},
        {"x0", required_argument, 0, 'x'},
        {"y0", required_argument, 0, 'y'},
        {"z0", required_argument, 0, 'z'},
        {"iter", required_argument, 0, 'i'},
        {"period", required_argument, 0, 'p'},
        {0, 0, 0, 0}
    };

    int option_index = 0;
    int c_opt;

    while ((c_opt = getopt_long(argc, argv, "a:b:c:x:y:z:i:p:", long_options, &option_index)) != -1) {
        switch (c_opt) {
            case 'a': params.a = std::stod(optarg); break;
            case 'b': params.b = std::stod(optarg); break;
            case 'c': params.c = std::stod(optarg); break;
            case 'x': params.x0 = std::stod(optarg); break;
            case 'y': params.y0 = std::stod(optarg); break;
            case 'z': params.z0 = std::stod(optarg); break;
            case 'i': params.iter = std::stoi(optarg); break;
            case 'p': params.period = std::stoi(optarg); break;
            default:
                throw std::runtime_error("Invalid argument.");
        }
    }
    return params;
}

int main(int argc, char* argv[]) {
    try {
        OrbitParams params = parse_arguments(argc, argv);
        cout.precision(17);

        DMap vectorField("par:a,b,c;var:x,y,z;fun:-(y+z),x+a*y,b+z*(x-c);");
        vectorField.setParameter("a", params.a);
        vectorField.setParameter("b", params.b);
        vectorField.setParameter("c", params.c);

        DOdeSolver solver(vectorField, 20);
        solver.setStep(0.01);

        // Cross section y = 0 from minus to plus
        DCoordinateSection section(3, 1);
        DPoincareMap pm(solver, section, poincare::MinusPlus);

        double data[] = {params.x0, params.y0, params.z0};
        DVector u(3, data);

        // We will store the result here
        DVector P = u;

        cout << "--- Starting Iterative Search (Transient) ---\n";
        for (int i = 0; i < params.iter; ++i) {
            DVector next_P = P;
            for (int k = 0; k < params.period; ++k) {
                next_P = pm(next_P);
            }
            if (euclNorm(next_P - P) < 1e-8) {
                P = next_P;
                cout << "Iterative search converged at iteration " << i << ".\n";
                break;
            }
            P = next_P;
        }
        cout << "Iterative Point: " << P << "\n";

        cout << "\n--- Starting Newton's Method ---\n";
        DMatrix I(3, 3);
        I[0][0] = 1; I[1][1] = 1; I[2][2] = 1;

        for (int i = 0; i < 20; ++i) {
            DVector P_k = P;
            DMatrix DP_k = I;

            for (int k = 0; k < params.period; ++k) {
                DMatrix monodromy(3, 3);
                double retTime = 0.0;
                DVector P_next = pm(P_k, monodromy, retTime);
                DMatrix DP_step = pm.computeDP(P_next, monodromy, retTime);

                DP_k = DP_step * DP_k;
                P_k = P_next;
            }

            DVector F = P_k - P;

            if (euclNorm(F) < 1e-12) {
                cout << "Newton's method converged at iteration " << i << ".\n";
                break;
            }

            DMatrix DF = DP_k - I;

            // To compute Newton step we solve DF * dP = -F
            // Since DPoincareMap usually returns DP with row corresponding to vector field equal to 0,
            // DF will have a -1 in that diagonal entry. We can just use standard capd matrix solver.
            DVector dP = capd::matrixAlgorithms::gauss(DF, -F);

            P = P + dP;
        }

        cout << "Refined Periodic Point: " << P << "\n";

        // Stability Analysis
        cout << "\n--- Stability Analysis ---\n";
        DVector P_k = P;
        DMatrix DP_k = I;
        for (int k = 0; k < params.period; ++k) {
            DMatrix monodromy(3, 3);
            double retTime = 0.0;
            DVector P_next = pm(P_k, monodromy, retTime);
            DMatrix DP_step = pm.computeDP(P_next, monodromy, retTime);
            DP_k = DP_step * DP_k;
            P_k = P_next;
        }

        DVector rV(3), iV(3);
        capd::alglib::computeEigenvalues(DP_k, rV, iV);
        cout << "Eigenvalues of DP^" << params.period << ":\n";
        bool stable = true;
        for (int i = 0; i < 3; ++i) {
            double mod = std::sqrt(rV[i]*rV[i] + iV[i]*iV[i]);
            cout << "  lambda_" << i << " = " << rV[i] << " + i * " << iV[i] << "  (modulus = " << mod << ")\n";
            // Ignore the trivial eigenvalue 0 (which corresponds to flow direction)
            if (mod > 1e-6 && mod >= 1.0) {
                stable = false;
            }
        }
        cout << "Orbit is " << (stable ? "STABLE" : "UNSTABLE") << ".\n";


    } catch (const exception& e) {
        cerr << "Exception caught: " << e.what() << "\n";
        return 1;
    }
    return 0;
}

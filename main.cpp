#include <iostream>
#include <Eigen/Dense>
#include "solver.h"

using namespace std;
using namespace Eigen;

int main()
{
    MatrixXd A(6,4);

    A <<
    1.0, 0.2, 0.0, 0.0,
    0.8, 1.0, 0.2, 0.0,
    0.3, 0.7, 1.0, 0.2,
    0.0, 0.2, 0.7, 1.0,
    0.0, 0.0, 0.2, 0.8,
    0.0, 0.0, 0.0, 1.0;

    VectorXd wavefront(6);

    wavefront <<
    0.5,
    0.8,
    1.0,
    0.7,
    0.2,
    0.1;

    VectorXd commands =
        computeActuatorCommands(A, wavefront);

    cout << "Actuator Commands:\n";
    cout << commands << endl;

    VectorXd correction = A * commands;

    cout << "\nMirror Correction:\n";
    cout << correction << endl;

    VectorXd residual =
        correction + wavefront;

    cout << "\nResidual Error:\n";
    cout << residual << endl;

    cout << "\nResidual Norm: "
         << residual.norm()
         << endl;

    return 0;
}
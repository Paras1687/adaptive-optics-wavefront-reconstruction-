#include "solver.h"

using namespace Eigen;

VectorXd computeActuatorCommands(
    const MatrixXd& influenceMatrix,
    const VectorXd& wavefront)
{
    VectorXd commands =
        influenceMatrix.bdcSvd(
            ComputeThinU | ComputeThinV)
        .solve(-wavefront);

    return commands;
}
#ifndef SOLVER_H
#define SOLVER_H

#include <Eigen/Dense>

Eigen::VectorXd computeActuatorCommands(
    const Eigen::MatrixXd& influenceMatrix,
    const Eigen::VectorXd& wavefront);

#endif
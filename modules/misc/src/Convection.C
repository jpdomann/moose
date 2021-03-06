/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#include "Convection.h"

/**
 * This function defines the valid parameters for
 * this Kernel and their default values
 */
template<>
InputParameters validParams<Convection>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<Real>("x", "Component of velocity in the x direction");
  params.addRequiredParam<Real>("y", "Component of velocity in the y direction");
  params.addParam<Real>("z", 0.0, "Component of velocity in the z direction");
  return params;
}

Convection::Convection(const std::string & name, InputParameters parameters)
  // You must call the constructor of the base class first
  // The "true" here specifies that this Kernel is to be integrated
  // over the domain.
  :Kernel(name, parameters),

   // This is the "Intialization List" it sets the values of class variables
   // Here we are grabbing the values of Parameters to use for a velocity vector
   _x(getParam<Real>("x")),
   _y(getParam<Real>("y")),
   _z(getParam<Real>("z"))
{
  // Build a velocity vector to use in the residual / jacobian computations.
  // We do this here so that it's only done once and then we just reuse it.
  // Note that RealVectorValues ALWAYS have 3 components... even when running in
  // 2D or 1D.  This makes the code simpler...
  velocity(0)=_x;
  velocity(1)=_y;
  velocity(2)=_z;
}

Real Convection::computeQpResidual()
{
  /*
  Moose::out<<"phi : "<<_phi[_i][_qp]<<std::endl;
  Moose::out<<"test: "<<_test[_i][_qp]<<std::endl;
  Moose::out<<"res : "<<(velocity*_grad_u[_qp])<<std::endl;
  Moose::out<<"all : "<<_test[_i][_qp]*(velocity*_grad_u[_qp])<<std::endl;
  */

  // velocity * _grad_u[_qp] is actually doing a dot product
  return _test[_i][_qp]*(velocity*_grad_u[_qp]);
}

Real Convection::computeQpJacobian()
{
  // the partial derivative of _grad_u is just _dphi[_j]
  return _test[_i][_qp]*(velocity*_grad_phi[_j][_qp]);
}

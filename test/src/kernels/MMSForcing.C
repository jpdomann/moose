/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/
#include "MMSForcing.h"

template<>
InputParameters validParams<MMSForcing>()
{
  InputParameters params = validParams<Kernel>();
  return params;
}

MMSForcing::MMSForcing(const std::string & name, InputParameters parameters) :
    Kernel(name, parameters),
    _mesh_dimension(_mesh.dimension())
{
}

Real
MMSForcing::computeQpResidual()
{
  Real a = libMesh::pi;
  Real x = _q_point[_qp](0);
  Real y = _q_point[_qp](1);
  Real t =_t;

  if (_mesh_dimension == 3)
  {
    Real z = _q_point[_qp](2);
    Real f= std::cos(a*x*y*z*t)*(a*x*y*z - a*y*z*t + 2.0*a*x*z*t - 3.0*a*x*y*t)+(std::sin(a*x*y*z*t)*std::sin(a*x*y*z*t)*std::sin(a*x*y*z*t))*(a*a*y*y*z*z*t*t + a*a*x*x*z*z*t*t + a*a*x*x*y*y*t*t) + ((std::cos(a*x*y*z*t)*std::cos(a*x*y*z*t)))*std::sin(a*x*y*z*t)*(-2.0*a*a*y*y*z*z*t*t - 2.0*a*a*x*x*z*z*t*t - 2.0*a*a*x*x*y*y*t*t) + ((std::sin(a*x*y*z*t)*std::sin(a*x*y*z*t)))*(-2.0*a*a*y*y*z*z*t*t - 2.0*a*a*x*x*z*z*t*t - 2.0*a*a*x*x*y*y*t*t + 2.0) + ((std::cos(a*x*y*z*t)*cos(a*x*y*z*t)))*(2.0*a*a*y*y*z*z*t*t + 2.0*a*a*x*x*z*z*t*t + 2.0*a*a*x*x*y*y*t*t) + std::sin(a*x*y*z*t)*(2.0*a*a*y*y*z*z*t*t + 2.0*a*a*x*x*z*z*t*t + 2.0*a*a*x*x*y*y*t*t);
    return  -(_test[_i][_qp] * f);
  }
  else
  {
    Real z = 1.0;
    Real f= std::cos(a*x*y*z*t)*(a*x*y*z - a*y*z*t + 2.0*a*x*z*t)+(std::sin(a*x*y*z*t)*std::sin(a*x*y*z*t)*std::sin(a*x*y*z*t))*(a*a*y*y*z*z*t*t + a*a*x*x*z*z*t*t) + ((std::cos(a*x*y*z*t)*std::cos(a*x*y*z*t)))*std::sin(a*x*y*z*t)*(-2.0*a*a*y*y*z*z*t*t - 2.0*a*a*x*x*z*z*t*t) + ((std::sin(a*x*y*z*t)*std::sin(a*x*y*z*t)))*(-2.0*a*a*y*y*z*z*t*t - 2.0*a*a*x*x*z*z*t*t + 2.0) + ((std::cos(a*x*y*z*t)*cos(a*x*y*z*t)))*(2.0*a*a*y*y*z*z*t*t + 2.0*a*a*x*x*z*z*t*t) + std::sin(a*x*y*z*t)*(2.0*a*a*y*y*z*z*t*t + 2.0*a*a*x*x*z*z*t*t);
    return  -(_test[_i][_qp] * f);
  }
}

Real
MMSForcing::computeQpJacobian()
{
  return 0;
}

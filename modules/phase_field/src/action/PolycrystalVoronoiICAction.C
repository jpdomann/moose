/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#include "PolycrystalVoronoiICAction.h"
#include "Factory.h"
#include "Parser.h"
#include "FEProblem.h"

#include <sstream>
#include <stdexcept>

// libMesh includes
#include "libmesh/libmesh.h"
#include "libmesh/exodusII_io.h"
#include "libmesh/equation_systems.h"
#include "libmesh/nonlinear_implicit_system.h"
#include "libmesh/explicit_system.h"
#include "libmesh/string_to_enum.h"

const Real PolycrystalVoronoiICAction::_abs_zero_tol = 1e-12;

template<>
InputParameters validParams<PolycrystalVoronoiICAction>()
{
  InputParameters params = validParams<Action>();
  params.addRequiredParam<unsigned int>("op_num", "number of order parameters to create");
  params.addRequiredParam<unsigned int>("grain_num", "number of grains to create, if it is going to greater than op_num");
  params.addRequiredParam<std::string>("var_name_base", "specifies the base name of the variables");
  params.addParam<unsigned int>("rand_seed", 12444, "The random seed");

  params.addParam<bool>("cody_test", false, "Use set grain center points for Cody's test. Grain num MUST equal 10");

  params.addParam<bool>("columnar_3D", false, "3D microstructure will be columnar in the z-direction?");

  return params;
}

PolycrystalVoronoiICAction::PolycrystalVoronoiICAction(const std::string & name, InputParameters params) :
    Action(name, params),
    _op_num(getParam<unsigned int>("op_num")),
    _grain_num(getParam<unsigned int>("grain_num")),
    _var_name_base(getParam<std::string>("var_name_base"))
{
}

void
PolycrystalVoronoiICAction::act()
{
#ifdef DEBUG
  Moose::err << "Inside the PolycrystalVoronoiICAction Object\n";
#endif

  // Loop through the number of order parameters
  for (unsigned int op = 0; op < _op_num; op++)
  {
    //Create variable names
    std::string var_name = _var_name_base;
    std::stringstream out;
    out << op;
    var_name.append(out.str());

    //Set parameters for BoundingBoxIC
    InputParameters poly_params = _factory.getValidParams("PolycrystalReducedIC");
    poly_params.set<VariableName>("variable") = var_name;
    poly_params.set<unsigned int>("op_num") = _op_num;
    poly_params.set<unsigned int>("grain_num") = _grain_num;
    poly_params.set<unsigned int>("op_index") = op;
    poly_params.set<unsigned int>("rand_seed") = getParam<unsigned int>("rand_seed");
    poly_params.set<bool>("cody_test") = getParam<bool>("cody_test");
    poly_params.set<bool>("columnar_3D") = getParam<bool>("columnar_3D");

    //Add initial condition
    _problem->addInitialCondition("PolycrystalReducedIC", "InitialCondition", poly_params);
  }
}

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

#include "PlotFunction.h"
#include "Function.h"
#include "SubProblem.h"

template<>
InputParameters validParams<PlotFunction>()
{
  InputParameters params = validParams<GeneralPostprocessor>();
  params.addRequiredParam<FunctionName>("function", "Name of the function to plot (i.e. sample)");
  params.addParam<Point>("point", "A point in space to be given to the function");
  params.addParam<Real>("scale_factor", 1, "A scale factor to be applied to the function");
  return params;
}

PlotFunction::PlotFunction(const std::string & name, InputParameters parameters) :
    GeneralPostprocessor(name, parameters),
    _func(getFunction("function")),
    _point(isParamValid("point") ? getParam<Point>("point") : Point()),
    _scale_factor(getParam<Real>("scale_factor"))
{
}

PlotFunction::~PlotFunction()
{
}

void
PlotFunction::initialize()
{
}

void
PlotFunction::execute()
{
}

Real
PlotFunction::getValue()
{
  return _scale_factor * _func.value(_t, _point);
}

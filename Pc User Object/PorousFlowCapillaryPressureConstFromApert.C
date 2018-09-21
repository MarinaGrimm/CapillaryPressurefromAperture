//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*


#include "PorousFlowCapillaryPressureConstFromApert.h"
#include "libmesh/quadrature.h"

//#include "MooseMesh.h"
//#include "libmesh/mesh_tools.h"

registerMooseObject("MooseApp", PorousFlowCapillaryPressureConstFromApert);

template <>
InputParameters
validParams<PorousFlowCapillaryPressureConstFromApert>()
{
  InputParameters params = validParams<PorousFlowCapillaryPressure>();
     params.addParam<FunctionName>(
            "function", 1.0, "This is the ImageMinMax function, that gives the aperture value");
  params.addParam<Real>( "int_tension", "Representative value of the interfacial tension of the two fluids (N/m)");
  params.addClassDescription("Capillary pressure calculate with Young-Laplace formula");
    
  return params;
}

// You must call the constructor of the base class first

PorousFlowCapillaryPressureConstFromApert::PorousFlowCapillaryPressureConstFromApert(
    const InputParameters & parameters)
:   PorousFlowCapillaryPressure(parameters),
  _func(getFunction("function")), //aperture values associated with _func
  _int_tension(getParam<Real>("int_tension"))
 // Real _cap_press;

{
  // Set _log_ext to false as the logarithmic extension is not necessary in this object
  _log_ext = false;
}

Real
PorousFlowCapillaryPressureConstFromApert::effectiveSaturation(Real /*pc*/, unsigned /*qp*/) const
{
    return 1.0;
}


Real
PorousFlowCapillaryPressureConstFromApert::dEffectiveSaturation(Real /*pc*/, unsigned /*qp*/) const
{
    return 0.0;
}

Real
PorousFlowCapillaryPressureConstFromApert::d2EffectiveSaturation(Real /*pc*/, unsigned /*qp*/) const
{
    return 0.0;
}


Real
PorousFlowCapillaryPressureConstFromApert::capillaryPressureCurve(Real /*saturation*/, unsigned /*qp*/) const
{
  return _int_tension/_func.value(_t, _q_point[_qp]);
  //  return 0.72/_func.value(_t, _q_point[_qp]);
}

Real
PorousFlowCapillaryPressureConstFromApert::dCapillaryPressureCurve(Real /*saturation*/,
                                                          unsigned /*qp*/) const
{
    return 0.0;
}

Real
PorousFlowCapillaryPressureConstFromApert::d2CapillaryPressureCurve(Real /*saturation*/,
                                                           unsigned /*qp*/) const
{
    return 0.0;
}

Real
PorousFlowCapillaryPressureConstFromApert::value(Real /*t*/, const Point & /*p*/) const
{
    return 0.0;
}

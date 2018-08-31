//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*


#include "PorousFlowCapillaryPressureConstFromApert.h"
//#include "MooseMesh.h"

//#include "libmesh/mesh_tools.h"

/**
 * This function defines the valid parameters for
 * this Kernel and their default values
 */

registerMooseObject("SaintBernardApp", PorousFlowCapillaryPressureConstFromApert);

template <>
InputParameters
validParams<PorousFlowCapillaryPressureConstFromApert>()
{
  InputParameters params = validParams<PorousFlowCapillaryPressure>();
    params += validParams<Function>();
    params.addRequiredParam<FunctionName>(
            "function", "This is the ImageMinMax function, that gives the aperture value");
   params.addRequiredParam<Real>(
            "int_tension", "Representative value of the interfacial tension of the two fluids (N/m)");
//   params.addRequiredCoupledVar("aperture", "Aperture of the fracture");
    
  params.addClassDescription("Capillary pressure calculate with Young-Laplace formula");
    
  return params;
}

// You must call the constructor of the base class first

PorousFlowCapillaryPressureConstFromApert::PorousFlowCapillaryPressureConstFromApert(const InputParameters & parameters) :

  PorousFlowCapillaryPressure(parameters),
  Function(parameters),
 // FunctionInterface(this),
  _func(getFunction("function")), //aperture values associated with _func
  _int_tension(getParam<Real>("int_tension"))
  Real _cap_press;

{
  // Set _log_ext to false as the logarithmic extension is not necessary in this object
  _log_ext = false;
}

Real PorousFlowCapillaryPressureConstFromApert::effectiveSaturation(Real /*pc*/) const { return 1.0; }

Real PorousFlowCapillaryPressureConstFromApert::dEffectiveSaturation(Real /*pc*/) const { return 0.0; }

Real PorousFlowCapillaryPressureConstFromApert::d2EffectiveSaturation(Real /*pc*/) const { return 0.0; }

//Real PorousFlowCapillaryPressureConstFromApert::value(Real, const Point &)

//{
 //  Real cap_press;
 //   _cap_press = _int_tension/_func.value(_t, _q_point);
    
//}

//Real PorousFlowCapillaryPressureConstFromApert::capillaryPressureCurve(Real /*saturation*/, Real t, const Point & p) const
Real PorousFlowCapillaryPressureConstFromApert::capillaryPressureCurve(Real /*saturation*/) const

{
 //   return _cap_press;
    return _int_tension/_func.value(_t, _q_point);


}

Real PorousFlowCapillaryPressureConstFromApert::dCapillaryPressureCurve(Real /*saturation*/) const
{
  return 0.0;
}

Real PorousFlowCapillaryPressureConstFromApert::d2CapillaryPressureCurve(Real /*saturation*/) const
{
  return 0.0;
}

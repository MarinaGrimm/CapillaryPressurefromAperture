/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "PorousFlowCapillaryPressureMaterial.h"

registerMooseObject("MooseApp", PorousFlowCapillaryPressureMaterial);

template <>
InputParameters
validParams<PorousFlowCapillaryPressureMaterial>()
{
  InputParameters params = validParams<PorousFlowMaterialBase>();
  params.addRequiredCoupledVar("capillarypressure", "The capillary pressure calculated from aperture of the fracture");
    // params.addRequiredParam<Real>("capillarypressure", "The capillary pressure calculated from aperture of the fracture");
  params.addClassDescription(
      "This Material captures the calculated value of capillary pressure per element, given a fracture aperture field.");
  return params;
}

PorousFlowCapillaryPressureMaterial::PorousFlowCapillaryPressureMaterial(
    const InputParameters & parameters)
  : PorousFlowMaterialBase(parameters),
   // _capillarypressure(coupledValue("capillarypressure"))
    _capillarypressure_qp(declareProperty<Real>("capillarypressure")),
 //   _capillarypressure(coupledValue("capillarypressure"))
   _capillarypressure(getParam<Real>("capillarypressure"))

{
     //   if (1 < _capillarypressure)
     //       mooseError("The code is calculating capillary pressure as negative, whereas Young-Laplace formaula does not allow this option.");
}

void
PorousFlowCapillaryPressureMaterial::computeQpProperties()
{

  _capillarypressure_qp[_qp] = _capillarypressure;


}

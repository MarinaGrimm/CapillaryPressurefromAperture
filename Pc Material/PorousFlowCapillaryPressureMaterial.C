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
  InputParameters params = validParams<Material>();
//The one that compiled before:
    // params.addRequiredCoupledVar("capillarypressure", "The capillary pressure calculated from aperture of the fracture");
    // params.addRequiredParam<Real>("capillarypressure", "The capillary pressure calculated from aperture of the fracture");
    params.addRequiredParam<UserObjectName>("capillarypressure",
                                            "Name of the UserObject defining the capillary pressure");
  params.addClassDescription(
      "This Material captures the calculated value of capillary pressure per element, given a fracture aperture field.");
  return params;
}

PorousFlowCapillaryPressureMaterial::PorousFlowCapillaryPressureMaterial(
    const InputParameters & parameters)
  : Material(parameters),
   // _capillarypressure(coupledValue("capillarypressure"))
    _capillarypressure_mat(declareProperty<Real>("capillarypressure")),
 //   _capillarypressure(coupledValue("capillarypressure"))
//The one that compiled ok:   _capillarypressure(getParam<Real>("capillarypressure"))
    _pc_value(getUserObject<PorousFlowCapillaryPressureConstFromApert>("capillarypressure"))

{
     //   if (1 < _capillarypressure)
     //       mooseError("The code is calculating capillary pressure as negative, whereas Young-Laplace formaula does not allow this option.");
}

void
PorousFlowCapillaryPressureMaterial::computeQpProperties()
{

 //   _capillarypressure_mat[_qp] = _pc_value.averageValue[_qp];
  //  _capillarypressure_mat[_qp] = _pc_value.value(_t, _q_point[_qp]);
    
   _capillarypressure_mat[_qp] = _pc_value.value(_t, _q_point[_qp]);
 //   _capillarypressure_mat[_qp] = _pc_value.value(_current_elem->subdomain_id());
    
  //    return _int_tension/_func.value(_t, _q_point[_qp]);


}

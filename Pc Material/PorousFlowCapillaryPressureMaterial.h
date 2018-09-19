/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef POROUSFLOWCAPILLARYPRESSUREMATERIAL_H
#define POROUSFLOWCAPILLARYPRESSUREMATERIAL_H

#include "PorousFlowMaterialBase.h"
//#include "PorousFlowDictator.h"

// Forward Declarations
class PorousFlowCapillaryPressureMaterial;

template <>
InputParameters validParams<PorousFlowCapillaryPressureMaterial>();

/**
 * Material to provide permeability calculated from a variable representing a fracture aperture. 
 * This material is primarily designed for use with heterogeneous fracture aperture models
 * where the aperture is provided by an
 * elemental aux variables that do not change.
 * The three diagonal entries corresponding to the x, y, and z directions
 * are assumed to be equal and calculated using the cubic law.
 */
class PorousFlowCapillaryPressureMaterial : public PorousFlowMaterialBase
{
public:
  PorousFlowCapillaryPressureMaterial(const InputParameters & parameters);

protected:
  void computeQpProperties() override;
    
/// Quadpoint Capillary Pressure
 // const MaterialProperty<Real> & _capillarypressure_qp;
    MaterialProperty<Real> & _capillarypressure_qp;

    
 /// Pc value
  // const VariableValue & _capillarypressure;
   Real _capillarypressure;

    
    /// Old value of capillary pressure
 // const MaterialProperty<Real> & _capillarypressure_old;

  /// Pc value
 // const VariableValue & _capillarypressure_qp;
};

#endif // POROUSFLOWCAPILLARYPRESSUREMATERIAL_H

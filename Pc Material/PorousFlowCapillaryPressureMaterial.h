/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef POROUSFLOWCAPILLARYPRESSUREMATERIAL_H
#define POROUSFLOWCAPILLARYPRESSUREMATERIAL_H

//#include "PorousFlowMaterialBase.h"
#include "Material.h"
#include "PorousFlowCapillaryPressureConstFromApert.h"
//#include "Function.h"
#include "libmesh/mesh_tools.h"


//#include "PorousFlowDictator.h"
// This .h already includes PorousFlowMaterial.h

// Forward Declarations
// class PorousFlowCapillaryPressureConstFromApert;
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
class PorousFlowCapillaryPressureMaterial : public Material
{
public:
  PorousFlowCapillaryPressureMaterial(const InputParameters & parameters);
    
 // virtual Real value(Real t, const Point & p) override;

protected:

    
  //    void buildQpPPSS();
    
    /**
     * Effective saturation of liquid phase
     * @param saturation true saturation
     * @return effective saturation
     */
  //  virtual Real effectiveSaturation(Real saturation) const;
    
//    virtual void initQpStatefulProperties() override;
    virtual void computeQpProperties() override;

private:
    
    /**
     * This is the member reference that will hold the computed values
     * for the Real value property in this class.
     */
     MaterialProperty<Real> & _capillarypressure_mat;

    
    /**
     * A member reference that will hold onto a UserObject
     * of type PorousFlowCapillaryPressureConstFromApert for us to be able to query
     * the Pc value.
     *
     * NOTE: UserObject references are _const_!
     */
    const PorousFlowCapillaryPressureConstFromApert & _pc_value;
    
 //   unsigned int _qp;

};

#endif // POROUSFLOWCAPILLARYPRESSUREMATERIAL_H

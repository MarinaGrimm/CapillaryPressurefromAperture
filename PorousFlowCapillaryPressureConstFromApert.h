//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//*


#ifndef POROUSFLOWCAPILLARYPRESSURECONSTFROMAPERT_H
#define POROUSFLOWCAPILLARYPRESSURECONSTFROMAPERT_H

#include "PorousFlowCapillaryPressure.h"
#include "Function.h"

/**
 * The forward declaration is so that we can declare the validParams() function
 * before we actually define the class... that way the definition isn't lost
 * at the bottom of the file.
*/

// Forward Declarations

class PorousFlowCapillaryPressureConstFromApert;

/**
 * validParams returns the parameters that this Kernel accepts / needs
 * The actual body of the function MUST be in the .C file.
*/

template <>
InputParameters validParams<PorousFlowCapillaryPressureConstFromApert>();

/**
 * Capillary pressure calculated from fracture aperture values Pc = int_tension/b.
 * This object is primarily designed for use with single fracture flows
 * where the components of the capillary pressure value can be
 * calculated from the local aperture of the volume element.
 * The interfacial tension must be given. We are here considering 
 * contact angle of zero degrees and the in-plane curvature radius 
 * as infinite (high spatial correlation length, or R2 infinite).
 */
 
class PorousFlowCapillaryPressureConstFromApert : public PorousFlowCapillaryPressure

{
public:
    
  PorousFlowCapillaryPressureConstFromApert(const InputParameters & parameters);

    virtual Real capillaryPressureCurve(Real saturation, unsigned qp = 0) const override;
    virtual Real dCapillaryPressureCurve(Real saturation, unsigned qp = 0) const override;
    virtual Real d2CapillaryPressureCurve(Real saturation, unsigned qp = 0) const override;

    virtual Real effectiveSaturation(Real pc, unsigned qp = 0) const override;
    virtual Real dEffectiveSaturation(Real pc, unsigned qp = 0) const override;
    virtual Real d2EffectiveSaturation(Real pc, unsigned qp = 0) const override;
    
//  virtual Real value(Real t, const Point & p) override;
    
    
protected:
    
    /// quadrature point index
    unsigned int _qp;

    /// Capillary pressure as a function of aperture (Pa)
    Function & _func;
    Real _int_tension;
    
 //  MooseMesh & _mesh;
 //  The current element pointer (available during execute())
 //  const Elem *& _current_elem;
 //  The current element volume (available during execute())
 //  const Real & _current_elem_volume;
 //  QBase *& _qrule;
 //  const MooseArray<Real> & _JxW;
 //  const MooseArray<Real> & _coord;
 //  void computeQpProperties() override;
 //  active quadrature points
 //  const MooseArray<Point> & _q_point;
 //  Real & _t;

};

#endif // POROUSFLOWCAPILLARYPRESSURECONSTFROMAPERT_H

# Test Brooks-Corey capillary pressure curve by varying saturation over the mesh
# lambda = 2, sat_lr = 0.1, log_extension = false

[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 4
  ny = 4
  xmax = 0.50
  ymax = 1.00
[]

[GlobalParams]
  PorousFlowDictator = dictator
[]

[Variables]
  [./p0]
    initial_condition = 1e6
  [../]
  [./s1]
  [../]
[]

[AuxVariables]
  [./s0aux]
    family = MONOMIAL
    order = CONSTANT
  [../]
  [./s1aux]
    family = MONOMIAL
    order = CONSTANT
  [../]
  [./p0aux]
    family = MONOMIAL
    order = CONSTANT
  [../]
  [./p1aux]
    family = MONOMIAL
    order = CONSTANT
  [../]
  [./aperture]
  order = CONSTANT
  family = MONOMIAL
  [../]
  [./cap_press]
  order = CONSTANT
  family = MONOMIAL
  [../]
[]

[AuxKernels]
  [./s0]
    type = PorousFlowPropertyAux
    property = saturation
    phase = 0
    variable = s0aux
  [../]
  [./s1]
    type = PorousFlowPropertyAux
    property = saturation
    phase = 1
    variable = s1aux
  [../]
  [./p0]
    type = PorousFlowPropertyAux
    property = pressure
    phase = 0
    variable = p0aux
  [../]
  [./p1]
    type = PorousFlowPropertyAux
    property = pressure
    phase = 1
    variable = p1aux
  [../]
[]

[Functions]
  [./s1]
    type = ParsedFunction
    value = x
  [../]
  [./my_image]
  type = ImageFunction
  file = btest_image2.png
  [../]
  [./image2aperture]
  type = ImageMinMaxFunction
  function = my_image
  switch = 1
  min = 1e-10
  max = 1e-3
#the maximum aperture is 1 mm.
  [../]
[]

[ICs]
  [./s1]
    type = FunctionIC
    variable = s1
    function = s1
  [../]
  [./apertureIC]
  type = FunctionIC
  function = image2aperture
  variable = aperture
  [../]
[]

[Kernels]
  [./p0]
    type = Diffusion
    variable = p0
  [../]
  [./s1]
    type = Diffusion
    variable = s1
  [../]
[]

[UserObjects]
  [./dictator]
    type = PorousFlowDictator
    porous_flow_vars = 'p0 s1'
    number_fluid_phases = 2
    number_fluid_components = 2
  [../]
  [./pc]
  type = PorousFlowCapillaryPressureConst
  pc = 0
  [../]
[]

[Materials]
  [./temperature]
    type = PorousFlowTemperature
  [../]
  [./ppss]
    type = PorousFlow2PhasePS
    phase0_porepressure = p0
    phase1_saturation = s1
    capillary_pressure = pc
  [../]
  [./kr0]
    type = PorousFlowRelativePermeabilityVG
    phase = 0
    m = 0.5
  [../]
  [./kr1]
    type = PorousFlowRelativePermeabilityCorey
    phase = 1
    n = 2
  [../]
[]

[Preconditioning]
active = 'preferred'
[./basic]
type = SMP
full = true
petsc_options = '-snes_converged_reason -ksp_diagonal_scale -ksp_diagonal_scale_fix -ksp_gmres_modifiedgramschmidt -snes_linesearch_monitor'
petsc_options_iname = '-ksp_type -pc_type -sub_pc_type -sub_pc_factor_shift_type -pc_asm_overlap'
petsc_options_value = 'gmres asm lu NONZERO 2'
[../]
[./preferred]
type = SMP
full = true
petsc_options_iname = '-pc_type -pc_factor_mat_solver_package'
petsc_options_value = 'lu mumps'
[../]
[]

[VectorPostprocessors]
  [./vpp]
    type = LineValueSampler
    variable = 's0aux s1aux p0aux p1aux'
    start_point = '0 0 0'
    end_point = '1 0 0'
    num_points = 500
    sort_by = id
  [../]
[]

[Executioner]
  type = Steady
  solve_type = NEWTON
  nl_abs_tol = 1e-12
[]

[BCs]
  [./sleft]
    type = DirichletBC
    variable = s1
    value = 0
    boundary = left
  [../]
  [./sright]
    type = DirichletBC
    variable = s1
    value = 1
    boundary = right
  [../]
[]

[Outputs]
  csv = true
  print_linear_residuals = false
  print_perf_log = true
  exodus = true
  execute_on = timestep_end
[]

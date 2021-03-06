[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
[]

[Variables]
  [./u]
  [../]
[]

[Kernels]
  [./diff]
    type = Diffusion
    variable = u
  [../]
  [./td]
    type = TimeDerivative
    variable = u
  [../]
[]

[BCs]
  [./left]
    type = DirichletBC
    variable = u
    boundary = left
    value = 0
  [../]
  [./right]
    type = DirichletBC
    variable = u
    boundary = right
    value = 1
  [../]
[]

[Executioner]
  type = Transient
  num_steps = 10
  dt = 0.2

  # Preconditioned JFNK (default)
  solve_type = 'PJFNK'

  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  output_initial = true
  exodus = true
  print_perf_log = true
[]

[MultiApps]
  [./sub_app]
    positions = '0 0 0  0.5 0.5 0  0.6 0.6 0  0.7 0.7 0'
    type = TransientMultiApp
    input_files = 'phase_field_slave.i'

    # Here we'll attempt to load a different module that's not compiled into this module
    app_type = InvalidApp

    # Here we set an input file specific relative library path instead of using MOOSE_LIBRARY_PATH
    library_path = '../../../../phase_field/lib'
  [../]
[]

//
// Non-Degree Granting Education License -- for use at non-degree
// granting, nonprofit, educational organizations only. Not for
// government, commercial, or other organizational use.
//
// File: Controller_data.cpp
//
// Code generated for Simulink model 'Controller'.
//
// Model version                  : 1.250
// Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
// C/C++ source code generated on : Mon Jul 13 17:57:14 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: 32-bit Generic
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "Controller.h"
#include "Controller_private.h"

// Block parameters (default storage)
ControllerModelClass::P_Controller_T ControllerModelClass::Controller_P = {
  // Mask Parameter: Controller_AutoCompensator_ThresHystMax
  //  Referenced by: '<S1>/Compensator Handling'

  0.05,

  // Mask Parameter: Controller_AutoCompensator_ThresHystMin
  //  Referenced by: '<S1>/Compensator Handling'

  0.005,

  // Mask Parameter: Controller_Compensator_Ki
  //  Referenced by: '<S1>/Compensator'

  1.0,

  // Mask Parameter: Controller_Compensator_Kp
  //  Referenced by: '<S1>/Compensator'

  10.0,

  // Mask Parameter: Controller_Plant_IC
  //  Referenced by:
  //    '<S1>/Reference Plant'
  //    '<S1>/Unit Delay'
  //    '<S1>/Unit Delay2'

  0.0,

  // Mask Parameter: Controller_Plant_Max
  //  Referenced by: '<S1>/Reference Plant'

  100.0,

  // Mask Parameter: Controller_Plant_Min
  //  Referenced by: '<S1>/Reference Plant'

  -100.0,

  // Mask Parameter: EdgeDetector_model
  //  Referenced by: '<S58>/Constant1'

  1.0,

  // Mask Parameter: Controller_compensator_state
  //  Referenced by: '<S1>/Constant1'

  Auto,

  // Mask Parameter: EdgeDetector_ic
  //  Referenced by: '<S58>/Unit Delay'

  0,

  // Expression: 0
  //  Referenced by: '<S1>/Constant'

  0.0,

  // Expression: [1 1]
  //  Referenced by: '<S58>/either edge'

  { 1.0, 1.0 },

  // Expression: [0 1]
  //  Referenced by: '<S58>/neg. edge'

  { 0.0, 1.0 },

  // Expression: [1 0]
  //  Referenced by: '<S58>/pos. edge'

  { 1.0, 0.0 },

  // Computed Parameter: OUT_Y0
  //  Referenced by: '<S59>/OUT'

  0,

  // Computed Parameter: OUT_Y0_d
  //  Referenced by: '<S60>/OUT'

  0,

  // Start of '<S1>/Reference Plant'
  {
    // Computed Parameter: DiscreteIntegrator_gainval
    //  Referenced by: '<S8>/Discrete Integrator'

    0.005
  }
  ,

  // End of '<S1>/Reference Plant'

  // Start of '<S1>/Filter1'
  {
    // Expression: [4.5e-4 9e-4 4.5e-4]
    //  Referenced by: '<S7>/Discrete Filter'

    { 0.00045, 0.0009, 0.00045 },

    // Expression: [1 -1.921 0.9231]
    //  Referenced by: '<S7>/Discrete Filter'

    { 1.0, -1.921, 0.9231 },

    // Expression: 0
    //  Referenced by: '<S7>/Discrete Filter'

    0.0
  }
  ,

  // End of '<S1>/Filter1'

  // Start of '<S1>/Filter'
  {
    // Expression: [4.5e-4 9e-4 4.5e-4]
    //  Referenced by: '<S6>/Discrete Filter'

    { 0.00045, 0.0009, 0.00045 },

    // Expression: [1 -1.921 0.9231]
    //  Referenced by: '<S6>/Discrete Filter'

    { 1.0, -1.921, 0.9231 },

    // Expression: 0
    //  Referenced by: '<S6>/Discrete Filter'

    0.0
  }
  ,

  // End of '<S1>/Filter'

  // Start of '<S1>/Compensator'
  {
    // Mask Parameter: DiscretePIDController_InitialConditionForIntegrator
    //  Referenced by: '<S41>/Integrator'

    0.0,

    // Computed Parameter: Integrator_gainval
    //  Referenced by: '<S41>/Integrator'

    0.005
  }
  // End of '<S1>/Compensator'
};

//
// File trailer for generated code.
//
// [EOF]
//

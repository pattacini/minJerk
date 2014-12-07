//
// File: Controller.h
//
// Code generated for Simulink model 'Controller'.
//
// Model version                  : 1.151
// Simulink Coder version         : 8.7 (R2014b) 08-Sep-2014
// C/C++ source code generated on : Sun Dec 07 10:53:13 2014
//
// Target selection: ert.tlc
// Embedded hardware selection: 32-bit Generic
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_Controller_h_
#define RTW_HEADER_Controller_h_
#include <string.h>
#ifndef Controller_COMMON_INCLUDES_
# define Controller_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 // Controller_COMMON_INCLUDES_

#include "Controller_types.h"
#include "rt_defines.h"

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

// Block signals for system '<S1>/Compensator'
typedef struct {
  real_T Sum;                          // '<S7>/Sum'
} B_Compensator_T;

// Block states (auto storage) for system '<S1>/Compensator'
typedef struct {
  real_T Integrator_DSTATE;            // '<S7>/Integrator'
  int8_T Integrator_PrevResetState;    // '<S7>/Integrator'
} DW_Compensator_T;

// Block signals for system '<S1>/Filter'
typedef struct {
  real_T DiscreteFilter;               // '<S4>/Discrete Filter'
} B_Filter_T;

// Block states (auto storage) for system '<S1>/Filter'
typedef struct {
  real_T DiscreteFilter_states[2];     // '<S4>/Discrete Filter'
} DW_Filter_T;

// Block signals for system '<S1>/Reference Plant'
typedef struct {
  real_T DiscreteIntegrator;           // '<S6>/Discrete Integrator'
} B_ReferencePlant_T;

// Block states (auto storage) for system '<S1>/Reference Plant'
typedef struct {
  real_T DiscreteIntegrator_DSTATE;    // '<S6>/Discrete Integrator'
} DW_ReferencePlant_T;

// Block signals (auto storage)
typedef struct {
  boolean_T RelationalOperator1;       // '<S10>/Relational Operator1'
  boolean_T RelationalOperator1_n;     // '<S9>/Relational Operator1'
  B_ReferencePlant_T ReferencePlant_j; // '<S1>/Reference Plant'
  B_Filter_T Filter1;                  // '<S1>/Filter1'
  B_Filter_T Filter_i;                 // '<S1>/Filter'
  B_Compensator_T Compensator_k;       // '<S1>/Compensator'
} B_Controller_T;

// Block states (auto storage) for system '<Root>'
typedef struct {
  real_T UnitDelay2_DSTATE;            // '<S1>/Unit Delay2'
  real_T UnitDelay_DSTATE;             // '<S1>/Unit Delay'
  boolean_T UnitDelay_DSTATE_e;        // '<S8>/Unit Delay'
  DW_ReferencePlant_T ReferencePlant_j;// '<S1>/Reference Plant'
  DW_Filter_T Filter1;                 // '<S1>/Filter1'
  DW_Filter_T Filter_i;                // '<S1>/Filter'
  DW_Compensator_T Compensator_k;      // '<S1>/Compensator'
} DW_Controller_T;

// Parameters for system: '<S1>/Compensator'
struct P_Compensator_T_ {
  real_T DiscretePIDController_I;      // Mask Parameter: DiscretePIDController_I
                                       //  Referenced by: '<S7>/Integral Gain'

  real_T DiscretePIDController_P;      // Mask Parameter: DiscretePIDController_P
                                       //  Referenced by: '<S7>/Proportional Gain'

  real_T Integrator_gainval;           // Computed Parameter: Integrator_gainval
                                       //  Referenced by: '<S7>/Integrator'

  real_T Integrator_IC;                // Expression: InitialConditionForIntegrator
                                       //  Referenced by: '<S7>/Integrator'

};

// Parameters for system: '<S1>/Filter'
struct P_Filter_T_ {
  real_T DiscreteFilter_NumCoef[3];    // Expression: [4.5e-4 9e-4 4.5e-4]
                                       //  Referenced by: '<S4>/Discrete Filter'

  real_T DiscreteFilter_DenCoef[3];    // Expression: [1 -1.921 0.9231]
                                       //  Referenced by: '<S4>/Discrete Filter'

  real_T DiscreteFilter_InitialStates; // Expression: 0
                                       //  Referenced by: '<S4>/Discrete Filter'

};

// Parameters for system: '<S1>/Reference Plant'
struct P_ReferencePlant_T_ {
  real_T DiscreteIntegrator_gainval;   // Computed Parameter: DiscreteIntegrator_gainval
                                       //  Referenced by: '<S6>/Discrete Integrator'

};

// Parameters (auto storage)
struct P_Controller_T_ {
  real_T Plant_IC;                     // Variable: Plant_IC
                                       //  Referenced by:
                                       //    '<S1>/Unit Delay'
                                       //    '<S1>/Unit Delay2'
                                       //    '<S6>/Discrete Integrator'

  real_T Plant_Max;                    // Variable: Plant_Max
                                       //  Referenced by: '<S6>/Discrete Integrator'

  real_T Plant_Min;                    // Variable: Plant_Min
                                       //  Referenced by: '<S6>/Discrete Integrator'

  real_T EdgeDetector_model;           // Mask Parameter: EdgeDetector_model
                                       //  Referenced by: '<S8>/Constant1'

  boolean_T EdgeDetector_ic;           // Mask Parameter: EdgeDetector_ic
                                       //  Referenced by: '<S8>/Unit Delay'

  real_T Constant_Value;               // Expression: 0
                                       //  Referenced by: '<S1>/Constant'

  real_T eitheredge_Value[2];          // Expression: [1 1]
                                       //  Referenced by: '<S8>/either edge'

  real_T negedge_Value[2];             // Expression: [0 1]
                                       //  Referenced by: '<S8>/neg. edge'

  real_T posedge_Value[2];             // Expression: [1 0]
                                       //  Referenced by: '<S8>/pos. edge'

  boolean_T OUT_Y0;                    // Computed Parameter: OUT_Y0
                                       //  Referenced by: '<S9>/OUT'

  boolean_T OUT_Y0_d;                  // Computed Parameter: OUT_Y0_d
                                       //  Referenced by: '<S10>/OUT'

  P_ReferencePlant_T ReferencePlant_j; // '<S1>/Reference Plant'
  P_Filter_T Filter1;                  // '<S1>/Filter1'
  P_Filter_T Filter_i;                 // '<S1>/Filter'
  P_Compensator_T Compensator_k;       // '<S1>/Compensator'
};

// Real-time Model Data Structure
struct tag_RTM_Controller_T {
  const char_T * volatile errorStatus;

  //
  //  ModelData:
  //  The following substructure contains information regarding
  //  the data used in the model.

  struct {
    B_Controller_T *blockIO;
    P_Controller_T *defaultParam;
    DW_Controller_T *dwork;
  } ModelData;
};

#ifdef __cplusplus

extern "C" {

#endif

#ifdef __cplusplus

}
#endif

#ifdef __cplusplus

extern "C" {

#endif

  // Model entry point functions
  extern void Controller_initialize(RT_MODEL_Controller_T *const Controller_M,
    real_T *Controller_U_reference, boolean_T *Controller_U_enable_compensation,
    real_T *Controller_U_plant_output, real_T *Controller_Y_controller_output,
    real_T *Controller_Y_controller_reference, real_T
    *Controller_Y_plant_reference);
  extern void Controller_step(RT_MODEL_Controller_T *const Controller_M, real_T
    Controller_U_reference, boolean_T Controller_U_enable_compensation, real_T
    Controller_U_plant_output, real_T *Controller_Y_controller_output, real_T
    *Controller_Y_controller_reference, real_T *Controller_Y_plant_reference);
  extern void Controller_terminate(RT_MODEL_Controller_T *const Controller_M);

#ifdef __cplusplus

}
#endif

//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Note that this particular code originates from a subsystem build,
//  and has its own system numbers different from the parent model.
//  Refer to the system hierarchy for this subsystem below, and use the
//  MATLAB hilite_system command to trace the generated code back
//  to the parent model.  For example,
//
//  hilite_system('minJerk/Controller')    - opens subsystem minJerk/Controller
//  hilite_system('minJerk/Controller/Kp') - opens and selects block Kp
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'minJerk'
//  '<S1>'   : 'minJerk/Controller'
//  '<S2>'   : 'minJerk/Controller/Compensator'
//  '<S3>'   : 'minJerk/Controller/Edge Detector'
//  '<S4>'   : 'minJerk/Controller/Filter'
//  '<S5>'   : 'minJerk/Controller/Filter1'
//  '<S6>'   : 'minJerk/Controller/Reference Plant'
//  '<S7>'   : 'minJerk/Controller/Compensator/Discrete PID Controller'
//  '<S8>'   : 'minJerk/Controller/Edge Detector/Model'
//  '<S9>'   : 'minJerk/Controller/Edge Detector/Model/NEGATIVE Edge'
//  '<S10>'  : 'minJerk/Controller/Edge Detector/Model/POSITIVE Edge'

#endif                                 // RTW_HEADER_Controller_h_

//
// File trailer for generated code.
//
// [EOF]
//

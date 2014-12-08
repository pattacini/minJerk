//
// File: Controller.cpp
//
// Code generated for Simulink model 'Controller'.
//
// Model version                  : 1.154
// Simulink Coder version         : 8.7 (R2014b) 08-Sep-2014
// C/C++ source code generated on : Mon Dec 08 12:32:34 2014
//
// Target selection: ert.tlc
// Embedded hardware selection: 32-bit Generic
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "Controller.h"
#include "Controller_private.h"

// Initial conditions for atomic system: '<S1>/Compensator'
void Compensator_Init(DW_Compensator_T *localDW, P_Compensator_T *localP)
{
  // InitializeConditions for DiscreteIntegrator: '<S7>/Integrator'
  localDW->Integrator_DSTATE = localP->Integrator_IC;
  localDW->Integrator_PrevResetState = 2;
}

// Output and update for atomic system: '<S1>/Compensator'
void Compensator(real_T rtu_e, boolean_T rtu_reset, B_Compensator_T *localB,
                 DW_Compensator_T *localDW, P_Compensator_T *localP,
                 P_Controller_T *Controller_P)
{
  real_T rtb_IntegralGain;
  real_T Integrator;

  // Gain: '<S7>/Integral Gain'
  rtb_IntegralGain = Controller_P->Compensator_Ki * rtu_e;

  // DiscreteIntegrator: '<S7>/Integrator'
  if (rtu_reset && (localDW->Integrator_PrevResetState <= 0)) {
    localDW->Integrator_DSTATE = localP->Integrator_IC;
  }

  Integrator = localP->Integrator_gainval * rtb_IntegralGain +
    localDW->Integrator_DSTATE;

  // End of DiscreteIntegrator: '<S7>/Integrator'

  // Sum: '<S7>/Sum' incorporates:
  //   Gain: '<S7>/Proportional Gain'

  localB->Sum = Controller_P->Compensator_Kp * rtu_e + Integrator;

  // Update for DiscreteIntegrator: '<S7>/Integrator'
  localDW->Integrator_DSTATE = localP->Integrator_gainval * rtb_IntegralGain +
    Integrator;
  if (rtu_reset) {
    localDW->Integrator_PrevResetState = 1;
  } else {
    localDW->Integrator_PrevResetState = 0;
  }

  // End of Update for DiscreteIntegrator: '<S7>/Integrator'
}

//
// Initial conditions for atomic system:
//    '<S1>/Filter'
//    '<S1>/Filter1'
//
void Filter_Init(DW_Filter_T *localDW, P_Filter_T *localP)
{
  // InitializeConditions for DiscreteTransferFcn: '<S4>/Discrete Filter'
  localDW->DiscreteFilter_states[0] = localP->DiscreteFilter_InitialStates;
  localDW->DiscreteFilter_states[1] = localP->DiscreteFilter_InitialStates;
}

//
// Output and update for atomic system:
//    '<S1>/Filter'
//    '<S1>/Filter1'
//
void Filter(real_T rtu_e, B_Filter_T *localB, DW_Filter_T *localDW, P_Filter_T
            *localP)
{
  real_T DiscreteFilter_tmp;

  // DiscreteTransferFcn: '<S4>/Discrete Filter'
  DiscreteFilter_tmp = ((rtu_e - localP->DiscreteFilter_DenCoef[1] *
    localDW->DiscreteFilter_states[0]) - localP->DiscreteFilter_DenCoef[2] *
                        localDW->DiscreteFilter_states[1]) /
    localP->DiscreteFilter_DenCoef[0];
  localB->DiscreteFilter = (localP->DiscreteFilter_NumCoef[0] *
    DiscreteFilter_tmp + localP->DiscreteFilter_NumCoef[1] *
    localDW->DiscreteFilter_states[0]) + localP->DiscreteFilter_NumCoef[2] *
    localDW->DiscreteFilter_states[1];

  // Update for DiscreteTransferFcn: '<S4>/Discrete Filter'
  localDW->DiscreteFilter_states[1] = localDW->DiscreteFilter_states[0];
  localDW->DiscreteFilter_states[0] = DiscreteFilter_tmp;
}

// Initial conditions for atomic system: '<S1>/Reference Plant'
void ReferencePlant_Init(DW_ReferencePlant_T *localDW, P_Controller_T
  *Controller_P)
{
  // InitializeConditions for DiscreteIntegrator: '<S6>/Discrete Integrator'
  localDW->DiscreteIntegrator_DSTATE = Controller_P->Plant_IC;
}

// Output and update for atomic system: '<S1>/Reference Plant'
void ReferencePlant(real_T rtu_u, B_ReferencePlant_T *localB,
                    DW_ReferencePlant_T *localDW, P_ReferencePlant_T *localP,
                    P_Controller_T *Controller_P)
{
  // DiscreteIntegrator: '<S6>/Discrete Integrator'
  localB->DiscreteIntegrator = localP->DiscreteIntegrator_gainval * rtu_u +
    localDW->DiscreteIntegrator_DSTATE;
  if (localB->DiscreteIntegrator >= Controller_P->Plant_Max) {
    localB->DiscreteIntegrator = Controller_P->Plant_Max;
  } else {
    if (localB->DiscreteIntegrator <= Controller_P->Plant_Min) {
      localB->DiscreteIntegrator = Controller_P->Plant_Min;
    }
  }

  // End of DiscreteIntegrator: '<S6>/Discrete Integrator'

  // Update for DiscreteIntegrator: '<S6>/Discrete Integrator'
  localDW->DiscreteIntegrator_DSTATE = localP->DiscreteIntegrator_gainval *
    rtu_u + localB->DiscreteIntegrator;
  if (localDW->DiscreteIntegrator_DSTATE >= Controller_P->Plant_Max) {
    localDW->DiscreteIntegrator_DSTATE = Controller_P->Plant_Max;
  } else {
    if (localDW->DiscreteIntegrator_DSTATE <= Controller_P->Plant_Min) {
      localDW->DiscreteIntegrator_DSTATE = Controller_P->Plant_Min;
    }
  }

  // End of Update for DiscreteIntegrator: '<S6>/Discrete Integrator'
}

// Model step function
void Controller_step(RT_MODEL_Controller_T *const Controller_M, real_T
                     Controller_U_reference, boolean_T
                     Controller_U_enable_compensation, real_T
                     Controller_U_plant_output, real_T
                     *Controller_Y_controller_output, real_T
                     *Controller_Y_controller_reference, real_T
                     *Controller_Y_plant_reference)
{
  P_Controller_T *Controller_P = ((P_Controller_T *)
    Controller_M->ModelData.defaultParam);
  B_Controller_T *Controller_B = ((B_Controller_T *)
    Controller_M->ModelData.blockIO);
  DW_Controller_T *Controller_DW = ((DW_Controller_T *)
    Controller_M->ModelData.dwork);
  real_T rtb_MultiportSwitch_idx_0;
  real_T rtb_MultiportSwitch_idx_1;

  // MultiPortSwitch: '<S8>/Multiport Switch' incorporates:
  //   Constant: '<S8>/Constant1'
  //   Constant: '<S8>/either edge'
  //   Constant: '<S8>/neg. edge'
  //   Constant: '<S8>/pos. edge'

  switch ((int32_T)Controller_P->EdgeDetector_model) {
   case 1:
    rtb_MultiportSwitch_idx_0 = Controller_P->posedge_Value[0];
    rtb_MultiportSwitch_idx_1 = Controller_P->posedge_Value[1];
    break;

   case 2:
    rtb_MultiportSwitch_idx_0 = Controller_P->negedge_Value[0];
    rtb_MultiportSwitch_idx_1 = Controller_P->negedge_Value[1];
    break;

   default:
    rtb_MultiportSwitch_idx_0 = Controller_P->eitheredge_Value[0];
    rtb_MultiportSwitch_idx_1 = Controller_P->eitheredge_Value[1];
    break;
  }

  // End of MultiPortSwitch: '<S8>/Multiport Switch'

  // Outputs for Enabled SubSystem: '<S8>/POSITIVE Edge' incorporates:
  //   EnablePort: '<S10>/Enable'

  if (rtb_MultiportSwitch_idx_0 > 0.0) {
    // RelationalOperator: '<S10>/Relational Operator1' incorporates:
    //   Inport: '<Root>/enable_compensation'
    //   UnitDelay: '<S8>/Unit Delay'

    Controller_B->RelationalOperator1 = ((int32_T)
      Controller_U_enable_compensation > (int32_T)
      Controller_DW->UnitDelay_DSTATE_e);
  }

  // End of Outputs for SubSystem: '<S8>/POSITIVE Edge'

  // Outputs for Enabled SubSystem: '<S8>/NEGATIVE Edge' incorporates:
  //   EnablePort: '<S9>/Enable'

  if (rtb_MultiportSwitch_idx_1 > 0.0) {
    // RelationalOperator: '<S9>/Relational Operator1' incorporates:
    //   Inport: '<Root>/enable_compensation'
    //   UnitDelay: '<S8>/Unit Delay'

    Controller_B->RelationalOperator1_n = ((int32_T)
      Controller_DW->UnitDelay_DSTATE_e > (int32_T)
      Controller_U_enable_compensation);
  }

  // End of Outputs for SubSystem: '<S8>/NEGATIVE Edge'

  // Outputs for Atomic SubSystem: '<S1>/Filter'

  // Sum: '<S1>/Sum3' incorporates:
  //   Inport: '<Root>/reference'
  //   UnitDelay: '<S1>/Unit Delay2'

  Filter(Controller_U_reference - Controller_DW->UnitDelay2_DSTATE,
         &Controller_B->Filter_i, &Controller_DW->Filter_i, (P_Filter_T *)
         &Controller_P->Filter_i);

  // End of Outputs for SubSystem: '<S1>/Filter'

  // Outputs for Atomic SubSystem: '<S1>/Reference Plant'
  ReferencePlant(Controller_B->Filter_i.DiscreteFilter,
                 &Controller_B->ReferencePlant_j,
                 &Controller_DW->ReferencePlant_j, (P_ReferencePlant_T *)
                 &Controller_P->ReferencePlant_j, Controller_P);

  // End of Outputs for SubSystem: '<S1>/Reference Plant'

  // Outputs for Atomic SubSystem: '<S1>/Filter1'

  // Sum: '<S1>/Sum2' incorporates:
  //   Inport: '<Root>/reference'
  //   UnitDelay: '<S1>/Unit Delay'

  Filter(Controller_U_reference - Controller_DW->UnitDelay_DSTATE,
         &Controller_B->Filter1, &Controller_DW->Filter1, (P_Filter_T *)
         &Controller_P->Filter1);

  // End of Outputs for SubSystem: '<S1>/Filter1'

  // Outputs for Atomic SubSystem: '<S1>/Compensator'

  // Sum: '<S1>/Sum1' incorporates:
  //   Logic: '<S8>/Logical Operator1'
  //   UnitDelay: '<S1>/Unit Delay'
  //   UnitDelay: '<S1>/Unit Delay2'

  Compensator(Controller_DW->UnitDelay2_DSTATE - Controller_DW->UnitDelay_DSTATE,
              Controller_B->RelationalOperator1 ||
              Controller_B->RelationalOperator1_n, &Controller_B->Compensator_k,
              &Controller_DW->Compensator_k, (P_Compensator_T *)
              &Controller_P->Compensator_k, Controller_P);

  // End of Outputs for SubSystem: '<S1>/Compensator'

  // Switch: '<S1>/Switch' incorporates:
  //   Constant: '<S1>/Constant'
  //   Inport: '<Root>/enable_compensation'

  if (Controller_U_enable_compensation) {
    rtb_MultiportSwitch_idx_0 = Controller_B->Compensator_k.Sum;
  } else {
    rtb_MultiportSwitch_idx_0 = Controller_P->Constant_Value;
  }

  // End of Switch: '<S1>/Switch'

  // Outport: '<Root>/controller_output' incorporates:
  //   Sum: '<S1>/Sum4'

  *Controller_Y_controller_output = Controller_B->Filter1.DiscreteFilter +
    rtb_MultiportSwitch_idx_0;

  // Outport: '<Root>/controller_reference'
  *Controller_Y_controller_reference = Controller_B->Filter_i.DiscreteFilter;

  // Outport: '<Root>/plant_reference'
  *Controller_Y_plant_reference =
    Controller_B->ReferencePlant_j.DiscreteIntegrator;

  // Update for UnitDelay: '<S1>/Unit Delay2'
  Controller_DW->UnitDelay2_DSTATE =
    Controller_B->ReferencePlant_j.DiscreteIntegrator;

  // Update for UnitDelay: '<S8>/Unit Delay' incorporates:
  //   Update for Inport: '<Root>/enable_compensation'

  Controller_DW->UnitDelay_DSTATE_e = Controller_U_enable_compensation;

  // Update for UnitDelay: '<S1>/Unit Delay' incorporates:
  //   Update for Inport: '<Root>/plant_output'

  Controller_DW->UnitDelay_DSTATE = Controller_U_plant_output;
}

// Model initialize function
void Controller_initialize(RT_MODEL_Controller_T *const Controller_M, real_T
  *Controller_U_reference, boolean_T *Controller_U_enable_compensation, real_T
  *Controller_U_plant_output, real_T *Controller_Y_controller_output, real_T
  *Controller_Y_controller_reference, real_T *Controller_Y_plant_reference)
{
  P_Controller_T *Controller_P = ((P_Controller_T *)
    Controller_M->ModelData.defaultParam);
  B_Controller_T *Controller_B = ((B_Controller_T *)
    Controller_M->ModelData.blockIO);
  DW_Controller_T *Controller_DW = ((DW_Controller_T *)
    Controller_M->ModelData.dwork);

  // Registration code

  // block I/O
  (void) memset(((void *) Controller_B), 0,
                sizeof(B_Controller_T));

  // states (dwork)
  (void) memset((void *)Controller_DW, 0,
                sizeof(DW_Controller_T));

  // external inputs
  (*Controller_U_reference) = 0.0;
  (*Controller_U_enable_compensation) = false;
  (*Controller_U_plant_output) = 0.0;

  // external outputs
  (*Controller_Y_controller_output) = 0.0;
  (*Controller_Y_controller_reference) = 0.0;
  (*Controller_Y_plant_reference) = 0.0;

  // Start for Enabled SubSystem: '<S8>/POSITIVE Edge'
  // VirtualOutportStart for Outport: '<S10>/OUT'
  Controller_B->RelationalOperator1 = Controller_P->OUT_Y0_d;

  // End of Start for SubSystem: '<S8>/POSITIVE Edge'

  // Start for Enabled SubSystem: '<S8>/NEGATIVE Edge'
  // VirtualOutportStart for Outport: '<S9>/OUT'
  Controller_B->RelationalOperator1_n = Controller_P->OUT_Y0;

  // End of Start for SubSystem: '<S8>/NEGATIVE Edge'

  // Start for Outport: '<Root>/controller_reference'
  *Controller_Y_controller_reference = Controller_B->Filter_i.DiscreteFilter;

  // Start for Outport: '<Root>/plant_reference'
  *Controller_Y_plant_reference =
    Controller_B->ReferencePlant_j.DiscreteIntegrator;

  // InitializeConditions for UnitDelay: '<S1>/Unit Delay2'
  Controller_DW->UnitDelay2_DSTATE = Controller_P->Plant_IC;

  // InitializeConditions for UnitDelay: '<S8>/Unit Delay'
  Controller_DW->UnitDelay_DSTATE_e = Controller_P->EdgeDetector_ic;

  // InitializeConditions for Atomic SubSystem: '<S1>/Filter'
  Filter_Init(&Controller_DW->Filter_i, (P_Filter_T *)&Controller_P->Filter_i);

  // End of InitializeConditions for SubSystem: '<S1>/Filter'

  // InitializeConditions for Atomic SubSystem: '<S1>/Reference Plant'
  ReferencePlant_Init(&Controller_DW->ReferencePlant_j, Controller_P);

  // End of InitializeConditions for SubSystem: '<S1>/Reference Plant'

  // InitializeConditions for UnitDelay: '<S1>/Unit Delay'
  Controller_DW->UnitDelay_DSTATE = Controller_P->Plant_IC;

  // InitializeConditions for Atomic SubSystem: '<S1>/Filter1'
  Filter_Init(&Controller_DW->Filter1, (P_Filter_T *)&Controller_P->Filter1);

  // End of InitializeConditions for SubSystem: '<S1>/Filter1'

  // InitializeConditions for Atomic SubSystem: '<S1>/Compensator'
  Compensator_Init(&Controller_DW->Compensator_k, (P_Compensator_T *)
                   &Controller_P->Compensator_k);

  // End of InitializeConditions for SubSystem: '<S1>/Compensator'
}

// Model terminate function
void Controller_terminate(RT_MODEL_Controller_T *const Controller_M)
{
  // (no terminate code required)
  UNUSED_PARAMETER(Controller_M);
}

//
// File trailer for generated code.
//
// [EOF]
//

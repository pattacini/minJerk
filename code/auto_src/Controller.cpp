//
// File: Controller.cpp
//
// Code generated for Simulink model 'Controller'.
//
// Model version                  : 1.230
// Simulink Coder version         : 8.7 (R2014b) 08-Sep-2014
// C/C++ source code generated on : Mon Dec 08 18:27:33 2014
//
// Target selection: ert.tlc
// Embedded hardware selection: 32-bit Generic
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "Controller.h"
#include "Controller_private.h"

// Named constants for Chart: '<S1>/Compensator Handling'
#define Controller_IN_AutomaticOff     ((uint8_T)1U)
#define Controller_IN_AutomaticOn      ((uint8_T)2U)
#define Controller_IN_NO_ACTIVE_CHILD  ((uint8_T)0U)
#define Controller_IN_Select           ((uint8_T)3U)

// Initial conditions for atomic system: '<S1>/Compensator'
void Compensator_Init(DW_Compensator_T *localDW, P_Compensator_T *localP)
{
  // InitializeConditions for DiscreteIntegrator: '<S9>/Integrator'
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

  // Gain: '<S9>/Integral Gain'
  rtb_IntegralGain = Controller_P->Compensator_Ki * rtu_e;

  // DiscreteIntegrator: '<S9>/Integrator'
  if (rtu_reset && (localDW->Integrator_PrevResetState <= 0)) {
    localDW->Integrator_DSTATE = localP->Integrator_IC;
  }

  Integrator = localP->Integrator_gainval * rtb_IntegralGain +
    localDW->Integrator_DSTATE;

  // End of DiscreteIntegrator: '<S9>/Integrator'

  // Sum: '<S9>/Sum' incorporates:
  //   Gain: '<S9>/Proportional Gain'

  localB->Sum = Controller_P->Compensator_Kp * rtu_e + Integrator;

  // Update for DiscreteIntegrator: '<S9>/Integrator'
  localDW->Integrator_DSTATE = localP->Integrator_gainval * rtb_IntegralGain +
    Integrator;
  if (rtu_reset) {
    localDW->Integrator_PrevResetState = 1;
  } else {
    localDW->Integrator_PrevResetState = 0;
  }

  // End of Update for DiscreteIntegrator: '<S9>/Integrator'
}

// Initial conditions for atomic system: '<S1>/Error Statistics'
void ErrorStatistics_Init(DW_ErrorStatistics_T *localDW, P_ErrorStatistics_T
  *localP)
{
  int32_T i;

  // InitializeConditions for Buffer: '<S5>/Buffer'
  localDW->Buffer_inBufPtrIdx = 100;
  localDW->Buffer_bufferLength = 100;
  localDW->Buffer_outBufPtrIdx = 0;

  // InitializeConditions for S-Function (sdspstatfcns): '<S5>/Mean'
  localDW->Mean_Iteration = 0U;
  localDW->Mean_AccVal = 0.0;
  for (i = 0; i < 200; i++) {
    // InitializeConditions for Buffer: '<S5>/Buffer'
    localDW->Buffer_CircBuf[i] = localP->Buffer_ic;

    // InitializeConditions for Unbuffer: '<S5>/Unbuffer'
    localDW->Unbuffer_CircBuf[i] = localP->Unbuffer_ic;
  }

  // InitializeConditions for Unbuffer: '<S5>/Unbuffer'
  localDW->Unbuffer_inBufPtrIdx = 100;
  localDW->Unbuffer_bufferLength = 100;
  localDW->Unbuffer_outBufPtrIdx = 0;
}

// Outputs for atomic system: '<S1>/Error Statistics'
void ErrorStatisticsTID0(real_T rtu_in, B_ErrorStatistics_T *localB,
  DW_ErrorStatistics_T *localDW)
{
  int32_T memIdx;
  int32_T i;
  int32_T nSampsAtBot;
  int32_T nSamps;
  real_T Abs;

  // Abs: '<S5>/Abs'
  Abs = std::abs(rtu_in);

  // Buffer: '<S5>/Buffer'
  nSamps = 1;
  nSampsAtBot = 200 - localDW->Buffer_inBufPtrIdx;
  memIdx = localDW->Buffer_inBufPtrIdx;
  if (nSampsAtBot <= 1) {
    i = 0;
    while (i < nSampsAtBot) {
      localDW->Buffer_CircBuf[localDW->Buffer_inBufPtrIdx] = Abs;
      i = 1;
    }

    memIdx = 0;
    nSamps = 1 - nSampsAtBot;
  }

  for (i = 0; i < nSamps; i++) {
    localDW->Buffer_CircBuf[memIdx + i] = Abs;
  }

  localDW->Buffer_inBufPtrIdx++;
  if (localDW->Buffer_inBufPtrIdx >= 200) {
    localDW->Buffer_inBufPtrIdx -= 200;
  }

  // End of Buffer: '<S5>/Buffer'

  // Unbuffer: '<S5>/Unbuffer'
  memIdx = localDW->Unbuffer_outBufPtrIdx;
  if (localDW->Unbuffer_outBufPtrIdx < 0) {
    memIdx = localDW->Unbuffer_outBufPtrIdx + 200;
  }

  nSampsAtBot = 200 - memIdx;
  nSamps = 1;
  if (nSampsAtBot <= 1) {
    i = 0;
    while (i < nSampsAtBot) {
      localB->Unbuffer = localDW->Unbuffer_CircBuf[memIdx];
      i = 1;
    }

    memIdx = 0;
    nSamps = 1 - nSampsAtBot;
  }

  for (i = 0; i < nSamps; i++) {
    localB->Unbuffer = localDW->Unbuffer_CircBuf[memIdx + i];
  }

  localDW->Unbuffer_outBufPtrIdx = memIdx + nSamps;

  // End of Unbuffer: '<S5>/Unbuffer'
}

// Outputs for atomic system: '<S1>/Error Statistics'
void ErrorStatisticsTID1(B_ErrorStatistics_T *localB, DW_ErrorStatistics_T
  *localDW)
{
  int32_T uyIdx;
  int32_T currentOffset;
  int32_T i;
  int32_T nSampsAtBot;
  int32_T nSamps;
  real_T rtb_Buffer[100];

  // Buffer: '<S5>/Buffer'
  uyIdx = 0;
  currentOffset = localDW->Buffer_outBufPtrIdx;
  if (localDW->Buffer_outBufPtrIdx < 0) {
    currentOffset = localDW->Buffer_outBufPtrIdx + 200;
  }

  nSampsAtBot = 200 - currentOffset;
  nSamps = 100;
  if (nSampsAtBot <= 100) {
    for (i = 0; i < nSampsAtBot; i++) {
      rtb_Buffer[i] = localDW->Buffer_CircBuf[currentOffset + i];
    }

    uyIdx = nSampsAtBot;
    currentOffset = 0;
    nSamps = 100 - nSampsAtBot;
  }

  for (i = 0; i < nSamps; i++) {
    rtb_Buffer[uyIdx + i] = localDW->Buffer_CircBuf[currentOffset + i];
  }

  localDW->Buffer_outBufPtrIdx = currentOffset + nSamps;

  // End of Buffer: '<S5>/Buffer'

  // S-Function (sdspstatfcns): '<S5>/Mean'
  uyIdx = 0;
  for (currentOffset = 0; currentOffset < 100; currentOffset++) {
    localDW->Mean_Iteration++;
    if (localDW->Mean_Iteration > 1U) {
      localDW->Mean_AccVal += rtb_Buffer[uyIdx];
      localB->Mean[uyIdx] = localDW->Mean_AccVal / (real_T)
        localDW->Mean_Iteration;
    } else {
      if (localDW->Mean_Iteration == 0U) {
        localDW->Mean_Iteration = 1U;
      }

      localDW->Mean_AccVal = rtb_Buffer[uyIdx];
      localB->Mean[uyIdx] = rtb_Buffer[uyIdx];
    }

    uyIdx++;
  }

  // End of S-Function (sdspstatfcns): '<S5>/Mean'

  // Unbuffer: '<S5>/Unbuffer'
  uyIdx = 0;
  nSamps = 100;
  nSampsAtBot = 200 - localDW->Unbuffer_inBufPtrIdx;
  currentOffset = localDW->Unbuffer_inBufPtrIdx;
  if (nSampsAtBot <= 100) {
    for (i = 0; i < nSampsAtBot; i++) {
      localDW->Unbuffer_CircBuf[localDW->Unbuffer_inBufPtrIdx + i] =
        localB->Mean[i];
    }

    uyIdx = nSampsAtBot;
    currentOffset = 0;
    nSamps = 100 - nSampsAtBot;
  }

  for (i = 0; i < nSamps; i++) {
    localDW->Unbuffer_CircBuf[currentOffset + i] = localB->Mean[uyIdx + i];
  }

  localDW->Unbuffer_inBufPtrIdx += 100;
  if (localDW->Unbuffer_inBufPtrIdx >= 200) {
    localDW->Unbuffer_inBufPtrIdx -= 200;
  }

  // End of Unbuffer: '<S5>/Unbuffer'
}

//
// Initial conditions for atomic system:
//    '<S1>/Filter'
//    '<S1>/Filter1'
//
void Filter_Init(DW_Filter_T *localDW, P_Filter_T *localP)
{
  // InitializeConditions for DiscreteTransferFcn: '<S6>/Discrete Filter'
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

  // DiscreteTransferFcn: '<S6>/Discrete Filter'
  DiscreteFilter_tmp = ((rtu_e - localP->DiscreteFilter_DenCoef[1] *
    localDW->DiscreteFilter_states[0]) - localP->DiscreteFilter_DenCoef[2] *
                        localDW->DiscreteFilter_states[1]) /
    localP->DiscreteFilter_DenCoef[0];
  localB->DiscreteFilter = (localP->DiscreteFilter_NumCoef[0] *
    DiscreteFilter_tmp + localP->DiscreteFilter_NumCoef[1] *
    localDW->DiscreteFilter_states[0]) + localP->DiscreteFilter_NumCoef[2] *
    localDW->DiscreteFilter_states[1];

  // Update for DiscreteTransferFcn: '<S6>/Discrete Filter'
  localDW->DiscreteFilter_states[1] = localDW->DiscreteFilter_states[0];
  localDW->DiscreteFilter_states[0] = DiscreteFilter_tmp;
}

// Initial conditions for atomic system: '<S1>/Reference Plant'
void ReferencePlant_Init(DW_ReferencePlant_T *localDW, P_Controller_T
  *Controller_P)
{
  // InitializeConditions for DiscreteIntegrator: '<S8>/Discrete Integrator'
  localDW->DiscreteIntegrator_DSTATE = Controller_P->Plant_IC;
}

// Output and update for atomic system: '<S1>/Reference Plant'
void ReferencePlant(real_T rtu_u, B_ReferencePlant_T *localB,
                    DW_ReferencePlant_T *localDW, P_ReferencePlant_T *localP,
                    P_Controller_T *Controller_P)
{
  // DiscreteIntegrator: '<S8>/Discrete Integrator'
  localB->DiscreteIntegrator = localP->DiscreteIntegrator_gainval * rtu_u +
    localDW->DiscreteIntegrator_DSTATE;
  if (localB->DiscreteIntegrator >= Controller_P->Plant_Max) {
    localB->DiscreteIntegrator = Controller_P->Plant_Max;
  } else {
    if (localB->DiscreteIntegrator <= Controller_P->Plant_Min) {
      localB->DiscreteIntegrator = Controller_P->Plant_Min;
    }
  }

  // End of DiscreteIntegrator: '<S8>/Discrete Integrator'

  // Update for DiscreteIntegrator: '<S8>/Discrete Integrator'
  localDW->DiscreteIntegrator_DSTATE = localP->DiscreteIntegrator_gainval *
    rtu_u + localB->DiscreteIntegrator;
  if (localDW->DiscreteIntegrator_DSTATE >= Controller_P->Plant_Max) {
    localDW->DiscreteIntegrator_DSTATE = Controller_P->Plant_Max;
  } else {
    if (localDW->DiscreteIntegrator_DSTATE <= Controller_P->Plant_Min) {
      localDW->DiscreteIntegrator_DSTATE = Controller_P->Plant_Min;
    }
  }

  // End of Update for DiscreteIntegrator: '<S8>/Discrete Integrator'
}

// Model step function for TID0
void Controller_step0(RT_MODEL_Controller_T *const Controller_M, real_T
                      Controller_U_reference, CompensatorState
                      Controller_U_compensator_state, real_T
                      Controller_U_plant_output, real_T
                      *Controller_Y_controller_output, real_T
                      *Controller_Y_controller_reference, real_T
                      *Controller_Y_plant_reference, real_T
                      *Controller_Y_error_statistics, boolean_T
                      *Controller_Y_enable_compensation) // Sample time: [0.01s, 0.0s] 
{
  P_Controller_T *Controller_P = ((P_Controller_T *)
    Controller_M->ModelData.defaultParam);
  B_Controller_T *Controller_B = ((B_Controller_T *)
    Controller_M->ModelData.blockIO);
  DW_Controller_T *Controller_DW = ((DW_Controller_T *)
    Controller_M->ModelData.dwork);
  real_T rtb_e_comp;
  real_T rtb_MultiportSwitch_idx_0;
  real_T rtb_MultiportSwitch_idx_1;

  // MultiPortSwitch: '<S10>/Multiport Switch' incorporates:
  //   Constant: '<S10>/Constant1'
  //   Constant: '<S10>/either edge'
  //   Constant: '<S10>/neg. edge'
  //   Constant: '<S10>/pos. edge'

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

  // End of MultiPortSwitch: '<S10>/Multiport Switch'

  // Sum: '<S1>/Sum1' incorporates:
  //   UnitDelay: '<S1>/Unit Delay'
  //   UnitDelay: '<S1>/Unit Delay2'

  rtb_e_comp = Controller_DW->UnitDelay2_DSTATE -
    Controller_DW->UnitDelay_DSTATE;

  // Outputs for Atomic SubSystem: '<S1>/Error Statistics'
  ErrorStatisticsTID0(rtb_e_comp, &Controller_B->ErrorStatistics_p,
                      &Controller_DW->ErrorStatistics_p);

  // End of Outputs for SubSystem: '<S1>/Error Statistics'

  // Chart: '<S1>/Compensator Handling' incorporates:
  //   Inport: '<Root>/compensator_state'

  // Gateway: Controller/Compensator Handling
  // During: Controller/Compensator Handling
  if (Controller_DW->is_active_c3_Controller == 0U) {
    // Entry: Controller/Compensator Handling
    Controller_DW->is_active_c3_Controller = 1U;

    // Entry Internal: Controller/Compensator Handling
    // Transition: '<S3>:9'
    Controller_DW->is_c3_Controller = Controller_IN_Select;
  } else {
    switch (Controller_DW->is_c3_Controller) {
     case Controller_IN_AutomaticOff:
      // During 'AutomaticOff': '<S3>:21'
      if (Controller_U_compensator_state != Auto) {
        // Transition: '<S3>:22'
        Controller_DW->is_c3_Controller = Controller_IN_Select;
      } else {
        if (Controller_B->ErrorStatistics_p.Unbuffer >
            Controller_P->AutoCompensator_ThresHystMax) {
          // Transition: '<S3>:24'
          Controller_DW->is_c3_Controller = Controller_IN_AutomaticOn;

          // Outport: '<Root>/enable_compensation'
          // Entry 'AutomaticOn': '<S3>:19'
          *Controller_Y_enable_compensation = true;
        }
      }
      break;

     case Controller_IN_AutomaticOn:
      // During 'AutomaticOn': '<S3>:19'
      if (Controller_U_compensator_state != Auto) {
        // Transition: '<S3>:20'
        Controller_DW->is_c3_Controller = Controller_IN_Select;
      } else {
        if (Controller_B->ErrorStatistics_p.Unbuffer <
            Controller_P->AutoCompensator_ThresHystMin) {
          // Transition: '<S3>:23'
          Controller_DW->is_c3_Controller = Controller_IN_AutomaticOff;

          // Outport: '<Root>/enable_compensation'
          // Entry 'AutomaticOff': '<S3>:21'
          *Controller_Y_enable_compensation = false;
        }
      }
      break;

     default:
      // During 'Select': '<S3>:3'
      // Transition: '<S3>:15'
      if (Controller_U_compensator_state == Off) {
        // Outport: '<Root>/enable_compensation'
        // Transition: '<S3>:12'
        *Controller_Y_enable_compensation = false;
        Controller_DW->is_c3_Controller = Controller_IN_Select;
      } else if (Controller_U_compensator_state == On) {
        // Outport: '<Root>/enable_compensation'
        // Transition: '<S3>:11'
        *Controller_Y_enable_compensation = true;
        Controller_DW->is_c3_Controller = Controller_IN_Select;
      } else {
        // Transition: '<S3>:17'
        if (Controller_B->ErrorStatistics_p.Unbuffer >
            Controller_P->AutoCompensator_ThresHystMax) {
          // Transition: '<S3>:26'
          Controller_DW->is_c3_Controller = Controller_IN_AutomaticOn;

          // Outport: '<Root>/enable_compensation'
          // Entry 'AutomaticOn': '<S3>:19'
          *Controller_Y_enable_compensation = true;
        } else {
          // Transition: '<S3>:27'
          Controller_DW->is_c3_Controller = Controller_IN_AutomaticOff;

          // Outport: '<Root>/enable_compensation'
          // Entry 'AutomaticOff': '<S3>:21'
          *Controller_Y_enable_compensation = false;
        }
      }
      break;
    }
  }

  // End of Chart: '<S1>/Compensator Handling'

  // Outputs for Enabled SubSystem: '<S10>/POSITIVE Edge' incorporates:
  //   EnablePort: '<S12>/Enable'

  if (rtb_MultiportSwitch_idx_0 > 0.0) {
    // RelationalOperator: '<S12>/Relational Operator1' incorporates:
    //   UnitDelay: '<S10>/Unit Delay'

    Controller_B->RelationalOperator1 = ((int32_T)
      *Controller_Y_enable_compensation > (int32_T)
      Controller_DW->UnitDelay_DSTATE_e);
  }

  // End of Outputs for SubSystem: '<S10>/POSITIVE Edge'

  // Outputs for Enabled SubSystem: '<S10>/NEGATIVE Edge' incorporates:
  //   EnablePort: '<S11>/Enable'

  if (rtb_MultiportSwitch_idx_1 > 0.0) {
    // RelationalOperator: '<S11>/Relational Operator1' incorporates:
    //   UnitDelay: '<S10>/Unit Delay'

    Controller_B->RelationalOperator1_n = ((int32_T)
      Controller_DW->UnitDelay_DSTATE_e > (int32_T)
      *Controller_Y_enable_compensation);
  }

  // End of Outputs for SubSystem: '<S10>/NEGATIVE Edge'

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

  // Logic: '<S10>/Logical Operator1'
  Compensator(rtb_e_comp, Controller_B->RelationalOperator1 ||
              Controller_B->RelationalOperator1_n, &Controller_B->Compensator_k,
              &Controller_DW->Compensator_k, (P_Compensator_T *)
              &Controller_P->Compensator_k, Controller_P);

  // End of Outputs for SubSystem: '<S1>/Compensator'

  // Switch: '<S1>/Switch' incorporates:
  //   Constant: '<S1>/Constant'

  if (*Controller_Y_enable_compensation) {
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

  // Outport: '<Root>/error_statistics'
  *Controller_Y_error_statistics = Controller_B->ErrorStatistics_p.Unbuffer;

  // Update for UnitDelay: '<S1>/Unit Delay2'
  Controller_DW->UnitDelay2_DSTATE =
    Controller_B->ReferencePlant_j.DiscreteIntegrator;

  // Update for UnitDelay: '<S10>/Unit Delay'
  Controller_DW->UnitDelay_DSTATE_e = *Controller_Y_enable_compensation;

  // Update for UnitDelay: '<S1>/Unit Delay' incorporates:
  //   Update for Inport: '<Root>/plant_output'

  Controller_DW->UnitDelay_DSTATE = Controller_U_plant_output;
}

// Model step function for TID1
void Controller_step1(RT_MODEL_Controller_T *const Controller_M) // Sample time: [1.0s, 0.0s] 
{
  B_Controller_T *Controller_B = ((B_Controller_T *)
    Controller_M->ModelData.blockIO);
  DW_Controller_T *Controller_DW = ((DW_Controller_T *)
    Controller_M->ModelData.dwork);

  // Outputs for Atomic SubSystem: '<S1>/Error Statistics'
  ErrorStatisticsTID1(&Controller_B->ErrorStatistics_p,
                      &Controller_DW->ErrorStatistics_p);

  // End of Outputs for SubSystem: '<S1>/Error Statistics'
}

// Model initialize function
void Controller_initialize(RT_MODEL_Controller_T *const Controller_M, real_T
  *Controller_U_reference, CompensatorState *Controller_U_compensator_state,
  real_T *Controller_U_plant_output, real_T *Controller_Y_controller_output,
  real_T *Controller_Y_controller_reference, real_T
  *Controller_Y_plant_reference, real_T *Controller_Y_error_statistics,
  boolean_T *Controller_Y_enable_compensation)
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
  (*Controller_U_compensator_state) = Off;
  (*Controller_U_plant_output) = 0.0;

  // external outputs
  (*Controller_Y_controller_output) = 0.0;
  (*Controller_Y_controller_reference) = 0.0;
  (*Controller_Y_plant_reference) = 0.0;
  (*Controller_Y_error_statistics) = 0.0;
  (*Controller_Y_enable_compensation) = false;

  // Start for Enabled SubSystem: '<S10>/POSITIVE Edge'
  // VirtualOutportStart for Outport: '<S12>/OUT'
  Controller_B->RelationalOperator1 = Controller_P->OUT_Y0_d;

  // End of Start for SubSystem: '<S10>/POSITIVE Edge'

  // Start for Enabled SubSystem: '<S10>/NEGATIVE Edge'
  // VirtualOutportStart for Outport: '<S11>/OUT'
  Controller_B->RelationalOperator1_n = Controller_P->OUT_Y0;

  // End of Start for SubSystem: '<S10>/NEGATIVE Edge'

  // Start for Outport: '<Root>/controller_reference'
  *Controller_Y_controller_reference = Controller_B->Filter_i.DiscreteFilter;

  // Start for Outport: '<Root>/plant_reference'
  *Controller_Y_plant_reference =
    Controller_B->ReferencePlant_j.DiscreteIntegrator;

  // Start for Outport: '<Root>/error_statistics'
  *Controller_Y_error_statistics = Controller_B->ErrorStatistics_p.Unbuffer;

  // InitializeConditions for UnitDelay: '<S1>/Unit Delay2'
  Controller_DW->UnitDelay2_DSTATE = Controller_P->Plant_IC;

  // InitializeConditions for UnitDelay: '<S10>/Unit Delay'
  Controller_DW->UnitDelay_DSTATE_e = Controller_P->EdgeDetector_ic;

  // InitializeConditions for UnitDelay: '<S1>/Unit Delay'
  Controller_DW->UnitDelay_DSTATE = Controller_P->Plant_IC;

  // InitializeConditions for Atomic SubSystem: '<S1>/Error Statistics'
  ErrorStatistics_Init(&Controller_DW->ErrorStatistics_p, (P_ErrorStatistics_T *)
                       &Controller_P->ErrorStatistics_p);

  // End of InitializeConditions for SubSystem: '<S1>/Error Statistics'

  // InitializeConditions for Chart: '<S1>/Compensator Handling'
  Controller_DW->is_active_c3_Controller = 0U;
  Controller_DW->is_c3_Controller = Controller_IN_NO_ACTIVE_CHILD;

  // InitializeConditions for Outport: '<Root>/enable_compensation' incorporates:
  //   InitializeConditions for Chart: '<S1>/Compensator Handling'

  *Controller_Y_enable_compensation = false;

  // InitializeConditions for Atomic SubSystem: '<S1>/Filter'
  Filter_Init(&Controller_DW->Filter_i, (P_Filter_T *)&Controller_P->Filter_i);

  // End of InitializeConditions for SubSystem: '<S1>/Filter'

  // InitializeConditions for Atomic SubSystem: '<S1>/Reference Plant'
  ReferencePlant_Init(&Controller_DW->ReferencePlant_j, Controller_P);

  // End of InitializeConditions for SubSystem: '<S1>/Reference Plant'

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

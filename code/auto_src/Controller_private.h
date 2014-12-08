//
// File: Controller_private.h
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
#ifndef RTW_HEADER_Controller_private_h_
#define RTW_HEADER_Controller_private_h_
#include "rtwtypes.h"

extern void Compensator_Init(DW_Compensator_T *localDW, P_Compensator_T *localP);
extern void Compensator(real_T rtu_e, boolean_T rtu_reset, B_Compensator_T
  *localB, DW_Compensator_T *localDW, P_Compensator_T *localP, P_Controller_T
  *Controller_P);
extern void Filter_Init(DW_Filter_T *localDW, P_Filter_T *localP);
extern void Filter(real_T rtu_e, B_Filter_T *localB, DW_Filter_T *localDW,
                   P_Filter_T *localP);
extern void ReferencePlant_Init(DW_ReferencePlant_T *localDW, P_Controller_T
  *Controller_P);
extern void ReferencePlant(real_T rtu_u, B_ReferencePlant_T *localB,
  DW_ReferencePlant_T *localDW, P_ReferencePlant_T *localP, P_Controller_T
  *Controller_P);

#endif                                 // RTW_HEADER_Controller_private_h_

//
// File trailer for generated code.
//
// [EOF]
//

/*
 * File: Fibonacci.c
 *
 * Code generated for Simulink model 'Fibonacci'.
 *
 * Model version                  : 1.3
 * Simulink Coder version         : 8.6 (R2014a) 27-Dec-2013
 * C/C++ source code generated on : Sun Feb  7 22:10:30 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Fibonacci.h"
#include "Fibonacci_private.h"

/* Block signals (auto storage) */
B_Fibonacci_T Fibonacci_B;

/* Block states (auto storage) */
DW_Fibonacci_T Fibonacci_DW;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_Fibonacci_T Fibonacci_Y;

/* Real-time model */
RT_MODEL_Fibonacci_T Fibonacci_M_;
RT_MODEL_Fibonacci_T *const Fibonacci_M = &Fibonacci_M_;

/* Model step function */
void Fibonacci_step(void)
{
  real_T u0;
  real_T u1;
  real_T u2;

  /* Outport: '<Root>/Out1' incorporates:
   *  UnitDelay: '<Root>/Fn'
   */
  Fibonacci_Y.Out1 = Fibonacci_DW.Fn_DSTATE;

  /* UnitDelay: '<Root>/Fn_1' */
  Fibonacci_B.Fn_1 = Fibonacci_DW.Fn_1_DSTATE;

  /* Saturate: '<Root>/Saturation' */
  u0 = Fibonacci_B.Fn_1;
  u1 = Fibonacci_P.Saturation_LowerSat;
  u2 = Fibonacci_P.Saturation_UpperSat;
  if (u0 > u2) {
    Fibonacci_B.Saturation = u2;
  } else if (u0 < u1) {
    Fibonacci_B.Saturation = u1;
  } else {
    Fibonacci_B.Saturation = u0;
  }

  /* End of Saturate: '<Root>/Saturation' */

  /* Outport: '<Root>/approximate_golden_ratio' incorporates:
   *  Product: '<Root>/Divide'
   */
  Fibonacci_Y.approximate_golden_ratio = Fibonacci_Y.Out1 /
    Fibonacci_B.Saturation;

  /* Sum: '<Root>/Subtract' incorporates:
   *  Constant: '<Root>/Golden_ratio'
   */
  Fibonacci_B.Subtract = Fibonacci_Y.approximate_golden_ratio -
    Fibonacci_P.Golden_ratio_Value;

  /* Abs: '<Root>/Abs' */
  Fibonacci_B.Abs = fabs(Fibonacci_B.Subtract);

  /* Outport: '<Root>/error[%]' incorporates:
   *  Gain: '<Root>/Gain'
   */
  Fibonacci_Y.error = Fibonacci_P.Gain_Gain * Fibonacci_B.Abs;

  /* Sum: '<Root>/Add' */
  Fibonacci_B.Add = Fibonacci_Y.Out1 + Fibonacci_B.Fn_1;

  /* Update for UnitDelay: '<Root>/Fn' */
  Fibonacci_DW.Fn_DSTATE = Fibonacci_B.Add;

  /* Update for UnitDelay: '<Root>/Fn_1' */
  Fibonacci_DW.Fn_1_DSTATE = Fibonacci_Y.Out1;
}

/* Model initialize function */
void Fibonacci_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  Fibonacci_P.Saturation_UpperSat = rtInf;

  /* initialize error status */
  rtmSetErrorStatus(Fibonacci_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &Fibonacci_B), 0,
                sizeof(B_Fibonacci_T));

  /* states (dwork) */
  (void) memset((void *)&Fibonacci_DW, 0,
                sizeof(DW_Fibonacci_T));

  /* external outputs */
  (void) memset((void *)&Fibonacci_Y, 0,
                sizeof(ExtY_Fibonacci_T));

  /* InitializeConditions for UnitDelay: '<Root>/Fn' */
  Fibonacci_DW.Fn_DSTATE = Fibonacci_P.Fn_InitialCondition;

  /* InitializeConditions for UnitDelay: '<Root>/Fn_1' */
  Fibonacci_DW.Fn_1_DSTATE = Fibonacci_P.Fn_1_InitialCondition;
}

/* Model terminate function */
void Fibonacci_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

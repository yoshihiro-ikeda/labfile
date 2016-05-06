/*
 * File: Fibonacci.h
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

#ifndef RTW_HEADER_Fibonacci_h_
#define RTW_HEADER_Fibonacci_h_
#include <math.h>
#include <stddef.h>
#include <string.h>
#ifndef Fibonacci_COMMON_INCLUDES_
# define Fibonacci_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* Fibonacci_COMMON_INCLUDES_ */

#include "Fibonacci_types.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals (auto storage) */
typedef struct {
  real_T Fn_1;                         /* '<Root>/Fn_1' */
  real_T Saturation;                   /* '<Root>/Saturation' */
  real_T Subtract;                     /* '<Root>/Subtract' */
  real_T Abs;                          /* '<Root>/Abs' */
  real_T Add;                          /* '<Root>/Add' */
} B_Fibonacci_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T Fn_DSTATE;                    /* '<Root>/Fn' */
  real_T Fn_1_DSTATE;                  /* '<Root>/Fn_1' */
} DW_Fibonacci_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T Out1;                         /* '<Root>/Out1' */
  real_T approximate_golden_ratio;     /* '<Root>/approximate_golden_ratio' */
  real_T error;                        /* '<Root>/error[%]' */
} ExtY_Fibonacci_T;

/* Parameters (auto storage) */
struct P_Fibonacci_T_ {
  real_T Fn_InitialCondition;          /* Expression: 1
                                        * Referenced by: '<Root>/Fn'
                                        */
  real_T Fn_1_InitialCondition;        /* Expression: 0
                                        * Referenced by: '<Root>/Fn_1'
                                        */
  real_T Saturation_UpperSat;          /* Expression: inf
                                        * Referenced by: '<Root>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: 1
                                        * Referenced by: '<Root>/Saturation'
                                        */
  real_T Golden_ratio_Value;           /* Expression: (1+sqrt(5))/2
                                        * Referenced by: '<Root>/Golden_ratio'
                                        */
  real_T Gain_Gain;                    /* Expression: 2/(1+sqrt(5))
                                        * Referenced by: '<Root>/Gain'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_Fibonacci_T {
  const char_T * volatile errorStatus;
};

/* Block parameters (auto storage) */
extern P_Fibonacci_T Fibonacci_P;

/* Block signals (auto storage) */
extern B_Fibonacci_T Fibonacci_B;

/* Block states (auto storage) */
extern DW_Fibonacci_T Fibonacci_DW;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_Fibonacci_T Fibonacci_Y;

/* Model entry point functions */
extern void Fibonacci_initialize(void);
extern void Fibonacci_step(void);
extern void Fibonacci_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Fibonacci_T *const Fibonacci_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Fibonacci'
 */
#endif                                 /* RTW_HEADER_Fibonacci_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

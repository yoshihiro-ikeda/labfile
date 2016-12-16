/*
 * File: offset_rate210.h
 *
 * Code generated for Simulink model 'offset_rate210'.
 *
 * Model version                  : 1.21
 * Simulink Coder version         : 8.6 (R2014a) 27-Dec-2013
 * C/C++ source code generated on : Tue Aug  9 15:22:31 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Emulation hardware selection:
 *    Differs from embedded hardware (MATLAB Host)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_offset_rate210_h_
#define RTW_HEADER_offset_rate210_h_
#include <math.h>
#include <string.h>
#ifndef offset_rate210_COMMON_INCLUDES_
# define offset_rate210_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* offset_rate210_COMMON_INCLUDES_ */

#include "offset_rate210_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T UnitDelay1_DSTATE;            /* '<Root>/UnitDelay1' */
  real_T UnitDelay2_DSTATE;            /* '<Root>/UnitDelay2' */
  real_T UnitDelay_DSTATE;             /* '<Root>/UnitDelay' */
} DW_offset_rate210_T;

/* Parameters (auto storage) */
struct P_offset_rate210_T_ {
  real_T UnitDelay1_InitialCondition;  /* Expression: 2
                                        * Referenced by: '<Root>/UnitDelay1'
                                        */
  real_T Gain_Gain;                    /* Expression: 2
                                        * Referenced by: '<Root>/Gain'
                                        */
  real_T UnitDelay2_InitialCondition;  /* Expression: 1
                                        * Referenced by: '<Root>/UnitDelay2'
                                        */
  real_T Gain1_Gain;                   /* Expression: 2
                                        * Referenced by: '<Root>/Gain1'
                                        */
  real_T Gain2_Gain;                   /* Expression: 0.5
                                        * Referenced by: '<Root>/Gain2'
                                        */
  real_T Gain3_Gain;                   /* Expression: 2
                                        * Referenced by: '<Root>/Gain3'
                                        */
  real_T Gain4_Gain;                   /* Expression: 0.5
                                        * Referenced by: '<Root>/Gain4'
                                        */
  real_T Gain5_Gain;                   /* Expression: 2
                                        * Referenced by: '<Root>/Gain5'
                                        */
  real_T Gain6_Gain;                   /* Expression: 0.5
                                        * Referenced by: '<Root>/Gain6'
                                        */
  real_T Gain7_Gain;                   /* Expression: 2
                                        * Referenced by: '<Root>/Gain7'
                                        */
  real_T Gain8_Gain;                   /* Expression: 0.5
                                        * Referenced by: '<Root>/Gain8'
                                        */
  real_T Gain9_Gain;                   /* Expression: 2
                                        * Referenced by: '<Root>/Gain9'
                                        */
  real_T Gain10_Gain;                  /* Expression: 0.5
                                        * Referenced by: '<Root>/Gain10'
                                        */
  real_T UnitDelay_InitialCondition;   /* Expression: 1
                                        * Referenced by: '<Root>/UnitDelay'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_offset_rate210_T {
  const char_T * volatile errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    struct {
      uint8_T TID[6];
    } TaskCounters;
  } Timing;
};

/* Block parameters (auto storage) */
extern P_offset_rate210_T offset_rate210_P;

/* Block states (auto storage) */
extern DW_offset_rate210_T offset_rate210_DW;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern real_T offset_rate210_UnitDelay1_1;/* '<Root>/UnitDelay1' */
extern real_T offset_rate210_Gain_1;   /* '<Root>/Gain' */
extern real_T offset_rate210_UnitDelay2_1;/* '<Root>/UnitDelay2' */
extern real_T offset_rate210_Sqrt1_1;  /* '<Root>/Sqrt1' */
extern real_T offset_rate210_MathFunction2_1;/* '<Root>/MathFunction2' */
extern real_T offset_rate210_S_Function_1;/* '<Root>/S_Function' */
extern real_T offset_rate210_Gain1_1;  /* '<Root>/Gain1' */
extern real_T offset_rate210_MathFunction1_1;/* '<Root>/MathFunction1' */
extern real_T offset_rate210_Gain2_1;  /* '<Root>/Gain2' */
extern real_T offset_rate210_Sqrt2_1;  /* '<Root>/Sqrt2' */
extern real_T offset_rate210_MathFunction4_1;/* '<Root>/MathFunction4' */
extern real_T offset_rate210_S_Function1_1;/* '<Root>/S_Function1' */
extern real_T offset_rate210_Gain3_1;  /* '<Root>/Gain3' */
extern real_T offset_rate210_MathFunction3_1;/* '<Root>/MathFunction3' */
extern real_T offset_rate210_Gain4_1;  /* '<Root>/Gain4' */
extern real_T offset_rate210_Sqrt3_1;  /* '<Root>/Sqrt3' */
extern real_T offset_rate210_MathFunction6_1;/* '<Root>/MathFunction6' */
extern real_T offset_rate210_S_Function2_1;/* '<Root>/S_Function2' */
extern real_T offset_rate210_Gain5_1;  /* '<Root>/Gain5' */
extern real_T offset_rate210_MathFunction5_1;/* '<Root>/MathFunction5' */
extern real_T offset_rate210_Gain6_1;  /* '<Root>/Gain6' */
extern real_T offset_rate210_Sqrt4_1;  /* '<Root>/Sqrt4' */
extern real_T offset_rate210_MathFunction8_1;/* '<Root>/MathFunction8' */
extern real_T offset_rate210_S_Function3_1;/* '<Root>/S_Function3' */
extern real_T offset_rate210_Gain7_1;  /* '<Root>/Gain7' */
extern real_T offset_rate210_MathFunction7_1;/* '<Root>/MathFunction7' */
extern real_T offset_rate210_Gain8_1;  /* '<Root>/Gain8' */
extern real_T offset_rate210_Sqrt5_1;  /* '<Root>/Sqrt5' */
extern real_T offset_rate210_MathFunction10_1;/* '<Root>/MathFunction10' */
extern real_T offset_rate210_S_Function4_1;/* '<Root>/S_Function4' */
extern real_T offset_rate210_Gain9_1;  /* '<Root>/Gain9' */
extern real_T offset_rate210_MathFunction9_1;/* '<Root>/MathFunction9' */
extern real_T offset_rate210_Gain10_1; /* '<Root>/Gain10' */
extern real_T offset_rate210_UnitDelay_1;/* '<Root>/UnitDelay' */
extern real_T offset_rate210_Sum_1;    /* '<Root>/Sum' */

/* Model entry point functions */
extern void offset_rate210_initialize(void);
extern void offset_rate210_step(void);
extern void offset_rate210_terminate(void);

/* Real-time Model object */
extern RT_MODEL_offset_rate210_T *const offset_rate210_M;

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
 * '<Root>' : 'offset_rate210'
 */
#endif                                 /* RTW_HEADER_offset_rate210_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

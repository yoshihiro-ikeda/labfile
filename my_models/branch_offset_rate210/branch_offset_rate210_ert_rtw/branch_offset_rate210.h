/*
 * File: branch_offset_rate210.h
 *
 * Code generated for Simulink model 'branch_offset_rate210'.
 *
 * Model version                  : 1.23
 * Simulink Coder version         : 8.6 (R2014a) 27-Dec-2013
 * C/C++ source code generated on : Sat Dec 17 00:02:52 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Emulation hardware selection:
 *    Differs from embedded hardware (MATLAB Host)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_branch_offset_rate210_h_
#define RTW_HEADER_branch_offset_rate210_h_
#include <math.h>
#include <string.h>
#ifndef branch_offset_rate210_COMMON_INCLUDES_
# define branch_offset_rate210_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* branch_offset_rate210_COMMON_INCLUDES_ */

#include "branch_offset_rate210_types.h"
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
} DW_branch_offset_rate210_T;

/* Parameters (auto storage) */
struct P_branch_offset_rate210_T_ {
  real_T UnitDelay1_InitialCondition;  /* Expression: 2
                                        * Referenced by: '<Root>/UnitDelay1'
                                        */
  real_T Gain_Gain;                    /* Expression: 2
                                        * Referenced by: '<Root>/Gain'
                                        */
  real_T UnitDelay2_InitialCondition;  /* Expression: 1
                                        * Referenced by: '<Root>/UnitDelay2'
                                        */
  real_T Gain11_Gain;                  /* Expression: 1
                                        * Referenced by: '<S1>/Gain11'
                                        */
  real_T Gain_Gain_j;                  /* Expression: 1
                                        * Referenced by: '<S1>/Gain'
                                        */
  real_T Gain2_Gain;                   /* Expression: 1
                                        * Referenced by: '<S1>/Gain2'
                                        */
  real_T Gain1_Gain;                   /* Expression: 2
                                        * Referenced by: '<S1>/Gain1'
                                        */
  real_T Gain13_Gain;                  /* Expression: 1
                                        * Referenced by: '<S1>/Gain13'
                                        */
  real_T Gain12_Gain;                  /* Expression: 1
                                        * Referenced by: '<S1>/Gain12'
                                        */
  real_T Gain14_Gain;                  /* Expression: 1
                                        * Referenced by: '<S1>/Gain14'
                                        */
  real_T Gain26_Gain;                  /* Expression: 0.5
                                        * Referenced by: '<S1>/Gain26'
                                        */
  real_T Gain27_Gain;                  /* Expression: 2
                                        * Referenced by: '<S1>/Gain27'
                                        */
  real_T Gain22_Gain;                  /* Expression: 2
                                        * Referenced by: '<S1>/Gain22'
                                        */
  real_T Gain28_Gain;                  /* Expression: 0.5
                                        * Referenced by: '<S1>/Gain28'
                                        */
  real_T Gain23_Gain;                  /* Expression: 0.5
                                        * Referenced by: '<S1>/Gain23'
                                        */
  real_T Gain24_Gain;                  /* Expression: 2
                                        * Referenced by: '<S1>/Gain24'
                                        */
  real_T Gain25_Gain;                  /* Expression: 0.5
                                        * Referenced by: '<S1>/Gain25'
                                        */
  real_T Gain19_Gain;                  /* Expression: 0.5
                                        * Referenced by: '<S1>/Gain19'
                                        */
  real_T Gain20_Gain;                  /* Expression: 2
                                        * Referenced by: '<S1>/Gain20'
                                        */
  real_T Gain15_Gain;                  /* Expression: 2
                                        * Referenced by: '<S1>/Gain15'
                                        */
  real_T Gain21_Gain;                  /* Expression: 0.5
                                        * Referenced by: '<S1>/Gain21'
                                        */
  real_T Gain16_Gain;                  /* Expression: 0.5
                                        * Referenced by: '<S1>/Gain16'
                                        */
  real_T Gain17_Gain;                  /* Expression: 2
                                        * Referenced by: '<S1>/Gain17'
                                        */
  real_T Gain18_Gain;                  /* Expression: 0.5
                                        * Referenced by: '<S1>/Gain18'
                                        */
  real_T Gain3_Gain;                   /* Expression: 2
                                        * Referenced by: '<S1>/Gain3'
                                        */
  real_T Gain4_Gain;                   /* Expression: 0.5
                                        * Referenced by: '<S1>/Gain4'
                                        */
  real_T Gain5_Gain;                   /* Expression: 2
                                        * Referenced by: '<S1>/Gain5'
                                        */
  real_T Gain6_Gain;                   /* Expression: 0.5
                                        * Referenced by: '<S1>/Gain6'
                                        */
  real_T Gain7_Gain;                   /* Expression: 2
                                        * Referenced by: '<S1>/Gain7'
                                        */
  real_T Gain8_Gain;                   /* Expression: 0.5
                                        * Referenced by: '<S1>/Gain8'
                                        */
  real_T Gain9_Gain;                   /* Expression: 2
                                        * Referenced by: '<S1>/Gain9'
                                        */
  real_T Gain10_Gain;                  /* Expression: 0.5
                                        * Referenced by: '<S1>/Gain10'
                                        */
  real_T UnitDelay_InitialCondition;   /* Expression: 1
                                        * Referenced by: '<Root>/UnitDelay'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_branch_offset_rate210_T {
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
extern P_branch_offset_rate210_T branch_offset_rate210_P;

/* Block states (auto storage) */
extern DW_branch_offset_rate210_T branch_offset_rate210_DW;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern real_T branch_offset_rate210_UnitDelay1_1;/* '<Root>/UnitDelay1' */
extern real_T branch_offset_rate210_Gain_1;/* '<Root>/Gain' */
extern real_T branch_offset_rate210_UnitDelay2_1;/* '<Root>/UnitDelay2' */
extern real_T branch_offset_rate210_Subsystem_Sqrt1_1;/* '<S1>/Sqrt1' */
extern real_T branch_offset_rate210_Subsystem_Gain11_1;/* '<S1>/Gain11' */
extern real_T branch_offset_rate210_Subsystem_Gain_1;/* '<S1>/Gain' */
extern real_T branch_offset_rate210_Subsystem_Gain2_1;/* '<S1>/Gain2' */
extern real_T branch_offset_rate210_Subsystem_Add1_1;/* '<S1>/Add1' */
extern real_T branch_offset_rate210_Subsystem_MathFunction2_1;/* '<S1>/MathFunction2' */
extern real_T branch_offset_rate210_Subsystem_S_Function_1;/* '<S1>/S_Function' */
extern real_T branch_offset_rate210_Subsystem_Gain1_1;/* '<S1>/Gain1' */
extern real_T branch_offset_rate210_Subsystem_MathFunction1_1;/* '<S1>/MathFunction1' */
extern real_T branch_offset_rate210_Subsystem_Add_1;/* '<S1>/Add' */
extern real_T branch_offset_rate210_Subsystem_Sqrt2_1;/* '<S1>/Sqrt2' */
extern real_T branch_offset_rate210_Subsystem_Gain13_1;/* '<S1>/Gain13' */
extern real_T branch_offset_rate210_Subsystem_Gain12_1;/* '<S1>/Gain12' */
extern real_T branch_offset_rate210_Subsystem_Gain14_1;/* '<S1>/Gain14' */
extern real_T branch_offset_rate210_Subsystem_Add2_1;/* '<S1>/Add2' */
extern real_T branch_offset_rate210_Subsystem_MathFunction17_1;/* '<S1>/MathFunction17' */
extern real_T branch_offset_rate210_Subsystem_Gain26_1;/* '<S1>/Gain26' */
extern real_T branch_offset_rate210_Subsystem_Gain27_1;/* '<S1>/Gain27' */
extern real_T branch_offset_rate210_Subsystem_Gain22_1;/* '<S1>/Gain22' */
extern real_T branch_offset_rate210_Subsystem_MathFunction18_1;/* '<S1>/MathFunction18' */
extern real_T branch_offset_rate210_Subsystem_MathFunction15_1;/* '<S1>/MathFunction15' */
extern real_T branch_offset_rate210_Subsystem_Gain28_1;/* '<S1>/Gain28' */
extern real_T branch_offset_rate210_Subsystem_Gain23_1;/* '<S1>/Gain23' */
extern real_T branch_offset_rate210_Subsystem_Gain24_1;/* '<S1>/Gain24' */
extern real_T branch_offset_rate210_Subsystem_MathFunction16_1;/* '<S1>/MathFunction16' */
extern real_T branch_offset_rate210_Subsystem_Gain25_1;/* '<S1>/Gain25' */
extern real_T branch_offset_rate210_Subsystem_MathFunction13_1;/* '<S1>/MathFunction13' */
extern real_T branch_offset_rate210_Subsystem_Gain19_1;/* '<S1>/Gain19' */
extern real_T branch_offset_rate210_Subsystem_Gain20_1;/* '<S1>/Gain20' */
extern real_T branch_offset_rate210_Subsystem_Gain15_1;/* '<S1>/Gain15' */
extern real_T branch_offset_rate210_Subsystem_MathFunction14_1;/* '<S1>/MathFunction14' */
extern real_T branch_offset_rate210_Subsystem_MathFunction11_1;/* '<S1>/MathFunction11' */
extern real_T branch_offset_rate210_Subsystem_Gain21_1;/* '<S1>/Gain21' */
extern real_T branch_offset_rate210_Subsystem_Gain16_1;/* '<S1>/Gain16' */
extern real_T branch_offset_rate210_Subsystem_Gain17_1;/* '<S1>/Gain17' */
extern real_T branch_offset_rate210_Subsystem_MathFunction12_1;/* '<S1>/MathFunction12' */
extern real_T branch_offset_rate210_Subsystem_Gain18_1;/* '<S1>/Gain18' */
extern real_T branch_offset_rate210_Subsystem_Add4_1;/* '<S1>/Add4' */
extern real_T branch_offset_rate210_Subsystem_MathFunction4_1;/* '<S1>/MathFunction4' */
extern real_T branch_offset_rate210_Subsystem_S_Function1_1;/* '<S1>/S_Function1' */
extern real_T branch_offset_rate210_Subsystem_Gain3_1;/* '<S1>/Gain3' */
extern real_T branch_offset_rate210_Subsystem_MathFunction3_1;/* '<S1>/MathFunction3' */
extern real_T branch_offset_rate210_Subsystem_Gain4_1;/* '<S1>/Gain4' */
extern real_T branch_offset_rate210_Subsystem_Sqrt3_1;/* '<S1>/Sqrt3' */
extern real_T branch_offset_rate210_Subsystem_MathFunction6_1;/* '<S1>/MathFunction6' */
extern real_T branch_offset_rate210_Subsystem_S_Function2_1;/* '<S1>/S_Function2' */
extern real_T branch_offset_rate210_Subsystem_Gain5_1;/* '<S1>/Gain5' */
extern real_T branch_offset_rate210_Subsystem_MathFunction5_1;/* '<S1>/MathFunction5' */
extern real_T branch_offset_rate210_Subsystem_Gain6_1;/* '<S1>/Gain6' */
extern real_T branch_offset_rate210_Subsystem_Sqrt4_1;/* '<S1>/Sqrt4' */
extern real_T branch_offset_rate210_Subsystem_MathFunction8_1;/* '<S1>/MathFunction8' */
extern real_T branch_offset_rate210_Subsystem_S_Function3_1;/* '<S1>/S_Function3' */
extern real_T branch_offset_rate210_Subsystem_Gain7_1;/* '<S1>/Gain7' */
extern real_T branch_offset_rate210_Subsystem_MathFunction7_1;/* '<S1>/MathFunction7' */
extern real_T branch_offset_rate210_Subsystem_Gain8_1;/* '<S1>/Gain8' */
extern real_T branch_offset_rate210_Subsystem_Add3_1;/* '<S1>/Add3' */
extern real_T branch_offset_rate210_Subsystem_Sqrt5_1;/* '<S1>/Sqrt5' */
extern real_T branch_offset_rate210_Subsystem_MathFunction10_1;/* '<S1>/MathFunction10' */
extern real_T branch_offset_rate210_Subsystem_S_Function4_1;/* '<S1>/S_Function4' */
extern real_T branch_offset_rate210_Subsystem_Gain9_1;/* '<S1>/Gain9' */
extern real_T branch_offset_rate210_Subsystem_MathFunction9_1;/* '<S1>/MathFunction9' */
extern real_T branch_offset_rate210_Subsystem_Gain10_1;/* '<S1>/Gain10' */
extern real_T branch_offset_rate210_UnitDelay_1;/* '<Root>/UnitDelay' */
extern real_T branch_offset_rate210_Sum_1;/* '<Root>/Sum' */

/* Model entry point functions */
extern void branch_offset_rate210_initialize(void);
extern void branch_offset_rate210_step(void);
extern void branch_offset_rate210_terminate(void);

/* Real-time Model object */
extern RT_MODEL_branch_offset_rate21_T *const branch_offset_rate210_M;

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
 * '<Root>' : 'branch_offset_rate210'
 * '<S1>'   : 'branch_offset_rate210/Subsystem'
 */
#endif                                 /* RTW_HEADER_branch_offset_rate210_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

/*
 * File: offset_rate210.c
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

#include "offset_rate210.h"
#include "offset_rate210_private.h"

/* Exported block signals */
real_T offset_rate210_UnitDelay1_1;    /* '<Root>/UnitDelay1' */
real_T offset_rate210_Gain_1;          /* '<Root>/Gain' */
real_T offset_rate210_UnitDelay2_1;    /* '<Root>/UnitDelay2' */
real_T offset_rate210_Sqrt1_1;         /* '<Root>/Sqrt1' */
real_T offset_rate210_MathFunction2_1; /* '<Root>/MathFunction2' */
real_T offset_rate210_S_Function_1;    /* '<Root>/S_Function' */
real_T offset_rate210_Gain1_1;         /* '<Root>/Gain1' */
real_T offset_rate210_MathFunction1_1; /* '<Root>/MathFunction1' */
real_T offset_rate210_Gain2_1;         /* '<Root>/Gain2' */
real_T offset_rate210_Sqrt2_1;         /* '<Root>/Sqrt2' */
real_T offset_rate210_MathFunction4_1; /* '<Root>/MathFunction4' */
real_T offset_rate210_S_Function1_1;   /* '<Root>/S_Function1' */
real_T offset_rate210_Gain3_1;         /* '<Root>/Gain3' */
real_T offset_rate210_MathFunction3_1; /* '<Root>/MathFunction3' */
real_T offset_rate210_Gain4_1;         /* '<Root>/Gain4' */
real_T offset_rate210_Sqrt3_1;         /* '<Root>/Sqrt3' */
real_T offset_rate210_MathFunction6_1; /* '<Root>/MathFunction6' */
real_T offset_rate210_S_Function2_1;   /* '<Root>/S_Function2' */
real_T offset_rate210_Gain5_1;         /* '<Root>/Gain5' */
real_T offset_rate210_MathFunction5_1; /* '<Root>/MathFunction5' */
real_T offset_rate210_Gain6_1;         /* '<Root>/Gain6' */
real_T offset_rate210_Sqrt4_1;         /* '<Root>/Sqrt4' */
real_T offset_rate210_MathFunction8_1; /* '<Root>/MathFunction8' */
real_T offset_rate210_S_Function3_1;   /* '<Root>/S_Function3' */
real_T offset_rate210_Gain7_1;         /* '<Root>/Gain7' */
real_T offset_rate210_MathFunction7_1; /* '<Root>/MathFunction7' */
real_T offset_rate210_Gain8_1;         /* '<Root>/Gain8' */
real_T offset_rate210_Sqrt5_1;         /* '<Root>/Sqrt5' */
real_T offset_rate210_MathFunction10_1;/* '<Root>/MathFunction10' */
real_T offset_rate210_S_Function4_1;   /* '<Root>/S_Function4' */
real_T offset_rate210_Gain9_1;         /* '<Root>/Gain9' */
real_T offset_rate210_MathFunction9_1; /* '<Root>/MathFunction9' */
real_T offset_rate210_Gain10_1;        /* '<Root>/Gain10' */
real_T offset_rate210_UnitDelay_1;     /* '<Root>/UnitDelay' */
real_T offset_rate210_Sum_1;           /* '<Root>/Sum' */

/* Block states (auto storage) */
DW_offset_rate210_T offset_rate210_DW;

/* Real-time model */
RT_MODEL_offset_rate210_T offset_rate210_M_;
RT_MODEL_offset_rate210_T *const offset_rate210_M = &offset_rate210_M_;
static void rate_scheduler(void);

/*
 *   This function updates active task flag for each subrate.
 * The function is called at model base rate, hence the
 * generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   *
   * Sample time offsets are handled by priming the counter with the
   * appropriate non-zero value in the model's initialization function.
   */
  (offset_rate210_M->Timing.TaskCounters.TID[1])++;
  if ((offset_rate210_M->Timing.TaskCounters.TID[1]) > 4) {/* Sample time: [0.01s, 0.0s] */
    offset_rate210_M->Timing.TaskCounters.TID[1] = 0;
  }

  (offset_rate210_M->Timing.TaskCounters.TID[2])++;
  if ((offset_rate210_M->Timing.TaskCounters.TID[2]) > 4) {/* Sample time: [0.01s, 0.002s] */
    offset_rate210_M->Timing.TaskCounters.TID[2] = 0;
  }

  (offset_rate210_M->Timing.TaskCounters.TID[3])++;
  if ((offset_rate210_M->Timing.TaskCounters.TID[3]) > 4) {/* Sample time: [0.01s, 0.004s] */
    offset_rate210_M->Timing.TaskCounters.TID[3] = 0;
  }

  (offset_rate210_M->Timing.TaskCounters.TID[4])++;
  if ((offset_rate210_M->Timing.TaskCounters.TID[4]) > 4) {/* Sample time: [0.01s, 0.006s] */
    offset_rate210_M->Timing.TaskCounters.TID[4] = 0;
  }

  (offset_rate210_M->Timing.TaskCounters.TID[5])++;
  if ((offset_rate210_M->Timing.TaskCounters.TID[5]) > 4) {/* Sample time: [0.01s, 0.008s] */
    offset_rate210_M->Timing.TaskCounters.TID[5] = 0;
  }
}

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T tmp;
  real_T tmp_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    tmp = fabs(u0);
    tmp_0 = fabs(u1);
    if (rtIsInf(u1)) {
      if (tmp == 1.0) {
        y = (rtNaN);
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = (rtNaN);
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

/* Model step function */
void offset_rate210_step(void)
{
  /* UnitDelay: '<Root>/UnitDelay1' */
  offset_rate210_UnitDelay1_1 = offset_rate210_DW.UnitDelay1_DSTATE;

  /* Gain: '<Root>/Gain' */
  offset_rate210_Gain_1 = offset_rate210_P.Gain_Gain *
    offset_rate210_UnitDelay1_1;

  /* UnitDelay: '<Root>/UnitDelay2' */
  offset_rate210_UnitDelay2_1 = offset_rate210_DW.UnitDelay2_DSTATE;
  if (offset_rate210_M->Timing.TaskCounters.TID[1] == 0) {
    /* Sqrt: '<Root>/Sqrt1' */
    offset_rate210_Sqrt1_1 = sqrt(offset_rate210_UnitDelay2_1);

    /* Math: '<Root>/MathFunction2'
     *
     * About '<Root>/MathFunction2':
     *  Operator: log10
     */
    offset_rate210_MathFunction2_1 = log10(offset_rate210_Sqrt1_1);

    /* S-Function (loop): '<Root>/S_Function' */
    loop_Outputs_wrapper(&offset_rate210_MathFunction2_1,
                         &offset_rate210_S_Function_1 );

    /* Gain: '<Root>/Gain1' */
    offset_rate210_Gain1_1 = offset_rate210_P.Gain1_Gain *
      offset_rate210_S_Function_1;

    /* Math: '<Root>/MathFunction1' */
    offset_rate210_MathFunction1_1 = rt_powd_snf(10.0, offset_rate210_Gain1_1);

    /* Gain: '<Root>/Gain2' */
    offset_rate210_Gain2_1 = offset_rate210_P.Gain2_Gain *
      offset_rate210_MathFunction1_1;
  }

  if (offset_rate210_M->Timing.TaskCounters.TID[2] == 0) {
    /* Sqrt: '<Root>/Sqrt2' */
    offset_rate210_Sqrt2_1 = sqrt(offset_rate210_Gain2_1);

    /* Math: '<Root>/MathFunction4'
     *
     * About '<Root>/MathFunction4':
     *  Operator: log10
     */
    offset_rate210_MathFunction4_1 = log10(offset_rate210_Sqrt2_1);

    /* S-Function (loop): '<Root>/S_Function1' */
    loop_Outputs_wrapper(&offset_rate210_MathFunction4_1,
                         &offset_rate210_S_Function1_1 );

    /* Gain: '<Root>/Gain3' */
    offset_rate210_Gain3_1 = offset_rate210_P.Gain3_Gain *
      offset_rate210_S_Function1_1;

    /* Math: '<Root>/MathFunction3' */
    offset_rate210_MathFunction3_1 = rt_powd_snf(10.0, offset_rate210_Gain3_1);

    /* Gain: '<Root>/Gain4' */
    offset_rate210_Gain4_1 = offset_rate210_P.Gain4_Gain *
      offset_rate210_MathFunction3_1;
  }

  if (offset_rate210_M->Timing.TaskCounters.TID[3] == 0) {
    /* Sqrt: '<Root>/Sqrt3' */
    offset_rate210_Sqrt3_1 = sqrt(offset_rate210_Gain4_1);

    /* Math: '<Root>/MathFunction6'
     *
     * About '<Root>/MathFunction6':
     *  Operator: log10
     */
    offset_rate210_MathFunction6_1 = log10(offset_rate210_Sqrt3_1);

    /* S-Function (loop): '<Root>/S_Function2' */
    loop_Outputs_wrapper(&offset_rate210_MathFunction6_1,
                         &offset_rate210_S_Function2_1 );

    /* Gain: '<Root>/Gain5' */
    offset_rate210_Gain5_1 = offset_rate210_P.Gain5_Gain *
      offset_rate210_S_Function2_1;

    /* Math: '<Root>/MathFunction5' */
    offset_rate210_MathFunction5_1 = rt_powd_snf(10.0, offset_rate210_Gain5_1);

    /* Gain: '<Root>/Gain6' */
    offset_rate210_Gain6_1 = offset_rate210_P.Gain6_Gain *
      offset_rate210_MathFunction5_1;
  }

  if (offset_rate210_M->Timing.TaskCounters.TID[4] == 0) {
    /* Sqrt: '<Root>/Sqrt4' */
    offset_rate210_Sqrt4_1 = sqrt(offset_rate210_Gain6_1);

    /* Math: '<Root>/MathFunction8'
     *
     * About '<Root>/MathFunction8':
     *  Operator: log10
     */
    offset_rate210_MathFunction8_1 = log10(offset_rate210_Sqrt4_1);

    /* S-Function (loop): '<Root>/S_Function3' */
    loop_Outputs_wrapper(&offset_rate210_MathFunction8_1,
                         &offset_rate210_S_Function3_1 );

    /* Gain: '<Root>/Gain7' */
    offset_rate210_Gain7_1 = offset_rate210_P.Gain7_Gain *
      offset_rate210_S_Function3_1;

    /* Math: '<Root>/MathFunction7' */
    offset_rate210_MathFunction7_1 = rt_powd_snf(10.0, offset_rate210_Gain7_1);

    /* Gain: '<Root>/Gain8' */
    offset_rate210_Gain8_1 = offset_rate210_P.Gain8_Gain *
      offset_rate210_MathFunction7_1;
  }

  if (offset_rate210_M->Timing.TaskCounters.TID[5] == 0) {
    /* Sqrt: '<Root>/Sqrt5' */
    offset_rate210_Sqrt5_1 = sqrt(offset_rate210_Gain8_1);

    /* Math: '<Root>/MathFunction10'
     *
     * About '<Root>/MathFunction10':
     *  Operator: log10
     */
    offset_rate210_MathFunction10_1 = log10(offset_rate210_Sqrt5_1);

    /* S-Function (loop): '<Root>/S_Function4' */
    loop_Outputs_wrapper(&offset_rate210_MathFunction10_1,
                         &offset_rate210_S_Function4_1 );

    /* Gain: '<Root>/Gain9' */
    offset_rate210_Gain9_1 = offset_rate210_P.Gain9_Gain *
      offset_rate210_S_Function4_1;

    /* Math: '<Root>/MathFunction9' */
    offset_rate210_MathFunction9_1 = rt_powd_snf(10.0, offset_rate210_Gain9_1);

    /* Gain: '<Root>/Gain10' */
    offset_rate210_Gain10_1 = offset_rate210_P.Gain10_Gain *
      offset_rate210_MathFunction9_1;

    /* UnitDelay: '<Root>/UnitDelay' */
    offset_rate210_UnitDelay_1 = offset_rate210_DW.UnitDelay_DSTATE;
  }

  /* Sum: '<Root>/Sum' */
  offset_rate210_Sum_1 = offset_rate210_UnitDelay_1 + offset_rate210_Gain_1;

  /* Update for UnitDelay: '<Root>/UnitDelay1' */
  offset_rate210_DW.UnitDelay1_DSTATE = offset_rate210_Sum_1;

  /* Update for UnitDelay: '<Root>/UnitDelay2' */
  offset_rate210_DW.UnitDelay2_DSTATE = offset_rate210_Gain_1;
  if (offset_rate210_M->Timing.TaskCounters.TID[5] == 0) {
    /* Update for UnitDelay: '<Root>/UnitDelay' */
    offset_rate210_DW.UnitDelay_DSTATE = offset_rate210_Gain10_1;
  }

  rate_scheduler();
}

/* Model initialize function */
void offset_rate210_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)offset_rate210_M, 0,
                sizeof(RT_MODEL_offset_rate210_T));

  /* initialize sample time offsets */
  offset_rate210_M->Timing.TaskCounters.TID[2] = 4;/* Sample time: [0.01s, 0.002s] */

  /* initialize sample time offsets */
  offset_rate210_M->Timing.TaskCounters.TID[3] = 3;/* Sample time: [0.01s, 0.004s] */

  /* initialize sample time offsets */
  offset_rate210_M->Timing.TaskCounters.TID[4] = 2;/* Sample time: [0.01s, 0.006s] */

  /* initialize sample time offsets */
  offset_rate210_M->Timing.TaskCounters.TID[5] = 1;/* Sample time: [0.01s, 0.008s] */

  /* block I/O */

  /* exported global signals */
  offset_rate210_UnitDelay1_1 = 0.0;
  offset_rate210_Gain_1 = 0.0;
  offset_rate210_UnitDelay2_1 = 0.0;
  offset_rate210_Sqrt1_1 = 0.0;
  offset_rate210_MathFunction2_1 = 0.0;
  offset_rate210_S_Function_1 = 0.0;
  offset_rate210_Gain1_1 = 0.0;
  offset_rate210_MathFunction1_1 = 0.0;
  offset_rate210_Gain2_1 = 0.0;
  offset_rate210_Sqrt2_1 = 0.0;
  offset_rate210_MathFunction4_1 = 0.0;
  offset_rate210_S_Function1_1 = 0.0;
  offset_rate210_Gain3_1 = 0.0;
  offset_rate210_MathFunction3_1 = 0.0;
  offset_rate210_Gain4_1 = 0.0;
  offset_rate210_Sqrt3_1 = 0.0;
  offset_rate210_MathFunction6_1 = 0.0;
  offset_rate210_S_Function2_1 = 0.0;
  offset_rate210_Gain5_1 = 0.0;
  offset_rate210_MathFunction5_1 = 0.0;
  offset_rate210_Gain6_1 = 0.0;
  offset_rate210_Sqrt4_1 = 0.0;
  offset_rate210_MathFunction8_1 = 0.0;
  offset_rate210_S_Function3_1 = 0.0;
  offset_rate210_Gain7_1 = 0.0;
  offset_rate210_MathFunction7_1 = 0.0;
  offset_rate210_Gain8_1 = 0.0;
  offset_rate210_Sqrt5_1 = 0.0;
  offset_rate210_MathFunction10_1 = 0.0;
  offset_rate210_S_Function4_1 = 0.0;
  offset_rate210_Gain9_1 = 0.0;
  offset_rate210_MathFunction9_1 = 0.0;
  offset_rate210_Gain10_1 = 0.0;
  offset_rate210_UnitDelay_1 = 0.0;
  offset_rate210_Sum_1 = 0.0;

  /* states (dwork) */
  (void) memset((void *)&offset_rate210_DW, 0,
                sizeof(DW_offset_rate210_T));

  /* InitializeConditions for UnitDelay: '<Root>/UnitDelay1' */
  offset_rate210_DW.UnitDelay1_DSTATE =
    offset_rate210_P.UnitDelay1_InitialCondition;

  /* InitializeConditions for UnitDelay: '<Root>/UnitDelay2' */
  offset_rate210_DW.UnitDelay2_DSTATE =
    offset_rate210_P.UnitDelay2_InitialCondition;

  /* InitializeConditions for UnitDelay: '<Root>/UnitDelay' */
  offset_rate210_DW.UnitDelay_DSTATE =
    offset_rate210_P.UnitDelay_InitialCondition;
}

/* Model terminate function */
void offset_rate210_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

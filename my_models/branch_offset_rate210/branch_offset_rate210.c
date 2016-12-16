/*
 * File: branch_offset_rate210.c
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

#include "branch_offset_rate210.h"
#include "branch_offset_rate210_private.h"

/* Exported block signals */
real_T branch_offset_rate210_UnitDelay1_1;/* '<Root>/UnitDelay1' */
real_T branch_offset_rate210_Gain_1;   /* '<Root>/Gain' */
real_T branch_offset_rate210_UnitDelay2_1;/* '<Root>/UnitDelay2' */
real_T branch_offset_rate210_Subsystem_Sqrt1_1;/* '<S1>/Sqrt1' */
real_T branch_offset_rate210_Subsystem_Gain11_1;/* '<S1>/Gain11' */
real_T branch_offset_rate210_Subsystem_Gain_1;/* '<S1>/Gain' */
real_T branch_offset_rate210_Subsystem_Gain2_1;/* '<S1>/Gain2' */
real_T branch_offset_rate210_Subsystem_Add1_1;/* '<S1>/Add1' */
real_T branch_offset_rate210_Subsystem_MathFunction2_1;/* '<S1>/MathFunction2' */
real_T branch_offset_rate210_Subsystem_S_Function_1;/* '<S1>/S_Function' */
real_T branch_offset_rate210_Subsystem_Gain1_1;/* '<S1>/Gain1' */
real_T branch_offset_rate210_Subsystem_MathFunction1_1;/* '<S1>/MathFunction1' */
real_T branch_offset_rate210_Subsystem_Add_1;/* '<S1>/Add' */
real_T branch_offset_rate210_Subsystem_Sqrt2_1;/* '<S1>/Sqrt2' */
real_T branch_offset_rate210_Subsystem_Gain13_1;/* '<S1>/Gain13' */
real_T branch_offset_rate210_Subsystem_Gain12_1;/* '<S1>/Gain12' */
real_T branch_offset_rate210_Subsystem_Gain14_1;/* '<S1>/Gain14' */
real_T branch_offset_rate210_Subsystem_Add2_1;/* '<S1>/Add2' */
real_T branch_offset_rate210_Subsystem_MathFunction17_1;/* '<S1>/MathFunction17' */
real_T branch_offset_rate210_Subsystem_Gain26_1;/* '<S1>/Gain26' */
real_T branch_offset_rate210_Subsystem_Gain27_1;/* '<S1>/Gain27' */
real_T branch_offset_rate210_Subsystem_Gain22_1;/* '<S1>/Gain22' */
real_T branch_offset_rate210_Subsystem_MathFunction18_1;/* '<S1>/MathFunction18' */
real_T branch_offset_rate210_Subsystem_MathFunction15_1;/* '<S1>/MathFunction15' */
real_T branch_offset_rate210_Subsystem_Gain28_1;/* '<S1>/Gain28' */
real_T branch_offset_rate210_Subsystem_Gain23_1;/* '<S1>/Gain23' */
real_T branch_offset_rate210_Subsystem_Gain24_1;/* '<S1>/Gain24' */
real_T branch_offset_rate210_Subsystem_MathFunction16_1;/* '<S1>/MathFunction16' */
real_T branch_offset_rate210_Subsystem_Gain25_1;/* '<S1>/Gain25' */
real_T branch_offset_rate210_Subsystem_MathFunction13_1;/* '<S1>/MathFunction13' */
real_T branch_offset_rate210_Subsystem_Gain19_1;/* '<S1>/Gain19' */
real_T branch_offset_rate210_Subsystem_Gain20_1;/* '<S1>/Gain20' */
real_T branch_offset_rate210_Subsystem_Gain15_1;/* '<S1>/Gain15' */
real_T branch_offset_rate210_Subsystem_MathFunction14_1;/* '<S1>/MathFunction14' */
real_T branch_offset_rate210_Subsystem_MathFunction11_1;/* '<S1>/MathFunction11' */
real_T branch_offset_rate210_Subsystem_Gain21_1;/* '<S1>/Gain21' */
real_T branch_offset_rate210_Subsystem_Gain16_1;/* '<S1>/Gain16' */
real_T branch_offset_rate210_Subsystem_Gain17_1;/* '<S1>/Gain17' */
real_T branch_offset_rate210_Subsystem_MathFunction12_1;/* '<S1>/MathFunction12' */
real_T branch_offset_rate210_Subsystem_Gain18_1;/* '<S1>/Gain18' */
real_T branch_offset_rate210_Subsystem_Add4_1;/* '<S1>/Add4' */
real_T branch_offset_rate210_Subsystem_MathFunction4_1;/* '<S1>/MathFunction4' */
real_T branch_offset_rate210_Subsystem_S_Function1_1;/* '<S1>/S_Function1' */
real_T branch_offset_rate210_Subsystem_Gain3_1;/* '<S1>/Gain3' */
real_T branch_offset_rate210_Subsystem_MathFunction3_1;/* '<S1>/MathFunction3' */
real_T branch_offset_rate210_Subsystem_Gain4_1;/* '<S1>/Gain4' */
real_T branch_offset_rate210_Subsystem_Sqrt3_1;/* '<S1>/Sqrt3' */
real_T branch_offset_rate210_Subsystem_MathFunction6_1;/* '<S1>/MathFunction6' */
real_T branch_offset_rate210_Subsystem_S_Function2_1;/* '<S1>/S_Function2' */
real_T branch_offset_rate210_Subsystem_Gain5_1;/* '<S1>/Gain5' */
real_T branch_offset_rate210_Subsystem_MathFunction5_1;/* '<S1>/MathFunction5' */
real_T branch_offset_rate210_Subsystem_Gain6_1;/* '<S1>/Gain6' */
real_T branch_offset_rate210_Subsystem_Sqrt4_1;/* '<S1>/Sqrt4' */
real_T branch_offset_rate210_Subsystem_MathFunction8_1;/* '<S1>/MathFunction8' */
real_T branch_offset_rate210_Subsystem_S_Function3_1;/* '<S1>/S_Function3' */
real_T branch_offset_rate210_Subsystem_Gain7_1;/* '<S1>/Gain7' */
real_T branch_offset_rate210_Subsystem_MathFunction7_1;/* '<S1>/MathFunction7' */
real_T branch_offset_rate210_Subsystem_Gain8_1;/* '<S1>/Gain8' */
real_T branch_offset_rate210_Subsystem_Add3_1;/* '<S1>/Add3' */
real_T branch_offset_rate210_Subsystem_Sqrt5_1;/* '<S1>/Sqrt5' */
real_T branch_offset_rate210_Subsystem_MathFunction10_1;/* '<S1>/MathFunction10' */
real_T branch_offset_rate210_Subsystem_S_Function4_1;/* '<S1>/S_Function4' */
real_T branch_offset_rate210_Subsystem_Gain9_1;/* '<S1>/Gain9' */
real_T branch_offset_rate210_Subsystem_MathFunction9_1;/* '<S1>/MathFunction9' */
real_T branch_offset_rate210_Subsystem_Gain10_1;/* '<S1>/Gain10' */
real_T branch_offset_rate210_UnitDelay_1;/* '<Root>/UnitDelay' */
real_T branch_offset_rate210_Sum_1;    /* '<Root>/Sum' */

/* Block states (auto storage) */
DW_branch_offset_rate210_T branch_offset_rate210_DW;

/* Real-time model */
RT_MODEL_branch_offset_rate21_T branch_offset_rate210_M_;
RT_MODEL_branch_offset_rate21_T *const branch_offset_rate210_M =
  &branch_offset_rate210_M_;
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
  (branch_offset_rate210_M->Timing.TaskCounters.TID[1])++;
  if ((branch_offset_rate210_M->Timing.TaskCounters.TID[1]) > 4) {/* Sample time: [0.01s, 0.0s] */
    branch_offset_rate210_M->Timing.TaskCounters.TID[1] = 0;
  }

  (branch_offset_rate210_M->Timing.TaskCounters.TID[2])++;
  if ((branch_offset_rate210_M->Timing.TaskCounters.TID[2]) > 4) {/* Sample time: [0.01s, 0.002s] */
    branch_offset_rate210_M->Timing.TaskCounters.TID[2] = 0;
  }

  (branch_offset_rate210_M->Timing.TaskCounters.TID[3])++;
  if ((branch_offset_rate210_M->Timing.TaskCounters.TID[3]) > 4) {/* Sample time: [0.01s, 0.004s] */
    branch_offset_rate210_M->Timing.TaskCounters.TID[3] = 0;
  }

  (branch_offset_rate210_M->Timing.TaskCounters.TID[4])++;
  if ((branch_offset_rate210_M->Timing.TaskCounters.TID[4]) > 4) {/* Sample time: [0.01s, 0.006s] */
    branch_offset_rate210_M->Timing.TaskCounters.TID[4] = 0;
  }

  (branch_offset_rate210_M->Timing.TaskCounters.TID[5])++;
  if ((branch_offset_rate210_M->Timing.TaskCounters.TID[5]) > 4) {/* Sample time: [0.01s, 0.008s] */
    branch_offset_rate210_M->Timing.TaskCounters.TID[5] = 0;
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
void branch_offset_rate210_step(void)
{
  /* UnitDelay: '<Root>/UnitDelay1' */
  branch_offset_rate210_UnitDelay1_1 =
    branch_offset_rate210_DW.UnitDelay1_DSTATE;

  /* Gain: '<Root>/Gain' */
  branch_offset_rate210_Gain_1 = branch_offset_rate210_P.Gain_Gain *
    branch_offset_rate210_UnitDelay1_1;

  /* UnitDelay: '<Root>/UnitDelay2' */
  branch_offset_rate210_UnitDelay2_1 =
    branch_offset_rate210_DW.UnitDelay2_DSTATE;
  if (branch_offset_rate210_M->Timing.TaskCounters.TID[1] == 0) {
    /* Sqrt: '<S1>/Sqrt1' */
    branch_offset_rate210_Subsystem_Sqrt1_1 = sqrt
      (branch_offset_rate210_UnitDelay2_1);

    /* Gain: '<S1>/Gain11' */
    branch_offset_rate210_Subsystem_Gain11_1 =
      branch_offset_rate210_P.Gain11_Gain *
      branch_offset_rate210_Subsystem_Sqrt1_1;

    /* Gain: '<S1>/Gain' */
    branch_offset_rate210_Subsystem_Gain_1 = branch_offset_rate210_P.Gain_Gain_j
      * branch_offset_rate210_Subsystem_Sqrt1_1;

    /* Gain: '<S1>/Gain2' */
    branch_offset_rate210_Subsystem_Gain2_1 = branch_offset_rate210_P.Gain2_Gain
      * branch_offset_rate210_Subsystem_Gain_1;

    /* Sum: '<S1>/Add1' */
    branch_offset_rate210_Subsystem_Add1_1 =
      branch_offset_rate210_Subsystem_Gain11_1 +
      branch_offset_rate210_Subsystem_Gain2_1;

    /* Math: '<S1>/MathFunction2'
     *
     * About '<S1>/MathFunction2':
     *  Operator: log10
     */
    branch_offset_rate210_Subsystem_MathFunction2_1 = log10
      (branch_offset_rate210_Subsystem_Sqrt1_1);

    /* S-Function (loop): '<S1>/S_Function' */
    loop_Outputs_wrapper(&branch_offset_rate210_Subsystem_MathFunction2_1,
                         &branch_offset_rate210_Subsystem_S_Function_1 );

    /* Gain: '<S1>/Gain1' */
    branch_offset_rate210_Subsystem_Gain1_1 = branch_offset_rate210_P.Gain1_Gain
      * branch_offset_rate210_Subsystem_S_Function_1;

    /* Math: '<S1>/MathFunction1' */
    branch_offset_rate210_Subsystem_MathFunction1_1 = rt_powd_snf(10.0,
      branch_offset_rate210_Subsystem_Gain1_1);

    /* Sum: '<S1>/Add' */
    branch_offset_rate210_Subsystem_Add_1 =
      branch_offset_rate210_Subsystem_Add1_1 +
      branch_offset_rate210_Subsystem_MathFunction1_1;
  }

  if (branch_offset_rate210_M->Timing.TaskCounters.TID[2] == 0) {
    /* Sqrt: '<S1>/Sqrt2' */
    branch_offset_rate210_Subsystem_Sqrt2_1 = sqrt
      (branch_offset_rate210_Subsystem_Add_1);
  }

  if (branch_offset_rate210_M->Timing.TaskCounters.TID[1] == 0) {
    /* Gain: '<S1>/Gain13' */
    branch_offset_rate210_Subsystem_Gain13_1 =
      branch_offset_rate210_P.Gain13_Gain *
      branch_offset_rate210_Subsystem_Sqrt2_1;

    /* Gain: '<S1>/Gain12' */
    branch_offset_rate210_Subsystem_Gain12_1 =
      branch_offset_rate210_P.Gain12_Gain *
      branch_offset_rate210_Subsystem_Sqrt2_1;

    /* Gain: '<S1>/Gain14' */
    branch_offset_rate210_Subsystem_Gain14_1 =
      branch_offset_rate210_P.Gain14_Gain *
      branch_offset_rate210_Subsystem_Gain12_1;

    /* Sum: '<S1>/Add2' */
    branch_offset_rate210_Subsystem_Add2_1 =
      branch_offset_rate210_Subsystem_Gain13_1 +
      branch_offset_rate210_Subsystem_Gain14_1;
  }

  if (branch_offset_rate210_M->Timing.TaskCounters.TID[4] == 0) {
    /* Math: '<S1>/MathFunction17' */
    branch_offset_rate210_Subsystem_MathFunction17_1 = rt_powd_snf(10.0,
      branch_offset_rate210_Subsystem_Add2_1);

    /* Gain: '<S1>/Gain26' */
    branch_offset_rate210_Subsystem_Gain26_1 =
      branch_offset_rate210_P.Gain26_Gain *
      branch_offset_rate210_Subsystem_MathFunction17_1;

    /* Gain: '<S1>/Gain27' */
    branch_offset_rate210_Subsystem_Gain27_1 =
      branch_offset_rate210_P.Gain27_Gain *
      branch_offset_rate210_Subsystem_Gain26_1;

    /* Gain: '<S1>/Gain22' */
    branch_offset_rate210_Subsystem_Gain22_1 =
      branch_offset_rate210_P.Gain22_Gain *
      branch_offset_rate210_Subsystem_Gain27_1;

    /* Math: '<S1>/MathFunction18' */
    branch_offset_rate210_Subsystem_MathFunction18_1 = rt_powd_snf(10.0,
      branch_offset_rate210_Subsystem_Gain22_1);

    /* Math: '<S1>/MathFunction15' */
    branch_offset_rate210_Subsystem_MathFunction15_1 = rt_powd_snf(10.0,
      branch_offset_rate210_Subsystem_MathFunction18_1);

    /* Gain: '<S1>/Gain28' */
    branch_offset_rate210_Subsystem_Gain28_1 =
      branch_offset_rate210_P.Gain28_Gain *
      branch_offset_rate210_Subsystem_MathFunction15_1;

    /* Gain: '<S1>/Gain23' */
    branch_offset_rate210_Subsystem_Gain23_1 =
      branch_offset_rate210_P.Gain23_Gain *
      branch_offset_rate210_Subsystem_Gain28_1;

    /* Gain: '<S1>/Gain24' */
    branch_offset_rate210_Subsystem_Gain24_1 =
      branch_offset_rate210_P.Gain24_Gain *
      branch_offset_rate210_Subsystem_Gain23_1;

    /* Math: '<S1>/MathFunction16' */
    branch_offset_rate210_Subsystem_MathFunction16_1 = rt_powd_snf(10.0,
      branch_offset_rate210_Subsystem_Gain24_1);

    /* Gain: '<S1>/Gain25' */
    branch_offset_rate210_Subsystem_Gain25_1 =
      branch_offset_rate210_P.Gain25_Gain *
      branch_offset_rate210_Subsystem_MathFunction16_1;

    /* Math: '<S1>/MathFunction13' */
    branch_offset_rate210_Subsystem_MathFunction13_1 = rt_powd_snf(10.0,
      branch_offset_rate210_Subsystem_Add2_1);

    /* Gain: '<S1>/Gain19' */
    branch_offset_rate210_Subsystem_Gain19_1 =
      branch_offset_rate210_P.Gain19_Gain *
      branch_offset_rate210_Subsystem_MathFunction13_1;

    /* Gain: '<S1>/Gain20' */
    branch_offset_rate210_Subsystem_Gain20_1 =
      branch_offset_rate210_P.Gain20_Gain *
      branch_offset_rate210_Subsystem_Gain19_1;

    /* Gain: '<S1>/Gain15' */
    branch_offset_rate210_Subsystem_Gain15_1 =
      branch_offset_rate210_P.Gain15_Gain *
      branch_offset_rate210_Subsystem_Gain20_1;

    /* Math: '<S1>/MathFunction14' */
    branch_offset_rate210_Subsystem_MathFunction14_1 = rt_powd_snf(10.0,
      branch_offset_rate210_Subsystem_Gain15_1);

    /* Math: '<S1>/MathFunction11' */
    branch_offset_rate210_Subsystem_MathFunction11_1 = rt_powd_snf(10.0,
      branch_offset_rate210_Subsystem_MathFunction14_1);

    /* Gain: '<S1>/Gain21' */
    branch_offset_rate210_Subsystem_Gain21_1 =
      branch_offset_rate210_P.Gain21_Gain *
      branch_offset_rate210_Subsystem_MathFunction11_1;

    /* Gain: '<S1>/Gain16' */
    branch_offset_rate210_Subsystem_Gain16_1 =
      branch_offset_rate210_P.Gain16_Gain *
      branch_offset_rate210_Subsystem_Gain21_1;

    /* Gain: '<S1>/Gain17' */
    branch_offset_rate210_Subsystem_Gain17_1 =
      branch_offset_rate210_P.Gain17_Gain *
      branch_offset_rate210_Subsystem_Gain16_1;

    /* Math: '<S1>/MathFunction12' */
    branch_offset_rate210_Subsystem_MathFunction12_1 = rt_powd_snf(10.0,
      branch_offset_rate210_Subsystem_Gain17_1);

    /* Gain: '<S1>/Gain18' */
    branch_offset_rate210_Subsystem_Gain18_1 =
      branch_offset_rate210_P.Gain18_Gain *
      branch_offset_rate210_Subsystem_MathFunction12_1;
  }

  if (branch_offset_rate210_M->Timing.TaskCounters.TID[1] == 0) {
    /* Sum: '<S1>/Add4' */
    branch_offset_rate210_Subsystem_Add4_1 =
      branch_offset_rate210_Subsystem_Gain25_1 +
      branch_offset_rate210_Subsystem_Gain18_1;
  }

  if (branch_offset_rate210_M->Timing.TaskCounters.TID[2] == 0) {
    /* Math: '<S1>/MathFunction4'
     *
     * About '<S1>/MathFunction4':
     *  Operator: log10
     */
    branch_offset_rate210_Subsystem_MathFunction4_1 = log10
      (branch_offset_rate210_Subsystem_Sqrt2_1);

    /* S-Function (loop): '<S1>/S_Function1' */
    loop_Outputs_wrapper(&branch_offset_rate210_Subsystem_MathFunction4_1,
                         &branch_offset_rate210_Subsystem_S_Function1_1 );

    /* Gain: '<S1>/Gain3' */
    branch_offset_rate210_Subsystem_Gain3_1 = branch_offset_rate210_P.Gain3_Gain
      * branch_offset_rate210_Subsystem_S_Function1_1;

    /* Math: '<S1>/MathFunction3' */
    branch_offset_rate210_Subsystem_MathFunction3_1 = rt_powd_snf(10.0,
      branch_offset_rate210_Subsystem_Gain3_1);

    /* Gain: '<S1>/Gain4' */
    branch_offset_rate210_Subsystem_Gain4_1 = branch_offset_rate210_P.Gain4_Gain
      * branch_offset_rate210_Subsystem_MathFunction3_1;
  }

  if (branch_offset_rate210_M->Timing.TaskCounters.TID[3] == 0) {
    /* Sqrt: '<S1>/Sqrt3' */
    branch_offset_rate210_Subsystem_Sqrt3_1 = sqrt
      (branch_offset_rate210_Subsystem_Gain4_1);

    /* Math: '<S1>/MathFunction6'
     *
     * About '<S1>/MathFunction6':
     *  Operator: log10
     */
    branch_offset_rate210_Subsystem_MathFunction6_1 = log10
      (branch_offset_rate210_Subsystem_Sqrt3_1);

    /* S-Function (loop): '<S1>/S_Function2' */
    loop_Outputs_wrapper(&branch_offset_rate210_Subsystem_MathFunction6_1,
                         &branch_offset_rate210_Subsystem_S_Function2_1 );

    /* Gain: '<S1>/Gain5' */
    branch_offset_rate210_Subsystem_Gain5_1 = branch_offset_rate210_P.Gain5_Gain
      * branch_offset_rate210_Subsystem_S_Function2_1;

    /* Math: '<S1>/MathFunction5' */
    branch_offset_rate210_Subsystem_MathFunction5_1 = rt_powd_snf(10.0,
      branch_offset_rate210_Subsystem_Gain5_1);

    /* Gain: '<S1>/Gain6' */
    branch_offset_rate210_Subsystem_Gain6_1 = branch_offset_rate210_P.Gain6_Gain
      * branch_offset_rate210_Subsystem_MathFunction5_1;
  }

  if (branch_offset_rate210_M->Timing.TaskCounters.TID[4] == 0) {
    /* Sqrt: '<S1>/Sqrt4' */
    branch_offset_rate210_Subsystem_Sqrt4_1 = sqrt
      (branch_offset_rate210_Subsystem_Gain6_1);

    /* Math: '<S1>/MathFunction8'
     *
     * About '<S1>/MathFunction8':
     *  Operator: log10
     */
    branch_offset_rate210_Subsystem_MathFunction8_1 = log10
      (branch_offset_rate210_Subsystem_Sqrt4_1);

    /* S-Function (loop): '<S1>/S_Function3' */
    loop_Outputs_wrapper(&branch_offset_rate210_Subsystem_MathFunction8_1,
                         &branch_offset_rate210_Subsystem_S_Function3_1 );

    /* Gain: '<S1>/Gain7' */
    branch_offset_rate210_Subsystem_Gain7_1 = branch_offset_rate210_P.Gain7_Gain
      * branch_offset_rate210_Subsystem_S_Function3_1;

    /* Math: '<S1>/MathFunction7' */
    branch_offset_rate210_Subsystem_MathFunction7_1 = rt_powd_snf(10.0,
      branch_offset_rate210_Subsystem_Gain7_1);

    /* Gain: '<S1>/Gain8' */
    branch_offset_rate210_Subsystem_Gain8_1 = branch_offset_rate210_P.Gain8_Gain
      * branch_offset_rate210_Subsystem_MathFunction7_1;

    /* Sum: '<S1>/Add3' */
    branch_offset_rate210_Subsystem_Add3_1 =
      branch_offset_rate210_Subsystem_Add4_1 +
      branch_offset_rate210_Subsystem_Gain8_1;
  }

  if (branch_offset_rate210_M->Timing.TaskCounters.TID[5] == 0) {
    /* Sqrt: '<S1>/Sqrt5' */
    branch_offset_rate210_Subsystem_Sqrt5_1 = sqrt
      (branch_offset_rate210_Subsystem_Add3_1);

    /* Math: '<S1>/MathFunction10'
     *
     * About '<S1>/MathFunction10':
     *  Operator: log10
     */
    branch_offset_rate210_Subsystem_MathFunction10_1 = log10
      (branch_offset_rate210_Subsystem_Sqrt5_1);

    /* S-Function (loop): '<S1>/S_Function4' */
    loop_Outputs_wrapper(&branch_offset_rate210_Subsystem_MathFunction10_1,
                         &branch_offset_rate210_Subsystem_S_Function4_1 );

    /* Gain: '<S1>/Gain9' */
    branch_offset_rate210_Subsystem_Gain9_1 = branch_offset_rate210_P.Gain9_Gain
      * branch_offset_rate210_Subsystem_S_Function4_1;

    /* Math: '<S1>/MathFunction9' */
    branch_offset_rate210_Subsystem_MathFunction9_1 = rt_powd_snf(10.0,
      branch_offset_rate210_Subsystem_Gain9_1);

    /* Gain: '<S1>/Gain10' */
    branch_offset_rate210_Subsystem_Gain10_1 =
      branch_offset_rate210_P.Gain10_Gain *
      branch_offset_rate210_Subsystem_MathFunction9_1;

    /* UnitDelay: '<Root>/UnitDelay' */
    branch_offset_rate210_UnitDelay_1 =
      branch_offset_rate210_DW.UnitDelay_DSTATE;
  }

  /* Sum: '<Root>/Sum' */
  branch_offset_rate210_Sum_1 = branch_offset_rate210_UnitDelay_1 +
    branch_offset_rate210_Gain_1;

  /* Update for UnitDelay: '<Root>/UnitDelay1' */
  branch_offset_rate210_DW.UnitDelay1_DSTATE = branch_offset_rate210_Sum_1;

  /* Update for UnitDelay: '<Root>/UnitDelay2' */
  branch_offset_rate210_DW.UnitDelay2_DSTATE = branch_offset_rate210_Gain_1;
  if (branch_offset_rate210_M->Timing.TaskCounters.TID[5] == 0) {
    /* Update for UnitDelay: '<Root>/UnitDelay' */
    branch_offset_rate210_DW.UnitDelay_DSTATE =
      branch_offset_rate210_Subsystem_Gain10_1;
  }

  rate_scheduler();
}

/* Model initialize function */
void branch_offset_rate210_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)branch_offset_rate210_M, 0,
                sizeof(RT_MODEL_branch_offset_rate21_T));

  /* initialize sample time offsets */
  branch_offset_rate210_M->Timing.TaskCounters.TID[2] = 4;/* Sample time: [0.01s, 0.002s] */

  /* initialize sample time offsets */
  branch_offset_rate210_M->Timing.TaskCounters.TID[3] = 3;/* Sample time: [0.01s, 0.004s] */

  /* initialize sample time offsets */
  branch_offset_rate210_M->Timing.TaskCounters.TID[4] = 2;/* Sample time: [0.01s, 0.006s] */

  /* initialize sample time offsets */
  branch_offset_rate210_M->Timing.TaskCounters.TID[5] = 1;/* Sample time: [0.01s, 0.008s] */

  /* block I/O */

  /* exported global signals */
  branch_offset_rate210_UnitDelay1_1 = 0.0;
  branch_offset_rate210_Gain_1 = 0.0;
  branch_offset_rate210_UnitDelay2_1 = 0.0;
  branch_offset_rate210_Subsystem_Sqrt1_1 = 0.0;
  branch_offset_rate210_Subsystem_Gain11_1 = 0.0;
  branch_offset_rate210_Subsystem_Gain_1 = 0.0;
  branch_offset_rate210_Subsystem_Gain2_1 = 0.0;
  branch_offset_rate210_Subsystem_Add1_1 = 0.0;
  branch_offset_rate210_Subsystem_MathFunction2_1 = 0.0;
  branch_offset_rate210_Subsystem_S_Function_1 = 0.0;
  branch_offset_rate210_Subsystem_Gain1_1 = 0.0;
  branch_offset_rate210_Subsystem_MathFunction1_1 = 0.0;
  branch_offset_rate210_Subsystem_Add_1 = 0.0;
  branch_offset_rate210_Subsystem_Sqrt2_1 = 0.0;
  branch_offset_rate210_Subsystem_Gain13_1 = 0.0;
  branch_offset_rate210_Subsystem_Gain12_1 = 0.0;
  branch_offset_rate210_Subsystem_Gain14_1 = 0.0;
  branch_offset_rate210_Subsystem_Add2_1 = 0.0;
  branch_offset_rate210_Subsystem_MathFunction17_1 = 0.0;
  branch_offset_rate210_Subsystem_Gain26_1 = 0.0;
  branch_offset_rate210_Subsystem_Gain27_1 = 0.0;
  branch_offset_rate210_Subsystem_Gain22_1 = 0.0;
  branch_offset_rate210_Subsystem_MathFunction18_1 = 0.0;
  branch_offset_rate210_Subsystem_MathFunction15_1 = 0.0;
  branch_offset_rate210_Subsystem_Gain28_1 = 0.0;
  branch_offset_rate210_Subsystem_Gain23_1 = 0.0;
  branch_offset_rate210_Subsystem_Gain24_1 = 0.0;
  branch_offset_rate210_Subsystem_MathFunction16_1 = 0.0;
  branch_offset_rate210_Subsystem_Gain25_1 = 0.0;
  branch_offset_rate210_Subsystem_MathFunction13_1 = 0.0;
  branch_offset_rate210_Subsystem_Gain19_1 = 0.0;
  branch_offset_rate210_Subsystem_Gain20_1 = 0.0;
  branch_offset_rate210_Subsystem_Gain15_1 = 0.0;
  branch_offset_rate210_Subsystem_MathFunction14_1 = 0.0;
  branch_offset_rate210_Subsystem_MathFunction11_1 = 0.0;
  branch_offset_rate210_Subsystem_Gain21_1 = 0.0;
  branch_offset_rate210_Subsystem_Gain16_1 = 0.0;
  branch_offset_rate210_Subsystem_Gain17_1 = 0.0;
  branch_offset_rate210_Subsystem_MathFunction12_1 = 0.0;
  branch_offset_rate210_Subsystem_Gain18_1 = 0.0;
  branch_offset_rate210_Subsystem_Add4_1 = 0.0;
  branch_offset_rate210_Subsystem_MathFunction4_1 = 0.0;
  branch_offset_rate210_Subsystem_S_Function1_1 = 0.0;
  branch_offset_rate210_Subsystem_Gain3_1 = 0.0;
  branch_offset_rate210_Subsystem_MathFunction3_1 = 0.0;
  branch_offset_rate210_Subsystem_Gain4_1 = 0.0;
  branch_offset_rate210_Subsystem_Sqrt3_1 = 0.0;
  branch_offset_rate210_Subsystem_MathFunction6_1 = 0.0;
  branch_offset_rate210_Subsystem_S_Function2_1 = 0.0;
  branch_offset_rate210_Subsystem_Gain5_1 = 0.0;
  branch_offset_rate210_Subsystem_MathFunction5_1 = 0.0;
  branch_offset_rate210_Subsystem_Gain6_1 = 0.0;
  branch_offset_rate210_Subsystem_Sqrt4_1 = 0.0;
  branch_offset_rate210_Subsystem_MathFunction8_1 = 0.0;
  branch_offset_rate210_Subsystem_S_Function3_1 = 0.0;
  branch_offset_rate210_Subsystem_Gain7_1 = 0.0;
  branch_offset_rate210_Subsystem_MathFunction7_1 = 0.0;
  branch_offset_rate210_Subsystem_Gain8_1 = 0.0;
  branch_offset_rate210_Subsystem_Add3_1 = 0.0;
  branch_offset_rate210_Subsystem_Sqrt5_1 = 0.0;
  branch_offset_rate210_Subsystem_MathFunction10_1 = 0.0;
  branch_offset_rate210_Subsystem_S_Function4_1 = 0.0;
  branch_offset_rate210_Subsystem_Gain9_1 = 0.0;
  branch_offset_rate210_Subsystem_MathFunction9_1 = 0.0;
  branch_offset_rate210_Subsystem_Gain10_1 = 0.0;
  branch_offset_rate210_UnitDelay_1 = 0.0;
  branch_offset_rate210_Sum_1 = 0.0;

  /* states (dwork) */
  (void) memset((void *)&branch_offset_rate210_DW, 0,
                sizeof(DW_branch_offset_rate210_T));

  /* InitializeConditions for UnitDelay: '<Root>/UnitDelay1' */
  branch_offset_rate210_DW.UnitDelay1_DSTATE =
    branch_offset_rate210_P.UnitDelay1_InitialCondition;

  /* InitializeConditions for UnitDelay: '<Root>/UnitDelay2' */
  branch_offset_rate210_DW.UnitDelay2_DSTATE =
    branch_offset_rate210_P.UnitDelay2_InitialCondition;

  /* InitializeConditions for UnitDelay: '<Root>/UnitDelay' */
  branch_offset_rate210_DW.UnitDelay_DSTATE =
    branch_offset_rate210_P.UnitDelay_InitialCondition;
}

/* Model terminate function */
void branch_offset_rate210_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

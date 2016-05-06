/*
 * File: mdl5_private.h
 *
 * Code generated for Simulink model 'mdl5'.
 *
 * Model version                  : 1.17
 * Simulink Coder version         : 8.6 (R2014a) 27-Dec-2013
 * C/C++ source code generated on : Tue Mar  8 17:18:38 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Specified
 * Emulation hardware selection:
 *    Differs from embedded hardware (32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_mdl5_private_h_
#define RTW_HEADER_mdl5_private_h_
#include "rtwtypes.h"

/* Used by FromWorkspace Block: '<Root>/Block7776' */
#ifndef rtInterpolate
# define rtInterpolate(v1,v2,f1,f2)    (((v1)==(v2))?((double)(v1)): (((f1)*((double)(v1)))+((f2)*((double)(v2)))))
#endif

#ifndef rtRound
# define rtRound(v)                    ( ((v) >= 0) ? floor((v) + 0.5) : ceil((v) - 0.5) )
#endif

#ifndef __RTWTYPES_H__
#error This file requires rtwtypes.h to be included
#endif                                 /* __RTWTYPES_H__ */

extern real_T rt_powd_snf(real_T u0, real_T u1);
extern real_T rt_roundd_snf(real_T u);
extern void mdl5_SubSystem2612(void);
extern void mdl5_SubSystem2691_Start(void);
extern void mdl5_SubSystem2691(void);

#endif                                 /* RTW_HEADER_mdl5_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

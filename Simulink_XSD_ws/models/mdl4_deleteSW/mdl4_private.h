/*
 * File: mdl4_private.h
 *
 * Code generated for Simulink model 'mdl4'.
 *
 * Model version                  : 1.17
 * Simulink Coder version         : 8.6 (R2014a) 27-Dec-2013
 * C/C++ source code generated on : Wed Apr 13 01:16:19 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Specified
 * Emulation hardware selection:
 *    Differs from embedded hardware (32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_mdl4_private_h_
#define RTW_HEADER_mdl4_private_h_
#include "rtwtypes.h"

/* Used by FromWorkspace Block: '<Root>/Block7331' */
#ifndef rtInterpolate
# define rtInterpolate(v1,v2,f1,f2)    (((v1)==(v2))?((double)(v1)): (((f1)*((double)(v1)))+((f2)*((double)(v2)))))
#endif

#ifndef rtRound
# define rtRound(v)                    ( ((v) >= 0) ? floor((v) + 0.5) : ceil((v) - 0.5) )
#endif

#ifndef __RTWTYPES_H__
#error This file requires rtwtypes.h to be included
#endif                                 /* __RTWTYPES_H__ */

extern real_T rt_roundd_snf(real_T u);
extern void mdl4_SubSystem2494(void);
extern void mdl4_SubSystem2577_Start(void);
extern void mdl4_SubSystem2577(void);

#endif                                 /* RTW_HEADER_mdl4_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

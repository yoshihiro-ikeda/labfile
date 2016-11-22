#ifndef __c2_mdl5_addTw_h__
#define __c2_mdl5_addTw_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc2_mdl5_addTwInstanceStruct
#define typedef_SFc2_mdl5_addTwInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c2_sfEvent;
  boolean_T c2_isStable;
  boolean_T c2_doneDoubleBufferReInit;
  uint8_T c2_is_active_c2_mdl5_addTw;
  int32_T c2_i1;
  uint8_T c2_doSetSimStateSideEffects;
  const mxArray *c2_setSimStateSideEffectsInfo;
  real_T *c2_N_Loop;
  real_T *c2_idx;
} SFc2_mdl5_addTwInstanceStruct;

#endif                                 /*typedef_SFc2_mdl5_addTwInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_mdl5_addTw_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c2_mdl5_addTw_get_check_sum(mxArray *plhs[]);
extern void c2_mdl5_addTw_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif

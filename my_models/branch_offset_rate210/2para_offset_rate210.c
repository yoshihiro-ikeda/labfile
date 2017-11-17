#include <mcos/mcos.h>
#include <mcos/mcos_ds.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include "rtwtypes.h"
#include "offset_rate210_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

#include <time.h>
#include <sys/time.h>
#include <unistd.h>

struct timeval start,end,tmp;

/*
 * Resource by Core
 */

/* Core 0 affinity task */
#ifndef CORE_0_STACK_SIZE
#define CORE_0_STACK_SIZE	0 /* default */
#endif /* CORE_0_STACK_SIZE */

#ifndef CORE_0_PRIORITY
#define CORE_0_PRIORITY	128
#endif /* CORE_0_PRIVATE */

/* Core 1 affinity task */
#ifndef CORE_1_STACK_SIZE
#define CORE_1_STACK_SIZE	0 /* default */
#endif /* CORE_1_STACK_SIZE */

#ifndef CORE_1_PRIORITY
#define CORE_1_PRIORITY	128
#endif /* CORE_1_PRIVATE */

/* Logical Core task */
#ifndef LCORE_STACK_SIZE
#define LCORE_STACK_SIZE	0 /* default */
#endif /* LCORE_STACK_SIZE */

#ifndef LCORE_PRIORITY
#define LCORE_PRIORITY	128
#endif /* LCORE_PRIVATE */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif


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
      uint8_T TID[5];
    } TaskCounters;
  } Timing;
};
#include "offset_rate210_private.h"

#include "2para_offset_rate210_res.c"


#ifndef __GNUC__
#define __inline__
#endif /* __GNUC__ */

#ifndef CORE_TASK_DATA_PREPARE
#define CORE_TASK_DATA_PREPARE(N)	/* none */
#endif /* CORE_TASK_DATA_PREPARE */

#ifndef CORE_TASK_DATA_ATTRIBUTE
#define CORE_TASK_DATA_ATTRIBUTE(N)	/* none */
#endif /* CORE_TASK_DATA_ATTRIBUTE */

#ifndef CORE_TASK_CODE_PREPARE
#define CORE_TASK_CODE_PREPARE(N)	/* none */
#endif /* CORE_TASK_CODE_PREPARE */

#ifndef CORE_TASK_CODE_ATTRIBUTE
#define CORE_TASK_CODE_ATTRIBUTE(N)	/* none */
#endif /* CORE_TASK_CODE_ATTRIBUTE */

#ifndef TASK_DATA_PREPARE
#define TASK_DATA_PREPARE(N)	/* none */
#endif /* TASK_DATA_PREPARE */

#ifndef TASK_DATA_ATTRIBUTE
#define TASK_DATA_ATTRIBUTE(N)	/* none */
#endif /* TASK_DATA_ATTRIBUTE */

#ifndef TASK_CODE_PREPARE
#define TASK_CODE_PREPARE(N)	/* none */
#endif /* TASK_CODE_PREPARE */

#ifndef TASK_CODE_ATTRIBUTE
#define TASK_CODE_ATTRIBUTE(N)	/* none */
#endif /* TASK_CODE_ATTRIBUTE */

/*
 * Channel Macros
 */
#define CH__VEC__CONCAT(A,B)	A##B
#define CH__VEC_CONCAT(A,B)	CH__VEC__CONCAT(A,B)
#define CH__VEC_NAME(N)	CH__VEC_CONCAT(ch__vec_,N)
#define CH__VEC_ELEMENT_TYPE	unsigned long
#define CH__VEC_ELEMENT_BITS	(sizeof (CH__VEC_ELEMENT_TYPE) * 8)
#define CH__VEC_ELEMENT_SIZE(S)	\
  (((S)+CH__VEC_ELEMENT_BITS-1)/CH__VEC_ELEMENT_BITS)
#define CH__VEC_ELEMENT_0	((CH__VEC_ELEMENT_TYPE)0)
#define CH__VEC_ELEMENT_1	((CH__VEC_ELEMENT_TYPE)1)
#define CH__VEC(N,S)	\
  CH__VEC_ELEMENT_TYPE CH__VEC_NAME(N)[CH__VEC_ELEMENT_SIZE(S)] = {0,}
#define CH__VEC_INIT(N) memset(CH__VEC_NAME(N), 0, sizeof CH__VEC_NAME(N))
#define CH__BITCHECK(N,B)	ch__bitcheck(CH__VEC_NAME(N),B)
#define CH__BITSET(N,B)	ch__bitset(CH__VEC_NAME(N),B)
#define CH__COMPLETED(N,S)	ch__completed(CH__VEC_NAME(N),S)

#ifndef CH__SYNCM
#if defined(__v850__) && defined(__GNUC__)
#define CH__SYNCM()	__asm__ __volatile__ ("syncm" ::: "memory")
#else /* !__v850__ || !__GNUC__ */
#define CH__SYNCM()	do { ; } while (0)
#endif /* !__v850__ || __GNUC__ */
#endif /* !CH__SYNCM */

#ifndef CH__MEM_BARRIER
#ifdef __GNUC__
#define CH__MEM_BARRIER()	__asm__ __volatile__ ("" ::: "memory")
#else /* !__GNUC__ */
#define CH__MEM_BARRIER()	do { ; } while (0)
#endif /* !__GNUC__ */
#endif /* !CH__MEM_BARRIER */

#ifndef CH__TASK_SCHED
#ifdef MCOS_H
#define CH__TASK_SCHED(C,V,S)	mcos_thread_delay(0)
#else /* !MCOS_H */
#define CH__TASK_SCHED(C,V,S)	do { ; } while (0)
#endif /* !MCOS_H */
#endif /* !CH__TASK_SCHED */

#ifndef CH__EVENT
#define CH__EVENT(T,C)	CH__MEM_BARRIER()
#endif /* CH__EVENT */

#ifndef CH__END_LOG
#define CH__END_LOG(C)	do { ; } while (0)
#endif /* CH__END_LOG */

#ifndef CH__CORE_THREAD_SCHED
#define CH__CORE_THREAD_SCHED(C,V,S)	do { ; } while (0)
#endif /* CH__CORE_THREAD_SCHED */

/* check channle bitvec */
static __inline__ int
ch__bitcheck (CH__VEC_ELEMENT_TYPE *v, size_t b)
{
  return (v[b/CH__VEC_ELEMENT_BITS]
          & (CH__VEC_ELEMENT_1 << (b % CH__VEC_ELEMENT_BITS)));
}

/* set channle bitvec */
static __inline__ void
ch__bitset (CH__VEC_ELEMENT_TYPE *v, size_t b)
{
  v[b/CH__VEC_ELEMENT_BITS]
    |= (CH__VEC_ELEMENT_1 << (b % CH__VEC_ELEMENT_BITS));
}

/* completed channel wait */
static __inline__ int
ch__completed (CH__VEC_ELEMENT_TYPE *v, size_t n)
{
  const size_t restbits = n % CH__VEC_ELEMENT_BITS;
  size_t i;
  size_t e = (n - 1) / CH__VEC_ELEMENT_BITS;
  CH__VEC_ELEMENT_TYPE const
    restmask =  ((restbits == 0)
		 ? (~CH__VEC_ELEMENT_0)
		 : ((CH__VEC_ELEMENT_1 << restbits) - 1));
  for (i = 0; i < e; i++, v++)
    {
      if (*v != ~(CH__VEC_ELEMENT_0))
	return 0;
    }
  if (*v != restmask)
    return 0;
  return 1;
}

/*
 * Channels
 */

/* From: offset_rate210_Gain
   To: offset_rate210_Sum */
typedef struct {
  int flag__0001_0027;
  real_T offset_rate210_Gain_1;
} TYPE_0001_0027;
TYPE_0001_0027 CH_0001_0027;

/* From: offset_rate210_Gain
   To: offset_rate210_Sqrt1 */
typedef struct {
  int flag__0001_0022;
  real_T offset_rate210_Gain_1;
} TYPE_0001_0022;
TYPE_0001_0022 CH_0001_0022;

/* From: offset_rate210_Gain1
   To: offset_rate210_MathFunction1 */
typedef struct {
  int flag__0002_0012;
  real_T offset_rate210_Gain1_1;
} TYPE_0002_0012;
TYPE_0002_0012 CH_0002_0012;

/* From: offset_rate210_Gain10
   To: offset_rate210_Sum */
typedef struct {
  int flag__0003_0027;
  real_T offset_rate210_Gain10_1;
} TYPE_0003_0027;
TYPE_0003_0027 CH_0003_0027;

/* From: offset_rate210_Gain2
   To: offset_rate210_Sqrt2 */
typedef struct {
  int flag__0004_0023;
  real_T offset_rate210_Gain2_1;
} TYPE_0004_0023;
TYPE_0004_0023 CH_0004_0023;

/* From: offset_rate210_Gain3
   To: offset_rate210_MathFunction3 */
typedef struct {
  int flag__0005_0015;
  real_T offset_rate210_Gain3_1;
} TYPE_0005_0015;
TYPE_0005_0015 CH_0005_0015;

/* From: offset_rate210_Gain4
   To: offset_rate210_Sqrt3 */
typedef struct {
  int flag__0006_0024;
  real_T offset_rate210_Gain4_1;
} TYPE_0006_0024;
TYPE_0006_0024 CH_0006_0024;

/* From: offset_rate210_Gain5
   To: offset_rate210_MathFunction5 */
typedef struct {
  int flag__0007_0017;
  real_T offset_rate210_Gain5_1;
} TYPE_0007_0017;
TYPE_0007_0017 CH_0007_0017;

/* From: offset_rate210_Gain6
   To: offset_rate210_Sqrt4 */
typedef struct {
  int flag__0008_0025;
  real_T offset_rate210_Gain6_1;
} TYPE_0008_0025;
TYPE_0008_0025 CH_0008_0025;

/* From: offset_rate210_Gain7
   To: offset_rate210_MathFunction7 */
typedef struct {
  int flag__0009_0019;
  real_T offset_rate210_Gain7_1;
} TYPE_0009_0019;
TYPE_0009_0019 CH_0009_0019;

/* From: offset_rate210_Gain8
   To: offset_rate210_Sqrt5 */
typedef struct {
  int flag__0010_0026;
  real_T offset_rate210_Gain8_1;
} TYPE_0010_0026;
TYPE_0010_0026 CH_0010_0026;

/* From: offset_rate210_Gain9
   To: offset_rate210_MathFunction9 */
typedef struct {
  int flag__0011_0021;
  real_T offset_rate210_Gain9_1;
} TYPE_0011_0021;
TYPE_0011_0021 CH_0011_0021;

/* From: offset_rate210_MathFunction1
   To: offset_rate210_Gain2 */
typedef struct {
  int flag__0012_0004;
  real_T offset_rate210_MathFunction1_1;
} TYPE_0012_0004;
TYPE_0012_0004 CH_0012_0004;

/* From: offset_rate210_MathFunction10
   To: offset_rate210_Gain9 */
typedef struct {
  int flag__0013_0011;
  real_T offset_rate210_MathFunction10_1;
} TYPE_0013_0011;
TYPE_0013_0011 CH_0013_0011;

/* From: offset_rate210_MathFunction2
   To: offset_rate210_Gain1 */
typedef struct {
  int flag__0014_0002;
  real_T offset_rate210_MathFunction2_1;
} TYPE_0014_0002;
TYPE_0014_0002 CH_0014_0002;

/* From: offset_rate210_MathFunction3
   To: offset_rate210_Gain4 */
typedef struct {
  int flag__0015_0006;
  real_T offset_rate210_MathFunction3_1;
} TYPE_0015_0006;
TYPE_0015_0006 CH_0015_0006;

/* From: offset_rate210_MathFunction4
   To: offset_rate210_Gain3 */
typedef struct {
  int flag__0016_0005;
  real_T offset_rate210_MathFunction4_1;
} TYPE_0016_0005;
TYPE_0016_0005 CH_0016_0005;

/* From: offset_rate210_MathFunction5
   To: offset_rate210_Gain6 */
typedef struct {
  int flag__0017_0008;
  real_T offset_rate210_MathFunction5_1;
} TYPE_0017_0008;
TYPE_0017_0008 CH_0017_0008;

/* From: offset_rate210_MathFunction6
   To: offset_rate210_Gain5 */
typedef struct {
  int flag__0018_0007;
  real_T offset_rate210_MathFunction6_1;
} TYPE_0018_0007;
TYPE_0018_0007 CH_0018_0007;

/* From: offset_rate210_MathFunction7
   To: offset_rate210_Gain8 */
typedef struct {
  int flag__0019_0010;
  real_T offset_rate210_MathFunction7_1;
} TYPE_0019_0010;
TYPE_0019_0010 CH_0019_0010;

/* From: offset_rate210_MathFunction8
   To: offset_rate210_Gain7 */
typedef struct {
  int flag__0020_0009;
  real_T offset_rate210_MathFunction8_1;
} TYPE_0020_0009;
TYPE_0020_0009 CH_0020_0009;

/* From: offset_rate210_MathFunction9
   To: offset_rate210_Gain10 */
typedef struct {
  int flag__0021_0003;
  real_T offset_rate210_MathFunction9_1;
} TYPE_0021_0003;
TYPE_0021_0003 CH_0021_0003;

/* From: offset_rate210_Sqrt1
   To: offset_rate210_MathFunction2 */
typedef struct {
  int flag__0022_0014;
  real_T offset_rate210_Sqrt1_1;
} TYPE_0022_0014;
TYPE_0022_0014 CH_0022_0014;

/* From: offset_rate210_Sqrt2
   To: offset_rate210_MathFunction4 */
typedef struct {
  int flag__0023_0016;
  real_T offset_rate210_Sqrt2_1;
} TYPE_0023_0016;
TYPE_0023_0016 CH_0023_0016;

/* From: offset_rate210_Sqrt3
   To: offset_rate210_MathFunction6 */
typedef struct {
  int flag__0024_0018;
  real_T offset_rate210_Sqrt3_1;
} TYPE_0024_0018;
TYPE_0024_0018 CH_0024_0018;

/* From: offset_rate210_Sqrt4
   To: offset_rate210_MathFunction8 */
typedef struct {
  int flag__0025_0020;
  real_T offset_rate210_Sqrt4_1;
} TYPE_0025_0020;
TYPE_0025_0020 CH_0025_0020;

/* From: offset_rate210_Sqrt5
   To: offset_rate210_MathFunction10 */
typedef struct {
  int flag__0026_0013;
  real_T offset_rate210_Sqrt5_1;
} TYPE_0026_0013;
TYPE_0026_0013 CH_0026_0013;

/* From: offset_rate210_Sum
   To: offset_rate210_Gain */
typedef struct {
  int flag__0027_0001;
  real_T offset_rate210_Sum_1;
} TYPE_0027_0001;
TYPE_0027_0001 CH_0027_0001;

/*
 * Tasks
 */

CORE_TASK_CODE_PREPARE(0)

/* Core#0 */
void mcos_core0_thread(uint32_t stacd, uintptr_t exinf)
{  /* omit input channel bit vector */
  /* CH__VEC(IN_0022,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0022,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0014,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0014,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0002,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0002,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0012,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0012,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0004,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0004,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0023,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0023,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0016,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0016,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0005,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0005,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0015,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0015,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0006,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0006,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0024,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0024,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0018,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0018,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0007,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0007,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0017,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0017,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0008,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0008,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0025,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0025,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0020,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0020,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0009,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0009,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0019,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0019,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0010,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0010,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0026,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0026,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0013,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0013,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0011,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0011,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0021,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0021,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0003,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0003,1); */

  /* Real-Time Model Object */
  RT_MODEL_offset_rate210_T offset_rate210_M_;
  RT_MODEL_offset_rate210_T * const offset_rate210_M = &offset_rate210_M_;

  /* states */
  struct {
    /* Block: offset_rate210_Sqrt1 */
    real_T UnitDelay2_DSTATE; /* task_0022 */
  } offset_rate210_DW;

  /* params */
  struct {
    /* Block: offset_rate210_Sqrt1 */
    real_T UnitDelay2_InitialCondition;

    /* Block: offset_rate210_Gain1 */
    real_T Gain1_Gain;

    /* Block: offset_rate210_Gain2 */
    real_T Gain2_Gain;

    /* Block: offset_rate210_Gain3 */
    real_T Gain3_Gain;

    /* Block: offset_rate210_Gain4 */
    real_T Gain4_Gain;

    /* Block: offset_rate210_Gain5 */
    real_T Gain5_Gain;

    /* Block: offset_rate210_Gain6 */
    real_T Gain6_Gain;

    /* Block: offset_rate210_Gain7 */
    real_T Gain7_Gain;

    /* Block: offset_rate210_Gain8 */
    real_T Gain8_Gain;

    /* Block: offset_rate210_Gain9 */
    real_T Gain9_Gain;

    /* Block: offset_rate210_Gain10 */
    real_T Gain10_Gain;
  } offset_rate210_P = {
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<Root>/UnitDelay2'
                                        */

  2.0,                                 /* Expression: 2
                                        * Referenced by: '<Root>/Gain1'
                                        */

  0.5,                                 /* Expression: 0.5
                                        * Referenced by: '<Root>/Gain2'
                                        */

  2.0,                                 /* Expression: 2
                                        * Referenced by: '<Root>/Gain3'
                                        */

  0.5,                                 /* Expression: 0.5
                                        * Referenced by: '<Root>/Gain4'
                                        */

  2.0,                                 /* Expression: 2
                                        * Referenced by: '<Root>/Gain5'
                                        */

  0.5,                                 /* Expression: 0.5
                                        * Referenced by: '<Root>/Gain6'
                                        */

  2.0,                                 /* Expression: 2
                                        * Referenced by: '<Root>/Gain7'
                                        */

  0.5,                                 /* Expression: 0.5
                                        * Referenced by: '<Root>/Gain8'
                                        */

  2.0,                                 /* Expression: 2
                                        * Referenced by: '<Root>/Gain9'
                                        */

  0.5,                                 /* Expression: 0.5
                                        * Referenced by: '<Root>/Gain10'
                                        */

  };

  /* internal variables */

  /* Block: offset_rate210_Sqrt1 */
  real_T offset_rate210_UnitDelay2_1;

  /* input variables */

  /* Block: offset_rate210_Sqrt1 */
  real_T offset_rate210_Gain_1;

  /* Block: offset_rate210_MathFunction2 */
  real_T offset_rate210_Sqrt1_1;

  /* Block: offset_rate210_Gain1 */
  real_T offset_rate210_MathFunction2_1;

  /* Block: offset_rate210_MathFunction1 */
  real_T offset_rate210_Gain1_1;

  /* Block: offset_rate210_Gain2 */
  real_T offset_rate210_MathFunction1_1;

  /* Block: offset_rate210_Sqrt2 */
  real_T offset_rate210_Gain2_1;

  /* Block: offset_rate210_MathFunction4 */
  real_T offset_rate210_Sqrt2_1;

  /* Block: offset_rate210_Gain3 */
  real_T offset_rate210_MathFunction4_1;

  /* Block: offset_rate210_MathFunction3 */
  real_T offset_rate210_Gain3_1;

  /* Block: offset_rate210_Gain4 */
  real_T offset_rate210_MathFunction3_1;

  /* Block: offset_rate210_Sqrt3 */
  real_T offset_rate210_Gain4_1;

  /* Block: offset_rate210_MathFunction6 */
  real_T offset_rate210_Sqrt3_1;

  /* Block: offset_rate210_Gain5 */
  real_T offset_rate210_MathFunction6_1;

  /* Block: offset_rate210_MathFunction5 */
  real_T offset_rate210_Gain5_1;

  /* Block: offset_rate210_Gain6 */
  real_T offset_rate210_MathFunction5_1;

  /* Block: offset_rate210_Sqrt4 */
  real_T offset_rate210_Gain6_1;

  /* Block: offset_rate210_MathFunction8 */
  real_T offset_rate210_Sqrt4_1;

  /* Block: offset_rate210_Gain7 */
  real_T offset_rate210_MathFunction8_1;

  /* Block: offset_rate210_MathFunction7 */
  real_T offset_rate210_Gain7_1;

  /* Block: offset_rate210_Gain8 */
  real_T offset_rate210_MathFunction7_1;

  /* Block: offset_rate210_Sqrt5 */
  real_T offset_rate210_Gain8_1;

  /* Block: offset_rate210_MathFunction10 */
  real_T offset_rate210_Sqrt5_1;

  /* Block: offset_rate210_Gain9 */
  real_T offset_rate210_MathFunction10_1;

  /* Block: offset_rate210_MathFunction9 */
  real_T offset_rate210_Gain9_1;

  /* Block: offset_rate210_Gain10 */
  real_T offset_rate210_MathFunction9_1;

  /* output variables */

  /* Block: offset_rate210_Sqrt1 */

  /* Block: offset_rate210_MathFunction2 */

  /* Block: offset_rate210_Gain1 */

  /* Block: offset_rate210_MathFunction1 */

  /* Block: offset_rate210_Gain2 */

  /* Block: offset_rate210_Sqrt2 */

  /* Block: offset_rate210_MathFunction4 */

  /* Block: offset_rate210_Gain3 */

  /* Block: offset_rate210_MathFunction3 */

  /* Block: offset_rate210_Gain4 */

  /* Block: offset_rate210_Sqrt3 */

  /* Block: offset_rate210_MathFunction6 */

  /* Block: offset_rate210_Gain5 */

  /* Block: offset_rate210_MathFunction5 */

  /* Block: offset_rate210_Gain6 */

  /* Block: offset_rate210_Sqrt4 */

  /* Block: offset_rate210_MathFunction8 */

  /* Block: offset_rate210_Gain7 */

  /* Block: offset_rate210_MathFunction7 */

  /* Block: offset_rate210_Gain8 */

  /* Block: offset_rate210_Sqrt5 */

  /* Block: offset_rate210_MathFunction10 */

  /* Block: offset_rate210_Gain9 */

  /* Block: offset_rate210_MathFunction9 */

  /* Block: offset_rate210_Gain10 */
  real_T offset_rate210_Gain10_1;

  /* functions */

  /* Block: offset_rate210_MathFunction1 */

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

  /* Block: offset_rate210_MathFunction3 */

  /* Block: offset_rate210_MathFunction5 */

  /* Block: offset_rate210_MathFunction7 */

  /* Block: offset_rate210_MathFunction9 */

  /* Common Initialization */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize Real-Time Model Object */
  /* initialize real-time model */
  (void) memset((void *)offset_rate210_M, 0,
                sizeof(RT_MODEL_offset_rate210_T));

  /* initialize state structure */
  memset(&offset_rate210_DW, 0, sizeof offset_rate210_DW);

  /* Block: offset_rate210_Sqrt1 */

  /* initialize states */
{
  /* InitializeConditions for UnitDelay: '<Root>/UnitDelay2' */
  offset_rate210_DW.UnitDelay2_DSTATE =
    offset_rate210_P.UnitDelay2_InitialCondition;

}

  /* initialize task context */
{
  offset_rate210_UnitDelay2_1 = 0.0;
}
{
  offset_rate210_Sqrt1_1 = 0.0;
}

  /* Block: offset_rate210_MathFunction2 */

  /* initialize task context */
{
  offset_rate210_MathFunction2_1 = 0.0;
}

  /* Block: offset_rate210_Gain1 */

  /* initialize task context */
{
  offset_rate210_Gain1_1 = 0.0;
}

  /* Block: offset_rate210_MathFunction1 */

  /* initialize task context */
{
  offset_rate210_MathFunction1_1 = 0.0;
}

  /* Block: offset_rate210_Gain2 */

  /* initialize task context */
{
  offset_rate210_Gain2_1 = 0.0;
}

  /* Block: offset_rate210_Sqrt2 */

  /* initialize task context */
{
  offset_rate210_Sqrt2_1 = 0.0;
}

  /* Block: offset_rate210_MathFunction4 */

  /* initialize task context */
{
  offset_rate210_MathFunction4_1 = 0.0;
}

  /* Block: offset_rate210_Gain3 */

  /* initialize task context */
{
  offset_rate210_Gain3_1 = 0.0;
}

  /* Block: offset_rate210_MathFunction3 */

  /* initialize task context */
{
  offset_rate210_MathFunction3_1 = 0.0;
}

  /* Block: offset_rate210_Gain4 */

  /* initialize task context */
{
  offset_rate210_Gain4_1 = 0.0;
}

  /* Block: offset_rate210_Sqrt3 */

  /* initialize task context */
{
  offset_rate210_Sqrt3_1 = 0.0;
}

  /* Block: offset_rate210_MathFunction6 */

  /* initialize task context */
{
  offset_rate210_MathFunction6_1 = 0.0;
}

  /* Block: offset_rate210_Gain5 */

  /* initialize task context */
{
  offset_rate210_Gain5_1 = 0.0;
}

  /* Block: offset_rate210_MathFunction5 */

  /* initialize task context */
{
  offset_rate210_MathFunction5_1 = 0.0;
}

  /* Block: offset_rate210_Gain6 */

  /* initialize task context */
{
  offset_rate210_Gain6_1 = 0.0;
}

  /* Block: offset_rate210_Sqrt4 */

  /* initialize task context */
{
  offset_rate210_Sqrt4_1 = 0.0;
}

  /* Block: offset_rate210_MathFunction8 */

  /* initialize task context */
{
  offset_rate210_MathFunction8_1 = 0.0;
}

  /* Block: offset_rate210_Gain7 */

  /* initialize task context */
{
  offset_rate210_Gain7_1 = 0.0;
}

  /* Block: offset_rate210_MathFunction7 */

  /* initialize task context */
{
  offset_rate210_MathFunction7_1 = 0.0;
}

  /* Block: offset_rate210_Gain8 */

  /* initialize task context */
{
  offset_rate210_Gain8_1 = 0.0;
}

  /* Block: offset_rate210_Sqrt5 */

  /* initialize task context */
{
  offset_rate210_Sqrt5_1 = 0.0;
}

  /* Block: offset_rate210_MathFunction10 */

  /* initialize task context */
{
  offset_rate210_MathFunction10_1 = 0.0;
}

  /* Block: offset_rate210_Gain9 */

  /* initialize task context */
{
  offset_rate210_Gain9_1 = 0.0;
}

  /* Block: offset_rate210_MathFunction9 */

  /* initialize task context */
{
  offset_rate210_MathFunction9_1 = 0.0;
}

  /* Block: offset_rate210_Gain10 */

  /* initialize task context */
{
  offset_rate210_Gain10_1 = 0.0;
}

#ifdef TASK_INITIALIZE_0022_COMPLETED
  TASK_INITIALIZE_0022_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0014_COMPLETED
  TASK_INITIALIZE_0014_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0002_COMPLETED
  TASK_INITIALIZE_0002_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0012_COMPLETED
  TASK_INITIALIZE_0012_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0004_COMPLETED
  TASK_INITIALIZE_0004_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0023_COMPLETED
  TASK_INITIALIZE_0023_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0016_COMPLETED
  TASK_INITIALIZE_0016_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0005_COMPLETED
  TASK_INITIALIZE_0005_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0015_COMPLETED
  TASK_INITIALIZE_0015_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0006_COMPLETED
  TASK_INITIALIZE_0006_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0024_COMPLETED
  TASK_INITIALIZE_0024_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0018_COMPLETED
  TASK_INITIALIZE_0018_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0007_COMPLETED
  TASK_INITIALIZE_0007_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0017_COMPLETED
  TASK_INITIALIZE_0017_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0008_COMPLETED
  TASK_INITIALIZE_0008_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0025_COMPLETED
  TASK_INITIALIZE_0025_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0020_COMPLETED
  TASK_INITIALIZE_0020_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0009_COMPLETED
  TASK_INITIALIZE_0009_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0019_COMPLETED
  TASK_INITIALIZE_0019_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0010_COMPLETED
  TASK_INITIALIZE_0010_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0026_COMPLETED
  TASK_INITIALIZE_0026_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0013_COMPLETED
  TASK_INITIALIZE_0013_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0011_COMPLETED
  TASK_INITIALIZE_0011_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0021_COMPLETED
  TASK_INITIALIZE_0021_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0003_COMPLETED
  TASK_INITIALIZE_0003_COMPLETED();
#endif

  /* task loop */
  while (1) {    /*
     * Block: offset_rate210_Sqrt1
     * Task: 0022
     */

    /* C code */
        {
{

  /* UnitDelay: '<Root>/UnitDelay2' */
  offset_rate210_UnitDelay2_1 = offset_rate210_DW.UnitDelay2_DSTATE;


}

{

  /* Sqrt: '<Root>/Sqrt1' */
  offset_rate210_Sqrt1_1 = sqrt(offset_rate210_UnitDelay2_1);


}

    }

#ifdef TASK_EXECUTE_0022_COMPLETED
    TASK_EXECUTE_0022_COMPLETED();
#endif
    /*
     * Block: offset_rate210_MathFunction2
     * Task: 0014
     */

    /* C code */
        {
{

  /* Math: '<Root>/MathFunction2'
   *
   * About '<Root>/MathFunction2':
   *  Operator: log10
   */
  offset_rate210_MathFunction2_1 = log10(offset_rate210_Sqrt1_1);


}

    }

#ifdef TASK_EXECUTE_0014_COMPLETED
    TASK_EXECUTE_0014_COMPLETED();
#endif
    /*
     * Block: offset_rate210_Gain1
     * Task: 0002
     */

    /* C code */
        {
{

  /* Gain: '<Root>/Gain1' */
  offset_rate210_Gain1_1 = offset_rate210_P.Gain1_Gain *
    offset_rate210_MathFunction2_1;


}

    }

#ifdef TASK_EXECUTE_0002_COMPLETED
    TASK_EXECUTE_0002_COMPLETED();
#endif
    /*
     * Block: offset_rate210_MathFunction1
     * Task: 0012
     */

    /* C code */
        {
{

  /* Math: '<Root>/MathFunction1' */
  offset_rate210_MathFunction1_1 = rt_powd_snf(10.0, offset_rate210_Gain1_1);


}

    }

#ifdef TASK_EXECUTE_0012_COMPLETED
    TASK_EXECUTE_0012_COMPLETED();
#endif
    /*
     * Block: offset_rate210_Gain2
     * Task: 0004
     */

    /* C code */
        {
{

  /* Gain: '<Root>/Gain2' */
  offset_rate210_Gain2_1 = offset_rate210_P.Gain2_Gain *
    offset_rate210_MathFunction1_1;

}

    }

#ifdef TASK_EXECUTE_0004_COMPLETED
    TASK_EXECUTE_0004_COMPLETED();
#endif
    /*
     * Block: offset_rate210_Sqrt2
     * Task: 0023
     */

    /* C code */
        {
{

  if (offset_rate210_M->Timing.TaskCounters.TID[1] == 0) {

    /* Sqrt: '<Root>/Sqrt2' */
    offset_rate210_Sqrt2_1 = sqrt(offset_rate210_Gain2_1);


  }

}

    }

#ifdef TASK_EXECUTE_0023_COMPLETED
    TASK_EXECUTE_0023_COMPLETED();
#endif
    /*
     * Block: offset_rate210_MathFunction4
     * Task: 0016
     */

    /* C code */
        {
{

  if (offset_rate210_M->Timing.TaskCounters.TID[1] == 0) {

    /* Math: '<Root>/MathFunction4'
     *
     * About '<Root>/MathFunction4':
     *  Operator: log10
     */
    offset_rate210_MathFunction4_1 = log10(offset_rate210_Sqrt2_1);


  }

}

    }

#ifdef TASK_EXECUTE_0016_COMPLETED
    TASK_EXECUTE_0016_COMPLETED();
#endif
    /*
     * Block: offset_rate210_Gain3
     * Task: 0005
     */

    /* C code */
        {
{

  if (offset_rate210_M->Timing.TaskCounters.TID[1] == 0) {

    /* Gain: '<Root>/Gain3' */
    offset_rate210_Gain3_1 = offset_rate210_P.Gain3_Gain *
      offset_rate210_MathFunction4_1;


  }

}

    }

#ifdef TASK_EXECUTE_0005_COMPLETED
    TASK_EXECUTE_0005_COMPLETED();
#endif
    /*
     * Block: offset_rate210_MathFunction3
     * Task: 0015
     */

    /* C code */
        {
{

  if (offset_rate210_M->Timing.TaskCounters.TID[1] == 0) {

    /* Math: '<Root>/MathFunction3' */
    offset_rate210_MathFunction3_1 = rt_powd_snf(10.0, offset_rate210_Gain3_1);


  }

}

    }

#ifdef TASK_EXECUTE_0015_COMPLETED
    TASK_EXECUTE_0015_COMPLETED();
#endif
    /*
     * Block: offset_rate210_Gain4
     * Task: 0006
     */

    /* C code */
        {
{

  if (offset_rate210_M->Timing.TaskCounters.TID[1] == 0) {

    /* Gain: '<Root>/Gain4' */
    offset_rate210_Gain4_1 = offset_rate210_P.Gain4_Gain *
      offset_rate210_MathFunction3_1;

  }

}

    }

#ifdef TASK_EXECUTE_0006_COMPLETED
    TASK_EXECUTE_0006_COMPLETED();
#endif
    /*
     * Block: offset_rate210_Sqrt3
     * Task: 0024
     */

    /* C code */
        {
{

  if (offset_rate210_M->Timing.TaskCounters.TID[2] == 0) {

    /* Sqrt: '<Root>/Sqrt3' */
    offset_rate210_Sqrt3_1 = sqrt(offset_rate210_Gain4_1);


  }

}

    }

#ifdef TASK_EXECUTE_0024_COMPLETED
    TASK_EXECUTE_0024_COMPLETED();
#endif
    /*
     * Block: offset_rate210_MathFunction6
     * Task: 0018
     */

    /* C code */
        {
{

  if (offset_rate210_M->Timing.TaskCounters.TID[2] == 0) {

    /* Math: '<Root>/MathFunction6'
     *
     * About '<Root>/MathFunction6':
     *  Operator: log10
     */
    offset_rate210_MathFunction6_1 = log10(offset_rate210_Sqrt3_1);


  }

}

    }

#ifdef TASK_EXECUTE_0018_COMPLETED
    TASK_EXECUTE_0018_COMPLETED();
#endif
    /*
     * Block: offset_rate210_Gain5
     * Task: 0007
     */

    /* C code */
        {
{

  if (offset_rate210_M->Timing.TaskCounters.TID[2] == 0) {

    /* Gain: '<Root>/Gain5' */
    offset_rate210_Gain5_1 = offset_rate210_P.Gain5_Gain *
      offset_rate210_MathFunction6_1;


  }

}

    }

#ifdef TASK_EXECUTE_0007_COMPLETED
    TASK_EXECUTE_0007_COMPLETED();
#endif
    /*
     * Block: offset_rate210_MathFunction5
     * Task: 0017
     */

    /* C code */
        {
{

  if (offset_rate210_M->Timing.TaskCounters.TID[2] == 0) {

    /* Math: '<Root>/MathFunction5' */
    offset_rate210_MathFunction5_1 = rt_powd_snf(10.0, offset_rate210_Gain5_1);


  }

}

    }

#ifdef TASK_EXECUTE_0017_COMPLETED
    TASK_EXECUTE_0017_COMPLETED();
#endif
    /*
     * Block: offset_rate210_Gain6
     * Task: 0008
     */

    /* C code */
        {
{

  if (offset_rate210_M->Timing.TaskCounters.TID[2] == 0) {

    /* Gain: '<Root>/Gain6' */
    offset_rate210_Gain6_1 = offset_rate210_P.Gain6_Gain *
      offset_rate210_MathFunction5_1;

  }

}

    }

#ifdef TASK_EXECUTE_0008_COMPLETED
    TASK_EXECUTE_0008_COMPLETED();
#endif
    /*
     * Block: offset_rate210_Sqrt4
     * Task: 0025
     */

    /* C code */
        {
{

  if (offset_rate210_M->Timing.TaskCounters.TID[3] == 0) {

    /* Sqrt: '<Root>/Sqrt4' */
    offset_rate210_Sqrt4_1 = sqrt(offset_rate210_Gain6_1);


  }

}

    }

#ifdef TASK_EXECUTE_0025_COMPLETED
    TASK_EXECUTE_0025_COMPLETED();
#endif
    /*
     * Block: offset_rate210_MathFunction8
     * Task: 0020
     */

    /* C code */
        {
{

  if (offset_rate210_M->Timing.TaskCounters.TID[3] == 0) {

    /* Math: '<Root>/MathFunction8'
     *
     * About '<Root>/MathFunction8':
     *  Operator: log10
     */
    offset_rate210_MathFunction8_1 = log10(offset_rate210_Sqrt4_1);


  }

}

    }

#ifdef TASK_EXECUTE_0020_COMPLETED
    TASK_EXECUTE_0020_COMPLETED();
#endif
    /*
     * Block: offset_rate210_Gain7
     * Task: 0009
     */

    /* C code */
        {
{

  if (offset_rate210_M->Timing.TaskCounters.TID[3] == 0) {

    /* Gain: '<Root>/Gain7' */
    offset_rate210_Gain7_1 = offset_rate210_P.Gain7_Gain *
      offset_rate210_MathFunction8_1;


  }

}

    }

#ifdef TASK_EXECUTE_0009_COMPLETED
    TASK_EXECUTE_0009_COMPLETED();
#endif
    /*
     * Block: offset_rate210_MathFunction7
     * Task: 0019
     */

    /* C code */
        {
{

  if (offset_rate210_M->Timing.TaskCounters.TID[3] == 0) {

    /* Math: '<Root>/MathFunction7' */
    offset_rate210_MathFunction7_1 = rt_powd_snf(10.0, offset_rate210_Gain7_1);


  }

}

    }

#ifdef TASK_EXECUTE_0019_COMPLETED
    TASK_EXECUTE_0019_COMPLETED();
#endif
    /*
     * Block: offset_rate210_Gain8
     * Task: 0010
     */

    /* C code */
        {
{

  if (offset_rate210_M->Timing.TaskCounters.TID[3] == 0) {

    /* Gain: '<Root>/Gain8' */
    offset_rate210_Gain8_1 = offset_rate210_P.Gain8_Gain *
      offset_rate210_MathFunction7_1;

  }

}

    }

#ifdef TASK_EXECUTE_0010_COMPLETED
    TASK_EXECUTE_0010_COMPLETED();
#endif
    /*
     * Block: offset_rate210_Sqrt5
     * Task: 0026
     */

    /* C code */
        {
{

  if (offset_rate210_M->Timing.TaskCounters.TID[4] == 0) {

    /* Sqrt: '<Root>/Sqrt5' */
    offset_rate210_Sqrt5_1 = sqrt(offset_rate210_Gain8_1);


  }

}

    }

#ifdef TASK_EXECUTE_0026_COMPLETED
    TASK_EXECUTE_0026_COMPLETED();
#endif
    /*
     * Block: offset_rate210_MathFunction10
     * Task: 0013
     */

    /* C code */
        {
{

  if (offset_rate210_M->Timing.TaskCounters.TID[4] == 0) {

    /* Math: '<Root>/MathFunction10'
     *
     * About '<Root>/MathFunction10':
     *  Operator: log10
     */
    offset_rate210_MathFunction10_1 = log10(offset_rate210_Sqrt5_1);


  }

}

    }

#ifdef TASK_EXECUTE_0013_COMPLETED
    TASK_EXECUTE_0013_COMPLETED();
#endif
    /*
     * Block: offset_rate210_Gain9
     * Task: 0011
     */

    /* C code */
        {
{

  if (offset_rate210_M->Timing.TaskCounters.TID[4] == 0) {

    /* Gain: '<Root>/Gain9' */
    offset_rate210_Gain9_1 = offset_rate210_P.Gain9_Gain *
      offset_rate210_MathFunction10_1;


  }

}

    }

#ifdef TASK_EXECUTE_0011_COMPLETED
    TASK_EXECUTE_0011_COMPLETED();
#endif
    /*
     * Block: offset_rate210_MathFunction9
     * Task: 0021
     */

    /* C code */
        {
{

  if (offset_rate210_M->Timing.TaskCounters.TID[4] == 0) {

    /* Math: '<Root>/MathFunction9' */
    offset_rate210_MathFunction9_1 = rt_powd_snf(10.0, offset_rate210_Gain9_1);


  }

}

    }

#ifdef TASK_EXECUTE_0021_COMPLETED
    TASK_EXECUTE_0021_COMPLETED();
#endif
    /*
     * Block: offset_rate210_Gain10
     * Task: 0003
     */

    /* C code */
        {
{

  if (offset_rate210_M->Timing.TaskCounters.TID[4] == 0) {

    /* Gain: '<Root>/Gain10' */
    offset_rate210_Gain10_1 = offset_rate210_P.Gain10_Gain *
      offset_rate210_MathFunction9_1;


  }

}

    }
gettimeofday(&end,NULL);
tmp.tv_sec = end.tv_sec - start.tv_sec;
if (end.tv_usec < start.tv_usec) {
   tmp.tv_sec = tmp.tv_sec - 1;
   tmp.tv_usec = end.tv_usec + 1000000 - start.tv_usec;
} else {
   tmp.tv_usec = end.tv_usec - start.tv_usec;
}
printf("%10ld.%06ld\n",tmp.tv_sec,tmp.tv_usec);
start = end;
#ifdef TASK_EXECUTE_0003_COMPLETED
    TASK_EXECUTE_0003_COMPLETED();
#endif

    /* wait output channel */
    while (1) {
      /* output: offset_rate210_Sum */
      if (CH_0003_0027.flag__0003_0027 == 0) {
	CH_0003_0027.offset_rate210_Gain10_1 = offset_rate210_Gain10_1;
	CH__SYNCM();
	CH_0003_0027.flag__0003_0027 = 1;
	CH__EVENT(TASK_0003,IN_0027);
	CH__END_LOG(OUT_0003);
	break;
      }

      CH__CORE_THREAD_SCHED(OUT_0003,NULL,1);

      CH__MEM_BARRIER();
    }

#ifdef TASK_OUT_0003_COMPLETED
    TASK_OUT_0003_COMPLETED();
#endif
    /*
     * Block: offset_rate210_Sqrt1
     * Update: 0022
     */

    /* wait input channel */
    while (1) {
      /* update: offset_rate210_Gain */
      if (CH_0001_0022.flag__0001_0022 == 1) {
	offset_rate210_Gain_1 = CH_0001_0022.offset_rate210_Gain_1;
	CH__SYNCM();
	CH_0001_0022.flag__0001_0022 = 0;
	CH__EVENT(TASK_0022, OUT_0001);
	CH__END_LOG(IN_0022);
	break;
      }

      CH__CORE_THREAD_SCHED(IN_0022,NULL,1);

      CH__MEM_BARRIER();
    }

#ifdef TASK_UPDATE_IN_0022_COMPLETED
    TASK_UPDATE_IN_0022_COMPLETED();
#endif

    /* Update */
    {
{

  /* Update for UnitDelay: '<Root>/UnitDelay2' */
  offset_rate210_DW.UnitDelay2_DSTATE = offset_rate210_Gain_1;

}

    }

#ifdef TASK_UPDATE_0022_COMPLETED
    TASK_UPDATE_0022_COMPLETED();
#endif
  }
}

CORE_TASK_CODE_PREPARE(1)

/* Core#1 */
void mcos_core1_thread(uint32_t stacd, uintptr_t exinf)
{  /* omit input channel bit vector */
  /* CH__VEC(IN_0001,1); */

  /* output channel bit vector */
  CH__VEC(OUT_0001,2);

  /* input channel bit vector */
  CH__VEC(IN_0027,2);

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0027,1); */

  /* Real-Time Model Object */
  RT_MODEL_offset_rate210_T offset_rate210_M_;
  RT_MODEL_offset_rate210_T * const offset_rate210_M = &offset_rate210_M_;

  /* states */
  struct {
    /* Block: offset_rate210_Gain */
    real_T UnitDelay1_DSTATE; /* task_0001 */

    /* Block: offset_rate210_Sum */
    real_T UnitDelay_DSTATE; /* task_0027 */
  } offset_rate210_DW;

  /* params */
  struct {
    /* Block: offset_rate210_Gain */
    real_T UnitDelay1_InitialCondition;
    real_T Gain_Gain;

    /* Block: offset_rate210_Sum */
    real_T UnitDelay_InitialCondition;
  } offset_rate210_P = {
  2.0,                                 /* Expression: 2
                                        * Referenced by: '<Root>/UnitDelay1'
                                        */

  2.0,                                 /* Expression: 2
                                        * Referenced by: '<Root>/Gain'
                                        */

  1.0                                  /* Expression: 1
                                        * Referenced by: '<Root>/UnitDelay'
                                        */,

  };

  /* internal variables */

  /* Block: offset_rate210_Gain */
  real_T offset_rate210_UnitDelay1_1;

  /* Block: offset_rate210_Sum */
  real_T offset_rate210_UnitDelay_1;

  /* input variables */

  /* Block: offset_rate210_Gain */
  real_T offset_rate210_Sum_1;

  /* Block: offset_rate210_Sum */
  real_T offset_rate210_Gain10_1;
  real_T offset_rate210_Gain_1;

  /* output variables */

  /* Block: offset_rate210_Gain */

  /* Block: offset_rate210_Sum */

  /* Common Initialization */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize Real-Time Model Object */
  /* initialize real-time model */
  (void) memset((void *)offset_rate210_M, 0,
                sizeof(RT_MODEL_offset_rate210_T));

  /* initialize state structure */
  memset(&offset_rate210_DW, 0, sizeof offset_rate210_DW);

  /* Block: offset_rate210_Gain */

  /* initialize states */
{
  /* InitializeConditions for UnitDelay: '<Root>/UnitDelay1' */
  offset_rate210_DW.UnitDelay1_DSTATE =
    offset_rate210_P.UnitDelay1_InitialCondition;

}

  /* initialize task context */
{
  offset_rate210_UnitDelay1_1 = 0.0;
}
{
  offset_rate210_Gain_1 = 0.0;
}

  /* Block: offset_rate210_Sum */

  /* initialize states */
{
  /* InitializeConditions for UnitDelay: '<Root>/UnitDelay' */
  offset_rate210_DW.UnitDelay_DSTATE =
    offset_rate210_P.UnitDelay_InitialCondition;
}

  /* initialize task context */
{
  offset_rate210_UnitDelay_1 = 0.0;
  /* Start for UnitDelay: '<Root>/UnitDelay' */
  offset_rate210_UnitDelay_1 = offset_rate210_P.UnitDelay_InitialCondition;

}
{
  offset_rate210_Sum_1 = 0.0;

}

gettimeofday(&start,NULL);

#ifdef TASK_INITIALIZE_0001_COMPLETED
  TASK_INITIALIZE_0001_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0027_COMPLETED
  TASK_INITIALIZE_0027_COMPLETED();
#endif

  /* task loop */
  while (1) {    /*
     * Block: offset_rate210_Gain
     * Task: 0001
     */

    /* C code */
        {
{

  /* UnitDelay: '<Root>/UnitDelay1' */
  offset_rate210_UnitDelay1_1 = offset_rate210_DW.UnitDelay1_DSTATE;


}

{

  /* Gain: '<Root>/Gain' */
  offset_rate210_Gain_1 = offset_rate210_P.Gain_Gain *
    offset_rate210_UnitDelay1_1;


}

    }

#ifdef TASK_EXECUTE_0001_COMPLETED
    TASK_EXECUTE_0001_COMPLETED();
#endif

    /* wait output channel */
    while (1) {
      /* skip local output CH_0001_0027: offset_rate210_Sum */

      /* output: offset_rate210_Sqrt1 */
      if (CH_0001_0022.flag__0001_0022 == 0) {
	CH_0001_0022.offset_rate210_Gain_1 = offset_rate210_Gain_1;
	CH__SYNCM();
	CH_0001_0022.flag__0001_0022 = 1;
	CH__EVENT(TASK_0001,IN_0022);
	CH__END_LOG(OUT_0001);
	break;
      }

      CH__CORE_THREAD_SCHED(OUT_0001,NULL,1);

      CH__MEM_BARRIER();
    }

#ifdef TASK_OUT_0001_COMPLETED
    TASK_OUT_0001_COMPLETED();
#endif
    /*
     * Block: offset_rate210_Sum
     * Task: 0027
     */

    /* C code */
        {
{

  if (offset_rate210_M->Timing.TaskCounters.TID[4] == 0) {

    /* UnitDelay: '<Root>/UnitDelay' */
    offset_rate210_UnitDelay_1 = offset_rate210_DW.UnitDelay_DSTATE;

  }

}

{

  /* Sum: '<Root>/Sum' */
  offset_rate210_Sum_1 = offset_rate210_UnitDelay_1 + offset_rate210_Gain_1;


}

    }

#ifdef TASK_EXECUTE_0027_COMPLETED
    TASK_EXECUTE_0027_COMPLETED();
#endif
    /*
     * Block: offset_rate210_Gain
     * Update: 0001
     */

    /* Update */
    {
{

  /* Update for UnitDelay: '<Root>/UnitDelay1' */
  offset_rate210_DW.UnitDelay1_DSTATE = offset_rate210_Sum_1;


}

    }

#ifdef TASK_UPDATE_0001_COMPLETED
    TASK_UPDATE_0001_COMPLETED();
#endif
    /*
     * Block: offset_rate210_Sum
     * Update: 0027
     */

    /* wait input channel */
    while (1) {
      /* update: offset_rate210_Gain10 */
      if (CH_0003_0027.flag__0003_0027 == 1) {
	offset_rate210_Gain10_1 = CH_0003_0027.offset_rate210_Gain10_1;
	CH__SYNCM();
	CH_0003_0027.flag__0003_0027 = 0;
	CH__EVENT(TASK_0027, OUT_0003);
	CH__END_LOG(IN_0027);
	break;
      }

      CH__CORE_THREAD_SCHED(IN_0027,NULL,1);

      CH__MEM_BARRIER();
    }

#ifdef TASK_UPDATE_IN_0027_COMPLETED
    TASK_UPDATE_IN_0027_COMPLETED();
#endif

    /* Update */
    {
{

  if (offset_rate210_M->Timing.TaskCounters.TID[4] == 0) {

    /* Update for UnitDelay: '<Root>/UnitDelay' */
    offset_rate210_DW.UnitDelay_DSTATE = offset_rate210_Gain10_1;

  }

}

    }



#ifdef TASK_UPDATE_0027_COMPLETED
    TASK_UPDATE_0027_COMPLETED();
#endif
  }
}

TASK_CODE_PREPARE(0000)

/* Block: t0 */
void mcos_lcore_task_0000(uint32_t stacd, uintptr_t extinfo)
{
  /* Common Initialization */
  rt_InitInfAndNaN(sizeof(real_T));

#ifdef TASK_INITIALIZE_0000_COMPLETED
  TASK_INITIALIZE_0000_COMPLETED();
#endif

  /* task loop */
  while (1) {

#ifdef TASK_EXECUTE_0000_COMPLETED
    TASK_EXECUTE_0000_COMPLETED();
#endif
  }
}

TASK_CODE_PREPARE(0100)

/* Block: extout */
void mcos_lcore_task_0100(uint32_t stacd, uintptr_t extinfo)
{
  /* Common Initialization */
  rt_InitInfAndNaN(sizeof(real_T));

#ifdef TASK_INITIALIZE_0100_COMPLETED
  TASK_INITIALIZE_0100_COMPLETED();
#endif

  /* task loop */
  while (1) {

#ifdef TASK_EXECUTE_0100_COMPLETED
    TASK_EXECUTE_0100_COMPLETED();
#endif

    /****************************************************
     *
     * You may insert some codes here for external output.
     *
     ****************************************************/
  }
}

/*
 * MCOS thread creation
 *
 *   create_init_threads
 */
void
create_init_threads (void)
{
  mcos_erid_t tid;
  mcos_id_t lcid;
  mcos_threadattr_t attr;
  static mcos_id_t tids[4];
  size_t num = 0;
  size_t i;

  mcos_threadattr_init (&attr);

  mcos_threadattr_setlcid (&attr, 1);
  mcos_threadattr_setpriority (&attr, CORE_0_PRIORITY);
  mcos_threadattr_setstacksize (&attr, CORE_0_STACK_SIZE);
  tid = mcos_thread_create (&attr, mcos_core0_thread, 0);
  if (tid == MC_EPAR || tid == MC_ENOMEM)
    return;
  tids[num++] = tid;

  mcos_threadattr_setlcid (&attr, 2);
  mcos_threadattr_setpriority (&attr, CORE_1_PRIORITY);
  mcos_threadattr_setstacksize (&attr, CORE_1_STACK_SIZE);
  tid = mcos_thread_create (&attr, mcos_core1_thread, 0);
  if (tid == MC_EPAR || tid == MC_ENOMEM)
    return;
  tids[num++] = tid;

  mcos_threadattr_setlcid (&attr, LCID_ANY);
  mcos_threadattr_setpriority (&attr, LCORE_PRIORITY);

#ifdef MCOS_LCORE_TASK_0000_STATCK_SIZE
  mcos_threadattr_setstacksize (&attr, MCOS_LCORE_TASK_0000_STATCK_SIZE);
#else
  mcos_threadattr_setstacksize (&attr, LCORE_STACK_SIZE);
#endif
  tid = mcos_thread_create (&attr, mcos_lcore_task_0000, 0);
  if (tid == MC_EPAR || tid == MC_ENOMEM)
    return;
  tids[num++] = tid;

#ifdef MCOS_LCORE_TASK_0100_STATCK_SIZE
  mcos_threadattr_setstacksize (&attr, MCOS_LCORE_TASK_0100_STATCK_SIZE);
#else
  mcos_threadattr_setstacksize (&attr, LCORE_STACK_SIZE);
#endif
  tid = mcos_thread_create (&attr, mcos_lcore_task_0100, 0);
  if (tid == MC_EPAR || tid == MC_ENOMEM)
    return;
  tids[num++] = tid;

  for (i = 0; i < num; i++) {
    mcos_thread_start (tids[i], 0);
  }
}
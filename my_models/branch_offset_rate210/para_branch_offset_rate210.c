#include <mcos/mcos.h>
#include <mcos/mcos_ds.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include "rtwtypes.h"
#include "branch_offset_rate210_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"


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
#include "branch_offset_rate210_private.h"

#include "para_branch_offset_rate210_res.c"


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

#define CH__TIME_LT(L,R)	((long)((L)-(R)) < (long)0)
#define CH__TIME_LE(L,R)	((long)((L)-(R)) <= (long)0)
#define CH__SEND_COUNT(N,D,R)	(((N)-(D)+((R)-1))/R)

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

/* From: branch_offset_rate210_Gain
   To: branch_offset_rate210_Sum */
typedef struct {
  int flag__0001_0067;
  real_T branch_offset_rate210_Gain_1;
} TYPE_0001_0067;
TYPE_0001_0067 CH_0001_0067;

/* From: branch_offset_rate210_Gain
   To: branch_offset_rate210_UnitDelay2 */
typedef struct {
  int flag__0001_0070;
  real_T branch_offset_rate210_Gain_1;
} TYPE_0001_0070;
TYPE_0001_0070 CH_0001_0070;

/* From: branch_offset_rate210_Subsystem_Add
   To: branch_offset_rate210_Subsystem_Sqrt2 */
typedef struct {
  int flag__0004_0062;
  real_T branch_offset_rate210_Subsystem_Add_1;
} TYPE_0004_0062;
TYPE_0004_0062 CH_0004_0062;

/* From: branch_offset_rate210_Subsystem_Add1
   To: branch_offset_rate210_Subsystem_Add */
typedef struct {
  int flag__0005_0004;
  real_T branch_offset_rate210_Subsystem_Add1_1;
} TYPE_0005_0004;
TYPE_0005_0004 CH_0005_0004;

/* From: branch_offset_rate210_Subsystem_Add2
   To: branch_offset_rate210_Subsystem_MathFunction13 */
typedef struct {
  int flag__0006_0042;
  real_T branch_offset_rate210_Subsystem_Add2_1;
} TYPE_0006_0042;
TYPE_0006_0042 CH_0006_0042;

/* From: branch_offset_rate210_Subsystem_Add2
   To: branch_offset_rate210_Subsystem_MathFunction17 */
typedef struct {
  int flag__0006_0046;
  real_T branch_offset_rate210_Subsystem_Add2_1;
} TYPE_0006_0046;
TYPE_0006_0046 CH_0006_0046;

/* From: branch_offset_rate210_Subsystem_Add3
   To: branch_offset_rate210_Subsystem_Sqrt5 */
typedef struct {
  int flag__0007_0065;
  real_T branch_offset_rate210_Subsystem_Add3_1;
} TYPE_0007_0065;
TYPE_0007_0065 CH_0007_0065;

/* From: branch_offset_rate210_Subsystem_Add4
   To: branch_offset_rate210_Subsystem_Add3 */
typedef struct {
  int flag__0008_0007;
  real_T branch_offset_rate210_Subsystem_Add4_1;
} TYPE_0008_0007;
TYPE_0008_0007 CH_0008_0007;

/* From: branch_offset_rate210_Subsystem_Gain
   To: branch_offset_rate210_Subsystem_Gain2 */
typedef struct {
  int flag__0009_0021;
  real_T branch_offset_rate210_Subsystem_Gain_1;
} TYPE_0009_0021;
TYPE_0009_0021 CH_0009_0021;

/* From: branch_offset_rate210_Subsystem_Gain1
   To: branch_offset_rate210_Subsystem_MathFunction1 */
typedef struct {
  int flag__0010_0038;
  real_T branch_offset_rate210_Subsystem_Gain1_1;
} TYPE_0010_0038;
TYPE_0010_0038 CH_0010_0038;

/* From: branch_offset_rate210_Subsystem_Gain10
   To: branch_offset_rate210_UnitDelay */
typedef struct {
  int flag__0011_0068;
  real_T branch_offset_rate210_Subsystem_Gain10_1;
} TYPE_0011_0068;
TYPE_0011_0068 CH_0011_0068;

/* From: branch_offset_rate210_Subsystem_Gain11
   To: branch_offset_rate210_Subsystem_Add1 */
typedef struct {
  int flag__0012_0005;
  real_T branch_offset_rate210_Subsystem_Gain11_1;
} TYPE_0012_0005;
TYPE_0012_0005 CH_0012_0005;

/* From: branch_offset_rate210_Subsystem_Gain12
   To: branch_offset_rate210_Subsystem_Gain14 */
typedef struct {
  int flag__0013_0015;
  real_T branch_offset_rate210_Subsystem_Gain12_1;
} TYPE_0013_0015;
TYPE_0013_0015 CH_0013_0015;

/* From: branch_offset_rate210_Subsystem_Gain13
   To: branch_offset_rate210_Subsystem_Add2 */
typedef struct {
  int flag__0014_0006;
  real_T branch_offset_rate210_Subsystem_Gain13_1;
} TYPE_0014_0006;
TYPE_0014_0006 CH_0014_0006;

/* From: branch_offset_rate210_Subsystem_Gain14
   To: branch_offset_rate210_Subsystem_Add2 */
typedef struct {
  int flag__0015_0006;
  real_T branch_offset_rate210_Subsystem_Gain14_1;
} TYPE_0015_0006;
TYPE_0015_0006 CH_0015_0006;

/* From: branch_offset_rate210_Subsystem_Gain15
   To: branch_offset_rate210_Subsystem_MathFunction14 */
typedef struct {
  int flag__0016_0043;
  real_T branch_offset_rate210_Subsystem_Gain15_1;
} TYPE_0016_0043;
TYPE_0016_0043 CH_0016_0043;

/* From: branch_offset_rate210_Subsystem_Gain16
   To: branch_offset_rate210_Subsystem_Gain17 */
typedef struct {
  int flag__0017_0018;
  real_T branch_offset_rate210_Subsystem_Gain16_1;
} TYPE_0017_0018;
TYPE_0017_0018 CH_0017_0018;

/* From: branch_offset_rate210_Subsystem_Gain17
   To: branch_offset_rate210_Subsystem_MathFunction12 */
typedef struct {
  int flag__0018_0041;
  real_T branch_offset_rate210_Subsystem_Gain17_1;
} TYPE_0018_0041;
TYPE_0018_0041 CH_0018_0041;

/* From: branch_offset_rate210_Subsystem_Gain18
   To: branch_offset_rate210_Subsystem_Add4 */
typedef struct {
  int flag__0019_0008;
  real_T branch_offset_rate210_Subsystem_Gain18_1;
} TYPE_0019_0008;
TYPE_0019_0008 CH_0019_0008;

/* From: branch_offset_rate210_Subsystem_Gain19
   To: branch_offset_rate210_Subsystem_Gain20 */
typedef struct {
  int flag__0020_0022;
  real_T branch_offset_rate210_Subsystem_Gain19_1;
} TYPE_0020_0022;
TYPE_0020_0022 CH_0020_0022;

/* From: branch_offset_rate210_Subsystem_Gain2
   To: branch_offset_rate210_Subsystem_Add1 */
typedef struct {
  int flag__0021_0005;
  real_T branch_offset_rate210_Subsystem_Gain2_1;
} TYPE_0021_0005;
TYPE_0021_0005 CH_0021_0005;

/* From: branch_offset_rate210_Subsystem_Gain20
   To: branch_offset_rate210_Subsystem_Gain15 */
typedef struct {
  int flag__0022_0016;
  real_T branch_offset_rate210_Subsystem_Gain20_1;
} TYPE_0022_0016;
TYPE_0022_0016 CH_0022_0016;

/* From: branch_offset_rate210_Subsystem_Gain21
   To: branch_offset_rate210_Subsystem_Gain16 */
typedef struct {
  int flag__0023_0017;
  real_T branch_offset_rate210_Subsystem_Gain21_1;
} TYPE_0023_0017;
TYPE_0023_0017 CH_0023_0017;

/* From: branch_offset_rate210_Subsystem_Gain22
   To: branch_offset_rate210_Subsystem_MathFunction18 */
typedef struct {
  int flag__0024_0047;
  real_T branch_offset_rate210_Subsystem_Gain22_1;
} TYPE_0024_0047;
TYPE_0024_0047 CH_0024_0047;

/* From: branch_offset_rate210_Subsystem_Gain23
   To: branch_offset_rate210_Subsystem_Gain24 */
typedef struct {
  int flag__0025_0026;
  real_T branch_offset_rate210_Subsystem_Gain23_1;
} TYPE_0025_0026;
TYPE_0025_0026 CH_0025_0026;

/* From: branch_offset_rate210_Subsystem_Gain24
   To: branch_offset_rate210_Subsystem_MathFunction16 */
typedef struct {
  int flag__0026_0045;
  real_T branch_offset_rate210_Subsystem_Gain24_1;
} TYPE_0026_0045;
TYPE_0026_0045 CH_0026_0045;

/* From: branch_offset_rate210_Subsystem_Gain25
   To: branch_offset_rate210_Subsystem_Add4 */
typedef struct {
  int flag__0027_0008;
  real_T branch_offset_rate210_Subsystem_Gain25_1;
} TYPE_0027_0008;
TYPE_0027_0008 CH_0027_0008;

/* From: branch_offset_rate210_Subsystem_Gain26
   To: branch_offset_rate210_Subsystem_Gain27 */
typedef struct {
  int flag__0028_0029;
  real_T branch_offset_rate210_Subsystem_Gain26_1;
} TYPE_0028_0029;
TYPE_0028_0029 CH_0028_0029;

/* From: branch_offset_rate210_Subsystem_Gain27
   To: branch_offset_rate210_Subsystem_Gain22 */
typedef struct {
  int flag__0029_0024;
  real_T branch_offset_rate210_Subsystem_Gain27_1;
} TYPE_0029_0024;
TYPE_0029_0024 CH_0029_0024;

/* From: branch_offset_rate210_Subsystem_Gain28
   To: branch_offset_rate210_Subsystem_Gain23 */
typedef struct {
  int flag__0030_0025;
  real_T branch_offset_rate210_Subsystem_Gain28_1;
} TYPE_0030_0025;
TYPE_0030_0025 CH_0030_0025;

/* From: branch_offset_rate210_Subsystem_Gain3
   To: branch_offset_rate210_Subsystem_MathFunction3 */
typedef struct {
  int flag__0031_0049;
  real_T branch_offset_rate210_Subsystem_Gain3_1;
} TYPE_0031_0049;
TYPE_0031_0049 CH_0031_0049;

/* From: branch_offset_rate210_Subsystem_Gain4
   To: branch_offset_rate210_Subsystem_Sqrt3 */
typedef struct {
  int flag__0032_0063;
  real_T branch_offset_rate210_Subsystem_Gain4_1;
} TYPE_0032_0063;
TYPE_0032_0063 CH_0032_0063;

/* From: branch_offset_rate210_Subsystem_Gain5
   To: branch_offset_rate210_Subsystem_MathFunction5 */
typedef struct {
  int flag__0033_0051;
  real_T branch_offset_rate210_Subsystem_Gain5_1;
} TYPE_0033_0051;
TYPE_0033_0051 CH_0033_0051;

/* From: branch_offset_rate210_Subsystem_Gain6
   To: branch_offset_rate210_Subsystem_Sqrt4 */
typedef struct {
  int flag__0034_0064;
  real_T branch_offset_rate210_Subsystem_Gain6_1;
} TYPE_0034_0064;
TYPE_0034_0064 CH_0034_0064;

/* From: branch_offset_rate210_Subsystem_Gain7
   To: branch_offset_rate210_Subsystem_MathFunction7 */
typedef struct {
  int flag__0035_0053;
  real_T branch_offset_rate210_Subsystem_Gain7_1;
} TYPE_0035_0053;
TYPE_0035_0053 CH_0035_0053;

/* From: branch_offset_rate210_Subsystem_Gain8
   To: branch_offset_rate210_Subsystem_Add3 */
typedef struct {
  int flag__0036_0007;
  real_T branch_offset_rate210_Subsystem_Gain8_1;
} TYPE_0036_0007;
TYPE_0036_0007 CH_0036_0007;

/* From: branch_offset_rate210_Subsystem_Gain9
   To: branch_offset_rate210_Subsystem_MathFunction9 */
typedef struct {
  int flag__0037_0055;
  real_T branch_offset_rate210_Subsystem_Gain9_1;
} TYPE_0037_0055;
TYPE_0037_0055 CH_0037_0055;

/* From: branch_offset_rate210_Subsystem_MathFunction1
   To: branch_offset_rate210_Subsystem_Add */
typedef struct {
  int flag__0038_0004;
  real_T branch_offset_rate210_Subsystem_MathFunction1_1;
} TYPE_0038_0004;
TYPE_0038_0004 CH_0038_0004;

/* From: branch_offset_rate210_Subsystem_MathFunction10
   To: branch_offset_rate210_Subsystem_S_Function4 */
typedef struct {
  int flag__0039_0060;
  real_T branch_offset_rate210_Subsystem_MathFunction10_1;
} TYPE_0039_0060;
TYPE_0039_0060 CH_0039_0060;

/* From: branch_offset_rate210_Subsystem_MathFunction11
   To: branch_offset_rate210_Subsystem_Gain21 */
typedef struct {
  int flag__0040_0023;
  real_T branch_offset_rate210_Subsystem_MathFunction11_1;
} TYPE_0040_0023;
TYPE_0040_0023 CH_0040_0023;

/* From: branch_offset_rate210_Subsystem_MathFunction12
   To: branch_offset_rate210_Subsystem_Gain18 */
typedef struct {
  int flag__0041_0019;
  real_T branch_offset_rate210_Subsystem_MathFunction12_1;
} TYPE_0041_0019;
TYPE_0041_0019 CH_0041_0019;

/* From: branch_offset_rate210_Subsystem_MathFunction13
   To: branch_offset_rate210_Subsystem_Gain19 */
typedef struct {
  int flag__0042_0020;
  real_T branch_offset_rate210_Subsystem_MathFunction13_1;
} TYPE_0042_0020;
TYPE_0042_0020 CH_0042_0020;

/* From: branch_offset_rate210_Subsystem_MathFunction14
   To: branch_offset_rate210_Subsystem_MathFunction11 */
typedef struct {
  int flag__0043_0040;
  real_T branch_offset_rate210_Subsystem_MathFunction14_1;
} TYPE_0043_0040;
TYPE_0043_0040 CH_0043_0040;

/* From: branch_offset_rate210_Subsystem_MathFunction15
   To: branch_offset_rate210_Subsystem_Gain28 */
typedef struct {
  int flag__0044_0030;
  real_T branch_offset_rate210_Subsystem_MathFunction15_1;
} TYPE_0044_0030;
TYPE_0044_0030 CH_0044_0030;

/* From: branch_offset_rate210_Subsystem_MathFunction16
   To: branch_offset_rate210_Subsystem_Gain25 */
typedef struct {
  int flag__0045_0027;
  real_T branch_offset_rate210_Subsystem_MathFunction16_1;
} TYPE_0045_0027;
TYPE_0045_0027 CH_0045_0027;

/* From: branch_offset_rate210_Subsystem_MathFunction17
   To: branch_offset_rate210_Subsystem_Gain26 */
typedef struct {
  int flag__0046_0028;
  real_T branch_offset_rate210_Subsystem_MathFunction17_1;
} TYPE_0046_0028;
TYPE_0046_0028 CH_0046_0028;

/* From: branch_offset_rate210_Subsystem_MathFunction18
   To: branch_offset_rate210_Subsystem_MathFunction15 */
typedef struct {
  int flag__0047_0044;
  real_T branch_offset_rate210_Subsystem_MathFunction18_1;
} TYPE_0047_0044;
TYPE_0047_0044 CH_0047_0044;

/* From: branch_offset_rate210_Subsystem_MathFunction2
   To: branch_offset_rate210_Subsystem_S_Function */
typedef struct {
  int flag__0048_0056;
  real_T branch_offset_rate210_Subsystem_MathFunction2_1;
} TYPE_0048_0056;
TYPE_0048_0056 CH_0048_0056;

/* From: branch_offset_rate210_Subsystem_MathFunction3
   To: branch_offset_rate210_Subsystem_Gain4 */
typedef struct {
  int flag__0049_0032;
  real_T branch_offset_rate210_Subsystem_MathFunction3_1;
} TYPE_0049_0032;
TYPE_0049_0032 CH_0049_0032;

/* From: branch_offset_rate210_Subsystem_MathFunction4
   To: branch_offset_rate210_Subsystem_S_Function1 */
typedef struct {
  int flag__0050_0057;
  real_T branch_offset_rate210_Subsystem_MathFunction4_1;
} TYPE_0050_0057;
TYPE_0050_0057 CH_0050_0057;

/* From: branch_offset_rate210_Subsystem_MathFunction5
   To: branch_offset_rate210_Subsystem_Gain6 */
typedef struct {
  int flag__0051_0034;
  real_T branch_offset_rate210_Subsystem_MathFunction5_1;
} TYPE_0051_0034;
TYPE_0051_0034 CH_0051_0034;

/* From: branch_offset_rate210_Subsystem_MathFunction6
   To: branch_offset_rate210_Subsystem_S_Function2 */
typedef struct {
  int flag__0052_0058;
  real_T branch_offset_rate210_Subsystem_MathFunction6_1;
} TYPE_0052_0058;
TYPE_0052_0058 CH_0052_0058;

/* From: branch_offset_rate210_Subsystem_MathFunction7
   To: branch_offset_rate210_Subsystem_Gain8 */
typedef struct {
  int flag__0053_0036;
  real_T branch_offset_rate210_Subsystem_MathFunction7_1;
} TYPE_0053_0036;
TYPE_0053_0036 CH_0053_0036;

/* From: branch_offset_rate210_Subsystem_MathFunction8
   To: branch_offset_rate210_Subsystem_S_Function3 */
typedef struct {
  int flag__0054_0059;
  real_T branch_offset_rate210_Subsystem_MathFunction8_1;
} TYPE_0054_0059;
TYPE_0054_0059 CH_0054_0059;

/* From: branch_offset_rate210_Subsystem_MathFunction9
   To: branch_offset_rate210_Subsystem_Gain10 */
typedef struct {
  int flag__0055_0011;
  real_T branch_offset_rate210_Subsystem_MathFunction9_1;
} TYPE_0055_0011;
TYPE_0055_0011 CH_0055_0011;

/* From: branch_offset_rate210_Subsystem_S_Function
   To: branch_offset_rate210_Subsystem_Gain1 */
typedef struct {
  int flag__0056_0010;
  real_T branch_offset_rate210_Subsystem_S_Function_1;
} TYPE_0056_0010;
TYPE_0056_0010 CH_0056_0010;

/* From: branch_offset_rate210_Subsystem_S_Function1
   To: branch_offset_rate210_Subsystem_Gain3 */
typedef struct {
  int flag__0057_0031;
  real_T branch_offset_rate210_Subsystem_S_Function1_1;
} TYPE_0057_0031;
TYPE_0057_0031 CH_0057_0031;

/* From: branch_offset_rate210_Subsystem_S_Function2
   To: branch_offset_rate210_Subsystem_Gain5 */
typedef struct {
  int flag__0058_0033;
  real_T branch_offset_rate210_Subsystem_S_Function2_1;
} TYPE_0058_0033;
TYPE_0058_0033 CH_0058_0033;

/* From: branch_offset_rate210_Subsystem_S_Function3
   To: branch_offset_rate210_Subsystem_Gain7 */
typedef struct {
  int flag__0059_0035;
  real_T branch_offset_rate210_Subsystem_S_Function3_1;
} TYPE_0059_0035;
TYPE_0059_0035 CH_0059_0035;

/* From: branch_offset_rate210_Subsystem_S_Function4
   To: branch_offset_rate210_Subsystem_Gain9 */
typedef struct {
  int flag__0060_0037;
  real_T branch_offset_rate210_Subsystem_S_Function4_1;
} TYPE_0060_0037;
TYPE_0060_0037 CH_0060_0037;

/* From: branch_offset_rate210_Subsystem_Sqrt1
   To: branch_offset_rate210_Subsystem_Gain */
typedef struct {
  int flag__0061_0009;
  real_T branch_offset_rate210_Subsystem_Sqrt1_1;
} TYPE_0061_0009;
TYPE_0061_0009 CH_0061_0009;

/* From: branch_offset_rate210_Subsystem_Sqrt1
   To: branch_offset_rate210_Subsystem_Gain11 */
typedef struct {
  int flag__0061_0012;
  real_T branch_offset_rate210_Subsystem_Sqrt1_1;
} TYPE_0061_0012;
TYPE_0061_0012 CH_0061_0012;

/* From: branch_offset_rate210_Subsystem_Sqrt1
   To: branch_offset_rate210_Subsystem_MathFunction2 */
typedef struct {
  int flag__0061_0048;
  real_T branch_offset_rate210_Subsystem_Sqrt1_1;
} TYPE_0061_0048;
TYPE_0061_0048 CH_0061_0048;

/* From: branch_offset_rate210_Subsystem_Sqrt2
   To: branch_offset_rate210_Subsystem_Gain12 */
typedef struct {
  int flag__0062_0013;
  real_T branch_offset_rate210_Subsystem_Sqrt2_1;
} TYPE_0062_0013;
TYPE_0062_0013 CH_0062_0013;

/* From: branch_offset_rate210_Subsystem_Sqrt2
   To: branch_offset_rate210_Subsystem_Gain13 */
typedef struct {
  int flag__0062_0014;
  real_T branch_offset_rate210_Subsystem_Sqrt2_1;
} TYPE_0062_0014;
TYPE_0062_0014 CH_0062_0014;

/* From: branch_offset_rate210_Subsystem_Sqrt2
   To: branch_offset_rate210_Subsystem_MathFunction4 */
typedef struct {
  int flag__0062_0050;
  real_T branch_offset_rate210_Subsystem_Sqrt2_1;
} TYPE_0062_0050;
TYPE_0062_0050 CH_0062_0050;

/* From: branch_offset_rate210_Subsystem_Sqrt3
   To: branch_offset_rate210_Subsystem_MathFunction6 */
typedef struct {
  int flag__0063_0052;
  real_T branch_offset_rate210_Subsystem_Sqrt3_1;
} TYPE_0063_0052;
TYPE_0063_0052 CH_0063_0052;

/* From: branch_offset_rate210_Subsystem_Sqrt4
   To: branch_offset_rate210_Subsystem_MathFunction8 */
typedef struct {
  int flag__0064_0054;
  real_T branch_offset_rate210_Subsystem_Sqrt4_1;
} TYPE_0064_0054;
TYPE_0064_0054 CH_0064_0054;

/* From: branch_offset_rate210_Subsystem_Sqrt5
   To: branch_offset_rate210_Subsystem_MathFunction10 */
typedef struct {
  int flag__0065_0039;
  real_T branch_offset_rate210_Subsystem_Sqrt5_1;
} TYPE_0065_0039;
TYPE_0065_0039 CH_0065_0039;

/* From: branch_offset_rate210_Sum
   To: branch_offset_rate210_Gain */
typedef struct {
  int flag__0067_0001;
  real_T branch_offset_rate210_Sum_1;
} TYPE_0067_0001;
TYPE_0067_0001 CH_0067_0001;

/* From: branch_offset_rate210_UnitDelay
   To: branch_offset_rate210_Sum
    [10000] -> [2000] */
typedef struct {
  int flag__0068_0067;
  unsigned long time__0068_0067;
  real_T branch_offset_rate210_UnitDelay_1;
} TYPE_0068_0067;
TYPE_0068_0067 CH_0068_0067;

/* From: branch_offset_rate210_UnitDelay2
   To: branch_offset_rate210_Subsystem_Sqrt1
    [2000] -> [10000] */
typedef struct {
  int flag__0070_0061;
  unsigned long time__0070_0061;
  real_T branch_offset_rate210_UnitDelay2_1;
} TYPE_0070_0061;
TYPE_0070_0061 CH_0070_0061;

/*
 * Tasks
 */

CORE_TASK_CODE_PREPARE(0)

/* Core#0 */
/* rate: 10000 */
void mcos_core0_thread(uint32_t stacd, uintptr_t exinf)
{
  /* task time */
  unsigned long task__time = 0;
  const unsigned long task__rate = 10000;

  /* multirate */
  /* omit input channel bit vector */
  /* CH__VEC(IN_0061,1); */

  /* output channel bit vector */
  CH__VEC(OUT_0061,3);

  /* omit input channel bit vector */
  /* CH__VEC(IN_0012,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0012,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0009,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0009,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0021,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0021,1); */

  /* input channel bit vector */
  CH__VEC(IN_0005,2);

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0005,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0048,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0048,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0056,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0056,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0010,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0010,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0038,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0038,1); */

  /* input channel bit vector */
  CH__VEC(IN_0004,2);

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0004,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0062,1); */

  /* output channel bit vector */
  CH__VEC(OUT_0062,3);

  /* omit input channel bit vector */
  /* CH__VEC(IN_0014,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0014,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0013,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0013,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0015,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0015,1); */

  /* input channel bit vector */
  CH__VEC(IN_0006,2);

  /* output channel bit vector */
  CH__VEC(OUT_0006,2);

  /* omit input channel bit vector */
  /* CH__VEC(IN_0046,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0046,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0028,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0028,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0029,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0029,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0024,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0024,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0047,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0047,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0044,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0044,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0030,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0030,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0025,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0025,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0026,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0026,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0045,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0045,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0027,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0027,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0042,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0042,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0020,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0020,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0022,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0022,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0016,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0016,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0043,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0043,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0040,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0040,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0023,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0023,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0017,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0017,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0018,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0018,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0041,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0041,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0019,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0019,1); */

  /* input channel bit vector */
  CH__VEC(IN_0008,2);

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0008,1); */

  /* params */
  struct {
    /* Block: branch_offset_rate210_Subsystem_Gain11 */
    real_T Gain11_Gain;

    /* Block: branch_offset_rate210_Subsystem_Gain */
    real_T Gain_Gain_j;

    /* Block: branch_offset_rate210_Subsystem_Gain2 */
    real_T Gain2_Gain;

    /* Block: branch_offset_rate210_Subsystem_Gain1 */
    real_T Gain1_Gain;

    /* Block: branch_offset_rate210_Subsystem_Gain13 */
    real_T Gain13_Gain;

    /* Block: branch_offset_rate210_Subsystem_Gain12 */
    real_T Gain12_Gain;

    /* Block: branch_offset_rate210_Subsystem_Gain14 */
    real_T Gain14_Gain;

    /* Block: branch_offset_rate210_Subsystem_Gain26 */
    real_T Gain26_Gain;

    /* Block: branch_offset_rate210_Subsystem_Gain27 */
    real_T Gain27_Gain;

    /* Block: branch_offset_rate210_Subsystem_Gain22 */
    real_T Gain22_Gain;

    /* Block: branch_offset_rate210_Subsystem_Gain28 */
    real_T Gain28_Gain;

    /* Block: branch_offset_rate210_Subsystem_Gain23 */
    real_T Gain23_Gain;

    /* Block: branch_offset_rate210_Subsystem_Gain24 */
    real_T Gain24_Gain;

    /* Block: branch_offset_rate210_Subsystem_Gain25 */
    real_T Gain25_Gain;

    /* Block: branch_offset_rate210_Subsystem_Gain19 */
    real_T Gain19_Gain;

    /* Block: branch_offset_rate210_Subsystem_Gain20 */
    real_T Gain20_Gain;

    /* Block: branch_offset_rate210_Subsystem_Gain15 */
    real_T Gain15_Gain;

    /* Block: branch_offset_rate210_Subsystem_Gain21 */
    real_T Gain21_Gain;

    /* Block: branch_offset_rate210_Subsystem_Gain16 */
    real_T Gain16_Gain;

    /* Block: branch_offset_rate210_Subsystem_Gain17 */
    real_T Gain17_Gain;

    /* Block: branch_offset_rate210_Subsystem_Gain18 */
    real_T Gain18_Gain;
  } branch_offset_rate210_P = {
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S1>/Gain11'
                                        */

  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S1>/Gain'
                                        */

  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S1>/Gain2'
                                        */

  2.0,                                 /* Expression: 2
                                        * Referenced by: '<S1>/Gain1'
                                        */

  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S1>/Gain13'
                                        */

  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S1>/Gain12'
                                        */

  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S1>/Gain14'
                                        */

  0.5,                                 /* Expression: 0.5
                                        * Referenced by: '<S1>/Gain26'
                                        */

  2.0,                                 /* Expression: 2
                                        * Referenced by: '<S1>/Gain27'
                                        */

  2.0,                                 /* Expression: 2
                                        * Referenced by: '<S1>/Gain22'
                                        */

  0.5,                                 /* Expression: 0.5
                                        * Referenced by: '<S1>/Gain28'
                                        */

  0.5,                                 /* Expression: 0.5
                                        * Referenced by: '<S1>/Gain23'
                                        */

  2.0,                                 /* Expression: 2
                                        * Referenced by: '<S1>/Gain24'
                                        */

  0.5,                                 /* Expression: 0.5
                                        * Referenced by: '<S1>/Gain25'
                                        */

  0.5,                                 /* Expression: 0.5
                                        * Referenced by: '<S1>/Gain19'
                                        */

  2.0,                                 /* Expression: 2
                                        * Referenced by: '<S1>/Gain20'
                                        */

  2.0,                                 /* Expression: 2
                                        * Referenced by: '<S1>/Gain15'
                                        */

  0.5,                                 /* Expression: 0.5
                                        * Referenced by: '<S1>/Gain21'
                                        */

  0.5,                                 /* Expression: 0.5
                                        * Referenced by: '<S1>/Gain16'
                                        */

  2.0,                                 /* Expression: 2
                                        * Referenced by: '<S1>/Gain17'
                                        */

  0.5,                                 /* Expression: 0.5
                                        * Referenced by: '<S1>/Gain18'
                                        */

  };

  /* input variables */

  /* Block: branch_offset_rate210_Subsystem_Sqrt1 */
  real_T branch_offset_rate210_UnitDelay2_1;

  /* Block: branch_offset_rate210_Subsystem_Gain11 */
  real_T branch_offset_rate210_Subsystem_Sqrt1_1;

  /* Block: branch_offset_rate210_Subsystem_Gain */

  /* Block: branch_offset_rate210_Subsystem_Gain2 */
  real_T branch_offset_rate210_Subsystem_Gain_1;

  /* Block: branch_offset_rate210_Subsystem_Add1 */
  real_T branch_offset_rate210_Subsystem_Gain11_1;
  real_T branch_offset_rate210_Subsystem_Gain2_1;

  /* Block: branch_offset_rate210_Subsystem_MathFunction2 */

  /* Block: branch_offset_rate210_Subsystem_S_Function */
  real_T branch_offset_rate210_Subsystem_MathFunction2_1;

  /* Block: branch_offset_rate210_Subsystem_Gain1 */
  real_T branch_offset_rate210_Subsystem_S_Function_1;

  /* Block: branch_offset_rate210_Subsystem_MathFunction1 */
  real_T branch_offset_rate210_Subsystem_Gain1_1;

  /* Block: branch_offset_rate210_Subsystem_Add */
  real_T branch_offset_rate210_Subsystem_Add1_1;
  real_T branch_offset_rate210_Subsystem_MathFunction1_1;

  /* Block: branch_offset_rate210_Subsystem_Sqrt2 */
  real_T branch_offset_rate210_Subsystem_Add_1;

  /* Block: branch_offset_rate210_Subsystem_Gain13 */
  real_T branch_offset_rate210_Subsystem_Sqrt2_1;

  /* Block: branch_offset_rate210_Subsystem_Gain12 */

  /* Block: branch_offset_rate210_Subsystem_Gain14 */
  real_T branch_offset_rate210_Subsystem_Gain12_1;

  /* Block: branch_offset_rate210_Subsystem_Add2 */
  real_T branch_offset_rate210_Subsystem_Gain13_1;
  real_T branch_offset_rate210_Subsystem_Gain14_1;

  /* Block: branch_offset_rate210_Subsystem_MathFunction17 */
  real_T branch_offset_rate210_Subsystem_Add2_1;

  /* Block: branch_offset_rate210_Subsystem_Gain26 */
  real_T branch_offset_rate210_Subsystem_MathFunction17_1;

  /* Block: branch_offset_rate210_Subsystem_Gain27 */
  real_T branch_offset_rate210_Subsystem_Gain26_1;

  /* Block: branch_offset_rate210_Subsystem_Gain22 */
  real_T branch_offset_rate210_Subsystem_Gain27_1;

  /* Block: branch_offset_rate210_Subsystem_MathFunction18 */
  real_T branch_offset_rate210_Subsystem_Gain22_1;

  /* Block: branch_offset_rate210_Subsystem_MathFunction15 */
  real_T branch_offset_rate210_Subsystem_MathFunction18_1;

  /* Block: branch_offset_rate210_Subsystem_Gain28 */
  real_T branch_offset_rate210_Subsystem_MathFunction15_1;

  /* Block: branch_offset_rate210_Subsystem_Gain23 */
  real_T branch_offset_rate210_Subsystem_Gain28_1;

  /* Block: branch_offset_rate210_Subsystem_Gain24 */
  real_T branch_offset_rate210_Subsystem_Gain23_1;

  /* Block: branch_offset_rate210_Subsystem_MathFunction16 */
  real_T branch_offset_rate210_Subsystem_Gain24_1;

  /* Block: branch_offset_rate210_Subsystem_Gain25 */
  real_T branch_offset_rate210_Subsystem_MathFunction16_1;

  /* Block: branch_offset_rate210_Subsystem_MathFunction13 */

  /* Block: branch_offset_rate210_Subsystem_Gain19 */
  real_T branch_offset_rate210_Subsystem_MathFunction13_1;

  /* Block: branch_offset_rate210_Subsystem_Gain20 */
  real_T branch_offset_rate210_Subsystem_Gain19_1;

  /* Block: branch_offset_rate210_Subsystem_Gain15 */
  real_T branch_offset_rate210_Subsystem_Gain20_1;

  /* Block: branch_offset_rate210_Subsystem_MathFunction14 */
  real_T branch_offset_rate210_Subsystem_Gain15_1;

  /* Block: branch_offset_rate210_Subsystem_MathFunction11 */
  real_T branch_offset_rate210_Subsystem_MathFunction14_1;

  /* Block: branch_offset_rate210_Subsystem_Gain21 */
  real_T branch_offset_rate210_Subsystem_MathFunction11_1;

  /* Block: branch_offset_rate210_Subsystem_Gain16 */
  real_T branch_offset_rate210_Subsystem_Gain21_1;

  /* Block: branch_offset_rate210_Subsystem_Gain17 */
  real_T branch_offset_rate210_Subsystem_Gain16_1;

  /* Block: branch_offset_rate210_Subsystem_MathFunction12 */
  real_T branch_offset_rate210_Subsystem_Gain17_1;

  /* Block: branch_offset_rate210_Subsystem_Gain18 */
  real_T branch_offset_rate210_Subsystem_MathFunction12_1;

  /* Block: branch_offset_rate210_Subsystem_Add4 */
  real_T branch_offset_rate210_Subsystem_Gain18_1;
  real_T branch_offset_rate210_Subsystem_Gain25_1;

  /* output variables */

  /* Block: branch_offset_rate210_Subsystem_Sqrt1 */

  /* Block: branch_offset_rate210_Subsystem_Gain11 */

  /* Block: branch_offset_rate210_Subsystem_Gain */

  /* Block: branch_offset_rate210_Subsystem_Gain2 */

  /* Block: branch_offset_rate210_Subsystem_Add1 */

  /* Block: branch_offset_rate210_Subsystem_MathFunction2 */

  /* Block: branch_offset_rate210_Subsystem_S_Function */

  /* Block: branch_offset_rate210_Subsystem_Gain1 */

  /* Block: branch_offset_rate210_Subsystem_MathFunction1 */

  /* Block: branch_offset_rate210_Subsystem_Add */

  /* Block: branch_offset_rate210_Subsystem_Sqrt2 */

  /* Block: branch_offset_rate210_Subsystem_Gain13 */

  /* Block: branch_offset_rate210_Subsystem_Gain12 */

  /* Block: branch_offset_rate210_Subsystem_Gain14 */

  /* Block: branch_offset_rate210_Subsystem_Add2 */

  /* Block: branch_offset_rate210_Subsystem_MathFunction17 */

  /* Block: branch_offset_rate210_Subsystem_Gain26 */

  /* Block: branch_offset_rate210_Subsystem_Gain27 */

  /* Block: branch_offset_rate210_Subsystem_Gain22 */

  /* Block: branch_offset_rate210_Subsystem_MathFunction18 */

  /* Block: branch_offset_rate210_Subsystem_MathFunction15 */

  /* Block: branch_offset_rate210_Subsystem_Gain28 */

  /* Block: branch_offset_rate210_Subsystem_Gain23 */

  /* Block: branch_offset_rate210_Subsystem_Gain24 */

  /* Block: branch_offset_rate210_Subsystem_MathFunction16 */

  /* Block: branch_offset_rate210_Subsystem_Gain25 */

  /* Block: branch_offset_rate210_Subsystem_MathFunction13 */

  /* Block: branch_offset_rate210_Subsystem_Gain19 */

  /* Block: branch_offset_rate210_Subsystem_Gain20 */

  /* Block: branch_offset_rate210_Subsystem_Gain15 */

  /* Block: branch_offset_rate210_Subsystem_MathFunction14 */

  /* Block: branch_offset_rate210_Subsystem_MathFunction11 */

  /* Block: branch_offset_rate210_Subsystem_Gain21 */

  /* Block: branch_offset_rate210_Subsystem_Gain16 */

  /* Block: branch_offset_rate210_Subsystem_Gain17 */

  /* Block: branch_offset_rate210_Subsystem_MathFunction12 */

  /* Block: branch_offset_rate210_Subsystem_Gain18 */

  /* Block: branch_offset_rate210_Subsystem_Add4 */
  real_T branch_offset_rate210_Subsystem_Add4_1;

  /* functions */

  /* Block: branch_offset_rate210_Subsystem_MathFunction1 */

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

  /* Block: branch_offset_rate210_Subsystem_MathFunction17 */

  /* Block: branch_offset_rate210_Subsystem_MathFunction18 */

  /* Block: branch_offset_rate210_Subsystem_MathFunction15 */

  /* Block: branch_offset_rate210_Subsystem_MathFunction16 */

  /* Block: branch_offset_rate210_Subsystem_MathFunction13 */

  /* Block: branch_offset_rate210_Subsystem_MathFunction14 */

  /* Block: branch_offset_rate210_Subsystem_MathFunction11 */

  /* Block: branch_offset_rate210_Subsystem_MathFunction12 */

  /* Common Initialization */
  rt_InitInfAndNaN(sizeof(real_T));

  /* Block: branch_offset_rate210_Subsystem_Sqrt1 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Sqrt1_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Gain11 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Gain11_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Gain */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Gain_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Gain2 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Gain2_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Add1 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Add1_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_MathFunction2 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_MathFunction2_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_S_Function */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_S_Function_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Gain1 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Gain1_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_MathFunction1 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_MathFunction1_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Add */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Add_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Sqrt2 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Sqrt2_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Gain13 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Gain13_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Gain12 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Gain12_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Gain14 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Gain14_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Add2 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Add2_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_MathFunction17 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_MathFunction17_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Gain26 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Gain26_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Gain27 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Gain27_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Gain22 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Gain22_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_MathFunction18 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_MathFunction18_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_MathFunction15 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_MathFunction15_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Gain28 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Gain28_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Gain23 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Gain23_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Gain24 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Gain24_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_MathFunction16 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_MathFunction16_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Gain25 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Gain25_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_MathFunction13 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_MathFunction13_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Gain19 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Gain19_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Gain20 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Gain20_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Gain15 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Gain15_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_MathFunction14 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_MathFunction14_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_MathFunction11 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_MathFunction11_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Gain21 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Gain21_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Gain16 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Gain16_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Gain17 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Gain17_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_MathFunction12 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_MathFunction12_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Gain18 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Gain18_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Add4 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Add4_1 = 0.0;
}

#ifdef TASK_INITIALIZE_0061_COMPLETED
  TASK_INITIALIZE_0061_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0012_COMPLETED
  TASK_INITIALIZE_0012_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0009_COMPLETED
  TASK_INITIALIZE_0009_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0021_COMPLETED
  TASK_INITIALIZE_0021_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0005_COMPLETED
  TASK_INITIALIZE_0005_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0048_COMPLETED
  TASK_INITIALIZE_0048_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0056_COMPLETED
  TASK_INITIALIZE_0056_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0010_COMPLETED
  TASK_INITIALIZE_0010_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0038_COMPLETED
  TASK_INITIALIZE_0038_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0004_COMPLETED
  TASK_INITIALIZE_0004_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0062_COMPLETED
  TASK_INITIALIZE_0062_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0014_COMPLETED
  TASK_INITIALIZE_0014_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0013_COMPLETED
  TASK_INITIALIZE_0013_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0015_COMPLETED
  TASK_INITIALIZE_0015_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0006_COMPLETED
  TASK_INITIALIZE_0006_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0046_COMPLETED
  TASK_INITIALIZE_0046_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0028_COMPLETED
  TASK_INITIALIZE_0028_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0029_COMPLETED
  TASK_INITIALIZE_0029_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0024_COMPLETED
  TASK_INITIALIZE_0024_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0047_COMPLETED
  TASK_INITIALIZE_0047_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0044_COMPLETED
  TASK_INITIALIZE_0044_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0030_COMPLETED
  TASK_INITIALIZE_0030_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0025_COMPLETED
  TASK_INITIALIZE_0025_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0026_COMPLETED
  TASK_INITIALIZE_0026_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0045_COMPLETED
  TASK_INITIALIZE_0045_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0027_COMPLETED
  TASK_INITIALIZE_0027_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0042_COMPLETED
  TASK_INITIALIZE_0042_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0020_COMPLETED
  TASK_INITIALIZE_0020_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0022_COMPLETED
  TASK_INITIALIZE_0022_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0016_COMPLETED
  TASK_INITIALIZE_0016_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0043_COMPLETED
  TASK_INITIALIZE_0043_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0040_COMPLETED
  TASK_INITIALIZE_0040_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0023_COMPLETED
  TASK_INITIALIZE_0023_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0017_COMPLETED
  TASK_INITIALIZE_0017_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0018_COMPLETED
  TASK_INITIALIZE_0018_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0041_COMPLETED
  TASK_INITIALIZE_0041_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0019_COMPLETED
  TASK_INITIALIZE_0019_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0008_COMPLETED
  TASK_INITIALIZE_0008_COMPLETED();
#endif

  /* task loop */
  while (1) {    /*
     * Block: branch_offset_rate210_Subsystem_Sqrt1
     * Task: 0061
     * rate: 10000
     */

    /* wait input channel */
    while (1) {
      /* input: branch_offset_rate210_UnitDelay2 */
      if (CH_0070_0061.flag__0070_0061 > 0) {
	branch_offset_rate210_UnitDelay2_1 = CH_0070_0061.branch_offset_rate210_UnitDelay2_1;
	CH__SYNCM();
	CH_0070_0061.flag__0070_0061--;
	CH__EVENT(TASK_0061, OUT_0070);
	CH__END_LOG(IN_0061);
	break;
      }

      CH__CORE_THREAD_SCHED(IN_0061,NULL,1);

      CH__MEM_BARRIER();
    }

#ifdef TASK_IN_0061_COMPLETED
    TASK_IN_0061_COMPLETED();
#endif

    /* C code */
        {
{

    /* Sqrt: '<S1>/Sqrt1' */
    branch_offset_rate210_Subsystem_Sqrt1_1 = sqrt
      (branch_offset_rate210_UnitDelay2_1);


}

    }

#ifdef TASK_EXECUTE_0061_COMPLETED
    TASK_EXECUTE_0061_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_Gain11
     * Task: 0012
     * rate: 10000
     */

    /* C code */
        {
{

    /* Gain: '<S1>/Gain11' */
    branch_offset_rate210_Subsystem_Gain11_1 =
      branch_offset_rate210_P.Gain11_Gain *
      branch_offset_rate210_Subsystem_Sqrt1_1;


}

    }

#ifdef TASK_EXECUTE_0012_COMPLETED
    TASK_EXECUTE_0012_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_Gain
     * Task: 0009
     * rate: 10000
     */

    /* C code */
        {
{

    /* Gain: '<S1>/Gain' */
    branch_offset_rate210_Subsystem_Gain_1 = branch_offset_rate210_P.Gain_Gain_j
      * branch_offset_rate210_Subsystem_Sqrt1_1;


}

    }

#ifdef TASK_EXECUTE_0009_COMPLETED
    TASK_EXECUTE_0009_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_Gain2
     * Task: 0021
     * rate: 10000
     */

    /* C code */
        {
{

    /* Gain: '<S1>/Gain2' */
    branch_offset_rate210_Subsystem_Gain2_1 = branch_offset_rate210_P.Gain2_Gain
      * branch_offset_rate210_Subsystem_Gain_1;


}

    }

#ifdef TASK_EXECUTE_0021_COMPLETED
    TASK_EXECUTE_0021_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_Add1
     * Task: 0005
     * rate: 10000
     */

    /* C code */
        {
{

    /* Sum: '<S1>/Add1' */
    branch_offset_rate210_Subsystem_Add1_1 =
      branch_offset_rate210_Subsystem_Gain11_1 +
      branch_offset_rate210_Subsystem_Gain2_1;


}

    }

#ifdef TASK_EXECUTE_0005_COMPLETED
    TASK_EXECUTE_0005_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_MathFunction2
     * Task: 0048
     * rate: 10000
     */

    /* C code */
        {
{

    /* Math: '<S1>/MathFunction2'
     *
     * About '<S1>/MathFunction2':
     *  Operator: log10
     */
    branch_offset_rate210_Subsystem_MathFunction2_1 = log10
      (branch_offset_rate210_Subsystem_Sqrt1_1);


}

    }

#ifdef TASK_EXECUTE_0048_COMPLETED
    TASK_EXECUTE_0048_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_S_Function
     * Task: 0056
     * rate: 10000
     */

    /* C code */
        {
{

    /* S-Function (loop): '<S1>/S_Function' */
    loop_Outputs_wrapper(&branch_offset_rate210_Subsystem_MathFunction2_1,
                         &branch_offset_rate210_Subsystem_S_Function_1 );


}

    }

#ifdef TASK_EXECUTE_0056_COMPLETED
    TASK_EXECUTE_0056_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_Gain1
     * Task: 0010
     * rate: 10000
     */

    /* C code */
        {
{

    /* Gain: '<S1>/Gain1' */
    branch_offset_rate210_Subsystem_Gain1_1 = branch_offset_rate210_P.Gain1_Gain
      * branch_offset_rate210_Subsystem_S_Function_1;


}

    }

#ifdef TASK_EXECUTE_0010_COMPLETED
    TASK_EXECUTE_0010_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_MathFunction1
     * Task: 0038
     * rate: 10000
     */

    /* C code */
        {
{

    /* Math: '<S1>/MathFunction1' */
    branch_offset_rate210_Subsystem_MathFunction1_1 = rt_powd_snf(10.0,
      branch_offset_rate210_Subsystem_Gain1_1);


}

    }

#ifdef TASK_EXECUTE_0038_COMPLETED
    TASK_EXECUTE_0038_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_Add
     * Task: 0004
     * rate: 10000
     */

    /* C code */
        {
{

    /* Sum: '<S1>/Add' */
    branch_offset_rate210_Subsystem_Add_1 =
      branch_offset_rate210_Subsystem_Add1_1 +
      branch_offset_rate210_Subsystem_MathFunction1_1;

}

    }

#ifdef TASK_EXECUTE_0004_COMPLETED
    TASK_EXECUTE_0004_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_Sqrt2
     * Task: 0062
     * rate: 10000
     */

    /* C code */
        {
{

    /* Sqrt: '<S1>/Sqrt2' */
    branch_offset_rate210_Subsystem_Sqrt2_1 = sqrt
      (branch_offset_rate210_Subsystem_Add_1);

}

    }

#ifdef TASK_EXECUTE_0062_COMPLETED
    TASK_EXECUTE_0062_COMPLETED();
#endif

    /* wait output channel */
    while (1) {
      /* skip local output CH_0062_0013: branch_offset_rate210_Subsystem_Gain12 */

      /* skip local output CH_0062_0014: branch_offset_rate210_Subsystem_Gain13 */

      /* output: branch_offset_rate210_Subsystem_MathFunction4 */
      if (CH_0062_0050.flag__0062_0050 == 0) {
	CH_0062_0050.branch_offset_rate210_Subsystem_Sqrt2_1 = branch_offset_rate210_Subsystem_Sqrt2_1;
	CH__SYNCM();
	CH_0062_0050.flag__0062_0050 = 1;
	CH__EVENT(TASK_0062,IN_0050);
	CH__END_LOG(OUT_0062);
	break;
      }

      CH__CORE_THREAD_SCHED(OUT_0062,NULL,1);

      CH__MEM_BARRIER();
    }

#ifdef TASK_OUT_0062_COMPLETED
    TASK_OUT_0062_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_Gain13
     * Task: 0014
     * rate: 10000
     */

    /* C code */
        {
{

    /* Gain: '<S1>/Gain13' */
    branch_offset_rate210_Subsystem_Gain13_1 =
      branch_offset_rate210_P.Gain13_Gain *
      branch_offset_rate210_Subsystem_Sqrt2_1;


}

    }

#ifdef TASK_EXECUTE_0014_COMPLETED
    TASK_EXECUTE_0014_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_Gain12
     * Task: 0013
     * rate: 10000
     */

    /* C code */
        {
{

    /* Gain: '<S1>/Gain12' */
    branch_offset_rate210_Subsystem_Gain12_1 =
      branch_offset_rate210_P.Gain12_Gain *
      branch_offset_rate210_Subsystem_Sqrt2_1;


}

    }

#ifdef TASK_EXECUTE_0013_COMPLETED
    TASK_EXECUTE_0013_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_Gain14
     * Task: 0015
     * rate: 10000
     */

    /* C code */
        {
{

    /* Gain: '<S1>/Gain14' */
    branch_offset_rate210_Subsystem_Gain14_1 =
      branch_offset_rate210_P.Gain14_Gain *
      branch_offset_rate210_Subsystem_Gain12_1;


}

    }

#ifdef TASK_EXECUTE_0015_COMPLETED
    TASK_EXECUTE_0015_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_Add2
     * Task: 0006
     * rate: 10000
     */

    /* C code */
        {
{

    /* Sum: '<S1>/Add2' */
    branch_offset_rate210_Subsystem_Add2_1 =
      branch_offset_rate210_Subsystem_Gain13_1 +
      branch_offset_rate210_Subsystem_Gain14_1;

}

    }

#ifdef TASK_EXECUTE_0006_COMPLETED
    TASK_EXECUTE_0006_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_MathFunction17
     * Task: 0046
     * rate: 10000
     */

    /* C code */
        {
{

    /* Math: '<S1>/MathFunction17' */
    branch_offset_rate210_Subsystem_MathFunction17_1 = rt_powd_snf(10.0,
      branch_offset_rate210_Subsystem_Add2_1);


}

    }

#ifdef TASK_EXECUTE_0046_COMPLETED
    TASK_EXECUTE_0046_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_Gain26
     * Task: 0028
     * rate: 10000
     */

    /* C code */
        {
{

    /* Gain: '<S1>/Gain26' */
    branch_offset_rate210_Subsystem_Gain26_1 =
      branch_offset_rate210_P.Gain26_Gain *
      branch_offset_rate210_Subsystem_MathFunction17_1;


}

    }

#ifdef TASK_EXECUTE_0028_COMPLETED
    TASK_EXECUTE_0028_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_Gain27
     * Task: 0029
     * rate: 10000
     */

    /* C code */
        {
{

    /* Gain: '<S1>/Gain27' */
    branch_offset_rate210_Subsystem_Gain27_1 =
      branch_offset_rate210_P.Gain27_Gain *
      branch_offset_rate210_Subsystem_Gain26_1;


}

    }

#ifdef TASK_EXECUTE_0029_COMPLETED
    TASK_EXECUTE_0029_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_Gain22
     * Task: 0024
     * rate: 10000
     */

    /* C code */
        {
{

    /* Gain: '<S1>/Gain22' */
    branch_offset_rate210_Subsystem_Gain22_1 =
      branch_offset_rate210_P.Gain22_Gain *
      branch_offset_rate210_Subsystem_Gain27_1;


}

    }

#ifdef TASK_EXECUTE_0024_COMPLETED
    TASK_EXECUTE_0024_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_MathFunction18
     * Task: 0047
     * rate: 10000
     */

    /* C code */
        {
{

    /* Math: '<S1>/MathFunction18' */
    branch_offset_rate210_Subsystem_MathFunction18_1 = rt_powd_snf(10.0,
      branch_offset_rate210_Subsystem_Gain22_1);


}

    }

#ifdef TASK_EXECUTE_0047_COMPLETED
    TASK_EXECUTE_0047_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_MathFunction15
     * Task: 0044
     * rate: 10000
     */

    /* C code */
        {
{

    /* Math: '<S1>/MathFunction15' */
    branch_offset_rate210_Subsystem_MathFunction15_1 = rt_powd_snf(10.0,
      branch_offset_rate210_Subsystem_MathFunction18_1);


}

    }

#ifdef TASK_EXECUTE_0044_COMPLETED
    TASK_EXECUTE_0044_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_Gain28
     * Task: 0030
     * rate: 10000
     */

    /* C code */
        {
{

    /* Gain: '<S1>/Gain28' */
    branch_offset_rate210_Subsystem_Gain28_1 =
      branch_offset_rate210_P.Gain28_Gain *
      branch_offset_rate210_Subsystem_MathFunction15_1;


}

    }

#ifdef TASK_EXECUTE_0030_COMPLETED
    TASK_EXECUTE_0030_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_Gain23
     * Task: 0025
     * rate: 10000
     */

    /* C code */
        {
{

    /* Gain: '<S1>/Gain23' */
    branch_offset_rate210_Subsystem_Gain23_1 =
      branch_offset_rate210_P.Gain23_Gain *
      branch_offset_rate210_Subsystem_Gain28_1;


}

    }

#ifdef TASK_EXECUTE_0025_COMPLETED
    TASK_EXECUTE_0025_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_Gain24
     * Task: 0026
     * rate: 10000
     */

    /* C code */
        {
{

    /* Gain: '<S1>/Gain24' */
    branch_offset_rate210_Subsystem_Gain24_1 =
      branch_offset_rate210_P.Gain24_Gain *
      branch_offset_rate210_Subsystem_Gain23_1;


}

    }

#ifdef TASK_EXECUTE_0026_COMPLETED
    TASK_EXECUTE_0026_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_MathFunction16
     * Task: 0045
     * rate: 10000
     */

    /* C code */
        {
{

    /* Math: '<S1>/MathFunction16' */
    branch_offset_rate210_Subsystem_MathFunction16_1 = rt_powd_snf(10.0,
      branch_offset_rate210_Subsystem_Gain24_1);


}

    }

#ifdef TASK_EXECUTE_0045_COMPLETED
    TASK_EXECUTE_0045_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_Gain25
     * Task: 0027
     * rate: 10000
     */

    /* C code */
        {
{

    /* Gain: '<S1>/Gain25' */
    branch_offset_rate210_Subsystem_Gain25_1 =
      branch_offset_rate210_P.Gain25_Gain *
      branch_offset_rate210_Subsystem_MathFunction16_1;


}

    }

#ifdef TASK_EXECUTE_0027_COMPLETED
    TASK_EXECUTE_0027_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_MathFunction13
     * Task: 0042
     * rate: 10000
     */

    /* C code */
        {
{

    /* Math: '<S1>/MathFunction13' */
    branch_offset_rate210_Subsystem_MathFunction13_1 = rt_powd_snf(10.0,
      branch_offset_rate210_Subsystem_Add2_1);


}

    }

#ifdef TASK_EXECUTE_0042_COMPLETED
    TASK_EXECUTE_0042_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_Gain19
     * Task: 0020
     * rate: 10000
     */

    /* C code */
        {
{

    /* Gain: '<S1>/Gain19' */
    branch_offset_rate210_Subsystem_Gain19_1 =
      branch_offset_rate210_P.Gain19_Gain *
      branch_offset_rate210_Subsystem_MathFunction13_1;


}

    }

#ifdef TASK_EXECUTE_0020_COMPLETED
    TASK_EXECUTE_0020_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_Gain20
     * Task: 0022
     * rate: 10000
     */

    /* C code */
        {
{

    /* Gain: '<S1>/Gain20' */
    branch_offset_rate210_Subsystem_Gain20_1 =
      branch_offset_rate210_P.Gain20_Gain *
      branch_offset_rate210_Subsystem_Gain19_1;


}

    }

#ifdef TASK_EXECUTE_0022_COMPLETED
    TASK_EXECUTE_0022_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_Gain15
     * Task: 0016
     * rate: 10000
     */

    /* C code */
        {
{

    /* Gain: '<S1>/Gain15' */
    branch_offset_rate210_Subsystem_Gain15_1 =
      branch_offset_rate210_P.Gain15_Gain *
      branch_offset_rate210_Subsystem_Gain20_1;


}

    }

#ifdef TASK_EXECUTE_0016_COMPLETED
    TASK_EXECUTE_0016_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_MathFunction14
     * Task: 0043
     * rate: 10000
     */

    /* C code */
        {
{

    /* Math: '<S1>/MathFunction14' */
    branch_offset_rate210_Subsystem_MathFunction14_1 = rt_powd_snf(10.0,
      branch_offset_rate210_Subsystem_Gain15_1);


}

    }

#ifdef TASK_EXECUTE_0043_COMPLETED
    TASK_EXECUTE_0043_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_MathFunction11
     * Task: 0040
     * rate: 10000
     */

    /* C code */
        {
{

    /* Math: '<S1>/MathFunction11' */
    branch_offset_rate210_Subsystem_MathFunction11_1 = rt_powd_snf(10.0,
      branch_offset_rate210_Subsystem_MathFunction14_1);


}

    }

#ifdef TASK_EXECUTE_0040_COMPLETED
    TASK_EXECUTE_0040_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_Gain21
     * Task: 0023
     * rate: 10000
     */

    /* C code */
        {
{

    /* Gain: '<S1>/Gain21' */
    branch_offset_rate210_Subsystem_Gain21_1 =
      branch_offset_rate210_P.Gain21_Gain *
      branch_offset_rate210_Subsystem_MathFunction11_1;


}

    }

#ifdef TASK_EXECUTE_0023_COMPLETED
    TASK_EXECUTE_0023_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_Gain16
     * Task: 0017
     * rate: 10000
     */

    /* C code */
        {
{

    /* Gain: '<S1>/Gain16' */
    branch_offset_rate210_Subsystem_Gain16_1 =
      branch_offset_rate210_P.Gain16_Gain *
      branch_offset_rate210_Subsystem_Gain21_1;


}

    }

#ifdef TASK_EXECUTE_0017_COMPLETED
    TASK_EXECUTE_0017_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_Gain17
     * Task: 0018
     * rate: 10000
     */

    /* C code */
        {
{

    /* Gain: '<S1>/Gain17' */
    branch_offset_rate210_Subsystem_Gain17_1 =
      branch_offset_rate210_P.Gain17_Gain *
      branch_offset_rate210_Subsystem_Gain16_1;


}

    }

#ifdef TASK_EXECUTE_0018_COMPLETED
    TASK_EXECUTE_0018_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_MathFunction12
     * Task: 0041
     * rate: 10000
     */

    /* C code */
        {
{

    /* Math: '<S1>/MathFunction12' */
    branch_offset_rate210_Subsystem_MathFunction12_1 = rt_powd_snf(10.0,
      branch_offset_rate210_Subsystem_Gain17_1);


}

    }

#ifdef TASK_EXECUTE_0041_COMPLETED
    TASK_EXECUTE_0041_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_Gain18
     * Task: 0019
     * rate: 10000
     */

    /* C code */
        {
{

    /* Gain: '<S1>/Gain18' */
    branch_offset_rate210_Subsystem_Gain18_1 =
      branch_offset_rate210_P.Gain18_Gain *
      branch_offset_rate210_Subsystem_MathFunction12_1;

}

    }

#ifdef TASK_EXECUTE_0019_COMPLETED
    TASK_EXECUTE_0019_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Subsystem_Add4
     * Task: 0008
     * rate: 10000
     */

    /* C code */
        {
{

    /* Sum: '<S1>/Add4' */
    branch_offset_rate210_Subsystem_Add4_1 =
      branch_offset_rate210_Subsystem_Gain25_1 +
      branch_offset_rate210_Subsystem_Gain18_1;

}

    }

#ifdef TASK_EXECUTE_0008_COMPLETED
    TASK_EXECUTE_0008_COMPLETED();
#endif

    /* wait output channel */
    while (1) {
      /* output: branch_offset_rate210_Subsystem_Add3 */
      if (CH_0008_0007.flag__0008_0007 == 0) {
	CH_0008_0007.branch_offset_rate210_Subsystem_Add4_1 = branch_offset_rate210_Subsystem_Add4_1;
	CH__SYNCM();
	CH_0008_0007.flag__0008_0007 = 1;
	CH__EVENT(TASK_0008,IN_0007);
	CH__END_LOG(OUT_0008);
	break;
      }

      CH__CORE_THREAD_SCHED(OUT_0008,NULL,1);

      CH__MEM_BARRIER();
    }

#ifdef TASK_OUT_0008_COMPLETED
    TASK_OUT_0008_COMPLETED();
#endif

    task__time += task__rate;
  }
}

CORE_TASK_CODE_PREPARE(1)

/* Core#1 */
/* rate: 2000 */
void mcos_core1_thread(uint32_t stacd, uintptr_t exinf)
{
  /* task time */
  unsigned long task__time = 0;
  const unsigned long task__rate = 2000;

  /* multirate */
  const unsigned long task__rate_1 = 10000;
  unsigned long task__time_1 = 0;
  /* omit input channel bit vector */
  /* CH__VEC(IN_0001,1); */

  /* output channel bit vector */
  CH__VEC(OUT_0001,2);

  /* omit input channel bit vector */
  /* CH__VEC(IN_0070,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0070,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0050,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0050,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0057,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0057,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0031,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0031,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0049,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0049,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0032,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0032,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0063,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0063,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0052,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0052,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0058,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0058,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0033,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0033,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0051,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0051,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0034,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0034,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0064,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0064,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0054,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0054,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0059,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0059,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0035,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0035,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0053,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0053,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0036,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0036,1); */

  /* input channel bit vector */
  CH__VEC(IN_0007,2);

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0007,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0065,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0065,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0039,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0039,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0060,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0060,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0037,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0037,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0055,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0055,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0011,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0011,1); */

  /* omit input channel bit vector */
  /* CH__VEC(IN_0068,1); */

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0068,1); */

  /* input channel bit vector */
  CH__VEC(IN_0067,2);

  /* omit output channel bit vector */
  /* CH__VEC(OUT_0067,1); */

  /* states */
  struct {
    /* Block: branch_offset_rate210_Gain */
    real_T UnitDelay1_DSTATE; /* task_0001 */

    /* Block: branch_offset_rate210_UnitDelay2 */
    real_T UnitDelay2_DSTATE; /* task_0070 */

    /* Block: branch_offset_rate210_UnitDelay */
    real_T UnitDelay_DSTATE; /* task_0068 */
  } branch_offset_rate210_DW;

  /* params */
  struct {
    /* Block: branch_offset_rate210_Gain */
    real_T UnitDelay1_InitialCondition;
    real_T Gain_Gain;

    /* Block: branch_offset_rate210_UnitDelay2 */
    real_T UnitDelay2_InitialCondition;

    /* Block: branch_offset_rate210_Subsystem_Gain3 */
    real_T Gain3_Gain;

    /* Block: branch_offset_rate210_Subsystem_Gain4 */
    real_T Gain4_Gain;

    /* Block: branch_offset_rate210_Subsystem_Gain5 */
    real_T Gain5_Gain;

    /* Block: branch_offset_rate210_Subsystem_Gain6 */
    real_T Gain6_Gain;

    /* Block: branch_offset_rate210_Subsystem_Gain7 */
    real_T Gain7_Gain;

    /* Block: branch_offset_rate210_Subsystem_Gain8 */
    real_T Gain8_Gain;

    /* Block: branch_offset_rate210_Subsystem_Gain9 */
    real_T Gain9_Gain;

    /* Block: branch_offset_rate210_Subsystem_Gain10 */
    real_T Gain10_Gain;

    /* Block: branch_offset_rate210_UnitDelay */
    real_T UnitDelay_InitialCondition;
  } branch_offset_rate210_P = {
  2.0,                                 /* Expression: 2
                                        * Referenced by: '<Root>/UnitDelay1'
                                        */

  2.0,                                 /* Expression: 2
                                        * Referenced by: '<Root>/Gain'
                                        */

  1.0,                                 /* Expression: 1
                                        * Referenced by: '<Root>/UnitDelay2'
                                        */

  2.0,                                 /* Expression: 2
                                        * Referenced by: '<S1>/Gain3'
                                        */

  0.5,                                 /* Expression: 0.5
                                        * Referenced by: '<S1>/Gain4'
                                        */

  2.0,                                 /* Expression: 2
                                        * Referenced by: '<S1>/Gain5'
                                        */

  0.5,                                 /* Expression: 0.5
                                        * Referenced by: '<S1>/Gain6'
                                        */

  2.0,                                 /* Expression: 2
                                        * Referenced by: '<S1>/Gain7'
                                        */

  0.5,                                 /* Expression: 0.5
                                        * Referenced by: '<S1>/Gain8'
                                        */

  2.0,                                 /* Expression: 2
                                        * Referenced by: '<S1>/Gain9'
                                        */

  0.5,                                 /* Expression: 0.5
                                        * Referenced by: '<S1>/Gain10'
                                        */

  1.0                                  /* Expression: 1
                                        * Referenced by: '<Root>/UnitDelay'
                                        */,

  };

  /* internal variables */

  /* Block: branch_offset_rate210_Gain */
  real_T branch_offset_rate210_UnitDelay1_1;

  /* input variables */

  /* Block: branch_offset_rate210_Gain */
  real_T branch_offset_rate210_Sum_1;

  /* Block: branch_offset_rate210_UnitDelay2 */
  real_T branch_offset_rate210_Gain_1;

  /* Block: branch_offset_rate210_Subsystem_MathFunction4 */
  real_T branch_offset_rate210_Subsystem_Sqrt2_1;

  /* Block: branch_offset_rate210_Subsystem_S_Function1 */
  real_T branch_offset_rate210_Subsystem_MathFunction4_1;

  /* Block: branch_offset_rate210_Subsystem_Gain3 */
  real_T branch_offset_rate210_Subsystem_S_Function1_1;

  /* Block: branch_offset_rate210_Subsystem_MathFunction3 */
  real_T branch_offset_rate210_Subsystem_Gain3_1;

  /* Block: branch_offset_rate210_Subsystem_Gain4 */
  real_T branch_offset_rate210_Subsystem_MathFunction3_1;

  /* Block: branch_offset_rate210_Subsystem_Sqrt3 */
  real_T branch_offset_rate210_Subsystem_Gain4_1;

  /* Block: branch_offset_rate210_Subsystem_MathFunction6 */
  real_T branch_offset_rate210_Subsystem_Sqrt3_1;

  /* Block: branch_offset_rate210_Subsystem_S_Function2 */
  real_T branch_offset_rate210_Subsystem_MathFunction6_1;

  /* Block: branch_offset_rate210_Subsystem_Gain5 */
  real_T branch_offset_rate210_Subsystem_S_Function2_1;

  /* Block: branch_offset_rate210_Subsystem_MathFunction5 */
  real_T branch_offset_rate210_Subsystem_Gain5_1;

  /* Block: branch_offset_rate210_Subsystem_Gain6 */
  real_T branch_offset_rate210_Subsystem_MathFunction5_1;

  /* Block: branch_offset_rate210_Subsystem_Sqrt4 */
  real_T branch_offset_rate210_Subsystem_Gain6_1;

  /* Block: branch_offset_rate210_Subsystem_MathFunction8 */
  real_T branch_offset_rate210_Subsystem_Sqrt4_1;

  /* Block: branch_offset_rate210_Subsystem_S_Function3 */
  real_T branch_offset_rate210_Subsystem_MathFunction8_1;

  /* Block: branch_offset_rate210_Subsystem_Gain7 */
  real_T branch_offset_rate210_Subsystem_S_Function3_1;

  /* Block: branch_offset_rate210_Subsystem_MathFunction7 */
  real_T branch_offset_rate210_Subsystem_Gain7_1;

  /* Block: branch_offset_rate210_Subsystem_Gain8 */
  real_T branch_offset_rate210_Subsystem_MathFunction7_1;

  /* Block: branch_offset_rate210_Subsystem_Add3 */
  real_T branch_offset_rate210_Subsystem_Add4_1;
  real_T branch_offset_rate210_Subsystem_Gain8_1;

  /* Block: branch_offset_rate210_Subsystem_Sqrt5 */
  real_T branch_offset_rate210_Subsystem_Add3_1;

  /* Block: branch_offset_rate210_Subsystem_MathFunction10 */
  real_T branch_offset_rate210_Subsystem_Sqrt5_1;

  /* Block: branch_offset_rate210_Subsystem_S_Function4 */
  real_T branch_offset_rate210_Subsystem_MathFunction10_1;

  /* Block: branch_offset_rate210_Subsystem_Gain9 */
  real_T branch_offset_rate210_Subsystem_S_Function4_1;

  /* Block: branch_offset_rate210_Subsystem_MathFunction9 */
  real_T branch_offset_rate210_Subsystem_Gain9_1;

  /* Block: branch_offset_rate210_Subsystem_Gain10 */
  real_T branch_offset_rate210_Subsystem_MathFunction9_1;

  /* Block: branch_offset_rate210_UnitDelay */
  real_T branch_offset_rate210_Subsystem_Gain10_1;

  /* Block: branch_offset_rate210_Sum */
  real_T branch_offset_rate210_UnitDelay_1;

  /* output variables */

  /* Block: branch_offset_rate210_Gain */

  /* Block: branch_offset_rate210_UnitDelay2 */
  real_T branch_offset_rate210_UnitDelay2_1;

  /* Block: branch_offset_rate210_Subsystem_MathFunction4 */

  /* Block: branch_offset_rate210_Subsystem_S_Function1 */

  /* Block: branch_offset_rate210_Subsystem_Gain3 */

  /* Block: branch_offset_rate210_Subsystem_MathFunction3 */

  /* Block: branch_offset_rate210_Subsystem_Gain4 */

  /* Block: branch_offset_rate210_Subsystem_Sqrt3 */

  /* Block: branch_offset_rate210_Subsystem_MathFunction6 */

  /* Block: branch_offset_rate210_Subsystem_S_Function2 */

  /* Block: branch_offset_rate210_Subsystem_Gain5 */

  /* Block: branch_offset_rate210_Subsystem_MathFunction5 */

  /* Block: branch_offset_rate210_Subsystem_Gain6 */

  /* Block: branch_offset_rate210_Subsystem_Sqrt4 */

  /* Block: branch_offset_rate210_Subsystem_MathFunction8 */

  /* Block: branch_offset_rate210_Subsystem_S_Function3 */

  /* Block: branch_offset_rate210_Subsystem_Gain7 */

  /* Block: branch_offset_rate210_Subsystem_MathFunction7 */

  /* Block: branch_offset_rate210_Subsystem_Gain8 */

  /* Block: branch_offset_rate210_Subsystem_Add3 */

  /* Block: branch_offset_rate210_Subsystem_Sqrt5 */

  /* Block: branch_offset_rate210_Subsystem_MathFunction10 */

  /* Block: branch_offset_rate210_Subsystem_S_Function4 */

  /* Block: branch_offset_rate210_Subsystem_Gain9 */

  /* Block: branch_offset_rate210_Subsystem_MathFunction9 */

  /* Block: branch_offset_rate210_Subsystem_Gain10 */

  /* Block: branch_offset_rate210_UnitDelay */

  /* Block: branch_offset_rate210_Sum */

  /* functions */

  /* Block: branch_offset_rate210_Subsystem_MathFunction3 */

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

  /* Block: branch_offset_rate210_Subsystem_MathFunction5 */

  /* Block: branch_offset_rate210_Subsystem_MathFunction7 */

  /* Block: branch_offset_rate210_Subsystem_MathFunction9 */

  /* Common Initialization */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize state structure */
  memset(&branch_offset_rate210_DW, 0, sizeof branch_offset_rate210_DW);

  /* Block: branch_offset_rate210_Gain */

  /* initialize states */
{
  /* InitializeConditions for UnitDelay: '<Root>/UnitDelay1' */
  branch_offset_rate210_DW.UnitDelay1_DSTATE =
    branch_offset_rate210_P.UnitDelay1_InitialCondition;

}

  /* initialize task context */
{
  branch_offset_rate210_UnitDelay1_1 = 0.0;
}
{
  branch_offset_rate210_Gain_1 = 0.0;
}

  /* Block: branch_offset_rate210_UnitDelay2 */

  /* initialize states */
{
  /* InitializeConditions for UnitDelay: '<Root>/UnitDelay2' */
  branch_offset_rate210_DW.UnitDelay2_DSTATE =
    branch_offset_rate210_P.UnitDelay2_InitialCondition;

}

  /* initialize task context */
{
  branch_offset_rate210_UnitDelay2_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_MathFunction4 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_MathFunction4_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_S_Function1 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_S_Function1_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Gain3 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Gain3_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_MathFunction3 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_MathFunction3_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Gain4 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Gain4_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Sqrt3 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Sqrt3_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_MathFunction6 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_MathFunction6_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_S_Function2 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_S_Function2_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Gain5 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Gain5_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_MathFunction5 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_MathFunction5_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Gain6 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Gain6_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Sqrt4 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Sqrt4_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_MathFunction8 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_MathFunction8_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_S_Function3 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_S_Function3_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Gain7 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Gain7_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_MathFunction7 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_MathFunction7_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Gain8 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Gain8_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Add3 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Add3_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Sqrt5 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Sqrt5_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_MathFunction10 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_MathFunction10_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_S_Function4 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_S_Function4_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Gain9 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Gain9_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_MathFunction9 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_MathFunction9_1 = 0.0;
}

  /* Block: branch_offset_rate210_Subsystem_Gain10 */

  /* initialize task context */
{
  branch_offset_rate210_Subsystem_Gain10_1 = 0.0;
}

  /* Block: branch_offset_rate210_UnitDelay */

  /* initialize states */
{
  /* InitializeConditions for UnitDelay: '<Root>/UnitDelay' */
  branch_offset_rate210_DW.UnitDelay_DSTATE =
    branch_offset_rate210_P.UnitDelay_InitialCondition;
}

  /* initialize task context */
{
  branch_offset_rate210_UnitDelay_1 = 0.0;
}

  /* Block: branch_offset_rate210_Sum */

  /* initialize task context */
{
  branch_offset_rate210_Sum_1 = 0.0;

}

#ifdef TASK_INITIALIZE_0001_COMPLETED
  TASK_INITIALIZE_0001_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0070_COMPLETED
  TASK_INITIALIZE_0070_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0050_COMPLETED
  TASK_INITIALIZE_0050_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0057_COMPLETED
  TASK_INITIALIZE_0057_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0031_COMPLETED
  TASK_INITIALIZE_0031_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0049_COMPLETED
  TASK_INITIALIZE_0049_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0032_COMPLETED
  TASK_INITIALIZE_0032_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0063_COMPLETED
  TASK_INITIALIZE_0063_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0052_COMPLETED
  TASK_INITIALIZE_0052_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0058_COMPLETED
  TASK_INITIALIZE_0058_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0033_COMPLETED
  TASK_INITIALIZE_0033_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0051_COMPLETED
  TASK_INITIALIZE_0051_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0034_COMPLETED
  TASK_INITIALIZE_0034_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0064_COMPLETED
  TASK_INITIALIZE_0064_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0054_COMPLETED
  TASK_INITIALIZE_0054_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0059_COMPLETED
  TASK_INITIALIZE_0059_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0035_COMPLETED
  TASK_INITIALIZE_0035_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0053_COMPLETED
  TASK_INITIALIZE_0053_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0036_COMPLETED
  TASK_INITIALIZE_0036_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0007_COMPLETED
  TASK_INITIALIZE_0007_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0065_COMPLETED
  TASK_INITIALIZE_0065_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0039_COMPLETED
  TASK_INITIALIZE_0039_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0060_COMPLETED
  TASK_INITIALIZE_0060_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0037_COMPLETED
  TASK_INITIALIZE_0037_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0055_COMPLETED
  TASK_INITIALIZE_0055_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0011_COMPLETED
  TASK_INITIALIZE_0011_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0068_COMPLETED
  TASK_INITIALIZE_0068_COMPLETED();
#endif

#ifdef TASK_INITIALIZE_0067_COMPLETED
  TASK_INITIALIZE_0067_COMPLETED();
#endif

  /* task loop */
  while (1) {    /*
     * Block: branch_offset_rate210_Gain
     * Task: 0001
     * rate: 2000
     */

    /* C code */
        {
{

  /* UnitDelay: '<Root>/UnitDelay1' */
  branch_offset_rate210_UnitDelay1_1 =
    branch_offset_rate210_DW.UnitDelay1_DSTATE;


}

{

  /* Gain: '<Root>/Gain' */
  branch_offset_rate210_Gain_1 = branch_offset_rate210_P.Gain_Gain *
    branch_offset_rate210_UnitDelay1_1;


}

    }

#ifdef TASK_EXECUTE_0001_COMPLETED
    TASK_EXECUTE_0001_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_UnitDelay2
     * Task: 0070
     * rate: 2000
     */

    /* C code */
        {
{

  /* UnitDelay: '<Root>/UnitDelay2' */
  branch_offset_rate210_UnitDelay2_1 =
    branch_offset_rate210_DW.UnitDelay2_DSTATE;

}

    }

#ifdef TASK_EXECUTE_0070_COMPLETED
    TASK_EXECUTE_0070_COMPLETED();
#endif

    /* wait output channel */
    while (1) {
      /* output: branch_offset_rate210_Subsystem_Sqrt1 */
      assert(!CH__TIME_LT(CH_0070_0061.time__0070_0061, task__time));
      if (CH__TIME_LE(task__time+2000, CH_0070_0061.time__0070_0061)) {
	/* no send this period */
	CH__END_LOG(OUT_0070);
	break;
      } else if (CH_0070_0061.flag__0070_0061 == 0) {
	CH_0070_0061.branch_offset_rate210_UnitDelay2_1 = branch_offset_rate210_UnitDelay2_1;
	CH__SYNCM();
	CH_0070_0061.flag__0070_0061 = 1;
	CH_0070_0061.time__0070_0061 += 10000;
	CH__EVENT(TASK_0070,IN_0061);
	CH__END_LOG(OUT_0070);
	break;
      }

      CH__CORE_THREAD_SCHED(OUT_0070,NULL,1);

      CH__MEM_BARRIER();
    }

#ifdef TASK_OUT_0070_COMPLETED
    TASK_OUT_0070_COMPLETED();
#endif

    if (task__time == task__time_1) {
      /*
       * Block: branch_offset_rate210_Subsystem_MathFunction4
       * Task: 0050
       * rate: 10000
       */

      /* wait input channel */
      while (1) {
	/* input: branch_offset_rate210_Subsystem_Sqrt2 */
	if (CH_0062_0050.flag__0062_0050 > 0) {
	  branch_offset_rate210_Subsystem_Sqrt2_1 = CH_0062_0050.branch_offset_rate210_Subsystem_Sqrt2_1;
	  CH__SYNCM();
	  CH_0062_0050.flag__0062_0050--;
	  CH__EVENT(TASK_0050, OUT_0062);
	  CH__END_LOG(IN_0050);
	  break;
	}

	CH__CORE_THREAD_SCHED(IN_0050,NULL,1);

	CH__MEM_BARRIER();
      }

#ifdef TASK_IN_0050_COMPLETED
      TASK_IN_0050_COMPLETED();
#endif

      /* C code */
            {
{

    /* Math: '<S1>/MathFunction4'
     *
     * About '<S1>/MathFunction4':
     *  Operator: log10
     */
    branch_offset_rate210_Subsystem_MathFunction4_1 = log10
      (branch_offset_rate210_Subsystem_Sqrt2_1);


}

      }

#ifdef TASK_EXECUTE_0050_COMPLETED
      TASK_EXECUTE_0050_COMPLETED();
#endif
      /*
       * Block: branch_offset_rate210_Subsystem_S_Function1
       * Task: 0057
       * rate: 10000
       */

      /* C code */
            {
{

    /* S-Function (loop): '<S1>/S_Function1' */
    loop_Outputs_wrapper(&branch_offset_rate210_Subsystem_MathFunction4_1,
                         &branch_offset_rate210_Subsystem_S_Function1_1 );


}

      }

#ifdef TASK_EXECUTE_0057_COMPLETED
      TASK_EXECUTE_0057_COMPLETED();
#endif
      /*
       * Block: branch_offset_rate210_Subsystem_Gain3
       * Task: 0031
       * rate: 10000
       */

      /* C code */
            {
{

    /* Gain: '<S1>/Gain3' */
    branch_offset_rate210_Subsystem_Gain3_1 = branch_offset_rate210_P.Gain3_Gain
      * branch_offset_rate210_Subsystem_S_Function1_1;


}

      }

#ifdef TASK_EXECUTE_0031_COMPLETED
      TASK_EXECUTE_0031_COMPLETED();
#endif
      /*
       * Block: branch_offset_rate210_Subsystem_MathFunction3
       * Task: 0049
       * rate: 10000
       */

      /* C code */
            {
{

    /* Math: '<S1>/MathFunction3' */
    branch_offset_rate210_Subsystem_MathFunction3_1 = rt_powd_snf(10.0,
      branch_offset_rate210_Subsystem_Gain3_1);


}

      }

#ifdef TASK_EXECUTE_0049_COMPLETED
      TASK_EXECUTE_0049_COMPLETED();
#endif
      /*
       * Block: branch_offset_rate210_Subsystem_Gain4
       * Task: 0032
       * rate: 10000
       */

      /* C code */
            {
{

    /* Gain: '<S1>/Gain4' */
    branch_offset_rate210_Subsystem_Gain4_1 = branch_offset_rate210_P.Gain4_Gain
      * branch_offset_rate210_Subsystem_MathFunction3_1;

}

      }

#ifdef TASK_EXECUTE_0032_COMPLETED
      TASK_EXECUTE_0032_COMPLETED();
#endif
      /*
       * Block: branch_offset_rate210_Subsystem_Sqrt3
       * Task: 0063
       * rate: 10000
       */

      /* C code */
            {
{

    /* Sqrt: '<S1>/Sqrt3' */
    branch_offset_rate210_Subsystem_Sqrt3_1 = sqrt
      (branch_offset_rate210_Subsystem_Gain4_1);


}

      }

#ifdef TASK_EXECUTE_0063_COMPLETED
      TASK_EXECUTE_0063_COMPLETED();
#endif
      /*
       * Block: branch_offset_rate210_Subsystem_MathFunction6
       * Task: 0052
       * rate: 10000
       */

      /* C code */
            {
{

    /* Math: '<S1>/MathFunction6'
     *
     * About '<S1>/MathFunction6':
     *  Operator: log10
     */
    branch_offset_rate210_Subsystem_MathFunction6_1 = log10
      (branch_offset_rate210_Subsystem_Sqrt3_1);


}

      }

#ifdef TASK_EXECUTE_0052_COMPLETED
      TASK_EXECUTE_0052_COMPLETED();
#endif
      /*
       * Block: branch_offset_rate210_Subsystem_S_Function2
       * Task: 0058
       * rate: 10000
       */

      /* C code */
            {
{

    /* S-Function (loop): '<S1>/S_Function2' */
    loop_Outputs_wrapper(&branch_offset_rate210_Subsystem_MathFunction6_1,
                         &branch_offset_rate210_Subsystem_S_Function2_1 );


}

      }

#ifdef TASK_EXECUTE_0058_COMPLETED
      TASK_EXECUTE_0058_COMPLETED();
#endif
      /*
       * Block: branch_offset_rate210_Subsystem_Gain5
       * Task: 0033
       * rate: 10000
       */

      /* C code */
            {
{

    /* Gain: '<S1>/Gain5' */
    branch_offset_rate210_Subsystem_Gain5_1 = branch_offset_rate210_P.Gain5_Gain
      * branch_offset_rate210_Subsystem_S_Function2_1;


}

      }

#ifdef TASK_EXECUTE_0033_COMPLETED
      TASK_EXECUTE_0033_COMPLETED();
#endif
      /*
       * Block: branch_offset_rate210_Subsystem_MathFunction5
       * Task: 0051
       * rate: 10000
       */

      /* C code */
            {
{

    /* Math: '<S1>/MathFunction5' */
    branch_offset_rate210_Subsystem_MathFunction5_1 = rt_powd_snf(10.0,
      branch_offset_rate210_Subsystem_Gain5_1);


}

      }

#ifdef TASK_EXECUTE_0051_COMPLETED
      TASK_EXECUTE_0051_COMPLETED();
#endif
      /*
       * Block: branch_offset_rate210_Subsystem_Gain6
       * Task: 0034
       * rate: 10000
       */

      /* C code */
            {
{

    /* Gain: '<S1>/Gain6' */
    branch_offset_rate210_Subsystem_Gain6_1 = branch_offset_rate210_P.Gain6_Gain
      * branch_offset_rate210_Subsystem_MathFunction5_1;

}

      }

#ifdef TASK_EXECUTE_0034_COMPLETED
      TASK_EXECUTE_0034_COMPLETED();
#endif
      /*
       * Block: branch_offset_rate210_Subsystem_Sqrt4
       * Task: 0064
       * rate: 10000
       */

      /* C code */
            {
{

    /* Sqrt: '<S1>/Sqrt4' */
    branch_offset_rate210_Subsystem_Sqrt4_1 = sqrt
      (branch_offset_rate210_Subsystem_Gain6_1);


}

      }

#ifdef TASK_EXECUTE_0064_COMPLETED
      TASK_EXECUTE_0064_COMPLETED();
#endif
      /*
       * Block: branch_offset_rate210_Subsystem_MathFunction8
       * Task: 0054
       * rate: 10000
       */

      /* C code */
            {
{

    /* Math: '<S1>/MathFunction8'
     *
     * About '<S1>/MathFunction8':
     *  Operator: log10
     */
    branch_offset_rate210_Subsystem_MathFunction8_1 = log10
      (branch_offset_rate210_Subsystem_Sqrt4_1);


}

      }

#ifdef TASK_EXECUTE_0054_COMPLETED
      TASK_EXECUTE_0054_COMPLETED();
#endif
      /*
       * Block: branch_offset_rate210_Subsystem_S_Function3
       * Task: 0059
       * rate: 10000
       */

      /* C code */
            {
{

    /* S-Function (loop): '<S1>/S_Function3' */
    loop_Outputs_wrapper(&branch_offset_rate210_Subsystem_MathFunction8_1,
                         &branch_offset_rate210_Subsystem_S_Function3_1 );


}

      }

#ifdef TASK_EXECUTE_0059_COMPLETED
      TASK_EXECUTE_0059_COMPLETED();
#endif
      /*
       * Block: branch_offset_rate210_Subsystem_Gain7
       * Task: 0035
       * rate: 10000
       */

      /* C code */
            {
{

    /* Gain: '<S1>/Gain7' */
    branch_offset_rate210_Subsystem_Gain7_1 = branch_offset_rate210_P.Gain7_Gain
      * branch_offset_rate210_Subsystem_S_Function3_1;


}

      }

#ifdef TASK_EXECUTE_0035_COMPLETED
      TASK_EXECUTE_0035_COMPLETED();
#endif
      /*
       * Block: branch_offset_rate210_Subsystem_MathFunction7
       * Task: 0053
       * rate: 10000
       */

      /* C code */
            {
{

    /* Math: '<S1>/MathFunction7' */
    branch_offset_rate210_Subsystem_MathFunction7_1 = rt_powd_snf(10.0,
      branch_offset_rate210_Subsystem_Gain7_1);


}

      }

#ifdef TASK_EXECUTE_0053_COMPLETED
      TASK_EXECUTE_0053_COMPLETED();
#endif
      /*
       * Block: branch_offset_rate210_Subsystem_Gain8
       * Task: 0036
       * rate: 10000
       */

      /* C code */
            {
{

    /* Gain: '<S1>/Gain8' */
    branch_offset_rate210_Subsystem_Gain8_1 = branch_offset_rate210_P.Gain8_Gain
      * branch_offset_rate210_Subsystem_MathFunction7_1;


}

      }

#ifdef TASK_EXECUTE_0036_COMPLETED
      TASK_EXECUTE_0036_COMPLETED();
#endif
      /*
       * Block: branch_offset_rate210_Subsystem_Add3
       * Task: 0007
       * rate: 10000
       */

      /* wait input channel */
      while (1) {
	/* input: branch_offset_rate210_Subsystem_Add4 */
	if (CH_0008_0007.flag__0008_0007 > 0) {
	  branch_offset_rate210_Subsystem_Add4_1 = CH_0008_0007.branch_offset_rate210_Subsystem_Add4_1;
	  CH__SYNCM();
	  CH_0008_0007.flag__0008_0007--;
	  CH__EVENT(TASK_0007, OUT_0008);
	  CH__END_LOG(IN_0007);
	  break;
	}

	/* skip local input CH_0036_0007: branch_offset_rate210_Subsystem_Gain8 */

	CH__CORE_THREAD_SCHED(IN_0007,NULL,1);

	CH__MEM_BARRIER();
      }

#ifdef TASK_IN_0007_COMPLETED
      TASK_IN_0007_COMPLETED();
#endif

      /* C code */
            {
{

    /* Sum: '<S1>/Add3' */
    branch_offset_rate210_Subsystem_Add3_1 =
      branch_offset_rate210_Subsystem_Add4_1 +
      branch_offset_rate210_Subsystem_Gain8_1;

}

      }

#ifdef TASK_EXECUTE_0007_COMPLETED
      TASK_EXECUTE_0007_COMPLETED();
#endif
      /*
       * Block: branch_offset_rate210_Subsystem_Sqrt5
       * Task: 0065
       * rate: 10000
       */

      /* C code */
            {
{

    /* Sqrt: '<S1>/Sqrt5' */
    branch_offset_rate210_Subsystem_Sqrt5_1 = sqrt
      (branch_offset_rate210_Subsystem_Add3_1);


}

      }

#ifdef TASK_EXECUTE_0065_COMPLETED
      TASK_EXECUTE_0065_COMPLETED();
#endif
      /*
       * Block: branch_offset_rate210_Subsystem_MathFunction10
       * Task: 0039
       * rate: 10000
       */

      /* C code */
            {
{

    /* Math: '<S1>/MathFunction10'
     *
     * About '<S1>/MathFunction10':
     *  Operator: log10
     */
    branch_offset_rate210_Subsystem_MathFunction10_1 = log10
      (branch_offset_rate210_Subsystem_Sqrt5_1);


}

      }

#ifdef TASK_EXECUTE_0039_COMPLETED
      TASK_EXECUTE_0039_COMPLETED();
#endif
      /*
       * Block: branch_offset_rate210_Subsystem_S_Function4
       * Task: 0060
       * rate: 10000
       */

      /* C code */
            {
{

    /* S-Function (loop): '<S1>/S_Function4' */
    loop_Outputs_wrapper(&branch_offset_rate210_Subsystem_MathFunction10_1,
                         &branch_offset_rate210_Subsystem_S_Function4_1 );


}

      }

#ifdef TASK_EXECUTE_0060_COMPLETED
      TASK_EXECUTE_0060_COMPLETED();
#endif
      /*
       * Block: branch_offset_rate210_Subsystem_Gain9
       * Task: 0037
       * rate: 10000
       */

      /* C code */
            {
{

    /* Gain: '<S1>/Gain9' */
    branch_offset_rate210_Subsystem_Gain9_1 = branch_offset_rate210_P.Gain9_Gain
      * branch_offset_rate210_Subsystem_S_Function4_1;


}

      }

#ifdef TASK_EXECUTE_0037_COMPLETED
      TASK_EXECUTE_0037_COMPLETED();
#endif
      /*
       * Block: branch_offset_rate210_Subsystem_MathFunction9
       * Task: 0055
       * rate: 10000
       */

      /* C code */
            {
{

    /* Math: '<S1>/MathFunction9' */
    branch_offset_rate210_Subsystem_MathFunction9_1 = rt_powd_snf(10.0,
      branch_offset_rate210_Subsystem_Gain9_1);


}

      }

#ifdef TASK_EXECUTE_0055_COMPLETED
      TASK_EXECUTE_0055_COMPLETED();
#endif
      /*
       * Block: branch_offset_rate210_Subsystem_Gain10
       * Task: 0011
       * rate: 10000
       */

      /* C code */
            {
{

    /* Gain: '<S1>/Gain10' */
    branch_offset_rate210_Subsystem_Gain10_1 =
      branch_offset_rate210_P.Gain10_Gain *
      branch_offset_rate210_Subsystem_MathFunction9_1;


}

      }

#ifdef TASK_EXECUTE_0011_COMPLETED
      TASK_EXECUTE_0011_COMPLETED();
#endif
      /*
       * Block: branch_offset_rate210_UnitDelay
       * Task: 0068
       * rate: 10000
       */

      /* C code */
            {
{

    /* UnitDelay: '<Root>/UnitDelay' */
    branch_offset_rate210_UnitDelay_1 =
      branch_offset_rate210_DW.UnitDelay_DSTATE;

}

      }

#ifdef TASK_EXECUTE_0068_COMPLETED
      TASK_EXECUTE_0068_COMPLETED();
#endif
    }
    /*
     * Block: branch_offset_rate210_Sum
     * Task: 0067
     * rate: 2000
     */

    /* C code */
        {
{

  /* Sum: '<Root>/Sum' */
  branch_offset_rate210_Sum_1 = branch_offset_rate210_UnitDelay_1 +
    branch_offset_rate210_Gain_1;


}

    }

#ifdef TASK_EXECUTE_0067_COMPLETED
    TASK_EXECUTE_0067_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_Gain
     * Update: 0001
     * rate: 2000
     */

    /* Update */
    {
{

  /* Update for UnitDelay: '<Root>/UnitDelay1' */
  branch_offset_rate210_DW.UnitDelay1_DSTATE = branch_offset_rate210_Sum_1;


}

    }

#ifdef TASK_UPDATE_0001_COMPLETED
    TASK_UPDATE_0001_COMPLETED();
#endif
    /*
     * Block: branch_offset_rate210_UnitDelay2
     * Update: 0070
     * rate: 2000
     */

    /* Update */
    {
{

  /* Update for UnitDelay: '<Root>/UnitDelay2' */
  branch_offset_rate210_DW.UnitDelay2_DSTATE = branch_offset_rate210_Gain_1;

}

    }

#ifdef TASK_UPDATE_0070_COMPLETED
    TASK_UPDATE_0070_COMPLETED();
#endif

    if (task__time == task__time_1) {
      /*
       * Block: branch_offset_rate210_UnitDelay
       * Update: 0068
       * rate: 10000
       */

      /* Update */
      {
{

    /* Update for UnitDelay: '<Root>/UnitDelay' */
    branch_offset_rate210_DW.UnitDelay_DSTATE =
      branch_offset_rate210_Subsystem_Gain10_1;

}

      }

#ifdef TASK_UPDATE_0068_COMPLETED
      TASK_UPDATE_0068_COMPLETED();
#endif
    }

    if (task__time_1 == task__time)
      task__time_1 += task__rate_1;
    task__time += task__rate;
  }
}

TASK_CODE_PREPARE(0000)

/* Block: t0 */
/* rate: 1 */
void mcos_lcore_task_0000(uint32_t stacd, uintptr_t extinfo)
{
  /* task time */
  unsigned long task__time = 0;

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
    task__time += 1;
  }
}

TASK_CODE_PREPARE(0100)

/* Block: extout */
/* rate: 1 */
void mcos_lcore_task_0100(uint32_t stacd, uintptr_t extinfo)
{
  /* task time */
  unsigned long task__time = 0;

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
    task__time += 1;
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

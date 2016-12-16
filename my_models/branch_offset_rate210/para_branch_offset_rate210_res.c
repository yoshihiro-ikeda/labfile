#include <stdio.h>
#include <pthread.h>

/* IN_0007 */
pthread_mutex_t mutex__IN_0007 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond__IN_0007 = PTHREAD_COND_INITIALIZER;
int flag__IN_0007 = 0;

/* IN_0050 */
pthread_mutex_t mutex__IN_0050 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond__IN_0050 = PTHREAD_COND_INITIALIZER;
int flag__IN_0050 = 0;

/* IN_0061 */
pthread_mutex_t mutex__IN_0061 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond__IN_0061 = PTHREAD_COND_INITIALIZER;
int flag__IN_0061 = 0;

/* OUT_0008 */
pthread_mutex_t mutex__OUT_0008 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond__OUT_0008 = PTHREAD_COND_INITIALIZER;
int flag__OUT_0008 = 0;

/* OUT_0062 */
pthread_mutex_t mutex__OUT_0062 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond__OUT_0062 = PTHREAD_COND_INITIALIZER;
int flag__OUT_0062 = 0;

/* OUT_0070 */
pthread_mutex_t mutex__OUT_0070 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond__OUT_0070 = PTHREAD_COND_INITIALIZER;
int flag__OUT_0070 = 0;

void mcos_core0_thread(uint32_t stacd, uintptr_t exinf);
void mcos_core1_thread(uint32_t stacd, uintptr_t exinf);
void mcos_lcore_task_0000(uint32_t stacd, uintptr_t exinf);
void mcos_lcore_task_0100(uint32_t stacd, uintptr_t exinf);

static void *f__mcos_core0_thread (void *arg)
{
  if (PTHREAD_DEBUG) {
    fputs ("start mcos_core0_thread\n", stdout);
    fflush (stdout);
  }
  mcos_core0_thread (0, (uintptr_t)arg);
  return NULL;
}

static void *f__mcos_core1_thread (void *arg)
{
  if (PTHREAD_DEBUG) {
    fputs ("start mcos_core1_thread\n", stdout);
    fflush (stdout);
  }
  mcos_core1_thread (0, (uintptr_t)arg);
  return NULL;
}

static void *f__mcos_lcore_task_0000 (void *arg)
{
  if (PTHREAD_DEBUG) {
    fputs ("start mcos_lcore_task_0000\n", stdout);
    fflush (stdout);
  }
  mcos_lcore_task_0000 (0, (uintptr_t)arg);
  return NULL;
}

static void *f__mcos_lcore_task_0100 (void *arg)
{
  if (PTHREAD_DEBUG) {
    fputs ("start mcos_lcore_task_0100\n", stdout);
    fflush (stdout);
  }
  mcos_lcore_task_0100 (0, (uintptr_t)arg);
  return NULL;
}

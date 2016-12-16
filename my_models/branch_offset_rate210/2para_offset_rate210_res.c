#include <stdio.h>
#include <pthread.h>

/* IN_0022 */
pthread_mutex_t mutex__IN_0022 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond__IN_0022 = PTHREAD_COND_INITIALIZER;
int flag__IN_0022 = 0;

/* IN_0027 */
pthread_mutex_t mutex__IN_0027 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond__IN_0027 = PTHREAD_COND_INITIALIZER;
int flag__IN_0027 = 0;

/* OUT_0001 */
pthread_mutex_t mutex__OUT_0001 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond__OUT_0001 = PTHREAD_COND_INITIALIZER;
int flag__OUT_0001 = 0;

/* OUT_0003 */
pthread_mutex_t mutex__OUT_0003 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond__OUT_0003 = PTHREAD_COND_INITIALIZER;
int flag__OUT_0003 = 0;

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

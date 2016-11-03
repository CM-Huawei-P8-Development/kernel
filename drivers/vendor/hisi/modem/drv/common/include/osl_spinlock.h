

#ifndef __OSL_SPINLOCK_H
#define __OSL_SPINLOCK_H

#ifdef __KERNEL__
#include <linux/spinlock.h>

#elif defined(__VXWORKS__)
#include "osl_irq.h"
#include "spinLockAmp.h"


typedef struct spinlock {
		volatile unsigned int rlock;
} spinlock_t;


#define spin_lock_init(__specific_lock)				\
do {							\
	((spinlock_t*)__specific_lock)->rlock = 0x0;		\
} while (0)

static __inline__ void spin_lock(spinlock_t *lock)
{
	raw_spin_lock(&lock->rlock);
}

static __inline__ int spin_trylock(spinlock_t *lock)
{
	return raw_spin_trylock(&lock->rlock);
}

static __inline__ void spin_unlock(spinlock_t *lock)
{
	raw_spin_unlock(&lock->rlock);
}


#define spin_lock_irqsave(__specific_lock, __specific_flags)				\
do { \
		local_irq_save(__specific_flags); \
		if(!intContext() && !(__specific_flags&I_BIT)) \
			(void)taskLock(); \
		spin_lock(__specific_lock); \
	} while (0)

static __inline__ void spin_unlock_irqrestore(spinlock_t *lock, unsigned long flags)
{
	raw_spin_unlock(&lock->rlock);
	local_irq_restore(flags);
	if(!intContext() && !(flags&I_BIT)) 
		(void)taskUnlock(); 
	
}

#elif defined(__CMSIS_RTOS)
#include "osl_common.h"

typedef  s32 spinlock_t;

#define spin_lock_init(lock)    \
do{ 	\
	*lock = *lock; \
}while(0)


#define spin_lock_irqsave(lock, flags)    \
do{ 	\
	local_irq_save(*lock); \
}while(0)

#define spin_unlock_irqrestore(lock, flags)    \
do{ 	\
	local_irq_restore(*lock); \
}while(0)

#else
#include "osl_types.h"

typedef  int spinlock_t;

#define spin_lock_init(lock)
#define spin_lock_irqsave(lock, flags)
#define spin_unlock_irqrestore(lock, flags)

#endif /* __KERNEL__ */

#endif


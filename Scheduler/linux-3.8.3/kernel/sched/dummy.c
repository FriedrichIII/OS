/*
 * Dummy scheduling class, mapped to last five levels of SCHED_NORMAL policy
 */

#include "sched.h"


/*
 * Timeslice and age threshold are represented in jiffies. Default timeslice
 * is 100ms. Both parameters can be tuned from /proc/sys/kernel.
 */

#define DUMMY_TIMESLICE		(100 * HZ / 1000)
#define DUMMY_AGE_THRESHOLD	(3 * DUMMY_TIMESLICE)
#define HIGHEST_PRIORITY 15
#define PRIORITY_RANGE 5
#define PRIO1 15
#define PRIO2 16
#define PRIO3 17
#define PRIO4 18
#define PRIO5 19

unsigned int sysctl_sched_dummy_timeslice = DUMMY_TIMESLICE;
static inline unsigned int get_timeslice()
{
	return sysctl_sched_dummy_timeslice;
}

unsigned int sysctl_sched_dummy_age_threshold = DUMMY_AGE_THRESHOLD;
static inline unsigned int get_age_threshold()
{
	return sysctl_sched_dummy_age_threshold;
}

/*
 * Init
 */

void init_dummy_rq(struct dummy_rq *dummy_rq, struct rq *rq)
{
	//INIT_LIST_HEAD(&dummy_rq->queue);
        printk(KERN_DEBUG "DUMMY RQ : initialized");
	INIT_LIST_HEAD(&dummy_rq->queueP15);
	INIT_LIST_HEAD(&dummy_rq->queueP16);
	INIT_LIST_HEAD(&dummy_rq->queueP17);
	INIT_LIST_HEAD(&dummy_rq->queueP18);
	INIT_LIST_HEAD(&dummy_rq->queueP19);
}

/*
 * Helper functions
 */

static inline struct task_struct *dummy_task_of(struct sched_dummy_entity *dummy_se)
{
	return container_of(dummy_se, struct task_struct, dummy_se);
}

// Unused
static inline void _enqueue_task_dummy(struct rq *rq, struct task_struct *p)
{
/*
	struct sched_dummy_entity *dummy_se = &p->dummy_se;
        struct list_head *queue = &rq->dummy.queue;
        list_add_tail(&dummy_se->run_list, queue);
*/
}

static inline void _dequeue_task_dummy(struct task_struct *p)
{
	struct sched_dummy_entity *dummy_se = &p->dummy_se;
        list_del_init(&dummy_se->run_list);
}

/*
 * Scheduling class functions to implement
 */

static void
enqueue_dummy_entity(struct sched_dummy_entity* dummy_se){
		

}

static void 
enqueue_task_dummy(struct rq *rq, struct task_struct *p, int flags)
{
	//_enqueue_task_dummy(rq, p);

	struct sched_dummy_entity* dummy_se= &p->dummy_se;

	struct list_head* queue = NULL;
	// TODO check the prio values used	
	// put the given task in the right priority queue	

        printk(KERN_DEBUG "ENQUEUE TASK DUMMY - task enqueued, priority: %i\n", p->prio);
        
	int totalPriority = PRIO_TO_NICE(p->prio) - dummy_se->priorityIncrement;
	
	if (totalPriority < HIGHEST_PRIORITY){
		totalPriority = HIGHEST_PRIORITY;
	}
        //ADDED TO DEBUG
        
//        queue = &rq->dummy.queueP15;
//        list_add_tail(&dummy_se->run_list, queue );
        
        
	switch (totalPriority){
		case PRIO1 : queue = &rq->dummy.queueP15;	
			break;
		case PRIO2 : queue = &rq->dummy.queueP16;
			break;
		case PRIO3 : queue = &rq->dummy.queueP17;
			break;
		case PRIO4 : queue = &rq->dummy.queueP18;
			break;
		case PRIO5 : queue = &rq->dummy.queueP19;
			break;
		default :
			// TODO : put something here to detect the error
                       printk(KERN_DEBUG "ENQUEUE_TASK - ooops, task not enqueued!!!");
			break;
				
		
	}
	// list_add_tail does not need dummy_se->run_list to be initialized
	
        if(queue != NULL){
            list_add_tail(&dummy_se->run_list, queue);
        }
        

	//TODO we need to verify if we should preempt a task
	int currentTaskPriority=(PRIO_TO_NICE(rq->curr->prio))-rq->curr->dummy_se.priorityIncrement;

	if(currentTaskPriority>totalPriority){
		resched_task(rq->curr);
	}
	
	//enqueue_dummy_entity(dummy_se);
         
	/*struct sched_rt_entity *rt_se = &p->rt;

		if (flags & ENQUEUE_WAKEUP)
			rt_se->timeout = 0;

		enqueue_rt_entity(rt_se, flags & ENQUEUE_HEAD);

		if (!task_current(rq, p) && p->nr_cpus_allowed > 1)
			enqueue_pushable_task(rq, p);

		*/

        
	inc_nr_running(rq);
}

static void dequeue_task_dummy(struct rq *rq, struct task_struct *p, int flags)
{
	_dequeue_task_dummy(p);
        
	dec_nr_running(rq);
}
//TODO adapt this to RR----------------------------------
/*
 * Put task to the head or the end of the run list without the overhead of
 * dequeue followed by enqueue.
 */
static void
requeue_dummy_entity(struct dummy_rq *dummy_rq, struct sched_dummy_entity *dummy_se, int head)
{

	/*
	if (on_rt_rq(rt_se)) {
		struct rt_prio_array *array = &rt_rq->active;
		struct list_head *queue = array->queue + rt_se_prio(rt_se);

		if (head)
			list_move(&rt_se->run_list, queue);
		else
			list_move_tail(&rt_se->run_list, queue);
	}*/
}

static void
requeue_task_dummy(struct rq *rq, struct task_struct *p, int head)
{
	/*
	struct sched_rt_entity *rt_se = &p->rt;
	struct rt_rq *rt_rq;

	for_each_sched_rt_entity(rt_se) {
		rt_rq = rt_rq_of_se(rt_se);
		requeue_rt_entity(rt_rq, rt_se, head);
	}*/
}
//---------------------------------------

static void yield_task_dummy(struct rq *rq)
{
	//We remove the task from the list and enqueue it again
	requeue_task_dummy(rq, rq->curr, 0);

}

static void
check_preempt_curr_dummy(struct rq *rq, struct task_struct *p, int flags)
{
	//TODO ask if we need to use our own prio or the one from the task
	
	if (p->prio < rq->curr->prio) {
		resched_task(rq->curr);
		return;
	}
		
}


/*
 * Returns the nonempty queue of highest prioriy
 * from the given dummy_rq
 */
static struct list_head *
higher_nonempty_queue(struct dummy_rq *dummy_rq)
{
	if (!list_empty(&dummy_rq->queueP15)) return &dummy_rq->queueP15;
	if (!list_empty(&dummy_rq->queueP16)) return &dummy_rq->queueP16;
	if (!list_empty(&dummy_rq->queueP17)) return &dummy_rq->queueP17;
	if (!list_empty(&dummy_rq->queueP18)) return &dummy_rq->queueP18;
	if (!list_empty(&dummy_rq->queueP19)) return &dummy_rq->queueP19;
	return NULL;
}

/*
 * Select the first task_struct of the higher priority nonempty
 * queue of dummy_rq.
 * returns NULL if no task_struct in any queue
 */
static struct task_struct *
pick_next_task_dummy(struct rq *rq)
{
	struct dummy_rq *dummy_rq = &rq->dummy;
	struct list_head *queue = higher_nonempty_queue(dummy_rq);
	struct sched_dummy_entity *next;

	if (queue) {
		next = list_first_entry(queue, struct sched_dummy_entity, run_list);
		return dummy_task_of(next);
	} else {
		return NULL;
	}
}

static void put_prev_task_dummy(struct rq *rq, struct task_struct *prev)
{
}

static void set_curr_task_dummy(struct rq *rq)
{
}

static void task_tick_dummy(struct rq *rq, struct task_struct *curr, int queued)
{
}

static void switched_from_dummy(struct rq *rq, struct task_struct *p)
{
}

static void switched_to_dummy(struct rq *rq, struct task_struct *p)
{
}

static void prio_changed_dummy(struct rq *rq, struct task_struct *p, int oldprio)
{
	// condition copied over from fair.c, is it needed ?
	if(!p->se.on_rq)
		return;
		/*
		 * Comment in fair.c :
		 *
		 * Reschedule if we are currently running on this runqueue and
		 * our priority decreased, or if we are not currently running on
		 * this runqueue and our priority is higher than the current's
		 * * *
		 * What resched_task does :
		 *
		 * resched_task is used to mark that a current running task
		 * should be rescheduled, i.e. that we want to take the CPU from it.
		 *
		 * resched_task() does not interrupt anything ; it sets the TIF_NEED_RESCHED flag
		 * in the task structure. The actual switch is done in the schedule() function.
		 * The schedule() function is invoked in a lazy way by setting the aforementioned flag.
		 * The value of the flag is checked before resuming the execution of a user mode process,
		 * which means that some more cycles could be spent in kernel code before the switch.
		 *
		 * In task_tick_dummy(), one can call test_tsk_need_resched() to check if the flag is set.
		 */
		if (rq->curr == p) {
			if (p->prio > oldprio) // priority decrease
				resched_task(rq->curr);
		} else
			check_preempt_curr(rq, p, 0);

}

static unsigned int get_rr_interval_dummy(struct rq *rq, struct task_struct *p)
{
	return get_timeslice();
}

/*
 * Scheduling class
 */

const struct sched_class dummy_sched_class = {
	.next		    = &idle_sched_class,
	.enqueue_task       = enqueue_task_dummy,
	.dequeue_task       = dequeue_task_dummy,
	.yield_task         = yield_task_dummy,

	.check_preempt_curr = check_preempt_curr_dummy,

	.pick_next_task     = pick_next_task_dummy,
	.put_prev_task      = put_prev_task_dummy,

	.set_curr_task      = set_curr_task_dummy,
	.task_tick          = task_tick_dummy,

	.switched_from      = switched_from_dummy,
	.switched_to        = switched_to_dummy,
	.prio_changed       = prio_changed_dummy,

	.get_rr_interval    = get_rr_interval_dummy,
};

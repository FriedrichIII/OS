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
	INIT_LIST_HEAD(&dummy_rq->queue);
}

/*
 * Helper functions
 */

static inline struct task_struct *dummy_task_of(struct sched_dummy_entity *dummy_se)
{
	return container_of(dummy_se, struct task_struct, dummy_se);
}

static inline void _enqueue_task_dummy(struct rq *rq, struct task_struct *p)
{
	struct sched_dummy_entity *dummy_se = &p->dummy_se;
        struct list_head *queue = &rq->dummy.queue;
        list_add_tail(&dummy_se->run_list, queue);
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
enqueue_dummy_entity(){

}

static void enqueue_task_dummy(struct rq *rq, struct task_struct *p, int flags)
{
	_enqueue_task_dummy(rq, p);
	struct sched_dummy_entity *dummy_se= &p->dummy_se;

	enqueue_dummy_entity(dummy_se);

	/*struct sched_rt_entity *rt_se = &p->rt;

		if (flags & ENQUEUE_WAKEUP)
			rt_se->timeout = 0;

		enqueue_rt_entity(rt_se, flags & ENQUEUE_HEAD);

		if (!task_current(rq, p) && p->nr_cpus_allowed > 1)
			enqueue_pushable_task(rq, p);

		inc_nr_running(rq);*/


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

static void requeue_task_dummy(struct rq *rq, struct task_struct *p, int head)
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

static void check_preempt_curr_dummy(struct rq *rq, struct task_struct *p, int flags)
{
}

static struct task_struct *pick_next_task_dummy(struct rq *rq)
{
	struct dummy_rq *dummy_rq = &rq->dummy;
	struct sched_dummy_entity *next;

	if (!list_empty(&dummy_rq->queue)) {
		next = list_first_entry(&dummy_rq->queue, struct sched_dummy_entity, run_list);
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

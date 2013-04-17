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
	
static void enqueue_task_dummy(struct rq *, struct task_struct *, int);
static void dequeue_task_dummy(struct rq *, struct task_struct *, int);
static void requeue_task_dummy(struct rq *, struct task_struct *, int);


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
    printk(KERN_DEBUG "DUMMY RQ : initialized");

    struct list_head* prioArray = dummy_rq->priorities;
    int i=0;
    for (; i< DUMMY_PRIO_RANGE; i++) {
        INIT_LIST_HEAD(prioArray+i);
    }
}

/*
 * Helper functions
 */

static inline struct task_struct *dummy_task_of(struct sched_dummy_entity *dummy_se)
{
	return container_of(dummy_se, struct task_struct, dummy_se);
}



// set the given task_struct in corresponding dummy_queue
static inline void
_enqueue_task_dummy(struct rq *rq, struct task_struct *p)
{
	struct sched_dummy_entity* dummy_se= &p->dummy_se;
	struct list_head* queue = NULL;
	
	// compute the effective priority of task in the nice form	
	int totalPriority = PRIO_TO_NICE(p->prio) - dummy_se->priorityIncrement;
	
	if (totalPriority < HIGHEST_PRIORITY){
		totalPriority = HIGHEST_PRIORITY;
	}
    printk(KERN_DEBUG "ENQUEUE TASK DUMMY - task %p enqueued, priority: %i, age: %i, timeslice: %i\n", p, totalPriority, dummy_se->age, dummy_se->timeslice);            
        
    // select the queue of corresponding priority in dummy_rq
    queue = &rq->dummy.priorities[totalPriority-HIGHEST_PRIORITY];
    
    // add the dummy_se to the corresponding runqueue
	// list_add_tail does not need dummy_se->run_list to be initialized
	if(queue != NULL){
        list_add_tail(&dummy_se->run_list, queue);
    }
    
	// we verify if we should preempt the current task
	int currentTaskPriority=(PRIO_TO_NICE(rq->curr->prio))-rq->curr->dummy_se.priorityIncrement;
	if (currentTaskPriority < HIGHEST_PRIORITY) {
		currentTaskPriority = HIGHEST_PRIORITY;
	}

	if(currentTaskPriority>totalPriority){
        printk(KERN_DEBUG "ENQUEUE TASK DUMMY - current task %p preempted, current_priority: %i, new priority : %i\n",p, currentTaskPriority,totalPriority);
        // the preempting task will be chosen by the next pick_next_task call
        resched_task(rq->curr);
	}
	    
	inc_nr_running(rq);

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
set_default_se(struct sched_dummy_entity *dummy_se) {
	dummy_se->priorityIncrement = 0;
	dummy_se->age = 0;
	dummy_se->timeslice = get_timeslice();
}

static void 
enqueue_task_dummy(struct rq *rq, struct task_struct *p, int flags)
{
	struct sched_dummy_entity* dummy_se= &p->dummy_se;
	// reinitialises default dummy_se fields before enqueueing
	set_default_se(dummy_se);
	_enqueue_task_dummy(rq, p);
}

static void dequeue_task_dummy(struct rq *rq, struct task_struct *p, int flags)
{
	printk(KERN_DEBUG "DEQUEUE TASK DUMMY: dequeuing task %p\n", p);
	_dequeue_task_dummy(p);
	dec_nr_running(rq);
}

static void
requeue_task_dummy(struct rq *rq, struct task_struct *p, int head)
{
    dequeue_task_dummy(rq, p, head);
    enqueue_task_dummy(rq, p, head);
}

static void yield_task_dummy(struct rq *rq)
{
    struct sched_dummy_entity* dummy_se = &rq->curr->dummy_se;
    printk(KERN_DEBUG "YIELD TASK DUMMY - task %p yields, age: %i, timeslice: %i\n", rq->curr, dummy_se->age, dummy_se->timeslice);            
    
	//We remove the task from the list and enqueue it again
	requeue_task_dummy(rq, rq->curr, 0);
	
}

static void
check_preempt_curr_dummy(struct rq *rq, struct task_struct *p, int flags)
{
    printk(KERN_DEBUG "CHECK_PREEMP : checking preemption of task %p\n", p);
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
    int i=0;
    for(; i<DUMMY_PRIO_RANGE; i++){
        if(!list_empty(dummy_rq->priorities+i)) return dummy_rq->priorities+i;
    }
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
        struct task_struct* chosenTask= dummy_task_of(next);
        printk(KERN_DEBUG "PICK_NEXT_TASK - task %p picked, age: %i, timeslice: %i\n", chosenTask, next->age, next->timeslice);            
    
        return chosenTask;
	} else {
		return NULL;
	}
}

static void put_prev_task_dummy(struct rq *rq, struct task_struct *prev)
{
    printk(KERN_DEBUG "PUT_PREV_TASK : executed %p, previous task %p\n", rq->curr, prev);
	
}

static void set_curr_task_dummy(struct rq *rq)
{
    printk(KERN_DEBUG "SET_CURR_TASK : executed %p\n", rq->curr);
	
}


// implements ageing and timeslice.
// ageing is done before timeslice to avoid that a process "timesliced" will not be aged on the same task_tick
static void
task_tick_dummy(struct rq *rq, struct task_struct *curr, int queued)
{	
	// ageing
    
    struct dummy_rq* dummy_rq=&rq->dummy;
    
    struct list_head* crtHead=NULL;
    struct sched_dummy_entity* crtEntity=NULL;
    struct task_struct* crtTask=NULL;
    
    int to_requeue_count;
    
    
    
    int curr_prio =PRIO_TO_NICE((curr->prio)-(tmpDummy_se->priorityIncrement));
    if (curr_prio < HIGHEST_PRIORITY) curr_prio=HIGHEST_PRIORITY;
    int i = curr_prio-HIGHEST_PRIORITY+1;
    printk(KERN_DEBUG "TASK_TICK : Current task prio = %d, starting at index %d\n", curr_prio, i);
    
    // loops over all priority queues of dummy_rq, starting at the queue following the one of the current process
    // process of the same prio as current process won't age
    for (;i<DUMMY_PRIO_RANGE;i++) {
    	to_requeue_count = 0;
        crtHead=(dummy_rq->priorities)+i;
        list_for_each_entry(crtEntity,crtHead, run_list){
            //Test for ageing
            crtTask=dummy_task_of(crtEntity);
            if(crtEntity != &curr->dummy_se){
                printk(KERN_DEBUG "TASK_TICK : a task %p is aging from %d to %d\n", crtTask, crtEntity->age, crtEntity->age+1);
                crtEntity->age++;
                
                if (crtEntity->age >= get_age_threshold()) {
                	// increment priority and count number of task to requeue
                    crtEntity->priorityIncrement++;
                    printk(KERN_DEBUG "TASK_TICK : a task %p has reached age threshold %d\n", crtTask, crtEntity->age);
                    to_requeue_count ++;
                }
            }    
        }
        
    	struct task_struct* to_requeue[to_requeue_count];
    	
    	// stores the task to requeue in an array
        int j=0;
    	list_for_each_entry (crtEntity,crtHead, run_list) {
    		if (crtEntity != &curr->dummy_se && crtEntity->age >= get_age_threshold()) {
            	crtTask=dummy_task_of(crtEntity);
                printk(KERN_DEBUG "TASK_TICK : planning requeueing of task %p, %d/%d\n", crtTask, j+1, to_requeue_count);
    			to_requeue[j] = crtTask;
    			j++;
    			crtEntity->age = 0;
    		}
    	}
    	
    	// requeue the task to requeue, without reseting dummy entity fields
    	for (j=0; j<to_requeue_count; j++) {
            printk(KERN_DEBUG "TASK_TICK : Requeuing task %p\n", to_requeue[j]);
            dequeue_task_dummy(rq, to_requeue[j], 0);
            _enqueue_task_dummy(rq, to_requeue[j]);
    	}
    } // end loop on dummy_prio_queue
    
    
    
    // timeslicing	
	
    struct sched_dummy_entity* tmpDummy_se = &curr->dummy_se;
    tmpDummy_se->timeslice--;
    printk(KERN_DEBUG "TASK TICK DUMMY: timeslice of task %p reduced from %i to %i\n", curr, tmpDummy_se->timeslice+1, tmpDummy_se->timeslice);
    if(tmpDummy_se->timeslice){
    	// no timeslice here!
    }else{
        printk(KERN_DEBUG "TASK TICK DUMMY: RR for task %p\n", curr);
    	// requeue will reset sched entity fields to default value
        resched_task(curr);
        requeue_task_dummy(rq, curr, 0);
	}
}

// task_struct p is leaving dummy_rq for another rq
static void switched_from_dummy(struct rq *rq, struct task_struct *p)
{
    printk(KERN_DEBUG "SWITCHED_FROM_DUMMY : task %p switched from dummy\n ", p);
}

// task_struct p is entering dummy_rq from another rq
static void switched_to_dummy(struct rq *rq, struct task_struct *p)
{
    printk(KERN_DEBUG "SWITCHED_TO_DUMMY : task %p switched to dummy\n ", p);
	
}

static void prio_changed_dummy(struct rq *rq, struct task_struct *p, int oldprio)
{
    printk(KERN_DEBUG "PRIO_CHANGED_DUMMY : priority changed from %i to %i on task %p\n ",p->prio,oldprio, p);
	
	requeue_task_dummy(rq, rq->curr, 0);
	if (rq->curr == p && p->prio > oldprio){ // priority of current decrease
        resched_task(rq->curr);
    }

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

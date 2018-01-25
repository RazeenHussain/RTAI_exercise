#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/io.h>
#include <math.h>
#include <rtai.h>
#include <rtai_sched.h>
#include <rtai_fifos.h>


#define TICK_PERIOD 1000000
#define TASK_PRIORITY 1
#define STACK_SIZE 10000
#define FIFO 0

static RT_TASK rt_task1, rt_task2, rt_task3;

static void fun(int t)
{
	int counter = 0;
	float sin_value;   
	while (1) {
		sin_value = sin(2*M_PI*1*rt_get_cpu_time_ns()/1E9);
		//sin_value = rt_get_cpu_time_ns()/1E9;
		rtf_put(FIFO, &counter, sizeof(counter));
		rtf_put(FIFO, &sin_value, sizeof(sin_value));
		printk("(%d %d) ",t, counter)
		counter++;
		rt_task_wait_period();
	}
}

int init_module(void)
{
	RTIME tick_period;
	rt_set_periodic_mode();
	rt_task_init(&rt_task1, fun, 1, STACK_SIZE, TASK_PRIORITY, 1, 0);
	rt_task_init(&rt_task2, fun, 2, STACK_SIZE, TASK_PRIORITY, 1, 0);
	rt_task_init(&rt_task3, fun, 3, STACK_SIZE, TASK_PRIORITY, 1, 0);

	rt_set_runnable_on_cpuid (&rt_task1, 0);
	rt_set_runnable_on_cpuid (&rt_task2, 0);
	rt_set_runnable_on_cpuid (&rt_task3, 0);

	rtf_create(FIFO, 8000);
	tick_period = start_rt_timer(nano2count(TICK_PERIOD));

	RTIME start_time=rt_get_time()+tick_period;
	rt_task_make_periodic(&rt_task1, start_time, tick_period);
	rt_task_make_periodic(&rt_task2, start_time, tick_period*2);
	rt_task_make_periodic(&rt_task3, start_time, tick_period*4);
	rt_svp_RMS(0);
	return 0;
}

void cleanup_module(void)
{
	stop_rt_timer();
	rtf_destroy(FIFO);
	rt_task_delete(&rt_task1);
	rt_task_delete(&rt_task2);
	rt_task_delete(&rt_task3);
	return;
}
MODULE_LICENSE("GPL");

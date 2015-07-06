#include "debug.h"
#include "state-machine.h"
#include <string.h>

typedef	struct {
	int n;
} input_t;

int s1_entered(struct state_t* state,void* input)
{
	input_t* p = (input_t*)input;
	DEBUG_MSG("enter state 1\n");
	scanf("%d",&(p->n));
	return 0;
}

int s1_exited(struct state_t* state,void* input)
{
	input_t* p = (input_t*)input;
	DEBUG_MSG("leave state 1\n");
	return 0;
}

int s2_entered(struct state_t* state,void* input)
{
	input_t* p = (input_t*)input;
	DEBUG_MSG("enter state 2\n");
	scanf("%d",&(p->n));
	return 0;
}

int s2_exited(struct state_t* state,void* input)
{
	input_t* p = (input_t*)input;
	DEBUG_MSG("leave state 2\n");
	return 0;
}

int s3_entered(struct state_t* state,void* input)
{
	input_t* p = (input_t*)input;
	DEBUG_MSG("enter state 3\n");
	scanf("%d",&(p->n));
	return 0;
}

int s3_exited(struct state_t* state,void* input)
{
	input_t* p = (input_t*)input;
	DEBUG_MSG("leave state 3\n");
}

int final_entered(struct state_t* state,void* input)
{
	DEBUG_MSG("enter final state\n");
	state->owner->isrunning = 0;
	return 0;
}

int trans1_check(void* input)
{
	input_t* p = (input_t*)input;
	DEBUG_MSG("trans1 check\n");
	return p->n == 1 ? 1 : 0;
}

int trans2_check(void* input)
{
	input_t* p = (input_t*)input;
	DEBUG_MSG("trans2 check\n");
	return p->n == 2 ? 1 : 0;
}

int trans3_check(void* input)
{
	input_t* p = (input_t*)input;
	DEBUG_MSG("trans3 check\n");
	return p->n == 3 ? 1 : 0;
}

int trans4_check(void* input)
{
	input_t* p = (input_t*)input;
	DEBUG_MSG("trans4 check\n");
	return p->n == 4 ? 1 : 0;
}

int trans5_check(void* input)
{
	input_t* p = (input_t*)input;
	DEBUG_MSG("trans4 check\n");
	return p->n == 5 ? 1 : 0;
}

int trans6_check(void* input)
{
	input_t* p = (input_t*)input;
	DEBUG_MSG("trans4 check\n");
	return p->n == 6 ? 1 : 0;
}

void test_state_machine(void)
{
	input_t input = { .n = 0 };
	struct state_machine_t* fsm;
	struct state_t s1;
	struct state_t s2;
	struct state_t s3;
	struct state_t s4;
	
	struct transition_t t1;
	struct transition_t t2;
	struct transition_t t3;
	struct transition_t t4;
	struct transition_t t5;
	struct transition_t t6;

	bzero(&s1,sizeof(state_t));
	bzero(&s2,sizeof(state_t));
	bzero(&s3,sizeof(state_t));
	bzero(&s4,sizeof(state_t));
	bzero(&t1,sizeof(transition_t));
	bzero(&t2,sizeof(transition_t));
	bzero(&t3,sizeof(transition_t));
	bzero(&t4,sizeof(transition_t));
	bzero(&t5,sizeof(transition_t));
	bzero(&t6,sizeof(transition_t));

	s1.entered = s1_entered;
	s1.exited = s1_exited;
	s2.entered = s2_entered;
	s2.exited = s2_exited;
	s3.entered = s3_entered;
	s3.exited = s3_exited;
	s4.entered = final_entered;
	s4.exited = NULL;

	t1.event.happend = trans1_check;
	t2.event.happend = trans2_check;
	t3.event.happend = trans3_check;
	t4.event.happend = trans4_check;
	t5.event.happend = trans5_check;
	t6.event.happend = trans6_check;

	fsm_init(&fsm);
	fsm_add_state(fsm,&s1);
	fsm_add_state(fsm,&s2);
	fsm_add_state(fsm,&s3);
	fsm_add_state(fsm,&s4);
	
	fsm->cur_state = &s1;

	fsm_add_transition(&s1,&s2,&t1);
	fsm_add_transition(&s1,&s3,&t2);
	fsm_add_transition(&s2,&s1,&t3);
	fsm_add_transition(&s2,&s3,&t4);
	fsm_add_transition(&s3,&s1,&t5);
	fsm_add_transition(&s3,&s4,&t6);

	fsm_start(fsm,&input);
}

int main(void)
{
	test_state_machine();
	return 0;
}

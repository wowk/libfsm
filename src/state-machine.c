#include "state-machine.h"
#include "debug.h"
#include <stdio.h>

static int default_entered_cb(struct state_t*state,void* input)
{
	return 0;
}
static int default_exited_cb(struct state_t*state,void* input)
{
	DEBUG_MSG("default exited\n");
	return 0;
}

int fsm_init(struct state_machine_t** fsm)
{
	if( !fsm ){
		ERR_MSG("invalid argument\n");
		return -1;
	}

	*fsm = (struct state_machine_t*)calloc(1,sizeof(struct state_machine_t));
	if( *fsm == NULL ){
		STD_ERR_MSG("Cant allocate memory");
		return -1;
	}
	
	(*fsm)->default_entered = default_entered_cb;
	(*fsm)->default_exited = default_exited_cb;

	return 0;
}

static int exit_state(struct state_t* state,void* input)
{
	int ret;
	
	if( !state->exited ){
		ret = state->owner->default_exited(state,input);
	}else{
		ret = state->exited(state,input);
	}
	
	return ret;
}

static int enter_state(struct state_t* state,void* input)
{
	int ret;
	
	if( !state->entered ){
		ret = state->owner->default_entered(state,input);
	}else{
		ret = state->entered(state,input);
	}
	return ret;
}

static int do_transition(struct state_t* state,void* input)
{
	struct transition_t* p;
	p = state->trans;
	while( p ){
		if( p->event.happend(input) ){
			state->owner->cur_state = p->next_state;
			state->prev = state;
			DEBUG_MSG("will transition to another state\n");
			return 0;
		}
		p = p->_next;
	}
	ERR_MSG("no target to transition to\n");
	return -1;
}

static int to_state(struct state_t* state,void* input)
{
	int ret;
	do{
		ret=enter_state(state,input);
	}while( state->owner->isrunning && do_transition(state,input) < 0 );

	return exit_state(state,input);
}

int fsm_start(struct state_machine_t* fsm,void* input)
{
	if( fsm->isrunning ){
		ERR_MSG("this state machine has been running");
		return -1;
	}else if( fsm->cur_state == NULL ){
		ERR_MSG("need start state");
		return -1;
	}
	
	fsm->isrunning = 1;
	while( fsm->isrunning ){
		to_state(fsm->cur_state,input);
	}

	return 0;
}

int fsm_add_state(struct state_machine_t* fsm,struct state_t* state)
{
	struct state_t* p = fsm->state_lst;
	
	if( !fsm || !state ){
		ERR_MSG("invalid argument\n");
		return -1;
	}
	if( state->owner && state->owner != fsm ){
		ERR_MSG("this state belongs to another state machine\n");
		return -1;
	}
	state->owner = fsm;

	if( !p ){
		fsm->state_lst = state;
		return 0;
	}else if( p && p == state ){
		ERR_MSG("this state has been added to the state machine\n");
		return -1;
	}

	while( p->_next && p->_next != state ){
		p = p->_next;
	}
	
	if( p->_next ){
		ERR_MSG("this state has been added to the state machine\n");
		return -1;
	}
	p->_next = state;

	return 0;
}

int fsm_add_transition(struct state_t* src,struct state_t* dst,struct transition_t* trans)
{
	struct transition_t* p;

	if( !src || !dst || !trans ){
		ERR_MSG("invalid argument\n");
		return -1;
	}

	p = src->trans;
	while( p ){
		if( p == trans ){
			break;
		}
		p = p->_next;
	}

	if( p ){
		ERR_MSG("this transition is already existed\n");
		return -1;
	}
	
	trans->_next = src->trans;
	src->trans = trans;
	trans->next_state = dst;

	return 0;
}

int fsm_stat_remove(struct state_machine_t* fsm,struct state_t* state)
{

	return 0;
}

int fsm_release(struct state_machine_t** fsm)
{
	if( !fsm || !(*fsm) ){
		return 0;
	}

	if( (*fsm)->isrunning ){
		ERR_MSG("the state machine is still running\n");
		return -1;
	}

	free(*fsm);
	*fsm = NULL;

	return 0;
}


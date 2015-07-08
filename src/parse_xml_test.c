#include "state-machine.h"
#include <stdlib.h>
#include <strings.h>

typedef struct simple_stack_t {
	char* name;
	simple_stack_t* next;
} simple_stack_t;

typedef	struct xml_check_test_t {
	char hashdr;
	char* data;
	int datalen;
	simple_stack_t* tagstack;
} xml_check_test_t;

//first state : emptystate

int entered_starttagstate(state_t* state,void* input)
{
	xml_check_test_t* p = (xml_check_test_t*)input;
	
}

int exited_starttagstate(state_t* state,void* input)
{
	xml_check_test_t* p = (xml_check_test_t*)input;
}

int entered_hdrstate(state_t* state,void* input)
{
	xml_check_test_t* p = (xml_check_test_t*)input;
}

int exited_hdrstate(state_t* state,void* input)
{
	xml_check_test_t* p = (xml_check_test_t*)input;
}
int entered_attrstate(state_t* state,void* input)
{
	xml_check_test_t* p = (xml_check_test_t*)input;
}

int exited_attrstate(state_t* state,void* input)
{
	xml_check_test_t* p = (xml_check_test_t*)input;
}
int entered_endtagstate(state_t* state,void* input)
{
	xml_check_test_t* p = (xml_check_test_t*)input;
}

int exited_endtagstate(state_t* state,void* input)
{
	xml_check_test_t* p = (xml_check_test_t*)input;
}
int entered_tagvaluestate(state_t* state,void* input)
{
	xml_check_test_t* p = (xml_check_test_t*)input;
}

int exited_tagvaluestate(state_t* state,void* input)
{
	xml_check_test_t* p = (xml_check_test_t*)input;
}
int entered_emptystate(state_t* state,void* input)
{
	xml_check_test_t* p = (xml_check_test_t*)input;
}

int exited_emptystate(state_t* state,void* input)
{
	xml_check_test_t* p = (xml_check_test_t*)input;
}
int entered_finalstate(state_t* state,void* input)
{
	xml_check_test_t* p = (xml_check_test_t*)input;
}

int exited_finalstate(state_t* state,void* input)
{
	xml_check_test_t* p = (xml_check_test_t*)input;
}
int entered_errorstate(state_t* state,void* input)
{
	xml_check_test_t* p = (xml_check_test_t*)input;
}

int exited_errorstate(state_t* state,void* input)
{
	xml_check_test_t* p = (xml_check_test_t*)input;
}

int trans2hdrstate_check(void* input)
{
	return 0;
}

int trans2starttagstate_check(void* input)
{
	return 0;
}

int trans2endtagstate_check(void* input)
{
	return 0;
}

int trans2finalstate_check(void* input)
{
	return 0;
}

int trans2errorstate_check(void* input)
{
	return 0;
}

int trans2emptystate_check(void* input)
{
	return 0;
}

int trans2attrstate_check(void* input)
{
	return 0;
}

int trans2tagvaluestate_check(void* input)
{
	return 0;
}

int main(void)
{
	xml_check_test_t xc = {
		.hashdr = 0,
		.tagstack = NULL
	};

	state_machine_t* fsm = NULL;
	state_t hdrstate;
	state_t starttagstate;
	state_t attrstate;
	state_t endtagstate;
	state_t tagvaluestate;
	state_t emptystate;
	state_t finalstate;
	state_t errorstate;

	transition_t to_hdrstate;
	transition_t to_starttagstate;
	transition_t to_errorstate;
	transition_t to_tagvaluestate;
	transition_t to_finalstate;
	transition_t to_emptystate;
	transition_t to_attrstate;
	transition_t to_endtagstate;

	bzero(&hdrstate,sizeof(hdrstate));
	bzero(&starttagstate,sizeof(starttagstate));
	bzero(&attrstate,sizeof(attrstate));
	bzero(&endtagstate,sizeof(endtagstate));
	bzero(&tagvaluestate,sizeof(tagvaluestate));
	bzero(&emptystate,sizeof(emptystate));
	bzero(&finalstate,sizeof(finalstate));
	bzero(&errorstate,sizeof(errorstate));

	bzero(&to_hdrstate,sizeof(to_hdrstate));
	bzero(&to_starttagstate,sizeof(to_starttagstate));
	bzero(&to_attrstate,sizeof(to_attrstate));
	bzero(&to_endtagstate,sizeof(to_endtagstate));
	bzero(&to_tagvaluestate,sizeof(to_tagvaluestate));
	bzero(&to_emptystate,sizeof(to_emptystate));
	bzero(&to_finalstate,sizeof(to_finalstate));
	bzero(&to_errorstate,sizeof(to_errorstate));
	
	fsm_add_state(fsm,&hdrstate);
	fsm_add_state(fsm,&starttagstate);
	fsm_add_state(fsm,&endtagstate);
	fsm_add_state(fsm,&attrstate);
	fsm_add_state(fsm,&emptystate);
	fsm_add_state(fsm,&tagvaluestate);
	fsm_add_state(fsm,&finalstate);
	fsm_add_state(fsm,&errorstate);
	
	fsm_add_transition(&emptystate,&hdrstate,&to_hdrstate);
	fsm_add_transition(&emptystate,&finalstate,&to_finalstate);
	fsm_add_transition(&emptystate,&errorstate,&to_errorstate);
	fsm_add_transition(&emptystate,&starttagstate,&to_starttagstate);
	fsm_add_transition(&emptystate,&endtagstate,&to_endtagstate);
	fsm_add_transition(&emptystate,&attrstate,&to_attrstate);
	fsm_add_transition(&emptystate,&tagvaluestate,&to_tagvaluestate);

	fsm_add_transition(&starttagstate,&attrstate,&to_attrstate);
	fsm_add_transition(&starttagstate,&,&to_attrstate);
	fsm_add_transition(&starttagstate,&attrstate,&to_attrstate);
	fsm_add_transition(&starttagstate,&attrstate,&to_attrstate);
	fsm_add_transition(&starttagstate,&attrstate,&to_attrstate);

	fsm_init(&fsm);
	
	return 0;
}

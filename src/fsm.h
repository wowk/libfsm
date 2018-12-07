#ifndef	STATE_MACHINE_H_INCLUDED
#define	STATE_MACHINE_H_INCLUDED

struct state_t;

typedef	int(*enter_func_t)(struct state_t* state,void* input);
typedef	int(*exit_func_t)(struct state_t* state,void* input);
typedef	int(*event_handler_t)(void* input);

typedef	struct event_t {
	char* name;
	event_handler_t happend;
} event_t;

typedef	struct basic_state_t {

} basic_state_t;

typedef	struct state_t {
	struct state_t* prev;
	struct state_t* _next;
	struct transition_t* trans;
	struct state_machine_t* owner;
	enter_func_t entered;
	exit_func_t exited;
} state_t;

typedef	struct history_state_t {
	
} history_state_t;

typedef	struct final_state_t {
	
} final_state_t;

typedef	struct transition_t {
	struct event_t event;
	struct state_t* next_state;
	struct transition_t* _next;
} transition_t;

typedef	struct state_machine_t {
	int isrunning;
	struct state_t* cur_state;
	struct state_t* state_lst;
	enter_func_t default_entered;
	exit_func_t default_exited;
} state_machine_t;

int fsm_init(struct state_machine_t** fsm);
int fsm_start(struct state_machine_t* fsm,void* input);
int fsm_add_state(struct state_machine_t* fsm,struct state_t* state);
int fsm_add_transition(struct state_t* src,struct state_t* dst,struct transition_t* trans);
int fsm_stat_remove(struct state_machine_t* fsm,struct state_t* state);
int fsm_release(struct state_machine_t** fsm);

#endif

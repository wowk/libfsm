#ifndef FSM_H_
#define FSM_H_

struct fsm_t;
struct fsm_state_t;
struct fsm_state_trans_t;

typedef int(*trig_func_t)(struct fsm_state_trans_t*);
typedef void(*enter_func_t)(struct fsm_state_trans_t*);
typedef void(*idle_func_t)(struct fsm_state_t*);
typedef void(*leave_func_t)(struct fsm_state_trans_t*);

#ifdef __cplusplus

#define fsm_lambda(return_type, function_body) []function_body

#else

#ifndef fsm_lambda
#define fsm_lambda(return_type, function_body) ({ \
      return_type fsm_lambda__fn__cb function_body \
      fsm_lambda__fn__cb; \
})
#endif

#endif

struct fsm_state_t {
    char name[256];
    int is_final;
    struct fsm_t* fsm;
    struct fsm_state_trans_t* trans;
    struct fsm_state_t* next;
    enter_func_t enter;
    idle_func_t idle;
    leave_func_t leave;
    void* priv_data;
};

struct fsm_state_trans_t {
    int prio;
    trig_func_t trig;
    struct fsm_state_t* source;
    struct fsm_state_t* target;
    struct fsm_state_trans_t* next;
    void* priv_data;
};

struct fsm_t {
    int running;
    struct fsm_state_t* start_state;
    struct fsm_state_t* final_state;
    struct fsm_state_t* curr_state;
    struct fsm_state_t* states;
};

#ifdef __cplusplus
extern "C" {
#endif

extern int fsm_create(struct fsm_t** fsm);
extern void fsm_destroy(struct fsm_t* fsm);

extern int fsm_run_once(struct fsm_t* fsm);
extern int fsm_set_start_state(struct fsm_t*, struct fsm_state_t* state);
extern int fsm_set_final_state(struct fsm_t*, struct fsm_state_t* state);

extern struct fsm_state_t*  fsm_add_state(struct fsm_t* fsm, const char*name, enter_func_t enter,
                                          leave_func_t leave, void* userdata);

extern int fsm_add_trans(struct fsm_state_t* source, struct fsm_state_t* target,
                         int prio, trig_func_t trig, void* userdata);
#ifdef __cplusplus
}
#endif

#endif

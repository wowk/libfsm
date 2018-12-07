#include <fsm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/queue.h>


static struct fsm_state_t* fsm_new_state(const char* name)
{
    struct fsm_state_t* p;

    p = calloc(1, sizeof(struct fsm_state_t));
    if( !p ){
        return NULL;
    }
    if( name ){
        strncpy(p->name, name, sizeof(p->name) - 1);
    }

    return p;
}

static struct fsm_state_trans_t* fsm_new_trans()
{
    struct fsm_state_trans_t* p;

    p = calloc(1, sizeof(struct fsm_state_trans_t));
    if( !p ){
        return NULL;
    }

    return p;
}

int fsm_run_once(struct fsm_t* fsm)
{
    struct fsm_state_trans_t* p;

    if( !fsm ){
        return -EINVAL;
    }

    p = fsm->curr_state->trans;
    while( p ){
        if( p->trig(p) ){
            if( p->source->leave ){
                p->source->leave(p);
            }
            fsm->curr_state = p->target;
            if( p->target->enter ){
                p->target->enter(p);
                if( p->target->is_final ){
                    fsm->running = 0;
                }
            }
            break;
        }
        p = p->next;
    }

    if( fsm->curr_state->idle ){
        p->source->idle(fsm->curr_state);
    }

    return 0;
}

int fsm_set_start_state(struct fsm_t* fsm, struct fsm_state_t* state)
{
    if( !fsm || !state ){
        return -EINVAL;
    }

    fsm->start_state = state;
    fsm->curr_state = state;

    return 0;
}

int fsm_set_final_state(struct fsm_t* fsm, struct fsm_state_t* state)
{
    if( !fsm || !state ){
        return -EINVAL;
    }

    state->is_final = 1;
    fsm->final_state = state;

    return 0;
}

int fsm_add_trans(struct fsm_state_t* source, struct fsm_state_t* target,
                  int prio, trig_func_t trig, void* userdata)
{
    struct fsm_state_trans_t* trans;
    struct fsm_state_trans_t* ptr;
    struct fsm_state_trans_t* prev;

    if( !source || !target || !trig ){
        return -EINVAL;
    }

    trans = fsm_new_trans();
    if( !trans ){
        return -ENOMEM;
    }
    trans->source   = source;
    trans->target   = target;
    trans->prio     = prio;
    trans->trig     = trig;
    trans->priv_data= userdata;
    trans->next     = NULL;

    if( source->trans == NULL ){
        source->trans = trans;
        return 0;
    }

    ptr = source->trans;
    if( ptr->prio > trans->prio ){
        trans->next = ptr;
        source->trans = trans;
        return 0;
    }

    prev = source->trans;
    ptr  = source->trans->next;

    while( ptr ){
        if( ptr->prio > trans->prio ){
            break;
        }else{
            ptr = ptr->next;
            prev = prev->next;
        }
    }
    trans->next = ptr;
    prev->next = trans;

    return 0;
}

struct fsm_state_t* fsm_add_state(struct fsm_t* fsm, const char* name, enter_func_t enter,
                                  leave_func_t leave, void* userdata)
{
    struct fsm_state_t* state;

    if( !fsm ){
        errno = EINVAL;
        return NULL;
    }

    state = fsm_new_state(name);
    if( state == NULL ){
        return NULL;
    }

    state->fsm      = fsm;
    state->enter    = enter;
    state->leave    = leave;
    state->priv_data= userdata;

    state->next = fsm->states;
    fsm->states = state;

    return state;
}

int fsm_create(struct fsm_t **fsm)
{
    if( !fsm ){
        return -EINVAL;
    }

    *fsm = calloc(1, sizeof(struct fsm_t));
    if( !(*fsm) ){
        return -errno;
    }

    return 0;
}

void fsm_destroy(struct fsm_t *fsm)
{
    struct fsm_state_t* pstate;
    struct fsm_state_t* pstate_tmp;
    struct fsm_state_trans_t* ptrans;
    struct fsm_state_trans_t* ptrans_tmp;

    fsm->running = 0;
    fsm->curr_state = NULL;
    fsm->final_state = NULL;

    pstate = fsm->states;
    fsm->states = NULL;

    while( pstate ){
        ptrans = pstate->trans;
        pstate->trans = NULL;
        while (ptrans) {
            ptrans_tmp = ptrans->next;
            free(ptrans);
            ptrans = ptrans_tmp;
        }
        pstate_tmp = pstate->next;
        free(pstate);
        pstate = pstate_tmp;
    }
}

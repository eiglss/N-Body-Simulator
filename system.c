/******************************************************************************/
/*        @TITRE : system.c                                                   */
/*      @VERSION : 0                                                          */
/*     @CREATION : september, 2019                                            */
/* @MODIFICATION :                                                            */
/*      @AUTEURS : Enzo IGLESIS                                               */
/*    @COPYRIGHT : Copyright (c) 2019 Enzo IGLESIS                            */
/*      @LICENSE : MIT License (MIT)                                          */
/******************************************************************************/

/*******************************    LIBRARYS    *******************************/
#include <math.h>
#include <time.h>
#include "system.h"

/*******************************     MACROS     *******************************/
#define gaussian_pdf(x) (0.5*M_SQRT1_2*M_2_SQRTPI*exp(-0.5*(x)*(x)))
/*******************************     TYPES      *******************************/

/*******************************   CONSTANTES   *******************************/

/*******************************    VARIABLES   *******************************/

/*******************************   FUNCTIONS    *******************************/
static void system_initialize_struct(system_t * system)
{
    system->initialize_position_uniform = initialize_position_uniform;
    system->initialize_position_gaussian = initialize_position_gaussian;
    system->initialize_velocity_zero = initialize_velocity_zero;
    system->initialize_mass = initialize_mass;
    system->update_body = update_body;
    system->update_bodies = update_bodies;
    system->delete_system = delete_system;
}

static body_t * add_bodies(size_t nb)
{
    return (body_t *)malloc(nb*sizeof(body_t));
}

static void initialize_bodies(system_t * this)
{
    /* local declaration */
    size_t i;
    position_t p;
    velocity_t v;
    /* program */
    p.x = p.y = p.z = 0;
    v.x = v.y = v.z = 0;
    for(i = 0; i < this->n; i++)
    {
        initialize_body(&(this->bodies[i]), p, v, 0);
    }
}

void initialize_system(system_t * system, size_t bodies_nb)
{
    system_initialize_struct(system);
    system->n = bodies_nb;
    system->bodies = add_bodies(bodies_nb);
    initialize_bodies(system);
}

void initialize_position_uniform(system_t * this, double sigma)
{
    /* local declaration */
    size_t i;
    /* program */
    srand(time(NULL));
    for(i = 0; i < this->n; i++)
    {
        this->bodies[i].p.x = sigma*rand();
        this->bodies[i].p.y = sigma*rand();
        this->bodies[i].p.z = sigma*rand();
    }
}

void initialize_position_gaussian(system_t * this, double sigma)
{
    /* local declaration */
    size_t i;
    /* program */
    initialize_position_uniform(this, 1);
    for(i = 0; i < this->n; i++)
    {
        this->bodies[i].p.x = sigma*gaussian_pdf(this->bodies[i].p.x);
        this->bodies[i].p.y = sigma*gaussian_pdf(this->bodies[i].p.y);
        this->bodies[i].p.z = sigma*gaussian_pdf(this->bodies[i].p.z);
    }
}

void initialize_velocity_zero(system_t * this)
{
    /* local declaration */
    size_t i;
    /* program */
    for(i = 0; i < this->n; i++)
    {
        this->bodies[i].v.x = 0;
        this->bodies[i].v.y = 0;
        this->bodies[i].v.z = 0;
    }
}

void initialize_mass(system_t * this, double mass)
{
    /* local declaration */
    size_t i;
    /* program */
    for(i = 0; i < this->n; i++)
    {
        this->bodies[i].mass = mass;
    }
}

void update_body(system_t * this, size_t body)
{
    /* local declaration */
    size_t i;
    double g;
    angle_t d;
    /* program */
    for(i = 0; i < this->n; i++)
    {
        if(i != body)
        {
            g = this->bodies[body].gravity(&(this->bodies[body]), &(this->bodies[i]));
            this->bodies[body].angle(&(this->bodies[body]), &(this->bodies[i]), &d);
            this->bodies[body].accelerate(&(this->bodies[body]), g, &d);
            this->bodies[body].update_position(&(this->bodies[body]));
        }
    }
}

void update_bodies(system_t * this)
{
    /* local declaration */
    size_t i;
    /* program */
    for(i = 0; i < this->n; i++)
    {
        update_body(this, i);
    }
}

void delete_system(system_t * this)
{
    free(this->bodies);
}

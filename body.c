/******************************************************************************/
/*        @TITRE : body.c                                                   */
/*      @VERSION : 0                                                          */
/*     @CREATION : september, 2019                                            */
/* @MODIFICATION :                                                            */
/*      @AUTEURS : Enzo IGLESIS                                               */
/*    @COPYRIGHT : Copyright (c) 2019 Enzo IGLESIS                            */
/*      @LICENSE : MIT License (MIT)                                          */
/******************************************************************************/

/*******************************    LIBRARYS    *******************************/
#include <math.h>
#include "body.h"

/*******************************     MACROS     *******************************/
#define G                           6.67430e-11
#define newtown_gravity(m1, m2, r)  G*((m1)*(m2)/((r)*(r)))
#define map(x, in_min, in_max, out_min, out_max) (((x)-(in_min))*((out_max)-(out_min))/((in_max)-(in_min))+(out_min))
#define norm(x, y, z)   (sqrt(((x)*(x))+((y)*(y))+((z)*(z))))
#define sign(x)         (((x) >= 0)? 1. : -1.)
/*******************************     TYPES      *******************************/

/*******************************   CONSTANTES   *******************************/

/*******************************    VARIABLES   *******************************/

/*******************************   FUNCTIONS    *******************************/
static void body_initialize_struct(body_t * body)
{
    body->distance = distance;
    body->angle = angle;
    body->accelerate = accelerate;
    body->update_position = update_position;
    body->gravity = gravity;
}

void initialize_body(body_t * body, position_t p, velocity_t v, double mass)
{
    body_initialize_struct(body);
    body->p = p;
    body->v = v;
    body->mass = mass;
}

double distance(body_t * b1, body_t * b2)
{
    return norm((b1->p.x)-(b2->p.x), (b1->p.y)-(b2->p.y), (b1->p.z)-(b2->p.z));
}

void angle(body_t * b1, body_t * b2, angle_t * d)
{
    /* local declaration */
    point3_t opposite;
    double r;
    /* program */
    opposite.x = norm(0, (b1->p.y)-(b2->p.y),( b1->p.z)-(b2->p.z));
    opposite.y = norm((b1->p.x)-(b2->p.x), 0,( b1->p.z)-(b2->p.z));
    opposite.z = norm((b1->p.x)-(b2->p.x), (b1->p.y)-(b2->p.y), 0);
    r = distance(b1, b2);
    d->x = asin(opposite.x/r)*sign(b1->p.x);
    d->y = asin(opposite.y/r)*sign(b1->p.y);
    d->z = asin(opposite.z/r)*sign(b1->p.z);
}

static void norm2vector(point3_t * v, double norm, angle_t * d)
{
    v->x = cos(d->x)*norm;
    v->y = cos(d->y)*norm;
    v->z = cos(d->z)*norm;
}

void accelerate(body_t * this, double f, angle_t * d)
{
    /* local declaration */
    double acc = f/this->mass;
    point3_t vector;
    /* program */
    norm2vector(&vector, acc, d);
    this->v.x = this->v.x-vector.x*sign(d->x);
    this->v.y = this->v.y-vector.y*sign(d->y);
    this->v.z = this->v.z-vector.z*sign(d->z);
}

void update_position(body_t * this)
{
    this->p.x = this->p.x+this->v.x;
    this->p.y = this->p.y+this->v.y;
    this->p.z = this->p.z+this->v.z;
}

double gravity(body_t * b1, body_t * b2)
{
    /* local declaration */
    double r;
    /* program */
    r = distance(b1, b2);
    return newtown_gravity(b1->mass, b2->mass, r);
}

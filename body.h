/******************************************************************************/
/*        @TITRE : body.h                                                   */
/*      @VERSION : 0                                                          */
/*     @CREATION : september, 2019                                            */
/* @MODIFICATION :                                                            */
/*      @AUTEURS : Enzo IGLESIS                                               */
/*    @COPYRIGHT : Copyright (c) 2019 Enzo IGLESIS                            */
/*      @LICENSE : MIT License (MIT)                                          */
/******************************************************************************/
#ifndef BODY_H_
#define BODY_H_

/*******************************    LIBRARYS    *******************************/
#include <stdio.h>
#include <stdlib.h>

/*******************************     MACROS     *******************************/

/*******************************     TYPES      *******************************/
typedef struct
{
    double x;
    double y;
    double z;
}
point3_t;

typedef point3_t position_t;
typedef point3_t velocity_t;
typedef point3_t angle_t;


typedef struct body_t
{
    /* variables */
    position_t p; /* position */
    velocity_t v; /* velocity */
    double mass; /* mass */
    /* functions */
    double (* distance)(struct body_t * b1, struct body_t * b2);
    void (* angle)(struct body_t * b1, struct body_t * b2, angle_t * d);
    void (* accelerate)(struct body_t * this, double a, angle_t * d);
    void (* update_position)(struct body_t * this);
    double (* gravity)(struct body_t * b1, struct body_t * b2);
}
body_t;

/*******************************   CONSTANTES   *******************************/

/*******************************    VARIABLES   *******************************/

/*******************************   FUNCTIONS    *******************************/
void initialize_body(body_t * body, position_t p, velocity_t v, double mass);
double distance(body_t * b1, body_t * b2);
void angle(body_t * b1, body_t * b2, angle_t * d);
void accelerate(body_t * this, double g, angle_t * d);
void update_position(body_t * this);
double gravity(body_t * b1, body_t * b2);

#endif /* BODY_H_ */

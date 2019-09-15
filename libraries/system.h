/******************************************************************************/
/*        @TITRE : system.h                                                   */
/*      @VERSION : 0                                                          */
/*     @CREATION : september, 2019                                            */
/* @MODIFICATION :                                                            */
/*      @AUTEURS : Enzo IGLESIS                                               */
/*    @COPYRIGHT : Copyright (c) 2019 Enzo IGLESIS                            */
/*      @LICENSE : MIT License (MIT)                                          */
/******************************************************************************/
#ifndef SYSTEM_H_
#define SYSTEM_H_

/*******************************    LIBRARYS    *******************************/
#include <stdio.h>
#include <stdlib.h>
#include "body.h"

/*******************************     MACROS     *******************************/

/*******************************     TYPES      *******************************/
typedef struct system_t
{
    /* variables */
    body_t * bodies;
    size_t n;
    /* functions */
    void (* initialize_position_uniform)(struct system_t * this, double sigma);
    void (* initialize_position_gaussian)(struct system_t * this, double sigma);
    void (* initialize_velocity_zero)(struct system_t * this);
    void (* initialize_mass)(struct system_t * this, double mass);
    void (* update_body)(struct system_t * this, size_t body);
    void (* update_bodies)(struct system_t * this);
    void (* delete_system)(struct system_t * this);
}
system_t;

/*******************************   CONSTANTES   *******************************/

/*******************************    VARIABLES   *******************************/

/*******************************   FUNCTIONS    *******************************/
void initialize_system(system_t * system, size_t bodies_nb);
void initialize_position_uniform(system_t * this, double sigma);
void initialize_position_gaussian(system_t * this, double sigma);
void initialize_velocity_zero(system_t * this);
void initialize_mass(system_t * this, double mass);
void update_body(system_t * this, size_t body);
void update_bodies(system_t * this);
void delete_system(system_t * system);

#endif /* SYSTEM_H_ */

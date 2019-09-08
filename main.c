/******************************************************************************/
/*        @TITRE : gravity.c                                                  */
/*      @VERSION : 0                                                          */
/*     @CREATION : september, 2019                                            */
/* @MODIFICATION :                                                            */
/*      @AUTEURS : Enzo IGLESIS                                               */
/*    @COPYRIGHT : Copyright (c) 2019 Enzo IGLESIS                            */
/*      @LICENSE : MIT License (MIT)                                          */
/******************************************************************************/

/*******************************    LIBRARYS    *******************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "body.h"
#include "system.h"
/*******************************     MACROS     *******************************/

/*******************************     TYPES      *******************************/
typedef struct
{
    size_t meas_interval;
}options_t;
/*******************************   CONSTANTES   *******************************/

/*******************************    VARIABLES   *******************************/


/*******************************   FUNCTIONS    *******************************/

/*******************************      MAIN      *******************************/
int main(int argc, char const *argv[])
{
    options_t opts;

    system_t e_i;
    size_t i, j;
    FILE * data;
    initialize_system(&e_i, 2);
    data = fopen("system.dat", "w");
    /* init earth */
    e_i.bodies[0].p.x = 0;
    e_i.bodies[0].p.y = -1;
    e_i.bodies[0].p.z = 0;
    e_i.bodies[0].v.x = -0.0001;
    e_i.bodies[0].v.y = 0;
    e_i.bodies[0].v.z = 0;
    e_i.bodies[0].mass = 100;
    /* init iss */
    e_i.bodies[1].p.x = 0.5;
    e_i.bodies[1].p.y = 0.1;
    e_i.bodies[1].p.z = 0;
    e_i.bodies[1].v.x = 0;
    e_i.bodies[1].v.y = 0;
    e_i.bodies[1].v.z = 0;
    e_i.bodies[1].mass = 100;

    opts.meas_interval = 60*10;

    for(i = 0; i < 50*60*60; i++)
    {
        update_bodies(&e_i);
        if(i%opts.meas_interval)
        {
            continue;
        }
        fprintf(data, "%lu", i);
        for(j = 0; j < e_i.n; j++)
        {
            fprintf(data, ", %f, %f, %f", e_i.bodies[j].p.x, e_i.bodies[j].p.y, e_i.bodies[j].p.z);
        }
        fprintf(data, "\n");
    }
    fclose(data);
    e_i.delete_system(&e_i);

    return EXIT_SUCCESS;
}

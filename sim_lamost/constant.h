//
// Created by htian on 15/03/2018.
//
/*
 * This is the constant file, which lists the parameters during the observation.
 */

#include <math.h>
#ifndef SIM_LAMOST_CONSTANT_H
#define SIM_LAMOST_CONSTANT_H

// fraction of the plates for Time-Dominating observation
const double f_td = 0.5;

// starting/ending (included) date of the observation in format yyyymmdd
// for example 20180923 means 23rd September 2018
const int date_start = 20180923;
const int date_end = 20230923;
// time parameters
const int T_guiding = 1800;      // time for guiding stars in second
const int T_2exp = 300;          // time between twice exposure in second
const int T_exp = 1200;          // time for exposure in second

// math parameters
const double deg2rad = M_PI/180;
const double rad2deg = 180/M_PI;

const int min_dec = -36000;
const int max_dec = 216000;

// days for each month
const int days[12]={31,28,31,30,31,30,31,31,30,31,30,31};
const int days4[12]={31,29,31,30,31,30,31,31,30,31,30,31};

// time format hhmmrr
const int start_obs_time_SEP23 = 190000;   // 7:00 PMin the
const int end_obs_time_SEP23 = 293000;     // 5:30 AM in the second day

const int start_obs_time_DEC22 = 173000;   // 5:30PM
const int end_obs_time_DEC22 = 303000; // here used 240000+hhmmss for the time in the second day

//speed_startobs_time = time interval/ 90days

const int speed_startobs_time = 60; // shift speed for starting time in second per day
const int speed_endobs_time = 40; // shift speed for ending time in second per day

// magnitude range
const float min_mag = 9;
const float max_mag = 15;

#endif //SIM_LAMOST_CONSTANT_H

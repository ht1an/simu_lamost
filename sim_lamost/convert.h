//
// Created by htian on 16/03/2018.
//

#ifndef SIM_LAMOST_CONVERT_H
#define SIM_LAMOST_CONVERT_H

float calc_midnight_cdec(int obs_date);
float calc_time_cdec(int obs_date, int64_t time);
int calc_nextday(int obs_date);
int calc_nextday_new(int obs_date);
int calc_interval_days(int start_date, int end_date);
int calc_obs_time(int obs_date);

#endif //SIM_LAMOST_CONVERT_H

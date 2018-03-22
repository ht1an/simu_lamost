/*
 This is used to simulate the areas of LAMOST with observe.
 */


#include <iostream>
#include <math.h>
#include "constant.h"
#include <stdlib.h>
#include <time.h>
#include "convert.h"
#include <random>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

int main() {
    std::cout << "Hello, World!" << date_start % 10000<< std::endl;
    int64_t obstime_plate = T_guiding + T_exp + T_2exp + T_exp + T_2exp + T_exp;
    cout<<"time for observing one plate is "<<obstime_plate<<endl;
    string s_exptime = to_string(T_exp);
    // 每年9月23日赤经0度半夜上中天(upper culmination)，以此为基准计算每个时刻的天区起止赤经
    string outputpath = "/Users/htian/Documents/work/sim_lamost/";
    string sdate_start = to_string(date_start);
    string sdate_end = to_string(date_end);
    string ofname = "sim_area_"+sdate_start+"_"+sdate_end+".dat";
    ofstream output(outputpath+ofname);
    cout<<"file name is "<< outputpath+ofname<<endl;
    output<<"ra              dec            obs_date    obs_time    exposure    exposure_times"<<endl;
    cout<<calc_nextday(20180930)<<endl;
    int obs_date = date_start;
    default_random_engine generator;
    uniform_real_distribution<double> rnd(0,1);
    while (obs_date<date_end)
    {
        string sobs_date = to_string(obs_date);
        int days;
        int mmdd = obs_date % 10000;
        int dd = mmdd % 100;
        int mm = (mmdd-dd)/100;
        int yyyy = (obs_date-mmdd)/10000;
        if (mmdd<1222)
            days = calc_interval_days(obs_date,yyyy*10000+1222);
        else
            days = calc_interval_days(yyyy*10000+1222,obs_date);
        if (days>183)
            days = 183 - days % 183;

        int mmss_os = start_obs_time_DEC22 % 10000;
        int hh_os = (start_obs_time_DEC22-mmss_os)/10000;
        int ss_os = mmss_os % 100;
        int mm_os = (mmss_os-ss_os)/100;
        int64_t startobs_time = hh_os*3600 + mm_os*60 +ss_os + days*speed_startobs_time;

        int mmss_oe = end_obs_time_DEC22 % 10000;
        int hh_oe = (end_obs_time_DEC22-mmss_oe)/10000;
        int ss_oe = mmss_oe % 100;
        int mm_oe = (mmss_oe-ss_oe)/100;
        int64_t endobs_time = hh_oe*3600 + mm_oe*60 +ss_oe - days*speed_endobs_time;

        int64_t tmp_time = startobs_time;      // in unit second
        while (endobs_time-tmp_time > obstime_plate/2)
        {
            stringstream ohh,omm,oss;
            ohh<<setw(2)<<setfill('0')<<floor(double(tmp_time)/3600);
            omm<<setw(2)<<setfill('0')<<floor(double((tmp_time%3600)/60));
            oss<<setw(2)<<setfill('0')<< tmp_time % 60;
            string sobs_time = ohh.str()+omm.str()+oss.str();
            float cra = calc_time_cdec(obs_date,tmp_time); // in arcsecond
            // range for coordinate selection is cdec-2hour to cra
            float min_cra = cra-108000;
            double rnd_ra = (cra-rnd(generator)*108000)/3600+360;   // convert to degree
            int tmp_rnd_ra = int(floor(rnd_ra));
            double res_rnd_ra = rnd_ra-tmp_rnd_ra;
            rnd_ra = ((tmp_rnd_ra)+360) % 360;
            double rnd_dec = rnd(generator)*(max_dec-min_dec)/3600-10;   // convert to degree
            output<<setprecision(10)<<rnd_ra+res_rnd_ra<<"    "\
                  <<setprecision(10)<<rnd_dec<<"    "\
                  <<sobs_date<<"    "\
                  <<sobs_time<<"    "\
                  <<s_exptime<<"    "<<3<<endl;
            tmp_time = tmp_time+obstime_plate;
        }
        obs_date = calc_nextday(obs_date);
    }
    output.close();
    return 0;
}


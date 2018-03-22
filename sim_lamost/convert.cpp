//
// Created by htian on 16/03/2018.
//

//
// Created by htian on 16/03/2018.
//
#include <iostream>
#include "convert.h"
#include "constant.h"
using namespace std;

float calc_midnight_cdec(int obs_date)
{
    // 9月23日半夜0度赤经上中天，因此一切以此为基准
    // the parameter obs_data should be in the following format
    // 0923, which mean 23rd september
    float dayspeed;  // 上中天精度每天走过的度数, 单位角分
    int interval_days;
    float cdec;
    int mmdd = obs_date % 10000;
    int yyyy = (obs_date-mmdd)/10000;
    int dd = mmdd % 100;
    int mm = (mmdd-dd)/100;

    if ((yyyy % 4)==0)
    {
        dayspeed = 360*60*60/365;
    }
    else
    {
        dayspeed = 360*60*60/366;
    }
    if (mmdd<923) {
        interval_days = calc_interval_days(obs_date, yyyy * 10000 + 923);
        cdec = -interval_days * dayspeed;
    }
    else
    {
        interval_days = calc_interval_days(yyyy*10000+923,obs_date);
        cdec = interval_days * dayspeed;
    }
    return cdec;
}

int calc_interval_days(int start_date, int end_date)
{
    int interval_days = 0;
    int pre_days = 0;    //days from 1st Jan to the start date
    int post_days = 0;   //days from end_date to 31st December
    int yyyy1,yyyy2,mm1,mm2,dd1,dd2,mmdd1,mmdd2;
    mmdd1 = start_date % 10000;
    yyyy1 = (start_date - mmdd1)/10000;
    dd1 = mmdd1 % 100;
    mm1 = (mmdd1-dd1)/100;

    mmdd2 = end_date % 10000;
    yyyy2 = (end_date - mmdd2)/10000;
    dd2 = mmdd2 % 100;
    mm2 = (mmdd2-dd2)/100;
    //  first calc. the days from 1st Jan to the start date mmdd1
    if ((yyyy1 % 4)==0)
    {
        for (int im = 1; im <= mm1; ++im) {
            pre_days = pre_days + days4[im - 1];
        }

        pre_days = pre_days - days4[mm1 - 1] + dd1;

        for (int im = mm2; im <= 12; ++im) {
            post_days = post_days + days4[im - 1];
        }
        post_days = post_days - dd2;
    } else
    {
        for (int im = 1; im <= mm1; ++im) {
            pre_days = pre_days + days[im - 1];
        }

        pre_days = pre_days - days[mm1 - 1] + dd1;

        for (int im = mm2; im <= 12; ++im) {
            post_days = post_days + days[im - 1];
        }
        post_days = post_days - dd2;
    }
    for (int iy=yyyy1; iy<=yyyy2;++iy)
    {
        if ((iy % 4)==0)
            interval_days = interval_days+366;
        else
            interval_days = interval_days+365;
    }
    interval_days = interval_days - pre_days - post_days;
    return interval_days;
}

float calc_time_cdec(int obs_date, int64_t ctime)
{
    // 计算每一时刻的上中天的赤经
    // the speed of the rotation each second. in unit arcsecond per second
    // 360*60*60/24/60/60=15
    float second_speed = 15;
//    int mmss = ctime % 10000;
//    int ss = mmss % 100;
//    int hh = (ctime-mmss)/10000;
//    int mm = (mmss-ss)/100;
//    int pre_time = 24*60*60-hh*60*60-mm*60-ss;
//    24*60*60 = 86400
    int pre_time = 86400 -ctime;
    float ddec = calc_midnight_cdec(obs_date);  //半夜上中天的赤经
    float tdec = ddec - pre_time*second_speed;   // in arcsecond
    return tdec;
}
//-----------------------------------------
// this function can be improved by mod
int calc_nextday(int obs_date)
{
    int next_date;
    int mmdd = obs_date % 10000;
    int dd = mmdd % 100;
    int mm = (mmdd-dd)/100;
    int yyyy = (obs_date-mmdd)/10000;
    int tmp_days;
    if ((yyyy%4)==0)
        tmp_days = days4[mm-1];
    else
        tmp_days = days[mm-1];
    if (mmdd == 228)
    {
        if ((yyyy % 4)==0)
        {
            next_date = obs_date+1;
        }
        else
        {
            next_date = yyyy*10000+301;
        }
    } else
    {
        if (dd>tmp_days)
        {
            cout<<"The observational date "<<obs_date<<" is not in the right format!!!"<<endl;
        } else
        {
            if (mmdd==1231)
                next_date = (yyyy+1)*10000+101;
            else
            {
                if (dd<tmp_days)
                {
                    next_date = obs_date+1;
                }
                else
                    next_date = yyyy*10000+(mm+1)*100+1;
            }
        }
    }
    return next_date;
}


int calc_nextday_new(int obs_date)
{
    int mmdd = obs_date % 10000;
    int yyyy = (obs_date-mmdd)/10000;
    int dd = mmdd % 100;
    int mm = (mmdd-dd)/100;
    int tmp_days, next_date;
//    cout<<yyyy<<" "<<mm<<" "<<dd<<endl;
    if ((yyyy%4)==0)
    {
        tmp_days = days4[mm-1];
    } else
    {
        tmp_days = days[mm-1];
    }
    if (dd<=tmp_days)
    {
        int tmp_dd = dd;
        dd = tmp_dd % tmp_days+1;      // next date
        int add_month = (tmp_dd-(tmp_dd % tmp_days))/tmp_days;

        int tmp_mm = mm;
        mm = (tmp_mm-1+add_month) % 12 + 1;
        int cmm = tmp_mm+add_month-1;

        yyyy = yyyy + (cmm-(cmm % 12))/12;
        next_date = yyyy*10000+mm*100+dd;
    }
    else
    {
        cout<<"THE INPUT DATE "<<obs_date<<" IS NOT LEGAL!!"<<endl;
        next_date = date_end;
    }
    return next_date;
}


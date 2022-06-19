#include "../KF/KalmanFilter.h"
#include <stdlib.h>  
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_set>

#define NB_LINES 9

double measurement(double x){
	return (((((sin(((0.0434825)+(x))*((0.727608)+(0.752715))))+(cos((0.0434825)+(x))))+(cos((x)*(sin((x)*(0.0267149))))))+(((sin(((x)*(0.895733))*(0.478449)))+(cos((x)*((0.991333)+(0.752715)))))+(((sin((0.128527)*(x)))+(((0.991333)+(0.993831))+((0.993831)+(x))))*(0.0267149))))+(((cos((((x)/(0.991333))-((0.619303)/(0.601771)))/(cos((x)*(0.892671)))))+(cos((sin((x)*(0.895733)))+((cos(x))/((0.752715)/(0.974509))))))+(((((cos(x))*((0.619303)/(0.601771)))*((0.619303)/(0.601771)))*(sqrt(cos(sin(x)))))+(((sin((x)*(0.478449)))+((cos(x))*(0.974509)))+(cos((x)*(sqrt(x))))))));

}

int main(){

    std::vector<double> kf;
    std::vector<double> gp;
    KalmanFilter kalmanFilter = KalmanFilter(0.9, 0.9, 1.1, 0, 0.95);//1.1,0, 0.95);//0.95);
    std::unordered_set<double> learning_set = {2013, 2014, 2015, 2016, 2017, 2018, 2019};
    std::vector<double> real_set = {55, 55, 54, 53, 59, 58, 46, 62, 60};    
    std::fstream f;

    f.open("result.txt", std::ios::out);
    if (!f) {
	std::cout << "ERROR: File not created" << std::endl;
	return -1;
    }

    double  x = 2013;
    double  y_gp = 0.;
    double  y_kf = 0.;

    f << "Time" << " " << "real_data" << " " << "gp" <<" " << "gp_kf" << std::endl;
    // Apply  KF for GP equation 
    for (size_t i = 0; i < NB_LINES+3; i++)
    {
	y_gp = measurement(x); 
        gp.push_back(y_gp);
/*	if (learning_set.count(x)) y_kf = kalmanFilter.filter(real_set[i],0);
	else*/
        y_kf = kalmanFilter.filter(y_gp, 0);
	if (learning_set.count(x))
		kf.push_back(y_gp);
	else kf.push_back(y_kf);

	if ( i > NB_LINES - 1)
	    f << x << " " << 0 << " " << gp[i] <<" " << kf[i] << std::endl;
	else 
	    f << x << " " << real_set[i] << " " << gp[i] <<" " << kf[i] << std::endl;
	x++;
     }

    f.close();
    return 0;
}

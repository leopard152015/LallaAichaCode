#include "../KF/KalmanFilter.h"
#include <stdlib.h>  
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_set>

#define NB_LINES 9

double measurement(double x){
	return ((sqrt((((((x)-(0.125621))-(sin(x)))-(((0.720985)/(0.333124))/((0.20632)/(0.720985))))-(((sin(x))/(cos(0.850544)))/(0.125621)))+((((sin(x))+(sqrt(x)))/(cos((((0.20632)/(0.720985))*(x))+((sin(x))-(x)))))-((((0.569272)/(0.51398))/((0.20632)/(0.720985)))/(sin((x)+(0.849919)))))))-((((((0.20632)/(sin(x)))+(cos(sqrt(x))))+(cos(((x)+(x))-((0.569272)/(0.51398)))))+((sin((sin(0.20632))+(x)))/((((0.20632)/(0.720985))/((0.012952)*(x)))+(sin((x)*(0.125621))))))+(cos((((sin(x))/(0.850544))-(x))+((sin((x)-(0.20632)))-((sin(0.20632))+(x)))))));

}

int main(){

    std::vector<double> kf;
    std::vector<double> gp;
    KalmanFilter kalmanFilter = KalmanFilter(0.2, 0.2, 0.95, 0, 1.1);
    std::unordered_set<double> learning_set = {2013, 2014, 2015, 2016, 2017, 2018, 2019, 2020, 2021};
    std::vector<double> real_set = {45, 45, 46, 47, 41, 42, 54, 38, 40};    
    std::fstream f;

    f.open("result.txt", std::ios::out);
    if (!f) {
	std::cout << "ERROR: File not created" << std::endl;
	return -1;
    }

    double  x = 2013;
    double  y_gp = 0.;
    double  y_kf = 0.;

    f << "Time" << " " << "real_data" << " " << "gp" <<" " << "kf_gp" << std::endl;


    // Apply  KF for GP equation 
    for (size_t i = 0; i < NB_LINES+3; i++)
    {
	y_gp = measurement(x); 
        gp.push_back(y_gp);
	y_kf = kalmanFilter.filter(y_gp, 0);
	if (learning_set.count(x))
		kf.push_back(y_gp);
	else kf.push_back(y_kf);
	if ( i > NB_LINES-1 )
	    f << x << " " << 0 << " " << gp[i] <<" " << kf[i] << std::endl;
	else
	    f << x << " " << real_set[i] << " " << gp[i] <<" " << kf[i] << std::endl;
	x++;
     }

    f.close();
    return 0;
}

#include "../KF/KalmanFilter.h"
#include <stdlib.h>  
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_set>

#define NB_LINES 9

double measurement(double x){
	return ((((((((x)-(0.997606))*(sin(0.0280363)))+(sin((x)/(0.580235))))+(sin(((x)*(x))-(x))))+(sin(((cos(x))-(x))-((((x)-(0.241579))+((0.469063)*(x)))*(0.408631)))))+(((((cos(x))-((0.997606)-(x)))-(((0.902923)+(0.902923))/(sin(x))))-((sin((x)/(0.365976)))*(((x)/(0.431886))*(0.0280363))))/((cos((0.0280363)+((0.469063)*(x))))*((((0.997606)+(x))-(cos(x)))+(cos((x)/(0.365976)))))))+((sin((sin(((x)*(x))-(x)))+(sin(((x)+(0.449259))-((0.186631)*(x))))))+(sin((x)-((0.365976)*(sin((0.852343)*(x))))))));

}

int main(){

    std::vector<double> kf;
    std::vector<double> gp;
    KalmanFilter kalmanFilter = KalmanFilter(0.9, 0.9, 1.1, 0, 0.95);//1.1,0, 0.95);//0.95);
    std::unordered_set<double> learning_set = {2013, 2014, 2015, 2016, 2017, 2018, 2019, 2020, 2021};
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
	if (learning_set.count(x)) y_kf = kalmanFilter.filter(real_set[i],0);
	else y_kf = kalmanFilter.filter(y_gp, 0);
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

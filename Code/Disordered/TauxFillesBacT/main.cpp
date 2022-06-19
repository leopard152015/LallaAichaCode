#include "../KF/KalmanFilter.h"
#include <stdlib.h>  
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_set>

#define NB_LINES 9

double measurement(double x){
	return ((sin((((((0.0713833)-(0.441893))-(0.0743487))/(sqrt((0.580397)*(x))))+
		((0.763943)-(x)))*(x)))+((sin((((((0.668942)-(0.398619))+
		((0.763943)-(x)))+(x))*(sqrt((x)-((x)*(0.0743487)))))*((x)+
		((cos(x))/((x)-(0.182491))))))+((sin(cos((((0.441893)-(0.398619))+
		((0.763943)-(x)))*(((x)-(0.863564))-(cos(x))))))+
		((cos(sin((x)*(x))))/(0.0713833)))));

}

int main(){

    std::vector<double> kf;
    std::vector<double> gp;
    KalmanFilter kalmanFilter = KalmanFilter(0.2, 0.2, 1.2, 0, 0.8);
    std::unordered_set<double> learning_set = {2013, 2014, 2015, 2016, 2018, 2019};
    std::vector<double> real_set = {7, 9, 9, 14, 14, 12, 16, 18, 22};    
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
	if ( i > NB_LINES - 1)
	    f << x << " " << 0 << " " << gp[i] <<" " << kf[i] << std::endl;
	else
	    f << x << " " << real_set[i] << " " << gp[i] <<" " << kf[i] << std::endl;
	
	x++;
     }

    f.close();
    return 0;
}

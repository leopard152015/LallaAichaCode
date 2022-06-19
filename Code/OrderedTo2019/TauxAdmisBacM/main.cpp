#include "../KF/KalmanFilter.h"
#include <stdlib.h>  
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_set>

#define NB_LINES 9

double measurement(double x){
	return (((sin((0.080592)*(((0.0438992)-(x))+((sin(x))*(sin(x))))))/(sin(((((x)+(x))+(0.0438992))*((sin(0.994644))/(0.783778)))+(x))))+((sin((cos(((x)-(0.0032769))+(0.281797)))-((x)+((0.0836494)/(cos(x))))))+(((cos((0.0438992)/(cos(x))))/(0.0662483))*(cos((cos((sin(x))-(0.95128)))*(sin((0.0516748)+(x))))))));



}

int main(){

    std::vector<double> kf;
    std::vector<double> gp;
    KalmanFilter kalmanFilter = KalmanFilter(0.2, 0.2, 0.85, 2, 2.1);//0.85, 0, 1.1);
    std::unordered_set<double> learning_set = {2013, 2014, 2015, 2016, 2017, 2018, 2019};
    std::vector<double> real_set = {10, 18, 13, 18, 14, 10, 8, 6, 6};    
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
	
	if (i > NB_LINES - 1)
	    f << x << " " << 0 << " " << gp[i] <<" " << kf[i] << std::endl;
	else
	    f << x << " " << real_set[i] << " " << gp[i] <<" " << kf[i] << std::endl;

	x++;
     }

    f.close();
    return 0;
}

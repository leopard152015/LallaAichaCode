#include "../KF/KalmanFilter.h"
#include <stdlib.h>  
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_set>

#define NB_LINES 9

double measurement(double x){
	return (((((sin(((x)/(0.687479))+((x)-(0.174083))))+(((cos(x))-(0.375297))+((cos(x))+((x)-(0.174083)))))/(0.515319))+((sin(((x)-(0.0501285))*(cos(x))))*((((sin(x))*(0.852549))*(((0.804744)*(x))-(sin(x))))+((sqrt(sqrt(x)))+(((0.99095)+(0.976517))+((0.99095)+(x)))))))+(((sin((sin((0.0179992)+(x)))+((sin(0.0501285))+(x))))*(((sin((0.0179992)+(x)))*(((0.99095)+(0.976517))+((0.99095)+(x))))+((sin(sqrt(x)))*(((x)-(0.804744))-((0.976517)+(0.687479))))))+((((sqrt((x)-(0.124205)))+(((x)-(0.124205))-(sin(x))))-(sin(((0.804744)*(x))*(sqrt(x)))))+((cos((0.804744)*((x)-(0.314266))))/((0.526762)+((cos(x))-(0.0501285)))))));

}

int main(){

    std::vector<double> kf;
    std::vector<double> gp;
    KalmanFilter kalmanFilter = KalmanFilter(0.2, 0.2, 1.1, 0, 0.8);
    std::unordered_set<double> learning_set = {2013, 2014, 2015, 2016, 2017, 2018, 2019};
    std::vector<double> real_set = {5696, 5017, 5782, 5081, 6693, 11114, 7094, 11658, 6234};    
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
	y_kf = kalmanFilter.filter(y_gp, 0);
	if (learning_set.count(x))
		kf.push_back(y_gp);
	else kf.push_back(y_kf);
	if ( i > NB_LINES - 1 )
	    f << x << " " << 0 << " " << gp[i] <<" " << kf[i] << std::endl;
	else
	    f << x << " " << real_set[i] << " " << gp[i] <<" " << kf[i] << std::endl;
	x++;
     }

    f.close();
    return 0;
}

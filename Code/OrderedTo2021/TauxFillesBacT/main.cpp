#include "../KF/KalmanFilter.h"
#include <stdlib.h>  
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_set>

#define NB_LINES 9

double measurement(double x){
	return (((sin((((x)+(0.274163))*(sqrt(x)))*(((cos(0.328619))+(x))/((x)*(0.653418)))))+((cos(sin(cos((x)*(0.544693)))))/(0.112664)))+((((cos((x)*(x)))+((0.489612)+(sqrt(0.582389))))/((((cos(x))*((x)*(0.0244581)))+((cos(x))+((x)+(0.941087))))/((cos(sin(x)))*((cos(0.563502))*((x)-(0.988787))))))+((sin(((x)+((0.000602046)/(0.265368)))*(sqrt(x))))+(((0.89599)+(cos((x)*(0.292049))))/(0.170995)))));



}

int main(){

    std::vector<double> kf;
    std::vector<double> gp;
    KalmanFilter kalmanFilter = KalmanFilter(0.2, 0.2, 1.2, 0, 0.8);
    std::unordered_set<double> learning_set = {2013, 2014, 2015, 2016, 2017, 2018, 2019, 2020, 2021};
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

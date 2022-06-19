#include "../KF/KalmanFilter.h"
#include <stdlib.h>  
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_set>

#define NB_LINES 9

double measurement(double x){
	return ((((sin((((0.195596)-(x))-((x)/(x)))+((x)*(0.122123))))-
		(((0.425661)/(cos(sin(x))))+(cos((0.195596)-
		((x)/(0.0513475))))))+(cos(((x)*(((0.73599)/(0.0863202))+
		(x)))*((((0.456684)*(0.0717149))-
		((0.425661)-(x)))-(0.0400493)))))+
		((cos(cos((((x)/(x))-(x))*(cos(x)))))/(0.0602618)));

}

int main(){

    std::vector<double> kf;
    std::vector<double> gp;
    KalmanFilter kalmanFilter = KalmanFilter(0.2, 0.2, 0.85, 0, 1.1);
    std::unordered_set<double> learning_set = {2013, 2014, 2015, 2016, 2018, 2019};
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

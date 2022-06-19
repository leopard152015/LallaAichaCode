#include "../KF/KalmanFilter.h"
#include <stdlib.h>  
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_set>

#define NB_LINES 9

double measurement(double x){
	return ((sin(((((x)-(0.019091))+((0.108698)*((0.716076)/(0.422298))))+(sin(((x)-(0.716076))/(sin(x)))))+(((0.716076)/(sin(x)))+(x))))+((sin((0.0228389)*(((sin(x))+((x)+(0.840454)))/(0.382937))))*(sqrt(((((x)-(0.441657))-((0.969457)/(0.0392936)))-((sin(x))/(0.019091)))+(((0.322664)/((sin(x))/(x)))/(((x)/(0.93276))*(0.0228389)))))));

}

int main(){

    std::vector<double> kf;
    std::vector<double> gp;
    KalmanFilter kalmanFilter = KalmanFilter(0.2, 0.2, 1.1, 0, 0.9);
    std::unordered_set<double> learning_set = {2013, 2014, 2015, 2016, 2017, 2018, 2019, 2020, 2021};
    std::vector<double> real_set = {31, 30, 33, 33, 39, 40, 39, 44, 42};    
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
	if ( i > NB_LINES - 1 )
	    f << x << " " << 0 << " " << gp[i] <<" " << kf[i] << std::endl;
	else
	    f << x << " " << real_set[i] << " " << gp[i] <<" " << kf[i] << std::endl;
	
	x++;
     }

    f.close();
    return 0;
}

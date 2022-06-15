#include "../KF/KalmanFilter.h"
#include <stdlib.h>  
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_set>

#define NB_LINES 9

double measurement(double x){
	return ((((sin(((sqrt(x))/(0.202768))*((x)/((0.63884)/(x)))))+
    	    (((((x)+(0.973513))/((x)-(0.973513)))+(sin(x)))/(((sqrt(x))/((x)+
    	    (0.885954)))+(cos(x)))))-(((sin((x)*((x)-(0.769523))))*
    	    (((sin(0.30451))-((0.973513)/(x)))*(cos((0.321263)/(0.529421)))))-
    	    (sin(((sqrt(x))/(0.202768))*((x)/((0.63884)/(x)))))))+
    	    (sqrt(((((cos(x))+(0.769523))+((cos(x))+(cos(x))))/(0.239402))-
    	    ((((sin(x))/(0.48938))-(sin((x)*(0.973513))))-(((sin(0.236029))+
    	    (0.885954))*((((0.101833)/(0.905996))+
	    (x))/(sin((0.0347334)*(x)))))))));
}

int main(){

    std::vector<double> kf;
    std::vector<double> gp;
    KalmanFilter kalmanFilter = KalmanFilter(0.2, 0.2, 1.1,0, 0.95);
    std::unordered_set<double> learning_set = {2013, 2014, 2015, 2016, 2018, 2019};
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

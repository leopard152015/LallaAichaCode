#include "../KF/KalmanFilter.h"
#include <stdlib.h>  
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_set>

#define NB_LINES 9

double measurement(double x){
	return ((((((((0.778374)+(0.754226))+(0.778374))+(sin((x)*(0.738549))))+((sin((x)*(x)))+(((0.634894)*(0.634894))+((x)-(0.00788974)))))*(0.0181823))-(((cos(((0.0148923)+(x))/((0.453147)*(0.634894))))-(sin((0.359923)+((x)-(0.0148923)))))-(cos(((0.359923)*((x)-(0.0181823)))+((sqrt(x))+(0.778374))))))-(((cos(((x)-(0.00581587))/((0.643997)*(0.634894))))-((sin((sin(x))+(0.533242)))+(sin((x)+((x)-(0.533242))))))-((sin((x)*(((0.359923)*(x))+((0.648598)+(0.778374)))))+((sin(((0.781769)*(x))+((0.81989)+(x))))/((((0.643997)+(0.754226))+(0.634894))+(cos(cos(x))))))));


}

int main(){

    std::vector<double> kf;
    std::vector<double> gp;
    KalmanFilter kalmanFilter = KalmanFilter(1, 3, 1, 0, 0.9);
    std::unordered_set<double> learning_set = {2013, 2014, 2015, 2016, 2017, 2018, 2019, 2020, 2021};
    std::vector<double> real_set = {37, 34, 36, 34, 37, 43, 36, 39, 38};    
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

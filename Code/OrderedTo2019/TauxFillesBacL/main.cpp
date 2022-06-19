#include "../KF/KalmanFilter.h"
#include <stdlib.h>  
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_set>

#define NB_LINES 9

double measurement(double x){
	return (((((0.0185472)*((((0.487779)+(0.598506))/(sin(x)))+((x)-((0.974361)+(0.598506)))))-((cos(cos((x)*(0.879991))))-((sin((0.242055)*(x)))-((0.847227)-(0.351498)))))-(sin((sin((sin(x))*(x)))*(((sin(x))-((0.974361)+(x)))-((cos(0.184717))+(0.974361))))))-((cos((sqrt((cos(x))+((x)*(x))))-((((0.954605)+(0.186416))+((0.0231169)*(x)))/((cos(x))+((0.0231169)*(x))))))/((((((x)-(0.847227))*(sin(x)))/((cos(x))*((0.82451)+(x))))-(((cos(0.637909))-(0.351498))+(sin(0.847227))))-(sin(sqrt((cos(x))+((x)*(x))))))));

}

int main(){

    std::vector<double> kf;
    std::vector<double> gp;
    KalmanFilter kalmanFilter = KalmanFilter(1, 3, 1, 0, 0.9);
    std::unordered_set<double> learning_set = {2013, 2014, 2015, 2016, 2017, 2018, 2019};
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

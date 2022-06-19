#include "../KF/KalmanFilter.h"
#include <stdlib.h>  
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_set>

#define NB_LINES 9

double measurement(double x){
	return (((sin(((sin(x))*(((0.0514928)+(x))/(0.392627)))+(cos(sin((x)/(0.181388))))))*((((((x)*(0.426815))*(sqrt(0.206128)))*(sin((x)/(0.392627))))+((((x)-(0.724371))-((0.999204)/(0.141539)))-(sin((x)/(0.657446)))))/(((0.426815)*((0.392627)-((0.622373)*(0.428416))))+(cos(sin(sin(x)))))))+(((((sin((x)/(0.657446)))+((sqrt(x))+((x)-(0.999204))))/(((0.28922)*((0.343326)-(sin(x))))+(cos(sin((x)/(0.392627))))))-(((((0.724371)-(x))/((x)*(0.40378)))/(sin(x)))-((cos((x)*(0.907424)))/(((0.622373)*(0.426815))*((0.392627)-(0.206128))))))/(0.28922)));

}

int main(){

    std::vector<double> kf;
    std::vector<double> gp;
    KalmanFilter kalmanFilter = KalmanFilter(0.2, 0.2, 1.1, 0, 0.8);
    std::unordered_set<double> learning_set = {2013, 2014, 2015, 2016, 2017, 2018, 2019, 2020, 2021};
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

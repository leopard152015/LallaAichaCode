#include <cstddef>
#pragma once

class KalmanFilter {
private:
	float R;
	float Q;
	float A;
	float C;
	float B;
	float covariance;
	float x;
public:
	KalmanFilter(float R, float Q, float A, float B, float C);
	float filter(float z, float u);
};

inline KalmanFilter::KalmanFilter(float R, float Q, float A, float B, float C)
{
	this->R = R;
	this->Q = Q;
	this->A = A;
	this->C = C;
	this->B = B;
	this->covariance = NULL;
	this->x = NULL;
}

inline float KalmanFilter::filter(float z, float u)
{
	if (this->x == NULL) {
		this->x = (1 / this->C) * z;
		this->covariance = (1 / this->C) * this->Q * (1 / this->C);
	}
	else {
		float predictedX = (this->A * this->x) + (this->B * u);
		float predictedCovariance = ((this->A * this->covariance) * this->A) + this->R;
		float K = predictedCovariance * this->C * (1 / ((this->C * predictedCovariance * this->C) + this->Q));
		this->x = predictedX + K * (z - (this->C * predictedX));
		this->covariance = predictedCovariance - (K * this->C * predictedCovariance);
	}

	return this->x;
}

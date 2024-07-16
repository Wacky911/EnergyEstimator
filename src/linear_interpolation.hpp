#ifndef LINEAR_INTERPOLATION_HPP
#define LINEAR_INTERPOLATION_HPP

#include <vector>

double linearInterpolation(double x0, double y0, double x1, double y1, double x);
void interpolateData(const std::vector<double>& time, const std::vector<double>& data, std::vector<double>& interpolatedData, double step);

#endif // LINEAR_INTERPOLATION_HPP
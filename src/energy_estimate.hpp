#ifndef ENERGY_ESTIMATE_HPP
#define ENERGY_ESTIMATE_HPP

#include <iostream>
#include <vector>
#include <cmath>

double accelerationCalc(const std::vector<double>& speed, int t);
std::vector<double> energyConsumptionCalc(const std::vector<double>& speed, 
                                          const std::vector<double>& gradient,
                                          const std::vector<double>& acceleration);

#endif // ENERGY_ESTIMATE_HPP

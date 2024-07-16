#ifndef PLOT_HPP
#define PLOT_HPP

#include <vector>
#include "matplotlibcpp.h"

void plot_data(const std::vector<double>& interpolatedTime,
               const std::vector<double>& interpolatedSpeedkmph,
               const std::vector<double>& interpolatedGradient,
               const std::vector<double>& energyConsumptionKw,
               const std::vector<double>& energyConsumptionKwh);

#endif // PLOT_HPP
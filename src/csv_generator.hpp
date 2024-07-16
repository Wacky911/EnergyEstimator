#ifndef CSV_GENERATOR_HPP
#define CSV_GENERATOR_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip> 

void writeCSVenergyConsumption(const std::string& filename,
                               const std::vector<double>& time,
                               const std::vector<double>& speed,
                               const std::vector<double>& gradient,
                               const std::vector<double>& energyConsumption,
                               const std::vector<double>& energyConsumptionKwh);

#endif // CSV_GENERATOR_HPP

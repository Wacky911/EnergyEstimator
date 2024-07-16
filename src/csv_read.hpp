#ifndef CSV_READ_HPP
#define CSV_READ_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

bool readCSV(const std::string& filename, std::vector<double>& time, std::vector<double>& speed, std::vector<double>& gradient);

#endif // CSV_READ_HPP

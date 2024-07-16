// ファイル名: csv_read.cpp
// 作成者: Yuya Wakita
// 作成日: 2024-07-04
// 説明: CSVから値を読み取り変数に格納する
/////////////////////////////////////////////////////////////////////////////////////
#include "csv_read.hpp"

// 説明: CSVから値を読み取り変数に格納する
// 引数: filename CSVファイル名
//      time 1列目から読み取った値を格納する変数
//      speed 2列目から読み取った値を格納する変数
//      gradient 3列目から読み取った値を格納する変数
// 戻り値: bool true:正常終了
bool readCSV(const std::string& filename, std::vector<double>& time, std::vector<double>& speed, std::vector<double>& gradient) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    std::string line;
    if (std::getline(file, line)) {
        // ヘッダーをスキップ
    }
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string item;
        double value;
        int column = 0;

        // 行をカンマで分割し、それぞれの値を対応する変数に格納
        while (std::getline(ss, item, ',')) {
            std::stringstream itemStream(item);
            itemStream >> value;
            if (column == 0)
            {
                time.push_back(value);
            }
            else if (column == 1)
            {
                speed.push_back(value);
            }
            else if (column == 2)
            {
                gradient.push_back(value);
            }
            ++column;
        }
    }

    file.close();
    return true;
}

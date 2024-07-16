// ファイル名: main.cpp
// 作成者: Yuya Wakita
// 作成日: 2024-07-04
// 説明: 車速と勾配のプロファイルからBEVの電力消費を求める
/////////////////////////////////////////////////////////////////////////////////////
#include "csv_read.hpp"
#include "energy_estimate.hpp"
#include "linear_interpolation.hpp"
#include "csv_generator.hpp"
#include "plot.hpp"

int main() {
    std::vector<double> time;
    std::vector<double> speed;
    std::vector<double> gradient;

    std::string filename = "input.csv";

    // CSVから値を取得
    if (!readCSV(filename, time, speed, gradient)) {
        return 1;
    }

    // 1秒刻みのデータに変換
    double step = 1.0;

    std::vector<double> interpolatedTime;
    std::vector<double> interpolatedSpeed;
    std::vector<double> interpolatedGradient;

    for (double t = 0; t <= time.back(); t += step) {
        interpolatedTime.push_back(t);
    }

    interpolateData(time, speed, interpolatedSpeed, step);
    interpolateData(time, gradient, interpolatedGradient, step);

    // 加速度算出
    std::vector<double> acceleration(interpolatedSpeed.size());

    for (size_t t = 0; t < interpolatedTime.size(); ++t) {
        acceleration[t] = accelerationCalc(interpolatedSpeed, t);
    }

    // 電力消費推定モデルによる計算を実施
    std::vector<double> energyConsumption = energyConsumptionCalc(interpolatedSpeed,
                                                                  interpolatedGradient,
                                                                  acceleration);

    // 結果閲覧用にデータを加工
    std::vector<double> interpolatedSpeedkmph(interpolatedSpeed.size());
    for (size_t i = 0; i < interpolatedSpeed.size(); ++i) {
         interpolatedSpeedkmph[i] = interpolatedSpeed[i] * 3.6;
    };

    std::vector<double> energyConsumptionKw(energyConsumption.size());
    for (size_t i = 0; i < energyConsumption.size(); ++i) {
         energyConsumptionKw[i] = energyConsumption[i] / 1000;
    };

    std::vector<double> energyConsumptionKwh(energyConsumptionKw.size());
    for (size_t i = 0; i < energyConsumptionKw.size(); ++i) {
        if (i == 0) {
            energyConsumptionKwh[i] = energyConsumptionKw[i] * (1.0 / 3600.0);
        } else {
            energyConsumptionKwh[i] = energyConsumptionKwh[i - 1] + (energyConsumptionKw[i] * 1/3600);
        }
    };

    // CSV出力
    writeCSVenergyConsumption("energy_consumption.csv", interpolatedTime, interpolatedSpeedkmph,interpolatedGradient,
                               energyConsumptionKw, energyConsumptionKwh);

    // グラフを描画
    plot_data(interpolatedTime, interpolatedSpeedkmph, interpolatedGradient, energyConsumptionKw, energyConsumptionKwh);

    return 0;
}

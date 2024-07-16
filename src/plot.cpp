// ファイル名: plot.cpp
// 作成者: Yuya Wakita
// 作成日: 2024-07-07
// 説明: pythonライブラリを使用しグラフを描画する
/////////////////////////////////////////////////////////////////////////////////////
#include "plot.hpp"

namespace plt = matplotlibcpp;

// 説明: 電力消費推定モデルの計算結果をプロットする
// 引数: interpolatedTime 時間[sec]
//      interpolatedSpeedkmph 車速[km/h]
//      interpolatedGradient 勾配[rad]
//      energyConsumptionKw 電力消瞬時値[kw]
//      energyConsumptionKwh 電力消費積算値[kWh]
// 戻り値: なし
void plot_data(const std::vector<double>& interpolatedTime,
               const std::vector<double>& interpolatedSpeedkmph,
               const std::vector<double>& interpolatedGradient,
               const std::vector<double>& energyConsumptionKw,
               const std::vector<double>& energyConsumptionKwh) {

    // プロットを作成
    plt::figure_size(1200, 800);
    plt::suptitle("Vehicle Speed, Gradient, and Energy Consumption");

    // 左上のプロット
    plt::subplot(2, 2, 1);
    plt::plot(interpolatedTime, interpolatedSpeedkmph, "r-");
    plt::xlabel("Time[sec]");
    plt::ylabel("Speed[km/h]");

    // 右上のプロット
    plt::subplot(2, 2, 2);
    plt::plot(interpolatedTime, interpolatedGradient, "b-");
    plt::xlabel("Time[sec]");
    plt::ylabel("Gradient[rad]");

    // 左下のプロット
    plt::subplot(2, 2, 3);
    plt::plot(interpolatedTime, energyConsumptionKw, "g-");
    plt::xlabel("Time[sec]");
    plt::ylabel("Energy Consumption[kw]");

    // 右下のプロット
    plt::subplot(2, 2, 4);
    plt::plot(interpolatedTime, energyConsumptionKwh, "m-");
    plt::xlabel("Time[sec]");
    plt::ylabel("Energy Consumption[kWh]");

    // グラフの表示
    plt::show();
}
// ファイル名: energy_estimate.cpp
// 作成者: Yuya Wakita
// 作成日: 2024-07-07
// 説明: 電力消費推定モデルによる計算を行う
/////////////////////////////////////////////////////////////////////////////////////
#include "energy_estimate.hpp"

/////////////////////////////////////////////////////////////////////////////////////
// ここで定数を設定
/////////////////////////////////////////////////////////////////////////////////////
const double g = 9.807;       // 重力加速度[m/s^2]
const double Cr = 0.011;      // 転がり抵抗係数: Tesla Model3
const double Cd = 0.23;       // 空気抵抗係数: Tesla Model3
const double rho = 1.204;     // 空気密度[kg/m^3]: 国際標準大気 気温20℃ 気圧101.3kPa 湿度65%
const double Af = 2.22;      // フロント面積[m^2]: Tesla Model3
const double m = 1681;        // 車両総重量[kg]: Tesla Model3 1611kg + 成人男性 70kg

// 説明: 加速度を算出する
// 引数: speed 車速[m/s]
//      t 配列インデックス
// 戻り値: 加速度[m/s^2]
double accelerationCalc(const std::vector<double>& speed, int t) {
    if (t == 0 || t == speed.size() - 1) {
        return 0; // 端は適当な値を使う
    } else {
        return (speed[t + 1] - speed[t - 1]) / 2.0;
    }
}

// 説明: BEVの電力消費を求める
// 引数: speed 車速[m/s]
//      gradient 勾配[rad]
//      acceleration 加速度[m/s^2]
// 戻り値: 消費電力[watt]
std::vector<double> energyConsumptionCalc(const std::vector<double>& speed, const std::vector<double>& gradient,
                                            const std::vector<double>& acceleration) {
    std::vector<double> energyConsumption(speed.size());

    for (size_t i = 0; i < speed.size(); ++i) {
        double Vt = speed[i];
        double theta = gradient[i];
        double at = acceleration[i];

        // 勾配抵抗
        double gradeResistance = Vt * (m * g * std::sin(theta));

        // 転がり抵抗
        double rollingResistance = Vt * (m * g * Cr * std::cos(theta));

        // 空気抵抗
        double airResistance = Vt * (0.5 * rho * Vt * Vt * Af * Cd);

        // 加速抵抗
        double accelerationResistance = Vt * (m * at);

        // 消費電力をそれぞれの抵抗の総和として表現
        double power = gradeResistance + rollingResistance + airResistance + accelerationResistance;

        energyConsumption[i] = power;
    }

    return energyConsumption;
}

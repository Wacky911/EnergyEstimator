// ファイル名: liner_interpolation.cpp
// 作成者: Yuya Wakita
// 作成日: 2024-07-05
// 説明: 配列を線形補間する
/////////////////////////////////////////////////////////////////////////////////////
#include "linear_interpolation.hpp"

// 説明: 2点(x0, y0)と(x1, y1)に基づいて、xに対する線形補間値を計算する
// 引数: x0, y0 現在の座標点
//      x1, y1 次の座標点
//      x 補間値を求めたいxの値
// 戻り値: xに対するyの補間値
double linearInterpolation(double x0, double y0, double x1, double y1, double x) {
    return y0 + (y1 - y0) * ((x - x0) / (x1 - x0));
}

// 説明: 線形補間を実施する
// 引数: time 時間配列
//      data データ配列
//      interpolatedData 補間されたデータを格納するための配列
//      step 補間する時間ステップ
// 戻り値: なし
void interpolateData(const std::vector<double>& time, const std::vector<double>& data, std::vector<double>& interpolatedData, double step) {
    for (double t = 0; t <= time.back(); t += step) {
        // 時間tがどの区間にあるかを探す
        for (size_t i = 0; i < time.size() - 1; ++i) {
            if (time[i] <= t && t <= time[i+1]) {
                // 線形補間を実行
                double value = linearInterpolation(time[i], data[i], time[i+1], data[i+1], t);
                interpolatedData.push_back(value);
                break;
            }
        }
    }
}

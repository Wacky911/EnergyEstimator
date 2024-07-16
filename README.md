# Energy Estimator

任意のルートを走行した際のBEVの電力消費を算出します。  

レーシングシミュレーターへの実装を想定している為、HVAC、補機類の電力消費は考慮せず、走行によって生じる電力消費のみを算出しています。

<br>

## 概要

車速と勾配のプロファイルから電力消費を求めます。  
電力消費は勾配抵抗、転がり抵抗、空気抵抗、加速抵抗の総和として表現しており、下記の電力消費推定モデルから算出します。

<br>

$$
p_t^{dr} = v_t \left( mg \sin \theta_t + mgC_r \cos \theta_t + \frac{1}{2} \rho v_t^2 A_f C_d + ma_t \right) 
$$

<br>

- $v_t$: 時刻tにおける車速 [m/s]
- $m$: 車両総重量（車両重量 + 乗客重量）[kg]
- $g$: 重力加速度 (= 9.807 [m/s²])
- $\theta_t$: 時刻tにおける位置情報に基づく道路勾配 [deg]
- $c_r$: 転がり抵抗係数
- $c_d$: 空気抵抗係数
- $\rho$: 空気密度 [kg/m³]
- $A_f$: フロント面積 [m²]
- $a_t$: 時刻tにおける加速度 [m/s²]

<br>

参考論文: [A battery electric bus energy consumption model for strategic purposes: Validation of a proposed model structure with data from bus fleets in China and Norway](https://doi.org/10.1016/j.trd.2021.102804)

<br>

## 使用方法

1. 車速と勾配プロファイルを記載したinput.csvを用意し、実行ファイルと同じディレクトリに配置します。  
このinput.csvは任意の手法で作成しても問題ありませんが、Mapbox APIを使用してinput.csvを生成するツールを別途公開しています。詳細は[RouteProfileExtractor](https://github.com/Wacky911/RouteProfileExtractor)をご参照ください。  

<br>

<div align="center">
input.csvの構成
</div>

<div align="center">

| 列名       | データ型    | 説明                       |
|------------|-----------|----------------------------|
| time       | 浮動小数点数| 時間[sec]              　  |
| speed      | 浮動小数点数| 車速[m/s]                  |
| gradient   | 浮動小数点数| 勾配[rad]                  |

</div>

<br>

<div align="center">
サンプルデータ
</div>

<div align="center">

| time | speed | gradient |
|------|-------|----------|
| 0    | 0     | 0        |
| 3.508| 11.4  | -1.15453 |
| 4.524| 11.7  | -0.468451|
| 5.508| 11.7  | -0.58387 |
| 6.314| 11.7  | 0        |

</div>

<br>
<br>

2. プログラム実行後、電力消費算出結果がenergy_consumption.csvとして出力されます。energy_consumption.csvの構成は以下の通りです。  

<div align="center">

| 列名       | データ型    | 説明                       |
|------------|-----------|----------------------------|
| time_sec       | 整数| 時間[sec]              　  |
| speed_kmph      | 浮動小数点数| 車速[km/h]                  |
| gradient_rad   | 浮動小数点数| 勾配[rad]                  |
| energy_consumption_kw   | 浮動小数点数| 電力消費(瞬時値)[kw]                  |
| energy_consumption_kWh   | 浮動小数点数| 電力消費(積算値)[kWh]                  |

</div>

<br>
<br>

3. CSV出力後、電力消費算出結果がmatplotlibによってプロットされます。

<br>

## 注意事項

 src/energy_estimate.cppに以下の定数を設定する必要があります。
* Cr: 転がり抵抗係数
* Cd: 空気抵抗係数
* rho: 空気密度[kg/m^3]
* Af: フロント面積[m^2]
* m: 車両総重量(乗員含む)[kg]

<br>

## 必要なライブラリ
* Python 3
* NumPy

<br>

このソフトではmatplotlib-cppを使用してグラフをプロットしています。  
matplotlib-cppはPythonのmatplotlibを呼び出してグラフを描画する為、上記ライブラリの実行環境が必要です。

ライブラリインストール後、使用しているPCに応じてCMakeLists.txtを書き換えてください。

<br>

参考リポジトリ: [matplotlib-cpp](https://github.com/lava/matplotlib-cpp)

<br>

## ビルドと実行

CMakeLists.txtを使用してビルドするには、以下のコマンドを実行します。

```
cd build
```

```
cmake ..
```

```
cmake --build .
```

<br>

プログラムを実行するには以下のコマンドを実行します。
```
./EnergyEstimator
```

<br>

## 使用言語とテスト環境

* OS: macOS 14.5
* プログラミング言語: C++  
* コンパイラ: clang++  
* 依存ライブラリ: Python 3.12, Numpy
* CMakeバージョン: 3.30.0
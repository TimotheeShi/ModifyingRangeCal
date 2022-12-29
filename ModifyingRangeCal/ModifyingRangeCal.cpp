#include <iostream>
#include <iomanip>
#include <math.h>

const double PI = 3.1415926;

using namespace std;

void calculate(double m, double z1, double x1, double z2, double x2, double a, double h1 = 1, double h2 = 2, double alpha = 20) {
    double hc1 = 1, hc2 = 1;
    double cc1 = 0.25, cc2 = 0.25;

    // Calculating tip diameters:
    double da1, da2, d_a1, d_a2; // da1 & da2 are theoretical tip diameters. d_a1 & d_a2 are actual tip diameters.
    da1 = m * z1 + 2 * (hc1 +  x1) * m;
    da2 = m * z2 + 2 * (hc2 +  x2) * m;
    if (h1 != hc1 || h2 != hc2) {
        d_a1 = m * z1 + 2 * (h1 + x1) * m;
        d_a2 = m * z2 + 2 * (h2 + x2) * m;
    }
    else {
        d_a1 = da1;
        d_a2 = da2;
    }

    // Calculating root diameters:
    double df1 = m * z1 - 2 * (hc1 + cc1 - x1) * m;
    double df2 = m * z2 - 2 * (hc2 + cc2 - x2) * m;

    // Calculating base diameters:
    double db1 = m * z1 * cos(alpha * PI / 180);
    double db2 = m * z2 * cos(alpha * PI / 180);

    // Calculating ranges:
    double a1 = (z1 + z2) * m / 2;
    if (a1 != a) {
        alpha = acos(a1 * cos(alpha * PI / 180) / a) / PI * 180;
        cout << "   |   理论中心距 != 实际中心距" << endl;
    }
    double lae = pow(pow(da1 / 2, 2) - pow(db1 / 2, 2), 0.5) + pow(pow(da2 / 2, 2) - pow(db2 / 2, 2), 0.5) - a * sin(alpha * PI / 180);
    double l_ae = pow(pow(d_a1 / 2, 2) - pow(db1 / 2, 2), 0.5) + pow(pow(d_a2 / 2, 2) - pow(db2 / 2, 2), 0.5) - a * sin(alpha * PI / 180);
    double la = l_ae * 0.92;
    double root_modify_range = lae / 4;
    double tip_modity_range = lae / 4 - (lae - l_ae);
    double flank_manage_range = lae / 2;

    // Calculating diameters:
    double db22 = pow(db2, 2);
    double l1 = pow(pow(da2/2, 2) - pow(db2/2, 2), 0.5);
    double l2 = l1 - 0.25 * lae;
    double d1 = pow(pow(2 * l2, 2) + db22, 0.5);
    double l3 = l1 - 0.75 * lae;
    double d2 = pow(pow(2 * l3, 2) + db22, 0.5);
    double l4 = l1 - lae;
    double dnf = pow(pow(2 * l4, 2) + db22, 0.5);
    double dff = dnf - 0.3 * m;

    // Calculating Tooth Spaned Number and the Wk:
    double k = (z2 / 180) * acos(z2 * cos(20 * PI / 180) / (z2 + 2 * x2)) * 180 / PI + 0.5;
    int k_a = k + 0.5;
    double inv_a = tan(PI / 9) - PI / 9;
    double Wk = m * cos(PI / 9) * (PI * (k_a - 0.5) + z2 * inv_a) + 2 * x2 * m * sin(PI / 9);
    double Wk_max = Wk + (-0.019);
    double Wk_min = Wk + (-0.044);

    // Print results:
    cout << "   |   行星齿轮相关参数: " << endl;
    cout << setiosflags(ios::fixed);
    cout << "   | * LAE()： " << setprecision(3) << l_ae << endl;
    cout << "   |   Lα： " << setprecision(3) << la << endl;
    cout << "   | * 齿廓计值范围：" << setprecision(3) << flank_manage_range << endl;
    cout << "   | * 齿顶修形管理范围：" << setprecision(3) << tip_modity_range << endl;
    cout << "   | * 齿根修形管理范围：" << setprecision(3) << root_modify_range << endl;
    cout << "   | * 齿顶圆直径：Φ" << setprecision(3) << d_a2 << endl;
    cout << "   | * 齿顶修形起始圆直径：Φ" << setprecision(3) << d1 << endl;
    cout << "   | * 齿根修形终止圆直径：Φ" << setprecision(3) << d2 << endl;
    cout << "   | * 齿根修形起始圆直径(dNf)：Φ" << setprecision(3) << dnf << endl;
    cout << "   |   渐开线起始圆直径(dFf)：Φ" << setprecision(3) << dff << endl;
    cout << "   |   齿根圆直径：Φ" << setprecision(3) << df2 << endl;
    cout << "   | " << endl;
    cout << "   |   跨齿数为：" << k_a << endl;
    cout << "   |   Wk：     " << Wk << endl;
    cout << "   |   Wk_max： " << Wk_max << endl;
    cout << "   |   Wk_min： " << Wk_min << endl << endl;
}

int main() {

    double m = 0;
    double z1 = 0, z2 = 0;
    double x1 = 0, x2 = 0;
    double a = 0;
    double h1 = 1, h2 = 1;

    int i = 1;

    while (true) {
        cout << "[" << i << "]: 请输入<输入齿轮>相关参数（以‘ ’（空格）分隔）：齿数，变位系数，齿顶高系数\n     ->  ";
        cin >> z1 >> x1 >> h1;
        cout << "[" << i << "]: 请输入<行星齿轮>相关参数（以‘ ’（空格）分隔）：齿数，变位系数，齿顶高系数\n     ->  ";
        cin >> z2 >> x2 >> h2;
        cout << "[" << i << "]: 请输入模数和中心距：\n     ->  ";
        cin >> m >> a;

        cout << endl << "[" << i << "] output: " << endl;

        calculate(m, z1, x1, z2, x2, a, h1, h2);

        cout << endl;
        i++;
    }
    return 0;
}
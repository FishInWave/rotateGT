/**
 * @file rotateGT.cpp
 * @author your name (you@domain.com)
 * @brief 读取文件名，并将其中的内容使用KITTI标定参数进行旋转。
 * @version 0.1
 * @date 2021-05-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <string>
#include <iostream>
#include <Eigen/Core>
#include <fstream>
#include "util_common.hpp"
int main(int argc, char **argv)
{
    std::cout << "please type in KITTI GT file path: " << std::endl;
    std::string file_name;
    std::cin >> file_name;
    std::cout << "please type in data of the sequence: (e.g. 09_30)" << std::endl;
    std::string data;
    std::cin >> data;
    Eigen::Matrix4d T_C2L;
    T_C2L.setIdentity();
    if (data.find("10_03")!= string::npos)
    {
        T_C2L.block<3, 4>(0, 0) << 4.276802385584e-04, -9.999672484946e-01, -8.084491683471e-03, -1.198459927713e-02, -7.210626507497e-03, 8.081198471645e-03, -9.999413164504e-01, -5.403984729748e-02, 9.999738645903e-01, 4.859485810390e-04, -7.206933692422e-03, -2.921968648686e-01;
    }
    else if (data.find("09_26")!= string::npos)
    {
        T_C2L.block<3, 4>(0, 0) << 2.347736981471e-04, -9.999441545438e-01, -1.056347781105e-02, -2.796816941295e-03, 1.044940741659e-02, 1.056535364138e-02, -9.998895741176e-01, -7.510879138296e-02, 9.999453885620e-01, 1.243653783865e-04, 1.045130299567e-02, -2.721327964059e-01;
    }
    else if (data.find("09_30")!= string::npos)
    {
        T_C2L.block<3, 4>(0, 0) << -1.857739385241e-03, -9.999659513510e-01, -8.039975204516e-03, -4.784029760483e-03, -6.481465826011e-03, 8.051860151134e-03, -9.999466081774e-01, - 7.337429464231e-02, 9.999773098287e-01, -1.805528627661e-03, -6.496203536139e-03, -3.339968064433e-01;
    }
    else
    {
        std::cout << "wrong data,please check." << std::endl;
        return -1;
    }

    // 配置文件流
    ifstream ifs(file_name, ifstream::in);
    string line;
    string new_file_name = file_name;
    auto position = new_file_name.find(".txt");
    position -= 3; // 定位到/
    string f_name = new_file_name.substr(position);
    new_file_name = new_file_name.substr(0, position);

    new_file_name += "/new";
    string command = "mkdir -p " + new_file_name;
    system(command.c_str());
    new_file_name += f_name;
    ofstream ofs(new_file_name, ofstream::out);
    double d;
    vector<double> list;
    double arr[12];
    int i = 0;
    while (ifs >> d)
    {
        arr[i++] = d;
        if (i >= 12)
        {
            // Note:必须指定row-major
            Eigen::Map<Eigen::Matrix<double, 3, 4, Eigen::RowMajor>> map(arr);
            Eigen::Matrix4d pose_C02i(Eigen::Matrix4d::Identity());
            pose_C02i.block<3, 4>(0, 0) = map;
            Eigen::Matrix4d pose_L02i = T_C2L.inverse() * pose_C02i * T_C2L;
            // 按照KITTI格式写入
            for (int m = 0; m < 3; ++m)
            {
                for (int n = 0; n < 4; ++n)
                {
                    ofs << pose_L02i(m, n);
                    if (m == 2 && n == 3)
                    {
                        ofs << endl;
                    }
                    else
                    {
                        ofs << " ";
                    }
                }
            }
            i = 0;
        }
    }

    // for(auto c:list){
    //     cout << c <<" "<<flush;
    // }
    // cout << endl;
    ifs.close();
    ofs.close();
    cout << "new file was saved as: " << new_file_name << endl;
    return 0;
}
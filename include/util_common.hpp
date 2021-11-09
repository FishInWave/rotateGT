#include <Eigen/Geometry>
#include <dirent.h>
#include <vector>
#include <iostream>
#include <yaml-cpp/yaml.h>
#include <algorithm>

using namespace std;
/**
 * @brief 给定路径，将一级路径下所有文件名存成vector 
 * 
 * @param dir in 文件夹路径
 * @param fileList out 文件名列表 
 * @return int <0为异常
 */
int getFileNames(string dir, vector<string> &fileList)
{
    DIR *pDir;
    dirent *ptr;
    if (!(pDir = opendir(dir.c_str())))
    {
        cout << "can not open the dirent: " << dir << endl;
        return -1;
    }
    while ((ptr = readdir(pDir)) != 0)
    {
        if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0)
            fileList.push_back(ptr->d_name);
    }
    sort(fileList.begin(),fileList.end());
    closedir(pDir);
    return 0;
}
# 程序说明
    KITTI里的pose是RTK模式下的GPS/IMU套件输出的结果，位置误差在0.1m以内，但是这个真值被转换成了 第i帧左目坐标系在第0帧左目中的位姿。该程序的目的是将上述值转换为 第i帧激光在第0帧激光中的位姿。calib.txt里给出了Tr，该值是指camere->Lidar,故程序的数学表达式为：
    (L0->Li)T=Tr^(-1) * pose * Tr

# 运行说明
    将ground_truth_pose拷贝至工程文件夹下，运行
    `
    mkdir build && cd build
    cmake ..
    make 
    ./rotateGT 
    `
    然后按照提示依次输入要转换的txt文件路径和该数据集的采集日期。
    输出结果将被存储至ground_truth_pose/new/下，该仓库中已经上传了转换后的txt文件。

    ps：
    00-02 为10_03
    03 为 09_26
    04-10 为 09_30
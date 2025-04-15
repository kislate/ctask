#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(void)
{
    // 打开摄像头（设备编号为 0）
    VideoCapture cap(0);
    if (!cap.isOpened())
    {
        cerr << "无法打开摄像头！" << endl;
        return -1;
    }

    Mat frame;
    while (true)
    {
        // 从摄像头捕获一帧
        cap >> frame;
        if (frame.empty())
        {
            cerr << "无法捕获帧！" << endl;
            break;
        }

        // 显示捕获的帧
        imshow("Camera Feed", frame);

        // 按下 'q' 键退出
        if (waitKey(30) == 'q')
        {
            break;
        }
    }

    // 释放摄像头资源
    cap.release();
    destroyAllWindows();
    return 0;
}

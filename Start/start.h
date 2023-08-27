#ifndef START_H
#define START_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <iomanip>
#include <opencv2/ml/ml.hpp>

#include <fcntl.h>   /* File Control Definitions           */
#include <termios.h> /* POSIX Terminal Control Definitions */
#include <unistd.h>  /* UNIX Standard Definitions 	   */
#include <errno.h>   /* ERROR Number Definitions           */
#include <stdlib.h>
#include <cstdio>
#include <unistd.h>
#include <sys/ioctl.h>
#include <mutex>

using namespace cv;
using namespace ml;//Ptr<SVM>
using namespace std;

class Start
{
public:
//    Start();

    void ImgProcess();
    void TargetProcess();
    void Recive();
    void Send();

    void aaa();
    void bbb();
    void ccc();

    Mat cam_matrix = (Mat_<double>(3,3)<<2034.4, -6.2, 663.4457, 0, 2058.11, 672.665, 0, 0, 1);
    Mat distortion_coeff = (Mat_<double>(5,1)<<-0.08441, 0.7558, -0.00717, 0.0049,0);

    Mat img;
    Mat prepare_img;
    uint enemy_color = 0;
    Rect roi_rect;
    unsigned char mode = 0;  //是否进入反陀螺模式，默认0未进入
    int target=0;            //目标装甲板0，符1
    unsigned char allow = 0; //是否允许发射，默认0允许
    double TY;
    double TP;
    int speed=1;               //弹速15m/s为3, 18m/s为2, 30m/s为1


        float deta = 0.0;


};
#endif // START_H

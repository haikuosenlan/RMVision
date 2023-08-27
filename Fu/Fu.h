#ifndef FU_H
#define FU_H
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include "Communication/serial.h"
#include <math.h>

using namespace std;
using namespace cv;

class FU_MatchSVM
{
public:
    bool R_Match(Mat & src);
private:
    Ptr<ml::SVM>R_svm = ml::SVM::load("/home/newmaker-01/SVM/R_svm.xml");
};

class FU
{
public:
    void getRwarp(Mat &R_img, Point2f vertices[]);
    void getLwarp(Mat &src_img, Mat &final_img, Point2f vertices[]);
    void findcenterR(Mat & src_img, Mat & final_img, Mat &R_img);
    void findcenterArmor(Mat & src_img, Mat & final_img);
    void predict(UsbSerial &usb_serial, Mat & img);
    void start();

    Mat cam_matrix = (Mat_<double>(3,3)<<2034.4, -6.2, 663.4457, 0, 2058.11, 672.665, 0, 0, 1);
    Mat distortion_coeff = (Mat_<double>(5,1)<<-0.08441, 0.7558, -0.00717, 0.0049,0);

    FU_MatchSVM matchsvm;
    Mat R_warp,L_warp;
    vector<RotatedRect> R_list,Armor_list;
    vector<Point2f> ArmorCenter_list;
    Point2f R_center,Armor_center;

    Point2f R_center1;
    Point2f R_center2;
    Point2f R_center3;
    Point2f R_center4;
    Point2f R_center5;
    Point2f R_center6;
    Point2f R_center7;
    Point2f R_center8;
    Point2f R_center9;

    Point2f Next_Armor_center;

    Point2f Armor_center1;
    Point2f Armor_center2;
    Point2f Armor_center3;
    Point2f Armor_center4;
    Point2f Armor_center5;
    Point2f Armor_center6;
    Point2f Armor_center7;
    Point2f Armor_center8;
    Point2f Armor_center9;

    int T = 0;
    float K = 1.0;
    float last_x = 100000.0;
    float bili = 1.0;

    double now_d_yaw=0;
    double now_d_pitch=0;

    double now_yaw=0;
    double now_pitch=0;

    double send_yaw=0;
    double send_pitch=0;

    double next_x=0,next_y=0;

    double word_x =0;
    double word_x1=0;
    double word_x2=0;
    double word_x3=0;
    double word_x4=0;
    double word_x5=0;
    double word_x6=0;
    double word_x7=0;
    double word_x8=0;

    double word_y =0;
    double word_y1=0;
    double word_y2=0;
    double word_y3=0;
    double word_y4=0;
    double word_y5=0;
    double word_y6=0;
    double word_y7=0;
    double word_y8=0;

    int state = 0;


};





#endif // FU_H

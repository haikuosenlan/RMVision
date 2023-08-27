#ifndef SOLVER_H
#define SOLVER_H
#include "Start/start.h"
#include "Communication/serial.h"
#include "Armor/Armor.h"
#include "Info/Info.h"
#include "Start/start.h"

class AngleSolver
{
public:
    AngleSolver()
    {
//        namedWindow("angle",WINDOW_AUTOSIZE);
//        cvCreateTrackbar("sp_num","angle",&sp_num,180);
        cvCreateTrackbar("dis_num","angle",&dis_num,180);
    }
    void SolveAngle(UsbSerial &usb_serial,ArmorBag &targetArmor,unsigned char &mode,unsigned char &allow,Point2f &shoot,int &shoot_t);              //结算角度
    void SolveDataProcess();       //处理信息准备发送       未写

//    Mat cam_matrix = (Mat_<double>(3,3)<<1953.12442,0,906.42745,0,1931.51178,463.95797,0,0,1);    //相机内参
//    Mat distortion_coeff = (Mat_<double>(5,1)<<-0.14520,-0.02640,0.00375,0.01146,0.00000);       //畸变系数
    Mat cam_matrix = (Mat_<double>(3,3)<<2034.4, -6.2, 663.4457, 0, 2058.11, 672.665, 0, 0, 1);//1981.3, -6.2, 684, 0, 2006.7, 504, 0, 0, 1
    Mat distortion_coeff = (Mat_<double>(5,1)<<-0.08441, 0.7558, -0.00717, 0.0049,0);//-0.1029, 0.0058, -0.0030, 0.0047,0
    std :: vector<cv::Point3f> Small_Armor_Points_3d;
    std :: vector<cv::Point3f> Big_Armor_Points_3d;

    double send_yaw = 0.0;
    double send_pitch = 0.0;
    double distance = 100.0;
    double width=120;
    double height=85;

    double now_d_yaw=0;
    double now_d_pitch=0;

    double now_yaw=0;
    double now_pitch=0;

    double next_x=0;
    double word_x =0;
    double word_x1=0;
    double word_x2=0;
    double word_x3=0;
    double word_x4=0;

    Point2f Next_Armor_center;//预测点位
    Point2f Armor_center1;
    Point2f Armor_center2;
    Point2f Armor_center3;
    Point2f Armor_center4;

    int speed=1;             //弹速15m/s为3, 18m/s为2, 30m/s为1
    int sp_num=100;
    int dis_num=100;


};
#endif // SOLVER_H

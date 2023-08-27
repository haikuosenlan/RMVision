#ifndef IMGPROCESSING_H
#define IMGPROCESSING_H
#include "Info/Info.h"
#include "Start/start.h"
#include "Armor/Armor.h"
class ImgProcessing
{
public:
    ImgProcessing()
    {
//    namedWindow("Control", WINDOW_AUTOSIZE);

    cvCreateTrackbar("B", "Control", &B, 255);
    cvCreateTrackbar("G", "Control", &G, 255);
    cvCreateTrackbar("R", "Control", &R, 255);

    cvCreateTrackbar("min1", "Control", &min1, 255);
    cvCreateTrackbar("min2", "Control", &min2, 255);
    cvCreateTrackbar("min_r", "Control", &min_r, 1000);
    cvCreateTrackbar("min_b", "Control", &min_b, 1000);
//____________________打符参数____________________________
    namedWindow("Control", WINDOW_AUTOSIZE);
    namedWindow("R", WINDOW_AUTOSIZE);
//R标和扇页分开处理以减轻R标色差带来的影响,但这会影响代码运行时长
    cvCreateTrackbar("R_R_B", "R", &R_R_B, 255);
    cvCreateTrackbar("R_R_G", "R", &R_R_G, 255);
    cvCreateTrackbar("R_R_R", "R", &R_R_R, 255);
    cvCreateTrackbar("B_R_B", "R", &B_R_B, 255);
    cvCreateTrackbar("B_R_G", "R", &B_R_G, 255);
    cvCreateTrackbar("B_R_R", "R", &B_R_R, 255);
    cvCreateTrackbar("R_R_BB", "R", &R_R_BB, 255);
    cvCreateTrackbar("R_R_GG", "R", &R_R_GG, 255);
    cvCreateTrackbar("R_R_RR", "R", &R_R_RR, 255);
    cvCreateTrackbar("B_R_BB", "R", &B_R_BB, 255);
    cvCreateTrackbar("B_R_GG", "R", &B_R_GG, 255);
    cvCreateTrackbar("B_R_RR", "R", &B_R_RR, 255);

    cvCreateTrackbar("R_FU_B", "Control", &R_FU_B, 255);
    cvCreateTrackbar("R_FU_G", "Control", &R_FU_G, 255);
    cvCreateTrackbar("R_FU_R", "Control", &R_FU_R, 255);
    cvCreateTrackbar("B_FU_B", "Control", &B_FU_B, 255);
    cvCreateTrackbar("B_FU_G", "Control", &B_FU_G, 255);
    cvCreateTrackbar("B_FU_R", "Control", &B_FU_R, 255);
    cvCreateTrackbar("R_FU_BB", "Control", &R_FU_BB, 255);
    cvCreateTrackbar("R_FU_GG", "Control", &R_FU_GG, 255);
    cvCreateTrackbar("R_FU_RR", "Control", &R_FU_RR, 255);
    cvCreateTrackbar("B_FU_BB", "Control", &B_FU_BB, 255);
    cvCreateTrackbar("B_FU_GG", "Control", &B_FU_GG, 255);
    cvCreateTrackbar("B_FU_RR", "Control", &B_FU_RR, 255);
//______________________________________________________
        enemycolor=RED;
        attackpattern=ARMOR;
    }


    Mat final_img;
    Mat R_img;
    EnemyColor enemycolor;//敌方装甲颜色
    AttackPattern attackpattern;//击打目标类别

    void Deal (Mat &img);

    vector<Mat> bgr_channels;//通道
    Mat color_img;//颜色二值化
    Mat sub_img;  //通道相减
    Mat bright_img;
    Mat element  = getStructuringElement(MORPH_RECT, Size(14,14));
    Mat element2  = getStructuringElement(MORPH_RECT, Size(3,3));

    int min1=140;
    int min2=130;
    int min_r=600;
    int min_b=560;
    int B = 25;//灰度图二值化参数 红：B=0  G=0  R=170  蓝： B=200  G=110  R=150
    int G = 200;
    int R = 25;
//------------------------------------------------------------------------
    int R_R_B = 30;
    int R_R_G = 180;
    int R_R_R = 190;
    int B_R_B = 190;
    int B_R_G = 180;
    int B_R_R = 30;

    int R_R_BB = 255;
    int R_R_GG = 255;
    int R_R_RR = 255;
    int B_R_BB = 255;
    int B_R_GG = 255;
    int B_R_RR = 255;


    int R_FU_B = 30;
    int R_FU_G = 190;
    int R_FU_R = 180;
    int B_FU_B = 180;
    int B_FU_G = 190;
    int B_FU_R = 30;

    int R_FU_BB = 255;
    int R_FU_GG = 255;
    int R_FU_RR = 255;
    int B_FU_BB = 255;
    int B_FU_GG = 255;
    int B_FU_RR = 255;
};

#endif // IMGPROCESSING_H

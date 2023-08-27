#include "imgprocessing.h"

using namespace std;
using namespace cv;

uint s = 0;
void ImgProcessing::Deal(Mat &img)
{
    if(s<3)cout << "目标是： "<< attackpattern <<  "   ImgProcessing的color:" << enemycolor << "   enemycolor" << enemycolor << endl;s++;

    if(attackpattern==FU)//打符模式
    {
        if(enemycolor==BLUE){enemycolor=RED;}else{enemycolor=BLUE;}
        enemycolor = RED;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        switch (enemycolor)
        {
        case RED:
        inRange(img,Scalar(R_FU_B,R_FU_G,R_FU_R),Scalar(R_FU_BB,R_FU_GG,R_FU_RR),final_img);
        inRange(img,Scalar(R_R_B,R_R_G,R_R_R),Scalar(R_R_BB,R_R_GG,R_R_RR),R_img);
            break;
        case BLUE:
        inRange(img,Scalar(B_FU_B,B_FU_G,B_FU_R),Scalar(B_FU_BB,B_FU_GG,B_FU_RR),final_img);
        inRange(img,Scalar(B_R_B,B_R_G,B_R_R),Scalar(B_R_BB,B_R_GG,B_R_RR),R_img);
            break;
        }
        morphologyEx(final_img,final_img,MORPH_OPEN,element2);
    }
    else//装甲板模式
    {

        split(img,bgr_channels);
        inRange(img,Scalar(B,G,R),Scalar(255,255,255),bright_img);
        morphologyEx(bright_img,bright_img,MORPH_OPEN,element2);                //imshow("bright_img",bright_img);
        switch (enemycolor)
        {
        case RED:
            subtract(bgr_channels[2],(min_r*0.001)*bgr_channels[1],sub_img);
            threshold(sub_img,sub_img,min1,255,THRESH_BINARY);
//            inRange(img,Scalar(R_R_B,R_R_G,R_R_R),Scalar(R_R_BB,R_R_GG,R_R_RR),sub_img);
            dilate(sub_img,sub_img,element);                                    //imshow("red_img",sub_img);
            final_img=sub_img & bright_img;
            break;
        case BLUE:
            subtract(bgr_channels[0],(min_b*0.001)*bgr_channels[1],sub_img);
            threshold(sub_img,sub_img,min2,255,THRESH_BINARY);
//            inRange(img,Scalar(B_R_B,B_R_G,B_R_R),Scalar(B_R_BB,B_R_GG,B_R_RR),sub_img);
            dilate(sub_img,sub_img,element);                                    //imshow("blue_img",sub_img);
            final_img=sub_img & bright_img;
            break;
        }

    }

//    dilate(final_img,final_img,element2);
//    imshow("R_img",R_img);
//    imshow("final",final_img);
}


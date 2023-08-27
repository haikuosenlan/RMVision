#include "Fu.h"

void FU::getRwarp(Mat &R_img, Point2f vertices[4])
{

    Mat rotation;
    Point2f dst_points[4];
    dst_points[0] = Point2f(0.0,    0.0  );
    dst_points[1] = Point2f(20.0,   0.0  );
    dst_points[2] = Point2f(20.0,   20.0 );
    dst_points[3] = Point2f(0.0,    20.0 );
//    cout << vertices[0]<< endl;cout << vertices[1]<< endl;cout << vertices[2]<< endl;cout << vertices[3]<< endl;
    rotation = getPerspectiveTransform(vertices,dst_points);//透视方式（最好写透视变换矩阵，才不显的low）
    warpPerspective(R_img,R_warp,rotation,Size(20,20),INTER_LINEAR,BORDER_CONSTANT);
//    imshow("R_warp",R_warp);
}

void FU::getLwarp(Mat &src_img,Mat &final_img, Point2f L_vertices[4])
{
    state =1;//保存图像作为svm样本的标志位用
    Mat rotation;
    Point2f dst_points[4];
    dst_points[3] = Point2f(20.0,  100.0);
    dst_points[2] = Point2f(0.0,   100.0);
    dst_points[1] = Point2f(20.0,   0.0 );
    dst_points[0] = Point2f(0.0,    0.0 );
    rotation = getPerspectiveTransform(L_vertices,dst_points);//透视方式（最好写透视变换矩阵，才不显的low）
    warpPerspective(final_img,L_warp,rotation,Size(20,100),INTER_LINEAR,BORDER_CONSTANT);
    morphologyEx(L_warp,L_warp,MORPH_OPEN, getStructuringElement(MORPH_RECT, Size(15,15)));
//    imshow("L_warp",L_warp);
//    circle(src_img,L_vertices[0],1,Scalar(5,5,255),2,8);      line(src_img,L_vertices[0],L_vertices[1],Scalar(200,23,255),2);
//    circle(src_img,L_vertices[1],2,Scalar(5,5,255),2,8);      line(src_img,L_vertices[1],L_vertices[3],Scalar(200,23,255),2);
//    circle(src_img,L_vertices[2],3,Scalar(5,5,255),2,8);      line(src_img,L_vertices[2],L_vertices[0],Scalar(200,23,255),2);
//    circle(src_img,L_vertices[3],4,Scalar(5,5,255),2,8);      line(src_img,L_vertices[3],L_vertices[2],Scalar(200,23,255),2);
}




void FU::findcenterR(Mat & src_img, Mat & final_img, Mat & R_img)
{
    R_list.clear();
    vector<vector<Point>> R_contours;  //候选R标轮廓
    RotatedRect R_rect;
    findContours(R_img,R_contours,RETR_LIST,CHAIN_APPROX_SIMPLE);//寻找轮廓
    for(uint i = 0; i < R_contours.size();i++)
    {
        Point2f vertices[4];
        if(R_contours[i].size() < 6)  continue;
//        if(contourArea(R_contours[i]) > 400.0 || contourArea(R_contours[i]) < 200) continue;  //面积筛选
        if(contourArea(R_contours[i]) > 400.0 || contourArea(R_contours[i]) < 150) continue;  //面积筛选

        R_rect = fitEllipse(R_contours[i]); //创建临时旋转矩形
        if (R_rect.size.width/R_rect.size.height < 1.5 && R_rect.size.width/R_rect.size.height > 0.5)//比例筛选
        {
            vertices[0].x=R_rect.center.x-0.8*R_rect.size.width;vertices[0].y=R_rect.center.y-0.8*R_rect.size.width;
            vertices[1].x=R_rect.center.x+0.8*R_rect.size.width;vertices[1].y=R_rect.center.y-0.8*R_rect.size.width;
            vertices[2].x=R_rect.center.x+0.8*R_rect.size.width;vertices[2].y=R_rect.center.y+0.8*R_rect.size.width;
            vertices[3].x=R_rect.center.x-0.8*R_rect.size.width;vertices[3].y=R_rect.center.y+0.8*R_rect.size.width;
            getRwarp(R_img,vertices);//裁减R标区域
            if(R_warp.size != nullptr)
            {
                if(matchsvm.R_Match(R_warp))
                {
                    R_list.emplace_back(R_rect);
//                    ellipse(src_img,R_rect,Scalar(255,155,0),2,8);//椭圆画出包围的R标
                    circle(src_img,R_list[0].center,3,Scalar(255,180,0),3,8,0);//圈出R_list第一个的中心点
                }
            }
        }
    }
}




void FU::findcenterArmor(Mat & src_img, Mat & final_img)
{
    Armor_list.clear();//及时清理，否则程序会越跑越慢，甚至卡死
    ArmorCenter_list.clear();
    Armor_center = Point2f();

    vector<vector<Point>> armor_contours; //候选装甲板轮廓
    RotatedRect armor_rect;
    float forecast_r = 0;
    findContours(final_img,armor_contours,RETR_LIST,CHAIN_APPROX_SIMPLE);//寻找轮廓
    for(uint i = 0; i < armor_contours.size();i++)
    {
        if(armor_contours[i].size() < 6)  continue;
        if(contourArea(armor_contours[i]) > 7*R_list[0].size.area() || contourArea(armor_contours[i]) < R_list[0].size.area() )continue;  //面积筛选
        armor_rect = fitEllipse(armor_contours[i]); //创建临时旋转矩形
        if (armor_rect.size.width/armor_rect.size.height < 0.25 || armor_rect.size.width/armor_rect.size.height >0.77)  continue;  //长宽比筛选
        if(R_list.size() != 0)
        {
            float dx = armor_rect.center.x - (R_center.x);
            float dy = armor_rect.center.y - (R_center.y);
            forecast_r =  sqrt(dx * dx + dy * dy);
            if(forecast_r > 12 * R_list[0].size.height  || forecast_r <  3 * R_list[0].size.width)  continue;//与R标距离筛选
            circle(src_img,R_list[0].center,12 * R_list[0].size.height,Scalar(255,255,255),1,8);
            circle(src_img,R_list[0].center,3 * R_list[0].size.height,Scalar(255,0,255),1,8);
            ellipse(src_img,armor_rect,Scalar(0,255,15),2,8);
            Armor_list.emplace_back(armor_rect);
        }
    }
    for (uint i = 0; i < Armor_list.size(); i++)
      {
        for (uint j = i + 1; j <  Armor_list.size(); j++)
        {
         RotatedRect &l_rect = Armor_list[i];
         RotatedRect &r_rect = Armor_list[j];
//两边框长度差
         float H_diff = abs(l_rect.size.height-r_rect.size.height);
         float H_diff_proportion = H_diff/max(l_rect.size.height,r_rect.size.height);            //cout<<"number"<<i<<"&"<<j<<"&       "<<H_diff_proportion<<endl;
         if(H_diff_proportion>0.25)continue;
//边框平行度
         float light_angle_diff = abs(l_rect.angle-r_rect.angle);                                //cout<<"number"<<i<<"&"<<j<<"&       "<<light_angle_diff<<endl;
         if(light_angle_diff>10 & light_angle_diff<170)continue;
//设置扇页中心点合集
         Point armorcenter((r_rect.center.x + l_rect.center.x)/2,(r_rect.center.y + l_rect.center.y)/2);
         double dx = armorcenter.x - (R_center.x);
         double dy = armorcenter.y - (R_center.y);
         forecast_r =  sqrt(dx * dx + dy * dy);
         if(forecast_r > 12 * R_list[0].size.height  || forecast_r <  3 * R_list[0].size.width)  continue;//与R标距离筛选
         ArmorCenter_list.emplace_back(armorcenter);
//             Point armor1((r_rect.center.x + l_rect.center.x)/2,(r_rect.center.y + l_rect.center.y)/2-40);//重力补偿后的目标中心
//             circle(src_img,armorcenter,5,Scalar(255,255,0),2,8,0); //画出过筛选的所有的目标中心
//             circle(img,armor1,5,Scalar(120,190,150),2,8,0); //重力补偿后的目标中心
//             circle(src_img,R,8 * R_list[0].size.width,Scalar(255,255,255),2,8,0);//显示与R标距离范围
//         break;
        }
      }

//设置目标扇页中心点
    for(uint i = 0; i < ArmorCenter_list.size(); i++)
    {
        Point2f L_vertices[4];
        double dis = sqrt((ArmorCenter_list[i].x-R_center.x)*(ArmorCenter_list[i].x-R_center.x)+(ArmorCenter_list[i].y-R_center.y)*(ArmorCenter_list[i].y-R_center.y));
        double cos = (ArmorCenter_list[i].x-R_center.x)/dis;
        double sin = (ArmorCenter_list[i].y-R_center.y)/dis;
        L_vertices[0].x = R_center.x - 0.025*dis*sin + 0.3*(ArmorCenter_list[i].x-R_center.x);              L_vertices[0].y = R_center.y + 0.025*dis*cos + 0.3*(ArmorCenter_list[i].y-R_center.y);
        L_vertices[1].x = R_center.x + 0.025*dis*sin + 0.3*(ArmorCenter_list[i].x-R_center.x);              L_vertices[1].y = R_center.y - 0.025*dis*cos + 0.3*(ArmorCenter_list[i].y-R_center.y);
        L_vertices[2].x = ArmorCenter_list[i].x - 0.025*dis*sin - 0.3*(ArmorCenter_list[i].x-R_center.x);   L_vertices[2].y = ArmorCenter_list[i].y + 0.025*dis*cos - 0.3*(ArmorCenter_list[i].y-R_center.y);
        L_vertices[3].x = ArmorCenter_list[i].x + 0.025*dis*sin - 0.3*(ArmorCenter_list[i].x-R_center.x);   L_vertices[3].y = ArmorCenter_list[i].y - 0.025*dis*cos - 0.3*(ArmorCenter_list[i].y-R_center.y);
        getLwarp(src_img,final_img,L_vertices);//裁减流动灯条区域
        if(L_warp.size != nullptr)
        {
            if((uint)L_warp.at<uchar>(10,50)<130)//判断该点像素值大小
            {
                Armor_center = ArmorCenter_list[i];
            }
        }
    }
    circle(src_img,Armor_center,2,Scalar(0,0,255),5,8);//画出目标扇页中心点
}



bool FU_MatchSVM ::R_Match(Mat & R_warp)
{

//    resize(R_warp,R_warp,Size(20,20));
//    cvtColor(R_warp,R_warp,COLOR_BGR2GRAY);//以下为作二值化处理
    threshold(R_warp,R_warp,20,255,THRESH_BINARY_INV);
//    imshow("R_warp",R_warp);
    Mat p = R_warp.reshape(1,1);
    p.convertTo(p,CV_32FC1);
    int response = (int)R_svm->predict(p);
//cout << "response" << response << endl;
    if(response == 0){return false;}
    else{return true;}
}








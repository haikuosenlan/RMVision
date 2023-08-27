
#include "Solver.h"


void AngleSolver :: SolveAngle(UsbSerial &usb_serial, ArmorBag &targetArmor, unsigned char &mode, unsigned char &allow, Point2f &shoot, int &shoot_t)
{

    Armor_center4 = Armor_center3;Armor_center3 = Armor_center2;Armor_center2 = Armor_center1;Armor_center1 = targetArmor.armor_center;
    Mat r,tr,rot,trans,ttrans;    vector <Point2f> ccc;
    Next_Armor_center = targetArmor.armor_center;
    switch (targetArmor.armor_size)
    {
    case SMALL_ARMOR :
//        cout << "small_armor" << endl;
        Small_Armor_Points_3d.push_back(Point3f(- small_x,  small_y,0));
        Small_Armor_Points_3d.push_back(Point3f(  small_x,  small_y,0));
        Small_Armor_Points_3d.push_back(Point3f(  small_x, -small_y,0));
        Small_Armor_Points_3d.push_back(Point3f(- small_x, -small_y,0));
        solvePnP(Small_Armor_Points_3d , targetArmor.light_Vertices , cam_matrix , distortion_coeff , r , trans);
        break;
    case BIG_ARMOR :
//        cout << "big_armor" << endl;
        Big_Armor_Points_3d.push_back(Point3f(- big_x,  big_y,0));
        Big_Armor_Points_3d.push_back(Point3f(  big_x,  big_y,0));
        Big_Armor_Points_3d.push_back(Point3f(  big_x, -big_y,0));
        Big_Armor_Points_3d.push_back(Point3f(- big_x, -big_y,0));
        solvePnP(Big_Armor_Points_3d , targetArmor.light_Vertices , cam_matrix , distortion_coeff , r , trans);
        break;
    }
    Small_Armor_Points_3d.clear();//及时清理，否则程序会越跑越慢，甚至卡死
    Big_Armor_Points_3d.clear();

    double x = trans.at<double>(0, 0);
    double y = trans.at<double>(1, 0);
    double z = trans.at<double>(2, 0);
    distance = sqrt(x*x + y*y + z*z);
    double tan_pitch = y / sqrt(x*x + z*z);
    double tan_yaw = x / z;
    now_d_pitch = -atan(tan_pitch) * 180 / CV_PI;
    now_d_yaw = atan(tan_yaw) * 180 / CV_PI;
    send_yaw = now_d_yaw ;
    send_pitch = now_d_pitch;


//---------------------------------------------------------------------------------------------------
if(shoot_t == 0 )//未进入反陀螺模式
{
    if(Next_Armor_center.x != 0)//相机坐标预测点
    {
    std :: vector<cv::Point3f> SHOOT;
    SHOOT.push_back(Point3f(- 2,  2,0));
    SHOOT.push_back(Point3f(  2,  2,0));
    SHOOT.push_back(Point3f(  2, -2,0));
    SHOOT.push_back(Point3f(- 2, -2,0));
    Point2f a (Next_Armor_center.x-100,Next_Armor_center.y-100);
    Point2f b (Next_Armor_center.x+100,Next_Armor_center.y-100);
    Point2f c (Next_Armor_center.x+100,Next_Armor_center.y+100);
    Point2f d (Next_Armor_center.x-100,Next_Armor_center.y+100);
    ccc.emplace_back(a);ccc.emplace_back(b);ccc.emplace_back(c);ccc.emplace_back(d);
    solvePnP(SHOOT , ccc , cam_matrix , distortion_coeff , tr , ttrans);

    double qqx = ttrans.at<double>(0, 0);
    double qqy = ttrans.at<double>(1, 0);
    double qqz = ttrans.at<double>(2, 0);
    double qtan_pitch = qqy / sqrt(qqx * qqx + qqz * qqz);
    double qtan_yaw = qqx / qqz;
    now_d_pitch = -atan(qtan_pitch) * 180 / CV_PI;
    now_d_yaw = atan(qtan_yaw) * 180 / CV_PI;
    }
    send_yaw = now_d_yaw;
    send_pitch = now_d_pitch;
//-----------------------------世界坐标的角度预测---------------------------------------
    word_x = now_yaw - now_d_yaw;

    word_x4 = word_x3;word_x3 = word_x2;word_x2 = word_x1;word_x1 = word_x;
    next_x = 0;
    if(word_x4 == 0)
    {
        if(word_x2 != 0)
        {    if(abs(word_x1-word_x2)>2.0)
            {word_x1 = word_x2 = word_x3 = word_x4 = 0;}
        }
    }
    else
    {
        if(abs(word_x1-word_x2)<2.0)
        {
            double yuce_k =0;
            if(speed == 1)
            {
                yuce_k = distance*0.01*1.35;
            }
            else if (speed == 2)
            {
                yuce_k = distance*0.01*1.6;
            }
            else if (speed == 3)
            {
                yuce_k = distance*0.01*1.75;
            }
            if(distance >550){yuce_k = -2;}
            else if (distance > 450 && distance <=550) {yuce_k = -1;}
            else if (distance > 350 && distance <=450) {yuce_k = -1;}
            next_x=word_x1
                    +(word_x1-word_x2)*(2+yuce_k)
                    +(word_x2-word_x3)*(2+yuce_k)
                    +(word_x3-word_x4)*(2+yuce_k);
        }
        else
        {word_x1 = word_x2 = word_x3 = word_x4 = 0;}
    }

    if(next_x != 0)
    {
//        cout<<"yuce"<<endl;
        send_yaw = now_yaw - next_x;send_pitch = 1.0*now_d_pitch;
    }
    else
    {
//        cout<<"wu"<<endl;
        send_yaw = 1.0*now_d_yaw;send_pitch = 1.0*now_d_pitch;
    }

//    if(abs(last_word_x - word_x)>0.6){cout << last_word_x - word_x << endl;}
//    cout << now_yaw <<"    " << now_d_yaw <<"    " << word_x <<  endl;

//    if(abs(word_x-last_word_x)>0.5){cout << word_x-last_word_x << endl;}
//    cout << word_x << endl;
//---------------------------------------------------------------------------

}
else//进入反陀螺模式
{
    std :: vector<cv::Point3f> SHOOT;
    SHOOT.push_back(Point3f(- 2,  2,0));
    SHOOT.push_back(Point3f(  2,  2,0));
    SHOOT.push_back(Point3f(  2, -2,0));
    SHOOT.push_back(Point3f(- 2, -2,0));
    Point2f a (shoot.x-100,shoot.y-100);
    Point2f b (shoot.x+100,shoot.y-100);
    Point2f c (shoot.x+100,shoot.y+100);
    Point2f d (shoot.x-100,shoot.y+100);
    ccc.emplace_back(a);ccc.emplace_back(b);ccc.emplace_back(c);ccc.emplace_back(d);
    solvePnP(SHOOT , ccc , cam_matrix , distortion_coeff , tr , ttrans);

    double qqx = ttrans.at<double>(0, 0);
    double qqy = ttrans.at<double>(1, 0);
    double qqz = ttrans.at<double>(2, 0);
    double qtan_pitch = qqy / sqrt(qqx * qqx + qqz * qqz);
    double qtan_yaw = qqx / qqz;
    now_d_pitch = -atan(qtan_pitch) * 180 / CV_PI;
    now_d_yaw = atan(qtan_yaw) * 180 / CV_PI;
    send_yaw = now_d_yaw;send_pitch = now_d_pitch;
}
//_____________________________________________pitch距离补偿______________________________________________
    send_pitch+=-1.5;//初始补偿
    send_yaw +=0.4;//初始补偿
    double dis_k=0;
    if(speed == 1)
    {
        dis_k = -0.01*(distance-100)*65*0.01;
        if(distance<450){dis_k += 0.01*(distance-100)*8*0.01;}
        else {dis_k += 0.01*(distance-100)*45*0.01;}
    }
    else if (speed == 2)
    {
        send_yaw +=0.15;
        dis_k = 0.01*(distance-100)*100*0.01;
    }
    else if (speed == 3)
    {
        send_yaw+=0.15;
        dis_k = 0.01*(distance-100)*120*0.01;
//        dis_k += dis_k*0.03;
    }
//    dis_k += 0.01*(distance-100)*dis_num*0.01;
    send_pitch+=dis_k;
//    send_pitch+=speed*sp_k;//根据弹速和距离的补偿
//    cout << dis_k << "    " <<  speed*sp_k << endl;
    if(abs(send_yaw)>20){cout << "离谱！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！"<< endl;send_yaw =  0;}//{send_yaw=0;send_pitch=0;}
    if(abs(send_pitch)>20){cout << "离谱！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！"<< endl;send_pitch =  0;}
    VisionData   vdata = {{(float)send_yaw},{(float)send_pitch},{(float)distance},mode,allow};
//    VisionData   vdata = {{0},{0},{0},mode,allow};
    usb_serial.TransformData(vdata);usb_serial.send();
//    cout << "yaw  " << send_yaw << "   //pitch  " << send_pitch << "    //distance  " << distance << endl;
}

#include "start.h"
#include "ImgProcessing/imgprocessing.h"
#include "CameraDriver/cameraapi.h"
#include  "CameraDriver/mvvideocapture.h"
#include "Communication/serial.h"
#include "Armor/Armor.h"
#include "Solver/Solver.h"
#include "Fu/Fu.h"

static UsbSerial usb_serial;

//void Start::aaa()
//{
//    while (1)
//    {cout << "111111111111" << endl;}
//}
//void Start::bbb()
//{
//    while (1)
//    {cout << "BBBBBBBBBBBB" << endl;}
//}
//void Start::ccc()
//{
//    while (1)
//    {cout << "333333333333" << endl;}
//}
void Start::TargetProcess()
{

}

void Start::ImgProcess()
{
//--------------------------------------------------------------------------------------------

    if(-1 == MVVideoCapture::Init())
    {
        std::cout << "MVVideoCapture ERROR!!!" << std::endl;
  //      return;
    }

    MVVideoCapture::Play();
//    MVVideoCapture::SetExposureTime(true, 10);
//    MVVideoCapture::SetLargeResolution(true);
//    std::cout << "MVVideoCapture Finished!" << std::endl;
//--------------------------------------------------------------------------------------------
    ImgProcessing imgprocessing;
    ArmorDetector armordetector;
    AngleSolver anglesolver;
    class FU fu;
    double time = 0.0;
    int TT=0;//获取云台计数
    int TTT=0;//相机掉线次数
    double start_time; start_time = getCPUTickCount();
//——————————————————————————————————保存视频————————————————————————————————————————
//    image = camera.GetFrame();
//    VideoWriter writer;
//    int codec = VideoWriter::fourcc('M','J','P','G');
//    double fps = 100.0;
//    string filename = "/home/newmaker-01/视频/game.avi";
//    writer.open(filename,codec,fps,image.size());
//————————————————————————————————————————————————————————————————————————————-

    while (1)
        {
//            if(1000*time >100){TTT++;cout << "刚刚相机掉线！已掉线 " << TTT << "次 掉线时长 " << 1000*time <<"ms"<< endl;}//相机掉线
//            cout << 11111111111111 << endl;
            MVVideoCapture::GetFrame(img);//耗时10ms左右
//            cout << 22222222222222 << endl;
//            if(img.empty()){cout << "111111111111111111111111111" << endl;continue;}

            armordetector.speed = anglesolver.speed = speed;
//————————————————————————————————保存视频————————————————————————————
//            writer.write(image);
//            writer<<image;
//————————————————————————————————————————————————————————————————————
//_______________________________________设置参数并图像预处理____________________________________________________
            if(enemy_color == 0){imgprocessing.enemycolor = RED;}else {imgprocessing.enemycolor = BLUE;}
            if(target == 1 || target == 0){imgprocessing.attackpattern = ARMOR;}else {imgprocessing.attackpattern = FU;}
            imgprocessing.Deal(img);
            prepare_img = imgprocessing.final_img;
//____________________________________________________________________________________________________________
//_________________________________________根据目标开始自瞄______________________________________________________
//+++++++++++++++++++++++++++++++++++++++++++目标为装甲板+++++++++++++++++++++++++++++++++++++++++++++++++++++//
if(target == 1 || target == 0)
{
    armordetector.detect(img,prepare_img);//装甲板识别函数

    if(armordetector.targetArmor.score != 0)//有击打目标
    {
        anglesolver.now_yaw =TY;anglesolver.now_pitch = TP;//获取当前云台陀螺仪角度
        anglesolver.SolveAngle(usb_serial,armordetector.targetArmor,mode,allow,armordetector.shoot,armordetector.shoot_t);
    }
    else
    {
        VisionData   vdata = {{0},{0},{0},0,0};
        usb_serial.TransformData(vdata);usb_serial.send();
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++目标为符+++++++++++++++++++++++++++++++++++++++++++++++++++++++==//
else if(target==2)
{
    waitKey(12);
//    double end; end = getCPUTickCount();//设置结束计时
//    double t = (end-start_time)/getTickFrequency();
//    int delta = 0.2*(60 - 1000*t);if(delta>0){waitKey(delta);cout << delta << endl;}

    fu.now_yaw =TY;fu.now_pitch = TP;//获取当前云台陀螺仪角度
    fu.findcenterR(img,imgprocessing.final_img,imgprocessing.R_img);
    if(fu.R_list.size() != 0)//找到R标
    {
        fu.R_center = fu.R_list[0].center;
        fu.findcenterArmor(img,prepare_img);
        if(fu.Armor_center.x != 0)
        {
            if(abs(fu.Armor_center.x - fu.R_center.x - deta)>3){/*cout << fu.Armor_center.x - fu.R_center.x - deta << endl;*/}
            deta = fu.Armor_center.x - fu.R_center.x;
            fu.predict(usb_serial,img);//预测
        }
        else
        {
            VisionData   vdata = {{0},{0},{0},0,0};
            usb_serial.TransformData(vdata);usb_serial.send();
        }
    }
    else//未找到R标
    {
        fu.Next_Armor_center = Point2f();fu.R_center = Point2f();
//        cout << "未找到R标" <<endl;
        VisionData   vdata = {{0},{0},{0},0,0};
        usb_serial.TransformData(vdata);usb_serial.send();
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++不识别目标+++++++++++++++++++++++++++++++++++++++++++++++++++++//
else
{
    VisionData   vdata = {{0},{0},{0},0,0};
    usb_serial.TransformData(vdata);usb_serial.send();
}
//____________________________________________其他处理___________________________________________________________

//    line(img,Point2f(0.5*img.cols,0),Point2f(0.5*img.cols,img.rows),Scalar(50,50,50),1);//图像中间线
//    circle(img,anglesolver.Next_Armor_center,8,Scalar(0,200,255),2,8);//armor预测点位置
//    circle(img,fu.Next_Armor_center,8,Scalar(0,200,255),2,8);//fu预测点位置
//--------------------------------------------计时------------------------------------------------------------
            double end_time; end_time = getCPUTickCount();//设置结束计时
            time = (end_time-start_time)/getTickFrequency();
            char string[10],dis[10];
            sprintf(string,"%.1f",1000*time);
            sprintf(dis,"%f",anglesolver.distance);
            std::string fpsString("delay:"),unit("ms");
            fpsString += string;fpsString += unit;
            putText(img,fpsString,Point(50,50), 2,1,Scalar(0,0,255));
            putText(img,dis,Point(1000,50), 2,1,Scalar(0,0,255));
            start_time = getCPUTickCount();//设置开始计时

            cout << fpsString << endl;
//————————————————————————————————————————————————————————————————————————————————————————————————————————————————
//            imshow("prepare_img", prepare_img);
//             imshow("Infantry img", img);//耗时10ms左右
            waitKey(1);
//            if(waitKey(0)==' ')//设置合适
//                break;
        }
}

void Start::Recive()
{
    usb_serial.SerialInit();
    double  rec_data[8];
    while (true)
    {
        usb_serial.SerialRecData(rec_data);
        enemy_color = (int)rec_data[0];
        target = (int)rec_data[1];
//        target = 2;
        TY = rec_data[2];
        TP = rec_data[3];
        speed = (int)rec_data[4];
//        cout <<enemy_color << "  " << target << "  "  << TY << "   " << TP << "  " << speed << endl;
    }
}



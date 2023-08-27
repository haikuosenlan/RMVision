#include "Fu.h"

void FU::predict(UsbSerial &usb_serial, Mat & img)
{
//    Armor_center5 = Armor_center4;       R_center5 = R_center4;
//    Armor_center4 = Armor_center3;       R_center4 = R_center3;
//    Armor_center3 = Armor_center2;       R_center3 = R_center2;
//    Armor_center2 = Armor_center1;       R_center2 = R_center1;
//    Armor_center1 = Armor_center;        R_center1 = R_center;
//    Next_Armor_center = Point2f();

//    if(Armor_center5.x == 0)
//    {
//        if(Armor_center2.x != 0)
//        {
//            if(abs((Armor_center2.x-R_center2.x)-(Armor_center1.x-R_center2.x))+abs((Armor_center2.y-R_center2.y)-(Armor_center1.y-R_center2.y))>3*R_list[0].size.width)
//            {
////                cout << "重置啦"<< endl;
//                R_center1 = Armor_center1 = Point2f();
//                R_center2 = Armor_center2 = Point2f();
//                R_center3 = Armor_center3 = Point2f();
//                R_center4 = Armor_center4 = Point2f();
//                R_center5 = Armor_center5 = Point2f();
//            }
//            else
//            {/*cout << "未准备好" << endl;*/}
//        }
//        else
//        {/*cout << "未准备好" << endl;*/}
//    }
//    else
//    {
//        if(abs((Armor_center2.x-R_center2.x)-(Armor_center1.x-R_center1.x))+abs((Armor_center2.y-R_center2.y)-(Armor_center1.y-R_center1.y))<3*R_list[0].size.width)
//        {
////           cout << bili << endl;
//            if(T<5)
//            {
//                Next_Armor_center.x=Armor_center1.x
//                        +((Armor_center1.x-R_center1.x)-(Armor_center2.x-R_center2.x))*bili*5
//                        +((Armor_center2.x-R_center2.x)-(Armor_center3.x-R_center3.x))*bili*5
//                        +((Armor_center3.x-R_center3.x)-(Armor_center4.x-R_center4.x))*bili*5
//                        +((Armor_center4.x-R_center4.x)-(Armor_center5.x-R_center5.x))*bili*5;
//            Next_Armor_center.y=Armor_center1.y
//                                +((Armor_center1.y-R_center1.y)-(Armor_center2.y-R_center2.y))*bili*5
//                                +((Armor_center2.y-R_center2.y)-(Armor_center3.y-R_center3.y))*bili*5
//                                +((Armor_center3.y-R_center3.y)-(Armor_center4.y-R_center4.y))*bili*5
//                                +((Armor_center4.y-R_center4.y)-(Armor_center5.y-R_center5.y))*bili*5;
////                Next_Armor_center.y = R_center.y;
//            //            cout << "准备好了" << endl;
//                circle(src_img,Next_Armor_center,1,Scalar(255,255,255),5,8);
//                line(src_img,Point2f(Next_Armor_center.x,0),Point2f(Next_Armor_center.x,src_img.rows),Scalar(250,250,250),1);
//                line(src_img,Point2f(0,Next_Armor_center.y),Point2f(src_img.cols,Next_Armor_center.y),Scalar(250,250,250),1);

//                if(T == 0)
//                {
//                    last_x = (Armor_center1.x-R_center1.x)-(Armor_center5.x-R_center5.x);
//                }
//            }
//            else
//            {
//                T=0;
//                bili = abs((Armor_center1.x-R_center1.x)-(Armor_center5.x-R_center5.x)/last_x);
//                bili*=0.008;
//                Next_Armor_center.x=Armor_center1.x
//                                    +((Armor_center1.x-R_center1.x)-(Armor_center2.x-R_center2.x))*bili*5
//                                    +((Armor_center2.x-R_center2.x)-(Armor_center3.x-R_center3.x))*bili*5
//                                    +((Armor_center3.x-R_center3.x)-(Armor_center4.x-R_center4.x))*bili*5
//                                    +((Armor_center4.x-R_center4.x)-(Armor_center5.x-R_center5.x))*bili*5;
//                Next_Armor_center.y=Armor_center1.y
//                                    +((Armor_center1.y-R_center1.y)-(Armor_center2.y-R_center2.y))*bili*5
//                                    +((Armor_center2.y-R_center2.y)-(Armor_center3.y-R_center3.y))*bili*5
//                                    +((Armor_center3.y-R_center3.y)-(Armor_center4.y-R_center4.y))*bili*5
//                                    +((Armor_center4.y-R_center4.y)-(Armor_center5.y-R_center5.y))*bili*5;
////                Next_Armor_center.y = R_center.y;
//    //            cout << "准备好了" << endl;
//                circle(src_img,Next_Armor_center,1,Scalar(255,255,255),5,8);
//                 line(src_img,Point2f(Next_Armor_center.x,0),Point2f(Next_Armor_center.x,src_img.rows),Scalar(250,250,250),1);
//                line(src_img,Point2f(0,Next_Armor_center.y),Point2f(src_img.cols,Next_Armor_center.y),Scalar(250,250,250),1);
//            }
//            T ++ ;
//        }
//        else
//        {
////            cout << "有armor_center5也重置啦" << endl;
//            R_center1 = Armor_center1 = Point2f();
//            R_center2 = Armor_center2 = Point2f();
//            R_center3 = Armor_center3 = Point2f();
//            R_center4 = Armor_center4 = Point2f();
//            R_center5 = Armor_center5 = Point2f();
//        }
//    }
//    if(Next_Armor_center.x != 0)
//    {
//        Mat r,rot,trans;
//        vector <Point2f> ccc;
//        std :: vector<cv::Point3f> SHOOT;
//        SHOOT.push_back(Point3f(- 2,  2,0));
//        SHOOT.push_back(Point3f(  2,  2,0));
//        SHOOT.push_back(Point3f(  2, -2,0));
//        SHOOT.push_back(Point3f(- 2, -2,0));
//        Point2f a (Next_Armor_center.x-100,Next_Armor_center.y-100);
//        Point2f b (Next_Armor_center.x+100,Next_Armor_center.y-100);
//        Point2f c (Next_Armor_center.x+100,Next_Armor_center.y+100);
//        Point2f d (Next_Armor_center.x-100,Next_Armor_center.y+100);
//    //    Point2f a (Armor_center.x-100,Armor_center.y-100);
//    //    Point2f b (Armor_center.x+100,Armor_center.y-100);
//    //    Point2f c (Armor_center.x+100,Armor_center.y+100);
//    //    Point2f d (Armor_center.x-100,Armor_center.y+100);
//        ccc.emplace_back(a);ccc.emplace_back(b);ccc.emplace_back(c);ccc.emplace_back(d);
//        solvePnP(SHOOT , ccc , cam_matrix , distortion_coeff , r , trans);

//        double qqx = trans.at<double>(0, 0);
//        double qqy = trans.at<double>(1, 0);
//        double qqz = trans.at<double>(2, 0);
//        double qtan_pitch = qqy / sqrt(qqx * qqx + qqz * qqz);
//        double qtan_yaw = qqx / qqz;
//        double pitch = -atan(qtan_pitch) * 180 / CV_PI;
//        double yaw   = atan(qtan_yaw) * 180 / CV_PI;
//        double send_pitch = 1*pitch;
//        double send_yaw   = 1*yaw;

//        if(abs(send_yaw) > 18){cout << "yaw离谱！！！！！！！！！！！！！！！！！！！！！！！！！！" << endl;send_yaw = 0;}
//        if(abs(send_pitch) > 18){cout << "pitch离谱！！！！！！！！！！！！！！！！！！！！！！！！！！" << endl;send_pitch = 0;}
//        cout << send_yaw << endl;
//        VisionData   vdata = {{(float)send_yaw},{(float)send_pitch},{0},0,0};
//        usb_serial.TransformData(vdata);usb_serial.send();

//    }
//    else
//    {
//        VisionData   vdata = {{0},{0},{0},0,0};
//        usb_serial.TransformData(vdata);usb_serial.send();
//    }




//-------------------------------------------------------------------------------------------------------------

//    Mat r,rot,trans;
//    vector <Point2f> ccc;
//    std :: vector<cv::Point3f> SHOOT;
//    SHOOT.push_back(Point3f(- 2,  2,0));
//    SHOOT.push_back(Point3f(  2,  2,0));
//    SHOOT.push_back(Point3f(  2, -2,0));
//    SHOOT.push_back(Point3f(- 2, -2,0));
////        Point2f a (Next_Armor_center.x-100,Next_Armor_center.y-100);
////        Point2f b (Next_Armor_center.x+100,Next_Armor_center.y-100);
////        Point2f c (Next_Armor_center.x+100,Next_Armor_center.y+100);
////        Point2f d (Next_Armor_center.x-100,Next_Armor_center.y+100);
//    Point2f a (Armor_center.x-100,Armor_center.y-100);
//    Point2f b (Armor_center.x+100,Armor_center.y-100);
//    Point2f c (Armor_center.x+100,Armor_center.y+100);
//    Point2f d (Armor_center.x-100,Armor_center.y+100);
//    ccc.emplace_back(a);ccc.emplace_back(b);ccc.emplace_back(c);ccc.emplace_back(d);
//    solvePnP(SHOOT , ccc , cam_matrix , distortion_coeff , r , trans);

//    double qqx = trans.at<double>(0, 0);
//    double qqy = trans.at<double>(1, 0);
//    double qqz = trans.at<double>(2, 0);
//    double qtan_pitch = qqy / sqrt(qqx * qqx + qqz * qqz);
//    double qtan_yaw = qqx / qqz;
//    double pitch = -atan(qtan_pitch) * 180 / CV_PI;
//    double yaw   = atan(qtan_yaw) * 180 / CV_PI;
//    double send_pitch = 1*pitch;
//    double send_yaw   = 1*yaw;
//        cout << "初始  " << send_pitch << "         ";


//    word_x = now_yaw - yaw;
//    word_y = now_pitch - pitch;
//    word_x7 = word_x6;word_x6 = word_x5;word_x5 = word_x4;word_x4 = word_x3;word_x3 = word_x2;word_x2 = word_x1;word_x1 = word_x;
//    word_y7 = word_y6;word_y6 = word_y5;word_y5 = word_y4;word_y4 = word_y3;word_y3 = word_y2;word_y2 = word_y1;word_y1 = word_y;
//    next_x = next_y = 0;

//    if(word_x7 == 0)
//    {
//        if(word_x2 != 0)
//        {    if(abs(word_x1-word_x2)>5 || abs(word_y1-word_y2)>5)
//            {word_x1 = word_x2 = word_x3 = word_x4 = word_x5 = word_x6 = word_x7 = word_x8 = 0;word_y1 = word_y2 = word_y3 =word_y4 = word_y5 = word_y6 = word_y7 =word_y8 = 0;cout << "重置"<< endl;}
//        }
//    }
//    else
//    {
//        if(abs(word_x1-word_x2)<5 && abs(word_y1-word_y2)<5)
//        {
////            cout << word_x1-word_x4 << endl;
//            double yuce_k =7.8,yuce_k2 =1.5;
//            next_x=word_x1
//                    +(word_x1-word_x7)*(yuce_k);
//            next_y=word_y1
//                    +(word_y1-word_y7)*(yuce_k2);
//        }
//        else
//        {word_x1 = word_x2 = word_x3 = word_x4 = word_x5 = word_x6 = word_x7 = word_x8 = 0;word_y1 = word_y2 = word_y3 =word_y4 = word_y5 = word_y6 = word_y7 =word_y8 = 0;cout << "全部重置"<< endl;}
//    }

//    if(next_x != 0)
//    {
////            cout<<"yuce"<<endl;
//        send_yaw = now_yaw - next_x;send_pitch = now_pitch - next_y;
//    }
//    else if (next_x == 0)
//    {
////            cout<<"wuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu"<<endl;
//        send_yaw = 0;send_pitch = 0;
//    }
//------------------------------------------------------------------------------------------------------------------------------
//    if(next_x != 0 )
//    {
        Armor_center7 = Armor_center6;Armor_center6 = Armor_center5;Armor_center5 = Armor_center4;Armor_center4 = Armor_center3;Armor_center3 = Armor_center2;Armor_center2 = Armor_center;
        R_center7= R_center6;R_center6 = R_center5;R_center5 = R_center4;R_center4= R_center3;R_center3 = R_center2;R_center2 = R_center;

        Point2f shoot = Point2f();

        if(R_center7.y!=0)
        {
            if(Armor_center7.x!=0)
            {
//                   line(img,Point2f(R_center.x,R_center.y),Point2f(R_center.x+215,R_center.y),Scalar(0,0,255));
//                   double tan1 = (Armor_center7.y-R_center7.y)/(Armor_center7.x-R_center7.x);
//                   double tan2 = (Armor_center.y-R_center.y)/(Armor_center.x-R_center.x);
//                   double tan3 = (Armor_center7.x-R_center7.x)/(Armor_center7.y-R_center7.y);
//                   double tan4 = (Armor_center.x-R_center.x)/(Armor_center.y-R_center.y);
//                   int x_dire=abs((Armor_center.x-R_center.x) - (Armor_center4.x-R_center4.x))/((Armor_center.x-R_center.x) - (Armor_center4.x-R_center4.x));//x移动方向
//                   int y_dire=abs((Armor_center.y-R_center.y) - (Armor_center4.y-R_center4.y))/((Armor_center.y-R_center.y) - (Armor_center4.y-R_center4.y));//y移动方向
//                   int dire = 0;//方向
//                   double yu = 0;
//                   if(Armor_center.y>R_center.y){x_dire *= -1;}
//                   if(Armor_center.x<R_center.x){y_dire *= -1;}
//                   if(abs(Armor_center.y-R_center.y)>abs(Armor_center.x-R_center.x)){/*cout << "x" << x_dire << endl;*/dire = x_dire;}
//                   if(abs(Armor_center.y-R_center.y)<=abs(Armor_center.x-R_center.x)){/*cout << "y" << y_dire << endl;*/dire = y_dire;}
//                   if(abs(Armor_center.y-R_center.y)>abs(Armor_center.x-R_center.x))
//                   {
//                       /*cout << abs(tan4 - tan3)*dire << endl;*//*cout << tan4 << endl;*/
//                       yu = abs(tan4 - tan3)*dire;
//                        line(img,Point2f(R_center.x,R_center.y),Point2f(R_center.x+215*tan4,R_center.y),Scalar(255,255,0));
//                   }
//                   else
//                   {
//                       /*cout << abs(tan2-tan1)*dire << endl;*//*cout << tan2 << endl;*/
//                       yu = abs(tan2-tan1)*dire;
//                   }
//                   if(abs(yu)>1){yu = 0;}
//                   cout << yu << endl;


//                line(img,Point2f(img.cols*0.5,img.rows*0.5),Point2f(img.cols*0.5+Armor_center.x-R_center.x,img.rows*0.5),Scalar(0,0,255));
//                line(img,Point2f(img.cols*0.5,img.rows*0.6),Point2f(img.cols*0.5+Armor_center7.x-R_center7.x,img.rows*0.6),Scalar(0,0,255));
//                line(img,Point2f(img.cols*0.5,img.rows*0.7),Point2f(img.cols*0.5+Armor_center.x-R_center.x-Armor_center7.x+R_center7.x,img.rows*0.7),Scalar(0,0,255));

//                line(img,Point2f(img.cols*0.5,img.rows*0.5),Point2f(img.cols*0.5,img.rows*0.5+Armor_center.y-R_center.y),Scalar(0,0,255));
//                line(img,Point2f(img.cols*0.6,img.rows*0.5),Point2f(img.cols*0.6,img.rows*0.5+Armor_center7.y-R_center7.y),Scalar(0,0,255));
//                line(img,Point2f(img.cols*0.7,img.rows*0.5),Point2f(img.cols*0.7,img.rows*0.5+((Armor_center.y-R_center.y)-(Armor_center7.y-R_center7.y))),Scalar(0,0,255));
//                float acc = Armor_center.x-R_center.x-Armor_center7.x+R_center7.x;
                shoot = Point2f (Armor_center.x+5*((Armor_center.x-R_center.x)-(Armor_center7.x-R_center7.x)),Armor_center.y+5*((Armor_center.y-R_center.y)-(Armor_center7.y-R_center7.y)));

                float RRR = sqrt((Armor_center.x-R_center.x)*(Armor_center.x-R_center.x)+(Armor_center.y-R_center.y)*(Armor_center.y-R_center.y));
                float rrr = sqrt((shoot.x-R_center.x)*(shoot.x-R_center.x)+(shoot.y-R_center.y)*(shoot.y-R_center.y));
//                cout << RRR/rrr << endl;
                shoot.x = R_center.x+(shoot.x-R_center.x)*(RRR/rrr);
                shoot.y = R_center.y+(shoot.y-R_center.y)*(RRR/rrr);
//                cout << RRR << "    " << rrr << endl;;
                circle(img,shoot,3,Scalar(0,0,255),3,8,0);
//------------------------------------------
//                cout << acc << endl;
//                    cout << abs((Armor_center1.x-R_center.x) - (Armor_center2.x-R_center2.x))/((Armor_center1.x-R_center.x) - (Armor_center2.x-R_center2.x)) << endl;
//                    cout << (Armor_center.x-R_center.x) - (Armor_center2.x-R_center2.x) << endl;
//                int x_dire=abs((Armor_center.x-R_center.x) - (Armor_center4.x-R_center4.x))/((Armor_center.x-R_center.x) - (Armor_center4.x-R_center4.x));//x移动方向
//                if(abs(Armor_center.y-R_center.y)*2/(R_list[0].size.height+R_list[0].size.height)<3){x_dire = 0;}
//                if(x_dire == -2147483648){x_dire = 0;}
////                cout << "x移动方向 " << x_dire << "   x移动系数  "  << (abs(Armor_center.y-R_center.y)*2/(R_list[0].size.height+R_list[0].size.height)) << endl;
//                send_yaw +=0.1*(abs(Armor_center.y-R_center.y)*2/(R_list[0].size.height+R_list[0].size.height))*x_dire;
////                send_yaw +=0.02*abs(abs(Armor_center.x-R_center.x)-abs(Armor_center7.x-R_center7.x))*x_dire;
//                if(x_dire == 0){send_yaw -= (abs(Armor_center.x-R_center.x)/(Armor_center.x-R_center.x))*0.4;}

//                double kkk = 1.0;
//                if(acc != -2147483648){
//                    if(abs(acc)<5){kkk=0.3;}
//                    else if(abs(acc)>=5 && abs(acc)<10){kkk=0.8;}
//                    else if(abs(acc)>=10 && abs(acc)<15){kkk=1.3;}
//                    else if(abs(acc)>=15 && abs(acc)<20){kkk=1.7;}
//                    else if(abs(acc)>=20 && abs(acc)<25){kkk=1.9;}
//                    else if(abs(acc)>=25 && abs(acc)<30){kkk=2.1;}
//                    else if(abs(acc)>=30 && abs(acc)<35){kkk=2.3;}
//                    else if(abs(acc)>=35 && abs(acc)<40){kkk=2.5;}
//                    else if(abs(acc)>=40 && abs(acc)<45){kkk=2.8;}
//                    else {kkk=0;}
//                }
//                kkk = abs(acc)/acc*kkk;
//                cout << kkk << endl;
//                int y_dire=abs((Armor_center.y-R_center.y) - (Armor_center4.y-R_center4.y))/((Armor_center.y-R_center.y) - (Armor_center4.y-R_center4.y));//x移动方向
//                if(abs(Armor_center.x-R_center.x)*2/(R_list[0].size.height+R_list[0].size.height)<3){y_dire = 0;}
//                if(y_dire == -2147483648){y_dire = 0;}
////                cout << "y移动方向 " << y_dire << "   y移动系数  "  << (abs(Armor_center.x-R_center.x)*2/(R_list[0].size.height+R_list[0].size.height)) << endl;
//                send_pitch -=0.1*(abs(Armor_center.x-R_center.x)*2/(R_list[0].size.height+R_list[0].size.height))*y_dire;
//                if(y_dire == 0 && (Armor_center.y-R_center.y)<0){send_yaw -= (abs(Armor_center.y-R_center.y)/(Armor_center.x-R_center.x))*0.3;}
//------------------------------------------





//------------------------------------------

//                if(abs((Armor_center.y-R_center.y) - (Armor_center4.y-R_center4.y))/((Armor_center.y-R_center.y) - (Armor_center4.y-R_center4.y))>0)
//                {
//    //                cout << "下移" << endl;
//                    if(Armor_center.y>R_center.y && abs(Armor_center.y-R_center.y)>5*R_list[0].size.height){
//    //                        cout << "y下限" << endl;
//                        send_pitch -=0.4;
//                    }
//                    else {
//    //                        cout << "______" << endl;
//                        send_pitch -=0.7;
//                    }
//                }
//                else
//                {
//    //                cout << "上!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
//                    if(Armor_center.y<R_center.y && abs(Armor_center.y-R_center.y)>5*R_list[0].size.height){
//    //                        cout << "y上限" << endl;
//                        send_pitch +=0.1;
//                    }
//                    else {
//    //                        cout << "______" << endl;
//                        send_pitch +=0.2;
//                    }
//                }
            }
        }
if(shoot.x != 0)
{

        Mat r,rot,trans;
        vector <Point2f> ccc;
        std :: vector<cv::Point3f> SHOOT;
        SHOOT.push_back(Point3f(- 2,  2,0));
        SHOOT.push_back(Point3f(  2,  2,0));
        SHOOT.push_back(Point3f(  2, -2,0));
        SHOOT.push_back(Point3f(- 2, -2,0));
    //        Point2f a (Next_Armor_center.x-100,Next_Armor_center.y-100);
    //        Point2f b (Next_Armor_center.x+100,Next_Armor_center.y-100);
    //        Point2f c (Next_Armor_center.x+100,Next_Armor_center.y+100);
    //        Point2f d (Next_Armor_center.x-100,Next_Armor_center.y+100);
        Point2f a (shoot.x-100,shoot.y-100);
        Point2f b (shoot.x+100,shoot.y-100);
        Point2f c (shoot.x+100,shoot.y+100);
        Point2f d (shoot.x-100,shoot.y+100);
        ccc.emplace_back(a);ccc.emplace_back(b);ccc.emplace_back(c);ccc.emplace_back(d);
        solvePnP(SHOOT , ccc , cam_matrix , distortion_coeff , r , trans);

        double qqx = trans.at<double>(0, 0);
        double qqy = trans.at<double>(1, 0);
        double qqz = trans.at<double>(2, 0);
        double qtan_pitch = qqy / sqrt(qqx * qqx + qqz * qqz);
        double qtan_yaw = qqx / qqz;
        double pitch = -atan(qtan_pitch) * 180 / CV_PI;
        double yaw   = atan(qtan_yaw) * 180 / CV_PI;
        send_pitch = 1.1*pitch;
        send_yaw   = 1.1*yaw;
//-----------------------------------------------------------------------------------------------------------
//        if(abs((Armor_center.y-R_center.y) - (Armor_center4.y-R_center4.y))/((Armor_center.y-R_center.y) - (Armor_center4.y-R_center4.y))>0)
//        {
////                cout << "下移" << endl;
//            if(Armor_center.y>R_center.y ){
//                if(abs(Armor_center.y-R_center.y)>abs(Armor_center.x-R_center.x))
//                {
//    //                cout << "y下限" << endl;
//                    send_pitch -=0.9;
//                }
//                else {
//                    send_pitch -=1.5;
//                }

//            }
//            else {
////                        cout << "______" << endl;
//                if(Armor_center.y<R_center.y ){
//                    if(abs(Armor_center.y-R_center.y)>abs(Armor_center.x-R_center.x))
//                    {
//        //                cout << "y上限" << endl;
//                        send_pitch -=1.7;
//                    }
//                    else {
//                        send_pitch -=2.1;
//                    }
//                }
//            }
//        }
//        else
//        {
////                cout << "上移!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
//            if(Armor_center.y>R_center.y ){
//                if(abs(Armor_center.y-R_center.y)>abs(Armor_center.x-R_center.x))
//                {
//    //                cout << "y下限" << endl;
//                    send_pitch +=0;
//                }
//                else {
//                    send_pitch +=0.3;
//                }

//            }
//            else {
////                        cout << "______" << endl;
//                if(Armor_center.y<R_center.y ){
//                    if(abs(Armor_center.y-R_center.y)>abs(Armor_center.x-R_center.x))
//                    {
//        //                cout << "y上限" << endl;
//                        send_pitch -=1.2;
//                    }
//                    else {
//                        send_pitch -=0.3;
//                    }
//                }
//            }
//        }
//-------------------------------------------------------------------------------------------------------
send_pitch -=1.9;
//    cout << "yaw   " << send_yaw << "  pitch   " << send_pitch << endl;
    if(abs(send_yaw) > 19){/*cout << "yaw离谱！！！！！！！！！！！！！！！！！！！！！！！！！！" << send_yaw << endl;*/send_yaw = 0;}
    if(abs(send_pitch) > 19){/*cout << "pitch离谱！！！！！！！！！！！！！！！！！！！！！！！！！！" << send_pitch << endl;*/send_pitch = 0;}
    VisionData   vdata = {{(float)send_yaw},{(float)send_pitch},{0},0,0};
    usb_serial.TransformData(vdata);usb_serial.send();
//    cout << "yaw  " << send_yaw << "   //pitch  " << send_pitch << endl;
}
else{
    VisionData   vdata = {{0},{0},{0},0,0};
    usb_serial.TransformData(vdata);usb_serial.send();
}


}

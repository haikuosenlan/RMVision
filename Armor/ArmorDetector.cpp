 #include "Armor.h"


ArmorDetector::ArmorDetector()
{
    T = T_max;
    targetArmor = ArmorBag();
    lastArmor = ArmorBag();
//    namedWindow("svm",WINDOW_AUTOSIZE);
//    cvCreateTrackbar("middle","svm",&middle,255);
}
ArmorDetector::~ArmorDetector(){}

void ArmorDetector::findLights(Mat &img,Mat &final_img)
{
    this->final_img=final_img;
    RotatedRect light_ellipse;
    vector<vector<Point>> lightContours;  //候选灯条轮廓
    Mat contourImg; //给findContours用的图像，防止findContours改变roi
    final_img.copyTo(contourImg);
    findContours(contourImg,lightContours,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);//找到轮廓,耗时

    for (uint i = 0;i < lightContours.size();i++)//这个循环的方式或许是个可以优化的点
    {
        if(lightContours[i].size()<6)continue;// 轮廓点数小于6，不可拟合椭圆
        if(contourArea(lightContours[i]) < 30.0||contourArea(lightContours[i]) > 8000.0)continue;//用面积简单筛选灯
        light_ellipse = fitEllipse(lightContours[i]);//创建临时旋转矩阵
//        if(light_ellipse.size.height/light_ellipse.size.width<1.8 || light_ellipse.size.height/light_ellipse.size.width>14.3 )continue;//用框选的长宽比筛选灯条
        if (light_ellipse.angle > 90){light_ellipse.angle = light_ellipse.angle - 180;}
        if(abs(light_ellipse.angle)>35)continue;//灯条倾斜度筛选灯条
//        Point2f vertices[4];light_ellipse.points(vertices);//旋转矩形画灯条
//        for (int i = 0; i < 4; i++)line(img, vertices[i], vertices[(i + 1) % 4], Scalar(250, 250, 50),2);

        lights.emplace_back(light_ellipse);//比push_back好，节省冗余运算
    }
    if (lights.size() < 2) {
        findResult = NO_COUPLIE_LIGHT_FOUND; //灯条少于两条则为没找到灯条
        return; //exit
    }

    //将灯条从左到右排序
    sort(lights.begin(), lights.end(),[](LightBag & a1, LightBag & a2)
    {return a1.center.x < a2.center.x; });
//    for(uint i = 0; i < lights.size();i++)//根据lights里的灯条顺序标号，检查用
//    {
//        char string[2];
//        sprintf(string,"%d",i);
//        putText(img,string,lights[i].center, 2,1,Scalar(0,0,255));
//    }

    findResult = COUPLIE_LIGHT_FOUND;
    return;
}


void ArmorDetector::matchArmor(Mat &img)
{
    for (uint i = 0; i < lights.size(); i++)
    {
        for (uint j = i + 1; j <  lights.size(); j++)
        {
            ArmorBag armor = ArmorBag(img,lights[i],lights[j]);//用左右灯条初始化 armor

            if(armor.SuitableArmor())//几何条件筛选装甲板
            {
//                cout <<"几何通过";
                armor.getWrap(img,armor.armor_Vertices,middle);//获取装甲板透视过的图案
                if(svm.picMatch(armor))//svm判断图案
                {
//                    cout <<"svm通过   "<<endl;
                    armors.emplace_back(armor); /*将匹配好的装甲板push入armors中*/
                }
            }
        }
    }
}

void ArmorDetector::priority(Mat &img)
{
    if(T == 0)//无缓冲
    {   /*cout << "无缓冲" << endl;*/
        if(armors.size() == 0)//无现目标
        {preArmor = lastArmor = targetArmor = ArmorBag();}
        else//有现目标
        {
            for(uint i = 0 ; i < armors.size();i++)//遍历装甲板，附分，找到得分最高的
            {
                armors[i].score += (int)armors[i].armor_area/10;              //根据装甲板面积大小加分
//                armors[i].score += (int)armors[i].armor_size*100;             //根据装甲板大小类型加分
                armors[i].score -= (int)armors[i].center_diff/10;            //根据装甲板中心距图像正中心距离减分
                if(armors[i].robotID == 2){armors[i].score -= 800;}         //若是工程，则减去对应得分
            }
            sort(armors.begin(), armors.end(),[](ArmorBag & a1, ArmorBag & a2)//根据装甲板得分从大到小排序
            {return a1.score > a2.score; });
            targetArmor = armors[0];
            lastArmor = targetArmor;
            preArmor = ArmorBag();
            T=T_max;
        }
    }
    else//有缓冲
    {
//        cout << T << endl;
        if(armors.size() == 0)//无现目标
        {
            if(lastArmor.score==0)//无前目标
            {preArmor = lastArmor = targetArmor = ArmorBag();T=T_max;}
            else//有前目标
            {
                if(preArmor.score==0)//无前前目标
                {targetArmor = lastArmor;T--;}
                else//有前前目标
                {
                    targetArmor = lastArmor;
                    targetArmor.armor_center.x = lastArmor.armor_center.x+0.5*(lastArmor.armor_center.x-preArmor.armor_center.x);
                    targetArmor.armor_center.y = lastArmor.armor_center.y+0.5*(lastArmor.armor_center.y-preArmor.armor_center.y);
                    preArmor = lastArmor;
                    lastArmor = targetArmor;
                    T--;
                }
            }
        }
        else//有现目标
        {
            for(uint i = 0 ; i < armors.size();i++)//遍历装甲板，附分，找到得分最高的
            {
                armors[i].score += (int)armors[i].armor_area/10;              //根据装甲板面积大小加分
//                armors[i].score += (int)armors[i].armor_size*100;             //根据装甲板大小类型加分
                armors[i].score -= (int)armors[i].center_diff/10;            //根据装甲板中心距图像正中心距离减分
                if(armors[i].robotID == 2){armors[i].score -= 800;}         //若是工程，则减去对应得分
            }
            sort(armors.begin(), armors.end(),[](ArmorBag & a1, ArmorBag & a2)//根据装甲板得分从大到小排序
            {return a1.score > a2.score; });
            if(lastArmor.score == 0)//无前目标
            {
                targetArmor = armors[0];
                lastArmor = targetArmor;
                preArmor = ArmorBag();
                T=T_max;
            }
            else//有前目标
            {
                if(abs(armors[0].armor_center.x-lastArmor.armor_center.x)<2.5*lastArmor.l_light.length)//上次目标不为空，判断与这次位置差
                {
                    targetArmor = armors[0];//位置相差不大，直接赋值
                    preArmor = lastArmor;
                    lastArmor = targetArmor;
                    T=T_max;
                }
                else//位置相差大
                {
                    if(lastArmor.robotID != armors[0].robotID)//判断这次目标装甲ID和上次是否一样,装甲板ID不同，进入缓冲
                    {
                        if(preArmor.score == 0)//无前前目标
                        {
                            targetArmor = lastArmor;
                            T--;
                        }
                        else//有前前目标
                        {
                            targetArmor = lastArmor;
                            targetArmor.armor_center.x = lastArmor.armor_center.x+0.5*(lastArmor.armor_center.x-preArmor.armor_center.x);
                            targetArmor.armor_center.y = lastArmor.armor_center.y+0.5*(lastArmor.armor_center.y-preArmor.armor_center.y);
                            preArmor = lastArmor;
                            lastArmor = targetArmor;
                            T--;
                        }
                    }
                    else//位置相差太大，但装甲板ID相同，则直接赋值
                    {
                        float mem = lastArmor.armor_center.y;
                        if(preArmor.score == 0)//无前前目标
                        {
                            targetArmor = armors[0];
                            direction = abs(lastArmor.armor_center.x-targetArmor.armor_center.x)/(lastArmor.armor_center.x-targetArmor.armor_center.x);//设置陀螺方向,负为左
                            lastArmor = targetArmor;
                            T=T_max;
                        }
                        else//有前前目标
                        {
                            targetArmor = armors[0];
                            direction = abs(lastArmor.armor_center.x-targetArmor.armor_center.x)/(lastArmor.armor_center.x-targetArmor.armor_center.x);//设置陀螺方向,负为左
                            lastArmor = targetArmor;
                            preArmor = ArmorBag();
                            T=T_max;
                        }
                        if(TuoLuo == 0)//未进入陀螺模式
                        {
                            shoot.x = targetArmor.armor_center.x /*+ direction*(targetArmor.l_light.length+targetArmor.r_light.length)*/;
                            shoot.y = /*0.5*(mem + */targetArmor.armor_center.y/*)*/;
                            TuoLuo = 30;//改变状态
                        }
                    }
                }
            }
        }
    }
    if(TuoLuo != 0)
    {
        shoot_t = 1;
        if(abs(direction)>2){direction = 1;}
        shoot.x = targetArmor.armor_center.x /*+ direction*(targetArmor.l_light.length+targetArmor.r_light.length)/(31-TuoLuo)*/;
        shoot.y = targetArmor.armor_center.y;
        TuoLuo -- ;
//        circle(img,shoot,9,Scalar(0,0,255),2,8);
    }
    else {shoot_t=0;shoot = Point2f();}
}


void ArmorDetector::detect(Mat &img, Mat &final_img)
{
    lights.clear();
    armors.clear();
    if(lastArmor.score != 0)
    {
       char string[30];
       sprintf(string,"T:%d",T);
//       circle(img,lastArmor.armor_center,8,Scalar(0,250,250));//黄圈画出上一次目标中心//在经过优先级处理过后，lastarmor 就会等于 targetarmor ,用于当下一次的lastarmor
       //putText(img,string,lastArmor.armor_center, 1,1,Scalar(0,0,255));
    }
//cout << lastArmor.armor_center.x << "     " ;
    findLights(img,final_img);//找灯条

    matchArmor(img);//判别装甲板

    priority(img);//优先级//在经过优先级处理过后，lastarmor 就会等于 targetarmor ,用于当下一次的lastarmor
//cout  << lastArmor.armor_center.x << endl;
    drew(img,armors);//画出筛选的所有找到的装甲板

//    OutArmors(armors);//终端输出信息
}


void ArmorDetector::drew(Mat &img,vector<ArmorBag> &armors)
{
    for(uint i=0;i<armors.size();i++)
    {char string[10];sprintf(string,"%d",i);/*imshow(string,armors[i].armor_warp);*/}//显示找到的装甲板图案

    for(uint i = 0 ; i < armors.size(); i++)//画出所有找到的装甲板
    {
        line(img,armors[i].armor_Vertices[0],armors[i].armor_Vertices[1],Scalar(250,250,0));//蓝色表示所有装甲板
        line(img,armors[i].armor_Vertices[2],armors[i].armor_Vertices[3],Scalar(250,250,0));
        line(img,armors[i].armor_Vertices[0],armors[i].armor_Vertices[3],Scalar(250,250,0));
        line(img,armors[i].armor_Vertices[1],armors[i].armor_Vertices[2],Scalar(250,250,0));
        line(img,targetArmor.armor_Vertices[0],targetArmor.armor_Vertices[1],Scalar(0,250,0));//绿色表示target装甲板
        line(img,targetArmor.armor_Vertices[2],targetArmor.armor_Vertices[3],Scalar(0,250,0));
        line(img,targetArmor.armor_Vertices[0],targetArmor.armor_Vertices[3],Scalar(0,250,0));
        line(img,targetArmor.armor_Vertices[1],targetArmor.armor_Vertices[2],Scalar(0,250,0));

//        circle(img,armor.armor_Vertices[0],5,Scalar(250,250,250),2,8,0);//根据圆圈大小显示四个点的顺序
//        circle(img,armor.armor_Vertices[1],5,Scalar(250,250,250),2,8,0);
//        circle(img,armor.armor_Vertices[2],5,Scalar(250,250,250),2,8,0);
//        circle(img,armor.armor_Vertices[3],5,Scalar(250,250,250),2,8,0);

        char string[30];
//        sprintf(string,"ID:%d score:%d",armors[i].robotID,armors[i].score);
        sprintf(string,"ID:%d",armors[i].robotID);
        putText(img,string,armors[i].armor_Vertices[0],2,1,Scalar(0,0,255));
    }

    circle(img,targetArmor.armor_center,5,Scalar(0,250,0));//画出targetarmor
    putText(img,"target",targetArmor.armor_Vertices[3],1,1,Scalar(0,255,0));

}

void OutLights(vector<LightBag> & lights)//输出找到灯条的中心、角度信息
{
    cout << "**************************** L I G H T S ******************************"<< endl;
    if (lights.empty()) {
        cout << "NO_COUPLIE_LIGHT_FOUND!" << endl;
    }
    else
    {
        cout << "COUPLIE_LIGHT_FOUND!" << endl;
//        for (size_t i = 0; i < lights.size(); i++)//输出找到灯条的中心、角度信息
//        {
//            cout << "Light " << i << " Center:" << lights[i].center << endl;
//            cout << "Light " << i << " Angle :" << lights[i].angle << endl;
//        }
    cout << "疑似灯条数 ： " << lights.size() << endl;
        cout << "***********************************************************************" << endl;
    }
}

void OutArmors(vector<ArmorBag> & armors)//输出找到装甲板的中心、数字、匹配信息
{
    cout << "**************************** A R M O R S ******************************" << endl;
    if (armors.empty()) {cout << "ARMORS NOT FOUND!" << endl;}
    else
    {
        cout << "ARMOR FOUND!" << endl;
/*
 * 为了方便系统之间的移植而定义的，不同的系统上，定义size_t 可能不一样。
 * size_t在32位系统上定义为 unsigned int，也就是32位无符号整型。在64位系统上定义为 unsigned long ，也就是64位无符号整形。
 * size_t 的目的是提供一种可移植的方法来声明与系统中可寻址的内存区域一致的长度。
 */
        cout <<"装甲板个数 : " <<armors.size() << endl;
        for (size_t i = 0; i < armors.size(); i++)
        {
            cout << "————————————————————————————" << endl;
            cout << "Armor " << i << " Center: " << armors[i].armor_center << endl;
            if (armors[i].armor_size == SMALL_ARMOR)    cout << "Armor Type: SMALL ARMOR" << endl;
            else if(armors[i].armor_size ==  BIG_ARMOR) cout << "Armor Type: BIG ARMOR" << endl;

            cout << "灯条平行度: " << armors[i].lightAngleDiff() << endl;
            cout << "中心连线水平度: " << armors[i].lightCenterDeviation() << endl;
            cout << "灯条距离与灯条长度比: " << armors[i].lengthDistanceProportion() << endl;
            cout << "左右灯条长度差比值: " << armors[i].lengthDiffProportion() << endl;
        }
        cout << "**********************************************************************" << endl;
    }

}

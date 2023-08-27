#include <algorithm>
#include <iostream>
#include <thread>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/imgproc/imgproc_c.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <math.h>
#include "opencv2/highgui/highgui_c.h"
#include "Start/start.h"

using namespace std;
using namespace cv;


int main()
{
    Start start;
    std::thread ImgProcessor(&Start::ImgProcess,&start);
    std::thread Reception(&Start::Recive,&start);
    ImgProcessor.join();
    Reception.join();
//    std::thread AAA(&Start::aaa,&start);
//    std::thread BBB(&Start::bbb,&start);
//    std::thread CCC(&Start::ccc,&start);
//    AAA.join();
//    BBB.join();
//    CCC.join();

    return 0;
}

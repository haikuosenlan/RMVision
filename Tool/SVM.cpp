#include "Armor/Armor.h"

using namespace std;
using namespace cv;
using namespace ml;

bool MatchSVM::picMatch(ArmorBag &armor)
{

   ArmorBag q = ArmorBag();
   q = armor;
   Mat p = q.armor_warp.reshape(1, 1);

   p.convertTo(p, CV_32FC1);
   int response =0;
   response = (int)svm->predict(p);
//   cout << "svm : " << response <<endl;
   switch (response)
   {
    case 0:
        armor.robotID = NO;
       break;
    case 1:
        armor.robotID = HERO;
       break;
    case 2:
        armor.robotID = TRUCK;
       break;
    case 3:
        armor.robotID = INFANTRY_3;
       break;
    case 4:
        armor.robotID = INFANTRY_4;
       break;
    case 5:
        armor.robotID = INFANTRY_5;
       break;
    case 6:
        armor.robotID = SENTRY;
       break;
   case 7:
       armor.robotID = HOME                                                        ;
      break;
   }

   if(armor.robotID == NO)
   {
//       cout << "no" << endl;
       return false;
   }
   else
   {
//       cout << "yes" << endl;
       return true;
   }



}

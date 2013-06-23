#include "opencv2/opencv.hpp"
#include "cv.h"
#include "highgui.h"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

Mat frame,fram,hsv,change;

int main()
{
  VideoCapture vid(0);
  if(!vid.isOpened())
    return -1;
  cvNamedWindow("color_isolation_hsv",0);
  for(;;)
  {
    vid >>fram;
    imshow("color_isolation_hsv",fram);
      cout << vid.GetFrameRate();
    if(waitKey(10)>=0)break;
  }
}
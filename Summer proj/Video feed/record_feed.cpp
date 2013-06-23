#include "opencv2/opencv.hpp"
#include "cv.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;
int main()
{
 VideoCapture vid(0);
  if(!vid.isOpened())
    return -1;
  Mat frame;
  vid>>frame;
  VideoWriter record("RobotVideo.ogg", CV_FOURCC('D','I','V','X'), 30, frame.size(), true);
  while(1)
  {
    vid>>frame;
    imshow("video", frame);
    record << frame; 
    if(waitKey(30) >= 0) break;
  }
  
}
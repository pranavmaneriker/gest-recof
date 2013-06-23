#include "opencv2/opencv.hpp"
#include "cv.h"
#include "highgui.h"
#include <iostream>
#include <stdio.h>
#define THRES 1000

using namespace std;
using namespace cv;

Mat frame1,frame2,frame3,motion_frame,t1,t2;

int main()
{
  VideoCapture vid(0);
  if(!vid.isOpened())
   return -1;
  cvNamedWindow("diff",0);
  while(1)
  {
    vid>>frame1;
    vid>>frame2;
    vid>>frame3;
    cvtColor(frame1,frame1,CV_RGB2HSV);
    cvtColor(frame2,frame2,CV_RGB2HSV);
    cvtColor(frame3,frame3,CV_RGB2HSV);
    blur(frame1,frame1,Size(10,10),Point(-1,-1));
    blur(frame2,frame2,Size(10,10),Point(-1,-1));
    blur(frame3,frame3,Size(10,10),Point(-1,-1));
    motion_frame=Mat::zeros(frame1.rows,frame1.cols,CV_32FC3);
    for(int i=0;i<frame1.cols;++i)
    {
      for(int j=0;j<frame1.rows;++j)
      {
	t1=frame2-frame1;
	t2=frame3-frame2;
	if(t1.at<Vec3b>(i,j)!=Vec3b(0,0,0) && t2.at<Vec3b>(i,j)!=Vec3b(0,0,0))
	{
	  motion_frame.at<Vec3b>(i,j)=Vec3b(255,255,255);
	  printf("%d%d%\n",i,j);
	}
      }
    }
    //bitwise_xor(frame2-frame1,frame3-frame2,motion_frame,noArray()); //try and, or ,xor
//     for(int i=0;i<frame3.rows;++i)
//   {
//     for(int j=0;j<frame3.cols;++j)
//     {
//       if((frame3.at<Vec3b>(i,j).val[0]*frame3.at<Vec3b>(i,j).val[0]+frame3.at<Vec3b>(i,j).val[1]*frame3.at<Vec3b>(i,j).val[1]+frame3.at<Vec3b>(i,j).val[2]*frame3.at<Vec3b>(i,j).val[2])<THRES)
//       {
// 	frame3.at<Vec3b>(i,j)=Vec3b(0,0,0);
//       }
//     }
//   }
    //flip(motion_frame,motion_frame,1);
   // imshow("diff",motion_frame);
    imshow("wind",frame1);
    if(waitKey(0)>=0)break;
  }
  return 0;
}
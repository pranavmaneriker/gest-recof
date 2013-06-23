#include "opencv2/opencv.hpp"
#include "cv.h"
#include "highgui.h"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

Mat frame,fram,hsv,change;
int hthres=100,sthres=255,vthres=255,ht=60,st=88,vt=114,hmax,hmin,smax,smin,vmax,vmin;

void update_greathue(int  h)
{
  for(int i=0;i<hsv.rows;++i)
  {
    for(int j=0;j<hsv.cols;++j)
    {
      if(hsv.at<Vec3b>(i,j).val[0]<h)
      {
	hsv.at<Vec3b>(i,j)=Vec3b(0,0,0);
      }
    }
  }
  imshow("color_isolation_hsv",hsv);
}
void update_lesshue(int l)
{
  for(int i=0;i<hsv.rows;++i)
  {
    for(int j=0;j<hsv.cols;++j)
    {
      if(hsv.at<Vec3b>(i,j).val[0]>l)
      {
	hsv.at<Vec3b>(i,j)=Vec3b(0,0,0);
      }
    }
  }
  imshow("color_isolation_hsv",hsv);
}
void update_greatsat(int  h)
{
  for(int i=0;i<hsv.rows;++i)
  {
    for(int j=0;j<hsv.cols;++j)
    {
      if(hsv.at<Vec3b>(i,j).val[1]<h)
      {
	hsv.at<Vec3b>(i,j)=Vec3b(0,0,0);
      }
    }
  }
  imshow("color_isolation_hsv",hsv);
}
void update_lesssat(int l)
{
  for(int i=0;i<hsv.rows;++i)
  {
    for(int j=0;j<hsv.cols;++j)
    {
      if(hsv.at<Vec3b>(i,j).val[1]>l)
      {
	hsv.at<Vec3b>(i,j)=Vec3b(0,0,0);
      }
    }
  }
  imshow("color_isolation_hsv",hsv);
}
void update_greatv(int  h)
{
  for(int i=0;i<hsv.rows;++i)
  {
    for(int j=0;j<hsv.cols;++j)
    {
      if(hsv.at<Vec3b>(i,j).val[2]<h)
      {
	hsv.at<Vec3b>(i,j)=Vec3b(0,0,0);
      }
    }
  }
  imshow("color_isolation_hsv",hsv);
}
void update_lessv(int l)
{
  for(int i=0;i<hsv.rows;++i)
  {
    for(int j=0;j<hsv.cols;++j)
    {
      if(hsv.at<Vec3b>(i,j).val[2]>l)
      {
	hsv.at<Vec3b>(i,j)=Vec3b(0,0,0);
      }
    }
  }
  imshow("color_isolation_hsv",hsv);
}
int update(int h1,int h2,int s1,int s2,int v1,int v2)
{
  for(int i=0;i<hsv.rows;++i)
  {
    for(int j=0;j<hsv.cols;++j)
    {
      if(!(hsv.at<Vec3b>(i,j).val[0]>h1 && hsv.at<Vec3b>(i,j).val[0]<h2 && hsv.at<Vec3b>(i,j).val[1]>s1 && hsv.at<Vec3b>(i,j).val[1]<s2 && hsv.at<Vec3b>(i,j).val[2]>v1 && hsv.at<Vec3b>(i,j).val[2]<v2))
      {
	hsv.at<Vec3b>(i,j)=Vec3b(0,0,0);
      }
    }
  }
  blur(hsv,hsv,Size(10,10),Point(-1,-1));
  imshow("color_isolation_hsv",hsv);
}
int main()
{
  VideoCapture vid(0);
  if(!vid.isOpened())
    return -1;
  cvNamedWindow("color_isolation_hsv",0);
  cvSetWindowProperty("color_isolation_hsv",CV_WND_PROP_FULLSCREEN,CV_WINDOW_FULLSCREEN);
  hmin=cvCreateTrackbar("Hue>", "color_isolation_hsv", &ht, 255,update_greathue);
  hmax=cvCreateTrackbar("Hue<", "color_isolation_hsv", &hthres, 255,update_lesshue);
  smin=cvCreateTrackbar("Sat>", "color_isolation_hsv", &st, 255,update_greatsat);
  smax=cvCreateTrackbar("Sat<", "color_isolation_hsv", &sthres, 255,update_lesssat);
  vmin=cvCreateTrackbar("Value>", "color_isolation_hsv", &vt, 255,update_greatv);
  vmax=cvCreateTrackbar("Value<", "color_isolation_hsv", &vthres, 255,update_lessv);
  for(;;)
  {
    vid >>fram;
    blur(fram,frame,Size(10,10),Point(-1,-1));
    cvtColor(frame,hsv,CV_RGB2HSV);
    update(ht,hthres,st,sthres,vt,vthres);
    //imshow("video_blur",frame);
    //imshow("video",fram);
    flip(hsv,hsv,1);
    imshow("color_isolation_hsv",hsv);
    if(waitKey(10)>=0)break;
  }
}

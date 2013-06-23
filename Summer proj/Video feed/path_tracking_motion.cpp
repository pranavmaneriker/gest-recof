#include "opencv2/opencv.hpp"
#include "cv.h"
#include "highgui.h"
#include <iostream>
#include <stdio.h>

#define THRES 5000

using namespace std;
using namespace cv;

Mat frame1,frame2,frame3,img,img_scl;
int switch_value=1,clear_value;
Point prev=Point(-1,-1);

void filter()
{
  blur(frame1,frame1,Size(10,10),Point(-1,-1));
  blur(frame2,frame2,Size(10,10),Point(-1,-1));
  blur(frame3,frame3,Size(30,30),Point(-1,-1));
  
  for(int i=0;i<frame3.rows;++i)
  {
    for(int j=0;j<frame3.cols;++j)
    {
      if((frame3.at<Vec3b>(i,j).val[0]*frame3.at<Vec3b>(i,j).val[0]+frame3.at<Vec3b>(i,j).val[1]*frame3.at<Vec3b>(i,j).val[1]+frame3.at<Vec3b>(i,j).val[2]*frame3.at<Vec3b>(i,j).val[2])<THRES)
      {
	frame3.at<Vec3b>(i,j)=Vec3b(0,0,0);
      }
    }
  }
  //TODO
}
void clear_callback(int position)
{
  for(int i=0;i<frame1.rows;++i)
  {
    for(int j=0;j<frame1.cols;++j)
    {
      img.at<Vec3b>(i,j)=Vec3b(0,0,0);      
    }
  }
}
void scale()
{
  resize(img,img_scl,Size(0,0),0.05,0.05,CV_INTER_AREA);
  imshow("IMG_SCL",img_scl);
}


void switch_callback(int n)
{
 if(switch_value==0)
 {
   prev.x=-1;
   prev.y=-1;
 }
}
int plot_centroid()
{
  int x=0, y=0;
  int count=0;
 for(int i=0;i<frame3.rows;++i)
  {
    for(int j=0;j<frame3.cols;++j)
    {
      
      if(!((frame3.at<Vec3b>(i,j).val[0]*frame3.at<Vec3b>(i,j).val[0]+frame3.at<Vec3b>(i,j).val[1]*frame3.at<Vec3b>(i,j).val[1]+frame3.at<Vec3b>(i,j).val[2]*frame3.at<Vec3b>(i,j).val[2])<THRES))
      {
	x+=i;y+=j;++count;
      }
    }
  }
 if(count!=0 /*&& switch_value*/)
 {
   x=((x)/count);y=(y/count);
   if(prev.x !=-1 && prev.y!=-1 /*&& (((prev.y-x)*(prev.y-x))+((prev.x-y)*(prev.x-y)))<SUDDEN_JUMP*/)
   {
     line(img,Point(y,x),prev,Scalar(255,255,255),2,8);
   }
   img.at<Vec3b>(x,y)=Vec3b(255,255,255);
   prev.x=y;
   prev.y=x;
   //blur(img, img, Size(10,10), Point(-1,-1));
 }
 imshow("motion",img);
}
int main()
{
  VideoCapture vid(0);
  if(!vid.isOpened())
   return -1;
  cvNamedWindow("motion",0);
  cvCreateTrackbar("Switch","motion",&switch_value,1,switch_callback);
  cvSetWindowProperty("motion",CV_WND_PROP_FULLSCREEN,CV_WINDOW_FULLSCREEN);
  cvCreateTrackbar("clear","motion",&clear_value,1,clear_callback);
  vid>>frame1;
  frame2=frame1.clone();
  img=frame1.clone();
  for(int i=0;i<img.rows;++i)
  {
    for(int j=0;j<img.cols;++j)
    {
      img.at<Vec3b>(i,j)=Vec3b(0,0,0);
    }
  }
  while(1)
  {
    vid>>frame1;
    frame3=frame1-frame2;
    flip(frame3,frame3,1);
    filter();
    frame2=frame1.clone();
    plot_centroid();
    scale();
    if(waitKey(10)>=0)break;
  }
  return 0;
}
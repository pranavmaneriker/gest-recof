#include "opencv2/opencv.hpp"
#include "cv.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#define SUDDEN_JUMP 10000
using namespace std;
using namespace cv;

Mat frame,img;
int switch_value;
Point prev=Point(-1,-1);
void filter(int h1,int h2,int s1,int s2,int v1,int v2)
{
  
  for(int i=0;i<frame.rows;++i)
  {
    for(int j=0;j<frame.cols;++j)
    {
      if(!(frame.at<Vec3b>(i,j).val[0]>h1 && frame.at<Vec3b>(i,j).val[0]<h2 && frame.at<Vec3b>(i,j).val[1]>s1 && frame.at<Vec3b>(i,j).val[1]<s2 && frame.at<Vec3b>(i,j).val[2]>v1 && frame.at<Vec3b>(i,j).val[2]<v2))
      {
	frame.at<Vec3b>(i,j)=Vec3b(0,0,0);
      }
      else
      {
	frame.at<Vec3b>(i,j)=Vec3b(255,255,255);
      }
    }
  }
  blur(frame,frame,Size(10,10),Point(-1,-1));
}

void switch_callback( int position ) {
  if(position ==0)
  {
    prev=Point(-1,-1);
  }
}

void out_edge()
{
 int x, y,count=0;
 for(int i=0;i<frame.rows;++i)
  {
    for(int j=0;j<frame.cols;++j)
    {
      if(frame.at<Vec3b>(i,j).val[0]==255)
      {
	x+=i;y+=j;++count;
      }
    }
  }
 if(count!=0 && switch_value)
 {
   x/=count;y/=count;
   if(prev.x !=-1 && prev.y!=-1)
   {
    line(img,Point(y,x),prev,Scalar(255,255,255),2,4);
   }
   img.at<Vec3b>(x,y)=Vec3b(255,255,255);
   prev.y=x;
   prev.x=y;
   blur(img, img, Size(10,10), Point(-1,-1));
 }
 imshow("path",img);
}
int main()
{
  VideoCapture vid(0);
  if(!vid.isOpened())
    return -1;
  cvNamedWindow("path",0);
  cvSetWindowProperty("path",CV_WND_PROP_FULLSCREEN,CV_WINDOW_FULLSCREEN);
  cvCreateTrackbar("Switch","path",&switch_value,1,switch_callback);
  vid>> frame;
  img=frame.clone();
  for(int i=0;i<img.rows;++i)
  {
    for(int j=0;j<img.cols;++j)
    {
      img.at<Vec3b>(i,j)=Vec3b(0,0,0);
    }
  } 
  while(1)
  {
    vid>> frame;
    cvtColor(frame,frame,CV_RGB2HSV);
    blur(frame,frame,Size(10,10),Point(-1,-1));
    filter(60,100,88,255,114,213);
    flip(frame,frame,1);
    out_edge();
    if(waitKey(10)>=0)
    break;
  }
  
}

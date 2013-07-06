/* This records a gesture and saves it in a file "recorded" by default otherwise with the argument passed*/

#include "opencv2/opencv.hpp"
#include "cv.h"
#include <opencv2/imgproc/imgproc.hpp>   //opencv
#include <iostream>
#include <stdio.h>      //std
#include <unistd.h> 
#include <time.h>       //time
#include <string.h>
#include <sstream>	//string concatenation
#include <dirent.h>    //count files
#include <math.h>
#include <stdlib.h>

#define FILTER1 73,100,88,255,114,255
#define FILTER2 50,72,100,171,149,212  //HSV filter args
#define MILS_BEFORE_GEST 100	       // Wait time before gesture starts recording
#define GEST_TIME 1.5 		       //Time for which a gesture is recorded
#define N_CONST 25 		      //Normalisation const for rescaling
using namespace std;
using namespace cv;
  
VideoCapture video(0);
Mat orig, filt1,filt2, cent,cropped,rescaled,result;
Point prev=Point(-1,-1);
int co,flag =0; //whether to start gesture recording
int vec[2],save_value;
int gest_arr[30][2];
FILE *fp;
String filename;
void clear(Mat &img)
{
  for(int row=0;row<img.rows;++row)
  {
    for(int col=0;col<img.cols;++col)
    {
      img.at<Vec3b>(row,col)=Vec3b(0,0,0);
    }
  }
}
void filter(int h1,int h2,int s1,int s2,int v1,int v2, Mat& filt)  //filter the coloured part 
{
  for(int i=0;i<orig.rows;++i)
  {
    for(int j=0;j<orig.cols;++j)
    {
      if(!(orig.at<Vec3b>(i,j).val[0]>h1 && orig.at<Vec3b>(i,j).val[0]<h2 && orig.at<Vec3b>(i,j).val[1]>s1 && orig.at<Vec3b>(i,j).val[1]<s2 && orig.at<Vec3b>(i,j).val[2]>v1 && orig.at<Vec3b>(i,j).val[2]<v2))
      {
	filt.at<Vec3b>(i,j)=Vec3b(0,0,0);
      }
      else
      {
	filt.at<Vec3b>(i,j)=Vec3b(255,255,255);
      }
    }
  }
  blur(filt,filt,Size(10,10),Point(-1,-1));
}
int mod (int *v)
{
  return (int)sqrt(v[0]*v[0]+v[1]*v[1]); 
}
void rescale()
{
  int r_max=0;
  for(int i=0;i<30;++i)
  {
    if(r_max<mod(gest_arr[i]))
    {
      r_max=mod(gest_arr[i]);
    }
  }
  for(int i=0;i<30;++i)
  {
    gest_arr[i][0]=(gest_arr[i][0]*N_CONST)/r_max;
    gest_arr[i][1]=(gest_arr[i][1]*N_CONST)/r_max;
  }
}

void centroid()                //plot the centroids and calculate vector 
{
  int row1=0,col1=0,count1=0;
  int row2=0,col2=0,count2=0;
  for(int i=0;i<filt1.rows;++i)
  {
    for(int j=0;j<filt1.cols;++j)
    {
      if(filt1.at<Vec3b>(i,j)==Vec3b(255,255,255))
      {
	count1++;row1+=i;col1+=j;
      }
      if(filt2.at<Vec3b>(i,j)==Vec3b(255,255,255))
      {
	count2++;row2+=i;col2+=j;
      }
    }
  }
  if(count1!=0 && count2!=0)
  {
    row1/=count1;col1/=count1;
    row2/=count2;col2/=count2;
    if(flag==1)
    {
      vec[0]=row1-row2;
      vec[1]=col1-col2;   
    }
    flag=1;
  }
}
void rec_gest_image()   	//Records the actual gesture
{
  clock_t t;
  t=clock();
  co=0;
  clear(result);
  while(co<30 && ((int)((float)((clock()-t)/CLOCKS_PER_SEC)*100))%5==0)	//Time for which gesture is recorded && framerate
  {
    video >>orig;
    cvtColor(orig,orig,CV_RGB2HSV);
    blur(orig,orig,Size(10,10),Point(-1,-1));
    filter(FILTER1,filt1);
    filter(FILTER2,filt2);
    centroid();
    gest_arr[co][0]=vec[0];
    gest_arr[co][1]=vec[1];
    co++;
  }
  rescale();
  for(int i=0;i<co;++i)
  {
    vec[0]=gest_arr[i][0];vec[1]=gest_arr[i][1];
    //fprintf("%d,%d\n",gest_arr[i][0],gest_arr[i][1]);
    line(result,Point(result.cols/2,result.rows/2),Point(result.cols/2+vec[1],result.rows/2+vec[0]),Scalar(255-i*8,255-i*8,255-i*8),1,4);
  }
  imwrite("img.png",result);  
}
void save_callback(int position)
{
  fp=fopen(&filename[0],"w");
  for(int i=0;i<30;i++)
  {
    fprintf(fp,"%d %d\n",gest_arr[i][0],gest_arr[i][1]);
  }
}

int rec_gest() //Record the gesture
{
  flag =0;
  if(!video.isOpened())
    return -1;
  video >>orig;
  filt1=orig.clone();
  clear(filt1);
  filt2=filt1.clone();
  result=filt1.clone();
  while(1)
  {
    video >>orig;
    cvtColor(orig,orig,CV_RGB2HSV);
    blur(orig,orig,Size(10,10),Point(-1,-1));
    filter(FILTER1,filt1);
    filter(FILTER2,filt2);
    centroid();
    if(flag)
    {
      usleep(MILS_BEFORE_GEST*1000);
      rec_gest_image();
      break;
    }
  }
  return 0;
}

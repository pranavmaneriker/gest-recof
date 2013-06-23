#include "opencv2/opencv.hpp"
#include "cv.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sstream>
#include <dirent.h>
#include <stdlib.h>
#include <fstream>
#include <math.h>

#define PATH "./gestures_2/"

using namespace std;
using namespace cv;

string path=PATH;
string train="./2_col_train/";

int count_gestures()
{
  DIR *dpdf;
  struct dirent *epdf;
  dpdf = opendir("./gestures_2");
  int count=0;
  if (dpdf != NULL)
  {
    while (epdf = readdir(dpdf))
    {
	count++;
    }
  }
  return count-2;
}
int count_files()
{
  DIR *dpdf;
  struct dirent *epdf;
  dpdf = opendir("./gestures_2/gesture1");
  int count=0;
  if (dpdf != NULL)
  {
    while (epdf = readdir(dpdf))
    {
	count++;
    }
  }
  return count-2;
}

int main()
{
  int no_files=count_files();
  int no_gest=count_gestures();
  int img_area=51*51; 	//for normalisation constant n, this should be (2n+1)
  int i;
  string path1;
  Mat training_mat(no_gest*no_files,img_area,CV_32FC1);
  Mat rowimg(51,51,CV_32FC1);
  Point prev(0,0);
  Mat labels(no_gest*no_files,1,CV_32FC1);
  CvSVMParams params;
  params.svm_type    = CvSVM::C_SVC;
  params.kernel_type = CvSVM::LINEAR;
  params.term_crit   = cvTermCriteria(CV_TERMCRIT_ITER, 1000, 1e-6);//100
  CvSVM svm;
  int no_row=0;
  ifstream instream;
  for(int rest=1;rest<=no_gest;rest++)
{
    for(i=0;i<no_files;i++)
    {
      for(int j=0;j<51;++j)
      {
	for(int k=0;k<51;++k)
	{
	  rowimg.at<float>(j,k)=0;
	}
      }
    prev.x=0;prev.y=0;
    stringstream ss,ss1;
    ss<< rest;
    ss1<< i+1;
    path1=path+"gesture"+ss.str()+"/gesture"+ss1.str();
    char *pl=&path1[0];
    instream.open(pl);
    int x,y;
    for(int k=0;k<30;k++)
    {
	    instream >> x >> y;
	    line(rowimg,Point(25+x,25+y),prev,Scalar((k+1)*8),1,4);
	    prev.x=25+x;prev.y=25+y;
    }
    int ii=0;
    for(int i=0;i<51;++i)
    {
      for(int j=0;j<51;++j)
      {
	training_mat.at<float>(no_row,ii++)=rowimg.at<float>(i,j);
      }
    }
    no_row++;
    instream.close();
    }
}
    
for(int i=0;i<=labels.rows;++i)
{
    labels.at<float>(i)=((int)(i/no_files))+1;
}
  svm.train(training_mat, labels, Mat(), Mat(), params);
  string name=(train+"traindata");
  char * p;
  p=&name[0];
  svm.save(p);
  return 0;
}

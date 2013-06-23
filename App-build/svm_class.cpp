#include "opencv2/opencv.hpp"
#include "cv.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sstream>
#include <dirent.h>

#define PATH "./gestures/"
using namespace std;
using namespace cv;

string path =PATH;
int ct;
int count_files()
{
  DIR *dpdf;
  struct dirent *epdf;
  dpdf = opendir("./traindata/");
  int 
  count=0;
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
  CvSVMParams params;
  params.svm_type    = CvSVM::C_SVC;
  params.kernel_type = CvSVM::LINEAR;
  params.term_crit   = cvTermCriteria(CV_TERMCRIT_ITER, 100000, 1e-6);
  CvSVM svm;
  ct=count_files();
  Mat img_mat_1 = imread("./lol.png",0);
  for(int nog=1;nog<=ct;++nog)
  {
   stringstream ss;
  ss<<nog;
  string path="./traindata/"+ss.str();
  char *p;
  p=&path[0];
  //printf("%s\n",p);
  svm.load(p); // loading
  Mat img_mat_1d(1,32*24,CV_32FC1);
  int ii = 0; 
    for (int i = 0; i<img_mat_1.rows; i++) 
    {
      for (int j = 0; j < img_mat_1.cols; j++) 
	{
	    img_mat_1d.at<float>(0,ii++) = img_mat_1.at<uchar>(i,j);
	}
    }
    float pred=svm.predict(img_mat_1d);
    if(pred==-1)
    {
    	continue;
    }
    else
    {
    	printf("%d\n",nog);
    	break;
    }
   }	
  return 0;
}

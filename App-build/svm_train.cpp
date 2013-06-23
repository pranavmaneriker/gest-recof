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

string path =PATH,train="./traindata/";
int count_gestures()
{
  DIR *dpdf;
  struct dirent *epdf;
  dpdf = opendir("./gestures");
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
  dpdf = opendir("./gestures/gesture1");
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
  int img_area=32*24; 
int i;
for(int nog=1;nog<=no_gest;nog++)
{
	 Mat training_mat(no_gest*no_files,img_area,CV_32FC1);
  	int no_row=0;
	for(i=0;i<no_files;i++)
	{
		stringstream ss,ss1;
		ss<< nog;
		ss1<< i+1;
		Mat img_mat_1=imread(path+"/gesture"+ss.str()+"/gesture"+ss1.str()+".png",0);
		int ii=0;
		for(int k=0;k<img_mat_1.rows;k++)
		{
			for (int j = 0; j < img_mat_1.cols; j++) 
				{
						training_mat.at<float>(i,ii++) = img_mat_1.at<uchar>(k,j);
				}
		}
		no_row++;
	}
	for(int rest=1;rest<=no_gest;rest++)
	{
		if(rest==nog)continue;
		for(i=0;i<no_files;i++)
		{
			stringstream ss,ss1;
			ss<< rest;
			ss1<< i+1;
			Mat img_mat_1=imread(path+"/gesture"+ss.str()+"/gesture"+ss1.str()+".png",0);
			int ii=0;
			for(int k=0;k<img_mat_1.rows;k++)
			{
				for (int j = 0; j < img_mat_1.cols; j++) 
					{
							training_mat.at<float>(no_row,ii++) = img_mat_1.at<uchar>(k,j);
					}
			}
			no_row++;
		}
	}
		
		
		Mat labels(no_gest*no_files,1,CV_32FC1);
	  for(int i=0;i<=labels.rows;++i)
	  {
	  	if(i<no_files)
	    	labels.at<float>(i)=1;
	    else
	    	labels.at<float>(i)=-1;
	  }
	  
	  CvSVMParams params;
	  params.svm_type    = CvSVM::C_SVC;
	  params.kernel_type = CvSVM::LINEAR;
	  params.term_crit   = cvTermCriteria(CV_TERMCRIT_ITER, 100000, 1e-6);
	  CvSVM svm;
	  svm.train(training_mat, labels, Mat(), Mat(), params);
	  stringstream ss;
	  ss<< nog;
	  string name=(train+ss.str());
	  char * p;
	  p=&name[0];
	  svm.save(p);
	  //imwrite("./SVMGest"+ss.str()+".png",training_mat);
	}
	
   // saving
  /*svm.load("svm_filename"); // loading
  Mat img_mat_1 = imread("./lol.png",0);
  Mat img_mat_1d(1,32*24,CV_32FC1);
  int ii = 0; // Current column in training_mat
    for (int i = 0; i<img_mat_1.rows; i++) 
    {
      for (int j = 0; j < img_mat_1.cols; j++) 
	{
	    img_mat_1d.at<float>(0,ii++) = img_mat_1.at<uchar>(i,j);
	}
    }
  printf("%f\n",svm.predict(img_mat_1d));*/
  if(waitKey(0)>=0)
  return 0;
}

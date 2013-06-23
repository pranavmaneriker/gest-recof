#include "opencv2/core/core.hpp"
#include "cv.h"
#include "highgui.h"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int main()
{
    Mat image;
    image=imread("images/airplane.jpg",CV_LOAD_IMAGE_COLOR);
    namedWindow("airplane",CV_WINDOW_AUTOSIZE);
    imshow("airplane",image);
    waitKey(0);
    return 0;
}
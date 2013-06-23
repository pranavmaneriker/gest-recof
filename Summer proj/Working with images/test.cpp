#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
using namespace std;

int main()
{
  stringstream ss;
  ss<<5;
  string s=ss.str();
  string s2="gesture";
  string s3=s2+".png"+s;
  cout <<s3;
  return 0;
}
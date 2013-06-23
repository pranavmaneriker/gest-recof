#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <iostream>
using namespace std;

int main()
{
  time_t t;
  time(&t);
  for(int i=1;i<=1000000;i*=10)
  {
    int a ,b;
    scanf("%d%d",&a,&b);
    time(&t);
    cout <<time<<endl;
    usleep(i);
    printf("%d\n",a+b);
    time(&t);
    cout <<time<<endl;
   }
  return 0;
}
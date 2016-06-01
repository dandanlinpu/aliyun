#include <iostream>
using namespace std;
#define MAX 100
int a=10;
int b;
static int c;
void * add_range(int l, double h, int c){
	return NULL;
}
int add_range(int low, int high)
{
        static int X;
	int i, sum=0;
	for (i = low; i <= high; i++)
		sum = sum + i;
	return sum;
}
int main(){
  int result[MAX];
  result[0]=add_range(1,10);
  result[1]=add_range(1,100);
  cout<<result[0]<<result[1]<<endl;
  return 0;
}

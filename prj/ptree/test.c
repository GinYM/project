#include<stdio.h>
int main(){
	struct prinfo test[100];
	printf("This is a test:\n");
	int a = 100;
	int *b = &a;
	int i=syscall(356,test,b);
	printf("Answer is %d!\n",i);
	printf("Test End!:\n\n");
	return 0;
}

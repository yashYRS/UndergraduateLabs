#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>


int main() {
	char c[50];
	printf(" Enter a string -");
	gets(c);
	int fp = creat("sample.txt",777);
	write(fp,c,strlen(c)*sizeof(char));
	close(fp);
}
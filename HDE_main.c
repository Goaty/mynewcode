#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//designed to work with input integers less than 100
int testNumber;//number of test case
int testPointer=0;//pointer of test number
int termNumber[100];//termNumber[i] = number of terms in test case i
char termValue_string[100][500];//termValue[i]=string of testcase i
int termValue[100][100]; //termValue[i][k] = value of term k in test case i
int termPointer=0;//pointer of term number in a test case

char seps[]=" ,\n";
char *token;//store the token of termValue_string[i]
long int memberSum=0;
int getInfo(){//store input information in termNumber and termValue
	char termNumber_string[100];
	if(testPointer<testNumber){
		fgets(termNumber_string,100,stdin);
		termNumber[testPointer]=atoi(termNumber_string);
		fgets(termValue_string[testPointer],500,stdin);
		testPointer++;
	}
	else{
		testPointer=0;
		return 0;
	}
	getInfo();
}
int enterNumber(){//enter number
	termValue[testPointer][termPointer]=atoi(token);
	token=strtok(NULL,seps);
	termPointer++;
	if(token!=NULL){
		enterNumber();
	}
	else{return 0;}
}
int getNumber(){//extract numbers from string str and store them in termValue[testPointer][termPointer]
	if(testPointer<testNumber){
		token=strtok(termValue_string[testPointer],seps);
		enterNumber();
		termPointer=0;
		testPointer++;
	}
	else{
		testPointer=0;
		return 0;
	}
	getNumber();
}
int printResult_case(int testPointer){//print the sum of testcase testPointer
	if(termPointer<termNumber[testPointer]){
		if(termValue[testPointer][termPointer]>0){
			memberSum+=(long)(termValue[testPointer][termPointer])*(termValue[testPointer][termPointer]);
		}
		termPointer++;
	}
	else{
		termPointer=0;
		fprintf(stdout,"%ld\n",memberSum);
		memberSum=0;
		return 1;
	}
	printResult_case(testPointer);
}
int printSum(){//print all the sums
	if(testPointer<testNumber){
		printResult_case(testPointer);
		testPointer++;
	}
	else{
		testPointer=0;
		return 1;
	}
	printSum();
}
void main(){
	char buffer[256];//string for number of testcases
	fgets(buffer, 256,stdin);
	testNumber=atoi(buffer);
	getInfo();
	getNumber();
	printSum();
	getchar();

}

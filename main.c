#include"kNN.h"
int main(){
	
	char  name[15]="datasets.txt";
	char  namet[15]="testdata.txt";
	load_dataset(name);
	load_testdata(namet);
	//printtrainset();
	//printtestset();
	int i;
	for(i=0;i<numberoftestdata;i++){
		knnpredict(3,&test[i]);
		printf("%d %s \n",i,test[i].name);
	}
	printf("K is and %d learning rate : %.3f \n",3,getpercantage());
	
	

	return 0;
}

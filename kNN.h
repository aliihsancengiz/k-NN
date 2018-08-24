#ifndef kNN
#define kNN
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
/*
	@brief : iris_f structure are used to store train and test data for iris dataset
	@f1,f2,f3,f4 is store feature of flowers
	@name stores name of flowers 
	@flag stores type of flowers 
		1-Iris-setosa
		2-Iris-versicolor
		3-Iris-virginica
*/
struct iris_f{
	float f1,f2,f3,f4;	
	char name[25];
	int flag;
};
typedef struct iris_f iris; 

/*
	@brief :dist_t structure are used to store ecludian distance of train datas to test data
*/

struct dist_t{
	float distance;
	int index;
};
typedef struct dist_t dist_t;

#define numberoftraindata 120
#define numberoftestdata 30
iris train[numberoftraindata];
iris test[numberoftraindata];
dist_t dist2t[numberoftraindata];

/*
	@brief : parse the data in th each line and map its @param parameter
*/
void parse_traindata(char line[40],iris * param){
	char * token=strtok(line,",");
	param->f1=atof(token);
	token = strtok(NULL, ",");
	param->f2=atof(token);
	token = strtok(NULL, ",");
	param->f3=atof(token);
	token = strtok(NULL, ",");
	param->f4=atof(token);
	token = strtok(NULL, ",");
	strcpy(param->name,token);
	if(strcmp(param->name,"Iris-setosaa")<0)
		param->flag=1;
	else if(strcmp(param->name,"Iris-versicolora")<0)
		param->flag=2;
	else if(strcmp(param->name,"Iris-virginicaa")<0)
		param->flag=3;
}
/*
	@brief : parse the data in th each line and map its @param parameter
*/
void parse_testdata(char line[40],iris * param){
	char * token=strtok(line,",");
	param->f1=atof(token);
	token = strtok(NULL, ",");
	param->f2=atof(token);
	token = strtok(NULL, ",");
	param->f3=atof(token);
	token = strtok(NULL, ",");
	param->f4=atof(token);
}
/*
	@brief : get the ecludian distance between two samples
*/
float GetEcludianDistance(iris *a,iris *b){
	float f1=pow(a->f1-b->f1,2);
	float f2=pow(a->f2-b->f2,2);
	float f3=pow(a->f3-b->f3,2);
	float f4=pow(a->f4-b->f4,2);
	return sqrt(f1+f2+f3+f4);
}
/*
	@brief : loading training data set into train array
*/
void load_dataset(char * name){
	FILE * fin=fopen(name,"r");
	int i=0;
    if(fin != NULL)
    {
        char line[40];
        while(fgets(line, sizeof(line), fin) != NULL)
        {
        	parse_traindata(line,&(train[i]));
        i++;
        if(i==numberoftraindata)
        break;
		}
    } 
	fclose(fin);
}
/*
	@brief : loading test data set into train array
*/

void load_testdata(char * name){
	FILE * fin=fopen(name,"r");
	int i=0;
    if(fin != NULL)
    {
        char line[40];
        while(fgets(line, sizeof(line), fin) != NULL)
        {
        	parse_testdata(line,&(test[i]));
        i++;
        if(i==numberoftestdata)
        break;
		}
    } 
	fclose(fin);	
}
/*
	@brief : print the train set with features
*/
void printtrainset(){
	int i;
	for(i=0;i<numberoftraindata;i++)
		printf("%d %.2f %.2f %.2f %.2f %s",train[i].flag,train[i].f1,train[i].f2,train[i].f3,train[i].f4,train[i].name);
	printf("\n-----------------------------------------------------------------\n");	
}
/*
	@brief : print the test set with features
*/
void printtestset(){
	int i;
	for(i=0;i<numberoftestdata;i++)
		printf("%.2f %.2f %.2f %.2f\n",test[i].f1,test[i].f2,test[i].f3,test[i].f4);
	printf("\n-----------------------------------------------------------------\n");
}
/*
	@brief : swap two distance node for sorting 
*/
void swap(dist_t*a1,dist_t *b1){
	float a,b;
	int c,d;
	a=a1->distance;
	b=b1->distance;
	c=a1->index;
	d=b1->index;
	a1->distance=b;
	b1->distance=a;
	a1->index=d;
	b1->index=c;
	
}
/*
	@brief : sort the distance data for sellecting K times min distance data
*/
void sort_distance(){
	int i,j;
	for(i=0;i<numberoftraindata-1;i++){
		for(j=0;j<numberoftraindata-i-1;j++){
			if(dist2t[j].distance > dist2t[j+1].distance){
				swap(&dist2t[j],&dist2t[j+1]);
			}
		}
	}
}
/*
	@brief : finds higest num of three integer for calculating which flowers are much than others  
*/
int higest(int a,int b,int c){
	if(a>b && a>c)
		return a;
	else if(b>c)
		return b;
	else 
		return c;
}
/*
	@brief : predict the test data by k-NN algorith
	@param K is K value of algorithm
	@param t is test data
*/
void knnpredict(unsigned int K,iris *t){
	float * dis=(float*)malloc(sizeof(float)*K);
	int i,res,a=0,b=0,c=0,j=0;
	// getting ecludian distance and map its index to dist2t array
	for(i=0;i<numberoftraindata;i++){
		dist2t[i].distance=GetEcludianDistance(t,&train[i]);
		dist2t[i].index=i;
	
	}
	// sort distance with appreciate index for sellecting K min samples
	sort_distance();
	for(i=0;i<K;i++){
		*(dis+i)=dist2t[i].index;
	}
	// count the which type is much more in the sellecting area
	for(i=0;i<K;i++){
		j=*(dis+i);
		if(train[j].flag==1){
			a++;
		}
		else if(train[j].flag==2){
			b++;
		}
		else if(train[j].flag==3){
			c++;
		}
	}
	// and map the names of max data in given area to test data
	res=higest(a,b,c);
	if(res==a){
			strcpy(t->name,"Iris-setosa");
			t->flag=1;
	}
	else if(res==b){
		t->flag=2;
		strcpy(t->name,"Iris-versicolor");
	}
	else if(res==c){
		t->flag=3;
		strcpy(t->name,"Iris-virginica");
	}
}
/*
	@brief : truth percentage of predicting data;
*/
float getpercantage(){
	int i,a=0,b=0,c=0;
	float res;
	for(i=0;i<numberoftestdata;i++){
		if(test[i].flag==1){
			a++;
		}
		else if(test[i].flag==2){
			b++;
		}
		else if(test[i].flag==3){
			c++;
		}
	}
	
	res=abs(numberoftestdata/3-a)+abs(numberoftestdata/3-b)+abs(numberoftestdata/3-c);
	res/=2.0;
	res=(numberoftestdata)-res;
	res=res*(100.0/(float)numberoftestdata);
	return res;
}
#endif

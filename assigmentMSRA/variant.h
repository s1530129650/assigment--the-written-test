#pragma once
#include<stdio.h>
#define MAX_LINE_SIZE 4096   //fgets函数读取的最大字节数
#define MAX_DATA_SIZE 33000  //处理数据的最大数量（行数）
#define MAX_char_SIZE 32	 //处理数据的单个字符额的最大数量
#define MAX_kind_SIZE 50	 //数据单个属性下最大类别数量 例如工作阶层最多有50种
#define MAX_encode_SIZE 3	 //文本数据转成数字数据的最大长度，规约后的最大类别数为3
#define feature_SIZE 28		 //特征向量的维数为28


 typedef struct               //定义结构体存放csv数据
{
	double  age[MAX_DATA_SIZE];                           //csv文件里的age数据
	char   workclass[MAX_DATA_SIZE][MAX_char_SIZE];			//csv文件里的workclass数据
	char   education[MAX_DATA_SIZE][MAX_char_SIZE];			//csv文件里的education数据 以下类似
	double  educationNum[MAX_DATA_SIZE];	
	char 	maritalStatus[MAX_DATA_SIZE][MAX_char_SIZE];	 
	char 	occupation[MAX_DATA_SIZE][MAX_char_SIZE];
	char 	relationship[MAX_DATA_SIZE][MAX_char_SIZE];	
	char	race[MAX_DATA_SIZE][MAX_char_SIZE];	
	char 	sex[MAX_DATA_SIZE][MAX_char_SIZE];	
	double	capitalGain[MAX_DATA_SIZE];
	double  capitalLoss[MAX_DATA_SIZE];
	double	hoursPerWeek[MAX_DATA_SIZE];
	char	nativeCountry[MAX_DATA_SIZE][MAX_char_SIZE];	
	

} attributes ; //属性数据

  typedef struct   //定义结构体统计各个属性的类别及其数量
{
	
	char   workclass[MAX_kind_SIZE][MAX_char_SIZE];   //workclassd的种类 比如有 State-gov、 Self-emp-not-inc、private等
	int    lenWorkclass;							//workclassd的种类的数量
	char   education[MAX_kind_SIZE][MAX_char_SIZE]; // education的种类 比如有 HS-grad、Bachelors等
	int    lenEducation;								// education的数量  以下类似
	char   maritalStatus[MAX_kind_SIZE][MAX_char_SIZE];	
	int    lenMaritalStatus;
	char   occupation[MAX_kind_SIZE][MAX_char_SIZE];
	int    lenOccupation;
	char   relationship[MAX_kind_SIZE][MAX_char_SIZE];	
	int    lenRelationship;
	char   race[MAX_kind_SIZE][MAX_char_SIZE];	
	int    lenRace;
	char   sex[MAX_kind_SIZE][MAX_char_SIZE];
	int    lenSex;
	char   nativeCountry[MAX_kind_SIZE][MAX_char_SIZE];	
	int    lenNativeCountry;

} attriNum ; //属性及其数量

  typedef struct{                         //存放各个属性 编码
	double  age[MAX_DATA_SIZE];                              //属性age的 编码
	int   encodeWorkclass[MAX_DATA_SIZE][MAX_encode_SIZE] ;   //属性Workclass的 编码 以下类似
	int   encodeEducation[MAX_DATA_SIZE][MAX_encode_SIZE];
	double  educationNum[MAX_DATA_SIZE];	
	int   encodeMaritalStatus[MAX_DATA_SIZE][MAX_encode_SIZE];		
	int  encodeOccupation[MAX_DATA_SIZE][MAX_encode_SIZE];	
	int   encodeRelationship[MAX_DATA_SIZE][MAX_encode_SIZE];	
	int   encodeRace[MAX_DATA_SIZE][MAX_encode_SIZE];	
	int   encodeSex[MAX_DATA_SIZE][MAX_encode_SIZE];
	double	capitalGain[MAX_DATA_SIZE];
	double  capitalLoss[MAX_DATA_SIZE];
	double	hoursPerWeek[MAX_DATA_SIZE];
	int  encodeNativeCountry[MAX_DATA_SIZE][MAX_encode_SIZE];	
	
  } dataEncode; //编码

  typedef struct{              //存放各个属性的label大于50k的比率
	double   rateWorkclass[MAX_kind_SIZE]; //属性Workclass的label大于50k的比率
	double   rateEducation[MAX_kind_SIZE];	//属性Education的label大于50k的比率
	double   rateMaritalStatus[MAX_kind_SIZE];	//属性eMaritalStatus的label大于50k的比率	
	double   rateOccupation[MAX_kind_SIZE];			//以下类似
	double   rateRelationship[MAX_kind_SIZE];	
	double   rateRace[MAX_kind_SIZE];	
	double   rateSex[MAX_kind_SIZE];
	double   rateNativeCountry[MAX_kind_SIZE];	
	
  } over50Rate; //存放各个属性的label大于50k的比率

  typedef struct{
    char   workclass[MAX_kind_SIZE][MAX_char_SIZE];   //workclassd的种类 比如有 State-gov、 Self-emp-not-inc、private等
	int    encodeWorkclass[MAX_kind_SIZE][MAX_encode_SIZE]	; //属性Workclass对应的数字编码 
	char   education[MAX_kind_SIZE][MAX_char_SIZE];			// education的种类 比如有 HS-grad、Bachelors等
	int    encodeEducation[MAX_kind_SIZE][MAX_encode_SIZE]; //属性education对应的数字编码 以下类似
	char   maritalStatus[MAX_kind_SIZE][MAX_char_SIZE];	
	int    encodeMaritalStatus[MAX_kind_SIZE][MAX_encode_SIZE];	
	char   occupation[MAX_kind_SIZE][MAX_char_SIZE];
	int    encodeOccupation[MAX_kind_SIZE][MAX_encode_SIZE];	
	char   relationship[MAX_kind_SIZE][MAX_char_SIZE];	
	int    encodeRelationship[MAX_kind_SIZE][MAX_encode_SIZE];	
	char   race[MAX_kind_SIZE][MAX_char_SIZE];	
	int    encodeRace[MAX_kind_SIZE][MAX_encode_SIZE];	
	char   sex[MAX_kind_SIZE][MAX_char_SIZE];
	int    encodeSex[MAX_kind_SIZE][MAX_encode_SIZE];
	char   nativeCountry[MAX_kind_SIZE][MAX_char_SIZE];	
	int   encodeNativeCountry[MAX_kind_SIZE][MAX_encode_SIZE];	
  } text2numcode;//保存文本与数字编码之间的对应转换

attributes trainDATA;     //存放训练集的原始csv数据
attributes testDATA;      //存放测试集的csv数据

attriNum trainAttriTextData;   //存放训练集的某些与文本属性有关的变量
dataEncode trainDataEncode;    //存放训练集的某些与文本属性有关的编码
over50Rate trainover50Rate;    //存放各个属性的label大于50k的比率
text2numcode Text2Num;		   //保存文本与数字编码之间的对应转换


int label[MAX_DATA_SIZE];		 //标签用int型

int trainNumRow ;				 //文件行数
int trainNumCol ;				 // 文件列数（以第一行为准）
int trainRealNumRow ;            //删除不需要的，实际用到的行数

double  trainFeatureVector[MAX_DATA_SIZE][feature_SIZE];		//特征向量为feature_SIZE维
int    lenPositive;												//正样本长度；
int    lenNegative;												//负样本长度；
double  postivefeatureVector[MAX_DATA_SIZE][feature_SIZE];		//正的特征向量集
double  negativefeatureVector[MAX_DATA_SIZE][feature_SIZE];		//负的特征向量集
double  trainingFeatureVector[MAX_DATA_SIZE][feature_SIZE];		//用于交叉验证的训练集
int     traininglabel[MAX_DATA_SIZE];							//训练集标签
int     lenTraining;											//训练集长度
double  ValidationFeatureVector[MAX_DATA_SIZE][feature_SIZE];	//用于交叉验证的验证集
int     Validationlabel[MAX_DATA_SIZE];							//验证集标签
int     lenValidation;											//验证集长度；

double w[feature_SIZE] ;										//权重w矩阵
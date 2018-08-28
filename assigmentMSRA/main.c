#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "processCSVFile.h"			//1.Data Loading
#include "Datapreprocessing.h"		//2.Data Preprocessing
#include"parameterSelection.h"      //3.Model Training and Parameter Selection
#include"testing.h"                 //4.Testing

int main()
{
    
	char *fpTrain1="census.csv";
	char *fpTest1="census-test.csv";
    double accuracy = 0;
  
	//1.data loading
	ReadCsvData(fpTrain1);           //读取csv数据
	

	//2.data preprocessing
	getAttriNum();					 //得到各个属性的种类以及种类数
	oneHotEncode();					 //one-hot encode
	HuffmanCoding();				 //赫夫曼-onehot编码 
    saveText2num();					 //保存文本与数字编码之间的对应转换
	normalization();				 //对数据进行归一化
	getfeatureVector();				 //得到特征向量


	//3.parameter selection and model training 
	stratifiedSampling();    //分层抽样 
	computeWeight();		 //计算不同参数的权重并选择最优的进行模型的训练
	

	//4.testing

	//4.1data loading
	ReadCsvData(fpTest1);           //读取csv数据

	//4.2.data preprocessing
	getAttriNum();					 //得到各个属性的种类以及种类数
	encodeText2num();				 //文本与数字编码之间的编码转换
	normalization();				 //对数据进行归一化
	getfeatureVector();				 //得到特征向量

	//4.3计算accuracy
	accuracy = testSetAccuracy();     //计算在测试集上的准确率
	printf("在测试集上的准确率为：%.8f\n",accuracy);
	
	return 0;
 } 
 

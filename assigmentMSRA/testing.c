#define _CRT_SECURE_NO_WARNINGS
#include"testing.h"

double  testSetAccuracy()     //计算准确率
{
	int i,j;
	double accuracy=0,count=0;           //count存放统计 预测正确的数量
	double fxi;                          //存放f(xi)的值
	int testlabel[MAX_DATA_SIZE];		//测得验证集标签
	memset(	testlabel,0,sizeof(testlabel));    //初始化测试结果的标签
	//使用线性函数预测label
	for(i=0;i<lenTraining;i++)
	{
		  fxi = 0;
          for(j=0;j<feature_SIZE;j++)          //feature_SIZE是特征向量的维数
		  {
			  fxi = fxi + w[j]*trainFeatureVector[i][j];		//计算f(xi)
		  }
		  testlabel[i]=(int)(fxi+0.5)>(int)fxi?(int)fxi+1:(int)fxi;   //对f(xi)进行四舍五入
	}
	 //计算正确率
	for(i=0;i<trainRealNumRow;i++ )
	{
		if(testlabel[i] == label[i])  //如果计算正确，则count加1
			count++;
	}
	accuracy = count/(double)trainRealNumRow;  //得到正确率
	return accuracy;         //返回正确率 
}
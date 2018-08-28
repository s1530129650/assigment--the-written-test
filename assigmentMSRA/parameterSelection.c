#define _CRT_SECURE_NO_WARNINGS
#include"parameterSelection.h"

double  lamdaset[2] ={0.01,0.001};								//参数集
double Betaset[4] = {0.001,0.01,0.1,1};

void xiPaiRand(int randarray[],int Times);						//洗牌算法生成范围为[0,Times-1]不重复的随机序列randarray
void Samping(int randArrayPostive[MAX_DATA_SIZE],int randArrayNegative[MAX_DATA_SIZE]);   ///取前70%为训练集 后30%为验证集
void computeRespectively(double LAmda,double BEta);				//分别计算不同参数的正确率
double lossFunction(double Lamda,double Beta);                  //计算lossfunction的值
void updateW(double Lamda,double Beta);                         //更新权重w
double  ValidationAccuracytest();								//在验证集上计算正确率

void computeFull(double LAmda,double BEta);				//在全部训练集的基础上计算最优参数得到的权重
double lossFunctionFull(double Lamda,double Beta);                  //在全部训练集的基础上计算lossfunction的值
void updateWFull(double Lamda,double Beta);                         //在全部训练集的基础上更新权重w

void stratifiedSampling()			//分层抽样 
{
	int randArrayPositive[MAX_DATA_SIZE];				 //随机数组
	int randArrayNegative[MAX_DATA_SIZE];
	int i,j;
	
	memset(	postivefeatureVector,0,sizeof(	postivefeatureVector));//初始化正负样本集合
	memset(	negativefeatureVector,0,sizeof(	negativefeatureVector));
	lenPositive = 0;     //初始化正负样本个数
	lenNegative = 0;
	//分出正负样本
	for(i = 0 ; i < trainRealNumRow; i++)
	{
		if(label[i] == 0)
		{
			 lenNegative++;
			for(j =0;j<feature_SIZE ;j++)
			negativefeatureVector[lenNegative-1][j] = trainFeatureVector[i][j];   //负样本集合
		}
		else
		{
			lenPositive++;	
			for(j =0;j<feature_SIZE ;j++)
				postivefeatureVector[lenPositive-1][j] = trainFeatureVector[i][j];   //正本集合
		}
	}
	
	printf("正样本有%d个   负样本有%d个\n", lenPositive, lenNegative);
	printf("\n");

  //打印postivefeatureVector
	printf("postivefeatureVector是：\n");
	for ( i = 0; i <3000; i=i+1000 )
	{
		for(j=0;j<feature_SIZE;j++)
			printf( "%.2f ",postivefeatureVector[i][j] ); 	
			printf("\n");
		
	}
	printf("\n");
	
	//打印negativefeatureVector
	printf("negativefeatureVector是：\n");
	for (  i = 0; i <3000; i=i+1000 )
	{
		for(j=0;j<feature_SIZE;j++)
			printf( "%.2f ", negativefeatureVector[i][j] ); 	
			printf("\n");
		
	}
	printf("\n");



	xiPaiRand(randArrayPositive,lenPositive);  //洗牌算法生成不重复的随机数
	xiPaiRand(randArrayNegative, lenNegative);                                       
	//取前70%的随机数 为训练集 后30%为验证集
	Samping(randArrayPositive,randArrayNegative);

	//打印traning set
	printf("分层抽样的结果是(以前三个为例)：\n");
	printf("traning set是：\n");
	for ( i = 0; i <3; i++ )
	{
		for(j=0;j<feature_SIZE;j++)
			printf( "%.2f ", trainingFeatureVector[i][j] ); 	
			printf("\n");
		
	}
	printf("\n");
	//打印traininglabel标签
	printf("标签是：\n");
	for ( i = 0; i <20000; i=i+1000 )
	{
		
			printf("%d\t",traininglabel[i]);
	}
	printf("\n");

	//打印验证集
	printf("validation set是(以前三个为例)：\n");
	for ( i = 0; i <3; i++ )
	{
		for(j=0;j<feature_SIZE;j++)
			printf( "%.2f ", ValidationFeatureVector[i][j] ); 	
			printf("\n");
	}
	printf("\n");

	//打印Validationlabel标签
	printf("标签是：\n");
	for ( i = 0; i <9000; i=i+1000 )
	{
		
			printf("%d\t",Validationlabel[i]);
	}
	printf("\n");
	
}
void xiPaiRand(int randarray[],int Times) //洗牌算法生成范围为[0,Times-1]不重复的机序列randarray
{//randarray是生成的随机数序列，生成范围为[0,Times-1]
	
	int i,j,tmp,count;
	count =Times;
	for(i=0;i<Times;i++) //初始化随机矩阵
	{
		randarray[i]=i;
	}

	while(count--)		//随机抽取，随机交换，生成随机矩阵
	{
		i=rand()%Times;
		j=rand()%Times;
		tmp=randarray[i];
		randarray[i]=randarray[j];
		randarray[j]=tmp;
	}

	//for test
	/*printf("生成的随机数为：\n");
	for(i=0;i<19;i++)
		printf("%d ",randarray[i]);
	puts("");*/
	
}
void Samping(int randArrayPostive[MAX_DATA_SIZE],int randArrayNegative[MAX_DATA_SIZE])   ///取前70%为训练集 后30%为验证集
{ //randArrayPostive范围为[0,正样本长度-1]的随机序列；randArrayNegative范围为[0,负样本长度-1]的随机序列
	int i,j,k;
	int countPositive,countNegative;  //训练集（相对为验证集而言）的长度

	memset(	trainingFeatureVector,0,sizeof(	trainingFeatureVector));	//初始化训练集和验证集
	memset(	ValidationFeatureVector,0,sizeof(ValidationFeatureVector));

	countPositive =  (int)lenPositive*0.7;
	//printf("countPositive 是%d.\n\n",countPositive );
	for(i=0;i<lenPositive;i++)
	{
		
		k = randArrayPostive[i];
		if( i < countPositive)
		{   traininglabel[i] = 1;
			for(j=0;j<feature_SIZE;j++)
			{trainingFeatureVector[i][j] = postivefeatureVector[k][j];} //分层抽取正的样本得到训练集
		}
		else
		{
			Validationlabel[i-countPositive] = 1;
			for(j=0;j<feature_SIZE;j++)
			{ValidationFeatureVector[i-countPositive][j] = postivefeatureVector[k][j];}//分层抽取正的样本得到验证集
		}	
	}

	countNegative =  (int)lenNegative*0.7;
	//printf("countNegative 是%d.\n\n",countNegative );
	for(i=0;i<lenNegative;i++)
	{
		
		k = randArrayNegative[i];
		if( i < countNegative)
		{    
			traininglabel[i+countPositive] = 0;
			for(j=0;j<feature_SIZE;j++)
			{trainingFeatureVector[i+countPositive][j] = negativefeatureVector[k][j];} //分层抽取正的样本得到训练集
		}
		else
		{
			Validationlabel[i+lenPositive-countPositive] = 0;
			for(j=0;j<feature_SIZE;j++)
			{ValidationFeatureVector[i+lenPositive-countPositive- countNegative][j] = negativefeatureVector[k][j];}//分层抽取正的样本得到验证集
		}	
	}
	lenTraining = countNegative+countPositive ;
	printf("training set有 %d个.\n\n",lenTraining  );
	lenValidation = lenNegative- countNegative+lenPositive-countPositive;
	printf("Validation set有 %d个.\n\n",lenValidation );
}

void computeWeight()//计算不同参数的权重
{
	FILE *fpweight = NULL; //需要注意
	int i,j;
	double Accuracy[2][4];
	double maxAccuracy = 0;
	double paraLamda,paraBeta;
	double a=0;

	printf("正确率为：\n");
	for(i=0;i<2;i++)
	{	for(j=0;j<4;j++)
		{    Accuracy[i][j]=0; 
	       
			computeRespectively(lamdaset[i],Betaset[j]);//带入不同的参数计算正确率
			Accuracy[i][j] = ValidationAccuracytest();
			printf("%.4f\n",Accuracy[i][j]);
		}
	}
	printf("\n");
	//的得到最佳参数
	for(i=0;i<2;i++)
	{	for(j=0;j<4;j++)
		{    
			if(Accuracy[i][j]>maxAccuracy) 
			{
				maxAccuracy = Accuracy[i][j];
				paraLamda = lamdaset[i];
				paraBeta = Betaset[j];
			}
		}
	}
	printf("最佳参数为：lamda= %.4f\t beta = %.4f\n",paraLamda,paraBeta );
	printf("正确率为 %.4f\n\n",maxAccuracy  );
	
	//保存最佳参数 和权重
	computeFull(paraLamda,paraBeta);
	fpweight = fopen("weight_and_parameter.txt","w+");//打开或者新建
    if(NULL ==  fpweight )
    {

        printf("weight_and_parameter.txt\n") ; //返回错误代码
		return ;
     }
	fprintf(fpweight ,"最佳参数为：lamda= %.4f\t beta = %.4f\n",paraLamda,paraBeta );
	fprintf(fpweight ,"权重系数w（28维列向量）为：\n" );
	 for (i = 0; i <  feature_SIZE; i++)
    {
		
		fprintf( fpweight ,"%.8f\t",w[i]); // 打印training数据}
		
    }
	fclose(fpweight);
   fpweight = NULL; //需要指向空，否则会指向原打开文件地址
   printf("权重系数w，最佳参数β和λ已保存至weight_and_parameter.txt文档中\n\n");

	
}
void computeRespectively(double LAmda,double BEta)
{
	int i;
	double wt[feature_SIZE] ;  //存放w向量的前一次迭代结果
	double lossValue=0;         //lossfunction的值
	double eplise = 0;          //两次迭代得到的w的变化大小

	for(i=0;i<feature_SIZE;i++) //feature_SIZE是特征向量的长度
	{
		w[i] = 0.1;             //权重初始为[0.1,0.1...0.1]
	}
	
	//设置终止条件
	while(lossValue<1e-10 || eplise <1e-10 )//两次之间w的变化很小 或者lossvalue本身的值很小
	{
		eplise =0;
		 for(i=0;i<feature_SIZE;i++) //feature_SIZE是特征向量的长度
		{
			wt[i] = w[i];                 //存放w向量的前一次迭代结果
		}
		
		lossValue = lossFunction( LAmda,BEta);//计算loss function的值
		updateW( LAmda,BEta);		//更新w
		//计算更新前后的变化大小
		 for(i=0;i<feature_SIZE;i++) //feature_SIZE是特征向量的长度
		{
			eplise =eplise+ fabs((wt[i] - w[i])); //计算更新前后的变化大小
		}  
	}
}
double lossFunction(double Lamda,double Beta)
{//计算lossfunction的值
	int i,j;
	double fxi,lossSum,weigh2Sum;           //f(xi) 、 lossFunction、w平方的值 
	
	lossSum = 0;      //loss function的值                     
	weigh2Sum = 0;    //存放 w的平方 的值
	for(i= 0;i<feature_SIZE;i++) //feature_SIZE是特征向量的长度
	{
		weigh2Sum = weigh2Sum +w[i]*w[i];//计算 wi的平方累加后 的值
	}
	for(i=0;i<lenTraining;i++)
	{
		  fxi = 0;
          for(j=0;j<feature_SIZE;j++) //feature_SIZE是特征向量的长度
		  {
			  fxi = fxi + w[j]*trainingFeatureVector[i][j];		//计算f(xi)
		  }
    lossSum = lossSum +(fxi-traininglabel[i])*(fxi-traininglabel[i]); //得到loss function的值 
	}
	lossSum = lossSum/lenTraining + Lamda*weigh2Sum;
	return lossSum;//返回得到的loss function的值 
}
void updateW(double Lamda,double Beta)
{  //更新w的权重
	int i,j,k;
	double fxi;                 //f(xi)的值
	double errorSum;           //f(xi)-yi的值，之后用来表示梯度 

	for(k=0;k<feature_SIZE;k++) //feature_SIZE是特征向量的长度
	{
		errorSum = 0;
        for(i=0;i<lenTraining;i++)
		{
		   fxi = 0;
           for(j=0;j<feature_SIZE;j++)
		   {
			  fxi = fxi + w[j]*trainingFeatureVector[i][j];		//计算f(xi)
		   }
		   errorSum = errorSum +trainingFeatureVector[i][k]*(fxi-traininglabel[i]);
		}
	    errorSum = -2*errorSum/lenTraining + 2*Lamda*w[k];  //计算得到梯度
		w[k] = w[k]+ Beta*errorSum ;						//更新w
		
	}
}
double  ValidationAccuracytest()
{//计算验证集上的准确率
	int i,j;
	double accuracy=0,count=0;   
	double fxi;
	int testValidationlabel[MAX_DATA_SIZE];								//测得验证集标签
	memset(	testValidationlabel,0,sizeof(testValidationlabel));    //初始化测试结果的标签
	//使用线性函数预测label
	for(i=0;i<lenTraining;i++)
	{
		  fxi = 0;
          for(j=0;j<feature_SIZE;j++)
		  {
			  fxi = fxi + w[j]*ValidationFeatureVector[i][j];		//计算f(xi)
		  }
   testValidationlabel[i]=(int)(fxi+0.5)>(int)fxi?(int)fxi+1:(int)fxi;//对f(xi)的值进行四舍五入

	}

	for(i=0;i<lenValidation;i++ )
	{
		if(testValidationlabel[i] == Validationlabel[i]) //如果预测正确,则count加1
			count++;
	}
	accuracy = count/(double)lenValidation;  //得到正确率
	return accuracy;    // 返回得到的正确率
}

void computeFull(double LAmda,double BEta)
{
	int i;
	double wt[feature_SIZE] ;  //存放w向量的前一次迭代结果
	double lossValue=0;         //lossfunction的值
	double eplise = 0;          //两次迭代得到的w的变化大小

	for(i=0;i<feature_SIZE;i++) //feature_SIZE是特征向量的长度
	{
		w[i] = 0.1;             //权重初始为[0.1,0.1...0.1]
	}
	
	//设置终止条件
	while(lossValue<1e-10 || eplise <1e-10 )//两次之间w的变化很小 或者lossvalue本身的值很小
	{
		eplise =0;
		 for(i=0;i<feature_SIZE;i++) //feature_SIZE是特征向量的长度
		{
			wt[i] = w[i];                 //存放w向量的前一次迭代结果
		}
		
		lossValue = lossFunctionFull( LAmda,BEta);//计算loss function的值
		updateWFull( LAmda,BEta);		//更新w
		//计算更新前后的变化大小
		 for(i=0;i<feature_SIZE;i++) //feature_SIZE是特征向量的长度
		{
			eplise =eplise+ fabs((wt[i] - w[i])); //计算更新前后的变化大小
		}  
	}
}
double lossFunctionFull(double Lamda,double Beta)
{//计算lossfunction的值
	int i,j;
	double fxi,lossSum,weigh2Sum;           //f(xi) 、 lossFunction、w平方的值 
	
	lossSum = 0;      //loss function的值                     
	weigh2Sum = 0;    //存放 w的平方 的值
	for(i= 0;i<feature_SIZE;i++) //feature_SIZE是特征向量的长度
	{
		weigh2Sum = weigh2Sum +w[i]*w[i];//计算 wi的平方累加后 的值
	}
	for(i=0;i<trainRealNumRow;i++)
	{
		  fxi = 0;
          for(j=0;j<feature_SIZE;j++) //feature_SIZE是特征向量的长度
		  {
			  fxi = fxi + w[j]*trainFeatureVector[i][j];		//计算f(xi)
		  }
    lossSum = lossSum +(fxi-label[i])*(fxi-label[i]); //得到loss function的值 
	}
	lossSum = lossSum/trainRealNumRow + Lamda*weigh2Sum;
	return lossSum;//返回得到的loss function的值 
}
void updateWFull(double Lamda,double Beta)
{  //更新w的权重
	int i,j,k;
	double fxi;                 //f(xi)的值
	double errorSum;           //f(xi)-yi的值，之后用来表示梯度 

	for(k=0;k<feature_SIZE;k++) //feature_SIZE是特征向量的长度
	{
		errorSum = 0;
        for(i=0;i<trainRealNumRow;i++)
		{
		   fxi = 0;
           for(j=0;j<feature_SIZE;j++)
		   {
			  fxi = fxi + w[j]*trainFeatureVector[i][j];		//计算f(xi)
		   }
		   errorSum = errorSum +trainFeatureVector[i][k]*(fxi-label[i]);
		}
	    errorSum = -2*errorSum/trainRealNumRow + 2*Lamda*w[k];  //计算得到梯度
		w[k] = w[k]+ Beta*errorSum ;						//更新w
		
	}
}


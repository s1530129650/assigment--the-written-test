#define _CRT_SECURE_NO_WARNINGS
#include"Datapreprocessing.h"
typedef struct{
	 double weight;
     int parent,lchild,rchild;
}HTNode;  //赫夫曼树结构  weight结点的权重，parent,lchild,rchild分别是父母结点和左右孩子节点，注意lchild的权重小于rchlid的权重




int getAttriRespectively(char init[MAX_DATA_SIZE][MAX_char_SIZE],char treat[MAX_kind_SIZE][MAX_char_SIZE] ,double overrate[MAX_kind_SIZE]);//分别处理各个属性,类别和长度
void oneHotEncodeRespectively(char init[MAX_DATA_SIZE][MAX_char_SIZE],char mask[MAX_kind_SIZE][MAX_char_SIZE],int count,int encode[MAX_DATA_SIZE][MAX_encode_SIZE]);//对各个属性独立编码
void HuffmanCodingRespectively(HTNode HT[],char init[MAX_DATA_SIZE][MAX_char_SIZE],int encode[MAX_DATA_SIZE][MAX_encode_SIZE],double weight[],int count,char Alpha[MAX_kind_SIZE][MAX_char_SIZE]);//霍夫曼编码
void normalizationrespectively(double data[],double dataencode[]);//分别对数据进行归一化
void encodeText2numRespectively(int length,char text[MAX_DATA_SIZE][MAX_char_SIZE],int data2number[MAX_DATA_SIZE][MAX_encode_SIZE],
								char mask[MAX_DATA_SIZE][MAX_char_SIZE],int maskcode[MAX_DATA_SIZE][MAX_encode_SIZE]);//各个属性文本与数字编码之间的编码
void getAttriNum()//得到各个属性的种类以及种类数
{
	int t;
	//统计workclass的情况
	trainAttriTextData.lenWorkclass=getAttriRespectively(trainDATA.workclass,trainAttriTextData.workclass,trainover50Rate.rateWorkclass); //统计workclass的情况
	
    printf("workclass有%d种，分别是： \n",trainAttriTextData.lenWorkclass);
	for(t=0;t<trainAttriTextData.lenWorkclass;t++)
	{
		trainover50Rate.rateWorkclass[t] = trainover50Rate.rateWorkclass[t]/trainRealNumRow;
		printf("%s\t\t\t label over50k的占 %.4f\n",trainAttriTextData.workclass[t],trainover50Rate.rateWorkclass[t]);
	}
	printf("\n");
	
	//统计education的情况
	trainAttriTextData.lenEducation=getAttriRespectively(trainDATA.education,trainAttriTextData.education,trainover50Rate.rateEducation); //统计workclass的情况
	
    printf("education有%d种，分别是：    \n",trainAttriTextData.lenEducation);
	for(t=0;t<trainAttriTextData.lenEducation;t++)
	{
		trainover50Rate.rateEducation[t] = trainover50Rate.rateEducation[t]/trainRealNumRow;
		printf("%s\t\t\t label over50k的占 %.4f\n",trainAttriTextData.education[t],trainover50Rate.rateEducation[t]);
	}
	printf("\n");
	
	//统计maritalStatus的情况
	trainAttriTextData.lenMaritalStatus=getAttriRespectively(trainDATA.maritalStatus,trainAttriTextData.maritalStatus,trainover50Rate.rateMaritalStatus); //统计workclass的情况
	
    printf("maritalStatus有%d种，    \n",trainAttriTextData.lenMaritalStatus);
	for(t=0;t<trainAttriTextData.lenMaritalStatus;t++)
	{
		trainover50Rate.rateMaritalStatus[t] = trainover50Rate.rateMaritalStatus[t]/trainRealNumRow;
		//printf("%s\t\t\t label over50k的占%.4f\n",trainAttriTextData.maritalStatus[t],trainover50Rate.rateMaritalStatus[t]);
	}
	printf("\n");
	
	
	//统计 occupation的情况
	trainAttriTextData.lenOccupation =getAttriRespectively(trainDATA.occupation,trainAttriTextData.occupation,trainover50Rate.rateOccupation); //统计workclass的情况
	
    printf("occupation有%d种    \n",trainAttriTextData.lenOccupation);
	for(t=0;t<trainAttriTextData.lenOccupation;t++)
	{
		trainover50Rate.rateOccupation[t] = trainover50Rate.rateOccupation[t]/trainRealNumRow;
		//printf("%s\n",trainAttriTextData.occupation[t]);
	}
	printf("\n");
	

	//统计 relationship的情况
	trainAttriTextData.lenRelationship =getAttriRespectively(trainDATA.relationship,trainAttriTextData.relationship,trainover50Rate.rateRelationship); //统计workclass的情况
	
    printf("relationship有%d种   \n",trainAttriTextData.lenRelationship);
	for(t=0;t<trainAttriTextData.lenRelationship;t++)
	{
		trainover50Rate.rateRelationship[t] = trainover50Rate.rateRelationship[t]/trainRealNumRow;
		//printf("%s\n",trainAttriTextData.relationship[t]);
	}
	printf("\n");
	

	//统计 race的情况
	trainAttriTextData.lenRace =getAttriRespectively(trainDATA.race,trainAttriTextData.race,trainover50Rate.rateRace); //统计workclass的情况
	
    printf("race有%d种 \n",trainAttriTextData.lenRace);
	for(t=0;t<trainAttriTextData.lenRace;t++)
	{
		trainover50Rate.rateRace[t] = trainover50Rate.rateRace[t]/trainRealNumRow;
		//printf("%s\n",trainAttriTextData.race[t]);
	}
	printf("\n");
	

	//统计 sex的情况
	trainAttriTextData.lenSex =getAttriRespectively(trainDATA.sex,trainAttriTextData.sex,trainover50Rate.rateSex); //统计workclass的情况
	
    printf("race有%d种 \n",trainAttriTextData.lenSex);
	for(t=0;t<trainAttriTextData.lenSex;t++)
	{
		trainover50Rate.rateSex[t] = trainover50Rate.rateSex[t]/trainRealNumRow;
		//printf("%s\n",trainAttriTextData.sex[t]);
	}
	printf("\n");
	

	//统计nativeCountry的情况
	trainAttriTextData.lenNativeCountry =getAttriRespectively(trainDATA.nativeCountry,trainAttriTextData.nativeCountry,trainover50Rate.rateNativeCountry); //统计workclass的情况
	
    printf("nativeCountry有%d种  \n",trainAttriTextData.lenNativeCountry);
	for(t=0;t<trainAttriTextData.lenNativeCountry;t++)
	{
		trainover50Rate.rateNativeCountry[t] = trainover50Rate.rateNativeCountry[t]/trainRealNumRow;
		//printf("%s\n",trainAttriTextData.nativeCountry[t]);
	}
	printf("\n");
	
}  
int getAttriRespectively(char init[MAX_DATA_SIZE][MAX_char_SIZE],char treat[MAX_kind_SIZE][MAX_char_SIZE] ,double overrate[MAX_kind_SIZE] ) //分别处理各个属性,类别和长度
{//以workclass为例 init代表从csv里读取的原始数据，treat是要 求得的workclass的种类个数；overrate是各个种类收入50k的比例
	//返回值为k
	int i,j,k=1;
	strcpy(treat[0],init[0]);//保存第一个种类
	overrate[0] = 1;
    for(i=1;i<trainRealNumRow;i++)
    {
    	for(j=0;j<k;j++)
    	{
    		if(strcmp(init[i],treat[j]) == 0)  //如果以后出现的种类与之前的种类不重复则保存，则保存此种类
    		{
				if(label[i]>0)
					{overrate[j]=overrate[j]+1;} //为了后续的霍夫曼-one hot编码 统计属性中各个类别的label大于50k的总数，
    			break;
			}
		}
		if(j>=k)              //k是目前的种类数，j>k 表明此种类与之前未出现，应该保存
		{   overrate[j] =0;
		    if(label[i]>0)
			{overrate[j]=overrate[j]+1; }  //统计属性中各个类别的label大于50k的总数
			strcpy(treat[k],init[i]);      //将此种类加入到种类集里
			k++;	
		}
		
	}
	return k;   //返回种类个数
}
void oneHotEncode() //得到各个属性的onehot编码  事实上我们只有sex用这个处理
{
	int i,j;
	
	//得到sex的one-hot编码 sex 只有两类编码很简单 male为10 female是01
	oneHotEncodeRespectively(trainDATA.sex,trainAttriTextData.sex,trainAttriTextData.lenSex,trainDataEncode.encodeSex);
	
	printf("sex的one-hot编码为：(以前八个为例)\n");
	for ( i = 0; i < 8; i++ )
	{
		printf( "%s:\t", trainDATA.sex[i] );
		for(j=0;j<trainAttriTextData.lenSex;j++)
      	  {
			  
			printf( "%d ", trainDataEncode.encodeSex[i][j] ); 
     		
	 		 }
  		printf("\n");
	} 
	printf("\n");//for test 
	
}
void oneHotEncodeRespectively(char init[MAX_DATA_SIZE][MAX_char_SIZE],char mask[MAX_kind_SIZE][MAX_char_SIZE],int count,int encode[MAX_DATA_SIZE][MAX_encode_SIZE]) //对各个属性独立编码
{ //对各个属性独立编码，以workclass为例 ，init代表从csv里读取的原始数据；mask就是之前得到的workclass种类个数，count是实际数据长度，encode是init的编码
	int i,j;

		for(i=0;i<trainRealNumRow;i++)
	{
		for(j=0;j<count;j++)
		{    encode[i][j] = 0;
			if(strcmp(mask[j],init[i]) == 0)  
		 		encode[i][j]=1;
		}	

	}
}

void HuffmanCoding() //得到各个属性的霍夫曼-onehot编码
{//我们借助霍夫曼给权重大的字符短的编码的特性，将编码长度差不多的数据归为一类，依此编码
	int i,j;
	HTNode tree[2*MAX_kind_SIZE-1];    //霍夫曼数的初始化
    
	//workclass的霍夫曼-onehot编码
	memset(tree,0,sizeof(tree));
	
	memset(trainDataEncode.encodeWorkclass,0,sizeof(trainDataEncode.encodeWorkclass));//初始化为0
	HuffmanCodingRespectively(tree,trainDATA.workclass,trainDataEncode.encodeWorkclass , trainover50Rate.rateWorkclass, trainAttriTextData.lenWorkclass, trainAttriTextData.workclass);
	
	printf("workclass的等长霍夫曼-onehot编码：（以前8个为例）    \n");
	for ( i = 0; i < 8; i++ )
	{
		for(j=0;j<MAX_encode_SIZE;j++)
      	  {
			printf( "%d ", trainDataEncode.encodeWorkclass[i][j] ); 
     		
	 		 }
  		printf("\n");
	}

	//Education的霍夫曼-onehot编码
	memset(tree,0,sizeof(tree));
	memset(trainDataEncode.encodeEducation,0,sizeof(trainDataEncode.encodeEducation));
	HuffmanCodingRespectively(tree,trainDATA.education,trainDataEncode.encodeEducation , trainover50Rate.rateEducation, trainAttriTextData.lenEducation, trainAttriTextData.education);
	/*printf("Education的等长霍夫曼-onehot编码：（以前8个为例）    \n");
	for ( i = 0; i < 8; i++ )
	{
		for(j=0;j<MAX_encode_SIZE;j++)
      	  {
			printf( "%d ", trainDataEncode.encodeEducation[i][j] ); 
     		
	 		 }
  		printf("\n");
	}*/

	//maritalStatus的霍夫曼-onehot编码
	memset(tree,0,sizeof(tree));
	memset(trainDataEncode.encodeMaritalStatus,0,sizeof(trainDataEncode.encodeMaritalStatus));
	HuffmanCodingRespectively(tree,trainDATA.maritalStatus,trainDataEncode.encodeMaritalStatus , trainover50Rate.rateMaritalStatus, trainAttriTextData.lenMaritalStatus, trainAttriTextData.maritalStatus);
	/*printf("maritalStatus的等长霍夫曼-onehot编码：（以前8个为例）    \n");
	for ( i = 0; i < 8; i++ )
	{
		for(j=0;j<MAX_encode_SIZE;j++)
      	  {
			printf( "%d ", trainDataEncode.encodeMaritalStatus[i][j] ); 
     		
	 		 }
  		printf("\n");
	}*/

	//occupation的霍夫曼-onehot编码
	memset(tree,0,sizeof(tree));
	memset(trainDataEncode.encodeOccupation,0,sizeof(trainDataEncode.encodeOccupation));
	HuffmanCodingRespectively(tree,trainDATA.occupation,trainDataEncode.encodeOccupation , trainover50Rate.rateOccupation, trainAttriTextData.lenOccupation, trainAttriTextData.occupation);
	/*printf("occupation的等长霍夫曼-onehot编码：（以前8个为例）    \n");
	for ( i = 0; i < 8; i++ )
	{
		for(j=0;j<MAX_encode_SIZE;j++)
      	  {
			printf( "%d ", trainDataEncode.encodeOccupation[i][j] ); 
     		
	 		 }
  		printf("\n");
	 }*/

   //relationship的霍夫曼-onehot编码
	memset(tree,0,sizeof(tree));
	memset(trainDataEncode.encodeRelationship,0,sizeof(trainDataEncode.encodeRelationship));
	HuffmanCodingRespectively(tree,trainDATA.relationship,trainDataEncode.encodeRelationship , trainover50Rate.rateRelationship, trainAttriTextData.lenRelationship, trainAttriTextData.relationship);
	/*printf("relationship的等长霍夫曼-onehot编码：（以前8个为例）    \n");
	for ( i = 0; i < 8; i++ )
	{
		for(j=0;j<MAX_encode_SIZE;j++)
      	  {
			printf( "%d ", trainDataEncode.encodeRelationship[i][j] ); 
     		
	 		 }
  		printf("\n");
	}*/

	//race的霍夫曼-onehot编码
	memset(tree,0,sizeof(tree));
	memset(trainDataEncode.encodeRace,0,sizeof(trainDataEncode.encodeRace));
	HuffmanCodingRespectively(tree,trainDATA.race,trainDataEncode.encodeRace , trainover50Rate.rateRace, trainAttriTextData.lenRace, trainAttriTextData.race);
	/* printf("race的等长霍夫曼-onehot编码：（以前8个为例）    \n");
	for ( i = 0; i < 8; i++ )
	{
		for(j=0;j<MAX_encode_SIZE;j++)
      	  {
			printf( "%d ", trainDataEncode.encodeRace[i][j] ); 
     		
	 		 }
  		printf("\n");
	}*/

	//nativeCountry的霍夫曼-onehot编码
	memset(tree,0,sizeof(tree));
	memset(trainDataEncode.encodeNativeCountry,0,sizeof(trainDataEncode.encodeNativeCountry));
	HuffmanCodingRespectively(tree,trainDATA.nativeCountry,trainDataEncode.encodeNativeCountry , trainover50Rate.rateNativeCountry, trainAttriTextData.lenNativeCountry, trainAttriTextData.nativeCountry);
	/* printf("nativeCountry的等长霍夫曼-onehot编码：（以前8个为例）    \n");
	for ( i = 0; i < 8; i++ )
	{
		for(j=0;j<MAX_encode_SIZE;j++)
      	  {
			printf( "%d ", trainDataEncode.encodeNativeCountry[i][j] ); 
     		
	 		 }
  		printf("\n");
	}*/

}

void HuffmanCodingRespectively(HTNode HT[],char init[MAX_DATA_SIZE][MAX_char_SIZE],int encode[MAX_DATA_SIZE][MAX_encode_SIZE],double weight[],int count,char mask[MAX_kind_SIZE][MAX_char_SIZE])
{
	//HT为霍夫曼树 init为某属性下所有类别原始数据 encode为霍夫曼下的独热编码 weight为每个字符出现的频率、权重 count为此属性下类别的总数，ALpha即为此属性下的所有类别
	double HC[2*MAX_kind_SIZE-1]={0};   //存放每个节点的编码
	int m,i,j,c,f;
    int s1,s2;
	double m1,m2;
	if( count<=1) return ;
	m=2* count-1;
		
	for(i=1;i<= count;++i) 
	{HT[i].weight=weight[i-1];
	
	}
	for(i= count+1;i<=m;++i){                         //构建赫夫曼树
	  
	   s1=s2=0;m1=m2=3;
	   for(j=1;j<i;++j)
	   {
		   if(HT[j].parent==0&&HT[j].weight<m1)    //权值小的为左节点，权值大的为右节点
		   {m2=m1;s2=s1;m1=HT[j].weight;s1=j;}
		   else if(HT[j].weight<m2&&HT[j].parent==0)   
		   {m2=HT[j].weight;s2=j;}
	   }
	   HT[s1].parent=i;HT[s2].parent=i; //将权值较小的两个节点权重相加，称为其父母节点的权重
	   HT[i].lchild=s1;HT[i].rchild=s2;
	   HT[i].weight=HT[s1].weight+HT[s2].weight;
	 
	}//构建完成
	//从叶子到根逆向求每个字符的赫夫曼编码
	for(i=1;i<= count;++i){
		for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent)
		{
			if(HT[f].lchild==c) 
				HC[i-1] = HC[i-1]+1.1;//权值小的为左节点，权值大的为右节点,因此我们给右节点较小的权重
			else 
				HC[i-1] = HC[i-1]+1;
		}	
		
		
	}
   //一下就类似于onehot编码，因为我们只分了三类，因此每一类对应一种编码分别为[1 0 0 ]、[0 1 0 ]、[0 0 1]。
	for(i=0;i< trainRealNumRow;i++)
	{
		for(j=0;j<count;j++)
		{
			if(strcmp(init[i],mask[j]) == 0) 
			{
				if(HC[j] <= 2)            //总权值不大于于2的编码为[1 0 0]
                  encode[i][0]=1; 
			    else
					{
						if(HC[j] <= 4 )    //总权值大于2小于4的编码为[0 1 0]
							encode[i][1]=1;
						else 
							encode[i][2]=1; //总权值大于4的编码为[0 0 1]
					}
				break;
			}
		}
	}
}//HuffmanTree

void normalization() //对数字数据进行归一化
{
	int i;

	//对age进行归一化
    normalizationrespectively(trainDATA.age,trainDataEncode.age);
	printf("\n");
	printf("对age进行归一化后的数据为：(以前八个为例)\n");
	for ( i = 0; i < 8; i++ )
	{	
		printf( "%.4f\t",trainDataEncode.age[i] ); 
	} 
	printf("\n");
	printf("\n");
	//for test 


	//对educationNum进行归一化
	//printf("educationNum的");
    normalizationrespectively(trainDATA.educationNum,trainDataEncode.educationNum);
	/*printf("\n");
	printf("对educationNum进行归一化后的数据为：(以前八个为例)\n");
	for ( i = 0; i < 8; i++ )
	{	
		printf( "%.4f\t",trainDataEncode.educationNum[i] ); // a[ 0 ] 才是第一行
	} 
	printf("\n");//for test 
	*/

	//对capitalGain进行归一化
	//printf("capitalGain的");
    normalizationrespectively(trainDATA.capitalGain,trainDataEncode.capitalGain);
	/*printf("\n");
	printf("对capitalGaine进行归一化后的数据为：(以前八个为例)\n");
	for ( i = 0; i < 8; i++ )
	{	
		printf( "%.4f\t",trainDataEncode.capitalGain[i] ); // a[ 0 ] 才是第一行
	} 
	printf("\n");//for test 
	*/

	//对capitalLoss进行归一化
	//printf("capitalLoss的");
    normalizationrespectively(trainDATA.capitalLoss,trainDataEncode.capitalLoss);
	/*printf("\n");
	printf("对capitalLoss进行归一化后的数据为：(以前八个为例)\n");
	for ( i = 0; i < 8; i++ )
	{	
		printf( "%.4f\t",trainDataEncode.capitalLoss[i] ); // a[ 0 ] 才是第一行
	} 
	printf("\n");//for test 
	*/

    //对hoursPerWeek进行归一化
	//printf("hoursPerWeek的");
    normalizationrespectively(trainDATA.hoursPerWeek,trainDataEncode.hoursPerWeek);
	/*printf("\n");
	printf("对hoursPerWeek进行归一化后的数据为：(以前八个为例)\n");
	for ( i = 0; i < 8; i++ )
	{	
		printf( "%.4f\t",trainDataEncode.hoursPerWeek[i] ); // a[ 0 ] 才是第一行
	} 
	printf("\n");//for test 
	*/
	 
}

void normalizationrespectively(double data[],double dataencode[])
{//对数据进行归一化， data[]是归一化前的数据，dataencode[]是归一化到[0,1]的数据
	double maxtemp=0,mintemp=100;
	int i;
	//求出最大值//求出最小值
	for(i=0;i< trainRealNumRow ;i++)
	{
		maxtemp = (data[i] > maxtemp? data[i] : maxtemp);		//求出最大值
		mintemp = (data[i] < mintemp? data[i] : mintemp);		//求出最小值
		
	}
	//printf("最大值为 %.4f   最小值是%.4f\n",maxtemp,mintemp);
	for(i=0;i< trainRealNumRow ;i++)
	{
		dataencode[i] = (data[i]-mintemp)/(maxtemp-mintemp); //归一化到[0,1]
	}	
}

void  getfeatureVector()//得到特征向量
{

	int i,j;
	memset(	trainFeatureVector,0,sizeof(	trainFeatureVector));		 //初始化特征向量
	for (i=0;i< trainRealNumRow ;i++)
	{
		trainFeatureVector[i][0] = trainDataEncode.age[i];               //将各个属性的值合并到一起得到特征向量
		for(j=1;j<4;j++)
			trainFeatureVector[i][j] = trainDataEncode.encodeWorkclass[i][j-1];
		for(j=1;j<4;j++)
			trainFeatureVector[i][j+3] = trainDataEncode.encodeEducation[i][j-1];
		trainFeatureVector[i][7] = trainDataEncode.educationNum[i];
		for(j=1;j<4;j++)
			trainFeatureVector[i][j+7] = trainDataEncode.encodeMaritalStatus[i][j-1];
		for(j=1;j<4;j++)
			trainFeatureVector[i][j+10] = trainDataEncode.encodeOccupation[i][j-1];
		for(j=1;j<4;j++)
			trainFeatureVector[i][j+13] = trainDataEncode.encodeRelationship[i][j-1];
		for(j=1;j<4;j++)
			trainFeatureVector[i][j+16] = trainDataEncode.encodeRace[i][j-1];
		for(j=1;j<3;j++)
			trainFeatureVector[i][j+19] = trainDataEncode.encodeSex[i][j-1];
		trainFeatureVector[i][22] = trainDataEncode.capitalGain[i];
		trainFeatureVector[i][23] = trainDataEncode.capitalLoss[i];
		trainFeatureVector[i][24] = trainDataEncode.hoursPerWeek[i];
		for(j=1;j<3;j++)
			trainFeatureVector[i][j+24] = trainDataEncode.encodeNativeCountry[i][j-1];
	}
	printf("得到的特征向量(28维)为：（以前3个为例）\n");
	for ( i = 0; i <3; i++ )
	{
		for(j=0;j<feature_SIZE;j++)
			printf( "%.2f ", trainFeatureVector[i][j] ); 	
			printf("\n");
	}
	printf("\n");
	
}

void saveText2num()	//保存文本与数字编码之间的对应转换
{
	int i,j,k;
	
	//workclass的文本与数字编码对应
	printf("workclass的编码对应关系为：\n");
	for(i=0;i<trainAttriTextData.lenWorkclass;i++)
	{
		strcpy(Text2Num.workclass[i],trainAttriTextData.workclass[i]);//初始化workplace 存储文本的种类
	}
	for(i=0;i<trainNumRow;i++)
	{  
		for(k=0;k<trainAttriTextData.lenWorkclass;k++)
		{
				if(strcmp(Text2Num.workclass[k],trainDATA.workclass[i])==0)
				{
					for(j=0;j<MAX_encode_SIZE;j++)
					{Text2Num.encodeWorkclass[k][j] = trainDataEncode.encodeWorkclass[i][j];}//储存文本与数字编码之间的对应关系
				}
		}
	}
	//for test
	for(i=0;i<trainAttriTextData.lenWorkclass;i++)
	{
		printf("%s:\t",Text2Num.workclass[i]);
		for(j=0;j<MAX_encode_SIZE;j++)
		{
			printf("%d\t",Text2Num.encodeWorkclass[i][j] );
		}
		printf("\n");
	}
	printf("\n");

	//Education的文本与数字编码对应
	
	for(i=0;i<trainAttriTextData.lenEducation;i++)
	{
		strcpy(Text2Num.education[i],trainAttriTextData.education[i]);//初始化workplace 存储文本的种类
	}
	for(i=0;i<trainNumRow;i++)
	{    
		
		for(k=0;k<trainAttriTextData.lenEducation;k++)
		{
				if(strcmp(Text2Num.education[k],trainDATA.education[i])==0)
				{
					
					for(j=0;j<MAX_encode_SIZE;j++)
					{Text2Num.encodeEducation[k][j] = trainDataEncode.encodeEducation[i][j];}//储存文本与数字编码之间的对应关系
				}
		}
	}
	/*
	printf("Education的编码对应关系为：\n");	
	for(i=0;i<trainAttriTextData.lenEducation;i++)
	{
		printf("%s:\t",Text2Num.education[i]);
		for(j=0;j<MAX_encode_SIZE;j++)
		{
			printf("%d\t",Text2Num.encodeEducation[i][j] );
		}
		printf("\n");
	}
	printf("\n");*/

	//maritalStatus的文本与数字编码对应
	for(i=0;i<trainAttriTextData.lenMaritalStatus;i++)
	{
		strcpy(Text2Num.maritalStatus[i],trainAttriTextData.maritalStatus[i]);//初始化workplace 存储文本的种类
	}
	for(i=0;i<trainNumRow;i++)
	{    
		
		for(k=0;k<trainAttriTextData.lenMaritalStatus;k++)
		{
				if(strcmp(Text2Num.maritalStatus[k],trainDATA.maritalStatus[i])==0)
				{
					
					for(j=0;j<MAX_encode_SIZE;j++)
					{Text2Num.encodeMaritalStatus[k][j] = trainDataEncode.encodeMaritalStatus[i][j];}//储存文本与数字编码之间的对应关系
				}
		}
	}
	/*
	printf("maritalStatus的编码对应关系为：\n");	
	for(i=0;i<trainAttriTextData.lenMaritalStatus;i++)
	{
		printf("%s:\t",Text2Num.maritalStatus[i]);
		for(j=0;j<MAX_encode_SIZE;j++)
		{
			printf("%d\t",Text2Num.encodeMaritalStatus[i][j] );
		}
		printf("\n");
	}
	printf("\n");
	*/

	//occupation的文本与数字编码对应
	for(i=0;i<trainAttriTextData.lenOccupation;i++)
	{
		strcpy(Text2Num.occupation[i],trainAttriTextData.occupation[i]);//初始化workplace 存储文本的种类
	}
	for(i=0;i<trainNumRow;i++)
	{    
		
		for(k=0;k<trainAttriTextData.lenOccupation;k++)
		{
				if(strcmp(Text2Num.occupation[k],trainDATA.occupation[i])==0)
				{
					
					for(j=0;j<MAX_encode_SIZE;j++)
					{Text2Num.encodeOccupation[k][j] = trainDataEncode.encodeOccupation[i][j];}//储存文本与数字编码之间的对应关系
				}
		}
	}
	/*
	printf("occupation的编码对应关系为：\n");	
	for(i=0;i<trainAttriTextData.lenOccupation;i++)
	{
		printf("%s:\t",Text2Num.occupation[i]);
		for(j=0;j<MAX_encode_SIZE;j++)
		{
			printf("%d\t",Text2Num.encodeOccupation[i][j] );
		}
		printf("\n");
	}
	printf("\n");*/

	//relationship的文本与数字编码对应
	for(i=0;i<trainAttriTextData.lenRelationship;i++)
	{
		strcpy(Text2Num.relationship[i],trainAttriTextData.relationship[i]);//初始化workplace 存储文本的种类
	}
	for(i=0;i<trainNumRow;i++)
	{    
		
		for(k=0;k<trainAttriTextData.lenRelationship;k++)
		{
				if(strcmp(Text2Num.relationship[k],trainDATA.relationship[i])==0)
				{
					
					for(j=0;j<MAX_encode_SIZE;j++)
					{Text2Num.encodeRelationship[k][j] = trainDataEncode.encodeRelationship[i][j];}//储存文本与数字编码之间的对应关系
				}
		}
	}
	/*
	printf("relationship的编码对应关系为：\n");	
	for(i=0;i<trainAttriTextData.lenRelationship;i++)
	{
		printf("%s:\t",Text2Num.relationship[i]);
		for(j=0;j<MAX_encode_SIZE;j++)
		{
			printf("%d\t",Text2Num.encodeRelationship[i][j] );
		}
		printf("\n");
	}
	printf("\n");*/


	//race的文本与数字编码对应
	for(i=0;i<trainAttriTextData.lenRace;i++)
	{
		strcpy(Text2Num.race[i],trainAttriTextData.race[i]);//初始化workplace 存储文本的种类
	}
	for(i=0;i<trainNumRow;i++)
	{    
		
		for(k=0;k<trainAttriTextData.lenRace;k++)
		{
				if(strcmp(Text2Num.race[k],trainDATA.race[i])==0)
				{
					
					for(j=0;j<MAX_encode_SIZE;j++)
					{Text2Num.encodeRace[k][j] = trainDataEncode.encodeRace[i][j];}//储存文本与数字编码之间的对应关系
				}
		}
	}
	
	printf("race的编码对应关系为：\n");	
	for(i=0;i<trainAttriTextData.lenRace;i++)
	{
		printf("%s:\t",Text2Num.race[i]);
		for(j=0;j<MAX_encode_SIZE;j++)
		{
			printf("%d\t",Text2Num.encodeRace[i][j] );
		}
		printf("\n");
	}
	printf("\n");

  //nativeCountry的文本与数字编码对应
	for(i=0;i<trainAttriTextData.lenNativeCountry;i++)
	{
		strcpy(Text2Num.nativeCountry[i],trainAttriTextData.nativeCountry[i]);//初始化workplace 存储文本的种类
	}
	for(i=0;i<trainNumRow;i++)
	{    
		
		for(k=0;k<trainAttriTextData.lenNativeCountry;k++)
		{
				if(strcmp(Text2Num.nativeCountry[k],trainDATA.nativeCountry[i])==0)
				{
					
					for(j=0;j<MAX_encode_SIZE;j++)
					{Text2Num.encodeNativeCountry[k][j] = trainDataEncode.encodeNativeCountry[i][j];}//储存文本与数字编码之间的对应关系
				}
		}
	}
	/*
	printf("nativeCountry的编码对应关系为：\n");	
	for(i=0;i<trainAttriTextData.lenNativeCountry;i++)
	{
		printf("%s:\t",Text2Num.nativeCountry[i]);
		for(j=0;j<MAX_encode_SIZE;j++)
		{
			printf("%d\t",Text2Num.encodeNativeCountry[i][j] );
		}
		printf("\n");
	}
	printf("\n");*/

}

void encodeText2num()//属性文本与数字编码之间的编码,用于测试集
{
	int i,j;
	//对workclass进行编码
	memset(trainDataEncode.encodeWorkclass,0,sizeof(trainDataEncode.encodeWorkclass));
	encodeText2numRespectively(trainAttriTextData.lenWorkclass,trainDATA.workclass,trainDataEncode.encodeWorkclass,Text2Num.workclass,Text2Num.encodeWorkclass);
	//对Education进行编码
	memset(trainDataEncode.encodeEducation,0,sizeof(trainDataEncode.encodeEducation));
	encodeText2numRespectively(trainAttriTextData.lenEducation,trainDATA.education,trainDataEncode.encodeEducation,Text2Num.education,Text2Num.encodeEducation);
	//对maritalStatus进行编码
	memset(trainDataEncode.encodeMaritalStatus,0,sizeof(trainDataEncode.encodeMaritalStatus));
	encodeText2numRespectively(trainAttriTextData.lenMaritalStatus,trainDATA.maritalStatus,trainDataEncode.encodeMaritalStatus,Text2Num.maritalStatus,Text2Num.encodeMaritalStatus);
	//对occupation进行编码
	memset(trainDataEncode.encodeOccupation,0,sizeof(trainDataEncode.encodeOccupation));
	encodeText2numRespectively(trainAttriTextData.lenOccupation,trainDATA.occupation,trainDataEncode.encodeOccupation,Text2Num.occupation,Text2Num.encodeOccupation);
	//对relationship进行编码
	memset(trainDataEncode.encodeRelationship,0,sizeof(trainDataEncode.encodeRelationship));
	encodeText2numRespectively(trainAttriTextData.lenRelationship,trainDATA.relationship,trainDataEncode.encodeRelationship,Text2Num.relationship,Text2Num.encodeRelationship);
	//对race进行编码
	memset(trainDataEncode.encodeRace,0,sizeof(trainDataEncode.encodeRace));
	encodeText2numRespectively(trainAttriTextData.lenRace,trainDATA.race,trainDataEncode.encodeRace,Text2Num.race,Text2Num.encodeRace);
	//对sex进行编码 由于其只有二维可以进行简单的one-hot编码
	memset(trainDataEncode.encodeSex,0,sizeof(trainDataEncode.encodeSex));
	
	for(i=0;i<trainNumRow;i++)
	{    
		
		for(j=0;j<2;j++)
		{
				if(strcmp("Male",trainDATA.workclass[i])==0)
				{
					 Text2Num.encodeRace[i][0] =1 ;  //Male编码为1 0 
					 Text2Num.encodeRace[i][1] =0 ;

				}
				else
				{
					Text2Num.encodeRace[i][0] =0 ;  //Female编码为1 0 
					 Text2Num.encodeRace[i][1] =1 ;
				}
		}
	}
	//对nativeCountry进行编码
	memset(trainDataEncode.encodeNativeCountry,0,sizeof(trainDataEncode.encodeNativeCountry));
	encodeText2numRespectively(trainAttriTextData.lenNativeCountry,trainDATA.nativeCountry,trainDataEncode.encodeNativeCountry,Text2Num.nativeCountry,Text2Num.encodeNativeCountry);
	

}
void encodeText2numRespectively(int length,char text[MAX_DATA_SIZE][MAX_char_SIZE],int data2number[MAX_DATA_SIZE][MAX_encode_SIZE],
								char mask[MAX_DATA_SIZE][MAX_char_SIZE],int maskcode[MAX_DATA_SIZE][MAX_encode_SIZE])				//各个属性文本与数字编码之间的编码
{//以workclass为例  length为workclass所有的种类个数如7个;text是需要编码的文本数据；data2number是文本数据编码后数字数据;maskhe maskcode是文本和对应的文本的编码
	int i,j,k;
	
	for(i=0;i<trainNumRow;i++)
	{    
		
		for(k=0;k<length;k++)
		{
				if(strcmp(mask[k],text[i])==0)
				{
					
					for(j=0;j<MAX_encode_SIZE;j++)
					{  data2number[i][j] = maskcode[k][j] ;}//文本与数字编码之间的对应关系
				}
				
		}

	}

}


	
	
	


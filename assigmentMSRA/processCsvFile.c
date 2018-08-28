#define _CRT_SECURE_NO_WARNINGS
#include"processCSVFile.h"

int GetTotalLineCount(FILE* fp);              //计算csv文件中的总行数
int GetTotalColCount(FILE * fp);              //计算csv文件中的总列数（以第一行的列数为基准）

//计算csv文件中的总行数
int GetTotalLineCount(FILE * fp)
{   
    int i = 0;
    char strLine[MAX_LINE_SIZE];                 //存放从文件中读出的字符数据
    fseek(fp,0,SEEK_SET);                       //重定位流上的文件指针 fp指向SEEK_SET(开头）+0 
    while (fgets(strLine, MAX_LINE_SIZE, fp))
        i++;                                      //计算行数
    fseek(fp,0,SEEK_SET);                        //复原fp指针 
    return i;
}

//计算csv文件中的总列数（以第一行的列数为基准）
int GetTotalColCount(FILE * fp)
{   
    int i = 0;
    char strLine[MAX_LINE_SIZE];                 //存放从文件中读出的字符数据
    fseek(fp,0,SEEK_SET);                       //重定位流上的文件指针 fp指向SEEK_SET(开头）+0 
    if (fgets(strLine, MAX_LINE_SIZE, fp))
    {
        i=strlen(strLine)/2;          //因为csv文件以逗号','作为分隔符，所以此处除以2,但可能存在问题，应该先split在统计，此处只是提到这个功能，尚未使用
    }
    else
    {
        fseek(fp,0,SEEK_SET);
        return -1;
    }
    fseek(fp,0,SEEK_SET);
    return i;
}


// 从csv文件中读取数据
int ReadCsvData(char* csvFilePath)
{
    FILE* fCsv;               //csvFilePath文件指针 
	char *err = " ?";              //分割出来的字符串为“？”则删除此行数据
    char strLine[MAX_LINE_SIZE];   //存放从文件中取出来的内容

	 
    int i,j,k,t;
	char *ptr;						//分割出来的单个字符串数据
	char *tempString[15];          //临时存放某一行分割出来的字符串数据
	int flag =1;                  //标志 如果分割出来的字符串为“？”，则flag置0
	

    // 打开文件
    if( fopen_s( &fCsv, csvFilePath, "r" ) != 0 )
    {
        printf("open file %s failed",csvFilePath);
        return -1;
    }
    else
    {

        trainNumRow = GetTotalLineCount(fCsv); // 读取数据的行数 不算第一行
    
		fgets(strLine,MAX_LINE_SIZE,fCsv);		//去除第一行，因为第一行是表头

        // 读取数据
        for (i = 0,k=0; i < trainNumRow; i++)			
        {   memset(tempString,'\0',sizeof(tempString)); //将tempString初始化为空
			flag = 1;
            j=0;
            if(fgets(strLine,MAX_LINE_SIZE,fCsv))
            {
				
                ptr=strtok(strLine,",");  //返回字符数组中字符‘,’之前的字符，剩下的保留到静态数组中
                while(ptr!=NULL)
                {
                    tempString[j]= ptr;				//将字符转换为int类型数据并保存到数组中
                    j++;
                    ptr = strtok(NULL,",");                //将从文件中读取的当前行剩余字符数组，读取字符‘,’前面的字节				
                }
				
				for(t=0;t<j;t++)	
				{
					if (strcmp(tempString[t],err) == 0)   //如果分割出来的字符串为“？”，则flag置0
						{
							flag = 0;                      //为了后续删除含有“？”的此行数据
							break;
						}
				}

				if (flag == 0)                               ///删除删除含有“？”的此行数据
					continue;
				
				//读出的数据按属性分类保存在trainDATA这个结构体里面
				trainDATA.age[k] = atoi(tempString[0]);
				strcpy(trainDATA.workclass[k],tempString[1]);
				strcpy(trainDATA.education[k] , tempString[2]);
				trainDATA.educationNum[k] = atoi(tempString[3]);
				strcpy(trainDATA.maritalStatus[k] , tempString[4]);
			    strcpy(trainDATA.occupation[k],tempString[5]);
				strcpy(trainDATA.relationship[k] ,tempString[6]);
				strcpy(trainDATA.race[k] , tempString[7]);
				strcpy(trainDATA.sex[k] , tempString[8]);
				trainDATA.capitalGain[k] = atoi(tempString[9]);
				trainDATA.capitalLoss[k] = atoi(tempString[10]);
				trainDATA.hoursPerWeek[k] =  atoi(tempString[11]);
				strcpy(trainDATA.nativeCountry[k],tempString[12]);
				label[k] = atoi(tempString[13]);
				k++;
				
            }
        }
		
    fclose(fCsv); //关闭文件
    }
	trainRealNumRow = k; //得到删除含“？”行的数据
	
	printf("共有数据%d个，其中出错的数据有 %d个\n",trainNumRow-1,trainNumRow-trainRealNumRow -1); //显示相关数据
	printf("\n");

    return 1;
}

//通过控制台显示读取的csv数据
void  ShowCsvData()                           
{
    int i;
   
    for (i = 0; i < trainRealNumRow ; i++)
    {
        printf("Line %d :",i+1);    //输出每行的行号 Line :

            printf("%f,%s,%s,%f,%s,%s,%s,%s,%s,%f,%f,%f,%s\n",trainDATA.age[i],trainDATA.workclass[i], 
		    trainDATA.education[i], trainDATA.educationNum[i], trainDATA.maritalStatus[i], trainDATA.occupation[i],
            trainDATA.relationship[i], trainDATA.race[i], trainDATA.sex[i], trainDATA.capitalGain[i], 
			trainDATA.capitalLoss[i], trainDATA.hoursPerWeek[i], trainDATA.nativeCountry[i] );  // 打印CSV数据

        printf("\n");                           //输出换行
    }
}

 int writeCsvData(char* csvFilePath)          //将所读取的数据写入到csv文件中
{

    FILE *fp = NULL; //需要注意
	int i;
    fp = fopen(csvFilePath, "w");//打开或者新建
    if(NULL == fp)
    {

        return -1; //返回错误代码
     }
    for (i = 0; i < trainRealNumRow ; i++)
    {
		fprintf(fp,"%f %s %s %f %s %s %s %s %s %f %f %f %s\n",trainDATA.age[i],trainDATA.workclass[i], 
		trainDATA.education[i], trainDATA.educationNum[i], trainDATA.maritalStatus[i], trainDATA.occupation[i],
        trainDATA.relationship[i], trainDATA.race[i], trainDATA.sex[i], trainDATA.capitalGain[i], 
		trainDATA.capitalLoss[i], trainDATA.hoursPerWeek[i], trainDATA.nativeCountry[i] );  // 打印CSV数据
    }

   fclose(fp);
   fp = NULL; //需要指向空，否则会指向原打开文件地址
   return 0;
 }

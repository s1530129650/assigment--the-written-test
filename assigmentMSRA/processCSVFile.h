#pragma once
#include <stdio.h>
#include <memory.h>		 // for memset
#include <stdlib.h>		 // for malloc, free
#include <string.h>		 // for strtok
#include "variant.h"	 //结构体和一些变量声明

/*
此文件用于第一步Data Loading，数据的行数和列数会保存在trainNumRow 、 trainNumCol中；读出的数据按属性分类保存在trainDATA这个结构体里面；

*/

int ReadCsvData(char* csvFilePath);           //读取Csv中数据
void  ShowCsvData();                          //通过控制台显示读取的csv数据
int writeCsvData(char* csvFilePath);          //写入csv数据

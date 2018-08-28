#pragma once
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include"variant.h"  //存放结构体变量

/*
为保证分层抽象后的比例，我们将数据集分为正负两个集合，存放在postivefeatureVector和negativefeatureVector中	
用洗牌算法生成随机数，分别从正负样本中抽取70%的数据作为训练集，剩余的30%为验证集，以此来分层抽样，
之后选择不同的参数在训练集上训练模型，得到选择最佳参数，全部的数据用于模型的训练；
将最优参数与训练出来的权重保存在“weight_and_parameter.txt”。
*/

void  stratifiedSampling();          //分层抽样 
void  computeWeight();				//计算不同参数的权重并选择最优的进行模型的训练

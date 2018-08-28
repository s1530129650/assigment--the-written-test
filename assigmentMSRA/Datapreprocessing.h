#include<stdio.h>
#include<string.h>
#include"variant.h"  //结构体和一些变量声明


/*
 对文本数据进行one-hot encode和赫夫曼-onehot编码，要求文本数据编码后的长度不超过3维，因此只有sex属性用one-hot编码，其余均用赫夫曼-onehot编码：
 编码完成后还需保存文本与数字编码之间的对应转换，以便后续再test集上使用；对数字数据进行归一化处理，使其取值区间在[0,1];然后将得到的所有向量合并成28维的特征向量
*/

void getAttriNum();               //得到各个属性的种类以及种类数
void oneHotEncode();              //one-hot encode
void dataHighRate();              //各个属性中大于label大于50k的比率
void HuffmanCoding();             //赫夫曼-onehot编码 
void normalization();			  //对数据进行归一化
void getfeatureVector();		  //得到特征向量
void saveText2num();			  //保存文本与数字编码之间的对应转换
void encodeText2num();			  //文本与数字编码之间的编码

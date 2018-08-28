#  Predict People’s Income 
 
# About
   There are two csv-format data files named `census.csv` and `census-test.csv` respectively. Each data 
file contains a header line, and after that each line contains an individual personal record including 14 attributes. The two files have the same format, where "ensus.csv" contains the training data, and
"census-test.csv" contains the test data.I will explore a simple linear model a simple linear model based on the squared error between prediction values  and label by optimizing  objective function with respect to the weight vector w = [w1; ... ; wd] to predict the label.My program is writtern in c language.


# Usage
## The Arguements

    char *fpTest1="XXX.csv";
You can replace `XXX.csv` with another file name.Note that the file must be csv-format and The content of the book should be the same as t`census.csv` .
## build
### Windows

 Open the `assigmentMSRA.sln` with  [Visual Studio 2012](https://baike.baidu.com/item/Visual%20Studio%202012) and build.
### Linux
	......
##Result
  After you have built it,you will get the accuarcy rate in `cmd window`and a file named`weight_and_parameter.txt` .

# Examples:
## Implemetation
The default parameter of fpTest1 is `census-test.csv`,So we can built it diretly.

	12.char *fpTest1="census-test.csv";

After Implementation, you can find the the accuarcy rate in `cmd window` like the following picture
![](https://ibb.co/eCyNV9)
the content of the `weight_and_parameter.txt` like this.
![](https://ibb.co/i21gOU)

 
## Evaluation
For the two-category problem, we believe that the correct rate must be greater than 50% to be reasonable.


# Design

## 1.Data Loading:

Data Loading ，whichcorresponds to the `processCsvfile.h` and `processCsvfile.c` files, mainly includes statistics on data reading, storage, data size etc and handling of errors.

* For the purpose of this assignment, i assume that i know the number of attributes and which attributes are numbers (or text values),SoI create structure variable` attributes `(text type data is defined as char type, numeric type is defined as double type) to save the data. The statistics read from the file will  be saved by their attributes respectively.
* I ignore all records with missing values.

## 2.Data Preprocessing

Data preprocessing, which corresponds to the `Datapreprocessing.h` and `Datapreprocessing.c` files, mainly includes the encoding of text values, the normalization of numerical values, and obtaining feature vectors.

* I employ the one-hot trick to encode attribute  `sex ` and Huffman&one-hot code to encode others text attributes.(Huffman&one-hot code is the idea of Huffman coding.The same size code is divided into one class sharing the same code)

* I implement a following scaling scheme  separately for each column,so that values after transformation are in the range of [0; 1]
![](https://ibb.co/jxLxDU)

* All the processed  values are merged in the order of attributes given by the header to obtain 28-dimensional feature vectors.

## 3.Model Training and Parameter Selection
Model training and parameter Selection ,which corresponds to the `parameterSelection.h` and `parameterSelection.c` files, mainly include the generation of random numbers, stratified sampling, cross-validation to select the optimal parameters, and the training  model.

* We use function `xiPaiRand(int randarray[],int Times)` to generate a random sequence `randarray[]` whose range is `[0, Times]` not repeated.
* In order to make sure that when I split the training data into training and validation sets by randomly assigning records to one of these sets, each set should observe about the same proportion of label values as the full data,I split the training data into positive sample set(label = 1) and negative sample set(label = 0) firtly.Then I sampled from two geometriesrespectively.
* I implement a validation scheme to select the best` λ ` from four possible values of λ, namely `{0.001; 0.01; 0.1; 1}` and the best` β `from four possible values of β,`{0.001; 0.01}`
* Finally, I train the model on the full training data using the optimal parameter selected by the validation scheme.

## 4.Testing
the test records are loaded from \census-test.csv",they are also preprocessed by applying the same preprocessing steps that were previously applied to the training data set. After preprocessing, each test record is converted to a feature Vector. We then apply linear prediction model to get the prediction accuracy.

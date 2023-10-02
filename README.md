# **Project Title** #
Bangla Topic Modelling Using Non-negative Matrix Factorization.


 # **Project Description**
This project aims to implement Non-Negative Matrix Factorization (NMF) for topic modelling, a technique used to extract latent topics from a collection of textual documents. By utilizing NMF, the project will analyze a given corpus, factorize it into non-negative matrices representing document-topic and topic-word distributions, and subsequently identify and label the underlying topics. The project will enable efficient exploration and understanding of large text datasets of Bangla text , providing valuable insights into the prominent themes and trends present within the documents.

I have used C++ as the programming language.

# **Project Flow**
![project flow](https://github.com/rony31416/SPL-1/assets/121255231/dbabd8fb-5ae8-46c3-a955-e99184a581da)

# **User Manual**
For the execution of this project you have to follow some instructions. 
#### Linux terminal
Create a new folder then open the terminal from this folder.Afer this type following command.
```shell
git clone https://github.com/rony31416/SPL-1.git
```
It takes a few seconds to download all these files.Then type
```shell
cd SPL-1
```
​Now we are in the SPL-1 directory 
Type the following command for compiling all these executable files
```shell
g++ *.cpp
./a.out 
```
After the execution, the figure below will appear.
![spl](https://github.com/rony31416/SPL-1/assets/121255231/00779e53-9fef-479d-8939-1e65e0cf0c9b)

Now, first type the input file name and  select any integer(1 to 5) to show the data.
Be careful while choosing "dimension for the factorized TFIDF Matrix" according to the input text
for me its 3

# **insufficiency**
There are many challenges to this project as this project is for the Bangla language as the compiler does not support Bangla .It was hard to collect data to stop words being removed.But the main problem was to use C++ and without any library function of matrix multiplication.There are many scores available for Bangla Topic Modelling with python.

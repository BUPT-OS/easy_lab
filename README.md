# magic print

- [magic print](#magic-print)
  - [lab任务与评分](#lab任务与评分)
    - [lab讲解](#lab讲解)
    - [lab前置操作（包括如何准备环境，如何拉取lab的代码，如何提交作业）](#lab前置操作包括如何准备环境如何拉取lab的代码如何提交作业)
    - [lab的评分规则和due](#lab的评分规则和due)
  - [lab基础知识讲解](#lab基础知识讲解)
    - [`printf`对内存模型的影响](#printf对内存模型的影响)
  - [lab实操](#lab实操)
    - [任务1](#任务1)
    - [lab测试方法](#lab测试方法)
  - [引用](#引用)

## 截止: 2024.12.26 23:59
助教 dujiajun.1@bupt.edu.cn

## lab任务与评分

### lab讲解

`print`在各个语言中都是必不可少的一个函数。例如，在C语言中，`printf`常常被用来输出一些信息或者用来`debug`，不承担代码逻辑，在C++中，`cout`承担类似的角色，由于大家没有学过C，下面的例子以C++说明，`printf`的实际内容为`cout`。。但是作为一个代码中的`隐藏第六人`，却会影响代码的执行结果，比如，经常会遇到注释或者增加一个`printf`，导致程序执行结果错误或者`segment fault`。这些诡异的bug都是因为对`printf`在内存模型的影响不够了解，我们这个作业就用一个例子浅探一下`printf`的世界。

### lab前置操作（包括如何准备环境，如何拉取lab的代码，如何提交作业）

1. 准备配置环境
本系列实验为了保证环境的一致性，提供docker镜像作为实验环境，大家应该在之前的lab里面已经把docker配置好了，如果还没有的话，可以通过这个[链接](https://github.com/rust-real-time-os/os_lab/tree/lab2#docker%E5%AE%89%E8%A3%85%E5%8F%8A%E6%8B%89%E5%8F%96%E4%BB%A3%E7%A0%81)配置docker。easy_lab3沿用easy_lab1/2的docker镜像。
2. 如何提交作业
本次实验的代码答案和文档需要提交到评测平台，代码提交的方式为patch，文档提交的格式为pdf，和lab1的方法一致，具体说明参照这个[链接](https://github.com/rust-real-time-os/os_lab/tree/lab1#%E6%8F%90%E4%BA%A4)。

### lab的评分规则和due

评分规则：patch 50分；文档50分；

due: 2024/12/26 23:59:59

## lab基础知识讲解

### `printf`对内存模型的影响

printf对内存模型的影响集中在两个方面

1. 打印内容前，会创建一个buffer作为打印内容的缓存，这个buffer的大小由具体的实现而定，是不确定的。助教在x86_64的机器上测试，得出的结果是1024字节。这个buffer的地址是在堆上的，所以对于。
2. 打印内容时，`printf`函数会产生一个`write` syscall，会对`printf`的buffer进行输出，这个过程会影响到`printf`的buffer的内容。

## lab实操

这里我们用一个简化后的`printf`使用的例子来作为lab，说明实际例子中`printf`的影响。

> 由于我们在例子中对`printf`的假设依赖于一些未定义行为，所以这个例子可能在不同的机器上有不同的结果，我们在`x86_64` Linux 5.4.0-150的机器上测试过，可以得到我们想要的结果。

### 任务1

1. 背景：在给出的`print.cpp`中，我们在23行打印了一个字符串，如果我们在程序中注释掉这一行，我们就会出现一个`segment fault`，如果解开注释，程序就会执行成功。大致原因是我们在`cout`函数中会在堆上隐式声明一个`char`数组，这个数组的大小是`1024`，我们在`main`函数的不同位置调用`cout`，这个数组的位置在堆上也是不确定的，如果由于程序中的隐含错误使用了这个数组就会导致`segment fault`。

```C++
#include <iostream>

using namespace std;

#define array_number 64

int matrix[array_number][array_number];

int **double_array(size_t n) {
    int **result = new int*[8];

        for (int i = 0; i < n; ++i) {
            result[i] = matrix[i];
            for (int j = 0; j < n; ++j){
                result[i][j] = j;
            }
    }

    return result;
}

int main() {
    // cout<<"A magic print! If you comment this, the program will break."<<endl;
    int **result = double_array(array_number);
    
    for (int i = 0; i < array_number; ++i) {
        cout<<"print address of result[i] "<<&result[i][0]<<endl;
        for (int j = 0; j < array_number; j++) {
            result[i][j] = j;
            cout<<"print content of result[i][j] "<<result[i][j]<<endl;
        }
    }
    free(result);
}
```
2. 需求：
   - 本次实验需要大家在注释掉`cout<<"A magic print! If you comment this, the program will break."<<endl;`后，修复这个段错误的bug(只需要修改一处)；
   - 然后提交一个文档，具体说明你怎么找到的这个修复方法，并且阐述为什么会出现这个问题，最好能写一段代码基于内存布局来证明为什么23行的`cout`可以修复这个bug。（注意思考程序中堆上都分配了哪些内存、这些内存之间的位置顺序）


### lab测试方法

```bash
g++ print.cpp -o print
./print
```

如果运行没有段错误，即为修复成功

## 引用

[1] [printf修复bug的例子](https://www.reddit.com/r/C_Programming/comments/p10ol6/printf_before_memory_allocation_fixes_bug_whats/)
# magic print

- [magic print](#magic-print)
  - [lab内容](#lab内容)
    - [背景](#背景)
    - [环境配置](#环境配置)
    - [代码说明](#代码说明)
    - [任务1](#任务1)
    - [任务2](#任务2)
    - [任务3](#任务3)
    - [测试方法](#测试方法)
  - [提交方式、评分规则、deadline](#提交方式评分规则deadline)
  - [基础知识引导](#基础知识引导)
    - [堆内存](#堆内存)
    - [gdb调试](#gdb调试)
  - [引用](#引用)

## 截止: 2025.12.24 23:59
助教 jiajundu@bupt.edu.cn

## lab内容

### 背景

`print`在各个语言中都是必不可少的一个函数。例如，在C语言中，`printf`常常被用来输出一些信息或者用来`debug`，在C++中，`cout`承担类似的角色，但是作为一个代码中的`隐藏第六人`，却会影响代码的执行结果，比如，经常会遇到注释或者增加一个`cout`，导致程序执行结果错误或者`segment fault`。这些诡异的bug都是因为对`cout`在内存模型的影响不够了解，我们这个作业就用一个简化后的例子浅探一下`cout`的世界。

### 环境配置

本系列实验为了保证环境的一致性，提供docker镜像作为实验环境，大家应该在之前的lab里面已经把docker配置好了，直接在容器环境里把easy_lab3的分支拉取下来即可。注意仓库中可能会有新的commit，请拉取到最新的lab3代码。可以参考下面的命令行拉取代码。

```bash
# 如果没有easy_lab的仓库代码, 则需要拉取仓库, 然后切换分支
# 如果连接不了github，也可以使用lab1提供的gitee仓库
git clone https://github.com/BUPT-OS/easy_lab.git

# 如果在本地已经有了easy_lab的仓库代码, 只需要在仓库目录下拉取easy_lab3的分支即可
git fetch origin lab3:lab3

# 拉取lab3的最新代码
git pull origin lab3:lab3

git checkout lab3
```

如果还没有配置docker容器环境的话，可以通过这个[链接](https://github.com/rust-real-time-os/os_lab/tree/lab2#docker%E5%AE%89%E8%A3%85%E5%8F%8A%E6%8B%89%E5%8F%96%E4%BB%A3%E7%A0%81)配置docker，easy_lab3沿用easy_lab1/2的docker镜像。

### 代码说明

在lab3的分支中含有`print.cpp`文件，文件中的代码包含一个很奇怪、有趣的现象：我们在23行通过调用`cout`打印了一个字符串，如果我们在程序中注释掉这一行，程序在运行时就会崩溃，如果解开注释，程序就能够执行成功。

你可以参考下面[测试方法](#测试方法)一节来验证这个奇怪的现象。

### 任务1

很显然，这个奇怪的现象背后肯定有一个bug在作怪。

所以，easy_lab3的第一个任务就是：**在注释掉23行的情况下，找出导致程序崩溃的bug，并且修复它，使得程序可以正常运行**。

> 完成任务1其实只需要更改`print.cpp`中一处即可。

在确定bug已经被成功修复之后，你需要生成patch，提交到评测平台来验证bug是否已经被修复。关于生成patch，可以参考[链接](https://github.com/rust-real-time-os/os_lab/tree/lab1#%E6%8F%90%E4%BA%A4)。

### 任务2

本次lab的本意其实是想让大家理解堆内存的管理方式、以及`cout`对于堆内存的影响，而方式就是通过分析任务1中的bug。

任务2中你需要分析原始的`print.cpp`文件，并且在评测平台上提交一个pdf格式的实验报告，内容包括：

1. 在注释掉23行`cout`后，程序是在执行到哪一行代码才崩溃的? （给出行号）
2. 从堆内存角度，在注释掉23行`cout`后，解释bug产生的原因、以及程序崩溃的原因
3. 从堆内存角度，说明为什么23行`cout`在解开注释的情况下可以使得程序正常运行

由于本次实验涉及的内容比较隐秘，所以我们在本文后半部分添加了[基础知识引导](#基础知识引导)章节，旨在帮助大家明确思路并引导正确的思考方向。

> 对于任务2来说，大家注意思考程序的堆上都分配了哪些内存、这些内存之间的位置顺序是怎么样的

### 任务3

在任务1和任务2的基础上，我们在`cout`被注释、bug依然存在的情况下，添加一行代码（可以查看`print_v2.cpp`文件）：

```cpp
if(i == 8 || i == 9) continue;
```

可以通过执行`make print_v2`命令编译运行该文件。该任务中你不需要修改代码，只需要回答以下问题：

1. 程序在运行的过程中会有输出吗?
2. 程序可以正常运行吗?
    * 如果可以正常运行，解释为什么在bug依然存在的情况下可以正常运行?
    * 如果不可以正常运行：
        * 程序是在执行到哪一行代码才崩溃的? （给出行号）
        * 解释此时导致程序崩溃的原因又是什么?

同样把对上面问题的回答写在pdf文档里一起提交到评测平台即可。

### 测试方法

在lab仓库根目录下，我们提供了一个`Makefile`来编译、运行，在修改`print.cpp`之后，可以通过命令运行`make all`来进行测试，如果执行成功，则会输出`Program execution successful.`，如果执行失败，则会输出`Program execution failed.`。

## 提交方式、评分规则、deadline

提交方式：将patch和pdf文档提交到评测平台（http://10.161.28.28:8765/ ）。

评分规则：patch 10分 (提交patch后成功修复的情况下得到10分)；文档90分。

deadline: 2025/12/24 23:59:59

## 基础知识引导

### 堆内存

在c/c++中，用户程序使用`malloc`或者`new`向glibc中的内存分配器申请堆内存时，内存分配器首先会查看维护的空闲内存块是否可以满足请求，如果可以，则直接分配成功，如果不能满足请求，则内存分配器会首先通过系统调用向内核请求更多内存，然后再完成分配。

为了方便维护堆内存的信息，glibc的内存分配器（以及其他大多数的内存分配器实现）会在用户指定的堆内存大小的基础上多分配一块堆内存，这一块多余的内存区域就用来保存该堆内存的信息（比如块大小等等），被称为元数据（meta-data）。比如用户如果指定需要分配32B，内存分配器在空闲堆内存空间中并不仅仅分配出32B的内存，而是会分配的大小是32+sizeof(meta-data)，前面sizeof(meta-data)的区域用来保存元数据，后面部分以指针的形式返回给用户使用。

除此之外，`cout`在执行过程中也会在堆内存上申请`buffer`来保存需要输出的内容。

为了验证上述机制，我们在`clue_to_you`目录下给出了一些程序，你可以根据运行结果或者自行编写程序来验证自己的想法。

```bash
# Makefile中也提供了clue_b、clue_c、clue_d的命令
make clue_a
```

对于本lab来说，你可以考虑以下问题：
1. 在你的Linux环境中，meta-data的大小是多少?
2. `cout`的`buffer`大小是多少?
3. `cout`的`buffer`在多个`cout`调用间可以复用吗?

关于glibc中其他更多的细节还可以阅读引用[1]，也可以尝试阅读glibc的内存分配器源代码[2] [3]。

### gdb调试

gdb是一个功能非常强大的代码调试工具，因为本次lab的关注点在于内存，所以学会使用gdb观测程序的内存状态是非常有用的。

在使用gdb调式前需要重新编译程序，在编译命令中添加`-g`参数使得在最后的二进制文件中包含调试信息。

```bash
# 添加-g参数
g++ a.cpp -g -o a
```

gdb中提供了一个`x`命令可以把触发断点后内存的信息打印出来，比如`x/2g a`的含义就是：获取a指针指向的地址后面的内存，以8个字节为单位，输出前两个，打印的结果就会如下：
```
(gdb) x/2g a
0x5d86e7901ea0: 0x0000000000000000      0x0000000000000031
```

你可以使用该功能来查看meta-data中保存的信息是什么，甚至你还可以打印`cout`的缓冲区内存信息，来查看内容是不是已经打印出来的内容。

对于其他比较常用的gdb指令，可以阅读引用[4]或者gdb的官方文档。

## 引用

[1] glibc文档: https://sourceware.org/glibc/wiki/MallocInternals

[2] glibc的_int_free函数：https://elixir.bootlin.com/glibc/glibc-2.31/source/malloc/malloc.c#L4154

[3] glibc的_int_malloc函数：https://elixir.bootlin.com/glibc/glibc-2.31/source/malloc/malloc.c#L3512

[4] gdb cheat sheet: https://darkdust.net/files/GDB%20Cheat%20Sheet.pdf

[5] reddit的相关讨论：https://www.reddit.com/r/C_Programming/comments/p10ol6/printf_before_memory_allocation_fixes_bug_whats/

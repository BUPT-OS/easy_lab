# 使用基础镜像为 Ubuntu 22.04
FROM ubuntu:22.04
COPY sources.list /etc/apt/sources.list
RUN apt-get update && apt-get install -y wget 
RUN wget -qO- https://apt.llvm.org/llvm-snapshot.gpg.key | tee /etc/apt/trusted.gpg.d/apt.llvm.org.asc &&\
    apt-get update
# 安装必要的软件包和工具链
RUN apt-get update && apt-get install -y \
    make \
    git \
    gcc \
    clang clangd gdb && \
    rm -rf /var/lib/apt/lists/*

# 默认的工作目录
WORKDIR /workspace



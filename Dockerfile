FROM ubuntu:20.04

RUN sed -i "s/http:\/\/archive.ubuntu.com/http:\/\/mirrors.tuna.tsinghua.edu.cn/g" /etc/apt/sources.list && \
    apt-get update && apt-get -y dist-upgrade

WORKDIR /

RUN apt-get install -y flex bison clang llvm

RUN apt-get install -y python3

RUN apt-get install -y python3-pip

RUN pip install graphviz

RUN mkdir /compiler

ADD src /compiler/src
ADD test /compiler/test

WORKDIR /compiler/src
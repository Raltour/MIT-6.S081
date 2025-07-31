FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    software-properties-common \
    build-essential \
    git \
    wget \
    curl \
    gdb-multiarch \
    vim \
    gcc-riscv64-linux-gnu \
    qemu-system-misc \
    binutils-riscv64-linux-gnu \
    && rm -rf /var/lib/apt/lists/*

RUN git config --global --add safe.directory /xv6 && \
    mkdir -p /usr/lib/gcc-cross/riscv64-linux-gnu/13/include && \
    ln -s /usr/lib/gcc-cross/riscv64-linux-gnu/9/include/stdarg.h /usr/lib/gcc-cross/riscv64-linux-gnu/13/include/

WORKDIR /xv6

COPY . /xv6/

CMD ["/bin/bash"]
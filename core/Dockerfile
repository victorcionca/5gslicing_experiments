FROM ubuntu:latest

RUN apt-get update && \
    apt-get upgrade -y && \
    DEBIAN_FRONTEND=noninteractive \
    apt-get install -y --no-install-recommends \
        python3-pip \
        python3-setuptools \
        python3-wheel \
        ninja-build \
        build-essential \
        flex \
        bison \
        git \
        meson \
        libsctp-dev \
        libgnutls28-dev \
        libgcrypt-dev \
        libssl-dev \
        libidn11-dev \
        libmongoc-dev \
        libbson-dev \
        libyaml-dev \
        libmicrohttpd-dev \
        libcurl4-gnutls-dev \
        libnghttp2-dev \
        iproute2 \
        ca-certificates \
        netbase \
        pkg-config && \
    apt-get clean

WORKDIR /root
COPY setup.sh /root

ARG USER=open5gs
ARG REPO=open5gs
ARG BRANCH=main
RUN	git clone https://github.com/$USER/$REPO
ADD https://api.github.com/repos/$USER/$REPO/branches/$BRANCH /root/open5gs-ver.json

RUN	cd $REPO && \
	git fetch && git checkout -f -B $BRANCH origin/$BRANCH && \
    meson build && ninja -C build install

RUN apt-get update && \
    apt-get upgrade -y && \
    DEBIAN_FRONTEND=noninteractive \
    apt-get install -y --no-install-recommends vim iputils-ping mongodb linux-tools-`uname -r`
COPY amf.yaml /usr/local/etc/open5gs/
COPY upf.yaml /usr/local/etc/open5gs/
COPY nssf.yaml /usr/local/etc/open5gs/
COPY setup_core.sh /root/
COPY start_core.sh /root/
COPY stop_core.sh /root/

COPY perf_server.c /root/
RUN gcc perf_server.c -o perf_server

FROM ubuntu:latest

WORKDIR /root

RUN apt-get update && \
    apt-get upgrade -y && \
    DEBIAN_FRONTENT=noninteractive \
    apt-get install -y --no-install-recommends tzdata
RUN DEBIAN_FRONTENT=noninteractive \
    apt-get install -y --no-install-recommends \
        ca-certificates \
        make \
        g++ \
        libsctp-dev \
        lksctp-tools \
        iproute2 \
        git \
        cmake \
        vim && \
    apt-get clean
#RUN git clone https://github.com/victorcionca/UERANSIM

#RUN cd UERANSIM &&\
#    git fetch && git checkout -f -B dimensioning origin/dimensioning &&\
#    make
RUN mkdir /root/ueransim_exp/
RUN mkdir -p /root/5gcore/UERANSIM/
COPY setup_amf_ip.sh /root/

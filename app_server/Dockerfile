FROM debian:latest

WORKDIR /root

RUN apt-get update && \
    apt-get upgrade -y && \
    DEBIAN_FRONTENT=noninteractive \
    apt-get install -y --no-install-recommends tzdata
RUN DEBIAN_FRONTENT=noninteractive \
    apt-get install -y --no-install-recommends \
        ca-certificates \
        iproute2 \
        telnet \
        iputils-ping \
        netcat \
        iptables \
        vim && \
    apt-get clean

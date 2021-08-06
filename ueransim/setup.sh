# Create /dev/net/tun
mkdir -p /dev/net
mknod /dev/net/tun c 10 200
# Configure the SCTP endpoint of AMF
cd /root/5gcore/UERANSIM
amf_ip=`getent hosts open5gs-run | awk '{print $1}'`
sed -i -e "s/open5gs-run/$amf_ip/" config/open5gs-gnb.yaml
cd /root

# Configure the mongodb connection
cd /usr/local
MONGOIP=`getent hosts mongodb | awk '{print $1}'`
grep "mongodb:" -R etc/open5gs/ | while read -r line
do
    fname=`echo $line | cut -d ':' -f 1`
    sed -i -e "s#\(db_uri: mongodb://\)[^/]\+/#\1$MONGOIP/#" $fname
done
# Configure the address of the UPF GTPU endpoint
ADDR=`ip addr show dev eth0 | grep "inet " | awk '{print $2}' | awk -F '/' '{print $1}'`
sed -i "s/upf_gtpu/$ADDR/" /usr/local/etc/open5gs/upf.yaml

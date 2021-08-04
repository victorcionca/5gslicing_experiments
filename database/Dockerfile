FROM mongo

WORKDIR /root

COPY db_init.sh /root/
COPY open5gs-dbctl /root/

RUN cd /root ; mongod & sleep 5 ; sh -c "./db_init.sh localhost"

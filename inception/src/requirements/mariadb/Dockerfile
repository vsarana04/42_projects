# Dockerfile
FROM debian:buster

ARG DB_NAME
ARG ROOT_PASS
ARG ADMIN_USER
ARG ADMIN_PASS

ENV DB_NAME=$DB_NAME \
    ROOT_PASS=$ROOT_PASS \
    ADMIN_USER=$ADMIN_USER \
    ADMIN_PASS=$ADMIN_PASS

RUN apt-get update -y && \
    apt-get upgrade -y && \
    apt-get install -y mariadb-server

COPY ./conf/50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf
COPY ./tools/setup.sh /setup.sh

RUN chmod +x /setup.sh

CMD ["/setup.sh"]

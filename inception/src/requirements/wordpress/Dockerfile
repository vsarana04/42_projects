FROM debian:buster

ARG DOMAIN
ARG TITLE
ARG DB_NAME
ARG DB_HOST
ARG USER
ARG USER_EMAIL
ARG USER_PASS
ARG ADMIN_USER
ARG ADMIN_PASS
ARG ADMIN_EMAIL

ENV DOMAIN=$DOMAIN \
    TITLE=$TITLE \
    DB_NAME=$DB_NAME \
    DB_HOST=$DB_HOST \
    USER=$USER \
    USER_EMAIL=$USER_EMAIL \
    USER_PASS=$USER_PASS \
    ADMIN_USER=$ADMIN_USER \
    ADMIN_PASS=$ADMIN_PASS \
    ADMIN_EMAIL=$ADMIN_EMAIL

RUN apt-get update -y && apt-get upgrade -y && \
    apt-get install -y php-fpm php-mysql curl mariadb-client && \
    apt-get clean

COPY ./tools/setup.sh /tools/setup.sh
RUN chmod +x /tools/setup.sh

CMD ["/tools/setup.sh"]
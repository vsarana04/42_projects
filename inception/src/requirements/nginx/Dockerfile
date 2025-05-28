FROM debian:bullseye

ARG DOMAIN
ARG CERT_PATH

ENV DOMAIN=${DOMAIN}
ENV CERT_PATH=${CERT_PATH}

RUN apt-get update && apt-get install -y nginx openssl

RUN mkdir -p /etc/nginx/ssl

COPY ./tools/build.sh /build.sh
COPY ./conf/nginx.conf /etc/nginx/sites-available/default

RUN chmod +x /build.sh && /build.sh

EXPOSE 443
CMD ["nginx", "-g", "daemon off;"]
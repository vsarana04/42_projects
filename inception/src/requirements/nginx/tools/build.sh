#!/bin/bash

CERT_DIR="/etc/nginx/ssl"

openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
  -subj "/C=BE/ST=Antwerp/L=Antwerp/O=42/OU=Inception/CN=${DOMAIN}" \
  -keyout ${CERT_DIR}/nginx.key \
  -out ${CERT_DIR}/nginx.crt

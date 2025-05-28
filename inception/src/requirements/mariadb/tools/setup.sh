#!/bin/bash

service mysql start

while ! mysqladmin ping --silent; do
    sleep 1
done

cat << EOF > /tmp/init.sql
CREATE DATABASE IF NOT EXISTS ${DB_NAME};
CREATE USER IF NOT EXISTS '${ADMIN_USER}'@'%' IDENTIFIED BY '${ADMIN_PASS}';
GRANT ALL PRIVILEGES ON ${DB_NAME}.* TO '${ADMIN_USER}'@'%';
ALTER USER 'root'@'localhost' IDENTIFIED BY '${ROOT_PASS}';
FLUSH PRIVILEGES;
EOF

mysql < /tmp/init.sql
kill $(cat /var/run/mysqld/mysqld.pid)
exec mysqld
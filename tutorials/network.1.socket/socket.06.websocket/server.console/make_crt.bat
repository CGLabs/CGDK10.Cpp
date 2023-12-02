openssl genrsa -out tutorial_server.key 2048

openssl req -new -key tutorial_server.key -out tutorial_server.csr -config tutorial_server.cnf

openssl x509 -req -days 3650 -in tutorial_server.csr -signkey tutorial_server.key -out tutorial_server_crt
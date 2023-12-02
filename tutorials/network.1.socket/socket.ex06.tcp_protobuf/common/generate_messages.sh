PATH_NAME=$(dirname $(realpath $0))
protoc messages.proto --cpp_out=./

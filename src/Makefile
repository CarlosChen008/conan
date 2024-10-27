SHELL=/bin/bash
export PKG_CONFIG_PATH=/home/carlos/workspace/conan/build # need manaul execute

GRPC_DEPS:=$(shell pkg-config --cflags --libs grpc++ protobuf)

CC=g++ -std=c++17 -static -O3

proto:
	../bin/protoc --cpp_out=. helloworld.proto
	../bin/protoc --grpc_out=. --plugin=protoc-gen-grpc=../bin/grpc_cpp_plugin helloworld.proto

server:
	@echo $(SHELL)
	$(CC) server.cpp helloworld.pb.cc helloworld.grpc.pb.cc -o server.bin $(GRPC_DEPS)

client:
	$(CC) client.cpp helloworld.pb.cc helloworld.grpc.pb.cc -o client.bin $(GRPC_DEPS)

test_spdlog:
	$(CC) test_spdlog.cpp -o test_spdlog.bin $(shell pkg-config --cflags --libs spdlog)

test_rapidjson:
	$(CC) test_rapidjson.cpp -o test_rapidjson.bin $(shell pkg-config --cflags --libs rapidjson)

test_redis:
	$(CC) test_redis++.cpp -o test_redis++.bin -DREDIS_PLUS_PLUS_BUILD_ASYNC=libuv $(shell pkg-config --cflags --libs libuv-static redis++)

test_pybind11:
	g++ test_pybind11.cpp -o test_pybind11.so -O3 -Wall -shared -fPIC $(shell python3 -m pybind11 --includes)

clean:
	rm -rf *.bin *.o


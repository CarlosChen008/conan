SHELL := /bin/bash
export PKG_CONFIG_PATH := /home/carlos/workspace/conan/build

CC := g++ -std=c++17 -O3 -fPIC -Wl,--as-needed -static

GRPC_DEPS := $(shell pkg-config --cflags --libs grpc++ protobuf)

.PHONY: proto server client test_spdlog test_rapidjson test_redis test_pybind11 clean

all: proto test_spdlog test_rapidjson test_redis test_pybind11

proto:
	../bin/protoc --cpp_out=. ./proto/helloworld.proto
	../bin/protoc --grpc_out=. --plugin=protoc-gen-grpc=../bin/grpc_cpp_plugin ./proto/helloworld.proto

server:
	@echo "Using shell: $(SHELL)"
	$(CC) server.cpp ./proto/helloworld.pb.cc ./proto/helloworld.grpc.pb.cc -Wl,--start-group ${GRPC_DEPS} -Wl,--end-group -o server.bin

client:
	$(CC) client.cpp ./proto/helloworld.pb.cc ./proto/helloworld.grpc.pb.cc -Wl,--start-group ${GRPC_DEPS} -Wl,--end-group -o client.bin

test_spdlog:
	$(CC) test_spdlog.cpp -o test_spdlog.bin $(shell pkg-config --cflags --libs spdlog)

test_rapidjson:
	$(CC) test_rapidjson.cpp -o test_rapidjson.bin $(shell pkg-config --cflags --libs rapidjson)

test_redis:
	$(CC) test_redis++.cpp -o test_redis++.bin -DREDIS_PLUS_PLUS_BUILD_ASYNC=libuv $(shell pkg-config --cflags --libs libuv-static redis++)

test_abseil:
	$(CC) test_abseil.cpp -Wl,--start-group $(shell pkg-config --cflags --libs abseil) -Wl,--end-group -o test_absl.bin

test_pybind11:
	g++ -std=c++17 -O3 -Wall -shared -fPIC -pthread test_pybind11.cpp -o test_pybind11.so $(shell python3 -m pybind11 --includes)

test_libnpy:
	$(CC) test_libnpy.cpp $(shell pkg-config --cflags --libs libnpy) -o test_libnpy.bin

clean:
	rm -rf *.bin *.o *.so proto/*.pb.cc proto/*.pb.h


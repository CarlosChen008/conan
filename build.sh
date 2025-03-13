mkdir -p ./build ./conf ./data ./logs
rm -rf ./build/*
conan install . --build=missing --output-folder=./build

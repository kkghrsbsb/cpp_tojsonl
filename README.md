parquet,text转jsonl的cpp方法（遍历文件目录，并生成对应的jsonl） ，根目录创建input文件夹放要转的数据，转成的jsonl会生成在output文件夹

## 如何使用
### 1. 克隆并拉取子模块
```
git clone --recurse-submodules https://github.com/kkghrsbsb/cpp_tojsonl.git
cd cpp_tojsonl
```

### 2. 初始化 vcpkg（只需第一次）
```
cd thirdparty/vcpkg
.\bootstrap-vcpkg.bat
cd ../..
```

### 3. 创建构建目录
```
mkdir build
cd build
```

### 4. 使用vcpkg toolchain并构建Release（确保cmake已安装）
```
cmake .. -DCMAKE_TOOLCHAIN_FILE=../thirdparty/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release
```

### 5. 编译
```
cmake --build . --config Release
```

# CAD C++ 通用配置与库模块说明

## 概述
本模块专为 CAD 项目设计，主要用于存放配置相关的文件以及通用的 C++ 库。其目的在于为 CAD 项目提供统一的配置管理，同时封装可复用的功能模块，以提高代码的可维护性和可扩展性。

## 目录结构
- `config/`：此目录用于存放项目的配置文件，例如环境配置、CAD 相关的参数设置等。
- `libs/`：该目录存放通用的 C++ 库文件，这些库可被 CAD 项目中的其他模块复用。

## 配置文件说明
- `config/cad_env.config`：CAD 环境配置文件，涵盖了开发、测试和生产环境下的 CAD 相关配置信息，如默认绘图单位、精度等。
- `config/cad_api.config`：CAD API 配置文件，定义了项目中使用的 CAD API 接口地址和相关参数。

## 通用库说明
- `libs/utils.h` 和 `libs/utils.cpp`：通用工具函数库，包含常用的工具函数，如数学计算辅助函数、文件操作工具、字符串处理等。
- `libs/http.h` 和 `libs/http.cpp`：HTTP 请求库，封装了常用的 HTTP 请求方法，方便与后端 CAD 数据 API 进行交互。

## 使用方法

### 配置文件
在项目中使用配置文件时，你可以通过读取文件内容来获取配置信息。以下是一个简单的示例：
```cpp
#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream envConfigFile("config/cad_env.config");
    if (envConfigFile.is_open()) {
        std::string line;
        while (std::getline(envConfigFile, line)) {
            std::cout << line << std::endl;
        }
        envConfigFile.close();
    } else {
        std::cerr << "Unable to open config file" << std::endl;
    }
    return 0;
}
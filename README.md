# Vehicle Rental Management System

这是一个 C++ 期末课程项目，该项目为一个车辆租赁管理系统。系统支持轿车和摩托车两类车辆的管理，包含车辆添加、显示、搜索、租赁、归还、更新、统计分析以及文件保存和加载等功能。

## 1. 项目功能

### 1.1 车辆管理

- 添加车辆
- 显示所有车辆
- 显示可租车辆
- 显示已租车辆
- 按车牌号搜索车辆
- 按品牌搜索并显示车辆
- 更新车辆基础信息

### 1.2 租赁业务

- 根据车牌号租出车辆
- 输入租车人和租赁天数
- 自动计算租金
- 归还车辆
- 检查车辆是否已经租出

### 1.3 数据管理

- 保存车辆数据到 CSV 文件
- 从 CSV 文件加载车辆数据
- 统计车辆总数、可租车辆数、已租车辆数和总日租金
- 按日租金、年份、品牌、车牌号排序

## 2. 使用的 C++ 技术

本项目综合使用了以下 C++ 知识点：

- 类与对象
- 继承
- 多态
- 虚函数与纯虚函数
- 虚析构函数
- 封装与 getter / setter
- 模板类
- 动态内存管理
- STL 容器：`vector`、`map`
- STL 算法：`find_if`、`count_if`、`sort`
- Lambda 表达式
- 文件 I/O：`ifstream`、`ofstream`
- CSV 文件解析
- 异常处理：`try`、`catch`、`throw`

## 3. 类结构

```text
Vehicle
├── Car
└── Motorcycle
```

### 3.1 Vehicle

`Vehicle` 是抽象基类，保存车辆共有信息：

- 车牌号
- 品牌
- 型号
- 年份
- 日租金
- 是否已租出
- 租车人姓名

### 3.2 Car

`Car` 继承自 `Vehicle`，包含轿车特有信息：

- 车门数量
- 燃料类型
- 是否有空调

### 3.3 Motorcycle

`Motorcycle` 继承自 `Vehicle`，包含摩托车特有信息：

- 排量
- 摩托车类型
- 是否有侧斗

### 3.4 VehicleManager

`VehicleManager` 是模板管理类，负责车辆数据管理。

主要成员包括：

```cpp
vector<T*> vehicles;
map<string, T*> plateIndex;
```

其中：

- `vehicles` 用于保存所有车辆指针，方便遍历、显示、排序和统计。
- `plateIndex` 用于建立车牌号到车辆指针的映射，方便根据车牌号快速查找车辆。

## 4. 项目文件结构

如果使用标准文件夹结构，项目可以组织为：

```text
VehicleRentalSystem/
├── include/
│   ├── Vehicle.h
│   ├── Car.h
│   ├── Motorcycle.h
│   └── VehicleManager.h
├── src/
│   ├── Main.cpp
│   ├── Vehicle.cpp
│   ├── Car.cpp
│   └── Motorcycle.cpp
├── data/
│   └── vehicles.csv
├── README.md
└── .gitignore
```

如果没有拆分 `include/` 和 `src/` 文件夹，也可以将所有 `.h` 和 `.cpp` 文件放在同一个目录下。

## 5. 编译和运行

### 5.1 所有文件在同一目录下

如果所有 `.h` 和 `.cpp` 文件都在同一个文件夹中，可以使用：

```bash
g++ -std=c++17 Main.cpp Vehicle.cpp Car.cpp Motorcycle.cpp -o rental
./rental
```

### 5.2 使用 include 和 src 文件夹

如果项目结构为：

```text
include/
src/
data/
```

可以使用：

```bash
g++ -std=c++17 src/*.cpp -Iinclude -o rental
./rental
```

如果希望把可执行文件放到 `build/` 文件夹中，可以使用：

```bash
mkdir -p build
g++ -std=c++17 src/*.cpp -Iinclude -o build/rental
./build/rental
```

## 6. CSV 文件格式

系统使用 CSV 文件保存车辆数据。

### 6.1 Car 格式

```csv
Car,车牌号,品牌,型号,年份,日租金,是否已租,租车人,车门数,燃料类型,是否有空调
```

示例：

```csv
Car,A1001,Toyota,Camry,2022,300,0,,4,Gasoline,1
```

### 6.2 Motorcycle 格式

```csv
Motorcycle,车牌号,品牌,型号,年份,日租金,是否已租,租车人,排量,车型,是否有侧斗
```

示例：

```csv
Motorcycle,B2001,Honda,CB500F,2021,180,0,,500,Street,0
```

### 6.3 字段说明

- `0` 表示 `false`
- `1` 表示 `true`
- 如果车辆未租出，租车人字段为空

例如：

```csv
Car,A1001,Toyota,Camry,2022,300,0,,4,Gasoline,1
```

其中：

```text
0,,4
```

表示：

```text
未租出
租车人为空
车门数为 4
```

## 7. 主菜单

程序运行后显示主菜单：

```text
===============================================
       Vehicle Rental Management System
===============================================
1. Add Vehicle
2. Display All Vehicles
3. Display Available Vehicles
4. Display Rented Vehicles
5. Search Vehicle
6. Rent Vehicle
7. Return Vehicle
8. Update Vehicle Information
9. Statistics
10. File Operations
11. Exit
===============================================
```

## 8. 异常和边界处理

系统包含以下异常和边界处理：

- 添加车辆时检查车牌号是否重复
- 添加车辆时检查年份、日租金、车门数、排量是否合法
- 租车时检查租赁天数是否合法
- 租车时检查车辆是否存在
- 租车时检查车辆是否已经租出
- 还车时检查车辆是否存在
- 还车时检查车辆是否已经租出
- 显示、统计、排序、保存时检查系统是否为空
- 文件加载时检查文件是否能够成功打开
- 文件保存时检查文件是否能够成功打开
- 加载 CSV 文件时检查字段数量是否合法

## 9. 测试数据

示例数据文件位于：

```text
data/vehicles.csv
```

可以通过菜单中的 File Operations 功能加载或保存数据。

## 10. 项目说明

本项目为 C++ 面向对象程序设计期末作业，主要用于练习以下内容：

- 面向对象程序设计
- 类继承体系设计
- 多态与虚函数
- 模板类
- STL 容器与算法
- 动态内存管理
- 文件读写与 CSV 数据持久化
- 基础异常处理

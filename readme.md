# MeshSimplifier
使用vcglib和Meshlab实现的网格简化器。
* 可以处理non-manifold类型的网格体
* 提供了vcglib和libigl模型数据之间的转换，可以在libigl的环境下调用
* 无需手动安装依赖
## 使用方法
本项目使用xmake构建，先到官网安装：https://xmake.io/#/zh-cn/getting_started

随后运行：
```
git clone https://github.com/hytracen/MeshSimplifier.git
cd MeshSimplifier
xmake
```
构建成功后，修改main.cpp：
```c++
std::string input_model_path{R"()"};  // 待减面的模型路径
std::string output_model_path{R"()"}; // 减面后模型的输出路径
int target_faces_count{1000};         // 简化后的模型面数
```
最后输入如下命令运行程序：
```
xmake run
```

# FastDDS 学习笔记

### 添加预处理指令，避免使Warning变为Error
    #pragma warning(disable : 4668)
    #pragma warning(disable : 4530)
    #pragma warning(disable : 4582)
    #pragma warning(disable : 4265)
### 根据VS的运行Log，确定UE中需要引入哪些dll和lib
![img.png](img.png)

### 注意Preprocessor Definitions，忽略可能的lib依赖
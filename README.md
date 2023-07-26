# FastDDS 学习笔记

### 添加预处理指令，避免使Warning变为Error
    #pragma warning(disable : 4668)
    #pragma warning(disable : 4530)
    #pragma warning(disable : 4582)
    #pragma warning(disable : 4265)
### 根据VS的运行Log，确定UE中需要引入哪些dll和lib
![img.png](img.png)

### 注意Preprocessor Definitions，忽略可能的lib依赖

### 注意jdk版本
![img_1.png](img_1.png)

### colon build失败的时候，可以clean之后再重新build

### 无法直接import fastdds，要先引入dll
![img_2.png](img_2.png)

### 注意编译python binding与使用python binding所用python版本一致

### 防火墙会导致subscriber找不到publisher
    加入对应应用程序即可 eg. python.exe
![img_3.png](img_3.png)

### 后缀改为cpp，就可以顺利链接了。如果后缀为cxx，则需要引入.lib
![img_4.png](img_4.png)

### 头文件顺序错误也会报错

### 遇到exception，使用Visual Studio查看完整信息，平时编码使用Rider方便


### 源码编译的好处
    预编译可能无debug symbol，定位到dll中的源码异常位置
    即使有debug版本的dll，但是编译设置和UE编译设置不同，无法顺利链接
![img_5.png](img_5.png)

![img_6.png](img_6.png)

### Visual Studio Code 处理merge conflicts好用

![img_7.png](img_7.png)

### 无法使用插件中的非UE类？
![img_8.png](img_8.png)
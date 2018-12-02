https://github.com/Tabris2016/Push_A_Ball/blob/master/README.md

# 鼠标推球（暂定）

## 系统要求

系统环境：
Qt5; OpenGl; VS2017 or MingW

准备工具：

依赖包简介

### 运行
```c++
XXX.exe
```

## 用户说明
执行 XXX.exe后
会提示导入stl模型文件（建议搞几个template）
1. 鼠标可推动模型滚动
2. 方向键可控制模型滚动。

*附加：
1. 多个模型
2. 碰撞、抛物等仿真实验

效果图：

![image]()


## 任务分工
 ### 架构：
 程序框架搭建、接口规范、任务协调
 
 ### UI层：
 实现用户界面、管理交互事件
 
 需实现：
 1. 监视鼠标键盘事件，并发出SIGNAL
 2. STL文件导入事件对应SLOTS
 3. 物理参数输入
 
```    
onClicked_STLbtn()    //STL导入按键事件
onMousePressed()  //鼠标长按事件，返回鼠标位置
onKeyboardEvent() //键盘输入事件，返回按下的键位
 ```
 ### 逻辑层：
 根据UI提供的信号，对数据层进行操作
 
 需实现：
 1. 接收键鼠信号并调用相应函数
  
 ### 数据层
实现STL模型的显示与基本位姿操作
 
 需实现：
 1. STL模型导入与显示
 2. 球体类
 
```    
getSTL()    //STL导入函数
Class Sphere{ //球体类
public:
    position
    X_Move();Y_Move();Z_Move();
    X_Rotate();Y_Rotate();Z_Rotate();
private:
    size, 
}
 ```


# Altium designer使用笔记

> 版本号:19.0.12
>
> 参考视频:
>
> https://www.bilibili.com/video/BV16t411N7RD?from=search&seid=898203580791670029
>
> https://www.bilibili.com/video/BV17b411W7P8?p=5 (速成)
>
> https://zhuanlan.zhihu.com/p/28567846

## 基础操作

1. 中文

   <img src="https://gitee.com/sun-roc/picture/raw/master/img/image-20200525160030582.png" alt="image-20200525160030582" style="zoom: 50%;" />

2. 创建工程

   <img src="https://gitee.com/sun-roc/picture/raw/master/img/image-20200525160133598.png" alt="image-20200525160133598" style="zoom:50%;" />

3. 添加PCB和原理图

   <img src="https://gitee.com/sun-roc/picture/raw/master/img/image-20200525160219551.png" alt="image-20200525161315384" style="zoom:50%;" />

   4. 新建原理图库和原件库

      <img src="https://gitee.com/sun-roc/picture/raw/master/img/image-20200525161315384.png" alt="image-20200525160219551" style="zoom:50%;" />

      
   
   5. AD库文件: 每一个AD软件中都包含2个基础库Miscellaneous Devices.IntLib和Miscellaneous Connectors.IntLib。Miscellaneous Devices.IntLib库中主要包含了我们比较常用的电阻、电容、电感、控制芯片等之类的东西（当让里面也就电阻、电容这些小物件我们一开始使用芯片之类的都比较过时了），Miscellaneous Connectors.IntLib库中主要包含了我们常见的接口库。我们初学时都可以用着写基础库，当然当需要一些这两个基础库中没有的元器件又不会自己制作库时，我们可以去Altium官网[http://www.altium.com/](https://link.zhihu.com/?target=http%3A//www.altium.com/)去寻找下载（里面包含许多免费的元件库都是官方提供比较标准）。
   
   6. 侧边栏多数从panel键找
   
      <img src="https://gitee.com/sun-roc/picture/raw/master/img/image-20200525164929465.png" alt="image-20200525164929465" style="zoom:50%;" />

## 原理图库and元件库

基本上schlib把带编号的导入即可,pcblib一股脑全导入

sop:贴片

ic:芯片

### 从已有库中获取

1. 安装库小齿轮里,或者自己右键(这是直接安装每次打开都有)

   ![image-20200527182128136](https://gitee.com/sun-roc/picture/raw/master/img/image-20200602221217344.png)

   <img src="https://gitee.com/sun-roc/picture/raw/master/img/image-20200525170444102.png" alt="image-20200526165234757" style="zoom:50%;" />

   

2. 不安装直接打开法

   可以把lib直接打开,把需要的原件直接copy到自己的元件库中,一劳永逸

3. 还可以把已经绘制好的原理图

### 新方法(封装统一管理)

当同时把原理图库和PCB库导入时

从原理图库中查找的会自动匹配PCB库,这个PCB库没导入时就会匹配失败

在原理图放置页面单击"工具""封装管理"进行自行导入,也可以通过验证按钮自行查找

也可把从库中找到的复制到doc,再复制到自己的库中构成自己的库

### 自己绘制(v+g+s设置捕捉格栅为100)

![image-20200525170444102](https://gitee.com/sun-roc/picture/raw/master/img/image-20200527182128136.png)

![](https://gitee.com/sun-roc/picture/raw/master/img/image-20200526165549532.png)



ID是原件名称,Dsignator是原件编号,comment是注释可有可无

### 所有原件库中查找()

这里可以选择是描述,姓名,footprint种种,**不识别中文**

![image-20200602221238570](https://gitee.com/sun-roc/picture/raw/master/img/image-20200602221238570.png)

遇事多找找封装里既有排针又有排母,名字对的上就行

![image-20200602225912128](https://gitee.com/sun-roc/picture/raw/master/img/image-20200602225912128.png)

## 原理图绘制

### 1. 选择原件

从components里进行选择拖过来即刻

### 2. 导线(ctrl+w)有电气属性的

<img src="https://gitee.com/sun-roc/picture/raw/master/img/image-20200526165234757.png" alt="image-20200526165549532" style="zoom:50%;" />

### 3. 网络标号

放置菜单里有**网络标号**按住tab键修改命名,之后可以自动添加

### 4.自动原件编号

TAA,即可

![image-20200527182621907](https://gitee.com/sun-roc/picture/raw/master/img/image-20200527182349801.png)



### 5. 封装导入

![image-20200527182349801](https://gitee.com/sun-roc/picture/raw/master/img/image-20200527182621907.png)

![image-20200527183132365](https://gitee.com/sun-roc/picture/raw/master/img/image-20200527182605395.png)



批量更改,把库里的改了然后选择从库中更新

单个双击

然后updatePCB

<img src="https://gitee.com/sun-roc/picture/raw/master/img/image-20200603095956648.png" alt="image-20200527183206525" style="zoom:50%;" />

### 编译查看错误

![image-20200527182605395](https://gitee.com/sun-roc/picture/raw/master/img/image-20200527183132365.png)

![image-20200603095956648](https://gitee.com/sun-roc/picture/raw/master/img/image-20200527183206525.png)



floating :网络悬浮,指的是网络编号没有跟导线末端对齐,**不管是电源还是接地都是从外面引进来的,单独放一个都不行**

only one pin: 没有相对应的网络编号,没连上

### 生成PCB图

<img src="https://gitee.com/sun-roc/picture/raw/master/img/image-20200603095956648.png" alt="image-20200527183206525" style="zoom:50%;" />

用这个也可以

<img src="https://gitee.com/sun-roc/picture/raw/master/img/image-20200603102146109.png" alt="image-20200603102549052" style="zoom:50%;" />

# PCB图绘制

报错: 

unkown pin:封装和原理图管脚不匹配,或者没有封装

failed to add class:试试编译一下,可能通过

绿色报错:把检查规则里跟电气属性无关的批量取消掉,具体的可以看凡亿教育出的

![image-20200603110853789](https://gitee.com/sun-roc/picture/raw/master/img/image-20200603102549052.png)



## 在矩形框内自动排列

![image-20200603111754576](https://gitee.com/sun-roc/picture/raw/master/img/image-20200603103814276.png)

## 快捷键设置

把鼠标放到要设置的那个选项上 ctrl+点击

然后放到选项上按动想要设置的键

PCB旋转的是,点住不放再空格旋转

Q键切换单位

![image-20200603102146109](https://gitee.com/sun-roc/picture/raw/master/img/image-20200603111754576.png)



## 自动布线

![image-20200603103814276](https://gitee.com/sun-roc/picture/raw/master/img/image-20200603105602725.png)



**移动元件后需要取消布线,再重新布线**

## 布局



选择垂直分割

![image-20200604165911341](https://gitee.com/sun-roc/picture/raw/master/img/image-20200603110853789.png)



将交叉选择模式选中

每次框选原理图,PCB中的图也会被选中

![image-20200603110918424](https://gitee.com/sun-roc/picture/raw/master/img/image-20200603110918424.png)


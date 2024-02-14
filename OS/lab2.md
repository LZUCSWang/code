### 2.键盘中断，当按下Ctrl+r 打印栈帧并重启；当按下CTRL+s 打印栈帧并关机。

#### 代码修改

​		1)通过修改`UART_QEMU_IRQ`情况下的代码实现键盘中断,修改`uart_interrupt_handler`函数及`uart_16550a_interrupt_handler`函数,使得其能够返回键盘的输入值

​			![image-20231106204845847](C:\Users\wxy43\AppData\Roaming\Typora\typora-user-images\image-20231106204845847.png)

​		2)若返回值为CTRL_R(0x12),打印栈帧并重启

​		3)若返回值为CTRL_S(0x13),打印栈帧并关机

![image-20231106195959701](C:\Users\wxy43\AppData\Roaming\Typora\typora-user-images\image-20231106195959701.png)

#### 运行结果

- **打印栈帧并重启**

  ![image-20231106203820913](C:\Users\wxy43\AppData\Roaming\Typora\typora-user-images\image-20231106203820913.png)

- **打印栈帧并关机**

  ![image-20231106203758639](C:\Users\wxy43\AppData\Roaming\Typora\typora-user-images\image-20231106203758639.png)

---



### 3.仿照断点异常的测试，测试一个其他类型的异常。

#### 代码修改

将`main`函数中添加下面代码,用来测试访问异常(非法访问)

![image-20231106204055832](C:\Users\wxy43\AppData\Roaming\Typora\typora-user-images\image-20231106204055832.png)

#### 运行结果

![image-20231106204339197](C:\Users\wxy43\AppData\Roaming\Typora\typora-user-images\image-20231106204339197.png)

出现`fault load`说明测试成功.	
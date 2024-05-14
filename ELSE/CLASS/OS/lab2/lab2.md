### 2.键盘中断，当按下Ctrl+r 打印栈帧并重启；当按下CTRL+s 打印栈帧并关机。

#### 代码修改

​		1)通过修改`UART_QEMU_IRQ`情况下的代码实现键盘中断,修改`uart_interrupt_handler`函数及`uart_16550a_interrupt_handler`函数,使得其能够返回键盘的输入值

![uart](.\pic\uart.png)

​		2)若返回值为CTRL_R(0x12),打印栈帧并重启

​		3)若返回值为CTRL_S(0x13),打印栈帧并关机

![external](.\pic\external.png)

#### 运行结果

- **打印栈帧并重启**

  ![reboot](.\pic\reboot.png)

- **打印栈帧并关机**

  ![shutdown](\pic\shutdown.png)

---



### 3.仿照断点异常的测试，测试一个其他类型的异常。

#### 代码修改

将`main`函数中添加下面代码,用来测试访问异常(非法访问)

![asm](\pic\asm.png)

#### 运行结果

![fault](\pic\fault.png)

出现`fault load`说明测试成功.	
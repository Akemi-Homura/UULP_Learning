# playagain
- 保存tty设置
- set -icanon -echo
- handle INT
- ignore QUIT signals
- get some answers
- reset tty mode

使用termios重点 c_cc[VTIME]来设置超时时间，而不是使用sleep

1) 忽略键盘信号，仅对yes和no作出反应
2) 接收到键盘信号后，重置终端属性并返回2

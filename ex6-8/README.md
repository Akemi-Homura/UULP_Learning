# playagain
- 保存tty设置
- set -icanon -echo
- handle INT
- ignore QUIT signals
- get some answers
- reset tty mode

使用termios重点 c_cc[VTIME]来设置超时时间，而不是使用sleep

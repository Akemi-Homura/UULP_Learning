# bounce async
使用`O_ASYNC`和输入信号来实现异步IO

有奇怪的bug，在没有printf的时候输入无法生效。任何情况下，Q都不生效，可能是异步IO的原因

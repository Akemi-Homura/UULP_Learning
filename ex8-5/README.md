# forkdemo5
测试程序运行结果

#### 结果分析
fprintf会把输出内容放到缓冲区中，fork时将缓冲区一起拷贝到了子进程。如果在fork之前的fprintf后加fflush，则只会输出一次msg1

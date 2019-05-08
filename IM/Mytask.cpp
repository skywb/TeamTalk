#include <iostream>
#include "reactor/task.h"
#include "IM/IMProtocol.h"


void ReadableTask::doit() {


	/* TODO: 
	 * 
	 * 1. 读取最少一个协议头
	 * 2. 读取消息
	 * 3. 判断是否还有未读信息， 有则循环
	 * 4. 执行对应的处理函数
	 * 5. 若不足一个协议头则返回nullprt  跳过
	 * <24-04-19, sky> */


}

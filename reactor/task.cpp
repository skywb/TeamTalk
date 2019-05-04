#include <iostream>
#include "reactor/task.h"
#include "IM/IMProtocol.h"


void Task::doit() {

	std::cout << "task doing..." << std::endl;
}

//void fun(std::shared_ptr<Connecter> con);
//
//void ReadableTask::doit() {
//
//	fun(p_con);
//
//
//	/* TODO: 
//	 * 
//	 * 1. 读取最少一个协议头
//	 * 2. 读取消息
//	 * 3. 判断是否还有未读信息， 有则循环
//	 * 4. 执行对应的处理函数
//	 * 5. 若不足一个协议头则返回nullprt  跳过
//	 * <24-04-19, sky> */
//
//
//}

void WriteableTask::doit() {
	/*
	 * 做可写事件处理
	 * 将缓冲区的数据写入套接字内
	 */
	p_con->onWriteable();
}


void NewConnectTask::doit() {
	/* 弃用 
	 * 接受一个或者多个新的连接
	 * 为每个新的连接创建一个connecter， 并添加到sockToConn中
	 * 想监听队列中添加一个需要监听的事件
	 * */

	std::cout << "newConnect task doing..." << std::endl;

}





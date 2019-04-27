#ifndef CMD_H_EL7F4YCT
#define CMD_H_EL7F4YCT

namespace IM 
{
	enum CMD 
	{

		INVALID = 1,

		//登录命令
		LOGIN = 11,
		LOGOUT = 12,
		REGIST = 13,

		//单人聊天命令
		SENDMSG = 20,
		RECIVEMSG = 21,
		SYNC_MSG = 22,
		//DEL_MSG = 23

		//群聊
		GROUP_SENDMSG = 30,
		GROUP_RECIVEMSG = 31,
		GROUP_SYNC_MSG = 32,

	};
}

#endif /* end of include guard: CMD_H_EL7F4YCT */

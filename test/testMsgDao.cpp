#include <boost/config/auto_link.hpp>
#include "dao/MsgDao.h"
#include "IM/IMProtocol.pb.h"


int main()
{
	Proto::Message msg;
	msg.set_fromid(1000);
	msg.set_toid(1002);
	msg.set_msg("hello");

	MsgDao::Insert(&msg);
	

	return 0;
}

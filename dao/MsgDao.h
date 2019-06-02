#ifndef MSGDAO_H_GGOHESDR
#define MSGDAO_H_GGOHESDR

#include "DB.h"
#include "IM/IMProtocol.pb.h"

class MsgDao : public DBUtil::Dao
{
public:
	virtual ~MsgDao () { }
	bool _insert(Proto::Message *msg);
	//bool _delete(Message::Account id);
	//bool _update(Message *user);
	Proto::Message* _obtain(int id);

	static bool Insert(Proto::Message *msg) { return getInstance()->_insert(msg); }
	//static bool Delete(Message::Account id) { return getInstance()->_delete(id); }
	//static bool Update(Message *user) { return getInstance()->_update(user); }
	static Proto::Message* Obtain(int id) { return getInstance()->_obtain(id); }


private:
	static MsgDao* getInstance() {return object;}
	static MsgDao* object;

	MsgDao (): Dao(MYSQLSERVERURL, MYSQLACCOUNT, MYSQLPASSWORD) { }
};

#endif /* end of include guard: MSGDAO_H_GGOHESDR */

#ifndef MSGTASK_H_2EKRGFFC
#define MSGTASK_H_2EKRGFFC

#include "loginTask.h"

class MsgTask : public Task {
public:
	MsgTask (const Proto::Request* req, std::shared_ptr<IM::IMConn> con) : request(req), p_con(con) {}
	virtual ~MsgTask () { }
	
	void doit() override;
private:
	std::shared_ptr<IM::IMConn> p_con;
	const Proto::Request* request;
	Proto::Response* response;
};

#endif /* end of include guard: MSGTASK_H_2EKRGFFC */

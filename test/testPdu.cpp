#include <iostream>

#include <gtest/gtest.h>

#include "IM/IMProtocol.h"


TEST(testPdu, Pdu1)
{
	auto login = std::make_shared<IM::LoginPdu> ();	
	login->setUserId(11);
	login->setPassword("aaaa");
}





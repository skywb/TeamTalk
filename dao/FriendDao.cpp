#include "FriendDao.h"

FriendDao* FriendDao::object = new FriendDao();

std::vector<std::pair<User::Account, int>> FriendDao::getAllFriendsByID(User::Account id) { 
	auto stat = conn->prepareStatement("select friendID, groupID from friends where Userid = ?"); 
	stat->setInt(1, id);

	auto res = stat->executeQuery();
	std::vector<std::pair<User::Account, int> > vec;
	while(res->next()) {
		vec.push_back(std::pair<User::Account, int> (res->getUInt64(1), res->getInt(2)));
	}
	delete  stat;
	return vec;

}
bool FriendDao::addFriend(User::Account id, User::Account friendID, int groupIDInThisAccount) {
	
	auto stat = conn->prepareStatement("insert into friends(UserID, friendID, groupID) values(?, ?, ?)"); 
	stat->setUInt64(1, id);
	stat->setUInt64(2, friendID);
	stat->setInt(3, groupIDInThisAccount);
	stat->execute();
	delete  stat;
	return true;
}

bool FriendDao::delFriend(User::Account id, User::Account friendID) {
	auto stat = conn->prepareStatement("delete from friends where UserID = ? and friendID = ?"); 
	stat->setUInt64(1, id);
	stat->setUInt64(2, friendID);
	stat->execute();
	delete  stat;
	return true;
}

std::string FriendDao::getGroupNameByID(int ID) {
	auto stat = conn->prepareStatement("select GroupName from friendgroups where GroupID = ?"); 
	stat->setUInt64(1,ID);
	auto res = stat->executeQuery();
	std::string name;
	if(res->next()) {
		name = res->getString(1);
	}
	delete  stat;
	return name;
}

std::string FriendDao::getGroupNameByID(User::Account UserID, int groupIDInUser) {
	auto stat = conn->prepareStatement("select GroupName from friendgroups where OwnerID = ? and GroupIDByOwner = ?"); 
	stat->setUInt64(1,UserID);
	stat->setUInt64(2,groupIDInUser);
	auto res = stat->executeQuery();
	std::string name;
	if(res->next()) {
		name = res->getString(1);
	}
	delete  stat;
	return name;
}

bool FriendDao::updateGroupName(User::Account userID, int groupIdInThisUser, const std::string name) {
	auto stat = conn->prepareStatement("update friendgroups set GroupName = ? where OwnerID = ? and GroupIDByOwner = ?"); 
	stat->setString(1, name);
	stat->setUInt64(2, userID);
	stat->setUInt64(3, groupIdInThisUser);
	auto res = stat->executeUpdate();
	delete  stat;
	return res == 1;
	
}
bool FriendDao::delGroup(User::Account userID, int groupIdInThisUser) {
	auto stat = conn->prepareStatement("delete from friendgroups where OwnerID = ? and GroupIDByOwner = ?"); 
	stat->setUInt64(1, userID);
	stat->setUInt64(2, groupIdInThisUser);
	auto res = stat->execute();
	delete  stat;
	return res;
}

int FriendDao::addGroup(User::Account userID, const std::string groupName) {
	auto stat = conn->prepareStatement("select GroupIDByOwner from friendgroups where OwnerID = ?"); 
	stat->setUInt64(1, userID);
	auto res = stat->executeQuery();
	int i = 1;
	while(res->next()) {
		if(res->getInt(1) != i++) break;
	}
	delete stat;

	stat = conn->prepareStatement("insert into friendgroups(GroupIDByOwner, OwnerID, GroupName) values(?, ?, ?)"); 

	stat->setUInt64(1, i);
	stat->setUInt64(2, userID);
	stat->setString(3, groupName);
	auto re = stat->execute();
	delete  stat;
	return 1;
}



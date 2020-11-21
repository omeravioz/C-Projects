/********************************************
File name : sorted_list.c
Author : Omer Avioz
Reviewer : Elior Nataf
Infinity Labs OL95	
*******************************************/

#include "uid.h"

static size_t COUNTER = 0;
ilrd_uid_t BAD_UID = {0};

ilrd_uid_t UIDCreate(void)
{
	ilrd_uid_t uid = {0};
	
	uid.time_stamp = time(NULL);
	uid.process_id = getpid();
	uid.number_id = ++COUNTER;
	
	if(0 == uid.time_stamp || 0 == uid.process_id)
	{
		return BAD_UID;
	}
	
	return uid;
	
}

int UIDIsSame(ilrd_uid_t uid1, ilrd_uid_t uid2)
{
	return (uid1.time_stamp == uid2.time_stamp &&
			uid1.process_id == uid2.process_id &&
			uid1.number_id == uid2.number_id);
	
	
}

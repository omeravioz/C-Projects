/*******************************************************************************
*********************************HEADER-FILE************************************
* Description:  API of the unique identifier functions.
* Date: 13.10.2020										 
* InfinityLabs OL95	
********************************************************************************
*******************************************************************************/
/*--------------------------------- Header Guard -----------------------------*/

#ifndef __ILRD_OL95_UID_H__
#define __ILRD_OL95_UID_H__

/*-------------------------- HEADER FILES ------------------------------------*/
#include <stddef.h> /* size_t */
#include <time.h>	/* time_t */
#include <unistd.h> /* pid_t */
#include <sys/types.h>	/* pid_t */
/*------------------------- TYPEDEF ------------------------------------------*/

typedef struct
{
	time_t time_stamp;
	pid_t process_id;
	size_t number_id;

}ilrd_uid_t;

extern ilrd_uid_t BAD_UID;
/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that creates a new unique identifier uid.
 * in case the create failed a non valid UID 
 * Time complexity: O(1)
 *
 * PARAMETERS:
 * function does not take any parameters
 *
 * RETURN VALUE:
 * ilrd_uid_t  -  new created uid in case of failure returns a BAD_UID assign to zero
 */
ilrd_uid_t UIDCreate(void);

/*----------------------------------------------------------------------------*/

/* DESCRIPTION:
 * A function that checks if two uids are the same.
 * 
 * Time complexity: O(1) 
 *
 * PARAMETERS:
 * ilrd_uid_t uid1 - sorted uid.
 * ilrd_uid_t uid2 - sorted uid.
 *
 * In case of invalid uids behavior is undefined.
 *
 * RETURN VALUE:
 * int * - zero ifsucceed, non-zero if failed.
 */
int UIDIsSame(ilrd_uid_t uid1, ilrd_uid_t uid2);

/*----------------------------------------------------------------------------*/
#endif /* __ILRD_OL95_UID_H__ */

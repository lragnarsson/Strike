/***************************************
MessageCodes.h

Defines headers for messages

Written by:
Erik Sk�ld
***************************************/

#ifndef _MESSAGECODES_
#define _MESSAGECODES_

//protocol defines
const int TCP = 10;
const int UDP = 11;

const int EMPTY_MESSAGE = 500;

//networkHandler internal messages
const int CLIENT_NOTIFY_UDP_PORT = 1001;
const int SERVER_ACCEPT_CONNECTION = 1002;

const int INTERNAL_MESSAGE_LIMIT = 1999;

//
const int ADD_PLAYER = 2001;
const int CONSOLE_PRINT_STRING = 2002;
const int INITIAL_INFORMATION = 2003;

const int PLAYER_UPDATE = 3000;
const int ADD_SHOT = 3001;
const int ROUND_RESTART = 3002;
const int GAME_OBJ_UPDATE = 3003;


#endif // _MESSAGECODES_

/***************************************
MessageCodes - Definition av olika meddelandens header

Skriven av:
Erik Sköld
***************************************/
#ifndef MESSAGECODES_H
#define MESSAGECODES_H

const int EMPTY_MESSAGE = 1;

//networkHandler internal messages
const int CLIENT_NOTIFY_UDP_PORT = 1001;

const int INTERNAL_MESSAGE_LIMIT = 1999;

//
const int SERVER_ACCEPT_CONNECTION = 2000;
const int ADD_PLAYER = 2001;
const int CONSOLE_PRINT_STRING = 2002;
const int INITIAL_INFORMATION_FROM_CLIENT = 2003;

const int PLAYER_UPDATE = 3000;
const int ADD_SHOT = 3001;
const int ROUND_RESTART = 3002;


#endif // MESSAGECODES_H

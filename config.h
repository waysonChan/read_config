/*
read_config, confguration parser

Copyright (c) 2017 Thomas Wink <thomas@geenbs.nl>

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/
#ifndef config_H_
#define config_H_
#include "uart.h"
#include "ntrip_client.h"

typedef struct{
    //server info
    char server[32];
    char user[16];
    char password[16];
    char nmea[128];
    char data[16];
}server_config; 

int get_uart_config(portinfo_t *config, char *fileName);
int get_server_config(struct ServerInfo *config, char *fileName);

#endif

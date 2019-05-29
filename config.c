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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#define MAXLEN 128

static server_config sev_cfg;

int get_uart_config(portinfo_t *config, char *fileName){
    size_t lineNr = 0;
    FILE *fp;
    fp = fopen(fileName, "r");

    if(fp != NULL){
        while(!feof(fp)){
            lineNr++;
            char sKey[MAXLEN] = {0};
            char sVal[MAXLEN] = {0};

            int rc = fscanf(fp, "\n%[^=]=%s[^\n]\n", sKey, sVal);
            if(rc == 0){
                printf("\tError in '%s', line number %zu\n", fileName, lineNr);
                return -1;
            }          
 
            size_t keyLen = strlen(sKey);
            size_t valLen = strlen(sVal);

            if(keyLen > MAXLEN || valLen > MAXLEN){
               printf("\nSorry, maximum length of key value exceeded (%d)\n", MAXLEN);
               return 1;
            }

            if(strcmp(sKey, "prompt") == 0){
                memcpy(&config->prompt, sVal, valLen);
                //printf("%s[%d]config->prompt=%c\n", __func__, __LINE__, config->prompt); 
            }

            if(strcmp(sKey, "baudrate") == 0){
               config->baudrate = (int)strtol(sVal, (char **)NULL, 10);
               //printf("%s[%d]config->baudrate=%d\n", __func__, __LINE__, config->baudrate); 
            }

            if(strcmp(sKey, "databit") == 0){
                memcpy(&config->databit, sVal, valLen);
                //printf("%s[%d]config->databit=%c\n", __func__, __LINE__, config->databit); 
            }

            if(strcmp(sKey, "debug") == 0){
                memcpy(&config->debug, sVal, valLen);
                //printf("%s[%d]config->debug=%c\n", __func__, __LINE__, config->debug); 
            }

            if(strcmp(sKey, "echo") == 0){
                memcpy(&config->echo, sVal, valLen);
                //printf("%s[%d]config->echo=%c\n", __func__, __LINE__, config->echo); 
            }

            if(strcmp(sKey, "fctl") == 0){
                memcpy(&config->fctl, sVal, valLen);
                //printf("%s[%d]config->fctl=%c\n", __func__, __LINE__, config->fctl); 
            }

            if(strcmp(sKey, "tty") == 0){
                memcpy(&config->tty, sVal, valLen);
                //printf("%s[%d]config->tty=%c\n", __func__, __LINE__, config->tty); 
            }

            if(strcmp(sKey, "parity") == 0){
                memcpy(&config->parity, sVal, valLen);
                //printf("%s[%d]config->parity=%c\n", __func__, __LINE__, config->parity); 
            }

            if(strcmp(sKey, "stopbit") == 0){
                memcpy(&config->stopbit, sVal, valLen);
                //printf("%s[%d]config->stopbit=%c\n", __func__, __LINE__, config->stopbit); 
            }
        }
    }else{
        //Pocess error
        return 1;
    }
    fclose(fp);
    return 0;
}

int get_server_config(struct ServerInfo *config, char *fileName){
    size_t lineNr = 0;
    FILE *fp;
    fp = fopen(fileName, "r");

    if(fp != NULL){
        while(!feof(fp)){
            lineNr++;
            char sKey[MAXLEN];
            char sVal[MAXLEN];

            int rc = fscanf(fp, "\n%[^=]=%s[^\n]\n", &sKey[0], sVal);
            if(rc == 0){
                printf("\tError in '%s', line number %zu\n", fileName, lineNr);
                return -1;
            }

            size_t keyLen = strlen(sKey);
            size_t valLen = strlen(sVal);
            
            if(keyLen > MAXLEN || valLen > MAXLEN){
               printf("\nSorry, maximum length of key value exceeded (%d)\n", MAXLEN);
               return 1;
            }

            if(strcmp(sKey, "server") == 0){
                memcpy(sev_cfg.server, sVal, valLen);
                config->server = sev_cfg.server;
                //printf("%s[%d]config->server=%s\n", __func__, __LINE__, config->server); 
            }

            if(strcmp(sKey, "port") == 0){
               config->port = (int)strtol(sVal, (char **)NULL, 10);
               //printf("%s[%d]config->port=%d\n", __func__, __LINE__, config->port); 
            }

            if(strcmp(sKey, "user") == 0){
                memcpy(sev_cfg.user, sVal, valLen);
                config->user = sev_cfg.user;
                //printf("%s[%d]config->user=%s\n", __func__, __LINE__, config->user); 
            }
          
            if(strcmp(sKey, "password") == 0){
                memcpy(sev_cfg.password, sVal, valLen);
                config->password = sev_cfg.password;
                //printf("%s[%d]config->password=%s\n", __func__, __LINE__, config->password); 
            }
        
            if(strcmp(sKey, "nmea") == 0){
                memcpy(sev_cfg.nmea, sVal, valLen);
                config->nmea = sev_cfg.nmea;
               //printf("%s[%d]config->nmea=%s\n", __func__, __LINE__, config->nmea);
            }
            
            if(strcmp(sKey, "data") == 0){
                memcpy(sev_cfg.data, sVal, valLen);
                config->data = sev_cfg.data;
               //printf("%s[%d]config->data=%s\n", __func__, __LINE__, config->data);
            }

            if(strcmp(sKey, "bitrate") == 0){
               config->bitrate = (int)strtol(sVal, (char **)NULL, 10);
               //printf("%s[%d]config->bitrate=%d\n", __func__, __LINE__, config->bitrate); 
            }
        }
    }else{
        //Pocess error
        return 1;
    }
    fclose(fp);
    return 0;
}

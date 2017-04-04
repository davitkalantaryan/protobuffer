/*
 *	File      : test/main_receiver_test.cpp
 *
 *	Created on: 04 Apr, 2017
 *	Author    : Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *
 */
#include <asockettcp.h>
#include "protosystemcommon.h"
#include <signal.h>
#include <stdio.h>
#include "receiver.pb.h"
#include <malloc.h>
#include <iostream>
#include <unistd.h>

#define BUFFER_SIZE     131072
#define DEFAULT_SERVER_HOST "mtcapitzcpu1"
#define SIGNAL_ARGUMENTS    int a_nSigNum, siginfo_t * /*a_pSigInfo*/, void *

typedef void (*TYPE_FUNC_HANDLER2)(SIGNAL_ARGUMENTS);
static void ListenerHandlerSimple(SIGNAL_ARGUMENTS);
static volatile int s_nWork;
static volatile int s_nWorkSmall;


int main(int argc, char* argv[])
{
    ASocketB::Initialize();
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    int nNewConnect;
    SearchRequestReciver aProto;
    const char* cpcServername = DEFAULT_SERVER_HOST;
    int nReceive(1);
    int nRet;
    ASocketTCP aSocket;
    struct sigaction sig_action;

    sigemptyset(&sig_action.sa_mask);
    sig_action.sa_flags		= SA_SIGINFO;
    sig_action.sa_sigaction	= (TYPE_FUNC_HANDLER2)ListenerHandlerSimple;
    sigaction( SIGPIPE,   &sig_action, NULL );
    sigaction( SIGINT,   &sig_action, NULL );

    if(argc>1){cpcServername=argv[1];}

    char* pcBuffer = (char*)malloc(BUFFER_SIZE);
    if(!pcBuffer)
    {
        fprintf(stderr,"fl:%s,ln:%d, LOW memory!\n",__FILE__,__LINE__);
        return -1;
    }

    s_nWork = 1;

    while(s_nWork)
    {
        nNewConnect=1;
        printf("trying to connect!\n");
        nRet = aSocket.CreateClient(cpcServername,SERVER_LISTEN_PORT,1000);
        if(nRet){continue;}
        s_nWorkSmall = 1;
        while((nReceive>=0)&&s_nWorkSmall)
        {
            nReceive = aSocket.RecvData(pcBuffer,BUFFER_SIZE,20000,20);

            if(nReceive>0)
            {
                if(nNewConnect ==1)
                {
                    printf("Connected!\n");
                    nNewConnect = 0;
                }
                printf("receive %d bytes!\n",nReceive);

                aProto.ParseFromArray(pcBuffer,nReceive);

                std::cout<<"hasSr="<<aProto.has_sr()<<", num="<<aProto.sr().incremental()<<std::endl;

            }
            else if(nNewConnect==0)
            {
                printf("Disconnected!\n");
            }
        } // while((nReceive>=0)&&s_nWorkSmall)
        usleep(1000000);
        nReceive=1;
        aSocket.Close();

    }  // while(s_nWork)

    free(pcBuffer);
    google::protobuf::ShutdownProtobufLibrary();
    ASocketB::Cleanup();

    return 0;
}


static void ListenerHandlerSimple(SIGNAL_ARGUMENTS)
{

    switch(a_nSigNum)
    {
    case SIGINT:
        printf("SIGINT\n");
        s_nWork = 0;
        s_nWorkSmall = 0;
        break;
    case SIGPIPE:
        printf("SIGPIPE");
        s_nWorkSmall = 0;
        break;
    default:
        printf("default:\n");
        break;
    }
}



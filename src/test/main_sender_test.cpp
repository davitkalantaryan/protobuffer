/*
 *	File      : test/main_sender_test.cpp
 *
 *	Created on: 04 Apr, 2017
 *	Author    : Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *
 */
#include <aservertcp.h>
#include "pitz_test_protoserver.hpp"
#include "protosystemcommon.h"
#include <signal.h>
#include <stdio.h>

#define SIGNAL_ARGUMENTS    int a_nSigNum, siginfo_t * /*a_pSigInfo*/, void *

typedef void (*TYPE_FUNC_HANDLER2)(SIGNAL_ARGUMENTS);

static pitz::test::ProtoServer*  s_pServerToStor;
static void ListenerHandlerSimple(SIGNAL_ARGUMENTS);


int main()
{
    ASocketB::Initialize();

    GOOGLE_PROTOBUF_VERIFY_VERSION;

    struct sigaction sig_action;
    sigemptyset(&sig_action.sa_mask);
    sig_action.sa_flags		= SA_SIGINFO;
    //sig_action.sa_sigaction	= (TYPE_FUNC_HANDLER2)ListenerHandler;
    sig_action.sa_sigaction	= (TYPE_FUNC_HANDLER2)ListenerHandlerSimple;
    sigaction( SIGPIPE,   &sig_action, NULL );
    sigaction( SIGINT,   &sig_action, NULL );

    pitz::test::ProtoServer aServer;


    s_pServerToStor = &aServer;
    aServer.StartServerNew(SERVER_LISTEN_PORT);

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
        s_pServerToStor->Stop();
        s_pServerToStor->SigPipeAccured();
        break;
    case SIGPIPE:
        printf("SIGPIPE\n");
        s_pServerToStor->SigPipeAccured();
        break;
    default:
        printf("default:\n");
        break;
    }
}


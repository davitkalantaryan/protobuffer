/*
 *	File      : test/pitz_test_protoserver.cpp
 *
 *	Created on: 04 Apr, 2017
 *	Author    : Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *
 */
#include "pitz_test_protoserver.hpp"
#include <stdio.h>
#include <unistd.h>


int pitz::test::ProtoServer::StartServerNew(int a_nPort)
{
    sockaddr_in aBufForRem;
    return StartServer(a_nPort,1000,&aBufForRem);
}


void pitz::test::ProtoServer::Stop()
{
    AServerTCP::StopServer();
}


void pitz::test::ProtoServer::SigPipeAccured()
{
    m_nIsSigPipe = 1;
}


void pitz::test::ProtoServer::RequestDeleted()
{
    //m_pSearchRequest=new SearchRequestSndrNew(this);
    printf("%s\n",__FUNCTION__);
}


int pitz::test::ProtoServer::AddClient(class ASocketTCP& a_ClientSocket, struct sockaddr_in* a_bufForRemAddress)
{
    char vcBuffer[64];
    int nRet(0);
    int nIteration=0;
    static std::string sBuffer;
    std::string ssHelloWorld("Hello world");

    ASocketB::GetHostName(a_bufForRemAddress,vcBuffer,63);
    printf("host:%s\n",vcBuffer);

    m_pSearchRequest = new SearchRequestSndrNew(this);
    if(!m_pSearchRequest)
    {
        fprintf(stderr,"Low memory!\n");
        return -1;
    }

#if 0
    required int32 incremental = 1;
    optional string some_string = 2;
    required int32 page_number = 3;
    required int32 result_per_page = 4;
#endif
    m_pSearchRequest->set_incremental(nIteration);
    //aSearchRequest.set_allocated_some_string(&ssHelloWorld);// This is buggi
    m_pSearchRequest->set_some_string(ssHelloWorld);
    m_pSearchRequest->set_page_number(2);
    m_pSearchRequest->set_result_per_page(1);

    m_proto.set_allocated_sr(m_pSearchRequest);

    m_nIsSigPipe=0;

    while(m_nIsSigPipe==0)
    {
        m_proto.SerializePartialToString(&sBuffer);
        nRet = a_ClientSocket.SendData(sBuffer.c_str(),sBuffer.length());
        if(nRet<0) break;
        usleep(100000);
        m_pSearchRequest->set_incremental(++nIteration);
    }

    a_ClientSocket.Close();

    return 0;
}

/*
 *	File      : test/pitz_test_protoserver.hpp
 *
 *	Created on: 04 Apr, 2017
 *	Author    : Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *
 */
#ifndef PITZ_TEST_PROTOSERVER_HPP
#define PITZ_TEST_PROTOSERVER_HPP

#include <aservertcp.h>
#include "sender.pb.h"
#include <stddef.h>
#include <stdio.h>

namespace pitz{ namespace test{

class ProtoServer : private AServerTCP
{
public:
    ProtoServer():m_pSearchRequest(NULL){}
    ~ProtoServer(){/*delete m_pSearchRequest;*/}
    int StartServerNew(int port);
    void Stop();
    void SigPipeAccured();
    void RequestDeleted();

private:
    int AddClient(class ASocketTCP& clientSocket, struct sockaddr_in* bufForRemAddress);

private:
    volatile int        m_nIsSigPipe;
    SearchRequestSndr   m_proto;
    SearchRequest*      m_pSearchRequest;
    //char*           m_pBuffer;
};

class SearchRequestSndrNew : public SearchRequest
{
public:
    SearchRequestSndrNew(ProtoServer* a_pParent):m_pParent(a_pParent){}
    ~SearchRequestSndrNew(){printf("%s\n",__FUNCTION__);if(m_pParent){m_pParent->RequestDeleted();}}
private:
    ProtoServer* m_pParent;
};

}}
#endif // PITZ_TEST_PROTOSERVER_HPP

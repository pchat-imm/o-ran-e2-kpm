/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Read the zproject/README.md for information about making permanent changes. #
################################################################################
*/
#ifndef Q_ZHTTP_SERVER_CONNECTION_H
#define Q_ZHTTP_SERVER_CONNECTION_H

#include "qczmq.h"

class QT_CZMQ_EXPORT QZhttpServerConnection : public QObject
{
    Q_OBJECT
public:

    //  Copy-construct to return the proper wrapped c types
    QZhttpServerConnection (zhttp_server_connection_t *self, QObject *qObjParent = 0);

    zhttp_server_connection_t *self;
};
#endif //  Q_ZHTTP_SERVER_CONNECTION_H
/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Read the zproject/README.md for information about making permanent changes. #
################################################################################
*/
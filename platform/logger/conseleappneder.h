#ifndef CONSELEAPPNEDER_H
#define CONSELEAPPNEDER_H

#include "iappender.h"
#include "QString"


class ConseleAppneder: public IAppender{
    public:
        ConseleAppneder();
        void write(QString str);
};

#endif // CONSELEAPPNEDER_H

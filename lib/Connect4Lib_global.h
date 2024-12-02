#ifndef CONNECT4LIB_GLOBAL_H
#define CONNECT4LIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CONNECT4LIB_LIBRARY)
#define CONNECT4LIB_EXPORT Q_DECL_EXPORT
#else
#define CONNECT4LIB_EXPORT Q_DECL_IMPORT
#endif

#endif // CONNECT4LIB_GLOBAL_H

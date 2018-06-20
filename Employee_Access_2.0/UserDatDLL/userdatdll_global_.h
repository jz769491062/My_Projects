#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(USERDATDLL_LIB)
#  define USERDATDLL_EXPORT Q_DECL_EXPORT
# else
#  define USERDATDLL_EXPORT Q_DECL_IMPORT
# endif
#else
# define USERDATDLL_EXPORT
#endif

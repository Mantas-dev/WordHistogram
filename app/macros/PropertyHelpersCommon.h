#ifndef GTM_PROPERTYHELPERSCOMMON_H
#define GTM_PROPERTYHELPERSCOMMON_H

#include <QtGlobal>

template<typename T> struct CheapestType          { typedef const T & type_def; };
template<>           struct CheapestType<bool>    { typedef bool      type_def; };
template<>           struct CheapestType<quint8>  { typedef quint8    type_def; };
template<>           struct CheapestType<quint16> { typedef quint16   type_def; };
template<>           struct CheapestType<quint32> { typedef quint32   type_def; };
template<>           struct CheapestType<quint64> { typedef quint64   type_def; };
template<>           struct CheapestType<qint8>   { typedef qint8     type_def; };
template<>           struct CheapestType<qint16>  { typedef qint16    type_def; };
template<>           struct CheapestType<qint32>  { typedef qint32    type_def; };
template<>           struct CheapestType<qint64>  { typedef qint64    type_def; };
template<>           struct CheapestType<float>   { typedef float     type_def; };
template<>           struct CheapestType<double>  { typedef double    type_def; };
template<typename T> struct CheapestType<T *>     { typedef T *       type_def; };

#ifdef QTQMLTRICKS_NO_PREFIX_ON_GETTERS
#   define MAKE_GETTER_NAME(name) name
#else
#   define MAKE_GETTER_NAME(name) get_##name
#endif

#endif // GTM_PROPERTYHELPERSCOMMON_H

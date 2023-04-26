#ifndef AUTOPROPERTYHELPERS_H
#define AUTOPROPERTYHELPERS_H

#include <QObject>

#include "PropertyHelpersCommon.h"

//Individual macros for getter, setter, notifier, and member

#define AUTO_GETTER(type, name) \
    CheapestType<type>::type_def MAKE_GETTER_NAME(name) (void) const { \
        return m_##name; \
    }

#define AUTO_SETTER(type, name, prefix) \
    bool prefix##name (CheapestType<type>::type_def name) { \
        if (m_##name != name) { \
            m_##name = name; \
            emit name##Changed (); \
            return true; \
        } \
        else { \
            return false; \
        } \
    }

#define AUTO_NOTIFIER(type, name) \
    void name##Changed (void);

#define AUTO_MEMBER(type, name) \
    type m_##name;

//Actual auto-property helpers

#define WRITABLE_AUTO_PROPERTY(type, name) \
    protected: \
        Q_PROPERTY (type name READ MAKE_GETTER_NAME(name) WRITE set_##name NOTIFY name##Changed) \
    private: \
        AUTO_MEMBER (type, name) \
    public: \
        AUTO_GETTER (type, name) \
        AUTO_SETTER (type, name, set_) \
    Q_SIGNALS: \
        AUTO_NOTIFIER (type, name) \
    private:

#define READONLY_AUTO_PROPERTY(type, name) \
    protected: \
        Q_PROPERTY (type name READ MAKE_GETTER_NAME(name) NOTIFY name##Changed) \
    private: \
        AUTO_MEMBER (type, name) \
    public: \
        AUTO_GETTER (type, name) \
        AUTO_SETTER (type, name, update_) \
    Q_SIGNALS: \
        AUTO_NOTIFIER (type, name) \
    private:

#define CONSTANT_AUTO_PROPERTY(type, name) \
    protected: \
        Q_PROPERTY (type name READ MAKE_GETTER_NAME(name) CONSTANT) \
    private: \
        AUTO_MEMBER (type, name) \
    public: \
        AUTO_GETTER (type, name) \
    private:

#endif // AUTOPROPERTYHELPERS_H

/****************************************************************************
** Meta object code from reading C++ file 'EmulationOrchestrator.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../EmulationOrchestrator.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EmulationOrchestrator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN21EmulationOrchestratorE_t {};
} // unnamed namespace

template <> constexpr inline auto EmulationOrchestrator::qt_create_metaobjectdata<qt_meta_tag_ZN21EmulationOrchestratorE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "EmulationOrchestrator",
        "finished",
        "",
        "SaveParametersButtonTimer",
        "num",
        "MainWindowSignal_DType",
        "SignalType",
        "QVariant",
        "value",
        "SaveParametersButtonCondition",
        "process",
        "stop",
        "pause",
        "resume",
        "UpdateParametersButtonTimer",
        "signal",
        "index",
        "UpdateParametersButtonCondition"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'finished'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'SaveParametersButtonTimer'
        QtMocHelpers::SignalData<void(qint32, MainWindowSignal_DType, const QVariant &)>(3, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 4 }, { 0x80000000 | 5, 6 }, { 0x80000000 | 7, 8 },
        }}),
        // Signal 'SaveParametersButtonCondition'
        QtMocHelpers::SignalData<void(qint32, MainWindowSignal_DType, const QVariant &)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 4 }, { 0x80000000 | 5, 6 }, { 0x80000000 | 7, 8 },
        }}),
        // Slot 'process'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'stop'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'pause'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'resume'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'UpdateParametersButtonTimer'
        QtMocHelpers::SlotData<void(const MainWindowSignal_DType, const QVariant &, int)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 5, 15 }, { 0x80000000 | 7, 8 }, { QMetaType::Int, 16 },
        }}),
        // Slot 'UpdateParametersButtonCondition'
        QtMocHelpers::SlotData<void(const MainWindowSignal_DType, const QVariant &, int)>(17, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 5, 15 }, { 0x80000000 | 7, 8 }, { QMetaType::Int, 16 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<EmulationOrchestrator, qt_meta_tag_ZN21EmulationOrchestratorE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject EmulationOrchestrator::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN21EmulationOrchestratorE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN21EmulationOrchestratorE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN21EmulationOrchestratorE_t>.metaTypes,
    nullptr
} };

void EmulationOrchestrator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<EmulationOrchestrator *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->finished(); break;
        case 1: _t->SaveParametersButtonTimer((*reinterpret_cast< std::add_pointer_t<qint32>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MainWindowSignal_DType>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QVariant>>(_a[3]))); break;
        case 2: _t->SaveParametersButtonCondition((*reinterpret_cast< std::add_pointer_t<qint32>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MainWindowSignal_DType>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QVariant>>(_a[3]))); break;
        case 3: _t->process(); break;
        case 4: _t->stop(); break;
        case 5: _t->pause(); break;
        case 6: _t->resume(); break;
        case 7: _t->UpdateParametersButtonTimer((*reinterpret_cast< std::add_pointer_t<MainWindowSignal_DType>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QVariant>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 8: _t->UpdateParametersButtonCondition((*reinterpret_cast< std::add_pointer_t<MainWindowSignal_DType>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QVariant>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MainWindowSignal_DType >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MainWindowSignal_DType >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MainWindowSignal_DType >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< MainWindowSignal_DType >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (EmulationOrchestrator::*)()>(_a, &EmulationOrchestrator::finished, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (EmulationOrchestrator::*)(qint32 , MainWindowSignal_DType , const QVariant & )>(_a, &EmulationOrchestrator::SaveParametersButtonTimer, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (EmulationOrchestrator::*)(qint32 , MainWindowSignal_DType , const QVariant & )>(_a, &EmulationOrchestrator::SaveParametersButtonCondition, 2))
            return;
    }
}

const QMetaObject *EmulationOrchestrator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EmulationOrchestrator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN21EmulationOrchestratorE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int EmulationOrchestrator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void EmulationOrchestrator::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void EmulationOrchestrator::SaveParametersButtonTimer(qint32 _t1, MainWindowSignal_DType _t2, const QVariant & _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2, _t3);
}

// SIGNAL 2
void EmulationOrchestrator::SaveParametersButtonCondition(qint32 _t1, MainWindowSignal_DType _t2, const QVariant & _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2, _t3);
}
QT_WARNING_POP

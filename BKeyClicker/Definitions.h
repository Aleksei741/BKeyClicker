#pragma once
#include <QMetaType>

enum class Condition_DType 
{
    NotEqual,
    Equal
};
Q_DECLARE_METATYPE(Condition_DType)  // обязательно для QVariant и signal/slot

enum class Buttons_DType 
{
    L0,
    L1,
    L2,
    L3,
    L4,
    L5,
    L6,
    L7,
    L8,
    L9,
    k_0,
    k_1,
    k_2,
    k_3,
    k_4,
    k_5,
    k_6,
    k_7,
    k_8,
    k_9,
    k_minus,
    k_equals,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    Space,
    Backspace,
    Enter,
    Tab,
    Tilde,
    Button_UP,
    Button_DOWN,
    Button_LEFT,
    Button_RIGHT,
};
Q_DECLARE_METATYPE(Buttons_DType)

enum class nWindows_DType
{
    n1,
    n2,
    n3,
};
Q_DECLARE_METATYPE(nWindows_DType)

enum class MainWindowSignal_DType
{
    Active, Window, Button, Conditional, Period, Repeate, 
    Pause, Ctrl, Alt, Shift,
};

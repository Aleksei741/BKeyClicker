#pragma once
#include <QComboBox>
#include <QString>
#include "Definitions.h"

class ListWindowComboBox : public QComboBox
{
	Q_OBJECT
public:
	explicit ListWindowComboBox(QWidget* parent = nullptr) : QComboBox(parent)
	{
		addItem("1", QVariant::fromValue(nWindows_DType::n1));
		addItem("2", QVariant::fromValue(nWindows_DType::n2));
		addItem("3", QVariant::fromValue(nWindows_DType::n3));
	}
};

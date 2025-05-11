#pragma once
#include <QComboBox>
#include <QString>
#include "Definitions.h"

class ConditionalComboBox : public QComboBox
{
	Q_OBJECT
public:
	explicit ConditionalComboBox(QWidget* parent = nullptr) : QComboBox(parent)
	{
		addItem("!=", QVariant::fromValue(Condition_DType::NotEqual));
		addItem("=", QVariant::fromValue(Condition_DType::Equal));
	}
};

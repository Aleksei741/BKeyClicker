#pragma once
#include <QComboBox>
#include <QString>
#include "Definitions.h"

class ListButtonComboBox : public QComboBox
{
	Q_OBJECT
public:
	explicit ListButtonComboBox(QWidget* parent = nullptr) : QComboBox(parent)
	{
		addItem("L0", QVariant::fromValue(Buttons_DType::L0));
		addItem("L1", QVariant::fromValue(Buttons_DType::L1));
		addItem("L2", QVariant::fromValue(Buttons_DType::L2));
		addItem("L3", QVariant::fromValue(Buttons_DType::L3));
		addItem("L4", QVariant::fromValue(Buttons_DType::L4));
		addItem("L5", QVariant::fromValue(Buttons_DType::L5));
		addItem("L6", QVariant::fromValue(Buttons_DType::L6));
		addItem("L7", QVariant::fromValue(Buttons_DType::L7));
		addItem("L8", QVariant::fromValue(Buttons_DType::L8));
		addItem("L9", QVariant::fromValue(Buttons_DType::L9));

		addItem("0", QVariant::fromValue(Buttons_DType::k_0));
		addItem("1", QVariant::fromValue(Buttons_DType::k_1));
		addItem("2", QVariant::fromValue(Buttons_DType::k_2));
		addItem("3", QVariant::fromValue(Buttons_DType::k_3));
		addItem("4", QVariant::fromValue(Buttons_DType::k_4));
		addItem("5", QVariant::fromValue(Buttons_DType::k_5));
		addItem("6", QVariant::fromValue(Buttons_DType::k_6));
		addItem("7", QVariant::fromValue(Buttons_DType::k_7));
		addItem("8", QVariant::fromValue(Buttons_DType::k_8));
		addItem("9", QVariant::fromValue(Buttons_DType::k_9));

		addItem("-", QVariant::fromValue(Buttons_DType::k_minus));
		addItem("=", QVariant::fromValue(Buttons_DType::k_equals));

		addItem("F1", QVariant::fromValue(Buttons_DType::F1));
		addItem("F2", QVariant::fromValue(Buttons_DType::F2));
		addItem("F3", QVariant::fromValue(Buttons_DType::F3));
		addItem("F4", QVariant::fromValue(Buttons_DType::F4));
		addItem("F5", QVariant::fromValue(Buttons_DType::F5));
		addItem("F6", QVariant::fromValue(Buttons_DType::F6));
		addItem("F7", QVariant::fromValue(Buttons_DType::F7));
		addItem("F8", QVariant::fromValue(Buttons_DType::F8));
		addItem("F9", QVariant::fromValue(Buttons_DType::F9));
		addItem("F10", QVariant::fromValue(Buttons_DType::F10));
		addItem("F11", QVariant::fromValue(Buttons_DType::F11));
		addItem("F12", QVariant::fromValue(Buttons_DType::F12));

		addItem("A", QVariant::fromValue(Buttons_DType::A));
		addItem("B", QVariant::fromValue(Buttons_DType::B));
		addItem("C", QVariant::fromValue(Buttons_DType::C));
		addItem("D", QVariant::fromValue(Buttons_DType::D));
		addItem("E", QVariant::fromValue(Buttons_DType::E));
		addItem("F", QVariant::fromValue(Buttons_DType::F));
		addItem("G", QVariant::fromValue(Buttons_DType::G));
		addItem("H", QVariant::fromValue(Buttons_DType::H));
		addItem("I", QVariant::fromValue(Buttons_DType::I));
		addItem("J", QVariant::fromValue(Buttons_DType::J));
		addItem("K", QVariant::fromValue(Buttons_DType::K));
		addItem("L", QVariant::fromValue(Buttons_DType::L));
		addItem("M", QVariant::fromValue(Buttons_DType::M));
		addItem("N", QVariant::fromValue(Buttons_DType::N));
		addItem("O", QVariant::fromValue(Buttons_DType::O));
		addItem("P", QVariant::fromValue(Buttons_DType::P));
		addItem("Q", QVariant::fromValue(Buttons_DType::Q));
		addItem("R", QVariant::fromValue(Buttons_DType::R));
		addItem("S", QVariant::fromValue(Buttons_DType::S));
		addItem("T", QVariant::fromValue(Buttons_DType::T));
		addItem("U", QVariant::fromValue(Buttons_DType::U));
		addItem("V", QVariant::fromValue(Buttons_DType::V));
		addItem("W", QVariant::fromValue(Buttons_DType::W));
		addItem("X", QVariant::fromValue(Buttons_DType::X));
		addItem("Y", QVariant::fromValue(Buttons_DType::Y));
		addItem("Z", QVariant::fromValue(Buttons_DType::Z));

		addItem("Space", QVariant::fromValue(Buttons_DType::Space));
		addItem("Backspace", QVariant::fromValue(Buttons_DType::Backspace));
		addItem("Enter", QVariant::fromValue(Buttons_DType::Enter));
		addItem("Tab", QVariant::fromValue(Buttons_DType::Tab));
		addItem("Tilde", QVariant::fromValue(Buttons_DType::Tilde));
		addItem("Button_UP", QVariant::fromValue(Buttons_DType::Button_UP));
		addItem("Button_DOWN", QVariant::fromValue(Buttons_DType::Button_DOWN));
		addItem("Button_LEFT", QVariant::fromValue(Buttons_DType::Button_LEFT));
		addItem("Button_RIGHT", QVariant::fromValue(Buttons_DType::Button_RIGHT));
	}
};


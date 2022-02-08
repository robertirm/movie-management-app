#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_InchiriereFillmeGUI.h"

class InchiriereFillmeGUI : public QMainWindow
{
    Q_OBJECT

public:
    InchiriereFillmeGUI(QWidget *parent = Q_NULLPTR);

private:
    Ui::InchiriereFillmeGUIClass ui;
};

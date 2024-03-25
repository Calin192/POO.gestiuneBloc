#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_POOmdalab10.h"

class POOmdalab10 : public QMainWindow
{
    Q_OBJECT

public:
    POOmdalab10(QWidget *parent = nullptr);
    ~POOmdalab10();

private:
    Ui::POOmdalab10Class ui;
};

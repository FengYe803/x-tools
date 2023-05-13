/******************************************************************************
 * Copyright 2023 Qsaker(wuuhaii@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part
 * of QtSwissArmyKnife project.
 *
 * QtSwissArmyKnife is licensed according to the terms in
 * the file LICENCE in the root of the source code directory.
 *****************************************************************************/
#include <QSerialPort>
#include "SAKFlowControlComboBox.hh"

SAKFlowControlComboBox::SAKFlowControlComboBox(QWidget *parent)
    : QComboBox(parent)
{
    addItem(tr("No"), QSerialPort::NoFlowControl);
    addItem(tr("Hardware"), QSerialPort::HardwareControl);
    addItem(tr("Software"), QSerialPort::SoftwareControl);
}

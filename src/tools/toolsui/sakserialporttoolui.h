/***************************************************************************************************
 * Copyright 2023 Qsaker(qsaker@foxmail.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of QtSwissArmyKnife project.
 *
 * QtSwissArmyKnife is licensed according to the terms in the file LICENCE in the root of the source
 * code directory.
 **************************************************************************************************/
#ifndef SAKSERIALPORTTOOLBOXUI_HH
#define SAKSERIALPORTTOOLBOXUI_HH

#include "sakcommunicationtoolui.h"
#include <QLoggingCategory>

namespace Ui {
class SAKSerialPortToolUi;
}

class SAKSerialPortTool;
class SAKSerialPortToolUi : public SAKCommunicationToolUi
{
    Q_OBJECT
public:
    explicit SAKSerialPortToolUi(QWidget *parent = nullptr);
    ~SAKSerialPortToolUi();
    virtual void onBaseToolUiInitialized(SAKBaseTool *tool, const QString &settingsGroup) final;

private:
    SAKSerialPortTool *mTool{nullptr};
    const QLoggingCategory mLoggingCategory{"sak.serialporttoolui"};

private:
    void checkInitializingStatus();

private:
    Ui::SAKSerialPortToolUi *ui;

    void onComboBoxPortNamesCurrentTextChanged();
    void onComboBoxBaudRateCurrentIndexChanged();
    void onComboBoxDataBitsCurrentIndexChanged();
    void onComboBoxStopBitsCurrentIndexChanged();
    void onComboBoxParityCurrentIndexChanged();
    void onComboBoxFlowControlCurrentIndexChanged();
};

#endif // SAKSerialPortToolUi_HH

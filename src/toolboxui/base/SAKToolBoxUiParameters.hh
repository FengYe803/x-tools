/******************************************************************************
 * Copyright 2023 Qsaker(wuuhaii@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part
 * of QtSwissArmyKnife project.
 *
 * QtSwissArmyKnife is licensed according to the terms in
 * the file LICENCE in the root of the source code directory.
 *****************************************************************************/
#ifndef SAKTOOLBOXUIPARAMETERS_HH
#define SAKTOOLBOXUIPARAMETERS_HH

#include <QDialog>
#include <QLoggingCategory>

namespace Ui {
class SAKToolBoxUiParameters;
}

class SAKToolBoxUiParameters : public QDialog
{
    Q_OBJECT
public:
    struct ParameterContext {
        struct {
            struct {
                bool isEnable;
                qint8 maskCode;
            } iMasker, oMasker;
            struct {

            } iAnalyzer, oAnalyzer;
        } communication;

        struct {

        } input;

        struct {

        } output;
    };
public:
    SAKToolBoxUiParameters(QWidget *parent = nullptr);
    ~SAKToolBoxUiParameters();
    void showDialog(int tabIndex);
    ParameterContext parameterContext();

private:
    const QLoggingCategory mLoggingCategory{"SAK.ToolBoxUiParameters"};

private:
    Ui::SAKToolBoxUiParameters *ui;
};

#endif // SAKTOOLBOXUIPARAMETERS_HH

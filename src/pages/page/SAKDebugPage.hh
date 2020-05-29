﻿/*
 * Copyright (C) 2018-2020 wuuhii. All rights reserved.
 *
 * The file is encoding with utf-8 (with BOM). It is a part of QtSwissArmyKnife
 * project. The project is a open source project, you can get the source from:
 *     https://github.com/wuuhii/QtSwissArmyKnife
 *     https://gitee.com/wuuhii/QtSwissArmyKnife
 *
 * For more information about the project, please join our QQ group(952218522).
 * In addition, the email address of the project author is wuuhii@outlook.com.
 */
#ifndef SAKTABPAGE_HH
#define SAKTABPAGE_HH

#include <QSize>
#include <QTimer>
#include <QLabel>
#include <QMutex>
#include <QWidget>
#include <QGroupBox>
#include <QComboBox>
#include <QDateTime>
#include <QMetaEnum>
#include <QTextEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QApplication>
#include <QTextBrowser>

#include "SAKCRCInterface.hh"
#include "SAKReadWriteSettingsWidget.hh"
#include "SAKAutoResponseSettingsWidget.hh"

class SAKDevice;
class SAKDataFactory;
class SAKCRCInterface;
class SAKStatisticsManager;
class SAKOtherSettingsManager;
class SAKTransmissionSettings;
class SAKDebugPageInputManager;
class SAKDebugPageOutputManager;
class SAKHighlightSettingsWidget;
#ifdef SAK_IMPORT_CHARTS_MODULE
class SAKDataVisualizationManager;
#endif

namespace Ui {
    class SAKDebugPage;
}

class SAKDebugPage : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief SAKDebugPage 调试页面基类
     * @param type 调试页面类型（SAKGlobal::SAKEnumDebugPageType）
     * @param parent 资源管理类
     */
    SAKDebugPage(int type, QWidget *parent = Q_NULLPTR);
    ~SAKDebugPage();

    struct ReadWriteParameters {
        int waitForBytesWrittenTime;
        int waitForReadyReadTime;
    };

    friend class SAKDataVisualizationManager;
    friend class SAKOtherSettingsManager;
    friend class SAKStatisticsManager;
    friend class SAKDebugPageInputManager;
    friend class SAKDebugPageOutputManager;

    /**
     * @brief changeDeviceState 更改设备状态
     * @param isOpened true表示设备已打开，false表示设备已关闭
     */
    void changeDeviceState(bool isOpened);

    /**
     * @brief write             -- 写数据
     * @param data              -- 待写的数据
     */
    void write(QByteArray data);

    /**
     * @brief writeRawData      -- 写数据
     * @param rawData           -- 代写数据（特殊格式字符串，未经过处理）
     * @param textFormat        -- SAKGlobal::SAKTextFormat，文本格式
     */
    void writeRawData(QString rawData, int textFormat);

    /**
     * @brief outputMessage 向ui输出信息
     * @param msg 带输出信息
     * @param isInfo true表示一般信息，false表示错误、警告信息
     */
    void outputMessage(QString msg, bool isInfo = true);
protected:
    /**
     * @brief setupDevice 初始化与设备有关的信号关联
     * @brief dev 设备实例指针
     */
    void setupDevice(SAKDevice *dev);

    /**
     * @brief refreshDevice         -- 刷新设备
     */
    virtual void refreshDevice();

    /**
     * @brief openOrColoseDevice    -- 打开或者关闭设备
     */
    virtual void openOrColoseDevice();
private:
    SAKDevice *device;
    bool isInitializing;
    int debugPageType = -1;
    QString settingKey;
    QTimer clearInfoTimer;
private:
    void initSettingKey();
    /// @brief 初始化配置选项名称
    void initSettingString();
    void initInputSettingString();
    void initOutputSettingString();
    /// @brief 从配置文件中读入配置选项
    void readinSettings();
    void readinInputSettings();
    void readinOutputSettings();
    /// @brief 清空ui消息显示
    void cleanInfo();
signals:
    /// 读取数据后发射该信号，参数为已读取的数据
    void bytesRead(QByteArray data);
    /// 发送数据后发射该信号，参数为已发送的数据
    void bytesWritten(QByteArray data);
    /// 子类关联该信号来发送数据即可
    void writeDataRequest(QByteArray data);
    /// 子类设备状态发生改变时(是否就绪)发送该信号
    void deviceStatusChanged(bool ready);
    /// 请求处理输出
    void writeRawDataRequest(QString data, int textFormat);

    /// @brief 读写参数
public:
    struct ReadWriteParameters readWriteParameters();
    void setReadWriteParameters(struct ReadWriteParameters parameters);
private:
    struct ReadWriteParameters _readWriteParameters;
    QMutex readWriteParametersQMutex;
protected:
    /// @brief 返回控制面板
    virtual QWidget *controllerWidget();
    /**
     * @brief setUpController -- 安装控制器（控制面板）
     */
    void setupController();
    /**
     * @brief changedDeviceStatus   -- 设备打开或者关闭时执行该函数
     * @param opened                -- true: 设备一打开 false：设备已关闭
     */
    void changedDeviceStatus(bool opened);




    /*************************************************************************/
    /// @brief ui文件初始化
private:
    Ui::SAKDebugPage *ui;
private:
    /// @brief initUiPointer -- 初始化指向ui控件的数据成员（指针）
    void initUiPointer();

    /*************************************************************************/
    /// @brief 设备设置
protected:
    QPushButton *refreshPushButton;
    QPushButton *switchPushButton;
    QFrame      *deviceSettingFrame;
private slots:
    void on_refreshPushButton_clicked();
    void on_switchPushButton_clicked();

    /*************************************************************************/
    /// @brief 输入设置组
protected:
    QComboBox   *inputModelComboBox;
    QCheckBox   *cycleEnableCheckBox;
    QLineEdit   *cycleTimeLineEdit;
    QPushButton *readinFilePushButton;
    QPushButton *saveInputDataPushButton;
    QCheckBox   *addCRCCheckBox;
    QCheckBox   *bigeEndianCheckBox;
    QPushButton *clearInputPushButton;
    QPushButton *sendPushButton;
    QTextEdit   *inputTextEdit;
    QComboBox   *crcParameterModelsComboBox;
    QLabel      *crcLabel;
    QPushButton *addInputItemPushButton;
    QPushButton *deleteInputItemPushButton;
    QListWidget *inputDataItemListWidget;
    QPushButton *presetPushButton;
    QPushButton *sendPresetPushButton;

    QString settingStringInputModel;
    QString settingStringCycleTime;
    QString settingStringAddCRC;
    QString settingStringBigeEndian;
    QString settingStringcrcParameterModel;
private slots:
    void on_inputModelComboBox_currentIndexChanged(int index);
    void on_cycleTimeLineEdit_textChanged(const QString &text);
    void on_addCRCCheckBox_clicked();
    void on_bigeEndianCheckBox_clicked();
    void on_crcParameterModelsComboBox_currentIndexChanged(int index);

    /*************************************************************************/
    /// @brief 消息输出组管理
protected:
    QLabel *infoLabel;

    /*************************************************************************/
    /// @brief 数据输出组
protected:
    QLabel       *rxLabel;
    QLabel       *txLabel;
    QComboBox    *outputTextFormatComboBox;
    QCheckBox    *showDateCheckBox;
    QCheckBox    *autoWrapCheckBox;
    QCheckBox    *showTimeCheckBox;
    QCheckBox    *showMsCheckBox;
    QCheckBox    *showRxDataCheckBox;
    QCheckBox    *showTxDataCheckBox;
    QCheckBox    *saveOutputFileToFilecheckBox;
    QPushButton  *outputFilePathPushButton;
    QPushButton  *clearOutputPushButton;
    QPushButton  *saveOutputPushButton;
    QTextBrowser *outputTextBroswer;

    QString settingStringOutputTextFormat;
    QString settingStringShowDate;
    QString settingStringAutoWrap;
    QString settingStringShowTime;
    QString settingStringShowMs;
    QString settingStringShowRx;
    QString settingStringShowTx;
private slots:
    void on_outputTextFormatComboBox_currentIndexChanged(int index);
    void on_showDateCheckBox_clicked();
    void on_autoWrapCheckBox_clicked();
    void on_showTimeCheckBox_clicked();
    void on_showMsCheckBox_clicked();
    void on_showRxDataCheckBox_clicked();
    void on_showTxDataCheckBox_clicked();

    /*************************************************************************/
    /// @brief 数据统计
protected:
    bool        receivedFlag;
    bool        sendFlag;

    QLabel      *rxSpeedLabel;
    QLabel      *txSpeedLabel;
    QLabel      *rxFramesLabel;
    QLabel      *txFramesLabel;
    QLabel      *rxBytesLabel;
    QLabel      *txBytesLabel;
    QPushButton *resetTxCountPushButton;
    QPushButton *resetRxCountPushButton;

    /*************************************************************************/
    /// @brief 其他设置
protected:
    QPushButton *transmissionSettingPushButton;
    QPushButton *readWriteSettingPushButton;
    QPushButton *autoResponseSettingPushButton;    
    QPushButton *timingSendingPushButton;
    QPushButton *highlightSettingPushButton;
    QPushButton *moreSettingsPushButton;

    /*************************************************************************/
    /// @brief 数据可视化
protected:
    QPushButton *dataVisualizationPushButton;
private slots:
    void on_dataVisualizationPushButton_clicked();
private:
#ifdef SAK_IMPORT_CHARTS_MODULE
    SAKDataVisualizationManager *dataVisualizationManager;
#endif
    SAKOtherSettingsManager *otherSettings;
    SAKStatisticsManager *statisticsManager;
    SAKDebugPageOutputManager *outputManager;
    SAKDebugPageInputManager *debugPageInputManager;
};

#endif  // SAKTabPage_H

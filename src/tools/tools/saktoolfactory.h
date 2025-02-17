/***************************************************************************************************
 * Copyright 2023 Qsaker(qsaker@foxmail.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of QtSwissArmyKnife project.
 *
 * QtSwissArmyKnife is licensed according to the terms in the file LICENCE in the root of the source
 * code directory.
 **************************************************************************************************/
#ifndef SAKTOOLFACTORY_H
#define SAKTOOLFACTORY_H

#include <QObject>

#include "sakbasetool.h"

class SAKToolFactory : public QObject
{
    Q_OBJECT
public:
    enum ToolsType {
        AnalyzerTool,
        SerialportTool,
        EmitterTool,
        MaskerTool,
        ResponserTool,
        StorerTool,
        PrestoreTool,
        VelometerTool,
        UdpClientTool,
        UdpServerTool,
        TcpClientTool,
        TcpServerTool,
        WebSocketClientTool,
        WebSocketServerTool,
        BleCentralTool,
        BlePeriheral,
        StatistiticianTool,
        SerialPortTransmitterTool,
        UdpTransmitterTool,
        TcpTransmitterTool,
        WebSocketTransmitterTool,
        CrcCalculatorTool
    };
    Q_ENUM(ToolsType)

private:
    explicit SAKToolFactory(QObject *parent = Q_NULLPTR);

public:
    static SAKToolFactory *instance();
    Q_INVOKABLE SAKBaseTool *createTool(int type);
    QString toolName(int type);
};

#endif // SAKTOOLFACTORY_H

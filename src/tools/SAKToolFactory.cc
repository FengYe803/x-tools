﻿/******************************************************************************
 * Copyright 2023 Qsaker(qsaker@foxmail.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part
 * of QtSwissArmyKnife project.
 *
 * QtSwissArmyKnife is licensed according to the terms in
 * the file LICENCE in the root of the source code directory.
 *****************************************************************************/
#include <QMetaEnum>
#include "SAKMaskerTool.h"
#include "SAKStorerTool.h"
#include "SAKToolFactory.h"
#include "SAKEmitterTool.h"
#include "SAKAnalyzerTool.h"
#include "SAKPrestorerTool.h"
#include "SAKResponserTool.h"
#include "SAKUdpClientTool.h"
#include "SAKUdpServerTool.h"
#include "SAKTcpClientTool.h"
#include "SAKTcpServerTool.h"
#include "SAKVelometerTool.h"
#include "SAKBleCentralTool.h"
#include "SAKSerialPortTool.h"
#include "SAKStatisticianTool.h"
#include "SAKTcpTransmitterTool.h"
#include "SAKUdpTransmitterTool.h"
#include "SAKWebSocketClientTool.h"
#include "SAKWebSocketServerTool.h"
#include "SAKWebSocketTransmitterTool.h"
#include "SAKSerialPortTransmitterTool.h"

SAKToolFactory::SAKToolFactory(QObject *parent)
    : QObject{parent}
{

}

SAKToolFactory *SAKToolFactory::instance()
{
    static SAKToolFactory toolsFactory;
    return &toolsFactory;
}

SAKBaseTool *SAKToolFactory::createTool(int type)
{
    SAKBaseTool *tool{nullptr};
    if (AnalyzerTool == type) {
        tool = new SAKAnalyzerTool();
    } else if (SerialportTool == type) {
        tool = new SAKSerialPortTool();
    } else if (EmitterTool == type) {
        tool = new SAKEmitterTool();
    } else if (MaskerTool == type) {
        tool = new SAKMaskerTool();
    } else if (ResponserTool == type) {
        tool = new SAKResponserTool();
    } else if (StorerTool == type) {
        tool = new SAKStorerTool();
    } else if (PrestoreTool == type) {
        tool = new SAKPrestorerTool();
    } else if (VelometerTool == type) {
        tool = new SAKVelometerTool();
    } else if (UdpClientTool == type) {
        tool = new SAKUdpClientTool();
    } else if (UdpServerTool == type) {
        tool = new SAKUdpServerTool();
    } else if (TcpClientTool == type) {
        tool = new SAKTcpClientTool();
    } else if (TcpServerTool == type) {
        tool = new SAKTcpServerTool();
    } else if (WebSocketClientTool == type) {
        tool = new SAKWebSocketClientTool();
    } else if (WebSocketServerTool == type) {
        tool = new SAKWebSocketServerTool();
    } else if (BleCentralTool == type) {
        tool = new SAKBleCentralTool();
    } else if (StatistiticianTool == type) {
        tool = new SAKStatisticianTool();
    } else if (SerialPortTransmitterTool == type) {
        tool = new SAKSerialPortTransmitterTool();
    } else if (UdpTransmitterTool == type) {
        tool = new SAKUdpTransmitterTool();
    } else if (TcpTransmitterTool == type) {
        tool = new SAKTcpTransmitterTool();
    } else if (WebSocketTransmitterTool == type) {
        tool = new SAKWebSocketTransmitterTool();
    } else {
        qWarning() << "Unknown tool type: " << type;
    }

    if (tool) {
        QMetaEnum metaEnum = QMetaEnum::fromType<SAKToolFactory::ToolsType>();
        tool->setProperty("toolTypeName", metaEnum.valueToKey(type));
    } else {
        QString msg = QString("Unknow tool type: %1.").arg(type);
        Q_UNUSED(msg);
        Q_ASSERT_X(false, __FUNCTION__, msg.toLatin1().data());
    }


    return tool;
}

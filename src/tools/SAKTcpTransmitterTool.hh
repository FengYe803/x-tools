﻿/******************************************************************************
 * Copyright 2023 Qsaker(wuuhaii@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part
 * of QtSwissArmyKnife project.
 *
 * QtSwissArmyKnife is licensed according to the terms in
 * the file LICENCE in the root of the source code directory.
 *****************************************************************************/
#ifndef SAKTCPTRANSMITTERTOOL_HH
#define SAKTCPTRANSMITTERTOOL_HH

#include "SAKSocketClientTransmitterTool.hh"

class SAKTcpTransmitterTool : public SAKSocketClientTransmitterTool
{
    Q_OBJECT
public:
    explicit SAKTcpTransmitterTool(QObject *parent = nullptr);
    virtual SAKSocketClientTool *createTool() override;
};

#endif // SAKTCPTRANSMITTERTOOL_HH

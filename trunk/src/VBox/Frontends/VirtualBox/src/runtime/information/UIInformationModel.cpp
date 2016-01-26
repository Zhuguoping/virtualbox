/* $Id$ */
/** @file
 * VBox Qt GUI - UIInformationModel class implementation.
 */

/*
 * Copyright (C) 2016 Oracle Corporation
 *
 * This file is part of VirtualBox Open Source Edition (OSE), as
 * available from http://www.virtualbox.org. This file is free software;
 * you can redistribute it and/or modify it under the terms of the GNU
 * General Public License (GPL) as published by the Free Software
 * Foundation, in version 2 as it comes in the "COPYING" file of the
 * VirtualBox OSE distribution. VirtualBox OSE is distributed in the
 * hope that it will be useful, but WITHOUT ANY WARRANTY of any kind.
 */

#ifdef VBOX_WITH_PRECOMPILED_HEADERS
# include <precomp.h>
#else  /* !VBOX_WITH_PRECOMPILED_HEADERS */

/* Qt includes: */
# include <QFont>
# include <QHash>
# include <QBrush>
# include <QGraphicsView>
# include <QGraphicsScene>
# include <QGraphicsSceneContextMenuEvent>

/* GUI includes: */
# include "VBoxGlobal.h"
# include "UIConverter.h"
# include "UIExtraDataManager.h"
# include "UIInformationModel.h"
# include "UIInformationDataItem.h"

#endif /* !VBOX_WITH_PRECOMPILED_HEADERS */

UIInformationModel::UIInformationModel(QObject *pParent, const CMachine &machine, const CConsole &console)
    : QAbstractListModel(pParent)
    , m_machine(machine)
    , m_console(console)
{
    /* Prepare information-model: */
    prepare();

    /* Prepare data for information-model: */
    prepareData();
}

UIInformationModel::~UIInformationModel()
{
}

int UIInformationModel::rowCount(const QModelIndex & /*parent */) const
{
    return m_list.count();
}

QVariant UIInformationModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();
    UIInformationDataItem *pItem = m_list.at(row);
    return pItem->data(index, role);
}

void UIInformationModel::prepare()
{
    /* Prepare role-names for model: */
    QHash<int, QByteArray> roleNames;
    roleNames[Qt::DisplayRole] = "";
    roleNames[Qt::DecorationRole] = "";
    roleNames[Qt::SizeHintRole] = "";
    roleNames[Qt::UserRole+1] = "";
    setRoleNames(roleNames);

    /* Register meta-type: */
    qRegisterMetaType<InformationElementType>();
}

void UIInformationModel::prepareData()
{
    /* Prepare data for information-model: */
    UIInformationDataItem *pGeneral = new UIInformationDataGeneral(m_machine, m_console);
    AssertPtrReturnVoid(pGeneral);
    {
        m_list.append(pGeneral);
    }
    UIInformationDataSystem *pSystem = new UIInformationDataSystem(m_machine, m_console);
    AssertPtrReturnVoid(pSystem);
    {
        m_list.append(pSystem);
    }
    UIInformationDataDisplay *pDisplay = new UIInformationDataDisplay(m_machine, m_console);
    AssertPtrReturnVoid(pDisplay);
    {
        m_list.append(pDisplay);
    }
}

QHash<int, QByteArray> UIInformationModel::roleNames() const
{
    QHash<int, QByteArray> roleNames;
    roleNames[Qt::DisplayRole] = "";
    roleNames[Qt::DecorationRole] = "";
    roleNames[Qt::SizeHintRole] = "";
    roleNames[Qt::UserRole+1] = "";
    return roleNames;
}


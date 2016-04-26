//==================================================================================
// Copyright (c) 2016 , Advanced Micro Devices, Inc.  All rights reserved.
//
/// \author AMD Developer Tools Team
/// \file afTreeCtrl.h
///
//==================================================================================

#ifndef __AFTREECTRL_H
#define __AFTREECTRL_H

// AMDTApplicationFramework:
#include <AMDTApplicationFramework/Include/afApplicationFrameworkDLLBuild.h>

#include <AMDTBaseTools/Include/gtIgnoreCompilerWarnings.h>


// Qt:
#include <QtWidgets>
#include <QTreeWidget>

// Infra:
#include <AMDTApplicationComponents/Include/acTreeCtrl.h>

/// afApplicationTreeCtrl class is derived from acTreeCtrl
/// and is added to allow drag and drop items
/// inside the tree
class AF_API afTreeCtrl : public acTreeCtrl
{

    Q_OBJECT

public:
    afTreeCtrl(QWidget* pParent, int numberOfColumns = 1, bool addPasteAction = true, bool addExpandCollapeAllActions = false);
    virtual ~afTreeCtrl();

    /// event for potential drag start
    void mousePressEvent(QMouseEvent* event);

    /// event for QDragObject creation
    void mouseMoveEvent(QMouseEvent* event);

    /// handles outer or inner drag onto the tree
    void dragEnterEvent(QDragEnterEvent* event);
    void dragMoveEvent(QDragMoveEvent* event);

    void dropEvent(QDropEvent* event);
    Qt::DropActions supportedDropActions() const;
    QStringList mimeTypes() const;
    //Qt::ItemFlags flags(const QModelIndex &index) const;
    QMimeData* mimeData(const QModelIndexList& indexes) const;

    QList<QTreeWidgetItem*> Items(const QMimeData* pMimeData) const { return items(pMimeData); }

    /// Returns the list of dragged items
    /// \return the list of currently dragged items
    const QList<QTreeWidgetItem*> DraggedItems() const { return m_draggedItemsList; };

    /// Is the user currently dragging items?
    bool IsDragging() const { return m_isDragging; }

protected slots:
    /// Handle the drag timer signal:
    void OnDragTimer();

signals:

    /// A drop event has occurred
    void TreeElementDropEvent(QDropEvent* pEvent);

    /// A drag move event has occurred
    void TreeElementDragMoveEvent(QDragMoveEvent* pEvent);

    /// sent before QDrag creation
    void DragAttempt(const QList<QTreeWidgetItem*>& draggedItemsList, bool& canItemBeDragged);

private:
    void PerformDrag();

    void AutoScroll();
private:
    /// drag start position
    QPoint m_startPos;

    /// The current list of dragged items
    QList<QTreeWidgetItem*> m_draggedItemsList;

    /// Contain the hovered item. When the hovered item is changed, the last hovered item's be back to normal
    QTreeWidgetItem* m_pHoveredItem;

    /// flag set to true if current drag permitted
    bool m_isDragging;

    /// Is used to workaround the non-working auto scroll feature of QTreeWidget
    /// Auto scroll is not working while dragging. The bug is documented here:
    /// https://bugreports.qt.io/browse/QTBUG-34819
    /// The workaround suggested in the bug description is implemented
    QTimer* m_pDragTimer;
};

#endif //__AFTREECTRL_H


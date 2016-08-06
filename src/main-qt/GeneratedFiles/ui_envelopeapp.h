/********************************************************************************
** Form generated from reading UI file 'envelopeapp.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENVELOPEAPP_H
#define UI_ENVELOPEAPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "segmentpaintwidget.h"

QT_BEGIN_NAMESPACE

class Ui_EnvelopeAppClass
{
public:
    QAction *actionClear;
    QAction *actionInsert_Random;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    SegmentPaintWidget *envDrawWidget;
    QMenuBar *menuBar;
    QMenu *menuEdit;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *EnvelopeAppClass)
    {
        if (EnvelopeAppClass->objectName().isEmpty())
            EnvelopeAppClass->setObjectName(QStringLiteral("EnvelopeAppClass"));
        EnvelopeAppClass->resize(410, 357);
        actionClear = new QAction(EnvelopeAppClass);
        actionClear->setObjectName(QStringLiteral("actionClear"));
        actionInsert_Random = new QAction(EnvelopeAppClass);
        actionInsert_Random->setObjectName(QStringLiteral("actionInsert_Random"));
        centralWidget = new QWidget(EnvelopeAppClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        envDrawWidget = new SegmentPaintWidget(centralWidget);
        envDrawWidget->setObjectName(QStringLiteral("envDrawWidget"));

        verticalLayout->addWidget(envDrawWidget);

        EnvelopeAppClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(EnvelopeAppClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 410, 21));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        EnvelopeAppClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(EnvelopeAppClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        EnvelopeAppClass->setStatusBar(statusBar);

        menuBar->addAction(menuEdit->menuAction());
        menuEdit->addAction(actionClear);
        menuEdit->addAction(actionInsert_Random);

        retranslateUi(EnvelopeAppClass);

        QMetaObject::connectSlotsByName(EnvelopeAppClass);
    } // setupUi

    void retranslateUi(QMainWindow *EnvelopeAppClass)
    {
        EnvelopeAppClass->setWindowTitle(QApplication::translate("EnvelopeAppClass", "EnvelopeApp", 0));
        actionClear->setText(QApplication::translate("EnvelopeAppClass", "Clear", 0));
        actionClear->setShortcut(QApplication::translate("EnvelopeAppClass", "Ctrl+Q", 0));
        actionInsert_Random->setText(QApplication::translate("EnvelopeAppClass", "Insert Random", 0));
        actionInsert_Random->setShortcut(QApplication::translate("EnvelopeAppClass", "Ctrl+R", 0));
        menuEdit->setTitle(QApplication::translate("EnvelopeAppClass", "Edit", 0));
    } // retranslateUi

};

namespace Ui {
    class EnvelopeAppClass: public Ui_EnvelopeAppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENVELOPEAPP_H

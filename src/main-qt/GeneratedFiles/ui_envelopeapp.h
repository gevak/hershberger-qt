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
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EnvelopeAppClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *EnvelopeAppClass)
    {
        if (EnvelopeAppClass->objectName().isEmpty())
            EnvelopeAppClass->setObjectName(QStringLiteral("EnvelopeAppClass"));
        EnvelopeAppClass->resize(600, 400);
        menuBar = new QMenuBar(EnvelopeAppClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        EnvelopeAppClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(EnvelopeAppClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        EnvelopeAppClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(EnvelopeAppClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        EnvelopeAppClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(EnvelopeAppClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        EnvelopeAppClass->setStatusBar(statusBar);

        retranslateUi(EnvelopeAppClass);

        QMetaObject::connectSlotsByName(EnvelopeAppClass);
    } // setupUi

    void retranslateUi(QMainWindow *EnvelopeAppClass)
    {
        EnvelopeAppClass->setWindowTitle(QApplication::translate("EnvelopeAppClass", "EnvelopeApp", 0));
    } // retranslateUi

};

namespace Ui {
    class EnvelopeAppClass: public Ui_EnvelopeAppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENVELOPEAPP_H

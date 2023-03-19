/********************************************************************************
** Form generated from reading UI file 'TCPWebsocketServer.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCPWEBSOCKETSERVER_H
#define UI_TCPWEBSOCKETSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TCPWebsocketServerClass
{
public:
    QWidget *centralWidget;
    QLabel *label_status;
    QLabel *label_message;
    QPushButton *pushMessageButton;
    QLabel *label_database;
    QLabel *label_user;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TCPWebsocketServerClass)
    {
        if (TCPWebsocketServerClass->objectName().isEmpty())
            TCPWebsocketServerClass->setObjectName(QString::fromUtf8("TCPWebsocketServerClass"));
        TCPWebsocketServerClass->resize(1248, 490);
        centralWidget = new QWidget(TCPWebsocketServerClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label_status = new QLabel(centralWidget);
        label_status->setObjectName(QString::fromUtf8("label_status"));
        label_status->setGeometry(QRect(290, 60, 591, 51));
        label_message = new QLabel(centralWidget);
        label_message->setObjectName(QString::fromUtf8("label_message"));
        label_message->setGeometry(QRect(20, 240, 1201, 71));
        pushMessageButton = new QPushButton(centralWidget);
        pushMessageButton->setObjectName(QString::fromUtf8("pushMessageButton"));
        pushMessageButton->setGeometry(QRect(200, 170, 141, 23));
        label_database = new QLabel(centralWidget);
        label_database->setObjectName(QString::fromUtf8("label_database"));
        label_database->setGeometry(QRect(10, 340, 691, 31));
        label_user = new QLabel(centralWidget);
        label_user->setObjectName(QString::fromUtf8("label_user"));
        label_user->setGeometry(QRect(10, 390, 691, 31));
        TCPWebsocketServerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TCPWebsocketServerClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1248, 22));
        TCPWebsocketServerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TCPWebsocketServerClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        TCPWebsocketServerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(TCPWebsocketServerClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        TCPWebsocketServerClass->setStatusBar(statusBar);

        retranslateUi(TCPWebsocketServerClass);
        QObject::connect(pushMessageButton, SIGNAL(clicked()), TCPWebsocketServerClass, SLOT(onSendMessageButtonClicked()));

        QMetaObject::connectSlotsByName(TCPWebsocketServerClass);
    } // setupUi

    void retranslateUi(QMainWindow *TCPWebsocketServerClass)
    {
        TCPWebsocketServerClass->setWindowTitle(QCoreApplication::translate("TCPWebsocketServerClass", "TCP-Websocket [Server]", nullptr));
        label_status->setText(QString());
        label_message->setText(QString());
        pushMessageButton->setText(QCoreApplication::translate("TCPWebsocketServerClass", "Envoyer message Client", nullptr));
        label_database->setText(QString());
        label_user->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TCPWebsocketServerClass: public Ui_TCPWebsocketServerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCPWEBSOCKETSERVER_H

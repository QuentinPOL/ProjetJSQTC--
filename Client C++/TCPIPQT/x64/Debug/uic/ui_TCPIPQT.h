/********************************************************************************
** Form generated from reading UI file 'TCPIPQT.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCPIPQT_H
#define UI_TCPIPQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TCPIPQTClass
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *IPEdit;
    QLineEdit *PortEdit;
    QPushButton *pushConnectButton;
    QPushButton *pushMessageButton;
    QLabel *label_status;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TCPIPQTClass)
    {
        if (TCPIPQTClass->objectName().isEmpty())
            TCPIPQTClass->setObjectName(QString::fromUtf8("TCPIPQTClass"));
        TCPIPQTClass->resize(555, 400);
        centralWidget = new QWidget(TCPIPQTClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 40, 47, 13));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 70, 47, 13));
        IPEdit = new QLineEdit(centralWidget);
        IPEdit->setObjectName(QString::fromUtf8("IPEdit"));
        IPEdit->setGeometry(QRect(70, 40, 113, 20));
        PortEdit = new QLineEdit(centralWidget);
        PortEdit->setObjectName(QString::fromUtf8("PortEdit"));
        PortEdit->setGeometry(QRect(70, 70, 113, 20));
        pushConnectButton = new QPushButton(centralWidget);
        pushConnectButton->setObjectName(QString::fromUtf8("pushConnectButton"));
        pushConnectButton->setGeometry(QRect(90, 130, 75, 23));
        pushMessageButton = new QPushButton(centralWidget);
        pushMessageButton->setObjectName(QString::fromUtf8("pushMessageButton"));
        pushMessageButton->setGeometry(QRect(320, 150, 141, 23));
        label_status = new QLabel(centralWidget);
        label_status->setObjectName(QString::fromUtf8("label_status"));
        label_status->setGeometry(QRect(200, 45, 371, 31));
        TCPIPQTClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TCPIPQTClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 555, 22));
        TCPIPQTClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TCPIPQTClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        TCPIPQTClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(TCPIPQTClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        TCPIPQTClass->setStatusBar(statusBar);

        retranslateUi(TCPIPQTClass);
        QObject::connect(pushConnectButton, SIGNAL(clicked()), TCPIPQTClass, SLOT(onConnectButtonClicked()));
        QObject::connect(pushMessageButton, SIGNAL(clicked()), TCPIPQTClass, SLOT(onSendMessageButtonClicked()));

        QMetaObject::connectSlotsByName(TCPIPQTClass);
    } // setupUi

    void retranslateUi(QMainWindow *TCPIPQTClass)
    {
        TCPIPQTClass->setWindowTitle(QCoreApplication::translate("TCPIPQTClass", "TCPIPQT", nullptr));
        label->setText(QCoreApplication::translate("TCPIPQTClass", "IP :", nullptr));
        label_2->setText(QCoreApplication::translate("TCPIPQTClass", "Port :", nullptr));
        pushConnectButton->setText(QCoreApplication::translate("TCPIPQTClass", "Connexion", nullptr));
        pushMessageButton->setText(QCoreApplication::translate("TCPIPQTClass", "Envoyer un message", nullptr));
        label_status->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TCPIPQTClass: public Ui_TCPIPQTClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCPIPQT_H

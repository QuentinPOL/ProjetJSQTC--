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
    QLabel *label_username;
    QLabel *label_password;
    QLineEdit *UsernameEdit;
    QLineEdit *PasswordEdit;
    QPushButton *pushSignUptButton;
    QPushButton *pushMessageButton;
    QLabel *label_status;
    QPushButton *pushConnectButton;
    QLineEdit *MessageEdit;
    QLabel *label_error;
    QLabel *label_message;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TCPIPQTClass)
    {
        if (TCPIPQTClass->objectName().isEmpty())
            TCPIPQTClass->setObjectName(QString::fromUtf8("TCPIPQTClass"));
        TCPIPQTClass->setEnabled(true);
        TCPIPQTClass->resize(768, 547);
        TCPIPQTClass->setAutoFillBackground(false);
        centralWidget = new QWidget(TCPIPQTClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label_username = new QLabel(centralWidget);
        label_username->setObjectName(QString::fromUtf8("label_username"));
        label_username->setGeometry(QRect(220, 170, 71, 16));
        label_password = new QLabel(centralWidget);
        label_password->setObjectName(QString::fromUtf8("label_password"));
        label_password->setGeometry(QRect(220, 200, 61, 16));
        UsernameEdit = new QLineEdit(centralWidget);
        UsernameEdit->setObjectName(QString::fromUtf8("UsernameEdit"));
        UsernameEdit->setGeometry(QRect(280, 170, 221, 20));
        PasswordEdit = new QLineEdit(centralWidget);
        PasswordEdit->setObjectName(QString::fromUtf8("PasswordEdit"));
        PasswordEdit->setGeometry(QRect(280, 200, 221, 21));
        pushSignUptButton = new QPushButton(centralWidget);
        pushSignUptButton->setObjectName(QString::fromUtf8("pushSignUptButton"));
        pushSignUptButton->setGeometry(QRect(280, 260, 91, 23));
        pushMessageButton = new QPushButton(centralWidget);
        pushMessageButton->setObjectName(QString::fromUtf8("pushMessageButton"));
        pushMessageButton->setEnabled(false);
        pushMessageButton->setGeometry(QRect(0, 450, 121, 41));
        pushMessageButton->setAutoFillBackground(false);
        pushMessageButton->setStyleSheet(QString::fromUtf8(""));
        pushMessageButton->setAutoDefault(false);
        pushMessageButton->setFlat(false);
        label_status = new QLabel(centralWidget);
        label_status->setObjectName(QString::fromUtf8("label_status"));
        label_status->setGeometry(QRect(20, 10, 171, 21));
        pushConnectButton = new QPushButton(centralWidget);
        pushConnectButton->setObjectName(QString::fromUtf8("pushConnectButton"));
        pushConnectButton->setGeometry(QRect(410, 260, 91, 23));
        MessageEdit = new QLineEdit(centralWidget);
        MessageEdit->setObjectName(QString::fromUtf8("MessageEdit"));
        MessageEdit->setEnabled(false);
        MessageEdit->setGeometry(QRect(120, 450, 641, 41));
        MessageEdit->setStyleSheet(QString::fromUtf8(""));
        label_error = new QLabel(centralWidget);
        label_error->setObjectName(QString::fromUtf8("label_error"));
        label_error->setGeometry(QRect(290, 230, 201, 21));
        label_message = new QLabel(centralWidget);
        label_message->setObjectName(QString::fromUtf8("label_message"));
        label_message->setGeometry(QRect(30, 340, 701, 21));
        TCPIPQTClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TCPIPQTClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 768, 21));
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
        QObject::connect(pushSignUptButton, SIGNAL(clicked()), TCPIPQTClass, SLOT(onSignUpButtonClicked()));

        QMetaObject::connectSlotsByName(TCPIPQTClass);
    } // setupUi

    void retranslateUi(QMainWindow *TCPIPQTClass)
    {
        TCPIPQTClass->setWindowTitle(QCoreApplication::translate("TCPIPQTClass", "Chat Client", nullptr));
        label_username->setText(QCoreApplication::translate("TCPIPQTClass", "Username :", nullptr));
        label_password->setText(QCoreApplication::translate("TCPIPQTClass", "Password :", nullptr));
        UsernameEdit->setPlaceholderText(QCoreApplication::translate("TCPIPQTClass", "Entrez un nom d'utilisateur", nullptr));
        PasswordEdit->setPlaceholderText(QCoreApplication::translate("TCPIPQTClass", "Entrez un mot de passe", nullptr));
        pushSignUptButton->setText(QCoreApplication::translate("TCPIPQTClass", "S'inscrire", nullptr));
        pushMessageButton->setText(QCoreApplication::translate("TCPIPQTClass", "Envoyer", nullptr));
        label_status->setText(QCoreApplication::translate("TCPIPQTClass", "Status : Aucun", nullptr));
        pushConnectButton->setText(QCoreApplication::translate("TCPIPQTClass", "Se connecter", nullptr));
        MessageEdit->setPlaceholderText(QCoreApplication::translate("TCPIPQTClass", "Entrez le texte souhaiter ....", nullptr));
        label_error->setText(QString());
        label_message->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TCPIPQTClass: public Ui_TCPIPQTClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCPIPQT_H

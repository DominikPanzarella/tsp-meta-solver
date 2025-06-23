/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QPushButton *btnOk;
    QPushButton *btnCancel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(525, 307);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(140, 0, 231, 91));
        label->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	font: 700 25pt \"Segoe UI\";\n"
"	color: rgb(255, 255, 255);\n"
"}"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(70, 100, 171, 21));
        label_2->setStyleSheet(QString::fromUtf8("font: 700 16pt \"Segoe UI\";"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(70, 140, 121, 21));
        label_3->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	font: 700 16pt \"Segoe UI\";\n"
"}"));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(200, 100, 201, 31));
        lineEdit->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	font: 16pt \"Segoe UI\";\n"
"}"));
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(200, 140, 201, 31));
        lineEdit_2->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	font: 16pt \"Segoe UI\";\n"
"}"));
        btnOk = new QPushButton(centralwidget);
        btnOk->setObjectName("btnOk");
        btnOk->setGeometry(QRect(210, 190, 81, 31));
        btnOk->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	font: 700 16pt \"Segoe UI\";\n"
"	background-color: rgb(255, 255, 255);\n"
"	color: rgb(0, 0, 0);\n"
"}"));
        btnCancel = new QPushButton(centralwidget);
        btnCancel->setObjectName("btnCancel");
        btnCancel->setGeometry(QRect(310, 190, 91, 31));
        btnCancel->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: rgb(255, 255, 255);\n"
"	font: 700 16pt \"Segoe UI\";\n"
"	color: rgb(0, 0, 0);\n"
"}"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 525, 33));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Login System", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Username :", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Password :", nullptr));
        btnOk->setText(QCoreApplication::translate("MainWindow", "OK", nullptr));
        btnCancel->setText(QCoreApplication::translate("MainWindow", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

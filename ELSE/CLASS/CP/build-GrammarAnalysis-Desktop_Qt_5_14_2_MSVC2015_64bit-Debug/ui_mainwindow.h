/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *title;
    QTextEdit *inputText;
    QPushButton *getFirstSet;
    QPushButton *getFollowSet;
    QPushButton *getLLTable;
    QPushButton *getLRTable;
    QPushButton *getSLRTable;
    QPushButton *enterInput;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(956, 583);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        title = new QLabel(centralWidget);
        title->setObjectName(QString::fromUtf8("title"));
        title->setGeometry(QRect(30, 20, 231, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("Adobe Arabic"));
        font.setPointSize(16);
        title->setFont(font);
        title->setAlignment(Qt::AlignCenter);
        inputText = new QTextEdit(centralWidget);
        inputText->setObjectName(QString::fromUtf8("inputText"));
        inputText->setGeometry(QRect(30, 70, 661, 471));
        QFont font1;
        font1.setPointSize(12);
        inputText->setFont(font1);
        getFirstSet = new QPushButton(centralWidget);
        getFirstSet->setObjectName(QString::fromUtf8("getFirstSet"));
        getFirstSet->setGeometry(QRect(730, 150, 181, 51));
        getFirstSet->setFont(font1);
        getFollowSet = new QPushButton(centralWidget);
        getFollowSet->setObjectName(QString::fromUtf8("getFollowSet"));
        getFollowSet->setGeometry(QRect(730, 230, 181, 51));
        getFollowSet->setFont(font1);
        getLLTable = new QPushButton(centralWidget);
        getLLTable->setObjectName(QString::fromUtf8("getLLTable"));
        getLLTable->setGeometry(QRect(730, 310, 181, 51));
        getLLTable->setFont(font1);
        getLRTable = new QPushButton(centralWidget);
        getLRTable->setObjectName(QString::fromUtf8("getLRTable"));
        getLRTable->setGeometry(QRect(730, 390, 181, 51));
        getLRTable->setFont(font1);
        getSLRTable = new QPushButton(centralWidget);
        getSLRTable->setObjectName(QString::fromUtf8("getSLRTable"));
        getSLRTable->setGeometry(QRect(730, 470, 181, 51));
        getSLRTable->setFont(font1);
        enterInput = new QPushButton(centralWidget);
        enterInput->setObjectName(QString::fromUtf8("enterInput"));
        enterInput->setGeometry(QRect(730, 70, 181, 51));
        enterInput->setFont(font1);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        title->setText(QCoreApplication::translate("MainWindow", "\350\257\255\346\263\225\345\210\206\346\236\220\351\233\206\346\210\220\347\250\213\345\272\217", nullptr));
        inputText->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\350\257\267\345\234\250\350\277\231\351\207\214\350\276\223\345\205\245\346\226\207\346\263\225</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\346\240\274\345\274\217\344\270\272\357\274\232\344\272\247\347\224\237\345\274\217\345\267\246\351\203\250-&gt;\344\272\247\347\224\237\345\274\217\345\217\263\351\203\250</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\347\251\272\344\270\262\350\257\267\347\224"
                        "\250~\344\273\243\346\233\277</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\344\276\213\345\246\202\357\274\232</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">A-&gt;b</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">B-&gt;AC</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">C-&gt;~</p></body></html>", nullptr));
        getFirstSet->setText(QCoreApplication::translate("MainWindow", "\350\216\267\345\217\226first\351\233\206", nullptr));
        getFollowSet->setText(QCoreApplication::translate("MainWindow", "\350\216\267\345\217\226follow\351\233\206", nullptr));
        getLLTable->setText(QCoreApplication::translate("MainWindow", "\350\216\267\345\217\226LL(1)\345\210\206\346\236\220\350\241\250", nullptr));
        getLRTable->setText(QCoreApplication::translate("MainWindow", "\350\216\267\345\217\226LR(0)\345\210\206\346\236\220\350\241\250", nullptr));
        getSLRTable->setText(QCoreApplication::translate("MainWindow", "\350\216\267\345\217\226SLR(0)\345\210\206\346\236\220\350\241\250", nullptr));
        enterInput->setText(QCoreApplication::translate("MainWindow", "\346\233\264\346\226\260\350\276\223\345\205\245\357\274\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

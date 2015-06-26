/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAboutQt;
    QWidget *centralWidget;
    QPushButton *cmdLoadFile;
    QTextEdit *txtHEXTXT;
    QLabel *lblNFrags;
    QPushButton *cmdSaveBINX;
    QLabel *lblNErrors;
    QMenuBar *menuBar;
    QMenu *menu;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(372, 502);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionAboutQt = new QAction(MainWindow);
        actionAboutQt->setObjectName(QStringLiteral("actionAboutQt"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        cmdLoadFile = new QPushButton(centralWidget);
        cmdLoadFile->setObjectName(QStringLiteral("cmdLoadFile"));
        cmdLoadFile->setGeometry(QRect(0, 0, 70, 23));
        txtHEXTXT = new QTextEdit(centralWidget);
        txtHEXTXT->setObjectName(QStringLiteral("txtHEXTXT"));
        txtHEXTXT->setGeometry(QRect(2, 24, 369, 437));
        lblNFrags = new QLabel(centralWidget);
        lblNFrags->setObjectName(QStringLiteral("lblNFrags"));
        lblNFrags->setGeometry(QRect(185, 0, 90, 23));
        lblNFrags->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        cmdSaveBINX = new QPushButton(centralWidget);
        cmdSaveBINX->setObjectName(QStringLiteral("cmdSaveBINX"));
        cmdSaveBINX->setEnabled(false);
        cmdSaveBINX->setGeometry(QRect(70, 0, 70, 23));
        lblNErrors = new QLabel(centralWidget);
        lblNErrors->setObjectName(QStringLiteral("lblNErrors"));
        lblNErrors->setGeometry(QRect(280, 0, 90, 23));
        lblNErrors->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 372, 20));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(actionAboutQt);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "HEX2BINX converter v1.0", 0));
        actionAboutQt->setText(QApplication::translate("MainWindow", "About Qt", 0));
#ifndef QT_NO_TOOLTIP
        actionAboutQt->setToolTip(QApplication::translate("MainWindow", "About Qt", 0));
#endif // QT_NO_TOOLTIP
        cmdLoadFile->setText(QApplication::translate("MainWindow", "Load File..", 0));
        lblNFrags->setText(QApplication::translate("MainWindow", "Fragments: 0", 0));
        cmdSaveBINX->setText(QApplication::translate("MainWindow", "Save BINX..", 0));
        lblNErrors->setText(QApplication::translate("MainWindow", "CRC Errors: 0", 0));
        menu->setTitle(QApplication::translate("MainWindow", "?", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

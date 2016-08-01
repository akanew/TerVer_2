/********************************************************************************
** Form generated from reading UI file 'data_table.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATA_TABLE_H
#define UI_DATA_TABLE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Data_Table
{
public:
    QTableWidget *Data_Table_for_Normal_Distribution;

    void setupUi(QWidget *Data_Table)
    {
        if (Data_Table->objectName().isEmpty())
            Data_Table->setObjectName(QString::fromUtf8("Data_Table"));
        Data_Table->resize(648, 300);
        Data_Table->setMaximumSize(QSize(648, 16777215));
        Data_Table_for_Normal_Distribution = new QTableWidget(Data_Table);
        Data_Table_for_Normal_Distribution->setObjectName(QString::fromUtf8("Data_Table_for_Normal_Distribution"));
        Data_Table_for_Normal_Distribution->setGeometry(QRect(0, 0, 651, 301));
        Data_Table_for_Normal_Distribution->horizontalHeader()->setVisible(false);
        Data_Table_for_Normal_Distribution->horizontalHeader()->setDefaultSectionSize(64);
        Data_Table_for_Normal_Distribution->horizontalHeader()->setMinimumSectionSize(20);
        Data_Table_for_Normal_Distribution->verticalHeader()->setVisible(false);
        Data_Table_for_Normal_Distribution->verticalHeader()->setDefaultSectionSize(20);

        retranslateUi(Data_Table);

        QMetaObject::connectSlotsByName(Data_Table);
    } // setupUi

    void retranslateUi(QWidget *Data_Table)
    {
        Data_Table->setWindowTitle(QApplication::translate("Data_Table", "Data_Table", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Data_Table: public Ui_Data_Table {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATA_TABLE_H

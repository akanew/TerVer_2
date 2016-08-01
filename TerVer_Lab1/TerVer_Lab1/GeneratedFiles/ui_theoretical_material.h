/********************************************************************************
** Form generated from reading UI file 'theoretical_material.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_THEORETICAL_MATERIAL_H
#define UI_THEORETICAL_MATERIAL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Theoretical_Material
{
public:
    QLabel *label;
    QPushButton *Next_Page;
    QPushButton *Previous_Page;

    void setupUi(QWidget *Theoretical_Material)
    {
        if (Theoretical_Material->objectName().isEmpty())
            Theoretical_Material->setObjectName(QString::fromUtf8("Theoretical_Material"));
        Theoretical_Material->resize(648, 694);
        label = new QLabel(Theoretical_Material);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 648, 694));
        Next_Page = new QPushButton(Theoretical_Material);
        Next_Page->setObjectName(QString::fromUtf8("Next_Page"));
        Next_Page->setGeometry(QRect(608, 10, 30, 14));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../../../../Desktop/TerVer_Lab1/TerVer_Lab1/Resources/next.png"), QSize(), QIcon::Normal, QIcon::Off);
        Next_Page->setIcon(icon);
        Previous_Page = new QPushButton(Theoretical_Material);
        Previous_Page->setObjectName(QString::fromUtf8("Previous_Page"));
        Previous_Page->setGeometry(QRect(10, 10, 30, 14));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../../../../../Desktop/TerVer_Lab1/TerVer_Lab1/Resources/back.png"), QSize(), QIcon::Normal, QIcon::Off);
        Previous_Page->setIcon(icon1);

        retranslateUi(Theoretical_Material);

        QMetaObject::connectSlotsByName(Theoretical_Material);
    } // setupUi

    void retranslateUi(QWidget *Theoretical_Material)
    {
        Theoretical_Material->setWindowTitle(QApplication::translate("Theoretical_Material", "Theoretical_Material", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        Next_Page->setText(QString());
        Previous_Page->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Theoretical_Material: public Ui_Theoretical_Material {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_THEORETICAL_MATERIAL_H

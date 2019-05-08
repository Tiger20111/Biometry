/********************************************************************************
** Form generated from reading UI file 'demonstration.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEMONSTRATION_H
#define UI_DEMONSTRATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_demonstrationClass
{
public:

    void setupUi(QWidget *demonstrationClass)
    {
        if (demonstrationClass->objectName().isEmpty())
            demonstrationClass->setObjectName(QString::fromUtf8("demonstrationClass"));
        demonstrationClass->resize(600, 400);

        retranslateUi(demonstrationClass);

        QMetaObject::connectSlotsByName(demonstrationClass);
    } // setupUi

    void retranslateUi(QWidget *demonstrationClass)
    {
        demonstrationClass->setWindowTitle(QApplication::translate("demonstrationClass", "demonstration", nullptr));
    } // retranslateUi

};

namespace Ui {
    class demonstrationClass: public Ui_demonstrationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEMONSTRATION_H

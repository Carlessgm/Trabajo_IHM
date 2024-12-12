/********************************************************************************
** Form generated from reading UI file 'pantallaranking.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANTALLARANKING_H
#define UI_PANTALLARANKING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PantallaRanking
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTableView *tableView;

    void setupUi(QWidget *PantallaRanking)
    {
        if (PantallaRanking->objectName().isEmpty())
            PantallaRanking->setObjectName("PantallaRanking");
        PantallaRanking->resize(620, 419);
        verticalLayout = new QVBoxLayout(PantallaRanking);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(PantallaRanking);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        label->setFont(font);
        label->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label);

        tableView = new QTableView(PantallaRanking);
        tableView->setObjectName("tableView");

        verticalLayout->addWidget(tableView);


        retranslateUi(PantallaRanking);

        QMetaObject::connectSlotsByName(PantallaRanking);
    } // setupUi

    void retranslateUi(QWidget *PantallaRanking)
    {
        PantallaRanking->setWindowTitle(QCoreApplication::translate("PantallaRanking", "Form", nullptr));
        label->setText(QCoreApplication::translate("PantallaRanking", "RANKING", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PantallaRanking: public Ui_PantallaRanking {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANTALLARANKING_H

/********************************************************************************
** Form generated from reading UI file 'CameraApp.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERAAPP_H
#define UI_CAMERAAPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QtImageManager.h"

QT_BEGIN_NAMESPACE

class Ui_CameraAppClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QFrame *line;
    CQtImageManager *window2;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QFrame *line_2;
    CQtImageManager *window3;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *train_but;
    QPushButton *image_cap;
    QPushButton *video_cap;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CameraAppClass)
    {
        if (CameraAppClass->objectName().isEmpty())
            CameraAppClass->setObjectName(QStringLiteral("CameraAppClass"));
        CameraAppClass->resize(570, 525);
        QIcon icon;
        icon.addFile(QStringLiteral("icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        CameraAppClass->setWindowIcon(icon);
        centralWidget = new QWidget(CameraAppClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_4 = new QVBoxLayout(centralWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(16777215, 20));

        verticalLayout->addWidget(label_2);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        window2 = new CQtImageManager(centralWidget);
        window2->setObjectName(QStringLiteral("window2"));

        verticalLayout->addWidget(window2);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer_3 = new QSpacerItem(13, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(16777215, 20));

        verticalLayout_2->addWidget(label);

        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_2);

        window3 = new CQtImageManager(centralWidget);
        window3->setObjectName(QStringLiteral("window3"));

        verticalLayout_2->addWidget(window3);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(17, 13, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        train_but = new QPushButton(centralWidget);
        train_but->setObjectName(QStringLiteral("train_but"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(train_but->sizePolicy().hasHeightForWidth());
        train_but->setSizePolicy(sizePolicy);
        train_but->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_2->addWidget(train_but);

        image_cap = new QPushButton(centralWidget);
        image_cap->setObjectName(QStringLiteral("image_cap"));
        sizePolicy.setHeightForWidth(image_cap->sizePolicy().hasHeightForWidth());
        image_cap->setSizePolicy(sizePolicy);
        image_cap->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_2->addWidget(image_cap);

        video_cap = new QPushButton(centralWidget);
        video_cap->setObjectName(QStringLiteral("video_cap"));
        sizePolicy.setHeightForWidth(video_cap->sizePolicy().hasHeightForWidth());
        video_cap->setSizePolicy(sizePolicy);
        video_cap->setMaximumSize(QSize(16777215, 30));
        video_cap->setCheckable(true);

        horizontalLayout_2->addWidget(video_cap);


        verticalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout_4->addLayout(verticalLayout_3);

        CameraAppClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CameraAppClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 570, 21));
        CameraAppClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CameraAppClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CameraAppClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CameraAppClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CameraAppClass->setStatusBar(statusBar);

        retranslateUi(CameraAppClass);

        QMetaObject::connectSlotsByName(CameraAppClass);
    } // setupUi

    void retranslateUi(QMainWindow *CameraAppClass)
    {
        CameraAppClass->setWindowTitle(QApplication::translate("CameraAppClass", "Camera App", Q_NULLPTR));
        label_2->setText(QApplication::translate("CameraAppClass", "Thresholded image", Q_NULLPTR));
        label->setText(QApplication::translate("CameraAppClass", "Result image", Q_NULLPTR));
        train_but->setText(QApplication::translate("CameraAppClass", "Train Classifier", Q_NULLPTR));
        image_cap->setText(QApplication::translate("CameraAppClass", "Open Image", Q_NULLPTR));
        video_cap->setText(QApplication::translate("CameraAppClass", "Video capture", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CameraAppClass: public Ui_CameraAppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERAAPP_H

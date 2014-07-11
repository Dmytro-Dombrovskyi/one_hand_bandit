#include "banditwindow.h"

BanditWindow::BanditWindow(QWidget *parent) :
    QWidget(parent)
{
    label_1 = new QLabel;
    label_1->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label_1->setMinimumSize(100, 100);
    //label_1->setPixmap();

    label_2 = new QLabel;
    label_2->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label_2->setMinimumSize(100, 100);

    label_3 = new QLabel;
    label_3->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label_3->setMinimumSize(100, 100);

    set_pictures();

    label_1->setPixmap(picture_1);

    quit_button = new QPushButton(tr("&Quit"));

    connect(quit_button, SIGNAL(clicked()),
            this, SLOT(quit_game()) );

    QHBoxLayout * horizontal_layout_1 = new QHBoxLayout;

    horizontal_layout_1->addWidget(label_1);
    horizontal_layout_1->addWidget(label_2);
    horizontal_layout_1->addWidget(label_3);

    QHBoxLayout * horizontal_layout_2 = new QHBoxLayout;

    horizontal_layout_2->addWidget(quit_button);

    QGridLayout * main_layout = new QGridLayout;

    main_layout->addLayout(horizontal_layout_1, 0, 0);
    main_layout->addLayout(horizontal_layout_2, 1, 0);

    setLayout(main_layout);
    setWindowTitle(tr("one hand bandit"));
}
// quit
void BanditWindow::quit_game()
{
    QMessageBox::StandardButton answer =
            QMessageBox::question(this, "Quit dialog",
                                  "Do you really want to quit?",
                                  QMessageBox::Yes |
                                  QMessageBox::No);
    if(answer == QMessageBox::Yes)
        QApplication::instance()->quit();
}
// resize picture
//void BanditWindow::resizeEvent(QResizeEvent *event)
//{
//    QWidget::resizeEvent(event);

//    double width_ration =
//            static_cast<double>(event->size().height()) / event->oldSize().height();
//    double height_ration =
//            static_cast<double>(event->size().width()) / event->oldSize().width();
//    int new_width = label[0]->width() * width_ration;
//    int new_height = label[0]->height() * height_ration;


//    if(label[0]->pixmap())
//    {
//        label[0]->setPixmap(picture_1->scaled(new_width, new_height,
//                                          Qt::KeepAspectRatio));
//    }
//}
void BanditWindow::set_pictures()
{
    picture_1->load(belka_1.png);
    //picture_2;
    //picture_3;
    //picture_4;
    //picture_5;
}

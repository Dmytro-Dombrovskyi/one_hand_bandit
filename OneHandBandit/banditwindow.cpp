#include "banditwindow.h"

BanditWindow::BanditWindow(QWidget *parent) :
    QWidget(parent)
{

    set_pictures();
    set_labels();

    quit_button = new QPushButton(tr("&Quit"));
    start_game_button = new QPushButton(tr("Start Game"));

    connect(quit_button, SIGNAL(clicked()),
            this, SLOT(quit_game()) );
    connect(start_game_button, SIGNAL(clicked()),
            this, SLOT(start_game()) );

    QHBoxLayout * horizontal_layout_1 = new QHBoxLayout;
    for(int i = 0; i < 3; ++i)
    {
       horizontal_layout_1->addWidget(label.at(i));
    }

    QHBoxLayout * horizontal_layout_2 = new QHBoxLayout;

    horizontal_layout_2->addWidget(quit_button);
    horizontal_layout_2->addWidget(start_game_button);

    QGridLayout * main_layout = new QGridLayout;

    main_layout->addLayout(horizontal_layout_1, 0, 0);
    main_layout->addLayout(horizontal_layout_2, 1, 0);

    setLayout(main_layout);
    setWindowTitle(tr("one hand bandit"));
}

// set pictures
void BanditWindow::set_pictures(const int num_of_pictures)
{
    QString filename;
    for(int i = 0; i < num_of_pictures; ++i)
    {
        pictures.push_back(QSharedPointer<QPixmap>::create());
        filename = (":/images/images/belka_" +
                    QString::number(i) + ".png");
        pictures.at(i)->load(filename);
    }
}
void BanditWindow::set_labels(const int lb_size)
{
    for(int i = 0; i < 3; ++i)
    {
        label.append(new QLabel);
        label.at(i)->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        label.at(i)->setMinimumSize(lb_size, lb_size);
        if(!pictures.at(i)->isNull())
            label.at(i)->setPixmap(*pictures.at(i));
    }
}
// resize picture
//void BanditWindow::resizeEvent(QResizeEvent *event)
//{
//    QWidget::resizeEvent(event);

//    double width_ration =
//            static_cast<double>(event->size().height()) / event->oldSize().height();
//    double height_ration =
//            static_cast<double>(event->size().width()) / event->oldSize().width();
//    int new_width = label.at(0)->width() * width_ration;
//    int new_height = label.at(0)->height() * height_ration;

//    QVector<QLabel>::iterator lb_itr = label.begin();
//    while(lb_itr != label.end())
//    {
//        if(lb_itr->pixmap())
//        {
//            lb_itr->setPixmap(lb_itr->ge);
//        }
//    }
//    if(label_1->pixmap())
//    {
//        label_1->setPixmap(picture_1->scaled(new_width, new_height,
//                                      Qt::KeepAspectRatio));
//    }
//    if(label_2->pixmap())
//    {
//        label_2->setPixmap(picture_2->scaled(new_width, new_height,
//                                      Qt::KeepAspectRatio));
//    }
//    if(label_3->pixmap())
//    {
//        label_3->setPixmap(picture_3->scaled(new_width, new_height,
//                                      Qt::KeepAspectRatio));
//    }
//}

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

// start game
void BanditWindow::start_game()
{
    int num_picture = 0;
    for(int num_label = 1; num_label < 3; ++num_label)
    {
        num_picture = static_cast<int>(qrand() % 5) + 1;

        if(!pictures.at(num_label)->isNull())
            label.at(num_label)->setPixmap(*pictures.at(num_picture));
    }
}






























#include "banditwindow.h"

BanditWindow::BanditWindow(QWidget *parent) :
    QWidget(parent)
{

    set_pictures();
    set_labels();
    load_pictures_to_labels();

    quit_button = new QPushButton(tr("&Quit"));
    start_game_button = new QPushButton(tr("Start Game"));

    connect(quit_button, SIGNAL(clicked()),
            this, SLOT(quit_game()) );
    connect(start_game_button, SIGNAL(clicked()),
            this, SLOT(start_game()) );

    QHBoxLayout * horizontal_layout_1 = new QHBoxLayout;

    horizontal_layout_1->addWidget(label_1);
    horizontal_layout_1->addWidget(label_2);
    horizontal_layout_1->addWidget(label_3);

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
void BanditWindow::set_pictures()
{
    picture_1 = QSharedPointer<QPixmap>::create();
    picture_2 = QSharedPointer<QPixmap>::create();
    picture_3 = QSharedPointer<QPixmap>::create();
    picture_4 = QSharedPointer<QPixmap>::create();
    picture_5 = QSharedPointer<QPixmap>::create();

    picture_1->load(":/images/images/belka_1.png");
    picture_2->load(":/images/images/belka_2.png");
    picture_3->load(":/images/images/belka_3.png");
    picture_4->load(":/images/images/belka_4.png");
    picture_5->load(":/images/images/belka_5.png");
}
void BanditWindow::set_labels(const int lb_size)
{
    label_1 = new QLabel;
    label_1->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label_1->setMinimumSize(lb_size, lb_size);

    label_2 = new QLabel;
    label_2->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label_2->setMinimumSize(lb_size, lb_size);

    label_3 = new QLabel;
    label_3->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label_3->setMinimumSize(lb_size, lb_size);
}

void BanditWindow::load_pictures_to_labels()
{
    if(!picture_1->isNull()) label_1->setPixmap(*picture_1);
    if(!picture_2->isNull()) label_2->setPixmap(*picture_2);
    if(!picture_3->isNull()) label_3->setPixmap(*picture_3);
}

// resize picture
void BanditWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    double width_ration =
            static_cast<double>(event->size().height()) / event->oldSize().height();
    double height_ration =
            static_cast<double>(event->size().width()) / event->oldSize().width();
    int new_width = label_1->width() * width_ration;
    int new_height = label_1->height() * height_ration;


    if(label_1->pixmap())
    {
        label_1->setPixmap(picture_1->scaled(new_width, new_height,
                                      Qt::KeepAspectRatio));
    }
    if(label_2->pixmap())
    {
        label_2->setPixmap(picture_2->scaled(new_width, new_height,
                                      Qt::KeepAspectRatio));
    }
    if(label_3->pixmap())
    {
        label_3->setPixmap(picture_3->scaled(new_width, new_height,
                                      Qt::KeepAspectRatio));
    }
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
// start game
void BanditWindow::start_game()
{
    int num_picture = 0;
    for(int num_label = 1; num_label <= 3; ++num_label)
    {
        num_picture = static_cast<int>(qrand() % 5) + 1;
        set_picture(num_label, num_picture);
    }
}

void BanditWindow::set_picture(const int num_label, const int num_picture)
{
    QSharedPointer<QPixmap> temp_pixmap =
            QSharedPointer<QPixmap>::create();
    // swith picture by number
    switch (num_picture) {
    case 1:
        temp_pixmap = picture_1;
        break;
    case 2:
        temp_pixmap = picture_2;
    case 3:
        temp_pixmap = picture_3;
    case 4:
        temp_pixmap = picture_4;
    case 5:
        temp_pixmap = picture_5;
    default:
        break;
    }
    // switch label by number
    switch(num_label)
    {
    case 1:
        if(!temp_pixmap->isNull())
            label_1->setPixmap(*temp_pixmap);
        break;
    case 2:
        if(!temp_pixmap->isNull())
            label_2->setPixmap(*temp_pixmap);
    case 3:
        if(!temp_pixmap->isNull())
            label_3->setPixmap(*temp_pixmap);
    default:
        break;
    }
}
































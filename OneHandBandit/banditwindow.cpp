#include "banditwindow.h"

// initial static variables
int BanditWindow::scores_counter_ = 0;
int BanditWindow::tryes_counter_ = 0;

BanditWindow::BanditWindow(QWidget *parent) :
    QWidget(parent), scores_label(nullptr), tryes_label(nullptr)
{
    scores_label = new QLabel(tr("Scores: "));
    tryes_label  = new QLabel(tr("Tryes : "));

    set_pictures();
    set_labels();

    quit_button = new QPushButton(tr("&Quit"));
    quit_button->sizeHint();
    start_game_button = new QPushButton(tr("Start Game"));

    connect(quit_button, SIGNAL(clicked()),
            this, SLOT(quit_game()) );
    connect(start_game_button, SIGNAL(clicked()),
            this, SLOT(start_game()) );

    QHBoxLayout * horizontal_layout_1 = new QHBoxLayout;
    for(int i = 0; i < label.size(); ++i)
    {
       horizontal_layout_1->addWidget(label.at(i));
    }

    QVBoxLayout * tryes_and_scores_layout = new QVBoxLayout;
    tryes_and_scores_layout->addWidget(scores_label);
    tryes_and_scores_layout->addWidget(tryes_label);

    QHBoxLayout * buttons_layout = new QHBoxLayout;
    buttons_layout->addWidget(quit_button);
    buttons_layout->addWidget(start_game_button);

    QGridLayout * main_layout = new QGridLayout;
    main_layout->addLayout(horizontal_layout_1, 0, 1);
    main_layout->addLayout(tryes_and_scores_layout, 1, 0);
    main_layout->addLayout(buttons_layout, 1, 1);

    setLayout(main_layout);
    setWindowTitle(tr("one hand bandit"));
}

// set pictures
void BanditWindow::set_pictures(const int num_of_pictures)
{
    for(int i = 1; i <= num_of_pictures; ++i)
    {
        picture_path.push_back(":/images/images/belka_" +
                               QString::number(i) + ".png");
    }
}
void BanditWindow::set_labels(const int lb_size)
{    
    for(int i = 0; i < 3; ++i)
    {
        label.push_back(new QLabel);
        label[i]->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        label[i]->setMinimumSize(lb_size, lb_size);
        label[i]->setMaximumSize(400, 400);

        if(!picture_path.at(i).isNull())
        {            
            label[i]->setPixmap(QPixmap(picture_path.at(i)).scaled(
                                    label.at(i)->size(),
                                        Qt::KeepAspectRatio,
                                        Qt::SmoothTransformation));
        }
    }
}
// resize picture
//void BanditWindow::resizeEvent(QResizeEvent *event)
//{
//   QWidget::resizeEvent(event);
//   QPixmap temp;

//   double width_ration =
//            static_cast<double>(event->size().height()) / event->oldSize().height();
//   double height_ration =
//            static_cast<double>(event->size().width()) / event->oldSize().width();

//   for(int i = 0; i < label.size(); ++i)
//   {
//       int new_width  = label.at(i)->width()  * width_ration;
//       int new_height = label.at(i)->height() * height_ration;

//       if(label.at(i)->pixmap())
//       {
//           temp = *label.at(i)->pixmap();
//       }
//            label[i]->setPixmap(temp.scaled(new_width, new_height,
//                                    Qt::KeepAspectRatio,
//                                    Qt::SmoothTransformation));
//   }
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
    for(int num_label = 0; num_label < 3; ++num_label)
    {
        num_picture = static_cast<int>(qrand() % 5);

        if(!picture_path.at(num_picture).isNull())
        {
            label[num_label]->setPixmap(QPixmap
                            (picture_path.at(num_picture)).
                                        scaled(label.at(num_label)->size(),
                                                 Qt::KeepAspectRatio,
                                                 Qt::SmoothTransformation));
        }
    }
}






























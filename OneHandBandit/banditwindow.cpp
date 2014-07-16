#include "banditwindow.h"

BanditWindow::BanditWindow(QWidget *parent) :
    QWidget(parent), scores_label(nullptr), tryes_label(nullptr)
{
    scores_label = new QLabel("Score: " + QString::number(scores_counter_));
    tryes_label  = new QLabel("Tryes: " + QString::number(tryes_counter_));

    set_pictures();
    set_labels();

    quit_button = new QPushButton(tr("&Quit"));    
    start_game_button = new QPushButton(tr("Start Game"));

    connect(quit_button, SIGNAL(clicked()),
            this, SLOT(quit_game()) );
    connect(start_game_button, SIGNAL(clicked()),
            this, SLOT(start_game()) );

    set_layouts();

    setWindowTitle(tr("One hand bandit"));
}


// set pictures
void BanditWindow::set_pictures()
{
    my_picture.push_back(QPixmap(":/images/images/elefant.png"));
    my_picture.push_back(QPixmap(":/images/images/fish.png"));
    my_picture.push_back(QPixmap(":/images/images/turkey.png"));
    my_picture.push_back(QPixmap(":/images/images/cat.png"));
    my_picture.push_back(QPixmap(":/images/images/belka_5.png"));
}
void BanditWindow::set_labels(const int lb_numbers)
{    
    for(int i = 0; i < lb_numbers; ++i)
    {
        create_new_label();        
        set_new_picture_in_label(i, i);
        set_labels_style();
    }    
}

void BanditWindow::create_new_label()
{
    label.push_back(new QLabel());
}

void BanditWindow::set_layouts()
{
    QHBoxLayout * horizontal_layout_1 = new QHBoxLayout;
    for(int i = 0; i < label.size(); ++i)
    {
       horizontal_layout_1->addWidget(label.at(i));
    }

    QVBoxLayout * tryes_and_scores_layout = new QVBoxLayout;
    tryes_and_scores_layout->addWidget(scores_label);
    tryes_and_scores_layout->addWidget(tryes_label);

    QHBoxLayout * buttons_layout = new QHBoxLayout;
    //buttons_layout->addStretch(1);
    buttons_layout->addWidget(quit_button);
    buttons_layout->addWidget(start_game_button);

    QGridLayout * main_layout = new QGridLayout;
    main_layout->addLayout(horizontal_layout_1, 0, 0, 1, 3);
    main_layout->addLayout(tryes_and_scores_layout, 1, 0);
    main_layout->addLayout(buttons_layout, 1, 1);

    setLayout(main_layout);
}

void BanditWindow::set_labels_style()
{
    foreach(QLabel * temp, label)
    {
        temp->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        temp->setMinimumSize(100, 100);
        temp->setMaximumSize(500, 500);
        //temp->setFixedSize(100, 100);
    }
}

// resize picture
void BanditWindow::resizeEvent(QResizeEvent *event)
{
   QWidget::resizeEvent(event);
   QPixmap temp;

   double width_ration =
            static_cast<double>(event->size().height()) / event->oldSize().height();
   double height_ration =
            static_cast<double>(event->size().width()) / event->oldSize().width();
   if(!(label.empty()))
   {
       int new_width  = label.front()->width()  * width_ration;
       int new_height = label.front()->height() * height_ration;
       for(int i = 0; i < label.size(); ++i)
       {
           if(label.at(i)->pixmap())
           {
               temp = *(label.at(i)->pixmap());
           }
           label[i]->clear();
                label[i]->setPixmap(temp.scaled(new_width,
                                                new_height,
                                        Qt::KeepAspectRatio));
       }
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
void BanditWindow::end_game()
{
    QString message = "Your attmepts are over! ";
    message.append(QString::number(get_scores()));
    message.append(" times! Try again?");

    QMessageBox::StandardButton answer =
            QMessageBox::information(this, "Game over",
                                     message,
                                     QMessageBox::Yes |
                                     QMessageBox::No);
    if(answer == QMessageBox::Yes)
    {
        reset_account();
    }
    if(answer == QMessageBox::No)
        QApplication::instance()->quit();
}

void BanditWindow::message_congratulation()
{
    QMessageBox::information(this, "Congratulation",
                             "Congratulation!,"
                             "You Win the round!");
}

void BanditWindow::set_new_picture_in_label(const int num_label,
                                            const int num_picture)
{
    if(!my_picture.at(num_picture).isNull())
    {
        label[num_label]->setPixmap(my_picture[num_picture]
                                    .scaled(label.at(num_label)->size(),
                                            Qt::KeepAspectRatio,
                                            Qt::SmoothTransformation));
    }
}

// start game
void BanditWindow::start_game()
{
    if(tryes_counter_)
    {
        decrese_tryes();
        set_new_tryes_label();


        QVector<int> random_numbers;

        int num_picture = 0;
        for(int num_label = 0; num_label < label.size(); ++num_label)
        {
            num_picture = static_cast<int>(qrand() % 5);

            set_new_picture_in_label(num_label, num_picture);
            random_numbers.push_back(num_picture);
        }

        if(picture_coincidence(random_numbers) == true)
        {
            set_win_round();
        }

        if(tryes_counter_ == 0)
        {
          end_game();
        }
    }
}

bool BanditWindow::picture_coincidence(const QVector<int> &number_arr)
{
    // check range
    if(number_arr.empty()) return false;

    int number = number_arr.front();
    foreach(int num_next, number_arr)
    {
        if(number != num_next)
            return false;
    }
    return true;
}

void BanditWindow::set_new_score_label()
{
    scores_label->setText("Score: " + QString::number(get_scores()));
}

void BanditWindow::set_new_tryes_label()
{
    tryes_label->setText("Tryes: " + QString::number(get_tryes()));
}

void BanditWindow::reset_account()
{
    reset_scores();
    reset_tryes();
    set_new_score_label();
    set_new_tryes_label();
}

void BanditWindow::set_win_round()
{
    message_congratulation();
    increse_scores();
    increse_tryes();
    set_new_score_label();
    set_new_tryes_label();
}























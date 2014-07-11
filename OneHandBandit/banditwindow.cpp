#include "banditwindow.h"

BanditWindow::BanditWindow(QWidget *parent) :
    QWidget(parent), label(nullptr), quit_button(nullptr),
    load_picture_button(nullptr)
{
    const int lbl_num = 3;
    *label = new QLabel[lbl_num];
    for(int i = 0; i < lbl_num; ++i)
    {
        label[i] = new QLabel;
        label[i]->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        label[i]->setAlignment(Qt::AlignCenter);
        label[i]->setMinimumSize(100, 100);
    }

    quit_button = new QPushButton(tr("&Quit"));
    //game_button = new QPushButton(tr("Go"));
    load_picture_button = new QPushButton(tr("&Load"));

    const int pict_num = 5;
    pictures = new QSharedPointer<QPixmap>[pict_num];
    for(int i = 0; i < pict_num; ++i)
    {
        pictures[i] = QSharedPointer<QPixmap>::create();
    }



    connect(quit_button, SIGNAL(clicked()),
            this, SLOT(quit_game()) );
    connect(load_picture_button, SIGNAL(clicked()),
            this, SLOT(load_picture()) );


    QGridLayout *layout = new QGridLayout;    
    layout->addWidget(label, 0, 0, 1, 2);
    layout->addWidget(quit_button, 1, 0);
    layout->addWidget(load_picture_button, 1, 1);

    setLayout(layout);
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
// load new picture for the game
void BanditWindow::load_picture()
{
    QString fileNameLoad =
            QFileDialog::getOpenFileName(this, tr("file name: "), "",
                                        ("Png files (*.png);;\
                                          Jpeg files (*.jpeg *.jpg);;\
                                          Bmp files (*.bmp)") );
    if(fileNameLoad != "")
    {
        pictures->load(fileNameLoad);

        if(!pictures->isNull())
        {
            int w = label->width();
            int h = label->height();

            label->setPixmap(pictures->scaled(w,h,Qt::KeepAspectRatio));
        }
        else
        {
            QMessageBox::information(this, "Can't load file!",
                                     tr("Fail file to load %1.").arg(fileNameLoad));
            return;
        }
    }
}

void BanditWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    double width_ration =
            static_cast<double>(event->size().height()) / event->oldSize().height();
    double height_ration =
            static_cast<double>(event->size().width()) / event->oldSize().width();
    int new_width = label->width() * width_ration;
    int new_height = label->height() * height_ration;

    if(label->pixmap())
    {
        label->setPixmap(pictures->scaled(new_width, new_height,
                                          Qt::KeepAspectRatio));
    }
}

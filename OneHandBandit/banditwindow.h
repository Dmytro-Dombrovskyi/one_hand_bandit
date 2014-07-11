#ifndef BANDITWINDOW_H
#define BANDITWINDOW_H

#include <QWidget>
#include <QApplication>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include <QResizeEvent>


class BanditWindow : public QWidget
{
    Q_OBJECT
public:
    explicit BanditWindow(QWidget *parent = nullptr);

signals:    

public slots:
    void quit_game();
    void load_picture();

protected:
    void resizeEvent(QResizeEvent *event);

private:
    QLabel **label;

    QPushButton *quit_button;
    QPushButton *load_picture_button;
    //QPushButton *game_button;

    // pictures
    QSharedPointer<QPixmap> *pictures;

   // QPixmap *picture_2;
   // QPixmap *picture_3;
   // QPixmap *picture_4;
   // QPixmap *picture_5;
};

#endif // BANDITWINDOW_H

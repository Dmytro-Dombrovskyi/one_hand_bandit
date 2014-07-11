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
#include <QtGlobal>
#include <QTime>


class BanditWindow : public QWidget
{
    Q_OBJECT
public:
    explicit BanditWindow(QWidget *parent = nullptr);

signals:    

public slots:
    void quit_game();
    void start_game();

protected:
    void resizeEvent(QResizeEvent *event);

private:
    QLabel *label_1;
    QLabel *label_2;
    QLabel *label_3;

    QPushButton *quit_button;
    QPushButton *start_game_button;

    // pictures
    QSharedPointer<QPixmap> picture_1;
    QSharedPointer<QPixmap> picture_2;
    QSharedPointer<QPixmap> picture_3;
    QSharedPointer<QPixmap> picture_4;
    QSharedPointer<QPixmap> picture_5;

    void set_pictures();
    void set_labels(const int lb_size = 200);
    void load_pictures_to_labels();

    void set_picture(const int num_label, const int num_picture);
};

#endif // BANDITWINDOW_H

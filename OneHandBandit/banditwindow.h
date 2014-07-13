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
   //void resizeEvent(QResizeEvent *event);

private:
    QVector<QLabel*> label;
    QVector<QString> picture_path;

    QPushButton *quit_button;
    QPushButton *start_game_button;

    void set_pictures(const int = 5);
    void set_labels(const int lb_size = 200);

    //void set_picture(const int num_label, const int num_picture);
};

#endif // BANDITWINDOW_H

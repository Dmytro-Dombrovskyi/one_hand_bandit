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
 //  void resizeEvent(QResizeEvent *event);

private:
    QLabel *scores_label;
    QLabel *tryes_label;

    int scores_counter_;
    int tryes_counter_;

    QVector<QLabel*> label;
    QVector<QString> picture_path;

    QPushButton *quit_button;
    QPushButton *start_game_button;

    void set_pictures(const int = 5);
    void set_labels(const int lb_size = 200);

    void set_new_picture_in_label(const int, const int);


    inline void increse_scores() { scores_counter_ += 1; }

    inline void increse_tryes() { scores_counter_ += 1;}
    inline void decrese_tryes() { tryes_counter_ -= 1;}

    inline int get_scores() const {return scores_counter_;}
    inline int get_tryes() const {return tryes_counter_;}

    void set_new_score_label();
    void set_new_tryes_label();
    bool picture_coincidence(QVector<int> & random_number);

    //void set_picture(const int num_label, const int num_picture);
};

#endif // BANDITWINDOW_H

#ifndef POKEMON_WIDGET_H
#define POKEMON_WIDGET_H

#include <QWidget>
#include "my_pokemon.h"

namespace Ui {
class pokemon_widget;
}

class pokemon_widget : public QWidget
{
    Q_OBJECT

public:
    explicit pokemon_widget(QWidget *parent = nullptr);
    ~pokemon_widget();

private:
    Ui::pokemon_widget *ui;
    my_pkm_container pkm;

public slots:
    void show_pokemon(my_pkm_container);
    void show_own_pokemon(my_pkm_container);
private slots:
    void on_name_returnPressed();

signals:
    void pkm_changed(my_pkm_container);

};

#endif // POKEMON_WIDGET_H

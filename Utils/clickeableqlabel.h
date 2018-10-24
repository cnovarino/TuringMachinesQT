#ifndef CLICKEABLEQLABEL_H
#define CLICKEABLEQLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>

class ClickeableQLabel : public QLabel
{
    Q_OBJECT
public:
    ClickeableQLabel(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    QString getReference() const;
    void setReference(const QString &value);

private:
    QString reference;

signals:
    void clicked(QString reference);

protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // CLICKEABLEQLABEL_H

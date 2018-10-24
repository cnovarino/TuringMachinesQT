#include "clickeableqlabel.h"

ClickeableQLabel::ClickeableQLabel(QWidget *parent, Qt::WindowFlags f)
    : QLabel(parent)
{
    Q_UNUSED(f);

}

QString ClickeableQLabel::getReference() const
{
    return reference;
}

void ClickeableQLabel::setReference(const QString &value)
{
    reference = value;
}

void ClickeableQLabel::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit clicked(reference);
}

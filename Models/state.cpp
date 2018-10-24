#include "state.h"
#include <QDebug>

State::State(const State *other)
{
    this->name = other->getName();
    this->on_zero = other->getOn_zero();
    this->on_one = other->getOn_one();
}

State::State(QString name)
{
    this->name = name.toLower();
}

State::State(QString name, StateAction on_zero, StateAction on_one)
{
    this->name = name.toLower();
    this->on_zero = on_zero;
    this->on_one = on_one;

}

StateAction State::getOn_zero() const
{
    return on_zero;
}

StateAction State::getOn_one() const
{
    return on_one;
}

const QString State::toString()
{
    return name + "\t" + on_zero.toString() + "\t" + on_one.toString();
}

bool State::operator==(const State &other)
{
    return this->getName() == other.getName();
}

StateAction State::getAction(int reading)
{
    if(reading)
        return on_one;
    else
        return on_zero;
}

QJsonObject State::toJson()
{
    QJsonObject result;
    result.insert("name",name);
    result.insert("on_zero",on_zero.toJson());
    result.insert("on_one",on_one.toJson());

    return  result;
}

void State::validateActions()
{
    on_one.validateAction();
    on_zero.validateAction();
}

void State::setName(const QString &value)
{
    name = value.toLower();
}

void State::setOn_zero(const StateAction &value)
{
    on_zero = value;
}

void State::setOn_one(const StateAction &value)
{
    on_one = value;
}

QString State::getName() const
{
    return name.toLower();
}

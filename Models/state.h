#ifndef STATE_H
#define STATE_H

#include <QString>
#include <QJsonObject>
#include "stateaction.h"

class State
{
public:
    State();
    State(const State* other);
    State(QString name);
    State(QString name, StateAction on_zero,StateAction on_one);

    QString getName() const;
    StateAction getOn_zero() const;
    StateAction getOn_one() const;

    void setName(const QString &value);
    void setOn_zero(const StateAction &value);
    void setOn_one(const StateAction &value);

    const QString toString();

    bool operator==(const State &other);

    StateAction getAction(int reading);

    QJsonObject toJson();

    void validateActions();


private:
    QString name;
    StateAction on_zero;
    StateAction on_one;

};

#endif // STATE_H


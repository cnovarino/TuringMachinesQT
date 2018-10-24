#ifndef STATEACTION_H
#define STATEACTION_H

#include <QString>
#include <QDebug>
#include <QJsonObject>

class StateAction
{    

public:

    enum Direction{
        Left = -1,
        Rigth = 1
    };

    enum StateActionError{
        NoError = 0,
        ParseError = 1
    };

    static StateAction endAction();

    StateAction();
    StateAction(QString rendering);
    StateAction(bool write_val,Direction direction_val, QString next_state_val, bool end_action = false);

    bool getWrite_val() const;
    void setWrite_val(bool value);

    Direction getDirection_val() const;
    void setDirection_val(Direction value);

    QString getNext_state_val() const;
    void setNext_state_val(const QString &value);

    const QString toString();

    bool isEnd_action() const;
    void setEnd_action(bool value);

    StateActionError validateAction();

    QString getRendering() const;
    void setRendering(const QString &value);

    QJsonObject toJson();

    bool operator==(const StateAction &other);

    StateAction invertedAction();

private:
    QString rendering;

    bool end_action;
    bool write_val;
    Direction direction_val;
    QString next_state_val;
};

#endif // STATEACTION_H

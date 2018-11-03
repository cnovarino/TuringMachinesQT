#include "stateaction.h"


StateAction StateAction::endAction(){
    return StateAction(false,Direction::Left,"",true);
}

StateAction::StateAction(){
    this->write_val = false;
    this->direction_val = Direction::Left;
    this->next_state_val = "";
    this->end_action = false;
    this->rendering = "";
}

StateAction::StateAction(QString rendering){
    this->write_val = false;
    this->direction_val = Direction::Left;
    this->next_state_val = "";
    this->end_action = false;
    this->rendering = rendering;
}

StateAction::StateAction(bool write_val, StateAction::Direction direction_val, QString next_state_val, bool end_action){
    this->write_val = write_val;
    this->direction_val = direction_val;
    this->next_state_val = next_state_val.toLower();
    this->end_action = end_action;

    this->rendering = QString((write_val ? "1":"0")) + QString((direction_val == 1 ? ">" : "<")) + next_state_val.toLower();
}

bool StateAction::getWrite_val() const {
    return write_val;
}

void StateAction::setWrite_val(bool value) {
    this->write_val = value;
}

StateAction::Direction StateAction::getDirection_val() const {
    return direction_val;
}

void StateAction::setDirection_val(StateAction::Direction value){
    this->direction_val = value;
}

QString StateAction::getNext_state_val() const {
    return next_state_val.toLower();
}

void StateAction::setNext_state_val(const QString &value) {
    this->next_state_val = value.toLower();
}

const QString StateAction::toString() {
    if(!end_action)
        return rendering.toLower();
    else
        return "FIN";
}

bool StateAction::isEnd_action() const {
    return end_action;
}

void StateAction::setEnd_action(bool value) {
    this->end_action = value;
}

StateAction::StateActionError StateAction::validateAction(){

    if(rendering.toUpper() == "FIN"){
        this->end_action = true;
        this->rendering = "FIN";
        return StateActionError::NoError;
    }


    if(rendering.isEmpty() || rendering.length() <3)
        return StateActionError::ParseError;

    QChar write_char = rendering.at(0);

    if(write_char != "0" && write_char != "1")
        return StateActionError::ParseError;

    bool tmp_write_val = static_cast<bool>(write_char.digitValue());

    QChar direction_char = rendering.at(1);

    if(direction_char != "<" && direction_char != ">")
        return StateActionError::ParseError;

    Direction tmp_direction_val = (direction_char == "<") ? Direction::Left : Direction::Rigth;

    QString aux = rendering.toLower();
    QString tmp_next_val = aux.remove(0,2);

    this->write_val = tmp_write_val;
    this->direction_val = tmp_direction_val;
    this->next_state_val = tmp_next_val.toLower();
    this->end_action = false;

    return StateActionError::NoError;

}

QString StateAction::getRendering() const{
    return rendering;
}

void StateAction::setRendering(const QString &value){
    this->rendering = value.toLower();
}

QJsonObject StateAction::toJson(){
    QJsonObject result;
    if(isEnd_action())
        result.insert("rendering","FIN");
    else
        result.insert("rendering",rendering);

    return result;
}

bool StateAction::operator==(const StateAction &other)
{
    return this->rendering == other.getRendering();
}

StateAction StateAction::invertedAction()
{
    StateAction inverted;
    QString original_rendering = this->getRendering();

    if(original_rendering.at(1) == "<")
        original_rendering.replace(1,">");
    else
        original_rendering.replace(1,"<");

    inverted.setRendering(original_rendering);
    inverted.validateAction();

    return  inverted;
}

void StateAction::updateRender()
{
    if(isEnd_action()){
        rendering = "FIN";
        return;
    }

    rendering = "";
    rendering += getWrite_val() ? "1" : "0";
    rendering += getDirection_val() == Direction::Left ? "<" : ">";
    rendering += getNext_state_val();

    return;
}


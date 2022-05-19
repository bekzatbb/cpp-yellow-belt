#include "node.h"

using namespace std;

bool DateComparisonNode::Evaluate(const Date &date, const string &event) const {
    if (_cmp == Comparison::Less) {
        return date < _date;
    } else if (_cmp == Comparison::LessOrEqual) {
        return date <= _date;
    } else if (_cmp == Comparison::NotEqual) {
        return date != _date;
    } else if (_cmp == Comparison::Equal) {
        return date == _date;
    } else if (_cmp == Comparison::Greater) {
        return date > _date;
    } else if (_cmp == Comparison::GreaterOrEqual) {
        return date >= _date;
    }
}


bool EventComparisonNode::Evaluate(const Date &date, const string &event) const {
    if(_cmp == Comparison::Less){
        return event <  _value;
    } else if (_cmp == Comparison::LessOrEqual){
        return event <= _value;
    } else if(_cmp == Comparison::NotEqual){
        return event != _value;
    } else if(_cmp == Comparison::Equal){
        return event == _value;
    } else if (_cmp == Comparison::Greater){
        return event > _value;
    } else if (_cmp == Comparison::GreaterOrEqual){
        return event >= _value;
   }
}

bool LogicalOperationNode::Evaluate(const Date &date, const string &event) const {
    if(_logical_op == LogicalOperation::Or){
        return _left->Evaluate(date, event) || _right->Evaluate(date, event);
    } else if (_logical_op == LogicalOperation::And){
        return _left->Evaluate(date, event) && _right->Evaluate(date, event);
    }
}

bool EmptyNode::Evaluate(const Date &date, const string &event) const {
    return true;
}
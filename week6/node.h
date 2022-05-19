#pragma once

#include "date.h"

enum Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum LogicalOperation{
    And,
    Or
};

class Node{
public:
    virtual bool Evaluate(const Date &date, const string &event) const = 0;
};

class EmptyNode: public Node{
public:
    bool Evaluate(const Date &date, const string &event) const override ; // ????
};

class DateComparisonNode: public Node{
public:
    DateComparisonNode(Comparison comp, Date date):
                        _cmp(comp), _date(date){};
    bool Evaluate(const Date &date, const string &event) const override;

private:
    Comparison _cmp;
    Date _date;
};

class EventComparisonNode: public Node{
public:
    bool Evaluate(const Date &date, const string &event) const override;
    EventComparisonNode(Comparison cmp, const string& value):
                            _cmp(cmp),_value(value){};

private:
    Comparison _cmp;
    const string _value;
};

class LogicalOperationNode: public Node{
public:
    bool Evaluate(const Date &date, const string &event) const override;
    LogicalOperationNode(const LogicalOperation& logical_op,
                        const shared_ptr<Node> left,
                        const shared_ptr<Node> right):
                        _logical_op(logical_op), _left(left), _right(right){};

private:
    const LogicalOperation _logical_op;
    const shared_ptr<Node> _left;
    const shared_ptr<Node> _right;
};



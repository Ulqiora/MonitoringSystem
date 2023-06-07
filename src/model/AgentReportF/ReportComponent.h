#pragma once
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include "Observer.h"

class ReportComponent {
 public:
    ReportComponent(std::string namecomponent, ReportComponent* parent)
        : name_(namecomponent), parent_(parent) {}
    virtual void Accept(IReportObserver* visitor) = 0;
    std::string_view GetName(){return name_;}
    ReportComponent* GetParent(){return parent_;}
    virtual ~ReportComponent() = default;
 private:
    std::string name_;
    ReportComponent* parent_;
};

class ReportComposite : public ReportComponent {
 public:
    ReportComposite(std::string namecomponent, ReportComponent* parent)
        : ReportComponent(namecomponent, parent) {}
    void add(ReportComponent* component) {
        if (component != nullptr) components_.push_back(component);
    }
    size_t Size() { return components_.size(); }
    ReportComponent* GetNode(size_t i){return components_[i];}
    void Accept(IReportObserver* visitor) override {
        visitor->Visit(this);
    }
    virtual ~ReportComposite() = default;
 private:
    std::vector<ReportComponent*> components_;
};
class ReportValue : public ReportComponent {
 public:
    ReportValue(const std::string& nameMetric, double value, ReportComponent* parent)
        : ReportComponent(nameMetric, parent), value_(value) {}
    void updateValue(double value) { value_ = value; }
    virtual ~ReportValue() = default;
    void Accept(IReportObserver* visitor)override{
        visitor->Visit(this);
    }
 private:
    double value_;
};


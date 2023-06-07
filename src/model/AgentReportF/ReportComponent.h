#pragma once
#include <string>
#include <vector>

class ReportComponent{
    public:
    ReportComponent(std::string namecomponent):name_(namecomponent){}
    virtual bool add(ReportComponent* ) = 0;
    virtual bool updateValue(double value) = 0;
    virtual std::string getname() = 0;
    private:
    std::string name_;
};

class ReportComposite: public ReportComponent{
    public:
    ReportComposite(std::string namecomponent):ReportComponent(namecomponent){}
    bool add(ReportComponent* component) {
        components_.push_back(component);
        return true;
    }
    bool updateValue(double value) override {return false;};
    private:
    std::vector<ReportComponent*> components_;
    
};
class ReportValue: public ReportComponent{
    public:
    ReportValue(const std::string& nameMetric, double value): ReportComponent(nameMetric),value_(value){}
    bool add(ReportComponent* component) override { return false; }
    bool updateValue(double value) override {
        value_ = value;
        return true;
    }
   private:
    double value_;
};

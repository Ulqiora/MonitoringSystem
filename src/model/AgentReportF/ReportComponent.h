#pragma once
#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
// #include "Observer.h"

class ReportComponent {
 public:
    using FullReport = std::vector<std::pair<std::vector<std::string_view>,double&>>;
    ReportComponent(std::string namecomponent, ReportComponent* parent)
        : name_(namecomponent)
        , parent_(parent) 
        {}
    // virtual void Accept(IReportObserver* visitor) = 0;
    // virtual FullReport GetReport() = 0;
    std::string_view GetName(){return name_;}
    ReportComponent* GetParent(){return parent_;}
    virtual ~ReportComponent() = default;
 private:
    std::string name_;
    ReportComponent* parent_;
};

class ReportValue : public ReportComponent {
 public:
    ReportValue(const std::string& nameMetric, double value, ReportComponent* parent)
        : ReportComponent(nameMetric, parent), value_(value) {}
    void updateValue(double value) { value_ = value; }
    virtual ~ReportValue() = default;
    // void Accept(IReportObserver* visitor)override{
    //     visitor->Visit(this);
    // }
    double GetValue() { return value_; }

   private:
    double value_;
};

class ReportComposite : public ReportComponent {
 public:
    class Iterator {
        public:
        Iterator(ReportComponent* root):root_(root){
            ReportComposite* temp = dynamic_cast<ReportComposite*>(root);
            while (temp!=nullptr) {
                root = temp->components_.front();
                temp = dynamic_cast<ReportComposite*>(root);
            }
            cursor=root;
        }
        void First() {
            auto root = root_;
            auto temp = dynamic_cast<ReportComposite*>(root);
            while (temp!=nullptr) {
                root = temp->components_.front();
                temp = dynamic_cast<ReportComposite*>(root);
            }
            cursor=root;
        }
        void Next() {
            ReportComposite* parent = dynamic_cast<ReportComposite*>(cursor->GetParent());
            while(parent && parent->IsLastNode(cursor)){
                cursor = parent;
                parent = dynamic_cast<ReportComposite*>(cursor->GetParent());
            }
            if(!parent->IsLastNode(cursor)){
                ReportComponent* next = parent->Next(cursor);
                ReportComposite* temp = dynamic_cast<ReportComposite*>(next);
                while (temp!=nullptr) {
                    next = temp->components_.front();
                    temp = dynamic_cast<ReportComposite*>(next);
                }
                cursor=next;
            } else {
                cursor = parent;
            }
        }
        ReportComponent* end(){return nullptr;}
        std::pair<std::list<std::string_view>,double> operator*(){
            std::list<std::string_view> output;
            auto temp = cursor;
            while(temp->GetParent()!=nullptr){
                output.push_front(temp->GetName());
                temp=temp->GetParent();
            }
            return {output,dynamic_cast<ReportValue*>(cursor)->GetValue()};
        }
        private:
        ReportComponent* root_;
        ReportComponent* cursor;
    };

    ReportComposite(std::string namecomponent, ReportComponent* parent)
        : ReportComponent(namecomponent, parent) {}
    void add(ReportComponent* component) {
        if (component != nullptr) components_.push_back(component);
    }
    size_t Size() { return components_.size(); }
    ReportComponent* GetNode(size_t i){return components_[i];}
    // void Accept(IReportObserver* visitor) override {
    //     visitor->Visit(this);
    // }
    void GetReport(){

    }
    ReportComponent* GetFirstComponent(){return components_.front();}

    virtual ~ReportComposite() = default;
    ReportComponent* Next(ReportComponent* node) {
        auto temp1 = std::find_if(components_.begin(), components_.end(),
                                  [node](const ReportComponent* temp) {
                                      std::cout << (node == temp) << std::endl;
                                      return node == temp;
                                  });
        auto temp = temp1 - components_.begin();
        return components_[temp1 - components_.begin()];
    }

 private:
    bool IsLastNode(ReportComponent* node){
        return node == components_.back();
    }
    std::vector<ReportComponent*> components_;
};



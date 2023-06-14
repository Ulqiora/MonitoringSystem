#pragma once
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "MetricParameters.h"

class ReportComponent {
 public:
    ReportComponent(std::string namecomponent, ReportComponent* parent)
        : name_(namecomponent), parent_(parent) {}
    bool isLast() {
        auto parent = getParent();
        assert(parent), assert(parent->end() - parent->begin() > 0);
        return (*(parent->end() - 1)) == this;
    }
    bool isRoot() { return parent_ == nullptr; }
    std::string_view getName() { return name_; }
    ReportComponent* getParent() { return parent_; }

    virtual ~ReportComponent() = default;

 public:
    virtual bool empty() = 0;
    virtual bool isLeaf() = 0;
    virtual std::vector<ReportComponent*>::iterator end() = 0;
    virtual std::vector<ReportComponent*>::iterator begin() = 0;

 private:
    std::string name_;
    ReportComponent* parent_;
};

class ReportValue : public ReportComponent {
 public:
    ReportValue(const std::string& nameMetric, const MetricParameters& value, ReportComponent* parent)
        : ReportComponent(nameMetric, parent), info_(value) {}

    MetricParameters GetValue() { return info_; }
    void updateValue(double value) { info_.setValue(value); }

    virtual ~ReportValue() = default;

 public:
    virtual bool empty() override;
    virtual bool isLeaf() override { return true; }
    virtual std::vector<ReportComponent*>::iterator end() override;
    virtual std::vector<ReportComponent*>::iterator begin() override;

 private:
    MetricParameters info_;
};

class ReportComposite : public ReportComponent {
 public:
    class Iterator {
     public:
        Iterator(ReportComponent* root);
        void First();
        void Next();
        bool isEnd() { return cursor_ == root_->end(); }
        ReportComponent* end() { return nullptr; }
        std::pair<std::list<std::string_view>, MetricParameters> operator*();

     private:
        void cursorDropDown();
        ReportComponent* root_;
        std::vector<ReportComponent*>::iterator cursor_;
    };
    ReportComposite(std::string namecomponent, ReportComponent* parent);
    size_t Size();
    void add(ReportComponent* component);
    virtual ~ReportComposite() = default;

 public:
    bool empty() override { return components_.empty(); }
    virtual bool isLeaf() override { return false; }
    std::vector<ReportComponent*>::iterator end() override { return components_.end(); }
    std::vector<ReportComponent*>::iterator begin() override { return components_.begin(); }

 private:
    std::vector<ReportComponent*> components_;
};

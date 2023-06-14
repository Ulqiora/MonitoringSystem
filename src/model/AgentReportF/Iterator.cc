#include "ReportComponent.h"
ReportComposite::Iterator::Iterator(ReportComponent* root) : root_(root) { First(); }

void ReportComposite::Iterator::First() {
    cursor_ = root_->begin();
    cursorDropDown();
}
void ReportComposite::Iterator::Next() {
    if (!(*cursor_)->isLast()) {
        cursor_++;
        return;
    }else {
        auto cursor=*cursor_;
        while(!cursor->isRoot() && cursor->isLast()){
            cursor = cursor->getParent();
        }
        if (cursor->isRoot()) {
            cursor_ = (cursor)->end();
            return;
        }
        for(auto i = cursor->getParent()->begin();i!=cursor->getParent()->end();i++){
            if((*i)==cursor) cursor_=i+1;
        }
    }
}



std::pair<std::list<std::string_view>, MetricParameters> ReportComposite::Iterator::operator*() {
    std::list<std::string_view> output;
    auto temp = *cursor_;
    while (temp->getParent() != nullptr) {
        output.push_front(temp->getName());
        temp = temp->getParent();
    }
    return {output, dynamic_cast<ReportValue*>(*cursor_)->GetValue()};
}
void ReportComposite::Iterator::cursorDropDown() {
    while (!(*cursor_)->isLeaf()) {
        assert(!(*cursor_)->empty());
        cursor_ = (*cursor_)->begin();
    }
}
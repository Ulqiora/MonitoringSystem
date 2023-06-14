#include "ReportComponent.h"

ReportComposite::ReportComposite(std::string namecomponent, ReportComponent* parent)
    : ReportComponent(namecomponent, parent) {}
void ReportComposite::add(ReportComponent* component) {
    if (component != nullptr) components_.push_back(component);
}
size_t ReportComposite::Size() { return components_.size(); }
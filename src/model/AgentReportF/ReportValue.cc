#include "ReportComponent.h"

std::vector<ReportComponent*>::iterator ReportValue::begin() {
    throw std::invalid_argument("This node is leaf!");
}
std::vector<ReportComponent*>::iterator ReportValue::end() {
    throw std::invalid_argument("This node is leaf!");
}
bool ReportValue::empty() { throw std::invalid_argument("This node is leaf!"); }

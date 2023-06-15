#include "Builder.h"

#include "ReportComponent.h"

Builder::Builder(fs::path path) {
    std::ifstream file(path);
    if (!file.is_open()) throw std::invalid_argument("Incorrect file!");
    json filejson = json::parse(file);
    byJson(std::move(filejson));
}
void Builder::byJson(json&& filejson) {
    temp_ = new ReportComposite("title", nullptr);
    for (auto& item : filejson.items()) {
        if (item.value().is_primitive()) {
            if (item.key() == "name") {
                info_.name_ = item.value();
            } else if (item.key() == "type") {
                info_.typeAgent_ = item.value();
            } else if (item.key() == "interval") {
                info_.time_seconds_ = item.value();
            } else if (item.key() == "enabled") {
                info_.enabled_ = item.value();
            }
        } else {
            byJson(std::move(item.value()), temp_);
        }
    }
}

void Builder::byJson(json&& filejson, ReportComposite* curNode) {
    std::list<ReportComponent*> currentNodes;
    if (filejson.is_array()) {
        for (auto& item : filejson.items()) {
            MetricParameters metric{item.value()["comparison"], item.value()["critical_value"], 0};
            currentNodes.push_back(new ReportValue(item.value()["name"], metric, curNode));
        }
        for (auto node : currentNodes) {
            curNode->add(node);
        }
    }
}
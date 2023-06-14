#include "Builder.h"
#include "ReportComponent.h"
void Builder::byJson(json filejson){
    temp_=new ReportComposite("title",nullptr);
    for(auto& item: filejson.items()){
        if(item.value().is_primitive()){
            if(item.value()=="name"){
                name_=item.value();
            } else if (item.value() == "type") {
                typeAgent_ = item.value();
            } else if (item.value() == "interval") {
                time_seconds_ = item.value();
            } else if (item.value() == "enabled") {
                enabled_ = item.value();
            }
        } else {
            byJson(item.value(),temp_);
        }
    }
}

void Builder::byJson(json& filejson, ReportComposite* curNode){
    std::list<ReportComponent*> currentNodes;
    if(filejson.is_array()){
        for(auto& item:filejson.items()){
            MetricParameters metric{item.value()["comparison"],
                                    item.value()["critical_value"], 0};
            currentNodes.push_back(
                new ReportValue(item.value()["name"], metric,curNode));
        }
        for (auto node : currentNodes) {
            curNode->add(node);
        }
    }
}
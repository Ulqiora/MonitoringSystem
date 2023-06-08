#include "Observer.h"
#include "ReportComponent.h"
#include <algorithm>
void IReportObserverGetWay::Visit(ReportComposite* component){
    if (component->GetParent() == nullptr) {
        for (size_t i = 0; i < component->Size(); i++) {
            result.push_back({{component->GetNode(i)->GetName()}, 0});
        }
    } else {
        auto point=std::find_if(result.begin(),result.end(),[](const std::pair<std::vector<std::string_view>,double>& a){
            a.first.
        })
    }
}

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <glog/logging.h>
//#include <gtest/gtest.h>

#include "croutetable.h"

class Entity {
public:
    int data;
};

int main(int ac, char **av) {
    google::InitGoogleLogging("app");
    FLAGS_logtostderr = 1;
    FLAGS_minloglevel = 0;

    using std::cout;
    using std::endl;
    using std::auto_ptr;
    Entity * acc = new Entity;
    CRouteTable* p = new CRouteTable;

    LOG(INFO) << "adding " << p;
    const char * keyOne = "111";
    p->AddIndex("111", "", (Handle&) acc);
    p->AddIndex("121", "", (Handle&) acc);
    p->AddIndex("1qq", "", (Handle&) acc);
    p->AddIndex("133", "", (Handle&) acc);
    LOG(INFO) << "add index finish";

    Entity * pSearch = NULL;
    if (p->FullMatchSearch(keyOne, "", (Handle&) pSearch)){
        LOG(INFO) << "searched " << pSearch;
    }else {
        LOG(INFO) << "this is huge, you better check it out....";
    }

    LOG(INFO) << "bye";
    return 0;
}

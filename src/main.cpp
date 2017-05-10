/*
 MIT License

 Copyright (c) 2017 Morya

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <glog/logging.h>
// #include <gtest/gtest.h>

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

    Entity *pEntity = new Entity;
    std::unique_ptr<CRouteTable> p(new CRouteTable);
    std::unique_ptr<Entity> pPtrEntity(pEntity);
    LOG(INFO) << "adding " << p;

    p->AddIndex("111", "123", (Handle &) pEntity);
    p->AddIndex("121", "123", (Handle &) pEntity);
    p->AddIndex("1qq", "123", (Handle &) pEntity);
    p->AddIndex("133", "123", (Handle &) pEntity);

    LOG(INFO) << "add index finish";
    Handle pSearch = NULL;

    if (p->FullMatchSearch("111", "123", pSearch)) {
        LOG(INFO) << "searched " << pSearch;
    } else {
        LOG(INFO) << "this is huge, you better check it out....";
    }

    LOG(INFO) << "bye";
    return 0;
}

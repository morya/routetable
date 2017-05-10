#include "croutetable.h"

#include <stddef.h>
#include <ctype.h>
#include <cstring>

#include <glog/logging.h>

using namespace std;

int AddrNode::chidrenCount() {
    int count = 0;

    for (int i = 0; i < MAX_NODE_COUNT; i++) {
        if (NULL != children[i]) {
            count++;
        }
    }

    return count;
}

CRouteTable::CRouteTable() {
    m_nodeCount = 0;
    m_head = new AddrNode;
}

CRouteTable::~CRouteTable() {
    if (m_head) {
        delete m_head;
        m_head = NULL;
    }
}

bool CRouteTable::AddIndex(PCChar firstLevel, PCChar secondLevel, const Handle h) {
    PNode p = NULL;
    CRouteTable *pLevel2Instance = NULL;
    LOG(INFO)<< "before search";
    searchAndBuildTree(firstLevel, p);

    if (p->handle) {
        LOG(INFO)<< "has second level, wonderful";
        pLevel2Instance = (CRouteTable *)(p->handle);
    } else {
        LOG(INFO) << "no second level, building one";
        pLevel2Instance = new CRouteTable;
    }

    if (!pLevel2Instance) {
        return false;
    }

    p->handle = pLevel2Instance;
    Handle old = NULL;
    pLevel2Instance->replaceItem(secondLevel, h, old);

    if (old) {
        LOG(INFO)<< "old instance " << old;
    }

    return true;
}

bool CRouteTable::DelIndex(PCChar firstLevel, PCChar secondLevel) {
    PNode p = NULL;
    CRouteTable *pLevel2Instance = NULL;
    searchTree(firstLevel, p);

    if (NULL == p || NULL == p->handle) {
        return false;
    }

    pLevel2Instance = static_cast<CRouteTable *>(p->handle);

    if (pLevel2Instance->DelIndex(secondLevel)) {
        return true;
    }

    // TODO: release child-nodes, free memory, for both level1 and level2
    return false;
}

// re-cursive match
bool CRouteTable::BestSearch(PCChar firstLevel, PCChar secondLevel, Handle &h) {
    return false;
}

bool CRouteTable::FullMatchSearch(PCChar firstLevel, PCChar secondLevel, Handle &h) {
    PNode p = NULL;
    CRouteTable *pLevel2Instance = NULL;
    searchTree(firstLevel, p);

    if (NULL == p || NULL == p->handle) {
        return false;
    }

    pLevel2Instance = (CRouteTable *) (p->handle);
    PNode pSecond = NULL;

    if (pLevel2Instance->searchTree(secondLevel, pSecond)) {
        h = pSecond->handle;
        return true;
    }

    return false;
}

int CRouteTable::getCount() {
    return m_nodeCount;
}

PNode CRouteTable::NewNode() {
    PNode pNode = new AddrNode;
    pNode->parent = NULL;
    pNode->handle = NULL;
    memset(pNode->children, 0, sizeof(pNode->children));
    return pNode;
}

char CRouteTable::getRouteChar(int arrayIndex) {
    if (arrayIndex <= 0 || arrayIndex >= MAX_NODE_COUNT) {
        return '*';
    }

    if (arrayIndex > 0 && arrayIndex < 10) {
        return arrayIndex + '0';
    }

    return arrayIndex - 10 + 'A';
}

int CRouteTable::getArrayIndex(char key) {
    key = toupper(key);

    if ('0' <= key && key <= '9') {
        return key - '0';
    } else if ('A' <= key && key <= 'Z') {
        return key - 'A' + 10;
    }

    // default one
    return MAX_NODE_COUNT - 1;
}

bool CRouteTable::replaceItem(PCChar code, Handle h, Handle &old) {
    PNode p = NULL;
    searchAndBuildTree(code, p);

    if (!p->handle) {
        // replace old
        old = p->handle;
        p->handle = h;
        return true;
    }

    // adding new
    old = NULL;
    p->handle = h;
    return false;
}

bool CRouteTable::DelIndex(PCChar oneLevel) {
    PNode p = NULL;

    if (!searchTree(oneLevel, p)) {
        LOG(INFO)<< "deleting " << oneLevel << " failed.";
        return false;
    }

    PNode parent = p->parent;

    if (parent) {
        int strPos = strlen(oneLevel) - 1;

        if (p->chidrenCount() == 0) {
            // leaf node
            parent->children[getArrayIndex(oneLevel[strPos])] = NULL;
            p->handle = NULL;
            delete p;
            m_nodeCount--;
        }
    } else {
        // this is root
        p->handle = NULL;
    }

    return true;
}

bool CRouteTable::searchTree(PCChar addr, PNode &node) {
    PNode p = m_head;
    PCChar pAddr = addr;

    while (*pAddr) {
        LOG(INFO)<<"pAddr = " << *pAddr;
        int nodeIdx = getArrayIndex(*pAddr);

        if (p->children[nodeIdx]) {
            p = p->children[nodeIdx];
        } else {
            return false;
        }
        pAddr++;
    }

    node = p;
    return true;
}

bool CRouteTable::searchAndBuildTree(PCChar code, PNode &node) {
    int i = 0;
    int nodeIdx = 0;
    int len = strlen(code);
    PNode p = m_head;

    while (i < len) {
        nodeIdx = getArrayIndex(code[i]);

        if (p->children[nodeIdx]) {
            p = p->children[nodeIdx];
            i++;
        } else {
            for (; i < len; i++) {
                m_nodeCount++;
                PNode tmpNode = NewNode();
                tmpNode->parent = p;
                nodeIdx = getArrayIndex(code[i]);
                p->children[nodeIdx] = tmpNode;
                p = tmpNode;
            }
        }
    }

    node = p;
    return true;
}


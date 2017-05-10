#ifndef CROUTETABLE_H_
#define CROUTETABLE_H_

#include <stdint.h>

// 10: 0-9
// 26: A-Z
// 1: anything else
const int MAX_NODE_COUNT = (10 + 26 + 1);

typedef void *Handle;
typedef const char *PCChar;
typedef struct AddrNode *PNode;

struct AddrNode {
    Handle      handle;
    AddrNode    *parent;
    AddrNode    *children[MAX_NODE_COUNT];

    int chidrenCount();
};

class CRouteTable {
    public:
        CRouteTable();
        virtual ~CRouteTable();

        // 双层搜索函数
        bool AddIndex(PCChar firstLevel, PCChar secondLevel, const Handle h);
        bool DelIndex(PCChar firstLevel, PCChar secondLevel);
        bool DelIndex(PCChar oneLevel);
        bool BestSearch(PCChar firstLevel, PCChar secondLevel, Handle &h);
        bool FullMatchSearch(PCChar firstLevel, PCChar secondLevel, Handle &h);

    protected:
        // helper functions
        PNode NewNode();
        char getRouteChar(int arrayIndex);
        int getArrayIndex(char key);
        int getCount();

        // 单层操作函数
        bool replaceItem(PCChar code, Handle h, Handle &old);
        bool searchTree(PCChar code, PNode &node);
        bool searchAndBuildTree(PCChar code, PNode &node);

        int m_nodeCount;
        AddrNode *m_head;
};


template <typename VALUE>
class CPartricia {
public:
    CPartricia(){}
};

#endif /* CROUTETABLE_H_ */

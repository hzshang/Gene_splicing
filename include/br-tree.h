#ifndef BR_TREE_H
#define BR_TREE_H
#define BLACK 1
#define RED 0


#define KEY_TYPE void*

struct _Node{
    KEY_TYPE key;
    struct _Node* p;
    struct _Node* left;
    struct _Node* right;
    int color;
};

typedef struct _Node* Node;


struct BR_Tree{
    Node root;
    Node end;
    int (*cmp)(KEY_TYPE,KEY_TYPE);
};

typedef struct BR_Tree BR_Tree;


static void left_rotate(BR_Tree *,Node);
static void right_rotate(BR_Tree *,Node);
static void trans_parent(BR_Tree *,Node,Node);


static void fixup_insert_node(BR_Tree *,Node);
static void fixup_delete_node(BR_Tree *,Node);

static int insert_node(BR_Tree *,Node);
static void delete_node(BR_Tree *,Node);
static Node tree_min(BR_Tree*, Node);


void init_tree(BR_Tree*,int (*cmp)(KEY_TYPE,KEY_TYPE));
int insert_key(BR_Tree *,KEY_TYPE);
int delete_key(BR_Tree *tree, KEY_TYPE key);

KEY_TYPE key_exist(BR_Tree *tree,KEY_TYPE key);

#endif

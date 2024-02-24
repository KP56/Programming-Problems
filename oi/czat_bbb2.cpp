#include <bits/stdc++.h>

#define MAX_CHAR 27

using namespace std;

struct SuffixTreeNode
{
    struct SuffixTreeNode *children[MAX_CHAR];

    // pointer to other node via suffix link
    struct SuffixTreeNode *suffixLink;

    /*(start, end) interval specifies the edge, by which the
    node is connected to its parent node. Each edge will
    connect two nodes, one parent and one child, and
    (start, end) interval of a given edge will be stored
    in the child node. Lets say there are two nods A and B
    connected by an edge with indices (5, 8) then this
    indices (5, 8) will be stored in node B. */
    int start;
    int *end;

    // leaves under a tree node
    int leaves_under = -1;

    /*for leaf nodes, it stores the index of suffix for
    the path from root to leaf*/
    int suffixIndex;
};

typedef struct SuffixTreeNode Node;

string text;       // Input string
Node *root = NULL; // Pointer to root node

struct base_information {
    /*lastNewNode will point to newly created internal node,
    waiting for it's suffix link to be set, which might get
    a new suffix link (other than root) in next extension of
    same phase. lastNewNode will be set to NULL when last
    newly created internal node (if there is any) got it's
    suffix link reset to new internal node created in next
    extension of same phase. */
    Node *lastNewNode = NULL;
    Node *activeNode = NULL;
    int counter = 0;

    /*activeEdge is represented as input string character
    index (not the character itself)*/
    int activeEdge = -1;
    int activeLength = 0;

    // remainingSuffixcount tells how many suffixes yet to
    // be added in tree
    int remainingSuffixcount = 0;
    int leafEnd = -1;
    int *rootEnd = NULL;
    int *splitEnd = NULL;
    int tree_size = -1; // Length of input string
};

vector<Node*> to_remove;
vector<tuple<Node*,int,Node*>> to_remove_reference;
vector<pair<Node*,Node*>> to_revert_suffix_links;

base_information past_tree_info;
base_information tree_info;

Node *newNode(int start, int *end)
{
    tree_info.counter++;
    Node *node = (Node *)malloc(sizeof(Node));
    int i;
    for (i = 0; i < MAX_CHAR; i++)
        node->children[i] = NULL;

    /*For root node, suffixLink will be set to NULL
    For internal nodes, suffixLink will be set to root
    by default in current extension and may change in
    next extension*/
    node->suffixLink = root;
    node->start = start;
    node->end = end;

    /*suffixIndex will be set to -1 by default and
    actual suffix index will be set later for leaves
    at the end of all phases*/
    node->suffixIndex = -1;
    return node;
}

int edgeLength(Node *n)
{
    return *(n->end) - (n->start) + 1;
}

int walkDown(Node *currNode)
{
    /*activePoint change for walk down (APCFWD) using
    Skip/counter Trick (Trick 1). If activeLength is greater
    than current edge length, set next internal node as
    activeNode and adjust activeEdge and activeLength
    accordingly to represent same activePoint*/
    if (tree_info.activeLength >= edgeLength(currNode))
    {
        tree_info.activeEdge =
            (int)text[tree_info.activeEdge + edgeLength(currNode)] - (int)'a';
        tree_info.activeLength -= edgeLength(currNode);
        tree_info.activeNode = currNode;
        return 1;
    }
    return 0;
}

void extendSuffixTree(int pos)
{
    past_tree_info = tree_info;
    to_remove = vector<Node*>();
    to_remove_reference = vector<tuple<Node*,int,Node*>>();
    to_revert_suffix_links = vector<pair<Node*,Node*>>();

    /*Extension Rule 1, this takes care of extending all
    leaves created so far in tree*/
    tree_info.leafEnd = pos;

    /*Increment remainingSuffixcount indicating that a
    new suffix added to the list of suffixes yet to be
    added in tree*/
    tree_info.remainingSuffixcount++;

    /*set lastNewNode to NULL while starting a new phase,
    indicating there is no internal node waiting for
    it's suffix link reset in current phase*/
    tree_info.lastNewNode = NULL;

    // Add all suffixes (yet to be added) one by one in tree
    while (tree_info.remainingSuffixcount > 0)
    {

        if (tree_info.activeLength == 0)
        {
            tree_info.activeEdge = (int)text[pos] - (int)'a';
        }
        // There is no outgoing edge starting with
        // activeEdge from activeNode
        if (tree_info.activeNode->children[tree_info.activeEdge] == NULL)
        {
            // Extension Rule 2 (A new leaf edge gets created)
            to_remove_reference.push_back({tree_info.activeNode,tree_info.activeEdge,tree_info.activeNode->children[tree_info.activeEdge]});
            tree_info.activeNode->children[tree_info.activeEdge] =
                newNode(pos, &tree_info.leafEnd);
            to_remove.push_back(tree_info.activeNode->children[tree_info.activeEdge]);

            /*A new leaf edge is created in above line starting
            from an existing node (the current activeNode), and
            if there is any internal node waiting for it's suffix
            link get reset, point the suffix link from that last
            internal node to current activeNode. Then set lastNewNode
            to NULL indicating no more node waiting for suffix link
            reset.*/
            if (tree_info.lastNewNode != NULL)
            {
                to_revert_suffix_links.push_back({tree_info.lastNewNode,tree_info.lastNewNode->suffixLink});
                tree_info.lastNewNode->suffixLink = tree_info.activeNode;
                tree_info.lastNewNode = NULL;
            }
        }
        // There is an outgoing edge starting with activeEdge
        // from activeNode
        else
        {
            // Get the next node at the end of edge starting
            // with activeEdge
            Node *next = tree_info.activeNode->children[tree_info.activeEdge];
            if (walkDown(next)) // Do walkdown
            {
                // Start from next node (the new activeNode)
                continue;
            }
            /*Extension Rule 3 (current character being processed
            is already on the edge)*/
            if (text[next->start + tree_info.activeLength] == text[pos])
            {
                // If a newly created node waiting for it's
                // suffix link to be set, then set suffix link
                // of that waiting node to current active node
                if (tree_info.lastNewNode != NULL && tree_info.activeNode != root)
                {
                    to_revert_suffix_links.push_back({tree_info.lastNewNode,tree_info.lastNewNode->suffixLink});
                    tree_info.lastNewNode->suffixLink = tree_info.activeNode;
                    tree_info.lastNewNode = NULL;
                }

                tree_info.activeLength++;
                /*STOP all further processing in this phase
                and move on to next phase*/
                break;
            }

            /*We will be here when activePoint is in middle of
            the edge being traversed and current character
            being processed is not on the edge (we fall off
            the tree). In this case, we add a new internal node
            and a new leaf edge going out of that new node. This
            is Extension Rule 2, where a new leaf edge and a new
            internal node get created*/
            tree_info.splitEnd = (int *)malloc(sizeof(int));
            *tree_info.splitEnd = next->start + tree_info.activeLength - 1;

            // New internal node
            Node *split = newNode(next->start, tree_info.splitEnd);
            to_remove.push_back(split);
            to_remove_reference.push_back({tree_info.activeNode,tree_info.activeEdge,tree_info.activeNode->children[tree_info.activeEdge]});
            tree_info.activeNode->children[tree_info.activeEdge] = split;

            // New leaf coming out of new internal node
            to_remove_reference.push_back({split,(int)text[pos] - (int)'a',split->children[(int)text[pos] - (int)'a']});
            split->children[(int)text[pos] - (int)'a'] = newNode(pos, &tree_info.leafEnd);
            to_remove.push_back(split->children[(int)text[pos] - (int)'a']);
            next->start += tree_info.activeLength;
            to_remove_reference.push_back({split,tree_info.activeEdge,split->children[tree_info.activeEdge]});
            split->children[tree_info.activeEdge] = next;

            /*We got a new internal node here. If there is any
            internal node created in last extensions of same
            phase which is still waiting for it's suffix link
            reset, do it now.*/
            if (tree_info.lastNewNode != NULL)
            {
                /*suffixLink of lastNewNode points to current newly
                created internal node*/
                to_revert_suffix_links.push_back({tree_info.lastNewNode,tree_info.lastNewNode->suffixLink});
                tree_info.lastNewNode->suffixLink = split;
            }

            /*Make the current newly created internal node waiting
            for it's suffix link reset (which is pointing to root
            at present). If we come across any other internal node
            (existing or newly created) in next extension of same
            phase, when a new leaf edge gets added (i.e. when
            Extension Rule 2 applies is any of the next extension
            of same phase) at that point, suffixLink of this node
            will point to that internal node.*/
            tree_info.lastNewNode = split;
        }

        /* One suffix got added in tree, decrement the counter of
        suffixes yet to be added.*/
        tree_info.remainingSuffixcount--;
        if (tree_info.activeNode == root && tree_info.activeLength > 0)
        {
            tree_info.activeLength--;
            tree_info.activeEdge = (int)text[pos - tree_info.remainingSuffixcount + 1] - (int)'a';
        }

        else if (tree_info.activeNode != root)
        {
            to_revert_suffix_links.push_back({tree_info.activeNode,tree_info.activeNode->suffixLink});
            tree_info.activeNode = tree_info.activeNode->suffixLink;
        }
    }
}

void print(int i, int j)
{
    int k;
    for (k = i; k <= j; k++)
        printf("%c", text[k]);
}

// Print the suffix tree as well along with setting suffix index
// So tree will be printed in DFS manner
// Each edge along with it's suffix index will be printed
void setSuffixIndexByDFS(Node *n, int labelHeight)
{
    if (n == NULL)
        return;

    if (n->start != -1) // A non-root node
    {
        // Print the label on edge from parent to current node
        print(n->start, *(n->end));
    }
    int leaf = 1;
    int i;
    for (i = 0; i < MAX_CHAR; i++)
    {
        if (n->children[i] != NULL)
        {
            if (leaf == 1 && n->start != -1)
                printf(" [%d]\n", n->suffixIndex);

            // Current node is not a leaf as it has outgoing
            // edges from it.
            leaf = 0;
            setSuffixIndexByDFS(n->children[i],
                                labelHeight + edgeLength(n->children[i]));
        }
    }
    if (leaf == 1)
    {
        n->suffixIndex = tree_info.tree_size - labelHeight;
        printf(" [%d]\n", n->suffixIndex);
    }
}

void freeSuffixTreeByPostOrder(Node *n)
{
    if (n == NULL)
        return;
    int i;
    for (i = 0; i < MAX_CHAR; i++)
    {
        if (n->children[i] != NULL)
        {
            freeSuffixTreeByPostOrder(n->children[i]);
        }
    }
    if (n->suffixIndex == -1)
        free(n->end);
    free(n);
}

/*Build the suffix tree and print the edge labels along with
suffixIndex. suffixIndex for leaf edges will be >= 0 and
for non-leaf edges will be -1*/
void buildSuffixTree()
{
    tree_info.tree_size = text.size();
    tree_info.rootEnd = (int *)malloc(sizeof(int));
    *tree_info.rootEnd = -1;

    /*Root is a special node with start and end indices as -1,
    as it has no parent from where an edge comes to root*/
    root = newNode(-1, tree_info.rootEnd);

    tree_info.activeNode = root; // First activeNode will be root
    for (int i = 0; i < tree_info.tree_size; i++) {
        extendSuffixTree(i);
    }
    int labelHeight = 0;
    setSuffixIndexByDFS(root, labelHeight);
}

// funkcja przyporządkowuje ilość liści wszystkim wierzchołkom drzewa
int dfs_find_leaves(Node *current) {
    int leaves_under = 0;

    bool is_leaf = true;    
    for (Node *node : current->children) {
        if (node != NULL) {
            leaves_under += dfs_find_leaves(node);
            is_leaf = false;
        }
    }

    if (is_leaf) {
        return current->leaves_under = 1;
    }

    return current->leaves_under = leaves_under;
}

void find_leaves_under() {
    dfs_find_leaves(root);
}

// zakładając, że napis jest podciągiem, funkcja odnajdzie wierzchołek, krawędź oraz indeks literki, które reprezentują dany napis
tuple<Node*,char,int> find_string(string s) {
    Node* current = root;
    Node* prev = NULL;
    int current_letter = 0;
    int prev_current_letter = -1;

    while (current_letter < s.length()) {
        prev = current;
        prev_current_letter = current_letter;

        current = current->children[s[current_letter] - 'a'];
        current_letter += *current->end - current->start + 1;
    }

    int letter_idx = s.length() - prev_current_letter - 1;
        
    return {prev,text[current->start],letter_idx};
}

char character_to_generate(Node* node, char vertex, int letter_idx) {
    Node* next = node->children[vertex - 'a'];

    // Podejmujemy decyzję dotyczącą kolejnej literki do generacji
    char to_generate;
    if (*next->end - next->start != letter_idx) {
        // Jeżeli mamy tylko jedną możliwą literkę i nie trzeba podejmować żadnej decyzji
        to_generate = text[next->start + letter_idx + 1];
    } else {
        Node* best_node;
        int current_leaves = 0;
        for (Node* to_choose_from : next->children) {
            if (to_choose_from != NULL) {
                if (to_choose_from->leaves_under > current_leaves) {
                    current_leaves = to_choose_from->leaves_under;
                    best_node = to_choose_from;
                }
            }
        }

        if (current_leaves == 0) {
            to_generate = 'a';
        } else {
            to_generate = text[best_node->start];
        }
    }

    if (to_generate == '{') {
        return 'a';
    }

    return to_generate;
}

void rollback() {
    tree_info = past_tree_info;

    for (auto i : to_revert_suffix_links) {
        i.first->suffixLink = i.second;
    }

    for (auto i : to_remove_reference) {
        Node* node1 = get<0>(i);
        int idx = get<1>(i);
        Node* node2 = get<2>(i);

        node1->children[idx] = node2;
    }

    for (auto i : to_remove) {
        // Może w przyszłości dodam czyszczenie, na razie jestem zbyt leniwy, by upewnić się, że wszystko dobrze poszło
    }
}

void add_character(char c) {
    rollback();
    text.pop_back();

    text += string(1,c);
    extendSuffixTree(text.size() - 1);

    text += "{";
    extendSuffixTree(text.size() - 1);
}

tuple<Node*,char,int> step_forward(Node* node, char vertex, int letter_idx) {
    Node* node2 = node->children[vertex-'a'];
    Node* current = node->suffixLink;

    char to_generate = character_to_generate(node, vertex, letter_idx);

    Node* prev = NULL;
    int current_letter = 0;
    int prev_current_letter;
    char current_vertex;
    while (current_letter <= letter_idx) {
        prev = current;
        current_vertex = text[node2->start + current_letter];
        current = current->children[current_vertex-'a'];

        prev_current_letter = current_letter;
        current_letter += *current->end - current->start + 1;
    }

    add_character(to_generate);

    int new_letter_idx;
    if (letter_idx - prev_current_letter == *current->end - current->start) {
        if (current->children[to_generate-'a'] == NULL) {
            int test = 0;
        }

        new_letter_idx = 0;
        prev = current;
        current_vertex = to_generate;
        current = current->children[current_vertex-'a'];
    } else {
        if (text[current->start + letter_idx - prev_current_letter + 1] != to_generate) {
            int test = 0;
        }

        new_letter_idx = letter_idx - prev_current_letter + 1;
    }

    return {prev,current_vertex,new_letter_idx};
}

int main() {
    text = "abbca{";
    buildSuffixTree();
    printf("Number of nodes in suffix tree are %d\n", tree_info.counter);
    find_leaves_under();
    
    /*tuple<Node*,char,int> result2 = find_string("bc");
    step_forward(get<0>(result2),get<1>(result2),get<2>(result2));*/

    //add_character('a');

    freeSuffixTreeByPostOrder(root);
}

#include <bits/stdc++.h>

using namespace std;

class SuffixNode
{
public:
    int depth, begin, end;
    SuffixNode *children[27];
    SuffixNode *parent, *suffixLink;

    SuffixNode(int begin, int end, int depth, SuffixNode *parent)
    {
        this->begin = begin;
        this->end = end;
        this->parent = parent;
        this->depth = depth;
    }

    bool contains(int d)
    {
        return depth <= d && d < depth + (end - begin);
    }
};

string alphabet;
int alphabetSize;

struct BuildInfo {
    SuffixNode *cn;
    SuffixNode *needsSuffixLink;
    int lastRule;
    int j;
};

struct SuffixTree
{
    BuildInfo build_info;
    BuildInfo past_info;

    SuffixNode *root;
    vector<int> a;
    int n;

    void buildOnLine(int i)
    {
        past_info = build_info;
        int cur = a[i + 1];

        for (; build_info.j <= i + 1; build_info.j++)
        {
            int curDepth = i + 1 - build_info.j;
            if (build_info.lastRule != 3)
            {
                if (build_info.cn->suffixLink != NULL)
                    build_info.cn = build_info.cn->suffixLink;
                else
                    build_info.cn = build_info.cn->parent->suffixLink;

                int k = build_info.j + build_info.cn->depth;

                while (curDepth > 0 && !build_info.cn->contains(curDepth - 1))
                {
                    k += build_info.cn->end - build_info.cn->begin;

                    build_info.cn = build_info.cn->children[a[k]];
                }
            }

            if (!build_info.cn->contains(curDepth))
            {

                if (build_info.needsSuffixLink != NULL)
                {
                    build_info.needsSuffixLink->suffixLink = build_info.cn;
                    build_info.needsSuffixLink = NULL;
                }

                if (build_info.cn->children[cur] == NULL)
                {
                    build_info.cn->children[cur] = new SuffixNode(i + 1, n, curDepth, build_info.cn);
                    build_info.lastRule = 2;
                }

                else
                {
                    build_info.cn = build_info.cn->children[cur];
                    build_info.lastRule = 3;
                    break;
                }
            }
            else
            {
                int end = build_info.cn->begin + curDepth - build_info.cn->depth;
                if (a[end] != cur)
                {
                    SuffixNode *newn = new SuffixNode(build_info.cn->begin, end, build_info.cn->depth, build_info.cn->parent);
                    newn->children[cur] = new SuffixNode(i + 1, n, curDepth, newn);
                    newn->children[a[end]] = build_info.cn;
                    build_info.cn->parent->children[a[build_info.cn->begin]] = newn;
                    if (build_info.needsSuffixLink != NULL)
                        build_info.needsSuffixLink->suffixLink = newn;

                    build_info.cn->begin = end;
                    build_info.cn->depth = curDepth;
                    build_info.cn->parent = newn;
                    build_info.cn = build_info.needsSuffixLink = newn;

                    build_info.lastRule = 2;
                }
                else if (build_info.cn->end != n || (build_info.cn->begin - build_info.cn->depth) < build_info.j)
                {
                    build_info.lastRule = 3;

                    break;
                }
                else
                    build_info.lastRule = 1;
            }
        }
    }

    void rollback() {
        
    }

    SuffixNode *buildSuffixTree(string s)
    {
        n = s.length();
        a = vector<int>(n);

        for (int i = 0; i < n; i++)
        {
            a[i] = alphabet.find(s.at(i));
        }

        root = new SuffixNode(0, 0, 0, NULL);
        build_info.cn = root;
        root->suffixLink = root;
        build_info.needsSuffixLink = NULL;

        build_info.lastRule = 0;
        build_info.j = 0;

        for (int i = -1; i < n - 1; i++)
        {
            buildOnLine(i);
        }

        root->suffixLink = NULL;

        return root;
    }
};

int main()
{
    alphabet = "abcdefghijklmnopqrstuvwxyz$";
    alphabetSize = alphabet.length();

    string s = "abbca$";
    SuffixTree st;
    SuffixNode *root = st.buildSuffixTree(s);
    int test = 0;
}

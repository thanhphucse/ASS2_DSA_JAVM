#ifndef __STACK_FRAME_H__
#define __STACK_FRAME_H__

#include <string>
#include <stack>

/*
StackFrame declaration
*/
struct data
{
    int type;
    float val;
};
typedef struct data DATA;

class StackFrame
{
public:
    class localVar;

private:
    int opStackMaxSize;    // max size of operand stack
    int localVarSpaceSize; // size of local variable array
    std::stack<DATA> opstack;
    localVar *LV = new localVar();
public:
    /*
    Constructor of StackFrame
    */
    StackFrame();
    ~StackFrame()
    {
        this->LV->~localVar();
    }
    class localVar
    {
    public:
        class node;

    private:
        node *root;
        int count;
        friend class StackFrame;

    public:
        localVar() : root(nullptr), count(0) {}
        // ~localVar();
        // node *rotageRight(node *root);
        // node *rotageLeft(node *root);
        // node *insertAVL(node *root, node *pnew, bool &taller);
        // node *leftBlances(node *root, bool &taller);
        // node *rightBlances(node *root, bool &taller);
        // void insert(DATA data, string key);
        int getHeightRec(node *root)
        {
            if (root == NULL)
                return 0;
            int lh = this->getHeightRec(root->left);
            int rh = this->getHeightRec(root->right);
            return (lh > rh ? lh : rh) + 1;
        }
        node *rotageLeft(node *root)
        {
            node *temp = root->right;
            root->right = temp->left;
            temp->left = root;
            temp->balance = this->getHeightRec(temp->left) - this->getHeightRec(temp->right);
            root->balance = this->getHeightRec(root->left) - this->getHeightRec(root->right);
            return temp;
        }
        node *rotageRight(node *root)
        {
            node *temp = root->left;
            root->left = temp->right;
            temp->right = root;
            temp->balance = this->getHeightRec(temp->left) - this->getHeightRec(temp->right);
            root->balance = this->getHeightRec(root->left) - this->getHeightRec(root->right);
            return temp;
        }
        node *leftBlances(node *root, bool &taller)
        {
            node *leftTree = root->left;
            // case 1: left of left. xoay don
            if (leftTree->balance == -1)
            {
                root = rotageRight(root);
                root->balance = 0;
                leftTree->balance = 0;
                taller = false;
            }
            else // case 2: right of left. xoay kep
            {
                node *rightTree = leftTree->right;
                if (rightTree->balance == -1)
                {
                    root->balance = 1;
                    leftTree->balance = 0;
                }
                else if (rightTree->balance == 0)
                {
                    root->balance = 0;
                    leftTree->balance = 0;
                }
                else
                {
                    root->balance = 0;
                    leftTree->balance = -1;
                }
                rightTree->balance = 0;
                root->left = rotageLeft(leftTree);
                root = rotageRight(root);
                taller = false;
            }
            return root;
        }
        node *rightBlances(node *root, bool &taller)
        {
            node *rightTree = root->right;
            if (rightTree->balance == 1) // case 1: right of right. xoay don
            {
                root = rotageLeft(root);
                root->balance = 0;
                rightTree->balance = 0;
                taller = false;
            }
            else
            {
                node *leftTree = rightTree->left;
                if (leftTree->balance == 1)
                {
                    root->balance = -1;
                    rightTree->balance = 0;
                }
                else if (leftTree->balance == 0)
                {
                    root->balance = 0;
                    rightTree->balance = 0;
                }
                else
                {
                    root->balance = 0;
                    rightTree->balance = 1;
                }
                leftTree->balance = 0;
                root->right = rotageRight(rightTree);
                root = rotageLeft(root);
                taller = false;
            }
            return root;
        }
        node *insertAVL(node *root, node *pnew, bool &taller)
        {
            if (root == nullptr)
            {
                root = pnew;
                taller = true;
                root->balance = this->getHeightRec(root->left) - this->getHeightRec(root->right);
                return root;
            }
            if (pnew->key < root->key)
            {
                root->left = insertAVL(root->left, pnew, taller);
                // root->left->balance = this->getHeightRec(root->left->left) - this->getHeightRec(root->left->right);
                if (taller)
                {
                    if (root->balance == -1)
                        root = leftBlances(root, taller);
                    else if (root->balance == 0)
                        root->balance = -1;
                    else
                    {
                        root->balance = 0;
                        taller = false;
                    }
                }
            }
            else
            {
                root->right = insertAVL(root->right, pnew, taller);
                // root->right->balance = this->getHeightRec(root->right->left) - this->getHeightRec(root->right->right);
                if (taller)
                {
                    if (root->balance == -1)
                    {
                        root->balance = 0;
                        taller = false;
                    }
                    else if (root->balance == 0)
                    {
                        root->balance = 1;
                    }
                    else
                    {
                        root = rightBlances(root, taller);
                    }
                }
            }
            return root;
        }
        int getCount(){
            return this->count;
        }
        void insert(DATA data, std::string key)
        {
            bool taller = true;
            node *pnew = new node(data, key);
            this->root = insertAVL(this->root, pnew, taller);
            this->count++;
        }
        void _replace(node* root, DATA data, std::string key, bool& check)
        {
            if(root != nullptr)
            {
                _replace(root->left, data, key, check);
                if(root->key == key)
                {
                    check = true;
                    root->data = data;
                }
                _replace(root->right, data, key, check);
            }
        }
        bool replace(DATA data, std::string key)
        {
            bool check = false;
            _replace(this->root, data, key, check);
            return check;
        }
        void _findKey(node* root, std::string key, bool& find, DATA &get)
        {
            if(root != nullptr)
            {
                _findKey(root->left, key, find, get);
                if(root->key == key)
                {
                    find = true;
                    get = root->data;
                }
                _findKey(root->right, key, find, get);
            }

        }
        bool findKey(std::string key, DATA &get)
        {
            bool find = false;
            _findKey(this->root, key, find, get);
            return find;
        }

        void _findPar(node* root, std::string key1, bool &find, std::string &get)
        {
            if((root != nullptr) && (root->left != nullptr || root->right != nullptr))
            {
                if(root->right == nullptr)
                {
                    if(root->left->key == key1)
                    {
                        find = true;
                        get = root->key;
                    }
                }
                else if(root->left == nullptr)
                {
                    if(root->right->key == key1)
                    {
                        find = true;
                        get = root->key;
                    }
                }
                else
                {
                    if(root->right->key == key1 || root->left->key == key1)
                    {
                        find = true;
                        get = root->key;
                    }
                }
                _findPar(root->left, key1, find, get);
                _findPar(root->right, key1, find, get);
            }
        }
        bool findPar(std::string key1, std::string &get)
        {
            bool find = false;
            _findPar(this->root, key1, find, get);
            return find;
        }
        bool checkRoot(std::string key)
        {
            if(this->root->key == key) return true;
            else return false;
        }
        void deleteTree(node* root)
        {
            if(root != nullptr)
            {
                deleteTree(root->left);
                deleteTree(root->right);
                delete root;
            }
        }
        ~localVar()
        {
            deleteTree(this->root);
        }
        class node
        {
        private:
            DATA data;
            std::string key;
            node *left;
            node *right;
            int balance;
            friend class localVar;

        public:
            node(DATA value, std::string k) : data(value), key(k), left(nullptr), right(nullptr), balance(0) {}
            // ~node();
        };
    };

    /*
    Run the method written in the testcase
    @param filename name of the file
    */
    void run(std::string filename);
    void is_Local_Space_Full();
    void is_undefined_variable();

    void iadd(int line);
    void fadd(int line);
    void isub(int line);
    void fsub(int line);
    void imul(int line);
    void fmul(int line);
    void idiv(int line);
    void fdiv(int line);
    void irem(int line);
    void ineg(int line);
    void fneg(int line);
    void iand(int line);
    void ior(int line);
    void ieq(int line);
    void feq(int line);
    void ineq(int line);
    void fneq(int line);
    void ilt(int line);
    void flt(int line);
    void igt(int line);
    void fgt(int line);
    void ibnot(int line);

    void iconst(int val, int line);
    void fconst(float val, int line);
    void iload(std::string key, int line);
    void fload(std::string key, int line);
    void istore(std::string key, int line);
    void fstore(std::string key, int line);

    void i2f(int line);
    void f2i(int line);
    void _top(int line);

    void val(std::string key, int line);
    void par(std::string key, int line);
};

#endif // !__STACK_FRAME_H__
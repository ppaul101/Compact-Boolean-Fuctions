#include <iostream>
#include <string>
#include <sstream>
#include <vector>


struct bdnode{
    std::string val;
    bdnode* left;
    bdnode* right;
    
};

typedef bdnode* bdt;



bdt buildbdt(const std::vector<std::string>& fvalues);
bdt consTree (int i, int n);
void populateTree (bdt tree, const std::vector<std::string>& fvalues);



bdt buildcompactbdt(const std::vector<std::string>& fvalues);
void simplifyTreeSameChildren(bdt tree, bool& treeUpdated);
bool isLeaf(bdt tree);
void simplifyTreeSymmetry(bdt tree, bool& treeUpdated);
std::string evalcompactbdt(bdt t, const std::string& input);



void printAll (bdt tree);

void printTree(bdt tree, int count, bool left);



int main(int argc, const char * argv[])
{

    std::vector<std::string> input;
    std::string in = "001";
    input.push_back(in);
    in = "011";
    input.push_back(in);
    in = "110";
    input.push_back(in);
    in = "111";
    input.push_back(in);


    bdt compactRoot = buildcompactbdt(input);


    printTree(compactRoot, 0, false);

    std::cout <<std::endl;

    std::cout << "Is it in the compact tree?" << std::endl;
    std::cout<< evalcompactbdt(compactRoot, "101")<<std::endl<<std::endl;



    printAll(compactRoot);

    std::cout <<std::endl;


    return 0;

}





bdt buildbdt(const std::vector<std::string>& fvalues)
{
    // starting with an empty tree, need to build it
    
    bdt hdTree = NULL;
    
    
    if (fvalues[0].length() != 0)
    {
        int n = fvalues[0].length();
        
        hdTree = consTree(1, n);
        
        
        // tree is now set up
        // however, all roots have value '0'
        // we need to populate the tree with the '1's
        
        populateTree(hdTree, fvalues);
        
        
    }
    
    return hdTree;
}


void populateTree (bdt tree, const std::vector<std::string>& fvalues)
{
    // populate the '1's
    
    bdt originalTree = tree;
    
    for (int i = 0; i<fvalues.size(); i++)
    {
        // for each element in the vector
        
        for (int j = 0; j<fvalues[0].length(); j++)
        {
            // for each character in each element
            
            if (fvalues[i][j] == '0')
            {
                // single quotation marks for a character
                
                tree = tree -> left;
                
            }
            
            else if (fvalues[i][j] == '1')
            {
                
                tree = tree -> right;
                
            }
        }
        
        tree -> val = "1";
        
        // reset the tree
        tree = originalTree;
    }
    
    
}



bdt consTree (int i, int n)
{
    // recursive fn that creates the tree and sets all the leaves to 0
    
    bdt temp = new bdnode;
    
    
    if (i <=n)
    {
        
        std::stringstream ss;
        ss << "x" << i;
        std::string name = ss.str();
        
        temp -> val = name;
        temp -> left = consTree(i+1, n);
        temp -> right = consTree(i+1, n);
        
    }
    
    else
    {
        // default, set all elements to 0
        
        temp -> val = "0";
        temp -> left = NULL;
        temp -> right = NULL;
    }
    
    return temp;
    
}




bdt buildcompactbdt(const std::vector<std::string>& fvalues){
    
    // first build the entire (non - compact) binary tree
    
    bdt compacthdTree = buildbdt(fvalues);
    
    // simplify the tree
    // will need to call simplifyTreeSameChildren
    // till treeUpdated is false
    
    bool treeDidUpdate = true;
    
    while (treeDidUpdate)
    {
        // by default, assume no changes made to the tree
        
        treeDidUpdate = false;
        simplifyTreeSameChildren(compacthdTree, treeDidUpdate);
        
    }
    
    // reset
    
    treeDidUpdate = true;
    
    while (treeDidUpdate)
    {
        treeDidUpdate = false;
        simplifyTreeSymmetry(compacthdTree, treeDidUpdate);
    }
    
    
    return compacthdTree;
}




void simplifyTreeSameChildren(bdt tree, bool& treeUpdated)
{
    if (tree != NULL)
    {
        if (tree -> left != NULL)
        {
            simplifyTreeSameChildren(tree -> left, treeUpdated);
            
            // here 'tree' is the parent of the leaf nodes
            
            
            // the &&  is needed to ensure that we aren't printing x2
            // for example matching children x3,x3, but x2 itself isn't a parent of a leaf node
            
            if (tree -> left -> val == tree -> right -> val && tree -> left -> left == NULL)
            {
                // replace parent with value of child
                
                tree -> val = tree -> left -> val;
                
                delete tree -> left;
                delete tree -> right;
                
                tree -> left = NULL;
                tree -> right = NULL;
                
                treeUpdated = true;
            }
            
            else if (!treeUpdated)
            {
                treeUpdated = false;
            }
            
            simplifyTreeSameChildren(tree -> right, treeUpdated);
        }
    }
    
}




bool isLeaf(bdt tree)
{
    if (tree -> left == NULL)
    {
        return true;
    }
    
    return false;
}



void simplifyTreeSymmetry(bdt tree, bool& treeUpdated)
{
    if (tree != NULL && !isLeaf(tree))
    {
        simplifyTreeSymmetry(tree -> left, treeUpdated);
        
        // to avoid analysing parents, we want to find the grandparents
        
        if (!isLeaf(tree -> right))
        {
            // ensure right child of grandparent is parent of two leaf nodes
            
            if (tree -> right -> right -> right == NULL && tree -> right -> left -> right == NULL)
            {
                
                bdt LST = tree -> left;
                bdt RST = tree -> right;
                
                // don't want to combine x2 and x3
                
                if (LST -> val == RST -> val)
                {
                    
                    if (LST -> left -> val == RST -> left -> val && LST -> right -> val == RST -> right -> val)
                    {
                        tree -> val = LST -> val; // = RST -> val
                        
                        LST -> val = LST -> left -> val;
                        RST -> val = RST -> right -> val;
                        
                        delete LST -> left;
                        delete LST -> right;
                        
                        LST -> left = NULL;
                        LST -> right = NULL;
                        
                        
                        delete RST -> left;
                        delete RST -> right;
                        
                        RST -> left = NULL;
                        RST -> right = NULL;
                        
                        
                        treeUpdated = true;
                        
                    }
                }
                
            }
        }
        
        
        simplifyTreeSymmetry(tree -> right, treeUpdated);
        
    }
    
}




std::string evalcompactbdt(bdt t, const std::string& input)
{
    
    if (input == "" || t == NULL)
    {
        return "";
    }
    
    int xLayer;
    
    for (int i = 0; i<input.size(); i++)
    {
        // place at the beginning for case when all leaf nodes are 1
        // the binary tree will be a 1
        
        if (isLeaf(t))
        {
            return t -> val;
        }
        
        // converting a character to an int (ASCII)
        
        xLayer = t -> val[1] - 48;
        
        
        // -1 as xLayer begins with 1 (corressponding to X1)
        // character count starts from index 0
        
        if (input[xLayer-1] == '1')
        {
            t = t->right;
        }
        
        else if (input[xLayer-1] == '0')
        {
            t = t->left;
        }
    }
    
    return t->val;
}




void printAll (bdt tree)
{
    if (tree != NULL)
    {
        printAll(tree -> left);

        std::cout << tree -> val << std::endl;

        printAll(tree -> right);
    }
}


// started off with tree -> left first

void printTree(bdt tree, int count, bool left)
{
   if (tree != NULL)
   {
       // formatting for LHS of binary tree

       if (left)
       {
           for (int i = 0; i < count -1 ; i++)
           {
               std::cout << " ";
           }

           // "\\" to print '\'

           std :: cout << "\\" << std::endl;
       }

       printTree(tree -> right, count + 3, false);

       for (int i = 0; i < count; i++)
       {
           std::cout << " ";
       }

       std::cout << tree -> val << std::endl;

       // formatting for RHS of binary tree

       if (!left)
       {
           for (int i = 0; i < count -1 ; i++)
           {
               std::cout << " ";
           }

           // avoid '/' for root

           if (count != 0)
           {
               std :: cout << "/" << std::endl;
           }
       }

       printTree(tree -> left, count + 3, true);

   }


}

# Compact-Boolean-Fuctions

This C++ project simplifies the use of truth tables for binary logic.

Consider the following 'and' operator on two binary variables x1 and x2:

![image](https://github.com/ppaul101/Compact-Boolean-Fuctions/blob/master/Compact-Boolean-Fuctions/Images%20for%20readme/Truth%20table.jpg)

This can be expressed using the following binary tree:

![image](https://github.com/ppaul101/Compact-Boolean-Fuctions/blob/master/Compact-Boolean-Fuctions/Images%20for%20readme/Binary%20tree.jpg)


The function 'buildbdt' takes in a vector of strings as input in order to construct the binary tree. 'buildbdt' returns a pointer to the root node of the tree data structure. 

The input strings correspond to the binary values '1'. 

For the above example with only two binary variables:

```
std::vector<std::string> input;
std::string in = "11";
input.push_back(in);
bdt andbdt = buildbdt(input);
```

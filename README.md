# Compact-Boolean-Fuctions

This C++ project simplifies the use of truth tables for binary logic.

Consider the following 'and' operator on two binary variables x1 and x2:

![image](https://github.com/ppaul101/Compact-Boolean-Fuctions/blob/master/Compact-Boolean-Fuctions/Images%20for%20readme/Truth%20table.jpg)

This can be expressed using the following binary tree:

![image](https://github.com/ppaul101/Compact-Boolean-Fuctions/blob/master/Compact-Boolean-Fuctions/Images%20for%20readme/Binary%20tree.jpg)

## The function 'buildbdt'
The function 'buildbdt' takes in a vector of strings as input in order to construct the binary tree. 'buildbdt' returns a pointer to the root node of the tree data structure. 

The input strings correspond to the binary values '1'. 

For the above example with only two binary variables:

```
std::vector<std::string> input;
std::string in = "11";
input.push_back(in);
bdt andbdt = buildbdt(input);
```

The build function constructs a binary tree of 'n' binary variables (two in the above case), indepdent of the boolean logic operator. 

For example, the same function can be called to represent the 'or' operator:

```
std::vector<std::string> input;
std::string in = "10";
input.push_back(in);
in = "11";
input.push_back(in);
in = "01";
input.push_back(in);
bdt orbdt = buildbdt(input);
```

We can also construct the logic for the truth table below, using 'buildbdt':

![image](https://github.com/ppaul101/Compact-Boolean-Fuctions/blob/master/Compact-Boolean-Fuctions/Images%20for%20readme/larger%20truth%20table.jpg)


This is achieved using the following vector of strings:
```
std::vector<std::string> input;
std::string in = "000010";
input.push_back(in);
in = "010010";
input.push_back(in);
in = "110011";
input.push_back(in);
bdt fbdt = buildbdt(input);
```

## The function 'evalbdt'
The function 'evalbdt' returns the string corresponding to the value of node specified by its input parameter. 

For example:
```
std::vector<std::string> input;
std::string in = "000010";
input.push_back(in);
in = "010010";
input.push_back(in);
in = "110011";
input.push_back(in);
bdt fbdt = buildbdt(input);
std::cout << evalbdt(fbdt, "000010") << std::endl;
// prints "1"
std::cout << evalbdt(fbdt, "000001") << std::endl;
// prints "0"
```

## The function 'buildcompactbdt'
'buildcompactbdt' takes in the same inputs as 'buildbdt', however it greatly simplifies the boolean logic represented by the binary tree. 

For example, the previous 'and' binary tree:

![image](https://github.com/ppaul101/Compact-Boolean-Fuctions/blob/master/Compact-Boolean-Fuctions/Images%20for%20readme/Binary%20tree.jpg)


can be simplified to the following:

![image](https://github.com/ppaul101/Compact-Boolean-Fuctions/blob/master/Compact-Boolean-Fuctions/Images%20for%20readme/Simplified%20and.jpg)


In addition, the binary tree below:

![image](https://github.com/ppaul101/Compact-Boolean-Fuctions/blob/master/Compact-Boolean-Fuctions/Images%20for%20readme/Grandparent%20complex.jpg)


can be more compactly represented as:

![image](https://github.com/ppaul101/Compact-Boolean-Fuctions/blob/master/Compact-Boolean-Fuctions/Images%20for%20readme/Grandparent%20simplified.jpg)


## The function 'evalcompactbdt'
'evalcompactbdt' is similar to 'evalbdt', however it operates on the simplified binary tree. 

## The report
Here is a link to my final project report, in PDF format: https://goo.gl/uGDYLT

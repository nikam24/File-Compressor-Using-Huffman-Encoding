**Huffman Algorithm for File Compression**
=========================

https://github.com/nikam24/huffman/  
License: Public Domain, no warranty  
Prathmesh Nikam

About
=====

Huffman Algorithm is an efficient way for file Compression and Decompression.
This program exactly follows huffman algorithm. It reads frequent characters from input file and replace it with shorter binary codeword.
The original file can be produced again without loosing any bit.

Usage
=====
Compression:
```
	./huffman <file to compress>
```
Output file named <inputfile>.bin will be produced.
Decompression:
```
   Decompression will automatically executed and a file named Decompression will be created.
```

Algorithm
============================
Steps to build Huffman Tree
Input is an array of unique characters along with their frequency of occurrences and output is Huffman Tree. 

Create a leaf node for each unique character and build a min heap of all leaf nodes (Min Heap is used as a priority queue. The value of frequency field is used to compare two nodes in min heap. Initially, the least frequent character is at root)
Extract two nodes with the minimum frequency from the min heap.
 
Create a new internal node with a frequency equal to the sum of the two nodes frequencies. Make the first extracted node as its left child and the other extracted node as its right child. Add this node to the min heap.
Repeat steps#2 and #3 until the heap contains only one node. The remaining node is the root node and the tree is complete.
Let us understand the algorithm with an example:
character   Frequency
    a            5
    b           9
    c           12
    d           13
    e           16
    f           45
Step 1. Build a min heap that contains 6 nodes where each node represents root of a tree with single node.
Step 2 Extract two minimum frequency nodes from min heap. Add a new internal node with frequency 5 + 9 = 14. 
 

Illustration of step 2
Illustration of step 2

Now min heap contains 5 nodes where 4 nodes are roots of trees with single element each, and one heap node is root of tree with 3 elements

character           Frequency
       c               12
       d               13
 Internal Node         14
       e               16
       f                45
Step 3: Extract two minimum frequency nodes from heap. Add a new internal node with frequency 12 + 13 = 25
 

Illustration of step 3
Illustration of step 3

Now min heap contains 4 nodes where 2 nodes are roots of trees with single element each, and two heap nodes are root of tree with more than one nodes

character           Frequency
Internal Node          14
       e               16
Internal Node          25
       f               45
Step 4: Extract two minimum frequency nodes. Add a new internal node with frequency 14 + 16 = 30
 

Illustration of step 4
Illustration of step 4

Now min heap contains 3 nodes.

character          Frequency
Internal Node         25
Internal Node         30
      f               45 
Step 5: Extract two minimum frequency nodes. Add a new internal node with frequency 25 + 30 = 55
 

Illustration of step 5
Illustration of step 5

Now min heap contains 2 nodes.

character     Frequency
       f         45
Internal Node    55
Step 6: Extract two minimum frequency nodes. Add a new internal node with frequency 45 + 55 = 100
 

Illustration of step 6
Illustration of step 6

Now min heap contains only one node.

character      Frequency
Internal Node    100
Since the heap contains only one node, the algorithm stops here.

Steps to print codes from Huffman Tree:
Traverse the tree formed starting from the root. Maintain an auxiliary array. While moving to the left child, write 0 to the array. While moving to the right child, write 1 to the array. Print the array when a leaf node is encountered.
 

Steps to print code from HuffmanTree
Steps to print code from HuffmanTree

The codes are as follows:

character   code-word
    f          0
    c          100
    d          101
    a          1100
    b          1101
    e          111


Contributing
============

Please feel free to submit issues and pull requests. I appreciate bug reports.
Testing on different platforms is especially appreciated. I only tested on Linux.

License
=======

This software is in the *Public Domain*. That means you can do whatever you like
with it. That includes being used in proprietary products without attribution or
restrictions. There are no warranties and there may be bugs. 

Formally we are using CC0 - a Creative Commons license to place this work in the
public domain. A copy of CC0 is in the LICENSE file. 

    "CC0 is a public domain dedication from Creative Commons. A work released
    under CC0 is dedicated to the public domain to the fullest extent permitted
    by law. If that is not possible for any reason, CC0 also provides a lax,
    permissive license as a fallback. Both public domain works and the lax
    license provided by CC0 are compatible with the GNU GPL."
      - http://www.gnu.org/licenses/license-list.html#CC0

Development
===========

To do:
* Binary files, like jpeg,mp3 support
* Run scan to group repeating bit patterns, not bit.
* Unicode support

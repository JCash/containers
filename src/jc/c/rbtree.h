// Alternatives:

// https://github.com/fbuihuu/libtree/blob/master/rb.c (GPL)


/*
ABOUT:
    Red-Black tree for binary searches

VERSION:
    1.00 - (2023-01-05) Initial commit

LICENSE:

    The MIT License (MIT)

    Copyright (c) 2023 Mathias Westerdahl

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.


DISCLAIMER:

    This software is supplied "AS IS" without any warranties and support

*/


/* Examples:
*/

#ifndef JC_RBTREE_H
#define JC_RBTREE_H

#include <assert.h>
#include <stdint.h>

typedef struct jc_rbt_node_ jc_rbt_node;
typedef struct jc_rbt_tree_ jc_rbt_tree;

typedef void* (*jc_rbt_alloc_fn)(size_t);
typedef void (*jc_rbt_free_fn)(void*);
typedef int (*jc_rbt_compare_fn)(const void*, const void*);


#pragma pack(push, 1)

struct jc_rbt_node_
{
    jc_rbt_node*    parent;
    jc_rbt_node*    child[2]; // 0 : left, 1: right
    void*           data;
    uint8_t         red:1;
    uint8_t         :7;
};

#pragma pack(pop)


jc_rbt_tree* jc_rbt_create(jc_rbt_compare_fn compare_fn, jc_rbt_alloc_fn alloc_fn, jc_rbt_free_fn free_fn);
void         jc_rbt_destroy(jc_rbt_tree* tree);
int          jc_rbt_empty(jc_rbt_tree* tree);
jc_rbt_node* jc_rbt_get_root(jc_rbt_tree* tree);

void         jc_rbt_insert(jc_rbt_tree* tree, void* key);
void         jc_rbt_remove(jc_rbt_tree* tree, void* key);

jc_rbt_node* jc_rbt_find(jc_rbt_tree* tree, void* key);
void         jc_rbt_insert_node(jc_rbt_tree* tree, jc_rbt_node* parent, int cmp, jc_rbt_node* child);
jc_rbt_node* jc_rbt_remove_node(jc_rbt_tree* tree, jc_rbt_node* node);

#endif // JC_RBTREE_H
/* ******************************************************************************************************** */

#ifdef JC_RBTREE_IMPLEMENTATION
#undef JC_RBTREE_IMPLEMENTATION

// Literature:
//  https://www.happycoders.eu/algorithms/red-black-tree-java/
//  https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/

struct jc_rbt_tree_
{
    jc_rbt_node*        root;
    jc_rbt_node*        nil;
    jc_rbt_node         _nil;
    jc_rbt_alloc_fn     alloc_fn;
    jc_rbt_free_fn      free_fn;
    jc_rbt_compare_fn   compare_fn;
};

static void jc_rbt_delete_node(jc_rbt_tree* tree, jc_rbt_node* node);

jc_rbt_tree* jc_rbt_create( jc_rbt_compare_fn compare_fn, jc_rbt_alloc_fn alloc_fn, jc_rbt_free_fn free_fn)
{
    if (!alloc_fn) alloc_fn = malloc;
    if (!free_fn) free_fn = free;
    assert(compare_fn != 0);
    assert(alloc_fn != 0);
    assert(free_fn != 0);

    jc_rbt_tree* tree = (jc_rbt_tree*)alloc_fn(sizeof(jc_rbt_tree));
    tree->nil = &tree->_nil;
    tree->_nil.parent = tree->nil;
    tree->_nil.child[0] = tree->nil;
    tree->_nil.child[1] = tree->nil;
    tree->_nil.data = 0;
    tree->_nil.red = 0;
    tree->root = tree->nil;
    tree->compare_fn = compare_fn;
    tree->alloc_fn = alloc_fn;
    tree->free_fn = free_fn;
    return tree;
}

void jc_rbt_destroy(jc_rbt_tree* tree)
{
    jc_rbt_delete_node(tree, tree->root);
    tree->free_fn((void*)tree);
}

int jc_rbt_empty(jc_rbt_tree* tree)
{
    return tree->root?0:1;
}

jc_rbt_node* jc_rbt_get_root(jc_rbt_tree* tree)
{
    return tree->root;
}

static jc_rbt_node* jc_rbt_alloc_node(jc_rbt_tree* tree)
{
    return (jc_rbt_node*)tree->alloc_fn(sizeof(jc_rbt_node));
}

static void jc_rbt_free_node(jc_rbt_tree* tree, jc_rbt_node* node)
{
    tree->free_fn((void*)node);
}

static jc_rbt_node* jc_rbt_new_node(jc_rbt_tree* tree)
{
    jc_rbt_node* node = jc_rbt_alloc_node(tree);
    node->parent = node->child[0] = node->child[1] = tree->nil;
    node->data = 0;
    node->red = 0;
    return node;
}

static void jc_rbt_delete_node(jc_rbt_tree* tree, jc_rbt_node* node)
{
    if (node == tree->nil)
        return;
    jc_rbt_delete_node(tree, node->child[0]);
    jc_rbt_delete_node(tree, node->child[1]);
    jc_rbt_free_node(tree, node);
}

static inline void jc_rbt_rotate_dir(jc_rbt_tree* tree, jc_rbt_node* node, int dir)
{
    int odir = 1 - dir; // other child
    jc_rbt_node* child = node->child[odir];
    node->child[odir] = child->child[dir];
    if (node->child[odir] != tree->nil)
        node->child[odir]->parent = node;
    child->parent = node->parent;
    if (node->parent == tree->nil)
        tree->root = child;
    else
    if (node == node->parent->child[dir])
        node->parent->child[dir] = child;
    else
        node->parent->child[odir] = child;
    child->child[dir] = node;
    node->parent = child;
}

static inline void jc_rbt_rotate_left(jc_rbt_tree* tree, jc_rbt_node* node)
{
    jc_rbt_rotate_dir(tree, node, 0);
}
static inline void jc_rbt_rotate_right(jc_rbt_tree* tree, jc_rbt_node* node)
{
    jc_rbt_rotate_dir(tree, node, 1);
}

jc_rbt_node* jc_rbt_find(jc_rbt_tree* tree, void* key)
{
    jc_rbt_node* node = tree->root;
    while (node != tree->nil)
    {
        int cmp = tree->compare_fn(key, node->data);
        if (cmp == 0)
            return node;
        node = cmp < 0 ? node->child[0] : node->child[1];
    }
    return 0;
}

static void jc_rbt_insert_fixup(jc_rbt_tree* tree, jc_rbt_node* node)
{
    do
    {
        jc_rbt_node* grandparent = node->parent->parent;
        if (node->parent == grandparent->child[0])
        {
            jc_rbt_node* uncle = grandparent->child[1];
            if (uncle->red)
            {
                node->parent->red = 0;
                uncle->red = 0;
                node = grandparent;
                node->red = 1;
            }
            else
            {
                if (node == node->parent->child[1])
                {
                    node = node->parent;
                    jc_rbt_rotate_left(tree, node);
                }

                node->parent->red = 0;
                grandparent->red = 1;
                jc_rbt_rotate_right(tree, grandparent);
            }
        }
        else
        {
            jc_rbt_node* uncle = grandparent->child[0];
            if (uncle->red)
            {
                node->parent->red = 0;
                uncle->red = 0;
                node = grandparent;
                node->red = 1;
            }
            else
            {
                if (node == node->parent->child[0])
                {
                    node = node->parent;
                    jc_rbt_rotate_right(tree, node);
                }

                node->parent->red = 0;
                grandparent->red = 1;
                jc_rbt_rotate_left(tree, grandparent);
            }
        }
    } while (node->parent->red);
    tree->root->red = 0;
}


void jc_rbt_insert_node(jc_rbt_tree* tree, jc_rbt_node* parent, int cmp, jc_rbt_node* child)
{
    if (parent == tree->nil)
        tree->root = child;
    else
    {
        if(cmp < 0)
            parent->child[0] = child;
        else
            parent->child[1] = child;
    }

    if (child->parent->red)
        jc_rbt_insert_fixup(tree, child);

    tree->root->red = 0;
}

void jc_rbt_insert(jc_rbt_tree* tree, void* key)
{
    jc_rbt_node* node = tree->root;
    jc_rbt_node* parent = tree->nil;
    while (node != tree->nil)
    {
        parent = node;
        int cmp = tree->compare_fn(key, node->data);
        if (cmp < 0)
            node = node->child[0];
        else if (cmp > 0)
            node = node->child[1];
        else {
            return; // Key already exists
        }
    }

    jc_rbt_node* new_node = jc_rbt_alloc_node(tree);
    new_node->child[0] = new_node->child[1] = tree->nil;
    new_node->parent = parent;
    new_node->data = key;
    new_node->red = 1;

    int cmp = 0;
    if (parent != tree->nil)
        cmp = tree->compare_fn(key, parent->data);

    jc_rbt_insert_node(tree, parent, cmp, new_node);
}

// https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/
static void jc_rbt_remove_fixup(jc_rbt_tree* tree, jc_rbt_node* node)
{
    const jc_rbt_node* root = tree->root;
    do
    {
        if (node == node->parent->child[0])
        {
            jc_rbt_node* sibling = node->parent->child[1];
            if (sibling->red)
            {
                sibling->red = 0;
                node->parent->red = 1;
                jc_rbt_rotate_left(tree, node->parent);
                sibling = node->parent->child[1];
            }

            if (!sibling->child[0]->red && !sibling->child[1]->red)
            {
                sibling->red = 1;
                if (node->parent->red)
                {
                    node->parent->red = 0;
                    break;
                }
                else
                {
                    node = node->parent;
                }
            }
            else
            {
                if (!sibling->child[1]->red)
                {
                    sibling->child[0]->red = 0;
                    sibling->red = 1;
                    jc_rbt_rotate_right(tree, sibling);
                    sibling = node->parent->child[1];
                }

                sibling->red = node->parent->red;
                sibling->child[1]->red = 0;
                node->parent->red = 0;
                jc_rbt_rotate_left(tree, node->parent);
                break;
            }
        }
        else
        {
            jc_rbt_node* sibling = node->parent->child[0];
            if (sibling->red)
            {
                sibling->red = 0;
                node->parent->red = 1;
                jc_rbt_rotate_right(tree, node->parent);
                sibling = node->parent->child[0];
            }

            if (!sibling->child[0]->red && !sibling->child[1]->red)
            {
                sibling->red = 1;
                if (node->parent->red)
                {
                    node->parent->red = 0;
                    break;
                }
                else
                {
                    node = node->parent;
                }
            }
            else
            {
                if (!sibling->child[0]->red)
                {
                    sibling->child[1]->red = 0;
                    sibling->red = 1;
                    jc_rbt_rotate_left(tree, sibling);
                    sibling = node->parent->child[0];
                }

                sibling->red = node->parent->red;
                sibling->child[0]->red = 0;
                node->parent->red = 0;
                jc_rbt_rotate_right(tree, node->parent);
                break;
            }
        }
    } while (node != root);
}

static jc_rbt_node* jc_rbt_successor(jc_rbt_tree* tree, jc_rbt_node* node)
{
    jc_rbt_node* n = node->child[1];
    if (n != tree->nil)
    {
        while (n->child[0] != tree->nil)
            n = n->child[0];
    }
    else
    {
        for (n = node->parent; node == n->child[1]; node = n, n = n->parent)
        {}
    }
    return n;
}



jc_rbt_node* jc_rbt_remove_node(jc_rbt_tree* tree, jc_rbt_node* node)
{
    assert(node != 0);

    jc_rbt_node* target;
    if (node->child[0] == tree->nil || node->child[1] == tree->nil)
    {
        target = node;
    }
    else
    {
        target = jc_rbt_successor(tree, node);
        node->data = target->data;
    }

    jc_rbt_node* child = target->child[0] == tree->nil ? target->child[1] : target->child[0];

    if (!target->red)
    {
        if (child->red)                 child->red = 0;
        else if (target == tree->root)  {}
        else                            jc_rbt_remove_fixup(tree, target);
    }

    if (child != tree->nil)
        child->parent = target->parent;

    if (target->parent == tree->nil)
        tree->root = child;
    else if (target == target->parent->child[0])
        target->parent->child[0] = child;
    else
        target->parent->child[1] = child;

    target->child[0] = target->child[1] = tree->nil;
    return target;
}

void jc_rbt_remove(jc_rbt_tree* tree, void* key)
{
    jc_rbt_node* node = jc_rbt_find(tree, key);
    if (node == tree->nil)
        return;
    jc_rbt_node* removed = jc_rbt_remove_node(tree, node);
    jc_rbt_delete_node(tree, removed);
}

#endif // JC_RBTREE_IMPLEMENTATION

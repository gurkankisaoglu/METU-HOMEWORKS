#ifndef _BIN_SEARCH_TREE_H_
#define _BIN_SEARCH_TREE_H_

#include <functional>
#include <cstddef>
#include <stack>
#include <list>
#include <ostream>


template <typename Key, typename Object, 
          typename Comparator=std::less<Key> >
class BinarySearchTree 
{
  private: 
    struct BinaryNode //node definition: a dependent type
    {
      Key key; //keys will be kept constant
      Object data; //objects that are referred to by keys may change
      BinaryNode * left;
      BinaryNode * right;
      size_t height; //height info should be updated per insert & delete

      BinaryNode(const Key &, const Object &,
                 BinaryNode *, BinaryNode *, size_t =0);
    };

  public: 
    class Iterator //iterator class will encapsulate the location within the BST
    {
      public:
        Iterator( ); //dummy constructor for type declaration purposes
        Iterator & operator++( ); //inorder increment
 
        Object & operator*( );  //update data
        const Object & operator*( ) const; //view data

        bool operator==(const Iterator & rhs) const; //compare iterators
        bool operator!=(const Iterator & rhs) const; //compare iterators
      
      private:
        BinaryNode * current; //position
        const BinaryNode * root; //for error check not implemented
        std::stack<BinaryNode *> s; //will be used to conduct in order traversal if
        bool useStack; //this variable is set to true, ignored in == and !=
        
      private:
        Iterator(BinaryNode *, const BinarySearchTree &, bool =true);
        
      friend class BinarySearchTree<Key, Object, Comparator>; 
    };

  public: 
    BinarySearchTree( ); //empty tree
    ~BinarySearchTree( ); //reclaim all dyn allocated mem

    void insert(const Key &, const Object &); //to insert new key,item
    void remove(const Key &); //remove the node with the key value (and also data) 

  public: //do not change
    Iterator find(const Key &) const; //single item
    std::list<Iterator> find(const Key &, const Key &) const;//range queries

    Iterator begin( ) const; //inorder begin
    Iterator end( ) const; //dummy NULL iterator

  public: //do not change
    int height( ) const; //return height of the tree
    size_t size( ) const; //return the number of items in the tree
    bool empty( ) const; //return whether the tree is empty or not
    void print(std::ostream &) const;
  
  private: //do not change
    BinaryNode * root; //designated root
    size_t nodes; //number of nodes 
    Comparator isLessThan; //function object to compare keys

  private:
    
    void makeEmpty(BinaryNode * &);

    BinaryNode * find(const Key &, BinaryNode *) const;
    int height(BinaryNode *) const;
    void print(BinaryNode *, std::ostream &) const;

    template <typename T> //static utility function
    static const T & max(const T &, const T &);

    //balancing functions
    void rotateWithLeftChild(BinaryNode * &);
    void rotateWithRightChild(BinaryNode * &);
    void doubleWithLeftChild(BinaryNode * &);
    void doubleWithRightChild(BinaryNode * &);
    
    //utility functions
    void insert(BinaryNode *&,const Key&,const Object &);
    void remove(BinaryNode *&, const Key &);
    void preorder(BinaryNode *&);
    BinaryNode *searchParent(BinaryNode* node,const Key & value);
    void swap(BinaryNode*& node);
 
private: 
    BinarySearchTree(const BinarySearchTree &);
    const BinarySearchTree & operator=(const BinarySearchTree &);
};


template <typename K, typename O, typename C>
BinarySearchTree<K,O,C>::BinaryNode::
BinaryNode(const K & _k, const O & _d,
           BinaryNode * _l, BinaryNode * _r, size_t _h)
  : key(_k), data(_d), left(_l), right(_r), height(_h)
{
}

template <typename K, typename O, typename C>
BinarySearchTree<K,O,C>::BinarySearchTree( )
  : root(NULL), nodes(0) 
{
}

template <typename K, typename O, typename C>
BinarySearchTree<K,O,C>::~BinarySearchTree( )
{
  makeEmpty(root);
}

template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::makeEmpty(BinaryNode * & t)
{
  if (t != NULL)
  {
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
    --nodes;
  }

  t = NULL;
}

template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::insert(BinaryNode*& node ,const K & k, const O & x){
  if(node==NULL){
    node=new BinaryNode(k,x,NULL,NULL,0);
    return;
  }
  else if(isLessThan(k,node->key)){

    insert(node->left,k,x);
    node->height=1+max(height(node->left),height(node->right));
    
    if(height(node->left)-height(node->right)==2){
      if(isLessThan(k,node->left->key)) rotateWithLeftChild(node);
      else doubleWithLeftChild(node);
    }
  }
  else if(isLessThan(node->key,k)){

    insert(node->right,k,x);
    node->height=1+max(height(node->left),height(node->right));
    
    if(height(node->right)-height(node->left)==2){
      if(isLessThan(node->right->key,k)) rotateWithRightChild(node);
      else doubleWithRightChild(node);
    }
  
  }
  else 

    node->height=max(height(node->left),height(node->right))+1;

}
template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::preorder(BinaryNode*& node){
  if(node==NULL) return;
  std::cout << node->key<< " " ;
  preorder(node->left);
  preorder(node->right);
}


template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::insert(const K & k, const O & x)
{ 
  BinaryNode *node=find(k,this->root);
  if(!node){
    this->nodes++;
    insert(this->root,k,x);
  }else{
    node->data=x;
  }
}

template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::BinaryNode *
BinarySearchTree<K,O,C>::searchParent(BinaryNode* node,const K & value){

  if(node==NULL) return NULL;
  if( (node->left != NULL && !isLessThan(node->left->key,value) && !isLessThan(value,node->left->key))
        || (node->right != NULL && !isLessThan(node->right->key,value) && !isLessThan(value,node->right->key))){
    return node;
  }
  if(isLessThan(value,node->key)){
    return searchParent(node->left,value);
  }
  if(isLessThan(node->key,value)){
    return searchParent(node->right,value);
  }else{
    return NULL;
  }
}
template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::swap(BinaryNode*& node){
  BinaryNode *curr=node;
  BinaryNode *currR=node->right;
  BinaryNode *parent=currR;
  while(currR->left){
    parent=currR;
    currR=currR->left;
  }

  if(parent==currR){
    BinaryNode *tmp(currR->right);
    currR->right=curr;
    curr->right=tmp;
    currR->left=curr->left;
    curr->left=NULL;
    node=currR;    
  }else{
    BinaryNode *tmp(currR->right);
    currR->right=curr->right;
    curr->right=tmp;
    currR->left=curr->left;
    curr->left=NULL;
    parent->left=curr;
    node=currR;
  }
}

template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::remove(BinaryNode*& node,const K & k){
  if(node==NULL){
    return;
  }
  

  if(isLessThan(k,node->key)){
    remove(node->left,k);

    if(height(node->right)-height(node->left)==2){
      if(height(node->right->left)>height(node->right->right)) doubleWithRightChild(node);
      else rotateWithRightChild(node);   
    }
  }
  else if(isLessThan(node->key,k)){
    remove(node->right,k);

    if(height(node->left)-height(node->right)==2){
      if(height(node->left->right)>height(node->left->left)) doubleWithLeftChild(node);
      else rotateWithLeftChild(node);   
    }

  }
 
  else{
    if((node->left==NULL) || (node->right==NULL)){
      BinaryNode* tmp=node->left ? node->left : node->right;
      if(tmp==NULL){
        delete node;
        node=NULL;
        return;
      }
      else{
        delete node;
        node=tmp;
      }
    }else{
      swap(node);      
      remove(node->right,k);
      if(height(node->left)-height(node->right)==2){
      	if(height(node->left->right)>height(node->left->left)) doubleWithLeftChild(node);
      	else rotateWithLeftChild(node);   
      }
    }
  } 
  
    node->height = 1 + max(height(node->left),height(node->right));

}

template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::remove(const K & k)
{
  BinaryNode *node=find(k,this->root);
  if(node){
    this->nodes--;
    remove(root,k);
  }

}

template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::Iterator
BinarySearchTree<K,O,C>::find(const K & key) const
{
  BinaryNode * node = find(key, root);

  if (node == NULL)
  {
    return end();
  }
  else
  {               //not inorder iterator
    return Iterator(node, *this, false);
  }
}

/*
 * private utility function to search elements
 */
template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::BinaryNode *
BinarySearchTree<K,O,C>::find(const K & key, BinaryNode * t) const
{
  if (t == NULL)
  {
    return NULL;
  }
  else if (isLessThan(key, t->key))
  {
    return find(key, t->left);
  }
  else if (isLessThan(t->key, key))
  {
    return find(key, t->right);
  }
  else //found
  {
    return t;
  }
}

//range queries those within range are inserted to the list
template <typename K, typename O, typename C>
std::list<typename BinarySearchTree<K,O,C>::Iterator>
BinarySearchTree<K,O,C>::find(const K & lower, const K & upper) const
{

  BinarySearchTree<K,O,C>::Iterator Low=this->begin();
  BinarySearchTree<K,O,C>::Iterator Up=this->begin();
  
  
  std::list<BinarySearchTree<K,O,C>::Iterator> result;



  while(Up.current && !isLessThan(upper,Up.current->key)){
    
    
    ++Up;
  }
  
  while(Low!=Up){

    if(!isLessThan(Low.current->key , lower)){
      BinarySearchTree<K,O,C>::Iterator it(Low.current,*this,false);
      result.push_back(it);
    }
    ++Low;
  }


  return result;

}

//INORDER iterator begins at ++root
template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::Iterator
BinarySearchTree<K,O,C>::begin() const
{
  return Iterator(root, *this);
}

//no more increment after end() also
//returned in case of unsuccessful search
//or when no more applicance of ++ is possible
template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::Iterator
BinarySearchTree<K,O,C>::end() const
{
  return Iterator(NULL, *this);
}

//public function to return height
template <typename K, typename O, typename C>
int
BinarySearchTree<K,O,C>::height( ) const
{
  return height(root);
}

/* private utility function for computing height */
template <typename K, typename O, typename C>
int
BinarySearchTree<K,O,C>::height(BinaryNode * t) const
{
  return (t == NULL) ? -1 : t->height;
}

//public function to return number of nodes in the tree
template <typename K, typename O, typename C>
size_t
BinarySearchTree<K,O,C>::size( ) const
{
  return nodes;
}

//public true if empty false o.w.
template <typename K, typename O, typename C>
bool
BinarySearchTree<K,O,C>::empty( ) const
{
  return nodes == 0;
}

//public function to print keys inorder to some ostream
template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::print(std::ostream & out) const
{
  print(root, out);
  out << '\n';
}

template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::print(BinaryNode * t, std::ostream & out) const
{
  if (t != NULL && t->left != NULL) 
  {
    out << '[';
    print( t->left, out );
  }
  else if (t != NULL && t->left == NULL && t->right != NULL)
  {
    out << "[";
  }

  if (t != NULL)
  {
    if (t->left == NULL && t->right == NULL)
    {
      out << '(' << (t->key) << ')';
    }
    else if (t->left != NULL || t->right != NULL)
    {
      out << '{' << (t->key) << ",H" << t->height << '}';
    }
  }
  
  if (t != NULL && t->right != NULL)
  {
    print( t->right, out );
    out << ']';
  }
  else if (t != NULL && t->left != NULL && t->right == NULL)
  {
    out << "]";
  }
}

/* static function to compute maximum of two elements */
template <typename K, typename O, typename C>
template <typename T>
const T &
BinarySearchTree<K,O,C>::max(const T & el1, const T & el2)
{
  return el1 > el2 ? el1 : el2;
}

/* ROTATIONS*/
template <typename K, typename O, typename C>
void 
BinarySearchTree<K,O,C>::rotateWithLeftChild(BinaryNode * & k2)
{
  BinaryNode *k1 = k2->left;
  k2->left = k1->right;
  k1->right = k2;
  k2->height = BinarySearchTree<K,O,C>::max(height(k2->left), 
                                            height(k2->right)) + 1;
  k1->height = BinarySearchTree<K,O,C>::max(height(k1->left), 
                                            height(k2)) + 1;
  k2 = k1;
}

template <typename K, typename O, typename C>
void 
BinarySearchTree<K,O,C>::rotateWithRightChild(BinaryNode * & k1)
{

  BinaryNode *k2 = k1->right;
  
  k1->right = k2->left;
  k2->left = k1;

  k1->height = BinarySearchTree<K,O,C>::max(height(k1->left), 
                                            height(k1->right)) + 1;
  k2->height = BinarySearchTree<K,O,C>::max(height(k2->right), 
                                            height(k1)) + 1;
  k1 = k2;
}

template <typename K, typename O, typename C>
void 
BinarySearchTree<K,O,C>::doubleWithLeftChild(BinaryNode * & k3)
{
  rotateWithRightChild(k3->left);
  rotateWithLeftChild(k3);
}

template <typename K, typename O, typename C>
void 
BinarySearchTree<K,O,C>::doubleWithRightChild(BinaryNode * & k1)
{
  rotateWithLeftChild(k1->right);
  rotateWithRightChild(k1);
}

/* ITERATOR functions */

// dummy constructor
template <typename K, typename O, typename C>
BinarySearchTree<K,O,C>::Iterator::Iterator( ) 
  : current(NULL), root(NULL), useStack(false)
{
}

// dereferencing operator non-const version
template <typename K, typename O, typename C>
O &
BinarySearchTree<K,O,C>::Iterator::operator*( )
{
  return this->current->data;
}

// dereferencing operator const version
template <typename K, typename O, typename C>
const O & 
BinarySearchTree<K,O,C>::Iterator::operator*( ) const
{
  return this->current->data; 
}

// compare Iterators ignoring useStack var
template <typename K, typename O, typename C>
bool 
BinarySearchTree<K,O,C>::Iterator::
operator==(const Iterator & rhs) const
{ 
  return current == rhs.current && 
         root == rhs.root; 
}

// compare Iterators ignoring useStack var
template <typename K, typename O, typename C>
bool 
BinarySearchTree<K,O,C>::Iterator::
operator!=(const Iterator & rhs) const
{ 
  return !(*this == rhs); 
}

// increment Iterator to point to the inorder next
// node of then-current node, in case that no further
// advances are possible return an Iterator that is
// equal to end( )
template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::Iterator &
BinarySearchTree<K,O,C>::Iterator::operator++()
{   
    if(current==NULL) return *this;


  if(useStack==false){
    current=NULL;
    return *this;
  }
  if(current->right==NULL){
    if(s.empty()){
      current=NULL;
      return *this;
    }
    BinaryNode *tmp=s.top();
    s.pop();
    current=tmp;
    return *this;
  }else{
    BinaryNode* node=current->right;
    while(node->left!=NULL){
      s.push(node);
      node=node->left;
    }
    current=node;
    return *this;
  }
}

/* real Iterator constructor will be invoked by 
 * BST member function only. if no inorder iterator
 * is required by the computation designer should 
 * explicitly set useStack variable to false, o.w.
 * it will be assumed to be true. 
 */
template <typename K, typename O, typename C>
BinarySearchTree<K,O,C>::Iterator::
Iterator(BinaryNode * p, const BinarySearchTree & rhs, bool stk)
{

  if(p==NULL){
    current=NULL;
    root=rhs.root;
    useStack=stk;
    return;
  }
  if(stk){
    useStack=stk;
    root=rhs.root;
    BinaryNode* node=p;
    while(node->left!=NULL){
      s.push(node);
      node=node->left;
    }
    current=node;
  }else{
    current=p;
    root=rhs.root;
    useStack=stk;
  }
}


#endif

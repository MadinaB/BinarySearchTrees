//
// Implementation
//
template <typename E>					// constructor
  AVLTree<E>::AVLTree() : ST() { }

template <typename E>					// node height utility
  int AVLTree<E>::height(const TPos& v) const
    { return (v.isExternal() ? 0 : (*v).height()); }

template <typename E>					// set height utility
  void AVLTree<E>::setHeight(TPos v) {
    int hl = height(v.left());
    int hr = height(v.right());
    (*v).setHeight(1 + std::max(hl, hr));			// max of left & right
  }

template <typename E>					// is v balanced?
  bool AVLTree<E>::isBalanced(const TPos& v) const {	
    int bal = height(v.left()) - height(v.right());
    return ((-1 <= bal) && (bal <= 1));
  }

template <typename E>					// get tallest grandchild
  typename AVLTree<E>::TPos AVLTree<E>::tallGrandchild(const TPos& z) const {
    TPos zl = z.left();
    TPos zr = z.right();
    if (height(zl) >= height(zr))			// left child taller
      if (height(zl.left()) >= height(zl.right()))
        return zl.left();
      else
        return zl.right();
    else 						// right child taller
      if (height(zr.right()) >= height(zr.left()))
        return zr.right();
      else
        return zr.left();
  }


//
// ToDo
//

template <typename E>					// remove key k entry
  void AVLTree<E>::erase(const K& k) {
    
    TPos v = this->finder(k, ST::root()); 
    if (Iterator(v) == ST::end()){
        std::cout<<("Erase of nonexistent")<<std::endl; return; }
    TPos w = this->eraser(v); 
    rebalance(w);
  }

template <typename E>					// insert (k,x)
  typename AVLTree<E>::Iterator AVLTree<E>::insert(const K& k, const V& x) {
    
    TPos v = this->inserter(k, x); 
    setHeight(v); 
    rebalance(v);
    return Iterator(v);
    
  }
  
template <typename E>					// rebalancing utility
  void AVLTree<E>::rebalance(const TPos& v) {
    TPos z = v;
    while (!(z == ST::root())) {
        z = z.parent(); 
        setHeight(z);
        if (!isBalanced(z)) {
            TPos x = tallGrandchild(z); 
            z = restructure(x);

            setHeight(z.left()); 
            setHeight(z.right()); 
            setHeight(z);
        }
    }
  }

template <typename E>				// Binary Search Tree Rotation
  typename AVLTree<E>::TPos AVLTree<E>::restructure(const TPos& v)  {
    TPos temp, x, y, z, k, T1, T2, T3, T4;
    
    x = v.v;
    y = v.v->par;
    z = v.v->par->par;
    k = v.v->par->par->par;

    /*  derived from page 442: restructure(x) */
    /*
    
    Input: 
    A node x of a binary search tree T that has both a parent y and a grand-
    parent z

    Output: Tree T after a trinode restructuring (which corresponds to a single or
    double rotation) involving nodes x, y, and z

    1: Let (a,b,c) be a left-to-right (inorder) listing of the nodes x, y, and z, 
    and let (T0,T1,T2,T3) be a left-to-right (inorder) listing of the four subtrees of x, y, 
    and z not rooted at x, y, or z.
    2: Replace the subtree rooted at z with a new subtree rooted at b.
    3: Let a be the left child of b and let T0 and T1 be the left and right subtrees of a,
    respectively.
    4: Let c be the rightchild of b and let T2 and T3 be the left and right subtrees of c,
    respectively.
    
    */
    if( x == y.left() && y == z.left() ){
        T2 = y.v->right;
        //step 1
        if(k.v->left == z.v){
            k.v->left = y.v;
            k.v->left->par = k.v;
        }
        else{   
            k.v->right = y.v;
            k.v->right->par = k.v;
        }
        //step 2
        z.v->left = T2.v;
        z.v->left->par = z.v;
        //step 3
        y.v->right = z.v;
        y.v->right->par = y.v;

        temp =y;
    }
    else if( x == y.right() && y == z.right() ){
        T2 = y.v->left;
        //step 1
        if(k.v->left == z.v){
            k.v->left = y.v;
            k.v->left->par = k.v;
        }
        else{   
            k.v->right = y.v;
            k.v->right->par = k.v;
        }

        //step 2
        z.v->right = T2.v;
        z.v->right->par = z.v;
    
        //step 3
        y.v->left = z.v;
        y.v->left->par = y.v;

        temp =y;
   }
    else if( x == y.left() && y == z.right() ){
        T2 = x.v -> left;
        T3 = x.v -> right;

        //step 1
        if(k.v->left == z.v){
            k.v->left = x.v;
            k.v->left->par = k.v;
        }
        else{   
            k.v->right = x.v;
            k.v->right->par = k.v;
        }
        //step 2
        z.v -> right = T2.v;
        z.v -> right ->par = z.v;

        y.v -> left = T3.v;
        y.v -> left ->par = y.v;
        
        //step 3
        x.v ->left = z.v;
        x.v ->left->par = x.v;

        x.v ->right = y.v;
        x.v ->right->par = x.v;

        temp = x;
    }
    else{ 
        T2 = x.v -> left;
        T3 = x.v -> right;

        //step 1
        if(k.v->left == z.v){
            k.v->left = x.v;
            k.v->left->par = k.v;
        }
        else{   
            k.v->right = x.v;
            k.v->right->par = k.v;
        }
        //step 2
        z.v -> left = T3.v;
        z.v -> left ->par = z.v;

        y.v -> right = T2.v;
        y.v -> right ->par = y.v;
        
        //step 3
        x.v ->left = y.v;
        x.v ->left->par = x.v;

        x.v ->right = z.v;
        x.v ->right->par = x.v;

        temp = x;
    }

return temp;

  }


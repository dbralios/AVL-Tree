#ifndef AVL_TREE_H_
#define AVL_TREE_H_
#include <stack>

template <class T>
class AvlTree {
private:
	template <class T>
	class AvlNode {
	public:
		friend AvlTree;
		AvlNode() : leftChild(nullptr), rightChild(nullptr), balance(0) {}
		AvlNode(T k) : leftChild(nullptr), rightChild(nullptr), balance(0), data(k) {}
	private:
		T data;
		short balance;
		AvlNode<T> *leftChild, *rightChild;
	};
	AvlNode<T> *root;

	void updatePathFactors(AvlNode<T> *cur, const T& k);

	void LLRotation(AvlNode<T> *A, const T& k);
	void RRRotation(AvlNode<T> *A, const T& k);
	void LRRotation(AvlNode<T> *A, const T& k);
	void RLRotation(AvlNode<T> *A, const T& k);

	void R0(AvlNode<T> *A);
	void R1(AvlNode<T> *A);
	void Rn1(AvlNode<T> *A);

	void L0(AvlNode<T> *A);
	void L1(AvlNode<T> *A);
	void Ln1(AvlNode<T> *A);

	void RightRemoveRotation(AvlNode<T> *A, bool & prevHeightDecreased);
	void LeftRemoveRotation(AvlNode<T> *A, bool & prevHeightDecreased);

	void Clear(AvlNode<T> *n);

public:
	AvlTree() : root(nullptr) {}
	~AvlTree() {
		Clear(root);
		root = nullptr;
	}

	void Clear();
	bool Find(const T& k);
	void Insert(const T& k);
	void Remove(const T& k);
};

template <class T>
void AvlTree<T>::updatePathFactors(AvlNode<T> *cur, const T& k) {
	// Update balance factors in path that all were 0 after adding k
	while (cur != nullptr)
		if (k < cur->data) {
			cur->balance++, cur = cur->leftChild;
		}
		else if (k > cur->data) {
			cur->balance--, cur = cur->rightChild;
		}
		else {
			break;
		}
}

template <class T>
void AvlTree<T>::LLRotation(AvlNode<T> *A, const T& k) {
	AvlNode<T> *B = A->leftChild;
	AvlNode<T> *rB = B->rightChild, *lB = B->leftChild, *rA = A->rightChild;

	A->leftChild = lB;
	A->rightChild = B;
	B->leftChild = rB;
	B->rightChild = rA;

	std::swap(A->data, B->data);
	std::swap(A, B);

	A->balance = 0, B->balance = 0;
	// Update balances in B->left
	updatePathFactors(B->leftChild, k);
}

template <class T>
void AvlTree<T>::RRRotation(AvlNode<T> *A, const T& k) {
	AvlNode<T> *B = A->rightChild;
	AvlNode<T> *rB = B->rightChild, *lB = B->leftChild, *lA = A->leftChild;

	A->rightChild = rB;
	A->leftChild = B;
	B->leftChild = lA;
	B->rightChild = lB;

	std::swap(A->data, B->data);
	std::swap(A, B);

	A->balance = 0, B->balance = 0;
	// Update balances in B->right
	updatePathFactors(B->rightChild, k);
}

template <class T>
void AvlTree<T>::LRRotation(AvlNode<T> *A, const T& k) {
	AvlNode<T> *B = A->leftChild, *C = B->rightChild;
	AvlNode<T> *rA = A->rightChild, *lC = C->leftChild, *rC = C->rightChild;

	// Compute unbalances in C subtree
	updatePathFactors(C, k);
	int b = C->balance;

	A->rightChild = C;
	B->rightChild = lC;
	C->leftChild = rC;
	C->rightChild = rA;

	std::swap(A->data, C->data);
	std::swap(A, C);

	C->balance = 0;
	// Update balance factors of A and B
	if (b == 0) {
		B->balance = 0, A->balance = 0;
	}
	else if (b == 1) {
		B->balance = 0, A->balance = -1;
	}
	else if (b == -1) {
		B->balance = 1, A->balance = 0;
	}
}

template <class T>
void AvlTree<T>::RLRotation(AvlNode<T> *A, const T& k) {
	AvlNode<T> *B = A->rightChild, *C = B->leftChild;
	AvlNode<T> *lA = A->leftChild, *lC = C->leftChild, *rC = C->rightChild;

	// Compute unbalances in C subtree
	updatePathFactors(C, k);
	int b = C->balance;

	A->leftChild = C;
	B->leftChild = rC;
	C->leftChild = lA;
	C->rightChild = lC;

	std::swap(A->data, C->data);
	std::swap(A, C);

	C->balance = 0;
	// Update balance factors of A and B
	if (b == 0) {
		A->balance = 0, B->balance = 0;
	}
	else if (b == 1) {
		A->balance = 0, B->balance = -1;
	}
	else if (b == -1) {
		A->balance = 1, B->balance = 0;
	}
}


template <class T>
void AvlTree<T>::R0(AvlNode<T> *A) {
	AvlNode<T> *B = A->leftChild;
	AvlNode<T> *rB = B->rightChild, *lB = B->leftChild, *rA = A->rightChild;
	A->leftChild = lB;
	A->rightChild = B;
	B->leftChild = rB;
	B->rightChild = rA;

	std::swap(A->data, B->data);
	std::swap(A, B);

	A->balance = 1, B->balance = -1;
}

template <class T>
void AvlTree<T>::R1(AvlNode<T> *A) {
	AvlNode<T> *B = A->leftChild;
	AvlNode<T> *rB = B->rightChild, *lB = B->leftChild, *rA = A->rightChild;
	A->leftChild = lB;
	A->rightChild = B;
	B->leftChild = rB;
	B->rightChild = rA;

	std::swap(A->data, B->data);
	std::swap(A, B);

	A->balance = 0, B->balance = 0;
}

template <class T>
void AvlTree<T>::Rn1(AvlNode<T> *A) {
	AvlNode<T> *B = A->leftChild;
	AvlNode<T> *C = B->rightChild;
	AvlNode<T> *rA = A->rightChild, *lC = C->leftChild, *rC = C->rightChild;

	// Compute unbalaces in C subtree
	int b = C->balance;

	A->rightChild = C;
	B->rightChild = lC;
	C->leftChild = rC;
	C->rightChild = rA;

	std::swap(A->data, C->data);
	std::swap(A, C);

	C->balance = 0;
	// Update balance factors of A and B
	if (b == 0) {
		B->balance = 0, A->balance = 0;
	}
	else if (b == 1) {
		B->balance = 0, A->balance = -1;
	}
	else if (b == -1) {
		B->balance = 1, A->balance = 0;
	}
}


template <class T>
void AvlTree<T>::L0(AvlNode<T> *A) {
	AvlNode<T> *B = A->leftChild;
	AvlNode<T> *rB = B->rightChild, *lB = B->leftChild, *lA = A->leftChild;
	A->rightChild = rB;
	A->leftChild = B;
	B->leftChild = lA;
	B->rightChild = lB;

	std::swap(A->data, B->data);
	std::swap(A, B);

	A->balance = -1, B->balance = 1;
}

template <class T>
void AvlTree<T>::L1(AvlNode<T> *A) {
	AvlNode<T> *B = A->leftChild;
	AvlNode<T> *rB = B->rightChild, *lB = B->leftChild, *lA = A->leftChild;
	A->rightChild = rB;
	A->leftChild = B;
	B->leftChild = lA;
	B->rightChild = lB;

	std::swap(A->data, B->data);
	std::swap(A, B);

	A->balance = 0, B->balance = 0;
}

template <class T>
void AvlTree<T>::Ln1(AvlNode<T> *A) {
	AvlNode<T> *B = A->leftChild;
	AvlNode<T> *C = B->rightChild;
	AvlNode<T> *lA = A->leftChild, *lC = C->leftChild, *rC = C->rightChild;

	// Compute unbalaces in C subtree
	int b = C->balance;

	A->leftChild = C;
	B->leftChild = rC;
	C->leftChild = lA;
	C->rightChild = lC;

	std::swap(A->data, C->data);
	std::swap(A, C);

	C->balance = 0;
	// Update balance factors of A and B
	if (b == 0) {
		A->balance = 0, B->balance = 0;
	}
	else if (b == 1) {
		A->balance = 0, B->balance = -1;
	}
	else if (b == -1) {
		A->balance = 1, B->balance = 0;
	}
}


template <class T>
void AvlTree<T>::RightRemoveRotation(AvlNode<T> *A, bool & prevHeightDecreased) {
	AvlNode<T> *B = A->leftChild;
	switch (B->balance) {
	case 0: R0(A);
		break;
	case 1: prevHeightDecreased = true; R1(A);
		break;
	case -1: prevHeightDecreased = true; Rn1(A);
		break;
	}
}

template <class T>
void AvlTree<T>::LeftRemoveRotation(AvlNode<T> *A, bool & prevHeightDecreased) {
	AvlNode<T> *B = A->leftChild;
	switch (B->balance) {
	case 0: L0(A);
		break;
	case 1: prevHeightDecreased = true; L1(A);
		break;
	case -1: prevHeightDecreased = true; Ln1(A);
		break;
	}
}


template <class T>
void AvlTree<T>::Clear(AvlNode<T> *n) {
	if (n == nullptr)
		return;
	Clear(n->leftChild);
	Clear(n->rightChild);
	delete n;
}

template <class T>
void AvlTree<T>::Clear() {
	clear(root);
	root = nullptr;
}

template <class T>
bool AvlTree<T>::Find(const T& k) {
	AvlNode<T> *cur = root;
	while (cur != nullptr) {
		if (k < cur->data) {
			cur = cur->leftChild;
		}
		else if (k > cur->data) {
			cur = cur->rightChild;
		}
		else {
			return true;
		}
	}
	return false;
}

template <class T>
void AvlTree<T>::Insert(const T& k) {
	AvlNode<T> *cur = root, *curParent = nullptr;
	AvlNode<T> *A = nullptr; // Last node in the insert path with balance factor 1 or -1
	while (cur != nullptr) {
		curParent = cur;
		if (cur->balance != 0) {
			A = cur;
		}

		if (k < cur->data) {
			cur = cur->leftChild;
		}
		else if (k > cur->data) {
			cur = cur->rightChild;
		}
		else {
			return; 
		}
	}

	AvlNode<T> *n = new AvlNode<T>(k);
	if (root != nullptr) {
		if (k < curParent->data) {
			curParent->leftChild = n;
		}
		else {
			curParent->rightChild = n;
		}
	}
	else {
		root = n;
	}

	// Rotate if needed and update balance factors
	if (A == nullptr) {
		updatePathFactors(root, k);
		return;
	}
	if (A->balance == 1) {
		if (k < A->data) { 
			if ((A->leftChild)->data > k) {
				LLRotation(A, k);
			}
			else {
				LRRotation(A, k);
			}
		}
		else {
			updatePathFactors(A, k); 
		}
	}
	else if (A->balance == -1) {
		if (k > A->data) { 
			if ((A->rightChild)->data < k) {
				RRRotation(A, k);
			}
			else {
				RLRotation(A, k);
			}
		}
		else {
			updatePathFactors(A, k); 
		}
	}
}

template <class T>
void AvlTree<T>::Remove(const T& k) {
	std::stack<AvlNode<T>*> path; // Save the path to the node that is to be deleted
	AvlNode<T> *cur = root, *curParent = nullptr;

	while (cur != nullptr && cur->data != k) {
		curParent = cur;
		path.push(curParent);

		if (k < cur->data) 	{
			cur = cur->leftChild;
		}
		else {
			cur = cur->rightChild;
		}
	}
	if (cur == nullptr) {
		return; 
	}

	// Node has two children
	if (cur->leftChild != nullptr && cur->rightChild != nullptr) {
		// Rotate with max in left sub-tree and convert to one child case
		AvlNode<T> *s = cur->leftChild, *sParent = cur;
		path.push(sParent);

		while (s->rightChild != nullptr) {
			sParent = s;
			path.push(sParent);
			s = s->rightChild;
		}
		cur->data = s->data;
		cur = s;
		curParent = sParent;
	}

	// One or no child
	AvlNode<T> *curChild;
	if (cur->leftChild != nullptr) {
		curChild = cur->leftChild;
	}
	else {
		curChild = cur->rightChild;
	}

	if (cur == root) {
		root = curChild;
	}
	else {
		if (cur->data > curParent->data)  {
			curParent->rightChild = curChild;
		}
		else if (cur->data < curParent->data) {
			curParent->leftChild = curChild;
		}
	}

	// Ascend the path, balancing the tree and update balance factors
	AvlNode<T> *A = cur, *prev;
	bool prevHeightDecreased = true;

	while (!path.empty() && prevHeightDecreased) {
		prev = A;
		A = path.top();
		path.pop();

		// Update balance factor
		if (A->data > prev->data) {
			A->balance--;
		}
		else {
			A->balance++;
		}

		// Rotate if needed
		switch (A->balance) {
		case 0: prevHeightDecreased = true; 
			break;
		case 1: prevHeightDecreased = false;
			break;
		case -1: prevHeightDecreased = false;
			break;
		case 2: RightRemoveRotation(A, prevHeightDecreased); 
			break;
		case -2: LeftRemoveRotation(A, prevHeightDecreased); 
			break;
		}
	}

	// Delete cur now because we might have to access it in the loop
	delete cur;
}

#endif
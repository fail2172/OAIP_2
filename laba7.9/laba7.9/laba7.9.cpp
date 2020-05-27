#include <iostream>
#include <conio.h>
#include <string>
using namespace std;
int quantity_of_knot = 0;
struct Tree {
	int key;
	string number;
	Tree* right, * left;
}*root;
Tree* create_list(int key) {
	Tree* p = new Tree;
	p->key = key;
	cout << "Введите номер телефона : ";
	cin.ignore();
	getline(cin, p->number);
	p->right = p->left = NULL;
	return p;
}
void create_knot(Tree* root,int key) {
	Tree* prev=NULL, * p;
	p = root;
	bool find = true;
	while (p && find) {
		prev = p;
		if (p->key == key) find = false;
		else {
			if (key < p->key)p = p->left;
			else p = p->right;
		}
	}
	if (find) {
		p = create_list(key);
		if (key < prev->key)prev->left = p;
		else prev->right = p;
	}
}
void view_1(Tree* p,int level) {
	if (p) {
		view_1(p->right, level + 1);
		for (int i = 0; i < level; i++)cout << "       ";
		cout << p->key << "-" << p->number << endl << endl;
		view_1(p->left, level + 1);
	}
}
void view_2(Tree* p) {
	if (p) {
		view_2(p->left);
		cout << p->key << "-" << p->number << endl;
		view_2(p->right);
	}
}
void tree_to_arr(Tree* p, Tree* t) {
	if (p) {
		tree_to_arr(p->left, t);
		t[quantity_of_knot].key = p->key;
		t[quantity_of_knot].number = p->number;
		quantity_of_knot++;
		tree_to_arr(p->right, t);
	}
}
void del_tree(Tree* p) {
	if (p != NULL) {
		del_tree(p->right);
		del_tree(p->left);
		delete p;
	}
}
void balans_tree(Tree** p, int n, int k,Tree* new_tree) {
	if (n == k) {
		*p = NULL;
		return;
	}
	else {
		int m = (n + k) / 2;
		*p = new Tree;
		(*p)->key = new_tree[m].key;
		(*p)->number = new_tree[m].number;
		balans_tree(&(*p)->left, n, m, new_tree);
		balans_tree(&(*p)->right, m + 1, k, new_tree);
	}
}
void balans() {
	Tree* new_tree = new Tree[100];
	tree_to_arr(root, new_tree);
	del_tree(root);
	balans_tree(&root, 0, quantity_of_knot, new_tree);
	quantity_of_knot = 0;
}
void find(Tree* p,int key) {
	while (p != NULL && p->key != key) {
		if (key > p->key)p = p->right;
		else p = p->left;
	}
	if (p == NULL) {
		puts("Узел не найден!");
		return;
	}
	cout << "Искомый номер : " << p->number;
}
Tree* del_knot(Tree* root, int key) {
	Tree* del, * prev_del = NULL, * r, * prev_r;
	del = root;
	while (del != NULL && del->key != key) {
		prev_del = del;
		if (key > del->key)del = del->right;
		else del = del->left;
	}
	if (del == NULL) {
		puts("Узел не найден!");
		return root;
	}
	if (del->right == NULL)r = del->left;
	else
		if (del->left == NULL)r = del->right;
		else {
			prev_r = del;
			r = del->left;
			while (r->right != NULL) {
				prev_r = r;
				r = r->right;
			}
			if (prev_r == del)r->right = del->right;
			else {
				r->right = del->right;
				prev_r->right = r->left;
				r->left = prev_r;
			}
		}
	if (del == root)root = r;
	else
		if (del->key > prev_del->key)prev_del->right = r;
		else prev_del->left = r;
	delete del;
	return root;
}
void count_knots(Tree* p) {
	if (p) {
		if (p->right != NULL && p->left == NULL)
			quantity_of_knot++;
		if (p->right == NULL && p->left != NULL)
			quantity_of_knot++;
		count_knots(p->right);
		count_knots(p->left);
	}
}
char select_function() {
	char fun;
	puts("Добавление узла : a\nПросмотр дерева : b\nСбалансировать дерево : c\nПросмотреть узел : d\nУдалить узел : e\nПосчитать количество узлов с одним потомком : f\nЗавершение работы : x");
	puts("--------------------------");
	cin >> fun;
	return fun;
}
void logics() {
	int key;
	while (true) {
		switch (select_function()) {
		case 'a':
			puts("Введите индефикационный номер : ");
			cin >> key;
			if (root == NULL)root = create_list(key);
			else create_knot(root, key); break;
		case 'b':
			int view;
			puts("1 - Просмотреть деревом\n2 - Просмотреть списком");
			cin >> view;
			if(view==1)
				view_1(root, 0);
			if(view==2)
				view_2(root); break;
		case 'c':balans(); break;
		case 'd':
			puts("Введите индефикационный номер : ");
			cin >> key;
			find(root, key);break;
		case 'e':
			puts("Введите индефикационный номер : ");
			cin >> key;
			root = del_knot(root, key);
			break;
		case 'f':
			count_knots(root);
			cout <<"Количество узлов, имеющих од ного сына : "<< quantity_of_knot;
			quantity_of_knot = 0;
			break;
		case 'x':return;
		default:puts("\nНекорректный ввод данных...");
		}puts("\nНажмите любую клавишу, чтобы продолжить...");
		_getch(); system("cls");
	}
}
int main() {
	setlocale(LC_ALL, "ru");
	logics();
}
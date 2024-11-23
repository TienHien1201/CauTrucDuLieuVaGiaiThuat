#include<iostream>
using namespace std;
#include<fstream>

// Khởi tạo cây nhị phân tìm kiếm các số nguyên
// khai báo cấu trúc 1 cái node
struct node
{
	int data;
	node* pLeft;
	node* pRight;
};
typedef struct node NODE;
typedef NODE* TREE;

// hàm thêm node vào cây
void ThemNode(node*& t, int x)
{
	if (t == NULL)
	{
		NODE* p = new NODE;
		p->data = x;
		p->pLeft = NULL;
		p->pRight = NULL;
		t = p;
	}
	else
	{
		// thêm node p sang bên nhánh trái
		if (x < t->data)
		{
			ThemNode(t->pLeft, x);
		}
		else if (x > t->data)
		{
			ThemNode(t->pRight, x);
		}
	}
}

// duyệt NLR
void NLR(node* t)
{
	if (t != NULL)
	{
		cout << t->data << "  ";
		NLR(t->pLeft);
		NLR(t->pRight);
	}
}

// duyệt NRL
void NRL(node* t)
{
	if (t != NULL)
	{
		cout << t->data << "  ";
		NRL(t->pRight);
		NRL(t->pLeft);
	}
}


// duyệt LNR
void LNR(node* t)
{
	if (t != NULL)
	{
		LNR(t->pLeft);
		cout << t->data << "  ";
		LNR(t->pRight);
	}
}
// duyệt RNL
void RNL(node* t)
{
	if (t != NULL)
	{
		RNL(t->pRight);
		cout << t->data << "  ";
		RNL(t->pLeft);
	}
}

// duyệt LRN
void LRN(node* t)
{
	if (t != NULL)
	{
		LRN(t->pLeft);
		LRN(t->pRight);
		cout << t->data << "  ";
	}
}

// duyệt RLN
void RLN(node* t)
{
	if (t != NULL)
	{
		RLN(t->pRight);
		RLN(t->pLeft);
		cout << t->data << "  ";
	}
}

// hàm đọc file
void Doc_File(node*& t, ifstream& filein)
{
	int n;
	filein >> n;
	for (int i = 1; i <= n; i++)
	{
		int x;
		filein >> x;
		ThemNode(t, x);
	}
}

// hàm đọc file
void Doc_File_1(node*& t, ifstream& filein)
{
	while (true)
	{
		int x;
		filein >> x;
		ThemNode(t, x);
		char c;
		filein >> c;
		if (filein.eof() == true)
		{
			break;
		}
	}
}

// hàm xuất các node lá
void Xuat_Node_La(node* t)
{
	if (t != NULL)
	{
		// xử lý cái node hiện tại
		if (t->pLeft == NULL && t->pRight == NULL)
		{
			cout << t->data << "  ";
		}
		Xuat_Node_La(t->pLeft);
		Xuat_Node_La(t->pRight);
	}
}

// hàm xuất các node có 1 con
void Xuat_Node_1_Con(node* t)
{
	if (t != NULL)
	{
		// xử lý cái node hiện tại
		if ((t->pLeft != NULL && t->pRight == NULL) || (t->pLeft == NULL && t->pRight != NULL))
		{
			cout << t->data << "  ";
		}
		Xuat_Node_1_Con(t->pLeft);
		Xuat_Node_1_Con(t->pRight);
	}
}

void Xuat_Node_2_Con(node* t)
{
	if (t != NULL)
	{
		// xử lý cái node hiện tại
		if (t->pLeft != NULL && t->pRight != NULL)
		{
			cout << t->data << "  ";
		}
		Xuat_Node_2_Con(t->pLeft);
		Xuat_Node_2_Con(t->pRight);
	}
}

// tìm phần tử lớn nhất của cây
int Tim_Max(node* t)
{
	if (t->pRight != NULL)
	{
		Tim_Max(t->pRight);
	}
	else
	{
		return t->data;
	}
}

int main()
{
	node* t;
	t = NULL; // khởi tạo cây

	/*ifstream filein;
	filein.open("INPUT.TXT", ios_base::in);
	Doc_File(t, filein);*/

	ifstream filein;
	filein.open("INPUT_1.TXT", ios_base::in);
	Doc_File_1(t, filein);

	cout << "\nXuat cay theo dang NLR: ";
	NLR(t);

	cout << "\nNODE LA: ";
	Xuat_Node_La(t);
	cout << "\nNODE 1 CON: ";
	Xuat_Node_1_Con(t);
	cout << "\nNODE 2 CON: ";
	Xuat_Node_2_Con(t);
	cout << "\nMAX: " << Tim_Max(t);

	filein.close();


	system("pause");
	return 0;
}
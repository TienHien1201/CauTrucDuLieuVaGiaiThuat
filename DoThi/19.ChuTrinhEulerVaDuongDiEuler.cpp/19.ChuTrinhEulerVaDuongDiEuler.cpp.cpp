//====================== TÌM CHU TRÌNH VÀ ĐƯỜNG ĐI EULER =======================================
#if 0
#include <iostream>
#include<set>
#include<stack>
#include<vector>
using namespace std;

/*Bài toán tìm chu trình Euler của dồ thị vô hướng(vô hướng là trường hợp tổng quát còn có hướng thì ở input ta chỉ insert y vào danh
sách kề của x là ra đồ thị có hướng)
input: n đỉnh = 5, m cạnh = 6 | output: 
6 cạnh là:                    |  Chu trình và đường đi Euler là: 1 2 4 5 2 3 1
           1 2                | 
		   2 3                |
		   3 1                |
		   2 4                |
		   4 5                |
		   2 5                | 
		                                   */
const int maxn = 20;
int n, m;
int degree[maxn];//Tính số bán bậc các đỉnh của đồ thị để chứng minh đồ thị là Euler
set<int> adj[maxn];//Dùng danh sách set để lưu danh sách kề của các đỉnh

void nhap() {
	cout << "Nhap n dinh va m canh va dinh xuat phat cua do thi: \n";
	cin >> n >> m;

	cout << "Nhap vao hai dinh x y ao thanh canh cua do thi va trong so cua hai dinh x va y: \n";
	for (int i = 0; i < m; i++) {
		int x, y; cin >> x >> y;
		adj[x].insert(y);
		adj[y].insert(x);

		//Tính số bán bậc của các đỉnh trong đồ thị
		degree[x]++;
		degree[y]++;
	}
}

void Euler(int v) {
	stack<int> st;//Stack đê chứa các đỉnh kề với đỉnh vừa đc lấy ở đầu stack
	vector<int> EC;//Ec là danh sách chứa các đỉnh của chu trình Euler
	st.push(v);//Thêm đỉnh vừa đc truyền vào hàm Euler vào Stack

	//Xét danh sách stack xem có còn phần tử không
	while (!st.empty()) {
		int x = st.top();//Lấy đỉnh ở đầu stack ra 
		if (adj[x].size() != 0)//Nếu danh kề của đỉnh vừa đc lấy ra ở đầu stack mà còn đỉnh kề với đỉnh vừa đc lấy ra ở đầu stack 
		{
			int y = *adj[x].begin();//Cho y là đỉnh đầu tiên kề với đỉnh x(là đỉnh vừa đc lấy ra ở đầu stack)
			st.push(y);/*Đưa đỉnh đầu tiên kề với đỉnh vừa đc lấy ra ở đầu stack vào stack*/

			/*Xóa cạnh (x,y) vì là đồ thị vô hướng nên xóa 2 chiều.Vì chu trình Euler là chu trình đi qua mõi cạnh 1 lần nên cạnh nào
			đi qua rồi ta xóa luôn*/
			adj[x].erase(y);
			adj[y].erase(x);

		}
		else//Ngược lại nếu Nếu danh kề của đỉnh vừa đc lấy ra ở đầu stack mà không còn đỉnh kề với đỉnh vừa đc lấy ra ở đầu stack
		{
			st.pop();/*Xóa đỉnh vừa lấy ra ở đầu stack ra khỏi stack vì danh sách kề của đỉnh vừa đc lấy ra ở đầu tack duyệt dsach kề
				mà rỗng tức đỉnh vừa đc lấy ra ở đầu stack đã đc duyệt xong và xóa khỏi stack luôn.*/
			EC.push_back(x);
		}

	}
	cout << "Chu trinh va duong di Euler cua do thi la: ";
	reverse(begin(EC), end(EC));
	for(int x: EC){
		cout << x << " ";
	}

}

int main()
{
	nhap();
	Euler(1);

}

#endif // 0




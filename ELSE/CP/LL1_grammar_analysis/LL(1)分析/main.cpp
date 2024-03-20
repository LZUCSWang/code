/*�����ǿ��Ժ���ֱ����ݹ���ķ�����!�����*/
/*
��������:
	3
	E->E+T|T
	T->T*F|F
	F->(E)|i
	i+i*i

��
	7
	E->TA
	A->+E|!
	T->FB
	B->T|!
	F->PC
	C->*C|!
	P->(E)|a|b|^
	a*b+b

*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <stack>
#include <set>
#include <map>

const int N = 100;

//���ķ�����
struct Grammar
{
	char vn = 'A';
	int cnt = 0;
	std::string vt[10];
}grammat[N];
//��FIRST����
struct First
{
	std::string st = "";
	int cnt = 0;
	std::set<char> ed;
}first[N];
//��FOLLOW����
struct Follow
{
	char st = 'A';
	int cnt = 0;
	std::set<char> ed;
}follow[N];

int h[N], e[N], ne[N], idx_all;//������FOLLOW��������ͼ
int a[N][N];//���ݵ�i������ĵ�j���жϵ�ǰ��first�����ڽṹ�������е�λ��
int num = 0, num_1 = 0, n = 0;//num�ǹ�������������num_1��first���ϵ�����
std::set<char> Vt, Vn, V; //Vt�ս���ţ� Vn���ս���ţ� V���з���
std::map<std::string, int> mp1;//�����ַ�����ѯ�Ը��ַ��������first�����ڽṹ�������е�λ�ã���a[N][N]Ӧ���ظ����壬���Դ����ת��
std::map<char, int> mp2, mp3;//�ս���ŵĲ�ѯ�����ս���ŵĲ�ѯ
std::vector<std::vector<std::string>> table(N, std::vector<std::string>(N, "")); //LL_table��
std::string ss[N]; //������ݹ��������¹���



void add(int a, int b) {
	e[idx_all] = b, ne[idx_all] = h[a], h[a] = idx_all++;
}

bool dfs_first(char t, int idx_i, int idx_j) {
	int x = a[idx_i][idx_j];
	if (Vt.count(t)) {		
		first[x].ed.insert(t); 
		return false;
	}
	else {
		bool flag = false;
		for (int i = 0; i < num; i++) {
			char vn = grammat[i].vn;
			int cnt = grammat[i].cnt;
			if (vn == t) {
				for (int j = 0; j < cnt; j++) {
					char tt = grammat[i].vt[j][0];
					if (tt == '!') {
						flag = true;
					}
					else {
						dfs_first(tt, idx_i, idx_j);
					}
				}
				break;
			}
		}
		return flag;
	}
}
void print1(std::stack<char> s) {
	std::string ans;
	while (s.size()) {
		ans += s.top();
		s.pop();
	}
	reverse(ans.begin(), ans.end());
	std::cout << ans;
}
void print2(std::stack<char> s) {
	std::string ans;
	while (s.size()) {
		ans += s.top();
		s.pop();
	}
	std::cout << ans;
}
void input_new_rules() {
	memset(h, -1, sizeof h);	
	for (int i = 0; i < n; i ++ )  {
		std::string s = ss[i];
		int st = 0, ed = 0;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '-' && s[i + 1] == '>') {
				grammat[num].vn = s[i - 1];
				Vn.insert(s[i - 1]);
				st = i + 1;
				i = i + 1;
			}
			else {
				if (s[i] == '|' || i == s.size() - 1) {
					if (s[i] == '|') {
						ed = i - 1;
					}
					else ed = (int)s.size();
					std::string tmp = s.substr(st + 1, ed - st);
					int cntt = grammat[num].cnt;
					grammat[num].vt[cntt] = tmp;
					grammat[num].cnt++;
					if (i == s.size() - 1) V.insert(s[i]);
					else {
						st = i;
					}
				}
				else V.insert(s[i]);
			}
		}
		num++;
	}
	for (auto t : V) {
		if (!Vn.count(t)) Vt.insert(t);
	}
}
void solve_first() {
	//������Ҳ��ַ�����FIRST����
	for (int i = 0; i < num; i++) {
		int cnt = grammat[i].cnt;
		for (int j = 0; j < cnt; j++) {
			std::string right = grammat[i].vt[j];
			mp1[right] = num_1;
			a[i][j] = num_1;
			first[num_1].st = right;
			for (int k = 0; k < right.size(); k++) {
				if (!dfs_first(right[k], i, j)) break;
			}
			num_1++;
		}
	}

	//�����Ҳ���������ַ���FIRST����
	for (int i = 0; i < num; i++) {
		int cnt = grammat[i].cnt;

		first[num_1].st = grammat[i].vn;
		mp1[first[num_1].st] = num_1;

		for (int j = 0; j < cnt; j++) {
			std::string right = grammat[i].vt[j];
			int backup = mp1[right];
			std::set<char> tmp = first[backup].ed;
			first[num_1].ed.insert(tmp.begin(), tmp.end());
		}
		num_1++;
	}
}
void solve_follow() {
	//��������ս���ŵ�FOLLOW���ϣ���������FIRST���ϣ�ͨ����ѯ�������У�������������FOLLOW���ϣ���һ���ߣ��ɱ�������ָ�������
	for (int i = 0; i < num; i++) {
		char t = grammat[i].vn;
		follow[i].st = t;
		mp3[t] = i;
		//�ķ���ʼ�������#
		if (!i) {
			follow[i].ed.insert('#');
			follow[i].cnt++;
		}
		//ö�����й���
		for (int j = 0; j < num; j++) {
			int cntt = grammat[j].cnt;
			for (int k = 0; k < cntt; k++) {
				std::string right = grammat[j].vt[k];
				int idxx = (int)right.find(t);
				//�����а������ַ�
				if (idxx != -1) {
					//���ַ��������
					if (idxx != right.size() - 1) {
						//������ս������ֱ�����
						if (Vt.count(right[idxx + 1])) {
							follow[i].ed.insert(right[idxx + 1]);
							follow[i].cnt++;
						}
						//���ս���������FIRST����
						else {
							std::string hh = std::string(1, right[idxx + 1]);
							int idx_x = mp1[hh];
							std::set<char> set_tmp = first[idx_x].ed;
							follow[i].ed.insert(set_tmp.begin(), set_tmp.end());
							//���FIRST�������ɿգ�����������FOLLOW���ϣ���������ߣ�����ɾ�������еĿշ���
							if (set_tmp.count('!')) {
								follow[i].ed.erase('!');
								add(j, i);//i�ǵ�ǰ�����ķ��ս���� j�ǵ�ǰ����
							}
						}
					}
					//�������������FOLLOW���ϣ���ӱ�
					else {
						add(j, i);
					}
				}
			}
		}
	}

	//ͨ��bfs������ͼ�������������
	std::queue<int> q;
	//�����еĵ���ӽ�����
	for (int i = 0; i < num; i++) {
		q.push(i);
	}
	//ֻҪ���в��գ�ȡ����ͷ
	while (q.size()) {
		int t = q.front();
		q.pop();
		//������ǰ�������ĵ㣬���������ļ��ϲ����Լ��ļ���
		for (int i = h[t]; i != -1; i = ne[i]) {
			int j = e[i];
			std::set<char> check_backup = follow[j].ed;
			follow[j].ed.insert(follow[t].ed.begin(), follow[t].ed.end());
			//����������֮ǰû�ı䣬��ʾ��ǰ���Ѿ�����������Ҫ��ӽ����У���֮�ӽ�����
			if (follow[j].ed != check_backup) {
				q.push(j);
			}
		}
	}
}
void output_first_and_follow() {
	std::cout << "FIRST���ϣ� \n";
	for (int i = 0; i < num_1; i++) {
		std::cout << "FIRST(" << first[i].st << "):  { ";
		for (auto t : first[i].ed) std::cout << t << ", ";
		std::cout << "}\n";
	}
	std::cout << "***********************************\n";

	std::cout << "FOLLOW���ϣ�\n";
	for (int i = 0; i < num; i++) {
		std::cout << "FOLLOW(" << follow[i].st << "):  { ";
		for (auto t : follow[i].ed) std::cout << t << ", ";
		std::cout << "}\n";
	}
	std::cout << "***********************************\n";

}
void output_LL_table() {
	//�����ս���ű�ɾ���շ��ţ�����#
	std::set<char> Vtt = Vt;
	Vtt.insert('#');
	Vtt.erase('!');
	int h = 0;
	//�ս��ַ����±�
	for (auto t : Vtt) {
		mp2[t] = h;
		h++;
	}

	//��ʼ��table��
	int n = (int)Vn.size();
	int m = (int)Vtt.size();

	//ö��ÿһ������ ������Ҳ���FIRST���ϣ���table����Ӧλ�����Ϲ���
	//��FIRST���ϰ����շ��ţ�������󲿵�FOLLOW���ϣ���table������Ӧλ�����Ϲ���
	for (int i = 0; i < num; i++) {
		int cnt = grammat[i].cnt;
		char left = grammat[i].vn;
		for (int j = 0; j < cnt; j++) {
			std::string right = grammat[i].vt[j];
			int idxx = mp1[right];
			std::set<char> tmp = first[idxx].ed;
			for (auto t : tmp) {
				int x = i;
				int y = mp2[t];
				table[x][y] = right;
			}
			if (tmp.count('!')) {
				tmp = follow[mp3[left]].ed;
				for (auto t : tmp) {
					int x = i;
					int y = mp2[t];
					table[x][y] = right;
				}
			}
		}
	}
	//���LL_table��
	std::cout << "LL(1)������ \n";
	for (auto t : Vtt) std::cout << "\t " << t;
	std::cout << "\n";
	for (int i = 0; i < n; i++) {
		std::cout << grammat[i].vn << "\t";
		for (int j = 0; j < m; j++) {
			if (table[i][j] != "") std::cout << grammat[i].vn << "::=" << table[i][j] << "\t";
			else std::cout << table[i][j] << "\t";
		}
		std::cout << "\n";
	}
	std::cout << "***********************************\n";

}

void quiry() {
	std::string quiry_s;
	std::cout << "��������Ҫ�жϵ��ַ����� \n";
	std::cin >> quiry_s;
	std::cout << "***********************************\n������������\n";

	//��ʼ������ջbegin����������ջend
	std::stack<char> begin, end;
	begin.push('#');
	begin.push(grammat[0].vn);
	end.push('#');
	for (int i = (int)quiry_s.size() - 1; i >= 0; i--) {
		end.push(quiry_s[i]);
	}
	//��ƥ��ʧ�ܻ���ƥ����ɽ���
	bool error_flag = true;
	while (error_flag && end.size()) {
		//ȡ������ջ��ջ��Ԫ�ز���ӡ
		char a = begin.top();
		char b = end.top();
		print1(begin);
		std::cout << "\t";
		print2(end);
		std::cout << "\t";
		begin.pop();

		//ջ��Ԫ�ز����
		if (a != b) {
			//ȡ��ջ��Ԫ�ض�Ӧ���±꣬����table
			int x = mp3[a];
			int y = mp2[b];
			//���tableΪ�գ���ʾ�����ó����ʾ���ж�
			if (table[x][y] == "") {
				error_flag = false;
				break;
			}
			//�����ʾ����ջջ��Ԫ�ؿ����滻Ϊ�����ַ��������ַ�����Ϊ�գ�������������ջ�У��ַ���Ϊ�գ�������
			else {
				std::string table_t = table[x][y];
				std::cout << table_t << "\n";
				if (table_t == "!") continue;
				for (int i = (int)table_t.size() - 1; i >= 0; i--) {
					begin.push(table_t[i]);
				}
			}
		}
		//���ջ��Ԫ����ȣ����ʾ��������ջ��������һ��Ԫ�أ���������ջ����ջ��Ԫ��
		else {
			std::cout << "\n";
			end.pop();
		}
	}
	std::cout << "***********************************\n";
	if (error_flag) std::cout << "success! �þ������ķ�������ľ��ӣ�\n";
	else std::cout << "fail! �þ��Ӳ����ķ�������ľ��ӣ�\n";
	std::cout << "***********************************\n";

}
void solve_left_recurrence(){
	std::cout << "�������ķ���������� n ��";
	std::cin >> n;
	int cnt = 0;
	while (cnt < n) {
		std::cout << "������� " << cnt + 1 << "������ \n";
		std::cin >> ss[cnt];		
		cnt++;
	}
	std::cout << "***********************************\n";
	for (int i = 0; i < n; i++) {
		std::string s = ss[i];
		for (int j = 0; j < s.size(); j++) {
			if (s[j] == '-' && s[j + 1] == '>') {
				Vn.insert(s[j - 1]);				
				j = j + 1;
			}
			else {
				if (s[j] != '|') {
					V.insert(s[j]);
				}
			}
		}
	}
	for (auto t : V) {
		if (!Vn.count(t)) Vt.insert(t);
	}
	int num = cnt;
	for (int i = 0; i < num; i++) {
		std::string s = ss[i];
		char vn = 'A';
		int st = 0, ed = 0;
		std::set<std::string> mid1, mid2;
		bool flag = false;
		for (int j = 0; j < (int)s.size(); j++) {
			if (s[j] == '-' && s[j + 1] == '>') {
				vn = s[j - 1];
				st = j + 1;
				j = j + 1;

			}
			else {
				if (s[j] == '|' || j == s.size() - 1) {
					if (s[j] == '|') {
						ed = j - 1;
					}
					else ed = (int)s.size();
					std::string tmp = s.substr(st + 1, ed - st);
					if (tmp[0] == vn) {
						flag = true;
						mid1.insert(tmp.substr(1));
					}
					else {
						mid2.insert(tmp);
					}
					if (j != s.size() - 1) st = j;
					
				}
			}
		}
		if (flag) {
			n += 1;
			char tmpp = 'A';
			bool flagg = false;
			for (char op = 'A'; op <= 'Z'; op++) {
				if (!V.count(op)) {
					tmpp = op;
					V.insert(op);
					flagg = true;
					break;
				}
			}
			if (flag == false) {
				std::cout << "���Ų����ã�\n";
				exit(0);
			}
			else {
				std::string new_rule1 = "";
				for (auto t : mid2) {
					if (new_rule1 == "") new_rule1 = std::string(1, vn) + "->" + t + std::string(1, tmpp);
					else {
						new_rule1 = new_rule1 + "|" + t + std::string(1, tmpp);
					}
				}
				ss[i] = new_rule1;
				std::string new_rule2 = "";
				for (auto t : mid1) {
					if (new_rule2 == "") new_rule2 = std::string(1, tmpp) + "->" + t + std::string(1, tmpp);
					else {
						new_rule2 = new_rule2 + "|" + t + std::string(1, tmpp);
					}
				}
				new_rule2 += "|!";
				ss[cnt++] = new_rule2;
			}
		}
	}
	std::cout << "��������ֱ����ݹ������ķ����� \n";
	for (int i = 0; i < n; i++) {
		std::cout << ss[i] << "\n";
	}
	std::cout << "***********************************\n";

}
int main()
{
	//������ݹ�
	solve_left_recurrence();
	//���봦��
	input_new_rules();
	//��FIRST����
	solve_first();
	//��FOLLOW����
	solve_follow();
	//���FIRST���Ϻ�FOLLOW����
	output_first_and_follow();
	//���LL_table��
	output_LL_table();
	//��ѯ�������Ƿ�Ϊ��LL(1)�ķ�
	quiry();	
	//����
	return 0;
}
#include "compiler.h"
using namespace std;
const int width = 30;
#define form 1//控制输出格式
int line;
string source;//存储源代码
vector<string> keywords = {//C语言中的保留字
    "char", "bool", "double", "float", "int", "long", "short", "signed", "unsigned", "auto", "break", "case", "const", "continue", "default", "do", "else", "enum", "extern",
    "for", "goto", "if", "register", "return",  "sizeof", "static","struct", "switch", "typedef", "union",  "void", "volatile", "while", "main", "printf", "write", "read"
};

vector<char> filter = {//过滤符
    ' ', '\t', '\r', '\n'
};
vector<char> delimiter = {//分隔符
    '(', ')', '[', ']', '{', '}', '\'', ';', ','
};
vector<char> singleoperator = {
    '+', '-', '*', '/', '<', '>', '=', '^', '&', '|', '%', '~', '\?', ':', '!'
};
vector<string> doubleoperator = {
    "+=", "-=", "*=", "/=", "%=", "<<", ">>", "<=", ">=", "==", "!=", "==", "!=", "++", "--", "&&", "||", ":="
};

template<class T>
int exist(vector<T> &v, T &c)
{
    for (int i = 0; i < v.size(); ++i)
    {
        if (c == v[i])
            return i + 1;
    }
    return 0;
}

map<string, int> tokens;//记录标识符
void analyse(ofstream &fout)//词法分析
{
    int i = 0, len = source.size();
    while (i < len)
    {
        if (exist(filter, source[i]))//去掉空白字符
        {
            while (i < len && exist(filter, source[i]))
            {
                ++i;
            }
        }
        else if (source[i] == '#')//预处理相关的内容暂时不处理
        {
            while (i < len && source[i] != '\n')
            {
                ++i;
            }
            ++i;
        }
        else if (source[i] == '/' && (i + 1 < len) && source[i + 1] == '/')//处理注释
        {
            i += 2;
            while (i < len)
            {
                if (source[i] == '\n')
                {
                   ++i;
                   break; 
                }
                ++i;
            }
        }
        else if (source[i] == '/' && (i + 1 < len) && source[i + 1] == '*')//处理注释
        {
            i += 2;
            while (i < len)
            { 
                if (source[i] == '*' && i + 1 < len && source[i + 1] == '/')
                {
                    i += 2;
                    break;
                }
                ++i;
            }
        }
        else if (isalpha(source[i]) || source[i] == '_')//字母或下划线开头
        {
            string token;
            while (i < len && (isalpha(source[i]) || isdigit(source[i])))
            {
                token += source[i];
                ++i;
            }
            int syn = exist(keywords, token);
            if (syn == 0)//标识符
            {
                int id = tokens[token];
                if (id == 0)//新的标识符
                {
                    id = tokens.size();
                    tokens[token] = id;
                }
                string ans = "<" + token + ", identifier" + to_string(id) + ">";
                if (form == 2)
                {
                    cout << setw(width) << ans;
                    fout << setw(width) << ans;
                    if (line++ % 2)
                    {
                        cout << endl;
                        fout << endl;
                    }
                }
                else if (form == 1)
                {
                    cout << ans << endl;
                    fout << ans << endl;
                }
            }
            else//关键字
            {
                string ans;
                if (syn >= 1 && syn <= 9)
                    ans = "<" + token + ", data_type>";
                else
                    ans = "<" + token + ", keyword>";
                if (form == 2)
                {
                    cout << setw(width) << ans;
                    fout << setw(width) << ans;
                    if (line++ % 2)
                    {
                        cout << endl;
                        fout << endl;
                    }
                }
                else if (form == 1)
                {
                    cout << ans << endl;
                    fout << ans << endl;
                }
            }
        }
        else if (isdigit(source[i]) || source[i] == '-' && (i + 1 < len) && isdigit(source[i + 1]))// 处理常数
        {
            string token;
            int f_float = 0;//是否为浮点数
            if (source[i] == '-')
            {
                token += '-';
                ++i;
            }
            while (i < len && (isdigit(source[i]) || source[i] == '.'))
            {
                token += source[i];
                if (source[i] == '.')
                {
                    ++f_float;
                }
                ++i;
            }
            if (f_float == 0)//整形
            {
                string ans = "<" + token + ", integer>";
                if (form == 2)
                {
                    cout << setw(width - 1) << ans;
                    fout << setw(width - 1) << ans;
                    if (line++ % 2)
                    {
                        cout << endl;
                        fout << endl;
                    }
                }
                else if (form == 1)
                {
                    cout << ans << endl;
                    fout << ans << endl;
                }
                
            }
            else if (f_float == 1)//浮点数
            {
                string ans = "<" + token + ", float>";
                if (form == 2)
                {
                    cout << setw(width) << ans;
                    fout << setw(width) << ans;
                    if (line++ % 2)
                    {
                        cout << endl;
                        fout << endl;
                    }
                }
                else if (form == 1)
                {
                    cout << ans << endl;
                    fout << ans << endl;
                }
            }
            else
            {
                cout << "数字" << token << "不合法\n";
                fout << "数字" << token << "不合法\n";
                fout.close();
                exit(0);
            }
        }
        else if (source[i] == '\"')//处理字符串
        {
            string token = "\"";
            ++i;
            while (i < len)
            {
                token += source[i];
                ++i;
                if (source[i - 1] == '\"')
                    break;
            }
            if (token[token.size() - 1] != '\"')
            {
                cout << "字符串不合法，缺少一个引号\n";
                fout << "字符串不合法，缺少一个引号\n";
                fout.close();
                exit(0);
            }
            string ans = "<" + token + ", string>";
            if (form == 2)
            {
                cout << setw(width) << ans;
                fout << setw(width) << ans;
                if (line++ % 2)
                {
                    cout << endl;
                    fout << endl;
                }
            }
            else if (form == 1)
            {
                cout << ans << endl;
                fout << ans << endl;
            }
            
        }
        else if (exist(delimiter, source[i]))//分隔符
        {
            string t(1, source[i]);
            string ans = "<" + t + ", delimiter>";
            if (form == 2)
            {
                cout << setw(width) << ans;
                fout << setw(width) << ans;
                if (line++ % 2)
                {
                    cout << endl;
                    fout << endl;
                } 
            }
            else if (form == 1)
            {
                cout << ans << endl;
                fout << ans << endl;
            }
            ++i;
        }
        else if (exist(singleoperator, source[i]))
        {
            string token;
            token += source[i];
            ++i;
            if (i < len)
            {
                token += source[i];
                if (exist(doubleoperator, token))
                {
                    ++i;
                }
                else
                {
                    token = token[0];
                }
            }
            string ans = "<" + token + ", op>";
            if (form == 2)
            {
                cout << setw(width) << ans;
                fout << setw(width) << ans;
                if (line++ % 2)
                {
                    cout << endl;
                    fout << endl;
                }
            }
            else if (form == 1)
            {
                cout << ans << endl;
                fout << ans << endl;
            }
        }
        else
        {
            cout << source[i] << "无法识别的字符\n";
            fout << source[i] << "无法识别的字符\n";
            fout.close();
            exit(0);
        }
    }
}

int lexical()
{
    int T;
    ofstream fout("output6.txt", ios::out);
    if (!fout.is_open())
    {
        cout << "写入文件打不开";
        exit(0);
    }
    cout << "欢迎使用词法分析器，请选择输入方式：" << endl;
    cout << "1:从文件中输入\t" << "2:从终端中输入\t" << "3:退出" << endl;
    while (cin >> T && T != 1 && T != 2 && T != 3)
    {
        cout << "请重新选择（1或2）" << endl;
    }
    if (T == 1)
    {
        ifstream fin("input6.txt", ios::in);
        if (!fin.is_open())
        {
            cout << "文件打不开" << endl;
            exit(0);
        }
        string buf;
        while (getline(fin, buf))
        {
            source += buf;
            source += '\n';
        }
        fin.close();
    }
    else if (T == 2)
    {
        cout << "请输入C语言程序，注意程序要以'$'结尾" << endl;
        char ch;
        cin.get(ch);//读掉上一个回车
        while (cin.get(ch) && ch != '$')
        {
            source += ch;
        }
    }
    else
    {
        exit(0);
    }
//    cout << source;
    cout.setf(ios::left);
    fout.setf(ios::left);
    analyse(fout);
    fout.close();
    return 0;
}
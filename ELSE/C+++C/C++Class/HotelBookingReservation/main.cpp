#include <bits/stdc++.h>
using namespace std;
class client
{
public:
    static int c_id_count; // 统计客户数量
    int cost_cnt;          // 统计客户花费
    char c_type;           // 客户类型
    virtual void check()
    {
        fstream fin;                                                         // 定义文件流
        fin.open("E:/HotelBookingReservation/client.csv", ios::in);          // 打开文件
        int target_phn, phn, count = 0;                                      // 定义变量
        cout << "Enter the phone number of the client to display details: "; // 提示输入
        cin >> target_phn;                                                   // 输入
        vector<string> row;                                                  // 定义vector
        string line, word;                                                   // 定义string
        while (fin >> line)                                                  // 读取文件
        {
            row.clear();                  // 清空vector
            stringstream s(line);         // 定义string流
            while (getline(s, word, ',')) // 按照逗号分割
            {
                row.push_back(word); // 将分割后的数据存入vector
            }
            phn = atoi(row[2].c_str()); // 将string转换为int
            if (target_phn == phn)      // 判断是否为目标客户
            {
                count = 1;                               // 标记找到客户
                cout << "Client ID: " << row[0] << "\n"; // 输出客户ID
                cout << "Name: " << row[1] << "\n";      // 输出客户姓名
                cout << "Phone No: " << row[2] << "\n";  // 输出客户电话号码
                cout << "Address: " << row[3] << "\n";   // 输出客户地址
                cout << "NID: " << row[4] << "\n";       // 输出客户身份证号
                break;
            }
        }
        fin.close(); // 关闭文件
        if (count == 0)
            cout << "Record not found\n";
    }
    // 虚函数，用于更新客户信息
    virtual int update()
    {
        fstream fout;                                                            // 定义文件流
        fout.open("E:/HotelBookingReservation/client.csv", ios::out | ios::app); // 打开文件
        int c_id;                                                                // 定义变量
        string c_name;
        string c_phone_no;
        string c_address;
        string c_nid;
        cout << "Enter Client ID:";       // 提示输入
        cin >> c_id;                      // 输入
        cout << endl                      // 输出
             << "Enter Client Name:";     // 提示输入
        cin >> c_name;                    // 输入
        cout << endl                      // 输出
             << "Enter Client Phone No:"; // 提示输入
        cin >> c_phone_no;                // 输入
        cout << endl                      // 输出
             << "Enter Client Address:";  // 提示输入
        cin >> c_address;                 // 输入
        cout << endl                      // 输出
             << "Enter Client NID:";      // 提示输入
        cin >> c_nid;                     // 输入
        // 将客户信息写入文件
        fout << c_id << ","
             << c_name << ","
             << c_phone_no << ","
             << c_address << ","
             << c_nid << "\n";
        fout.close(); // 关闭文件
        return 0;
    }
};
class client_hotelroom : virtual public client // 虚继承client类，解决菱形问题
{
public:
    // 虚函数，用于检查酒店房间是否空闲
    void check()
    {
        ifstream inf("E:/HotelBookingReservation/hotelroom.txt"); // 定义文件流
        if (!inf)                                                 // 判断文件是否打开
            cout << endl
                 << "Unable to open hotelroom file" << endl; // 输出文件打开失败
        int room_id;
        string room_type;
        string room_book;
        cout << endl
             << "hotelrooms to book:" << endl; // 输出提示要预订的房间
        while (!inf.eof())                     // 判断文件是否结束
        {
            inf >> room_id >> room_type >> room_book;        // 读取文件
            if (room_book == "NULL")                         // 判断房间是否空闲
                cout << room_id << " " << room_type << endl; // 输出空闲房间
        }
        inf.close(); // 关闭文件
    }
    // 虚函数，用于预订酒店房间
    int update()
    {
        // 输入要预订的房间号和ID
        int target_room_id, c_id;
        cout << "Please enter the required room id:";
        cin >> target_room_id;
        cout << "Please enter the client id:";
        cin >> c_id;
        // 将int类型的c_id转换为string类型的client_id
        string client_id;
        stringstream ss;
        ss << c_id;
        client_id = ss.str();
        // 打开文件
        ifstream inf("E:/HotelBookingReservation/hotelroom.txt");
        ofstream outf("E:/HotelBookingReservation/hotelroom1.txt");
        // 检查文件是否打开
        if (!inf)
            cout << endl
                 << "Unable to open hotelroom file" << endl;
        int room_id;
        string room_type;
        string room_book;
        // 读取文件
        while (!inf.eof()) // 判断文件是否结束
        {
            inf >> room_id >> room_type >> room_book; // 读取文件
            if (room_id == target_room_id)            // 判断是否是要预订的房间
            {
                cost_cnt += 1000;                                                // 计算客户的花费
                cout << room_id << " " << room_type << endl;                     // 输出要预订的房间
                outf << room_id << " " << room_type << " " << client_id << endl; // 将房间号和ID写入新文件
            }
            else // 如果不是要预订的房间
            {
                outf << room_id << " " << room_type << " " << room_book << endl; // 将房间号和ID写入新文件
            }
        }
        // 关闭文件
        outf.close();
        inf.close();
        // 删除旧文件，重命名新文件
        remove("E:/HotelBookingReservation/hotelroom.txt");
        rename("E:/HotelBookingReservation/hotelroom1.txt", "E:/HotelBookingReservation/hotelroom.txt");
        // 返回客户的花费
        return cost_cnt;
    }
    // 虚函数，用于退房
    void checkout()
    {
        // 输入要退房的房间号和ID
        int c_id;
        cout << "Please enter the client id:"; // 输入客户ID
        cin >> c_id;                           // 输入客户ID
        string client_id;
        stringstream ss;
        ss << c_id;           // 将int类型的c_id转换为string类型的client_id
        client_id = ss.str(); // 将int类型的c_id转换为string类型的client_id
        // 打开文件
        ifstream inf("E:/HotelBookingReservation/hotelroom.txt");
        ofstream outf("E:/HotelBookingReservation/hotelroom1.txt");
        if (!inf) // 检查文件是否打开
            cout << endl
                 << "Unable to open hotelroom file" << endl;
        int room_id;
        string room_type;
        string room_book;
        while (true) // 读取文件
        {
            inf >> room_id >> room_type >> room_book;
            if (inf.eof()) // 判断文件是否结束
                break;
            if (room_book == client_id) // 判断是否是要退房的房间
            {
                cout << room_id << " " << room_type << endl; // 输出要退房的房间
                outf << room_id << " " << room_type << " "
                     << "NULL" << endl; // 将房间号和ID写入新文件
            }
            else // 如果不是要退房的房间
            {
                outf << room_id << " " << room_type << " " << room_book << endl; // 将房间号和ID写入新文件
            }
        }
        // 关闭文件
        outf.close();
        inf.close();
        //  删除旧文件，重命名新文件
        remove("hotelroom.txt");
        rename("hotelroom1.txt", "hotelroom.txt");
    }
    virtual void display_cost(){}; // 虚函数，用于显示客户的花费
};
// 会议厅继承客户类
class client_conventionhall : virtual public client
{
public:
    void check() // 检查会议厅是否空闲
    {
        // 打开文件
        ifstream inf("E:/HotelBookingReservation/conventionhall.txt");
        if (!inf) // 检查文件是否打开
            cout << endl
                 << "Unable to open conventionhall file" << endl;
        string day, time, hall_book, target_day, target_time, res = "Not booked"; // res 是结果
        cout << endl
             << "Please enter the date(Ex: 23/05/2019):"; // 输入日期
        cin >> target_day;
        cout << endl
             << "Please enter the time(07:00 / 11:00):"; // 输入时间
        cin >> target_time;
        while (!inf.eof()) // 读取文件
        {
            inf >> day >> time >> hall_book;                        // 读取文件
            cout << day << " " << time << " " << hall_book << endl; // 输出文件
            if (day == target_day && time == target_time)           // 判断是否是要预定的时间
                res = "booked";                                     // 如果是要预定的时间，结果改为booked
        }
        cout << endl         // 输出结果
             << res << endl; // 输出结果
        inf.close();         // 关闭文件
    }
    int update() // 更新会议厅预定
    {
        string target_day, target_time;                          // 目标日期和时间
        int c_id;                                                // 客户ID
        cout << "Please enter the required date:";               // 输入日期
        cin >> target_day;                                       // 输入日期
        cout << "Please enter the required time:";               // 输入时间
        cin >> target_time;                                      // 输入时间
        cout << "Please enter the client id:";                   // 输入客户ID
        cin >> c_id;                                             // 输入客户ID
        cost_cnt += 20000;                                       // 会议厅费用
        ofstream outf("conventionhall.txt", ios::app);           // 打开文件
        outf << endl                                             // 写入文件
             << target_day << " " << target_time << " " << c_id; // 写入文件
        outf.close();                                            // 关闭文件
        return cost_cnt;                                         // 返回费用
    }
    virtual void display_cost(){}; // 虚函数
};
class client_restaurant : virtual public client // 餐厅继承客户类
{
public:
    void check() // 检查餐厅是否预定
    {
        ifstream inf("E:/HotelBookingReservation/restaurant.txt");               // 打开文件
        if (!inf)                                                                // 检查文件是否打开
            cout << endl                                                         // 输出错误信息
                 << "Unable to open restaurant file" << endl;                    // 输出错误信息
        string day, time, res_book, target_day, target_time, res = "Not booked"; // res 是结果
        cout << endl                                                             // 输出提示信息
             << "Please enter the date(Ex: 23/05/2019):";                        // 输出提示信息
        cin >> target_day;                                                       // 输入日期
        cout << endl                                                             // 输出提示信息
             << "Please enter the time(Ex: 07:00):";                             // 输出提示信息
        cin >> target_time;                                                      // 输入时间
        while (!inf.eof())                                                       // 读取文件
        {
            inf >> day >> time >> res_book;                        // 读取文件
            cout << day << " " << time << " " << res_book << endl; // 输出文件
            if (day == target_day && time == target_time)          // 判断是否是要预定的时间
                res = "booked";                                    // 如果是要预定的时间，结果改为booked
        }
        cout << endl         // 输出结果
             << res << endl; // 输出结果
        inf.close();         // 关闭文件
    }
    int update() // 预定餐厅
    {
        string target_day, target_time;            // 目标日期和时间
        int c_id;                                  // 客户ID
        cout << "Please enter the required date:"; // 输入日期
        cin >> target_day;                         // 输入日期
        cout << "Please enter the required time:"; // 输入时间
        cin >> target_time;                        // 输入时间
        cout << "Please enter the client id:";     // 输入客户ID
        cin >> c_id;                               // 输入客户ID
        cost_cnt += 200;                           // 餐厅费用
        ofstream outf("restaurant.txt", ios::app); // 打开文件
        outf << endl
             << target_day << " " << target_time << " " << c_id; // 写入文件
        outf.close();                                            // 关闭文件
        return cost_cnt;                                         // 返回费用
    }
    virtual void display_cost(){};
};
class cost : public client_conventionhall, public client_hotelroom, public client_restaurant // 费用类继承客户类
{
public:
    //
    void check() {}             // 检查
    int update() { return 0; }  // 更新
    void display_cost(int cost) // 显示费用
    {
        cout << endl
             << "Total cost:" << cost << endl; // 输出费用
        int paid;
        cout << endl
             << "Paid money:" << endl; // 输入支付金额
        cin >> paid;
        cout << endl
             << "Recievable change:" << paid - cost << endl; // 输出找零
    }
    cost operator-(cost c) // 重载减法运算符
    {
        cost c3;                                   // 创建新的费用对象
        c3.cost_cnt = c.cost_cnt - this->cost_cnt; // 计算费用
        return c3;                                 // 返回费用
    }
};
int main()
{
    client *bptr;              // 基类指针
    int t;                     // 选项
    client c1;                 // 基类对象
    client_conventionhall ch1; // 派生类对象
    client_hotelroom h1;       // 派生类对象
    client_restaurant r1;      // 派生类对象
    cost c2;                   // 派生类对象
    while (true)
    {
    // 输入选项
    A:
        cout << endl
             << "Type 1 to search for a client id" << endl // 查找客户id
             << "Type 2 to create a client id" << endl     // 创建客户id
             << "Type 0 end" << endl;                      // 输入0结束
        cin >> t;
        // 基类client指针获取到基类client对象的地址
        bptr = &c1;
        try // 异常处理
        {
            if (t == 1)
                // 登记操作
                bptr->check();
            else if (t == 2)
                // 更新操作
                bptr->update();
            else if (t == 0)
            {
            }
            else
                // 抛出异常
                throw(t);
        }
        catch (...) // 捕获异常
        {
            cout << endl
                 << "typed unavailable option"; // 输入不可用选项
            goto A;
        }
    // 输入选项
    B:
        cout << endl
             << "Type 1 to book a hotelroom" << endl        // 预定酒店房间
             << "Type 2 to book convention hall" << endl    // 预定会议厅
             << "Type 3 to reserve restaurant meal" << endl // 预定餐厅
             << "Type 4 to check out hotel room" << endl    // 退房
             << "Type 0 to end" << endl;                    // 输入0结束
        cin >> t;                                           // 输入选项
        try                                                 // 异常处理
        {
            if (t == 1)
            {
                bptr = &h1;                                          // 基类指针指向派生类对象
                bptr->cost_cnt = 0;                                  // 成员变量初始化
                bptr->check();                                       // 登记操作
                cout << endl                                         // 输出
                     << "Type 1 to checkin , Type 0 to not" << endl; // 输入1登记，输入0不登记
                cin >> t;                                            // 输入选项
                if (t)
                {
                    int i, d;
                    cout << endl
                         << "How many rooms do you need?" << endl; // 需要几间房
                    cin >> i;                                      // 输入房间数
                    while (i--)                                    // 循环
                        d = bptr->update();                        // 更新操作
                    c2.display_cost(d);                            // 显示费用
                }
            }
            else if (t == 2) // 预定会议厅
            {
                bptr = &ch1;                                      // 基类指针指向派生类对象
                bptr->cost_cnt = 0;                               // 成员变量初始化
                bptr->check();                                    // 登记操作
                cout << endl                                      // 输出
                     << "Type 1 to book , Type 0 to not" << endl; // 输入1登记，输入0不登记
                cin >> t;                                         // 输入选项
                if (t)
                    c2.display_cost(bptr->update()); // 显示费用
            }
            else if (t == 3) // 预定餐厅
            {
                bptr = &r1;                                       // 基类指针指向派生类对象
                bptr->cost_cnt = 0;                               // 成员变量初始化
                bptr->check();                                    // 登记操作
                cout << endl                                      // 输出
                     << "Type 1 to book , Type 0 to not" << endl; // 输入1登记，输入0不登记
                cin >> t;                                         // 输入选项
                if (t)
                    c2.display_cost(bptr->update()); // 显示费用
            }
            else if (t == 4) // 退房
            {
                h1.checkout(); // 结账
            }
            else if (t == 0)
            {
            }
            else
                throw(t); // 抛出异常
        }
        catch (...) // 捕获异常
        {
            cout << endl                        // 输出异常
                 << "typed unavailable option"; // 抛出异常
            goto B;                             // 跳转到B
        }
    }
}
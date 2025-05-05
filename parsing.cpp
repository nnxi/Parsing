#include <iostream>
#include <string>
using namespace std;

class Passing {  // �� ���޿�
public:
    double front;
    double end;
    int front_index;
    int end_index;
};

string firstcalc(string s);
double secondcalc(double front, double end, char c);
Passing div(string s, int index);

int main() {
    string s, temp;
    double result;

    while (1) {
        cout << "�Ʒ��� ������ �Է��ϼ���(x �Է� �� ����)" << "\n";
        getline(cin, s);

        if (s == "x")
            break;

        while (s.find(' ') != -1)  // ���� ����
            s.erase(s.find(' '), 1);

        temp = firstcalc(s);
        if (temp[0] == '-') {  // ������� ��ȣ ����� ���� �Ǽ��� ���� �� -1 ����
            temp.erase(0, 1);
            result = stod(temp) * -1;
        }
        else
            result = stod(temp);

        cout << "�� : " << result << "\n\n";
    }
}

string firstcalc(string s) {
    string temp;
    int st, en, middle;
    double t;
    Passing p;

    while (s.find('(') != -1) {  // ��ȣ�� �ִٸ� ���� ó��
        st = s.find('(');
        en = s.find(')', st);
        temp = firstcalc(s.substr(st + 1, en - st - 1));  // ��ȣ�� �����ϰ� ���ȣ��
        s.erase(st, en - st + 1);  // ��ȣ ���� ����
        s.insert(st, temp);  // ���� ������ ��ü
    }

    while (s.find('*') != -1 || s.find('/') != -1) {  // ������ �켱���� ���
        if (s.find('*') != -1) {
            middle = s.find('*');
            p = div(s, middle);
            t = secondcalc(p.front, p.end, '*');
        }
        else {
            middle = s.find('/');
            p = div(s, middle);
            t = secondcalc(p.front, p.end, '/');
        }

        s.erase(p.front_index, p.end_index - p.front_index + 1);  // ���� ������ ��ü
        s.insert(p.front_index, to_string(t));
    }

    while (s.find('+') != -1 || (s.find('-') != -1 && s.rfind('-') != 0)) {
        if (s.find("--") != -1) {
            middle = s.find("--");
            s.erase(middle, 2);
            s.insert(middle, "+");
        }

        if (s.find('+') != -1) {
            middle = s.find('+');
            p = div(s, middle);
            t = secondcalc(p.front, p.end, '+');
        }
        else if (s.find('-') != -1) {
            middle = s.find('-');
            p = div(s, middle);
            t = secondcalc(p.front, p.end, '-');
        }

        s.erase(p.front_index, p.end_index - p.front_index + 1);  // ���� ������ ��ü
        s.insert(p.front_index, to_string(t));
    }

    return s;
}

double secondcalc(double front, double end, char c) {  // ������ ���
    switch (c) {
    case '*':
        return front * end;
    case '/':
        return front / end;
    case '+':
        return front + end;
    case '-':
        return front - end;
    default:
        return 0;
    }
}

Passing div(string s, int index) {  // �־��� ������ ��ġ�� �߽����� �������� �ε��� ����
    Passing p;
    int st = index - 1;
    int en = index + 1;
    bool is_fminus = false;
    bool is_eminus = false;

    if (s[en] == '-') {  // ������ �� ��ȣ �Ǻ�
        is_eminus = true;
        en++;
    }

    while (st >= 0 && (isdigit(s[st]) || s[st] == '.')) {  // ���� ���� ���ڰų� .�̸� �ε��� ����
        st--;
    }

    if (st >= 0 && s[st] == '-') {  // ���� �� ��ȣ �Ǻ�
        if (st == 0)
            is_fminus = true;
        else if (!isdigit(s[st - 1]))
            is_fminus = true;
        st++;
    }
    else {
        st++;
    }

    while (en < s.length() && (isdigit(s[en]) || s[en] == '.')) {  // ������ �� �ε��� �̵�
        en++;
    }
    en--;

    p.front = stod(s.substr(st, index - st));  // ���� �� ����
    p.front_index = st;

    if (is_fminus) {  // ��ȣ�� �°� �� ����
        p.front *= -1;
        p.front_index--;
    }

    p.end_index = en;
    if (is_eminus) {
        p.end = stod(s.substr(index + 2, en - index - 1));
    }
    else {
        p.end = stod(s.substr(index + 1, en - index));
    }

    if (is_eminus) {  // ��ȣ�� �°� �� ����
        p.end *= -1;
    }

    return p;
}

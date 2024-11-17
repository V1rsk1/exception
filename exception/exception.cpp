﻿#include <iostream>
#include <stdexcept> // Для виключень
#include <Windows.h>
using namespace std;

class Time {
    int sec;
    int min;
    int hour;

    void normalize() {
        while (sec >= 60) {
            sec -= 60;
            min++;
        }
        while (sec < 0) {
            sec += 60;
            min--;
        }

        while (min >= 60) {
            min -= 60;
            hour++;
        }
        while (min < 0) {
            min += 60;
            hour--;
        }

        if (hour >= 24) hour %= 24;
        if (hour < 0) hour = 0;
    }

public:
    Time() : sec(0), min(0), hour(0) {}
    Time(int s, int m, int h) {
        if (s < 0 || m < 0 || h < 0)
            throw invalid_argument("Час не може містити від’ємні значення.");
        sec = s;
        min = m;
        hour = h;
        normalize();
    }

    Time(const Time& other) : sec(other.sec), min(other.min), hour(other.hour) {}

    Time& operator=(const Time& other) {
        if (this != &other) {
            sec = other.sec;
            min = other.min;
            hour = other.hour;
        }
        return *this;
    }

    Time& operator++() {
        sec++;
        normalize();
        return *this;
    }

    friend Time operator-(const Time& t1, const Time& t2) {
        if (t1 < t2)
            throw invalid_argument("Не можна відняти більший час від меншого.");
        Time result;
        result.sec = t1.sec - t2.sec;
        result.min = t1.min - t2.min;
        result.hour = t1.hour - t2.hour;
        result.normalize();
        return result;
    }

    bool operator==(const Time& t) const {
        return hour == t.hour && min == t.min && sec == t.sec;
    }

    bool operator!=(const Time& t) const {
        return !(*this == t);
    }

    bool operator>(const Time& t) const {
        return (hour > t.hour) || (hour == t.hour && min > t.min) || (hour == t.hour && min == t.min && sec > t.sec);
    }

    bool operator<(const Time& t) const {
        return !(*this > t || *this == t);
    }

    friend ostream& operator<<(ostream& output, const Time& t) {
        output << (t.hour < 10 ? "0" : "") << t.hour << ":"
            << (t.min < 10 ? "0" : "") << t.min << ":"
            << (t.sec < 10 ? "0" : "") << t.sec;
        return output;
    }

    friend istream& operator>>(istream& input, Time& t) {
        input >> t.hour;
        if (t.hour < 0 || t.hour >= 24)
            throw out_of_range("Година має бути в діапазоні [0, 23]");
        input.ignore(1);
        input >> t.min;
        if (t.min < 0 || t.min >= 60)
            throw out_of_range("Хвилини мають бути в діапазоні [0, 59]");
        input.ignore(1);
        input >> t.sec;
        if (t.sec < 0 || t.sec >= 60)
            throw out_of_range("Секунди мають бути в діапазоні [0, 59]");
        t.normalize();
        return input;
    }

    Time& operator+=(int s) {
        if (s < 0)
            throw invalid_argument("Не можна додати від’ємний час.");
        sec += s;
        normalize();
        return *this;
    }

    Time& operator-=(int s) {
        if (s < 0)
            throw invalid_argument("Не можна відняти від’ємний час.");
        sec -= s;
        normalize();
        return *this;
    }

    void operator()(int h, int m, int s) {
        if (h < 0 || m < 0 || s < 0)
            throw invalid_argument("Час не може містити від’ємні значення.");
        hour = h;
        min = m;
        sec = s;
        normalize();
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    try {
        Time t(1, 4, 6);
        ++t;
        cout << "Поточний час t: " << t << endl;

        Time t2(0, 3, 7);
        cout << "Різниця часу t - t2: " << t - t2 << endl;

        cout << (t > t2 ? "t більше за t2" : "t не більше за t2") << endl;
        cout << (t < t2 ? "t менше за t2" : "t не менше за t2") << endl;
        cout << (t == t2 ? "t дорівнює t2" : "t не дорівнює t2") << endl;
        cout << (t != t2 ? "t не дорівнює t2" : "t дорівнює t2") << endl;

        t -= 2;
        t2 += 7;
        cout << "Після зміни: t = " << t << ", t2 = " << t2 << endl;

    }
    catch (const invalid_argument& e) {
        cerr << "Помилка: " << e.what() << endl;
    }
    catch (const out_of_range& e) {
        cerr << "Помилка діапазону: " << e.what() << endl;
    }
    catch (...) {
        cerr << "Невідома помилка." << endl;
    }

    return 0;
}

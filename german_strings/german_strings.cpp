#include <iostream>
#include <cstring>
#include <string>

using namespace std;

class GermanString
{
private:
    uint32_t len;

    union
    {
        char inlineData[12];
        struct
        {
            uint32_t prefix;
            const char *ptr;
        } longRep;
    };

    void init(const char *s, uint32_t n)
    {
        len = n;

        if (n < 12)
        {
            memcpy(inlineData, s, n);
            inlineData[n] = '\0';
        }

        else
        {
            uint32_t p = 0;
            memcpy(&p, s, 4);
            longRep.prefix = p;

            char *buf = new char[n + 1];
            memcpy(buf, s, n);
            buf[n] = '\0';

            longRep.ptr = buf;
        }
    }

public:
    GermanString() : len(0) { inlineData[0] = '\0'; }

    GermanString(const char *s) { init(s, strlen(s)); }

    GermanString(const string &s) { init(s.data(), s.size()); }

    GermanString(const GermanString &other) { init(other.data(), other.size()); }

    ~GermanString()
    {
        if (len >= 12)
            delete[] longRep.ptr;
    }

    GermanString &operator=(const GermanString &other)
    {
        if (this != &other)
        {
            if (len >= 12)
                delete[] longRep.ptr;

            init(other.data(), other.size());
        }

        return *this;
    }

    bool operator==(const GermanString &other) const
    {
        if (len != other.len)
            return false;

        if (len < 12)
            return memcmp(inlineData, other.inlineData, len) == 0;

        if (longRep.prefix != other.longRep.prefix)
            return false;

        return memcmp(longRep.ptr, other.longRep.ptr, len) == 0;
    }

    char operator[](uint32_t index) const
    {
        if (len < 12)
            return inlineData[index];

        else
            return longRep.ptr[index];
    }

    uint32_t size() const
    {
        return len;
    }

    const char *data() const
    {
        return (len < 12 ? inlineData : longRep.ptr);
    }

    string toStdString() const
    {
        return string(data(), size());
    }

    bool empty() const
    {
        return len == 0;
    }
};

ostream &operator<<(ostream &os, const GermanString &gs)
{
    os << gs.data();
    return os;
}

int main()
{
    GermanString s1("Nikola");
    cout << "Short German String Test" << endl
         << s1 << endl
         << endl;

    GermanString s2("Nikola Peshevski");
    cout << "Long German String Test" << endl
         << s2 << endl
         << endl;

    GermanString s3 = s1;
    cout << "Copy Constructor Test" << endl
         << s3 << endl
         << endl;

    s3 = s2;
    cout << "Operator = Test" << endl
         << s3.data() << endl
         << endl;

    GermanString a("Test");
    GermanString b("Nikola");
    GermanString c("Nikola");

    cout << "Operator == Test" << endl;
    cout << "a == b ? " << (a == b ? "True" : "False") << endl;
    cout << "a == c ? " << (a == c ? "True" : "False") << endl;
    cout << "b == c ? " << (b == c ? "True" : "False") << endl;

    return 0;
}

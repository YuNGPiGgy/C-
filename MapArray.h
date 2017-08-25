#include <iterator>
#include <algorithm>
#include <utility>

using namespace std;

#ifndef MAPARRAY_H
#define MAPARRAY_H

template <typename key, typename T>

class MapArray
{
    int sz;
    pair <key, T> * buf;
public:
    struct iterator
    {
        //Iterator traits
        typedef random_access_iterator_tag iterator_category;
        typedef iterator self_type;
        typedef key key_type;
        typedef T mapped_type;
        typedef pair<key, T> value_type;
        typedef value_type& reference;
        typedef value_type* pointer;
        typedef ptrdiff_t difference_type;

        private:
            pointer buf;

        public:
            iterator(pointer ptr ) : buf(ptr) {}
            self_type operator ++ () {++buf; return *this;}
            self_type operator ++ (int postfix) {self_type cpy = *this; buf++; return cpy;}
            self_type operator -- () {--buf; return *this;}
            self_type operator -- (int postfix) {self_type cpy = *this; buf--; return cpy;}    
            reference  operator * () { return *buf; }
            pointer operator -> () { return buf; }
            bool operator == (const self_type& rhs) const {return buf == rhs.buf;}
            bool operator != (const self_type& rhs) const {return buf != rhs.buf;}
            bool operator < (const self_type& rhs) const {return buf->first< rhs.buf->first;}
            bool operator > (const self_type& rhs) const  {return buf->first> rhs.buf->first;}
            bool operator <= (const self_type& rhs) const {return *this < rhs || *this == rhs;}
            bool operator >= (const self_type& rhs) const {return *this > rhs|| *this == rhs;}
            self_type operator += (int i) {buf += i; return *this;}
            self_type operator + (int i) {self_type temp = *this; temp += i; return temp;}
            self_type operator -= (int i) {buf -= i; return *this;}
            self_type operator - (int i) {self_type temp = *this; temp -= i; return temp;}
    };
    
    class const_iterator
    {
        typedef random_access_iterator_tag iterator_category;
        typedef const_iterator self_type;
        typedef key key_type;
        typedef T mapped_type;
        typedef pair<key, T> value_type;
        typedef value_type& reference;
        typedef value_type* pointer;

        private:
            pointer buf;
            
        public:
            const_iterator(pointer ptr) : buf(ptr) {}
            self_type operator ++ () {++buf; return *this;}
            self_type operator ++ (int postfix) {self_type cpy = *this; buf++; return cpy;}
            self_type operator -- () {--buf; return *this;}
            self_type operator -- (int postfix) {self_type cpy = *this; buf--; return cpy;}    
            reference  operator * () { return *buf; }
            const pointer operator -> () { return buf; }
            bool operator == (const self_type& rhs) const {return buf == rhs.buf;}
            bool operator != (const self_type& rhs) const {return buf != rhs.buf;}
            bool operator < (const self_type& rhs) const {return buf->first< rhs.buf->first;}
            bool operator > (const self_type& rhs) const  {return buf->first> rhs.buf->first;}
            bool operator <= (const self_type& rhs) const {return *this < rhs || *this == rhs;}
            bool operator >= (const self_type& rhs) const {return *this > rhs || *this == rhs;}
            self_type operator += (int i) {buf += i; return *this;}
            self_type operator + (int i) {self_type temp = *this; temp += i; return temp;}
            self_type operator -= (int i) {buf -= i; return *this;}
            self_type operator - (int i) {self_type temp = *this; temp -= i; return temp;};
    };

    MapArray() :sz(0), buf(new pair <key, T> [sz]){}
    MapArray(initializer_list < pair<key,T> > s): sz(s.size()), buf(new pair<key,T> [sz]) { uninitialized_copy(s.begin(), s.end(), buf);}
    int size() {return sz;}
    iterator begin() { return iterator(buf); }
    iterator end() { return iterator(buf) + sz;}
    const_iterator begin() const { return const_iterator(buf);}
    const_iterator end() const { return const_iterator(buf) + sz;}
    T & operator [](const key& k)
	{
        for (int i = 0; i < sz; i++)
        {if(buf[i].first == k)return buf[i].second;}
        return insert(make_pair(k, T()));
    }

    T & insert (pair<key, T> x)
    {
        pair<key,T> *temp = new pair<key, T>[++sz];
        int stop = sz-1;
        for (int i = 0; i < stop; i++)
        {
            if (x.first < buf[i].first) {stop = i;}
            else
            {
                temp[i].first = buf[i].first;
                temp[i].second = buf[i].second;
            }
        }
        temp[stop].first = x.first;
        temp[stop].second = x.second;

        for (int i = stop+1; i < sz; i++)
        {
            temp[i].first = buf[i-1].first;
            temp[i].second = buf[i-1].second;
        }
        delete[]buf;
        buf = temp;
        return buf[stop].second;
    }

    ~MapArray() { delete[] buf;}
};

#endif
#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <iterator>

using namespace std;

#ifndef SETLIST_H
#define SETLIST_H

template <typename T>

class SetList
{
private:
    struct ListNode
    {
        T info;
        ListNode * next;
        ListNode(T newInfo, ListNode * newNext): info(newInfo), next(newNext){}
    };
    ListNode * head;
    static int length(ListNode * L){return L == nullptr ? 0 : 1 + length(L->next);}
    static ListNode * ListToNode (initializer_list<T> s)
    {
        ListNode* head = nullptr;
        for (T x: s)
        {
            if (head == nullptr)
            {head = new ListNode(x);}
            else
            {head = new ListNode(x, head);}
        }
        return head;
    }

public:
    struct iterator
    {
        //Iterator traits
        typedef forward_iterator_tag iterator_category;
        typedef iterator self_type;
        typedef T value_type;
        typedef value_type reference;
		typedef value_type* pointer;
		typedef ptrdiff_t difference_type;

        private:
            ListNode * buf;

        public:
            iterator(ListNode *ptr) : buf(ptr) { }
            self_type operator ++ () {buf = buf->next; return *this; }
            self_type operator ++ (int postfix) { self_type copy = *this; buf = buf->next; return copy; }
            reference  operator * () { return buf->info; }
            pointer operator -> () { return buf; }
            bool operator == (const self_type& rhs) const {return buf == rhs.buf;}
            bool operator != (const self_type& rhs) const {return buf != rhs.buf;}
    };
    
    class const_iterator
    {
        typedef forward_iterator_tag iterator_category; 
		typedef const_iterator self_type;
		typedef T value_type;
		typedef value_type& reference;
		typedef value_type* pointer;
		typedef ptrdiff_t difference_type;

        private:
            ListNode *buf;
            
        public:
            const_iterator(ListNode * ptr) : buf(ptr) { }
            self_type operator ++ () {buf = buf->next; return *this; }
            self_type operator ++ (int postfix) { self_type copy = *this; buf = buf->next; return copy; }
            pointer operator * () { return buf->info; }
            const pointer operator -> () { return buf;}
            bool operator == (const self_type& rhs) const {return buf == rhs.buf;}
            bool operator != (const self_type& rhs) const {return buf != rhs.buf;}
    };
SetList() {head = nullptr;}
int size() {return ListNode::length(head);}
iterator begin() {return iterator(head);}
iterator end() {return iterator(nullptr);}
iterator insert (const T & e)
{
    if (find (e) == nullptr)
    {
        if (head == nullptr || head -> info > e)
        {
            head = new ListNode(e, head);
        }
        else
        {
            ListNode *temp = head;
            while (temp -> next != nullptr && temp->next->info < e)
            {
                temp = temp->next;
            }
            temp -> next = new ListNode(e, temp->next);
        }
    }
}

iterator find(const T & e)
{
    for( ListNode * p = head; p != nullptr; p = p->next)
    {
        if( p->info == e )
            return iterator(p);
    }
    return nullptr;
}

const_iterator begin() const {return const_iterator(head);}
const_iterator end() const {return const_iterator(nullptr);}
const_iterator find(const T& e) const
{
    ListNode * temp = head;
    for (int n =0; temp!=nullptr; n++, temp = temp->next)
    {
        if (temp->info == e)
            return const_iterator(temp);
    }
    return nullptr;
}

~SetList()
{
    ListNode *temp;
		for(ListNode *p = head; p!=nullptr;)
		{
			temp = p;
			p = p->next;
			delete temp;
		}
}
};

#endif
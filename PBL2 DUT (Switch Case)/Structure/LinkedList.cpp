#pragma once
#include <iostream>
using namespace std;

template <class T>
class Node
{
private:
    T data;
    Node<T> *next;
    template <class U>
    friend class LinkedList;

public:
    Node()
    {
        this->next = NULL;
    }
};

template <class T>
class LinkedList
{
private:
    Node<T> *head;

public:
    LinkedList()
    {
        this->head = NULL;
    }

    void addLast(T item)
    {
        Node<T> *node = new Node<T>[1];
        node->data = item;
        if (head == NULL)
        {
            head = node;
            return;
        }
        Node<T> *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = node;
    }

    void addFirst(T item)
    {
        Node<T> *node = new Node<T>[1];
        node->data = item;
        if (head == NULL)
        {
            head = node;
            return;
        }
        node->next = head;
        head = node;
    }

    void addAtIndex(int index, T item)
    {
        if (index > length() || index < 0)
        {
            return;
        }
        Node<T> *node = new Node<T>[1];
        node->data = item;
        int count = 0;
        Node<T> *temp = head;
        while (temp != NULL && count < index)
        {
            if (count == index - 1)
            {
                if (temp->next != NULL)
                {
                    node->next = temp->next;
                }
                temp->next = node;
                break;
            }
            count++;
            temp = temp->next;
        }
    }

    int length() // Số lượng
    {
        int len = 0;
        Node<T> *temp = head;
        while (temp != NULL)
        {
            len++;
            temp = temp->next;
        }
        return len;
    }

    void remove()
    {
        if (head == NULL)
        {
            return;
        }
        if (head->next == NULL)
        {
            head = NULL;
            return;
        }

        Node<T> *temp = head;
        while (temp != NULL)
        {
            if (temp->next->next == NULL)
            {
                temp->next = NULL;
                break;
            }
            temp = temp->next;
        }
    }

    void removeAtIndex(int index)
    {
        if (head == NULL)
        {
            return;
        }

        if (index >= length() || index < 0)
        {
            return;
        }

        if (index == 0)
        {
            removeFirst();
            return;
        }

        int count = 0;
        Node<T> *temp = head;
        while (temp != NULL)
        {
            if (count == index - 1)
            {
                temp->next = temp->next->next;
                break;
            }
            count++;
            temp = temp->next;
        }
    }

    void removeFirst()
    {
        if (head == NULL)
        {
            return;
        }
        head = head->next;
    }

    T get(int index)
    {
        if (head == NULL)
        {
            cout << "Empty list!";
        }
        else if (index >= length() || index < 0)
        {
            cout << "Index out of bound!";
        }

        if (index == 0)
        {
            return head->data;
        }
        int count = 0;
        T res;
        Node<T> *temp = head;
        while (temp != NULL)
        {
            if (count++ == index)
            {
                res = temp->data;
                break;
            }
            temp = temp->next;
        }
        return res;
    }

    bool empty()
    {
        if (head == NULL)
        {
            return true;
        }
        return false;
    }
};

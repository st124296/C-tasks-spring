#include<iostream>
#include<limits.h>

class ArrayList
{
private:
    int len;
    int capacity;
    int* data;

    void init(int len = 10)
    {
        this->len = len;
        this->capacity = len;
        this->data = (int*)malloc(sizeof(int) * len);
    }

    bool indexValid(int index)
    {
        return 0 <= index < this->len;
    }

    void expand()
    {
        this->capacity *= 2;
        int* newData = (int*)malloc(sizeof(int) * this->capacity);
        for (int i = 0; i < len; ++i)
        {
            newData[i] = data[i];
        }
        free(data);
        this->data = newData;
    }

public:
    ArrayList(int len = 10)
    {
        this->init(len);
        for (int i = 0; i < this->len; ++i)
        {
            this->data[i] = 0;
        }
    }
    ArrayList(ArrayList& list)
    {
        this->init(list.len);
        for (int i = 0; i < list.len; ++i)
        {
            this->set(i, list.get(i));
        }
    }
    ~ArrayList()
    {
        //for (int i = 0; i < this->len; ++i)
        //{
        //	this->data[i] = 0;
        //}
        free(this->data);
        //this->data = nullptr;
        //this->len = 0;
    }
    void randomize(int min = 10, int max = 99)
    {
        for (int i = 0; i < len; ++i)
        {
            this->data[i] = rand() % (max - min + 1) + min;
        }
    }
    void print()
    {
        for (int i = 0; i < this->len; ++i)
        {
            printf("%d ", this->data[i]);
        }
        printf("\n");
    }
    int get(int index)
    {
        if (indexValid(index))
        {
            return this->data[index];
        }
        return -1;
    }
    void set(int index, int value)
    {
        if (indexValid(index))
        {
            this->data[index] = value;
        }
    }
    int count()
    {
        return len;
    }

    void pushBack(int element)
    {
        if (len == capacity)
            expand();

        data[len++] = element;
    }

    void pushFront(int element)
    {
        if (len == capacity)
            expand();

        for (int i = len; i > 0; --i)
        {
            data[i] = data[i - 1];
        }

        data[0] = element;
        len++;
    }

    int popBack()
    {
        return data[--len];
    }

    int popFront()
    {
        int frontValue = data[0];

        for (int i = 0; i < len - 1; ++i)
        {
            data[i] = data[i + 1];
        }

        len--;
        return frontValue;
    }

    int extract(int index)
    {
        int value = data[index];

        for (int i = index; i < len - 1; ++i)
        {
            data[i] = data[i + 1];
        }
        len--;
        return value;
    }

    void reverse(int start, int end)
    {
        while (start < end)
        {
            int temp = data[start];

            data[start] = data[end];
            data[end] = temp;
            start++;
            end--;
        }
    }

    int sum()
    {
        int sum = 0;

        for (int i = 0; i < len; ++i)
        {
            sum += data[i];
        }

        return sum;
    }


    int secondMax()
    {
        int max1 = INT_MIN, max2 = INT_MIN;

        for (int i = 0; i < len; ++i)
        {
            if (data[i] > max1)
            {
                max2 = max1;
                max1 = data[i];
            }
            else if (data[i] > max2 && data[i] != max1)
            {
                max2 = data[i];
            }
        }
        return max2;
    }

    int lastMinIndex()
    {
        int minIndex = 0;

        for (int i = 1; i < len; ++i)
        {
            if (data[i] <= data[minIndex])
            {
                minIndex = i;
            }
        }
        return minIndex;
    }

    void shift(int k)
    {
        k = k % len;

        if (k < 0)
        {
            k += len;
        }

        reverse(0, len - 1);
        reverse(0, k - 1);
        reverse(k, len - 1);
    }

    int countOdd()
    {
        int count = 0;

        for (int i = 0; i < len; ++i)
        {
            if (data[i] % 2 != 0)
            {
                count++;
            }
        }

        return count;
    }

    int sumEven()
    {
        int sum = 0;

        for (int i = 0; i < len; ++i)
        {
            if (data[i] % 2 == 0)
            {
                sum += data[i];
            }
        }

        return sum;
    }

};

int max(ArrayList list)
{
    int mx = list.get(0);
    for (int i = 0; i < list.count(); ++i)
    {
        mx = (mx > list.get(i) ? mx : list.get(i));
    }
    return mx;
}

int main(int argc, char* argv[])
{
    ArrayList list(10);

    list.randomize();
    list.print();

    list.pushFront(1);
    list.pushFront(2);
    list.pushFront(3);
    int r1 = list.popFront();
    int r2 = list.popFront();
    int r3 = list.popFront();

    if (r1 != 3 || r2 != 2 || r3 != 1)
    {
        printf("Error in ArrayList pushFront/popFront functions.");
    }

    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
    r1 = list.popBack();
    r2 = list.popBack();
    r3 = list.popBack();

    if (r1 != 3 || r2 != 2 || r3 != 1)
    {
        printf("Error in ArrayList pushBack/popBack functions.");
    }

    printf("%d\n", max(list));

	ArrayList reversed_list(5);

    reversed_list.set(0, 1);
    reversed_list.set(1, 2);
    reversed_list.set(2, 3);
    reversed_list.set(3, 4);
    reversed_list.set(4, 5);

    printf("Default list: ");
    reversed_list.print();
    reversed_list.reverse(0, 4);
    printf("Reversed list: ");
    reversed_list.print();

    reversed_list.extract(2);
    printf("List without 3: ");
    reversed_list.print();

    if (reversed_list.sumEven() != 6 || reversed_list.countOdd() != 2)
    {
        printf("Error in even/odd functions");
    }

    reversed_list.shift(3);
    printf("Shifted (by 3) list: ");
    reversed_list.print();

    int sec_max = reversed_list.secondMax();
    int min_index = reversed_list.lastMinIndex();
    printf("Second max: %i Last Min Index: %i\n", sec_max, min_index);

    return 0;
}
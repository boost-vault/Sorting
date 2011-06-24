// SortingLib.cpp : Defines the entry point for the DLL application.
//
#include <iostream>
#include <deque>
namespace boost
{
	namespace detail
	{
        template<typename T, typename Holder>
        class qobjclass //I use a class because only class templates can be partially specialized
        {
        public:
        inline static const T& qobj(typename const Holder& a, int d)
        {
            return a[d];
        }
        };
        template<typename T>
        class qobjclass<T, typename std::deque<T>::iterator>//I use a class because only class templates can be partially specialized
        {
        public:
        inline static const T& qobj(typename const std::deque<T>::iterator& a, int d)
        {
            return *(a + d);
        }
        };
         //I need all of these special functions because I cannot do partial specializations for function templates, but I need the simulate it
        template<typename T>
        inline T& _get(typename T* a, int d)
        {
            return a[d];
        }
        template<typename T>
        inline T& _get(typename std::deque<T>::iterator& a, int d)
        {
            return *(a + d);
        }
#define qobj(a, b) qobjclass<KeyHolds, Key>::qobj((a), (b))
#define get(a, b) _get<Key>((a), (b))
        template<typename KeyHolds, typename Key>
        void mkquicksort(typename Key* ar, int l, int r, int bit, typename const KeyHolds& term)
        {
            if(r <= l) return;
            typename register Key* a = ar;
            register int i = l - 1, j = r, d = bit; typename const KeyHolds v = qobj(get(a, j), d);//speed increase with registers
            int p = i, q = j;
            while(i < j)
            {
                while(qobj(get(a, ++i), d) < v) ;
                while(v < qobj(get(a, --j), d)) if(j == l) break;
                if(i > j) break;
                std::swap(get(a, i), get(a, j));
                if(qobj(get(a, i), d) == v) {++p; std::swap(get(a, p), get(a, i));}
                if(qobj(get(a, j), d) == v) {--q; std::swap(get(a, q), get(a, j));}
            }
            if(p == q)
            {
                 if(!(v == term)) mkquicksort(a, l, r, d + 1, term);
                 return;
            }
            if(qobj(get(a, i), d) < v) ++i;
            int k = l;
            for( ; k <= p; j--, k++) std::swap(get(a, k), get(a, j));
            for(k = r; k >= q; i++, k--) std::swap(get(a, k), get(a, i));
            mkquicksort(a, l, j, d, term);
            if((i == r) && (qobj(get(a, i), d) == v)) ++i;
            if(!(v == term)) mkquicksort(a, j + 1, i - 1, d + 1, term);
            mkquicksort(a, i, r, d, term);
        }
        //////////////////
        template<typename KeyHolds, typename Key>
        void rmkquicksort(typename Key* ar, int l, int r, int bit, typename const KeyHolds& term)
        {
            if(r <= l) return;
            typename register Key* a = ar;
            register int i = l - 1, j = r, d = bit; typename const KeyHolds v = qobj(get(a, j), d);//speed increase with registers
            int p = i, q = j;
            while(i < j)
            {
                while(v < qobj(get(a, ++i), d)) ;
                while(qobj(get(a, --j), d) < v) if(j == l) break;
                if(i > j) break;
                std::swap(get(a, i), get(a, j));
                if(qobj(get(a, i), d) == v) {++p; std::swap(get(a, p), get(a, i));}
                if(qobj(get(a, j), d) == v) {--q; std::swap(get(a, q), get(a, j));}
            }
            if(p == q)
            {
                 if(!(v == term)) rmkquicksort(a, l, r, d + 1, term);
                 return;
            }
            if(v < qobj(get(a, i), d)) ++i;
            int k = l;
            for( ; k <= p; j--, k++) std::swap(get(a, k), get(a, j));
            for(k = r; k >= q; i++, k--) std::swap(get(a, k), get(a, i));
            rmkquicksort(a, l, j, d, term);
            if((i == r) && (qobj(get(a, i), d) == v)) ++i;
            if(!(v == term)) rmkquicksort(a, j + 1, i - 1, d + 1, term);
            rmkquicksort(a, i, r, d, term);
        }
    }
	template<typename KeyHolds, typename Key>
	inline void mk_qsort(typename Key* data, int size, typename const KeyHolds term) //normal
	{
		detail::mkquicksort<KeyHolds, Key>(data, 0, size, 0, term);
	}
    template<typename KeyHolds, typename Key>
    inline void r_mk_qsort(typename Key* data, int size, typename const KeyHolds term) //reverse
    {
        detail::rmkquicksort<KeyHolds, Key>(data, 0, size, 0, term);
    }
}
#include <time.h>
//can't sort these with normal quicksort but you can with multikey quicksort
//these aren't real 
int rrr[10];
int rrr1[10];
int rrr2[10];
int rrr3[10];
//cna't sort this with normal quicksort but you can with multikey quicksort
int* rrrr[4] = {rrr, rrr1, rrr2, rrr3};
void test()
{
    time_t repeatable = time(NULL);
    srand((unsigned)repeatable);
    for(int x = 0; x < 4; x++)
    {
        for(int y = 0; y < 5; y++)
        {
            rrrr[x][y] = rand() % 2;
        }
        for(int y = 5; y < 10; y++)
        {
            rrrr[x][y] = rand() % 3;
        }
        rrrr[x][10] = 255;
    }
    cout << "Normal" << endl;
    boost::mk_qsort<int, int*>(rrrr, 3, 255);
    for(int x = 0; x < 4; x++)
    {
        cout << endl;
        for(int y = 0; y < 10; y++)
        {
            cout << rrrr[x][y] << " ";
        }
    }
    cout << endl << endl << "Reverse" << endl << endl;
    srand((unsigned)repeatable);
    for(int x = 0; x < 4; x++)
    {
        for(int y = 0; y < 5; y++)
        {
            rrrr[x][y] = rand() % 2;
        }
        for(int y = 5; y < 10; y++)
        {
            rrrr[x][y] = rand() % 3;
        }
        rrrr[x][10] = 255;
    }
    boost::r_mk_qsort<int, int*>(rrrr, 3, 255);
    for(int x = 0; x < 4; x++)
    {
        for(int y = 0; y < 10; y++)
        {
            cout << rrrr[x][y] << " ";
        }
        cout << endl;
    }
}
int main()
{
	test();
	return 0;
}
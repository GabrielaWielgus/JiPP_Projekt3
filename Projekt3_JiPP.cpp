#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

template <class T> class Matrix
{
private:
    T** A;                                   // Elementy
    int n, m;
public:
    Matrix(const Matrix<T>& other);          // Konstruktor kopiujacy
    Matrix(int r, int c);                    // Konstruktor tworzacy macierz nxm
    Matrix(int r);                           // Konstruktor tworzacy macierz nxn
    Matrix(string filename);                 // Konstruktor tworzacy macierz z pliku po podaniu nazwy utworzy sie plik, do ktorego chcemy wrzucic macierz
    ~Matrix();                               // Destruktor
    T getv(int r, int c);                    // Pobiera element na podanej pozycji
    void setv(int r, int c, T v);            // Ustawia element na podanej pozycji
    int rows();                              // Zwraca liczbę wierszy macierzy
    int cols();                              // Zwraca liczbę kolumn macierzy
    void print();                            // Wyswietla macierz
    Matrix<T> multiply(Matrix<T>& a);       // Mnozy dwie macierze
    Matrix<T> add(Matrix<T>& a);            // Dodaje dwie macierze
    Matrix<T> subtract(Matrix<T>& a);       // Odejmuje dwie macierze
    void store(string filename);             // Zachowuje w pliku o podanej nazwie, jesli takiego nie ma to go tworzy
    Matrix<T> operator+(const Matrix<T>& other); // Obciazony operator dodawania macierzy
    Matrix<T> operator-(const Matrix<T>& other); // Obciazony operator odejmowania macierzy
    Matrix<T> operator*(const Matrix<T>& other); // Obciazony operator mnozenia macierzy
    Matrix<T> operator=(const Matrix<T>& other); // Obciazony operator przypisywania macierzy
    Matrix<T> operator[](int row);               // Obciazony operator pobierajacy wiersz macierzy z elementami
    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const Matrix<U>& t); // Obciazony operator wyjscia macierzy
    template <typename U>
    friend bool operator==(const Matrix<U>& rhs, const Matrix<U>& lft); // Obciazony operator przyrownywania macierzy

};
template <class T> 
Matrix<T> Matrix<T>::operator[](int r)
{
    Matrix result(r, m);
    if (r<=0 || r>n)
    {
        cout << "\nWrong number of rows in this array\n" << endl;
        exit(1);
    }
    else
    {
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < m; j++)
            {
                result.A[i][j] = (*this).A[i][j];
            }
        }
    }
    return result;
}

template <typename U>
std::ostream& operator<<(std::ostream& out, const Matrix<U>& t) 
{
    for (int i = 0; i < t.n; i++) 
    {
        std::cout << std::endl;
        for (int j = 0; j < t.m; j++)
            out << t.A[i][j] << " ";
    }
    std::cout << std::endl;
    return out;
}
template <typename U>
bool operator ==(const Matrix<U>& rhs,const Matrix<U>& lft) 
{
    if ((rhs.n != lft.n) || (rhs.m != lft.m))
    {
        return false;
    }
    else if ((rhs.n == lft.n) && (rhs.m == lft.m))
    {
        for (int i = 0; i < rhs.n; ++i)
        {
            for (int j = 0; j < rhs.m; ++j)
            {
                if (rhs.A[i][j] != lft.A[i][j])
                {
                    return false;
                }
            }
        }
    }
    return true;
}
template <class T>
Matrix<T> Matrix<T>::operator=(const Matrix<T>& T1) 
{
    n = T1.n;
    m = T1.m;
    if (this == &T1) return *this;
    for (int i = 0; i < n; i++)
        delete[] A[i];
    delete[] A;

    A = new double* [n];
    for (int i = 0; i < n; i++)
        A[i] = new double[m];
    if (T1.A) 
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                A[i][j] = T1.A[i][j];
    }
    return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& rhs) 
{
    int r = n;
    int c = m;
    Matrix result(r,c);
    if ((n != rhs.n) || (m != rhs.m))
    {
        cout << "\nCan't add two matrix in another size, change the size\n" << endl;
        exit(1);
    }
    else
    {
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                result.A[i][j] = (*this).A[i][j] + rhs.A[i][j];
    }
    return result;
}

template <class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& rhs)
{
    int r = n;
    int c = m;
    Matrix result(r, c);
    if ((n != rhs.n) || (m != rhs.m))
    {
        cout << "\nCan't add two matrix in another size, change the size\n" << endl;
        exit(1);
    }
    else
    {
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                result.A[i][j] = (*this).A[i][j] - rhs.A[i][j];
    }
    return result;
}

template <class T> 
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other)
{
    T sum = 0;
    int r = n;
    int c = other.m;
    Matrix result(r, c);
    if (m != other.n)
    {
        cout << "\nCan't multiply two matrix if number of columns in first matrix not equals to rows of second matrix, change the size\n" << endl;
        exit(1);
    }
    else
    {
        int i, j, k;

        for (i = 0; i < n; i++)
        {
            for (j = 0; j < other.m; j++)
            {
                sum = 0;
                for (k = 0; k < m; k++)

                    sum += A[i][k] * (other.A[k][j]);

                result.A[i][j] = sum;
            }
        }
    }
    return result;
}

template<class T> Matrix<T>::Matrix(const Matrix<T>& other)  
{
    n = other.n;
    m = other.m;
  
    A = new double* [n];
    for (int i = 0; i < n; i++)
        A[i] = new double[m];
    if (other.A) 
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                A[i][j] = other.A[i][j];
    }
}

template <class T> Matrix<T>::Matrix(int r)
{
    n = r;
    m = r;
    A = new double* [n];
    for (int i = 0; i < n; i++)
        A[i] = new double[m];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            A[i][j] = 0.0;
}

template <class T> Matrix<T>::Matrix(int r, int c)
{
    n = r;
    m = c;
    A = new double* [n];
    for (int i = 0; i < n; i++)
        A[i] = new double[m];
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            A[i][j] = 0.0;
      
}

template <class T> Matrix<T>::Matrix(string filename)
{
    ifstream fin(filename);  
    fin >> n >> m;

    A = new double* [n];
    for (int i = 0; i < n; i++)
        A[i] = new double[m];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            fin >> A[i][j];

    fin.close();  
}

template <class T> Matrix<T>::~Matrix()
{
    for (int i = 0; i < n; i++)
        delete[] A[i];
    delete[] A;
}

template <class T> T Matrix<T>::getv(int r, int c)
{
    if (r >= 0 && r <= n && c >= 0 && c <= m)
    {
        return A[r][c];
        
    }
    else
    {
        cout << "Can't get number of matrix, wrong number of rows or columns size\n" << endl;
        exit(1);
    }
}

template <class T> void Matrix<T>::setv(int r, int c, T v)
{
    if ((r >= 0 && r <= n) && (c >= 0 && c <= m))
    {
        A[r][c] = v;
    }
    else
    {
        cout << "Can't set number of matrix, wrong number of rows or columns size\n" << endl;
    }
}

template <class T> int Matrix<T>::rows()
{
    return n;
}

template <class T> int Matrix<T>::cols()
{
    return m;
}

template <class T> void Matrix<T>::print()
{
    
    cout << "Matrix:" << n << "x" << m << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << setw(5) << (double) A[i][j];
        }
        cout << endl;
    }
}

template <class T> Matrix<T> Matrix<T>::multiply(Matrix<T>& a)
{
    T sum = 0;
    int r = n;
    int c = a.m;
    Matrix result(r, c);
    if (m != a.n)
    {
        cout << "\nCan't multiply two matrix if number of columns in first matrix not equals to rows of second matrix, change the size\n" << endl;
        exit(1);
    }
    else
    {
        int i, j, k;

        for (i = 0; i < n; i++)
        {
            for (j = 0; j < a.m; j++)
            {
                sum = 0;
                for (k = 0; k < m; k++)

                    sum += A[i][k] * (a.A[k][j]);

                result.A[i][j] = sum;
            }
        }
    }
    return result;
}

template <class T> Matrix<T> Matrix<T>::add(Matrix<T>& a)
{
    int r = n;
    int c = m;
    Matrix result(r, c);
    if ((n != a.n) || (m != a.m))
    {
        cout << "\nCan't add two matrix in another size, change the size\n" << endl;
        exit(1);
    }
    else
    {
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                result.A[i][j] = (*this).A[i][j] + a.A[i][j];
    }
    return result;
}

template <class T> Matrix<T> Matrix<T>::subtract(Matrix<T>& a)
{
    int r = n;
    int c = m;
    Matrix result(r, c);
    if ((n != a.n) || (m != a.m))
    {
        cout << "\nCan't add two matrix in another size, change the size\n" << endl;
        exit(1);
    }
    else
    {
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                result.A[i][j] = (*this).A[i][j] - a.A[i][j];
    }
    return result;
}
template <class T> void Matrix<T>::store(string filename)
{
    ofstream fin(filename);  //tworzy plik o podanej nazwie, jezeli nie istnieje

   // fin.open(filename, ifstream::out); // Otwieramy strumień do odczytu, nie potrzebujemy jezeli chcemy tworzyc plik
    fin << n << " " << m << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            fin << setw(5) << A[i][j];
        fin << endl;
    }

    fin.close();   
}

int main()
{
    cout << "-------------------------------------------------------------------------------------" << endl;
    cout << "-------------------------------------------------------------------------------------" << endl;
    cout << "         Gabriela Wielgus, Projekt 3, obciazenie operatorow - JiPP                   " << endl;
    cout << "-------------------------------------------------------------------------------------" << endl;
    cout << "-------------------------------------------------------------------------------------" << endl;
   
    Matrix<double> j(6, 6), l(8, 7), x(6, 6), o(7,8);
    //cout << "getv(1,1000000000) : " << j.getv(1, 1) << endl;
    //cout << "getv(1,1000000000) : " << j.getv(1, 100000) << endl; //wrong size, exit
    cout << "Matrix j: \n"; j.print();
    cout << "Matrix k: \n"; o.print();
    cout << "Matrix l: \n"; l.print();
    cout << "Matrix x: \n"; x.print();
    cout << "-------------------------------------------------------------------------------------" << endl;
    cout << "Testing that if matrix j equals to matrix x\n" << endl;
    if (j == x) 
    {
        cout << "True" << endl;
    }
    else
    {
        cout << "False" << endl;
    }
    cout << "-------------------------------------------------------------------------------------" << endl;
    cout << "Change elements of matrix j:\n" << endl;
    for (int i = 0; i < j.rows(); i++)
    {
        for (int z = 0; z < j.cols(); z++)
        {
            j.setv(i, z, 30.);
        }
    }
    j.print();
    //cout << "getv(1,1) : " << j.getv(1, 1) << endl;
    cout << "\nChange elements of matrix o:\n" << endl;
    for (int i = 0; i < o.rows(); i++)
    {
        for (int j = 0; j < o.cols(); j++)
            o.setv(i, j, 2.);
    }
    o.print();
    cout << "\nChange elements of matrix l:\n" << endl;
    for (int i = 0; i < l.rows(); i++)
    {
        for (int j = 0; j < l.cols(); j++)
            l.setv(i, j, 10.);
    }
    l.print();
    //cout << "getv(1,1) : " << l.getv(1, 1) << endl;
    cout << "-------------------------------------------------------------------------------------" << endl;
    cout << "Adding matrix j to matrix j: \n" << j+j <<endl;
    //cout << "-------------------------------------------------------------------------------------" << endl;
    //cout << j+o << endl; //dodawanie macierzy rozny rozmiar
    //cout << "-------------------------------------------------------------------------------------" << endl;
    //cout << "Assigning k to j : \n" << (j = o) << endl;
    cout << "-------------------------------------------------------------------------------------" << endl;
    cout << "Subtraction matrix j to matrix j: \n" << j - j << endl;
    cout << "-------------------------------------------------------------------------------------" << endl;
    cout << "Multiplying matrix k to matrix l: \n" << o * l << endl;
    cout << "-------------------------------------------------------------------------------------" << endl;
    //cout << "Multiplying matrix k to matrix l: \n" << j * o << endl; //mnozenie macierzy rozny rozmiar,
    //cout << "-------------------------------------------------------------------------------------" << endl;
   
    //nie wiem czy poprawnie zrozumialam kwestie porownywania macierzy, zalozylam z gory, ze
    //porownywanie ma sens jedynie wtedy kiedy rozmiary macierzy sa sobie rowne i tak zaimplementowalam rozwiazanie
    //cout << "-------------------------------------------------------------------------------------" << endl;
    cout << "Testing that if matrix j equals to matrix x\n" << endl;
    if (j == x) //mimo takiego samego rozmiaru, rozne elementy, zatem false
    {
        cout << "True" << endl;
    }
    else
    {
        cout << "False" << endl;
    }
    //cout << "-------------------------------------------------------------------------------------" << endl;
    //testowanie operatora wyjscia '<<' na wyjsciu do pliku, nie jestem pewna czy chodzilo ogolnie o operator wyjscia + testowanie na pliku, czy operator z gory mial przesylac
    //do pilku podana macierz, 
    cout << "-------------------------------------------------------------------------------------" << endl;
    cout << "Checking constructor(filename), Matrix j\nChecking .store() and .print() methods by using another matrix and overloaded operator '+' Matrix<T> name(r,c); name = j+j; \n" << endl;
    Matrix<double> addition(6, 6);
    addition = j + j;
    cout << " addition.print(); : \n" << endl; addition.print();
    addition.store("addition.txt");
    Matrix<double> testing("addition.txt");
    cout << "\ntesting.print(); : \n" << endl; testing.print();
    cout << "-------------------------------------------------------------------------------------" << endl;
    cout << "Elements of chose number of rows: (number of rows can't be 0, even iteration is started in 0)\nMatrix j:" << endl;
    cout << j[4] << endl;
    cout << "-------------------------------------------------------------------------------------" << endl;
    return 0;
}

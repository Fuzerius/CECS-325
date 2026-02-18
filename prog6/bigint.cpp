// Author: Giahuy Thai
// CECS 325-02 Prog 6
// Due 12/05/2025
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>   // for max function
#include <iomanip>      // for setw()
#include <climits>      // for INT_MAX
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ostream;
using std::flush;
using std::setw;


class BigInt
{
private:
	vector<char> v;  //<- notice this is a vector of char, not int
public:
	
BigInt();
BigInt(int);
BigInt(string);
	
	BigInt operator+ (BigInt);
	BigInt operator- (BigInt);
	BigInt operator- (int);
	BigInt operator* (BigInt);

	bool operator==(BigInt); // added
    bool operator>=(BigInt); // added
    bool operator>(BigInt); // added
    bool operator<(BigInt); // added

	BigInt operator/ (BigInt);
	BigInt operator% (BigInt);
	BigInt operator++(int);
	BigInt operator++( );
	BigInt operator[](int);  // index function

	int size();

void print();
	BigInt fibo( ); // Fibonacci of current number
	BigInt fact( ); // Factorial of current number
	BigInt collatz(bool); // prints Collatz sequence – returns number of steps. 
                            //Accepts a bool: true means print the steps	
	friend BigInt operator+ (int, BigInt);
	friend ostream& operator<<(ostream&, const BigInt&);
};

BigInt::BigInt() // default constructor.
{
	v.push_back(0);  // Store numeric 0
}

BigInt::BigInt(int n) // constructor from int
{
    if (n == 0)
    {
        v.push_back(0);  // Store numeric 0
        return;
    }
    // Example input = 123
	while (n > 0)
	{
        int digit = n % 10; // get the last digit
		v.push_back(digit); // Store numeric value (0-9) directly
		n /= 10; // remove the last digit
	}
    // vector now contains [3, 2, 1]. calculations must be done in reverse order.
}

BigInt::BigInt(string s) // constructor from string
{
    for (int i = s.length() - 1; i >= 0; i--)
    {
        v.push_back(s[i] - '0');  // Convert ASCII character to numeric value
    }
}

int BigInt::size()
{
    return v.size();
}

void BigInt::print() // prints the BigInt in reverse order because the vector is stored in reverse order.
{
    for (int i = v.size() - 1; i >= 0; i--)
    {
        cout << (char)(v[i] + '0');  // Convert numeric value to ASCII character for printing
    }
}

// Tail-recursive helper function for Fibonacci
BigInt fibo_helper(int n, BigInt a, BigInt b)
{
    if (n == 0) return a;
    if (n == 1) return b;
    return fibo_helper(n - 1, b, a + b);  // Tail recursive call - last operation
}

BigInt BigInt::fibo()
{
    // Convert BigInt to int
    int n = 0;
    for (int i = v.size() - 1; i >= 0; i--)
    {
        n = n * 10 + v[i]; 
    }
    
    // Call tail-recursive
    return fibo_helper(n, BigInt(0), BigInt(1));
}

// Tail-recursive helper function for factorial
BigInt fact_helper(int n, BigInt acc)
{
    if (n <= 1) return acc;  // Base case
    return fact_helper(n - 1, acc * BigInt(n));  // Tail recursive call - last operation
}

BigInt BigInt::fact()
{
    // Convert BigInt to int
    int n = 0;
    for (int i = v.size() - 1; i >= 0; i--)
    {
        n = n * 10 + v[i];  
    }
    
    // Call tail-recursive helper.
    return fact_helper(n, BigInt(1));
}

BigInt BigInt::collatz(bool printSteps)
{
    int steps = 0; 
    BigInt current = *this; // Copy the current BigInt

    // Print starting value if printSteps is true
    if (printSteps)
    {
        cout << current << ". ";
    }

    while (current > BigInt(1))
    {

        if ((current % BigInt(2)) == BigInt(0))
        {
            current = current / BigInt(2); // Even: divide by 2
        }
        else
        {
            current = current + current + current + BigInt(1); // Odd: multiply by 3 and add 1
        }

        steps++; 
        
        // Print current value if printSteps is true
        if (printSteps)
        {
            cout << current << ". ";
        }
    }

    cout << endl << ":->";

    return BigInt(steps); // Convert back to BigInt for return
}

ostream& operator<<(ostream& os, const BigInt& num)
{
    if (num.v.size() <= 12)
    {
        // Print all digits if size is 12 or less
        for (int i = num.v.size() - 1; i >= 0; i--)
        {
            os << (char)(num.v[i] + '0');  // Convert numeric to ASCII
        }
    }
    else
    {
        // Print in exponential notation for size > 12
        os << (char)(num.v.back() + '0') << "."; // First digit
        for (int i = num.v.size() - 2; i >= num.v.size() - 7; i--)
        {
            os << (char)(num.v[i] + '0'); // Next 6 significant digits
        }
        os << "e" << num.v.size() - 1; // Exponent
    }
    return os;
}

BigInt operator+(int n, BigInt num)
{
    return BigInt(n) + num;
}

BigInt BigInt::operator+(BigInt other)
{
    // Example input = 1 + 456 = 457
    // 1 =   [1]
    // 456 = [6, 5, 4]
    // 457 = [7, 5, 4]

    BigInt result;
    result.v.clear(); // Clear the default 0 from the constructor
    int carry = 0;
    int max_size = std::max(v.size(), other.v.size()); // get the size of the larger vector. When adding two numbers of different lengths, need to loop through all digits of the longer number.
    for (int i = 0; i < max_size; i++)
    {
        // Get the digits from the two vectors. If the vector is shorter, use 0.
        int digit1 = i < v.size() ? v[i] : 0;  
        int digit2 = i < other.v.size() ? other.v[i] : 0;  
        
        int sum = digit1 + digit2 + carry; // Add the digits and the carry
        result.v.push_back(sum % 10);
        carry = sum / 10; // carry is the value of the digit that is carried over to the next digit. If the sum is greater than 9, the carry is 1.
    }

    // After the loop, check if there's a final carry:
    if (carry > 0)
    {
        result.v.push_back(carry);
    }
    
    // If result is empty, the sum is 0
    if (result.v.empty())
    {
        result.v.push_back(0);
    }

    return result;
}

BigInt BigInt::operator*(BigInt other)
{
    // Result size will be at most v.size() + other.v.size()
    BigInt result("0");  // Start with 0
    
    // For each digit in other
    for (int i = 0; i < other.v.size(); i++)
    {
        BigInt partial_product;  // This will hold one row
        partial_product.v.clear(); // Clear the default 0
        int carry = 0;
        int digit2 = other.v[i];  
        
        // Add i zeros at the beginning 
        for (int k = 0; k < i; k++)
        {
            partial_product.v.push_back(0);
        }
        
        // Multiply digit2 by each digit of *this
        for (int j = 0; j < v.size(); j++)
        {
            int digit1 = v[j];  // Already numeric (0-9)
            int product = digit1 * digit2 + carry;
            partial_product.v.push_back(product % 10);
            carry = product / 10;
        }
        
        // final carry
        if (carry > 0)
        {
            partial_product.v.push_back(carry);
        }
        
        // Add partial_product to result
        result = result + partial_product;
    }
    
    return result;
}

bool BigInt::operator==(BigInt other)
{
    return v == other.v;
}

BigInt BigInt::operator-(int other)
{
    BigInt result;
    result.v.clear(); // Clear the default 0
    int borrow = 0;
    int i = 0;
    
    while (i < v.size() || other > 0)  // While there are digits to process
    {
        int digit1 = i < v.size() ? v[i] : 0;  // Already numeric (0-9)
        int digit2 = other % 10;  // Extract rightmost digit from int
        other = other / 10;       // Remove that digit
        
        int diff = digit1 - digit2 - borrow;
        
        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        
        result.v.push_back(diff);
        i++;
    }
    
    // Remove leading zeros
    while (result.v.size() > 1 && result.v.back() == 0)  // Compare with numeric 0
    {
        result.v.pop_back();
    }
    
    // If result is empty, the result is 0
    if (result.v.empty())
    {
        result.v.push_back(0);
    }
    
    return result;
}

BigInt BigInt::operator-(BigInt other)
{
    BigInt result;
    result.v.clear();
    int borrow = 0;
    int i = 0;
    
    while (i < v.size() || i < other.v.size())  
    {
        int digit1 = i < v.size() ? v[i] : 0;  
        int digit2 = i < other.v.size() ? other.v[i] : 0;  
        int diff = digit1 - digit2 - borrow;
        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        result.v.push_back(diff);
        i++;
    }
    // Remove trailing zeros
    while (result.v.size() > 1 && result.v.back() == 0)
    {
        result.v.pop_back();
    }
    return result;
}

BigInt BigInt::operator++(int) // post-increment
{
    BigInt result = *this;
    *this = *this + BigInt(1);
    return result;
}

BigInt BigInt::operator++() // pre-increment
{
    *this = *this + BigInt(1); 
    return *this;
}

bool BigInt::operator>=(BigInt other) 
{
    // Size comparison
    if (v.size() != other.v.size())
        return v.size() > other.v.size();
    
    // Digit-by-digit comparison
    for (int i = v.size() - 1; i >= 0; i--)
    {
        if (v[i] > other.v[i]) return true;
        if (v[i] < other.v[i]) return false;
    }
    
    return true;  // Equal counts as >=
}

bool BigInt::operator<(BigInt other)
{
    // Size comparison
    if (v.size() != other.v.size())
        return v.size() < other.v.size();  // Fewer digits = smaller
    
    // Digit-by-digit comparison (most significant first)
    for (int i = v.size() - 1; i >= 0; i--)
    {
        if (v[i] < other.v[i]) return true;
        if (v[i] > other.v[i]) return false;
    }
    
    return false;  // Equal, so not less than
}

bool BigInt::operator>(BigInt other)
{
    // Size comparison
    if (v.size() != other.v.size())
        return v.size() > other.v.size();  // More digits = larger
    
    // Digit-by-digit comparison (most significant first)
    for (int i = v.size() - 1; i >= 0; i--)
    {
        if (v[i] > other.v[i]) return true;
        if (v[i] < other.v[i]) return false;
    }
    
    return false;  // Equal, so not greater than
}

BigInt BigInt::operator/(BigInt other) 
{
    if (*this < other)
    {
        return BigInt("0");
    }
    
    // Check if other is a single digit or small number
    if (other.v.size() <= 4)  // divisor fits in an int
    {
        int divisor = 0;
        for (int i = other.v.size() - 1; i >= 0; i--)
        {
            divisor = divisor * 10 + other.v[i];  
        }
        
        // Perform long division digit by digit
        BigInt result;
        result.v.clear(); // Clear the default 0
        int remainder = 0;
        
        for (int i = v.size() - 1; i >= 0; i--)
        {
            remainder = remainder * 10 + v[i];  
            int quotient = remainder / divisor;
            result.v.insert(result.v.begin(), quotient);
            remainder = remainder % divisor;
        }
        
        // Remove leading zeros
        while (result.v.size() > 1 && result.v.back() == 0)  // Compare with numeric 0
        {
            result.v.pop_back();
        }
        
        // If result is empty, it means the quotient is 0
        if (result.v.empty())
        {
            result.v.push_back(0);
        }
        
        return result;
    }
   

    BigInt result; // Starts with 0 from default constructor
    BigInt dividend = *this;
    BigInt divisor = other;
    while (dividend >= divisor)
    {
        dividend = dividend - divisor;
        result++;
    }
    return result;
}

BigInt BigInt::operator%(BigInt other)
{
    if (*this < other)
    {
        return *this;
    }
    
    if (other.v.size() <= 4)
    {
        int divisor = 0;
        for (int i = other.v.size() - 1; i >= 0; i--)
        {
            divisor = divisor * 10 + other.v[i];  
        }
        
        // Compute remainder digit by digit
        int remainder = 0;
        for (int i = v.size() - 1; i >= 0; i--)
        {
            remainder = (remainder * 10 + v[i]) % divisor;
        }
        
        return BigInt(remainder);
    }
    
    BigInt dividend = *this;
    BigInt divisor = other;
    while (dividend >= divisor)
    {
        dividend = dividend - divisor;
    }
    return dividend;
}


int main() 
{
    int space = 10;
    cout << "\a\nTestUnit:\n" << flush;
    cout << "User Name:" << flush;
    system("whoami");
    system("date");
    BigInt n1(25);
    BigInt s1("25");
    BigInt n2(1234);
    BigInt s2("1234");
    BigInt n3(n2);
    BigInt X(3000);
    BigInt Y(50);
    BigInt Z1(123);
    BigInt Z2("989345275647");
    BigInt Z3(X.fibo());
    BigInt imax = INT_MAX;
    BigInt big("9223372036854775807");

    cout << "n1(int)    :" << setw(space) << n1 << endl;
    cout << "s1(str)    :" << setw(space) << s1 << endl;
    cout << "n2(int)    :" << setw(space) << n2 << endl;
    cout << "s2(str)    :" << setw(space) << s2 << endl;
    cout << "n3(n2)     :" << setw(space) << n3 << endl;
    cout << "X.fibo(1234):" <<setw(space) << X.fibo() << endl;
    cout << "Y.fact(50)   :" << setw(space) << Y.fact() << endl;
    cout << "imax       :" << setw(space) << imax << endl;
    cout << "big        :" << setw(space) << big << endl;
    cout << "big.print(): "; big.print(); cout << endl;
    
    cout << n2 << "/" << n1 <<  " = " << n2/n1 <<" rem "<<n2%n1<<endl;
    cout << "fibo("<<X<<") = "<<X.fibo() << endl;
    cout << "fact("<<Y<<") = "<<Y.fact() << endl;

    bool printSteps = true;
    cout << "steps for collatz(" << Z1<<"):" << Z1.collatz(printSteps) << endl;

    printSteps = false;

    // 1348 steps per Wikipedia https://en.wikipedia.org/wiki/Collatz_conjecture
    cout << "steps for collatz(" << Z2<<"):"<< Z2.collatz(printSteps) << endl;

    cout << "steps for collatz(" << Z3<<"):"<< Z3.collatz(printSteps) << endl;

    cout << "10 + n1 = " << BigInt(10) + n1 << endl;
    cout << "n1 + 10 = " << n1 + BigInt(10) << endl;

    cout << "(n1 == s1)? --> "<<((n1==s1)?"true":"false")<<endl;
    cout << "n1++ = ?  --> before:"<<n1++<<" after:" << n1 << endl;
    cout << "++s1 = ?  --> before:"<<++s1<<" after:" << s1 << endl;

    cout << "s2 * big = ? --> "<< s2 * big << endl;
    cout << "big * s2 = ? --> "<< big * s2 << endl;

    cout << endl;
    system("date");

    return 0;
}

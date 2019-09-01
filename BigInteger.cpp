#include <iostream>
#include <vector>
#define f(i,a,b) for(int i=(int)a;i<=(int)b;i++)
#define rf(i,a,b) for(int i=(int)a;i>=(int)b;i--)
using namespace std;

class BigInteger
{
	public:
	vector<int> digit;

	BigInteger(string s)
	{
		int min_index;
		if(s[0]=='-')
		{
			digit.push_back(-1);
			min_index = 1;
		}
		else
		{
			digit.push_back(0);	
			min_index = 0;
		}

		rf(i,s.length()-1,min_index)
		{

			digit.push_back(s[i] - '0');
		}
		
	}

	BigInteger(int size)
	{
		digit = vector<int>(size,0);
	}

	
	BigInteger()
	{
	
	}	
	
public:

	void rprint(BigInteger B)	
	{
		f(i,0,B.size()- 1)
		{ 
			cout<<B.digit[i];
		}
		cout<<endl;
	}
public:
	 void print()
	{
		if(digit[0]==-1)
			cout<<"-";


		rf(i,size()-1,1)
		{ 
			cout<<digit[i];
		}

		cout<<endl;
	}
public:
	int size()
	{
		return digit.size();
	}


	int operator [] (int i)
	{
		return digit[i];
	}

};

std::ostream & operator << (ostream &out,  BigInteger b)
{
	string s="";
	if(b.digit[0]==-1)
		s.append("-");

	rf(i,b.size()-1,1)
		s = s.append(to_string(b.digit[i]));
	out<<s;
	return out;
}


BigInteger operator + ( BigInteger &op1, BigInteger &op2);


BigInteger operator - ( BigInteger op1, BigInteger op2)
{
	int op1size = op1.size();
	int op2size = op2.size();

	if(op1.size() < op2.size())
		op1.digit.resize(op2.size());

	if(op1.size() > op2.size())
		op2.digit.resize(op1.size());


 	BigInteger x = op1;
 	BigInteger y = op2;
 	bool both_neg = false;
	
	if(op1.digit[0]== 0 && op2.digit[0]==-1)
	 {
	 	y.digit[0] = 0;
	 	return x + y;
	 }
	else if(op1.digit[0]==-1 && op2.digit[0]==0)
	{
		y.digit[0] = -1;
		return x + y;
	}
	else if(op1.digit[0]==-1 && op2.digit[0]==-1)
	{
		both_neg = true;
	}

	BigInteger ans(1);
	int carry = 0,max = op1.size() > op2.size() ? op1.size() : op2.size();
	f(i,1, max-1)
	{
		int diff = op1.digit[i] - op2.digit[i] + carry;

		if(diff >= 0)
		{
			carry = 0;
		}
		else
		{
			diff += 10;
			carry = -1;
		}
		
		ans.digit.push_back(diff);
	}
	int last_digit = ans.digit.size()-1;
	//ans.print();
	


	if(carry == -1)
	{
	//	cout<<"Carry";
		//10's complement in reverse order
		f(i,1,last_digit)
		{
			ans.digit[i] = 9 - ans.digit[i];
		}
		
		BigInteger y("1");
		BigInteger x = ans;
		x.digit[0] = 0;
		
		//x.print();
		ans = x + y;
		ans.digit[0] = -1;
	}
	else
		ans.digit[0] = 0;

	if(both_neg)
	{
		ans.digit[0] = ans.digit[0] == -1 ? 0 : -1;
	}
	op1.digit.resize(op1size);
	op2.digit.resize(op2size);
	int i = ans.size()-1;
	while(i > 1 && ans[i]==0)
	{
		ans.digit.pop_back();
		i--;
	}
	
	return ans;
}


BigInteger operator + ( BigInteger &op1, BigInteger &op2)
{

	int op1size = op1.size();
	int op2size = op2.size();

	if(op1.size() < op2.size())
		op1.digit.resize(op2.size());

	if(op1.size() > op2.size())
		op2.digit.resize(op1.size());
	
	BigInteger ans (op1.digit.size());

	BigInteger x = op1;
 	BigInteger y = op2;

	if(op1.digit[0]==-1 && op2.digit[0]==-1)
		ans.digit[0] = -1;
	else if(op1.digit[0]==0 && op2.digit[0]==0)
		ans.digit[0] = 0;
	else if(op1.digit[0]==0 && op2.digit[0]==-1)
	{
		y.digit[0] = 0;
		return x - y;
	}
	else
	{
		x.digit[0] = 0;
		return y - x;
	}
	

	int last_digit = op2.digit.size()-1,carry=0;
	int max = op1.size() > op2.size() ? op1.size() : op2.size();
	f(i,1,max-1)
	{
		ans.digit[i] = op2.digit[i] + op1.digit[i] + carry;
		if(ans.digit[i] > 9)
		{
			ans.digit[i] = ans.digit[i] % 10;
			if(last_digit == i)
				ans.digit.push_back(1);
			else
				carry = 1; 
		}
		else
				carry = 0;
	}


	op1.digit.resize(op1size);
	op2.digit.resize(op2size);
	int i = ans.size()-1;
	while(i > 1 && ans[i]==0)
	{
		ans.digit.pop_back();
		i--;
	}
	
	return ans;
	
}

BigInteger operator * (BigInteger a, BigInteger b)
{
	int n = a.size();
	int m = b.size();
	
	BigInteger ans(m+n-1);

	if((a[0]==-1 && b[0]==0) || (a[0]==0 && b[0]==-1))
		ans.digit[0] = -1;

	int k=0;
	f(i,1,m-1)
	{
		k=i;
		f(j,1,n-1)
		{
			ans.digit[k] = ans[k] + a[j] * b[i];
			if(ans[k]>9)
			{
				int x = ans[k];
				ans.digit[k] = x%10;
				ans.digit[k+1] = ans[k+1] + (x/10);
			}
			k++;
		}
		//f(l,1,m+n-1)
		//	cout<<ans[l]<<" ";
		//cout<<endl;
	}
	int i = ans.size()-1;
	while(i > 1 && ans[i]==0)
	{
		ans.digit.pop_back();
		i--;
	}
	
	
	
	return ans;
}

bool isZero(BigInteger b)
{
	f(i,1,b.size()-1)
	{
		if(b[i]!=0)
			return false;
	}
	return true;
}



bool operator > ( BigInteger &op1, BigInteger &op2)
{
	BigInteger ans = op1 - op2;
	if(isZero(ans))
		return false;
	return (ans.digit[0] == 0);
}


bool operator == (BigInteger &op1, BigInteger &op2)
{
	BigInteger ans = op1 - op2;
	f(i,1,ans.digit.size()-1)
	{
		if(ans.digit[i] != 0)
			return false;
	}
	return true;
}





BigInteger divbyTwo(BigInteger op)
{
	BigInteger b = op;
	int carry = 0;
	rf(i,b.size()-1,1)
	{
		//cout<<b[i]<<":"<<carry<<endl;
		if(carry == 1)
			b.digit[i] = b[i]+10;
		
		if(b[i]%2 == 0)
			carry = 0;
		else
			carry = 1;
		
		b.digit[i] = b[i] / 2;
	}
	return b;
}

BigInteger mfastExpo(BigInteger a, BigInteger n)
{
	BigInteger one("1");
	
	if(isZero(n))
		return one;

	BigInteger temp = mfastExpo(a,divbyTwo(n));
	//cout<<"temp "<<temp<<endl;
	if(n[1]%2==0)
		return temp*temp;
	else
		return (temp*temp)*a;
}

BigInteger fastExpo(BigInteger a, BigInteger n)
{
	BigInteger ans = mfastExpo(a,n);
	if(n[1]%2!=0)
	{
		if(a[0] == -1)
		{
			ans.digit[0] = -1;
		}
	}
	return ans;

}

BigInteger findFact(BigInteger n)
{

	BigInteger fact("1"),one("1");
	while(!isZero(n))
	{
		fact = fact*n;
		n = n - one;
		cout<<n<<":"<<fact<<endl;
	}

	return fact;
}

BigInteger fastFact(BigInteger n)
{
	BigInteger sum("0"),fact("1"),zero("0"),n2,one("1"),two("2");
	if(n[1]%2!=0)
		n2 = n - one;
	else
		n2 = n;

	while(n2 > zero)
	{
		
		sum = sum + n2;
		fact = fact * sum;
		//cout<<sum<<":"<<endl;
		//cout<<fact<<"is fact"<<endl;
		n2 = n2 - two;
	}

	if(n[1] % 2!=0)
		fact=fact  * n;
	return fact;

}
BigInteger gcd(BigInteger x, BigInteger y)
{
	//cout<<"a : "<<a<<" b : "<<b<<endl;
	if(isZero(x))
		return y;
	if(isZero(y))
		return x;
	
	BigInteger a = x;
	BigInteger b = y;
	
	a.digit[0] = 0;
	b.digit[0] = 0;
	
	while(! (a == b))
	{		
		if(a>b)
		{
			BigInteger ten("10");
			int diff_digit = a.size() - b.size();
			if(diff_digit - 1 >= 0)			
				diff_digit--;
			
			BigInteger diff(to_string(diff_digit));
			//cout<<diff<<endl;
			BigInteger no = fastExpo(ten, diff);
			//0cout<<"a : "<<a<<" b : "<<b<<endl;
		//	cout<<no;
			a = a - (b*no);
		//	a = a-b;
		}
		else
		{
			BigInteger ten("10");
			int diff_digit = b.size() - a.size();
			if(diff_digit - 1 >= 0)			
				diff_digit--;
			BigInteger diff(to_string(diff_digit));
			BigInteger no = fastExpo(ten, diff);
			
			b = b - (a*no);
			
		}
		//cout<<"a : "<<a<<" b : "<<b<<endl;
	}
	//cout<<"a : "<<a<<" b : "<<b<<endl;
	return a;
}

int main()
{
	
	int test,k;
	string x,y;
	cin>>test;
	while(test-->0)
	{
		cin>>k;
		if(k==1)
		{
			cin>>x>>y;
			BigInteger a(x);
			BigInteger b(y);
			cout<<fastExpo(a,b)<<endl;
		}
		else if(k==2)
		{
			cin>>x>>y;			
			BigInteger a(x);
			BigInteger b(y);
			cout<<gcd(a,b)<<endl;
		}
		else
		{
			cin>>x;
			BigInteger a(x);			
			cout<<fastFact(a)<<endl;
		}

	}

	return 1;	
}





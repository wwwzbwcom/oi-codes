#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;

typedef unsigned u32;

struct mt_generator
{
	u32 mt[624];
	int p;

	inline mt_generator(u32 seed)
	{
		p = 0;
		mt[0] = seed;
		for (int i = 1; i < 624; i++)
			mt[i] = 0x6c078965 * (mt[i - 1] ^ (mt[i - 1] >> 30)) + i;
	}

	inline u32 next()
	{
		if (p == 0)
		{
			for (int i = 0; i < 624; i++)
			{
				u32 y = (mt[i] & 0x80000000) + (mt[(i + 1) % 624] & 0x7fffffff);
				mt[i] = mt[(i + 397) % 624] ^ (y >> 1);
				if (y & 1)
					mt[i] ^= 0x9908b0df;
			}
		}

		u32 y = mt[p];
		y ^= y >> 11;
		y ^= (y << 7) & 0x9d2c5680;
		y ^= (y << 15) & 0xefc60000;
		y ^= y >> 18;

		p = (p + 1) % 624;
		return y;
	}
};

struct prog_cmd
{
	char type;
	union
	{
		struct
		{
			int a;
		} input_data;
		struct
		{
			int a;
		} output_data;
		struct
		{
			char op;
			char type_a, type_b;
			int a, b, c;
		} calc_data;
		struct
		{
			char type_b;
			int b, c;
		} mov_data;
		struct
		{
			char type_c;
			int c, t;
		} if_data;
	};
};

bool token_to_int(const string &token, int *v)
{
	if (token == "0")
		*v = 0;
	else
	{
		int sp = token[0] == '-' ? 1 : 0;
		if ((int)token.size() <= sp || token[sp] == '0')
			return false;

		int res = 0;
		for (int i = sp; i < (int)token.size(); i++)
		{
			if ('0' <= token[i] && token[i] <= '9')
				res = res * 10 + token[i] - '0';
			else
				return false;
		}

		if (token[0] == '-')
			res = -res;

		char str[33];
		sprintf(str, "%d", res);

		if (token != str)
			return false;

		*v = res;
	}
	return true;
}

void put_var_info(int line_num, const string &token, int *v)
{
	if (token.size() == 1 && ('a' <= token[0] && token[0] <= 'z'))
		*v = token[0] - 'a';
	else
	{
		fprintf(stderr, "Expected a variable name but found \"%s\" at line #%d\n", token.c_str(), line_num);
		exit(1);
	}
}
void put_int_info(int line_num, const string &token, int *v)
{
	if (!token_to_int(token, v))
	{
		fprintf(stderr, "Expected a 32-bit integer but found \"%s\" at line #%d\n", token.c_str(), line_num);
		exit(1);
	}
}
void put_var_or_int_info(int line_num, const string &token, int *v, char *t)
{
	if (token.size() == 1 && ('a' <= token[0] && token[0] <= 'z'))
		*t = 'v', *v = token[0] - 'a';
	else
	{
		*t = 'i';
		if (!token_to_int(token, v))
		{
			fprintf(stderr, "Expected a variable name or a 32-bit integer but found \"%s\" at line #%d\n", token.c_str(), line_num);
			exit(1);
		}
	}
}

const int MaxN = 100000;
int n;
prog_cmd *prog;

mt_generator mt_gen(time(NULL));

void compile()
{
	ifstream fin("prog.txt");

	prog = new prog_cmd[MaxN + 1];

	string line;
	while (getline(fin, line))
	{
		n++;

		if (n == MaxN + 1)
		{
			fprintf(stderr, "The code is too long\n");
			exit(1);
		}

		int lp = 0;
		vector<string> tokens;
		while (true)
		{
			int p = line.find(' ', lp);
			if (p == -1)
			{
				tokens.push_back(line.substr(lp));
				break;
			}
			else
			{
				tokens.push_back(line.substr(lp, p - lp));
				lp = p + 1;
			}
		}

		if (tokens.empty())
		{
			fprintf(stderr, "Empty statement at line #%d\n", n);
			exit(1);
		}

		if (tokens[0] == "input")
		{
			if (tokens.size() != 2)
			{
				fprintf(stderr, "Invalid input statement at line #%d\n", n);
				exit(1);
			}
			prog[n].type = 'I';
			put_var_info(n, tokens[1], &prog[n].input_data.a);
		}
		else if (tokens[0] == "output")
		{
			if (tokens.size() != 2)
			{
				fprintf(stderr, "Invalid output statement at line #%d\n", n);
				exit(1);
			}
			prog[n].type = 'O';
			put_var_info(n, tokens[1], &prog[n].output_data.a);
		}
		else if (tokens.size() == 3 && tokens[1] == "=")
		{
			prog[n].type = '=';
			put_var_info(n, tokens[0], &prog[n].mov_data.c);
			put_var_or_int_info(n, tokens[2], &prog[n].mov_data.b, &prog[n].mov_data.type_b);
		}
		else if (tokens.size() == 5 && tokens[1] == "=")
		{
			prog[n].type = 'c';
			if (tokens[3] == "+")
				prog[n].calc_data.op = '+';
			else if (tokens[3] == "-")
				prog[n].calc_data.op = '-';
			else if (tokens[3] == "*")
				prog[n].calc_data.op = '*';
			else if (tokens[3] == "/")
				prog[n].calc_data.op = '/';
			else if (tokens[3] == "%")
				prog[n].calc_data.op = '%';
			else if (tokens[3] == "==")
				prog[n].calc_data.op = 'e';
			else if (tokens[3] == "!=")
				prog[n].calc_data.op = 'n';
			else if (tokens[3] == "<")
				prog[n].calc_data.op = '<';
			else if (tokens[3] == ">")
				prog[n].calc_data.op = '>';
			else if (tokens[3] == "<=")
				prog[n].calc_data.op = 'l';
			else if (tokens[3] == ">=")
				prog[n].calc_data.op = 'g';
			else
			{
				fprintf(stderr, "Invalid assign statement at line #%d\n", n);
				exit(1);
			}
			put_var_info(n, tokens[0], &prog[n].calc_data.c);
			put_var_or_int_info(n, tokens[2], &prog[n].calc_data.a, &prog[n].calc_data.type_a);
			put_var_or_int_info(n, tokens[4], &prog[n].calc_data.b, &prog[n].calc_data.type_b);
		}
		else if (tokens[0] == "if")
		{
			if (tokens.size() != 4 || tokens[2] != "goto")
			{
				fprintf(stderr, "Invalid if statement at line #%d\n", n);
				exit(1);
			}
			prog[n].type = 'f';
			put_var_or_int_info(n, tokens[1], &prog[n].if_data.c, &prog[n].if_data.type_c);
			put_int_info(n, tokens[3], &prog[n].if_data.t);
		}
		else
		{
			fprintf(stderr, "Invalid statement at line #%d\n", n);
			exit(1);
		}
	}
}

void run()
{
	int var[26];
	for (int i = 0; i < 26; i++)
		var[i] = 0;

	int tot = 0;

	int p = 1;
	while (p <= n)
	{
		tot++;

		if (tot > 1000000)
		{
			fprintf(stderr, "Too many instructions\n");
			exit(1);
		}

		if (p < 1)
		{
			fprintf(stderr, "Runtime Error\n");
			exit(1);
		}

		int a, b, c;
		switch (prog[p].type)
		{
			case 'I':
				scanf("%d", &var[prog[p].input_data.a]);
				p++;
				break;
			case 'O':
				printf("%d\n", var[prog[p].output_data.a]);
				p++;
				break;
			case '=':
				var[prog[p].mov_data.c] = prog[p].mov_data.type_b == 'v' ? var[prog[p].mov_data.b] : prog[p].mov_data.b;
				p++;
				break;
			case 'f':
				if (prog[p].if_data.type_c == 'v' ? var[prog[p].if_data.c] : prog[p].if_data.c)
					p = prog[p].if_data.t;
				else
					p++;
				break;
			case 'c':
				a = prog[p].calc_data.type_a == 'v' ? var[prog[p].calc_data.a] : prog[p].calc_data.a;
				b = prog[p].calc_data.type_b == 'v' ? var[prog[p].calc_data.b] : prog[p].calc_data.b;
				c = prog[p].calc_data.c;

				bool wrong = mt_gen.next() < (1u << 29);

				switch (prog[p].calc_data.op)
				{
					case '+':
						var[c] = a + b;
						if (wrong)
							var[c] = mt_gen.next();
						break;
					case '-':
						var[c] = a - b;
						if (wrong)
							var[c] = mt_gen.next();
						break;
					case '*':
						var[c] = a * b;
						if (wrong)
							var[c] = mt_gen.next();
						break;
					case '/':
						if (b == 0)
						{
							fprintf(stderr, "Runtime Error");
							exit(1);
						}
						var[c] = a / b;
						if (wrong)
							var[c] = mt_gen.next();
						break;
					case '%':
						if (b == 0)
						{
							fprintf(stderr, "Runtime Error");
							exit(1);
						}
						var[c] = a % b;
						if (wrong)
							var[c] = mt_gen.next();
						break;
					case 'e':
						var[c] = a == b;
						if (wrong)
							var[c] = !var[c];
						break;
					case 'n':
						var[c] = a != b;
						if (wrong)
							var[c] = !var[c];
						break;
					case '<':
						var[c] = a < b;
						if (wrong)
							var[c] = !var[c];
						break;
					case '>':
						var[c] = a > b;
						if (wrong)
							var[c] = !var[c];
						break;
					case 'l':
						var[c] = a <= b;
						if (wrong)
							var[c] = !var[c];
						break;
					case 'g':
						var[c] = a >= b;
						if (wrong)
							var[c] = !var[c];
						break;
				}

				p++;
				break;
		}
	}
}

int main()
{
	compile();
	run();
	return 0;
}

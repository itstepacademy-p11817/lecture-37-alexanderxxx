#include <iostream>
#include <cstdlib>
#include <utility>
#include <time.h>
#include <cstring>
#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include <stdarg.h>

typedef struct
{
	char books[100][100] = { { NULL } };
	int ind[100] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
}lib_t;

typedef struct
{
	char login[20] = { NULL };
	char password[20] = { NULL };
	char book[5][100] = { { NULL } };
}user_t;

typedef struct
{
	char login[6] = "admin";
	char password[4] = "252";
}admin_t;




void open(lib_t* library, user_t user_massive[])
{

	FILE* file1 = fopen("save", "rb");
	if (file1 == NULL)
	{
		//fclose(file1);
		return;
	}
	else
	{
		FILE* file1 = fopen("save", "rb");

		//fseek(file1, 0, SEEK_END);
		//int size1 = ftell(file1);
		fseek(file1, 0, SEEK_SET);

		int code1 = fread(library, sizeof(lib_t), 1, file1);
		int code2 = fread(user_massive, sizeof(user_t), 10, file1);

		std::cout << code1 << " " << code2;
		fclose(file1);
	}
}

void save(lib_t* library, user_t user_massive[])
{
	FILE* file1 = fopen("save", "wb");

	int code1 = fwrite(library, sizeof(lib_t), 1, file1);
	int code2 = fwrite(user_massive, sizeof(user_t), 10, file1);
	std::cout << code1 << " " << code2;
	fclose(file1);
	//rename("save_temp", "save");
}


void admin(lib_t* library, user_t user_massive[])
{
	int g = -1;
	while (true)
	{
		std::cout << "1 - Add book, 2 - list book, 3 - user filter 0 - exit: ";
		std::cin >> g;
		if (g == 1)
		{
			for (int i = 0; i < 100; i++)
			{
				if (*library->books[i] != 0)
				{
					continue;
				}
				else
				{
					std::cout << "New book: ";
					std::cin >> library->books[i];
					break;
				}
			}
		}
		else if (g == 2)
		{
			for (int i = 0; i < 100; i++)
			{
				if (library->ind[i] >= 0)
				{
					std::cout << library->books[i] << " - " << user_massive[library->ind[i]].login << '\n';
				}
				else if (*library->books[i] != 0)
				{
					std::cout << library->books[i] << '\n';
				}
			}
		}
		else if (g == 3)
		{
			for (int i = 0; i < 10; i++)
			{
				if (user_massive[i].login != 0)
				{
					std::cout << i << "  " << user_massive[i].login << '\n';
				}
			}
			int index = -1;
			std::cout << "User index: ";
			std::cin >> index;
			if (user_massive[index].login != 0)
			{
				for (int i = 0; i < 5; i++)
				{
					if (user_massive[index].book[i] != 0)
					{
						std::cout << user_massive[index].book[i] << '\n';
					}
				}
			}
		}
		else if (g == 0)
		{
			return;
		}
	}
}


void user(user_t* user, lib_t* library, int user_index)
{
	int g = -1;
	while (true)
	{
		std::cout << "1 - List books, 2 - take book, 3 - return book, 0 - exit: ";
		std::cin >> g;
		if (g == 1)
		{
			for (int i = 0; i < 100; i++)
			{
				if (library->ind[i]<0 && *library->books[i] != 0)
				{
					std::cout << library->books[i] << '\n';
				}
			}
		}
		else if (g == 2)
		{
			for (int i = 0; i < 100; i++)
			{
				if (library->ind[i]<0 && *library->books[i] != 0)
				{
					std::cout << i << "  " << library->books[i] << '\n';
				}
			}
			int index = -1, flag = 0;
			std::cout << "Book index: ";
			std::cin >> index;
			for (int i = 0; i < 5; i++)
			{
				if (*user->book[i] == 0 && library->ind[index]<0)
				{
					strcpy(user->book[i], library->books[index]);
					library->ind[index] = user_index;
					flag = 1;
					break;
				}
			}
			if (flag == 0)
			{
				std::cout << "invalid index or maximum books!";
			}
		}
		else if (g == 3)
		{
			for (int i = 0; i < 5; i++)
			{
				if (user->book[i] != 0)
				{
					std::cout << i << "  " << user->book[i];
				}
			}
			int index = -1;
			std::cout << "Book index: ";
			std::cin >> index;
			if (user->book[index] != 0)
			{
				for (int i = 0; i < 100; i++)
				{
					if (strcmp(library->books[i], user->book[index]) == 0)
					{
						library->ind[i] = -1;
						strcpy(user->book[index], "000\0");
						break;
					}
				}
			}
			else
			{
				std::cout << "Invalid index!" << '\n';
			}
		}
		else if (g == 0)
		{
			return;
		}
	}
}



int main()
{
	setlocale(LC_ALL, "Russian");
	int g = 0;

	admin_t adm;
	user_t user_massive[10];
	lib_t library;

	//std::fill(library.ind[0], library.ind[99], -1);

	//for (int i = 0; i < 100; i++)
	//{
	//	library.ind[i] = -1;
	//}

	//std::cout << sizeof(library) << '\n';
	//std::cout << sizeof(user_massive) << '\n';

	open(&library, user_massive);

	while (true)
	{
		save(&library, user_massive);
		std::cout << "1 - Login, 2 - New user, 0 - exit: ";
		std::cin >> g;
		char login[20], password[20];
		int user_index = -1;
		if (g == 1)
		{
			std::cout << "Login: ";
			std::cin >> login;
			std::cout << "Password: ";
			std::cin >> password;

			if (strcmp(login, adm.login) == 0 && strcmp(password, adm.password) == 0)
			{
				std::cout << "Admin account!" << '\n';
				admin(&library, user_massive);
				continue;
			}

			for (int i = 0; i < 10; i++)
			{
				if (strcmp(user_massive[i].login, login) == 0 && strcmp(user_massive[i].password, password) == 0)
				{
					user_index = i;
					break;
				}
			}
			if (user_index < 0)
			{
				std::cout << "Access denied!" << '\n';
			}
			else
			{
				std::cout << "Welcome, " << user_massive[user_index].login << '\n';
				user(&user_massive[user_index], &library, user_index);
			}
		}
		else if (g == 2)
		{
			for (int i = 0; i < 10; i++)
			{
				if (user_massive[i].login[0] == NULL)
				{
					user_index = i;
					break;
				}
			}
			if (user_index < 0)
			{
				std::cout << "Maximum users!" << '\n';
			}
			else
			{
				std::cout << "Login: ";
				std::cin >> user_massive[user_index].login;
				std::cout << "Password: ";
				std::cin >> user_massive[user_index].password;
				std::cout << "User " << user_massive[user_index].login << " created" << '\n';
			}
		}
		else if (g == 0)
		{
			break;
		}
	}




	system("pause");
	return 0;
}
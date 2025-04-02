//Main.cpp
#include <iostream>
#include "Socket.h"

using namespace std;

int main()
{
	int nChoice;
	char menuu[225] = "\n1-Bruschetta with tomatoes - 350 $ \n 2-Tom Yum with shrimp - 680 $ \n 3-Ribeye steak - 1 900 $ \n 4-New York cheesecake - 520 $ \n 5-Coffee (Espresso) - 250 $";
	int port = 24242; //выбираем порт
	int check = 0;
	string ipAddress = "127.0.0.1"; //Адрес сервера
	char receiveMessage[MAXSTRLEN];
	char sendMessage[MAXSTRLEN];
	cout << "1) Start server" << endl;
	cout << "2) Connect to server" << endl;
	cout << "3) Exit" << endl;
	cin >> nChoice;
	if (nChoice == 1)
	{
		ServerSocket server;
		cout << "Starting server..." << endl;
		//Запускаем сервер
		server.StartHosting(port);
		while (true)
		{
			cout << "\tWaiting..." << endl;
			//Получаем данные от клиента
			//и сохраняем в переменной receiveMessage
			server.ReceiveData(receiveMessage, MAXSTRLEN);
			cout << "Received: " << receiveMessage << endl;
			if (strcmp(receiveMessage, "menu") == 0) {
				strcpy_s(sendMessage, menuu);
				server.SendData(sendMessage);
			}
			else if (strcmp(receiveMessage, "1") == 0) {
				server.SendData("You will pay - 350$");
				check += 350;
			}
			else if (strcmp(receiveMessage, "2") == 0) {
				server.SendData("You will pay - 680$");
				check += 680;
			}
			else if (strcmp(receiveMessage, "3") == 0) {
				server.SendData("You will pay - 1900$");
				check += 1900;
			}
			else if (strcmp(receiveMessage, "4") == 0) {
				server.SendData("You will pay - 520$");
				check += 520;
			}
			else if (strcmp(receiveMessage, "5") == 0) {
				server.SendData("You will pay - 250$");
				check += 250;
			}
			else if (strcmp(receiveMessage, "check") == 0) {
				char ch[50];
				sprintf_s(ch, "%d", check);
				server.SendData(ch);
			}
			else {
				server.SendDataMessage();
			}
			while (strcmp(receiveMessage, "cont") == 0) {
			
			}
			//Отправляем данные клиенту
			//Если есть сообщение "end", завершаем работу
			if (strcmp(receiveMessage, "end") == 0 ||
				strcmp(sendMessage, "end") == 0)
				break;
		}
	}
	else if (nChoice == 2)
	{
		//cout << "Enter an IP address: " << endl;
		////Запрашиваем IP сервера
		//cin >> ipAddress;
		ClientSocket client;
		//подключаемся к серверу
		client.ConnectToServer(ipAddress.c_str(), port);
		while (true)
		{
			//отправляем сообщение
			client.SendDataMessage();
			cout << "\tWaiting" << endl;
			//получаем ответ
			client.ReceiveData(receiveMessage, MAXSTRLEN);
			cout << "Received: " << receiveMessage << endl;
			if (strcmp(receiveMessage, "end") == 0 ||
				strcmp(sendMessage, "end") == 0)
				break;
		}
		//Закрываем соединение
		client.CloseConnection();
	}
	else if (nChoice == 3)
		return 0;
}











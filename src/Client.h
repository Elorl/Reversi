
#ifndef REVERSI_CLIENT_H
#define REVERSI_CLIENT_H


class Client {
public:
    Client(const char *serverIP, int serverPort);
    void connectToServer();
    int sendExercise(int arg1, char op, int arg2);
private:
    const char *serverIP;
    int serverPort;
    int clientSocket;
};


#endif //REVERSI_CLIENT_H

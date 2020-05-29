#include "Client.h"

Client& Client::Create()
{
	return *(new Client());
}

bool Client::ConnectServer()
{
	pipe = new ClientPipe(pipeName + std::to_string(GetCurrentProcessId()));
	return pipe->ConnectServer();
}

bool Client::DisconnectServer()
{
	return pipe->DisconnectServer();
}

Employee Client::ReadEmployee(int employeeNum, bool isReadOnly)
{
	Employee employee;

	Message in;
	in.type = Type::Success;

	Message out;
	out.type = Type::Read;
	out.buffer = nullptr;

	memcpy(out.buffer, &employeeNum, sizeof(int));
	memcpy(out.buffer + sizeof(int), &isReadOnly, sizeof(bool));

	pipe->SendNewMessage(out);
	pipe->ReceiveMessage(in);

	memcpy(&employee, in.buffer, sizeof(employee));
	return employee;
}

void Client::WriteEmployee(Employee employee)
{
	Message in;
	in.type = Type::Success;

	Message out;
	out.type = Type::Write;
	out.buffer = nullptr;

	memcpy(out.buffer, &employee, sizeof(Employee));
	pipe->SendNewMessage(out);
	pipe->ReceiveMessage(in);
}

void Client::SendReleaseMessage(int employeeNum)
{
	Message in;
	in.type = Type::Success;

	Message out;
	out.type = Type::Release;
	out.buffer = nullptr;

	memcpy(out.buffer, &employeeNum, sizeof(int));
	pipe->SendNewMessage(out);
	pipe->ReceiveMessage(in);
}

void Client::SendEndMessage()
{
	Message out;
	out.type = Type::End;
	pipe->SendNewMessage(out);
}

Client::~Client()
{
	delete pipe;
}

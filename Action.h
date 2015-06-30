#include <strsafe.h>
#include <string>
#include <sstream> 
#include <stdlib.h>
#include "stdafx.h"
#include "BodyBasics.h"
#include "NetworkClient.h"

using namespace std;

class Action
{
public:
	Action(void(*callback_function)(const char*));
	~Action();
	void activationFunc(IBody* pBody, D2D1_POINT_2F* jointPoints, INT64 nTime);
	void Action::isTracked();

private:
	void(*mySend)(const char* s); //pointer to send function
};


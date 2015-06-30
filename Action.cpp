#include "Action.h"
#include "dictionary.h"



Action::Action(void(*callback_function)(const char*))
{
	mySend = callback_function;
}


Action::~Action(){}


void Action::activationFunc(IBody* pBody, D2D1_POINT_2F* jointPoints, INT64 nTime) {

	/* Indicates weather the previous iteration was characterized as a 'gesture' or not;
	* The activation function is responsible to define what it treats as a valid gesture
	*/
	static boolean isPrevMotion = false;
	static INT64 prevTime = 0;

	HandState leftHandState = HandState_Unknown;
	HandState rightHandState = HandState_Unknown;

	pBody->get_HandLeftState(&leftHandState);
	pBody->get_HandRightState(&rightHandState);


	//right hand is closed
	if (rightHandState == HandState_Closed || leftHandState == HandState_Closed) {

		std::ostringstream os;

		//send data
		os << "(" << jointPoints[JointType_HandRight].x << "," << jointPoints[JointType_HandRight].y << ")";
		mySend(os.str().c_str());

		isPrevMotion = true;
		prevTime = nTime;
	}
	else {
		// Gesture is complete
		if (isPrevMotion && (nTime - prevTime) >(INT64)MOTION_SMOOTH_CONST) {
			mySend(GESTURE_END);
			isPrevMotion = false;
		}
	}

}

void Action::isTracked() {
	mySend(SWITCH_SCREEN);
}

#include "Timer.h"
#include <time.h>

Timer::Timer(){

}

Timer::Timer(int delai){
	this->delai = delai;
	timerValue = clock();
}

void Timer::setDelai(int delai){
	this->delai = delai;
}

int Timer::getDelai(int delai) const {
	return 0;
}

bool Timer::estPret(){
	bool retour = false;

	if (clock() >= timerValue + delai) {
		retour = true;
		timerValue = clock();
	}

	return retour;
}

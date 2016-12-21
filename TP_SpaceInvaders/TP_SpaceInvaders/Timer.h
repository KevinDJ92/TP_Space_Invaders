#pragma once

class Timer {
public:
	int timerValue;
	int delai;

	Timer();

	Timer(int delai);
	void setDelai(int delai);

	int getDelai(int delai) const;

	bool estPret();

};
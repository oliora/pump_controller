#pragma once

class temperature
{
private:
	char currentTemp[3];
	bool checkTemp;
public:
	temperature();
	temperature(bool checkTemp);
	int getInt();
	char *getString();
	bool isCheckTemp();
};

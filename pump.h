#pragma once

#define LED_RED BIT0
#define LED_GREEN BIT6
#define PUMP_RELAY BIT6

class pump
{
private:
	bool pumpIsWorking;
public:
	int pumpWorkTime;
	int pumpMaxWorkTime;
	pump();
	pump(int pumpMaxWorkTime);
	void startPump();
	void stopPump();
	bool isPumpWorking();
	void blinkGreen();
};
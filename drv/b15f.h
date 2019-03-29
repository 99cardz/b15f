#ifndef B15F_H
#define B15F_H

#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <cstdint>
#include <vector>

#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <termios.h>
#include "usart.h"
#include "driverexception.h"
#include "timeoutexception.h"

class B15F
{
private:
	B15F(void); // privater Konstruktor
public:
	// Grundfunktionen
	void init(void);
	void reconnect(void);
	void discard(void);
	bool testConnection(void);
	bool testIntConv(void);
	std::vector<std::string> getBoardInfo(void);
	
	// Board Befehle
	bool digitalWrite0(uint8_t);
	bool digitalWrite1(uint8_t);
	uint8_t digitalRead0(void);
	uint8_t digitalRead1(void);
	bool analogWrite0(uint16_t);
	bool analogWrite1(uint16_t);
	uint16_t analogRead(uint8_t);
	bool analogSequence(uint8_t channel_a, uint16_t* buffer_a, uint32_t offset_a, uint8_t channel_b, uint16_t* buffer_b, uint32_t offset_b, uint16_t start, int16_t delta, uint16_t count);
	
	/**
	 * Lässt den Treiber für eine angegebene Zeit pausieren
	 * \param ms Verzögerung in Millisekunden
	 */
	void delay_ms(uint16_t ms);
	
	/**
	 * Lässt den Treiber für eine angegebene Zeit pausieren
	 * \param us Verzögerung in Microsekunden
	 */
	void delay_us(uint16_t us);
	
	/**
	 * Liefert eine Referenz zur aktuellen Treiber-Instanz
	 * @throws DriverException
	 */
	static B15F& getInstance(void);

private:
	uint16_t timeout = 1000; // ms
	uint16_t block_timeout = 1; // ms
	USART usart;

	static B15F* instance;
	


	// CONSTANTS
	const std::string PRE = "[B15F] ";
	const std::string SERIAL_DEVICE = "/dev/ttyUSB0";
	constexpr static uint8_t  MSG_OK = 0xFF;
	constexpr static uint8_t  MSG_FAIL = 0xFE;
	constexpr static uint16_t RECONNECT_TIMEOUT = 64; // ms
	constexpr static uint8_t  RECONNECT_TRIES = 3;
	constexpr static uint32_t BAUDRATE = 115200;
	
	// REQUESTS
	constexpr static uint8_t RQ_DISC = 0;
	constexpr static uint8_t RQ_TEST = 1;
	constexpr static uint8_t RQ_INFO = 2;
	constexpr static uint8_t RQ_INT  = 3;
	constexpr static uint8_t RQ_BA0  = 5;
	constexpr static uint8_t RQ_BA1  = 6;
	constexpr static uint8_t RQ_BE0  = 7;
	constexpr static uint8_t RQ_BE1  = 8;
	constexpr static uint8_t RQ_AA0  = 9;
	constexpr static uint8_t RQ_AA1  = 10;
	constexpr static uint8_t RQ_ADC  = 11;
	constexpr static uint8_t RQ_ADC_DAC_STROKE  = 12;
};

#endif // B15F_H

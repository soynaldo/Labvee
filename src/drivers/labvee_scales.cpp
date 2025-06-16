// #include <Arduino.h>

// #define SHIFTIN_WITH_SPEED_SUPPORT(data,clock,order) shiftIn(data,clock,order)


// void begin(byte dout, byte pd_sck, byte gain) {
// 	PD_SCK = pd_sck;
// 	DOUT = dout;

// 	pinMode(PD_SCK, OUTPUT);
// 	pinMode(DOUT, INPUT);

// 	set_gain(gain);
// }

// bool is_ready() {
// 	return digitalRead(DOUT) == LOW;
// }

// void set_gain(byte gain) {
// 	switch (gain) {
// 		case 128:		// channel A, gain factor 128
// 			GAIN = 1;
// 			break;
// 		case 64:		// channel A, gain factor 64
// 			GAIN = 3;
// 			break;
// 		case 32:		// channel B, gain factor 32
// 			GAIN = 2;
// 			break;
// 	}

// }

// long read() {

// 	// Wait for the chip to become ready.
// 	wait_ready();

// 	// Define structures for reading data into.
// 	unsigned long value = 0;
// 	uint8_t data[3] = { 0 };
// 	uint8_t filler = 0x00;

// 	// Disable interrupts.
// 	noInterrupts();

// 	// Pulse the clock pin 24 times to read the data.
// 	data[2] = SHIFTIN_WITH_SPEED_SUPPORT(DOUT, PD_SCK, MSBFIRST);
// 	data[1] = SHIFTIN_WITH_SPEED_SUPPORT(DOUT, PD_SCK, MSBFIRST);
// 	data[0] = SHIFTIN_WITH_SPEED_SUPPORT(DOUT, PD_SCK, MSBFIRST);

// 	// Set the channel and the gain factor for the next reading using the clock pin.
// 	for (unsigned int i = 0; i < GAIN; i++) {
// 		digitalWrite(PD_SCK, HIGH);
// 		digitalWrite(PD_SCK, LOW);
// 	}

// 	// Enable interrupts again.
// 	interrupts();

// 	// Replicate the most significant bit to pad out a 32-bit signed integer
// 	if (data[2] & 0x80) {
// 		filler = 0xFF;
// 	} else {
// 		filler = 0x00;
// 	}

// 	// Construct a 32-bit signed integer
// 	value = ( static_cast<unsigned long>(filler) << 24
// 			| static_cast<unsigned long>(data[2]) << 16
// 			| static_cast<unsigned long>(data[1]) << 8
// 			| static_cast<unsigned long>(data[0]) );

// 	return static_cast<long>(value);
// }

// void wait_ready(unsigned long delay_ms) {
// 	while (!is_ready()) {
// 		delay(delay_ms);
// 	}
// }

// bool wait_ready_retry(int retries, unsigned long delay_ms) {
// 	int count = 0;
// 	while (count < retries) {
// 		if (is_ready()) {
// 			return true;
// 		}
// 		delay(delay_ms);
// 		count++;
// 	}
// 	return false;
// }

// bool wait_ready_timeout(unsigned long timeout, unsigned long delay_ms) {
// 	unsigned long millisStarted = millis();
// 	while (millis() - millisStarted < timeout) {
// 		if (is_ready()) {
// 			return true;
// 		}
// 		delay(delay_ms);
// 	}
// 	return false;
// }

// long read_average(byte times) {
// 	long sum = 0;
// 	for (byte i = 0; i < times; i++) {
// 		sum += read();
// 		delay(0);
// 	}
// 	return sum / times;
// }

// double get_value(byte times) {
// 	return read_average(times) - OFFSET;
// }

// float get_units(byte times) {
// 	return get_value(times) / SCALE;
// }

// void tare(byte times) {
// 	double sum = read_average(times);
// 	set_offset(sum);
// }

// void set_scale(float scale) {
// 	SCALE = scale;
// }

// float get_scale() {
// 	return SCALE;
// }

// void set_offset(long offset) {
// 	OFFSET = offset;
// }

// long get_offset() {
// 	return OFFSET;
// }

// void power_down() {
// 	digitalWrite(PD_SCK, LOW);
// 	digitalWrite(PD_SCK, HIGH);
// }

// void power_up() {
// 	digitalWrite(PD_SCK, LOW);
// }
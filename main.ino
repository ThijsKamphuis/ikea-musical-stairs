

#define TRIG 2
#define ECHO 3

long echo_ms;
int dist;

void TriggerSensors() {
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);    
}

void setup() {
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, OUTPUT);

    Serial.begin(9600);
}

void loop () {
    TriggerSensors();
    echo_ms = pulseIn(ECHO, HIGH);
    dist = echo_ms * 0.034 / 2;

    Serial.println(dist);
    delay(50);
}

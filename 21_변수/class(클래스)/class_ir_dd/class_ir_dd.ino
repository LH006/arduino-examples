// TODO pin 설정
#include <IRremote.h>    // IR receiver
#include <Servo.h>



// servo moter
#define ANGLE_MAX 179
#define SERVO_PIN 9

// dc motor
//#define SPEED_MAX 255 // TODO check
#define RELAY_PIN 3

// IR Receiver
const unsigned int IR_RECEIVER_PIN = 11;
const unsigned int BAUD_RATE = 9600;
IRrecv ir_receiver(IR_RECEIVER_PIN);
decode_results results;

//================================================================
class ServoMoter {
    private:
        int m_angle;

    public:
        ServoMoter() : m_angle(ANGLE_MAX/2) {
        }

        void init() {
            m_angle = ANGLE_MAX/2;
            Serial.print("init");
            Serial.println(m_angle);
        }

        int turnLeft() {
            if (m_angle > 20) {
                m_angle = m_angle - 10;
            }
            return m_angle;
        }

        int turnRight() {
            if (m_angle < 160 ) {
                m_angle = m_angle + 10;
            }
            return m_angle;
        }

        int turnStright() {
            if ( m_angle != ANGLE_MAX/2) {
                m_angle = ANGLE_MAX/2;
            }
            return m_angle;
        }
};
//=================================================================

class DcMoter {
    private:
        //int m_speed;  // TODO check
        int m_motorState;
        long m_lastDebounceTime;
        long m_debounceDelay;
    public:

        DcMoter() : m_motorState(LOW), m_lastDebounceTime(0), m_debounceDelay(5000) {
        }

        int run(int inputStatus) {

            if (inputStatus == LOW) {
                // run start
                m_lastDebounceTime = millis();
            }

            m_motorState = inputStatus;

            return m_motorState;
        }

        int safeStop() {
            // safe gaurd
            if ((millis() - m_lastDebounceTime) > m_debounceDelay) {
                m_motorState = HIGH;
            }
            return m_motorState;
        }
};

// Controller from IR receiver
ServoMoter m_servo;
DcMoter m_dc;

class Controller {
    private:
        bool m_durtyServo;
        bool m_durtyDc;
        int m_servoValue;
        int m_dcValue;

    public:
        Controller() : m_durtyServo(false), m_durtyDc(false), m_servoValue(ANGLE_MAX/2), m_dcValue(LOW) {
        }

        void run(const decode_results* results) {
            //   NEC only

            int servoValue = m_servoValue;
            int dcValue = m_dcValue;
            if (results->value == 0xFD20DF) {
                Serial.println("Turn left");
               // servo = ServoMoter::getInstance().turnLeft();
               servoValue = m_servo.turnLeft();
            } else if (results->value == 0xFD609F) {
                Serial.println("Turn right");
                servoValue = m_servo.turnRight();
            } else if (results->value == 0xFDA05F) {
                Serial.println("Turn stright");
                servoValue = m_servo.turnStright();
            } else if (results->value == 0xFD807F) {
                Serial.println("Go");
                dcValue = m_dc.run(LOW);
            }
            else if (results->value == 0xFD00FF) {
                Serial.println("Stop");
                dcValue = m_dc.run(HIGH);
            }
            /*
             * Addition key
             1 = FD08F7
             2 = FD8877
             3 = FD48B7
             */

            if (servoValue != m_servoValue) {
                m_durtyServo = true;
                m_servoValue = servoValue;
            }

            if (dcValue != m_dcValue) {
                m_durtyDc = true;
                m_dcValue = dcValue;
            }
        }

        bool isDurtyDc(int &dcValue) {
            if (m_durtyDc) {
                m_durtyDc = false;
                dcValue = m_dcValue;
                return true;
            }
            return false;
        }

        bool isDurtyServo(int &servoValue) {
            if (m_durtyServo) {
                m_durtyServo = false;
                servoValue = m_servoValue;
                return true;
            }
            return false;
        }

        void isSafeStop() {
            int dcTmp;
            dcTmp = m_dc.safeStop();
            if (dcTmp != m_dcValue) {
                Serial.println("Safe stop on");
                m_dcValue = dcTmp;
                m_durtyDc = true;
            }
        }
};


Controller m_control;
Servo serv;         // servo moter
//==========================================================
void setup() {
    // IR receiver
    Serial.begin(BAUD_RATE);
    ir_receiver.enableIRIn();

    // servo motor
    serv.attach(SERVO_PIN);

    m_servo.init();

    // dc motor
    pinMode(RELAY_PIN, OUTPUT);

    digitalWrite(RELAY_PIN, HIGH);
}
//===========================================================
void loop() {

    if (ir_receiver.decode(&results)) {
        int servo, dc;
        m_control.run(&results);

        if (m_control.isDurtyServo(servo)) {
            Serial.print("Servo : ");
            Serial.println(servo);
            serv.write(servo);
        }
        if (m_control.isDurtyDc(dc)) {
            digitalWrite(RELAY_PIN, dc);
        }
        m_control.isSafeStop();

        ir_receiver.resume();
    }
}




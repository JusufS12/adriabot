#include <AFMotor.h>
#include <HCSR04.h>
#include <HUSKYLENS.h>
#include <Servo.h>

// privremeno da se lakse promini
#define KUT_OTVORI_RUKU 0       // kalibriraj da se ruka skroz otvori
#define KUT_ZATVORI_RUKU 90     // kalibriraj da se ruka skroz zatvori

#define SS 25
#define LS 47
#define DS 46

#define SPEED 200

#define BCRVENA  30    // promini kad dodas botun
#define BPLAVA 32      // promini kad dodas botun
#define BZELENA  28    // promini kad dodas botun

#define SERVO 10     // promini kad dodas servo za ruku
#define OTVORI 0
#define ZATVORI 1

void lineFollower();
void birajBoju();
void pCrvena();
void pPlava();
void pZelena();
int prepoznajBoje();
bool ultraZvucni();
void ruka(bool stanje);


Servo servo;

AF_DCMotor dM4(4);
AF_DCMotor lM3(3);

HCSR04 zvucni(22, 23);

HUSKYLENS huskylens;


void setup() {
  // debug
  Serial.begin(9600);
  // turn on motor
  lM3.setSpeed(SPEED);
  dM4.setSpeed(SPEED - 50);
  lM3.run(RELEASE);
  dM4.run(RELEASE);
  // postavi botun
  pinMode(BCRVENA, INPUT_PULLUP);
  pinMode(BPLAVA, INPUT_PULLUP);
  pinMode(BZELENA, INPUT_PULLUP);
  // postavi huskylens
  Wire.begin();
  huskylens.begin(Wire);
  // servo
  servo.attach(SERVO);
  ruka(OTVORI);
}

void loop() {
  // while (ultraZvucni()) {
  //   // Serial.println("Dobar");
  // }

  // lineFollower();

  // birajBoju();

  // ruka(OTVORI);
  // delay(1000);
  // ruka(ZATVORI);
  // delay(1000);

  // prepoznajBoje();
}


void lineFollower() {
  if (digitalRead(SS)) {
    if (!digitalRead(LS) && !digitalRead(DS)) {
      // vozi ravno
      lM3.run(FORWARD);
      dM4.run(FORWARD);
    }

    if (digitalRead(LS) && !digitalRead(DS)) {
      // ostro livo
      lM3.run(BACKWARD);
      dM4.run(FORWARD);
    }

    if (!digitalRead(LS) && digitalRead(DS)) {
      // ostro desno
      lM3.run(FORWARD);
      dM4.run(BACKWARD);
    }

    if (digitalRead(LS) && digitalRead(DS)) {
      // stani
      lM3.run(RELEASE);
      dM4.run(RELEASE);
    }
  } else {
    if (digitalRead(LS) && !digitalRead(DS)) {
      // livo
      lM3.run(RELEASE);
      dM4.run(FORWARD);
    }

    if (!digitalRead(LS) && digitalRead(DS)) {
      // desno
      lM3.run(FORWARD);
      dM4.run(RELEASE);
    }

    if (!digitalRead(LS) && !digitalRead(DS)) {
      // nazad
      lM3.run(BACKWARD);
      dM4.run(BACKWARD);
    }

    // if (digitalRead(LS) && digitalRead(DS)) {
    //   // naprid
    //   lM3.run(FOWARD);
    //   dM4.run(FOWARD);
    // }
  }
}


void birajBoju() {
  while (1) {
    if (!digitalRead(BCRVENA)) {
      // crvena
      Serial.println("Crveni");
      pCrvena();
    }
    if (!digitalRead(BPLAVA)) {
      //plava
      Serial.println("Plavi");
      pPlava();
    }
    if (!digitalRead(BZELENA)) {
      //zelena
      Serial.println("Zeleni");
      pZelena();
    }
  }
}


void pCrvena() {
  return;
}

void pPlava() {
  return;
}

void pZelena() {
  return;
}


int prepoznajBoje() {
  // huskylens
  // stavi funkciju u if statement u loopu
  huskylens.request();
  if (huskylens.available()) {
    HUSKYLENSResult result = huskylens.read();
    if (result.ID == 1) {
      // crvena
      Serial.println("Prepoznata crvena");
      return 1;
    }
    else if (result.ID == 2) {
      // plava
      Serial.println("Prepoznata plava");
      return 2;
    }
    else if (result.ID == 3) {
      // zelena
      Serial.println("Prepoznata zelena");
      return 3;
    }
    else {
      Serial.println("Prepoznata boja nije definirana");
      return -1;
    }
  }
}


bool ultraZvucni() {
  // Serial.println(zvucni.dist());
  if (zvucni.dist() > 6 || !zvucni.dist()) {
    Serial.println("[+] Ultrazvucni: reazmak dovoljan.");
    return true;
  }
  else {
    Serial.println("[-] Ultrazvucni: rezmak nedovoljan!");
    return false;
  }
}


void ruka(bool stanje) {
  if (!servo.attached()) {
    Serial.println("Failed, no servo attached!");
    return;
  }

  if (stanje) {
    servo.write(KUT_ZATVORI_RUKU);
  }
  else {
    servo.write(KUT_OTVORI_RUKU);
  }
}

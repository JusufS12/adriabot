#include <AFMotor.h>
#include <HCSR04.h>
#include <HUSKYLENS.h>

#define SS 25
#define LS 47
#define DS 46

#define SPEED 250
#define BCRVENA -1      // promini kad dodas botun
#define BPLAVA -1      // promini kad dodas botun
#define BZELENA  -1      // promini kad dodas botun

void lineFollower();
void birajBoju();
void pCrvena();
void pPlava();
void pZelena();

AF_DCMotor dM4(4);
AF_DCMotor lM3(3);

HCSR04 zvucni(22, 23);

HUSKYLENS huskylens;

void setup() {
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
}

void loop() {

  // if (zvucni.dist() > 6 || !zvucni.dist()) {
  //   lineFollower();
  // }
  // else {
  //   lM3.run(RELEASE);
  //   dM4.run(RELEASE);
  // }
  lineFollower();
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
  // risi se break i stavi procedure za odredjenu boju
  while (1) {
    if (BCRVENA)
      //crvena
      pCrvena();
    if (BPLAVA)
      //plava
      pPlava();
    if (BZELENA)
      //zelena
      pZelena();
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
      return 1;
    }
    else if (result.ID == 2) {
      // plava
      return 2;
    }
    else if (result.ID == 3) {
      // zelena
      return 3;
    }
    else {
      return -1;
    }
  }
}

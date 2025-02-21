unsigned long currentTime = 0;  //numéro étudiant 6308958 donc   5    8
const int nbrePin = 4;
const int ledPins[nbrePin] = { 8, 9, 10, 11 };
int pinButton = 2;
int valeurPotentiometre;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Ton code ici
  for (int i = 0; i < nbrePin; i++) {
    // Initialisation des DEL en sortie
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(pinButton, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  currentTime = millis();
  int valeurPotentiometre = analogRead(A1);

  potentiometre(valeurPotentiometre);
  boutton(currentTime, valeurPotentiometre);
}


void potentiometre(int valeurPotentiometre) {

  int Pin_allume = map(valeurPotentiometre, 0, 1023, 0, nbrePin);
  for (int i = 0; i < nbrePin; i++) {

    if (i <= Pin_allume) {

      digitalWrite(ledPins[i], HIGH);

    } else {

      digitalWrite(ledPins[i], LOW);
    }
  }
}

void boutton(unsigned long currentTime, int valeurPotentiometre) {
  static int etatPrecedent = HIGH;             // État initial cohérent avec INPUT_PULLUP
  static int etat = HIGH;                      // État stable du bouton
  const int delai = 50;                        // Délai anti-rebond en ms
  static unsigned long dernierChangement = 0;  // Dernier changement d'état

  int etatPresent = digitalRead(pinButton);  // Lecture de l'état du capteur

  if (etatPresent != etatPrecedent) {  // Si l'état change
    dernierChangement = millis();      // Mise à jour du temps
  }

  if ((millis() - dernierChangement) > delai && etatPresent != etat) {
    etat = etatPresent;
    if (etat == LOW) {
      printFunction(valeurPotentiometre);
    }
  }
  etatPrecedent = etatPresent;
}
void printFunction(int valeurPotentiometre) {

  int caseTableau = 20;
  int valueProgressBar = map(valeurPotentiometre, 0, 1023, 0, 100);
  int valeur_convertie = map(valueProgressBar, 0, 100, 0, caseTableau);


  Serial.print(valueProgressBar);
  Serial.print("% [");

  for (int i = 0; i < caseTableau; i++) {

    if (i <= valeur_convertie) {
      Serial.print("@");

    } else {
      Serial.print(("."));
    }
  }
  Serial.println("]");
}
/*
  testNobleWarrior.cpp
  Ryan Kawahara
  Association: Noble - Warrior
  Test code for hw04
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Warrior {
      friend ostream& operator<<(ostream& os, const Warrior& outputWarrior);
    
     private:
          string name;
          double warriorStrength;
          bool alreadyHired;

     public:
          Warrior(const string& nameWarrior, double strengthWarrior): name(nameWarrior), warriorStrength(strengthWarrior) {alreadyHired = false;}
          
          // checks if Warrior is hired
          bool checkHired() const {return alreadyHired;}
          // reflects Warrior hired
          void pledgeAllegiance() {alreadyHired = true;}
          // reflects Warrior fired
          void endAllegiance() {alreadyHired = false;}
          // kills Warrior
          void kill() {warriorStrength = 0;}
          // reduces Warrior strength when it wins
          void loseStrength(double killRatio) {warriorStrength -= warriorStrength * killRatio;}
          // getter for Warrior name
          string getName() const {return name;}
          // getter for Warrior strength
          double getStrength() const {return warriorStrength;}

     // output operator for Warriors
     friend ostream& operator<<(ostream& os, const Warrior& outputWarrior) {
          os << outputWarrior.name << ": " << outputWarrior.warriorStrength;
          return os;
     }    
};

class Noble {

     private:
          string name;
          vector<Warrior*> warriorRoster;
          bool isAlive;
          double nobleStrength;

     friend ostream& operator<<(ostream& os, const Noble& outputNoble);
     
     public:
     Noble( const string& nobleName):name(nobleName) {
          isAlive = true; 
          nobleStrength = 0;}

     // getter for Noble name
     string getName() const {return name;}

     // finds Warrior in roster and returns index
     size_t findWarrior (const Warrior &searchingWarrior) {
          for (size_t i = 0; i < warriorRoster.size(); ++i) {
               if ((warriorRoster[i]->getName()) ==
                searchingWarrior.getName()) {
                    return i;
               };
          }
          return warriorRoster.size();
     }

     // adds Warrior to warriorRoster
     void hire( Warrior &newWarrior) {
          if (isAlive) {
               if (newWarrior.checkHired() == false){
                    newWarrior.pledgeAllegiance();
                    Warrior* warriorPtr = &newWarrior;
                    warriorRoster.push_back(warriorPtr);
               }
               else {
                    cerr << newWarrior.getName() << 
                    " has already been hired." << endl;
               }
          }
          else {
               cerr << "Dead nobles cannot hire." << endl;
          }
     }

     // fires Warrior by removing from warriorRoster
     void fire(Warrior firedWarrior) {
          if (isAlive) {
               size_t cursor = this->findWarrior(firedWarrior);
               size_t endCursor = warriorRoster.size()-1;
               if (cursor == warriorRoster.size()) {
                    cerr << "That warrior is not employed be you." << endl;
               }
               else {
                    cout << "You don't work for me anymore " 
                    << firedWarrior.getName() << "! -- " << this->getName() 
                    << "." << endl;
                    // removes warrior from roster while maintaining order
                    while (cursor < endCursor) {
                         Warrior *swapHelper = warriorRoster[cursor];
                         warriorRoster[cursor] = warriorRoster[endCursor];
                         warriorRoster[endCursor] = swapHelper;
                         cursor += 1;
                         endCursor -= 1;
                    }
                    warriorRoster.pop_back();
               }
          }
          else {
               cerr << "Dead nobles cannot fire." << endl;
          }
     }

     // kills all Warriors in roster
     void killWarriors(){
          for (size_t i=0;i<warriorRoster.size();++i) {
               if (warriorRoster[i]!=nullptr){
                warriorRoster[i]->kill();
               }
          }
     }
     // applies battle damage to all warriors in roster
     void dealBattleDamage(double battleDamage){
          // iterates through warriorRoster
          for (size_t i=0;i<warriorRoster.size();++i) {
               if (warriorRoster[i]!=nullptr){
                warriorRoster[i]->loseStrength(battleDamage);
               }
          }
     }

     // calculates strength of noble's army by adding all up
     double calculateStrength() {
          double nobleStrength = 0;
          // iterates through warriorRoster
          for (size_t i = 0; i < warriorRoster.size(); ++i) {
               nobleStrength += warriorRoster[i]->getStrength();
          }
          return nobleStrength;
     }

     // determines outcomes during battle based on combating nobles' strength
     void battle(Noble &nobleOpponent){
          double myStrength = this->calculateStrength();
          double opponentStrength = nobleOpponent.calculateStrength();
          cout << name << " battles " << nobleOpponent.name << endl;
          if ((!isAlive) && (!nobleOpponent.isAlive)) {
               cout << "OH NO! They're both dead! Yuck!" << endl;
          }
          else if ((!isAlive) || (!nobleOpponent.isAlive)) {
               if (!isAlive) {
                    cout << "He's dead, " << nobleOpponent.name << endl;
               }
               else if (!nobleOpponent.isAlive) {
                    cout << "He's dead, " << name << endl;
               }
          }
          else if (opponentStrength > myStrength) {
               cout << nobleOpponent.name << "defeats " << name;
               double defeatRatio = myStrength / opponentStrength;
               isAlive = false;
               this->killWarriors();
               nobleOpponent.dealBattleDamage(defeatRatio);
          }
          else if (myStrength == opponentStrength) {
               cout << "Mutual Annihilation: " << name << " and " 
               << nobleOpponent.name << " die at each other's hands." << endl;
               this -> killWarriors();
               nobleOpponent.killWarriors();
               isAlive = false;
               nobleOpponent.isAlive = false;
          }
          else if (myStrength > opponentStrength) {
               cout << name << " defeats " << nobleOpponent.name << endl;
               double defeatRatio = opponentStrength / myStrength;
               nobleOpponent.isAlive = false;
               nobleOpponent.killWarriors();
               this->dealBattleDamage(defeatRatio);
          }
     }

     // output operator for Nobles
     friend ostream& operator<<(ostream& os, const Noble& outputNoble) {
     os << outputNoble.name << " has an army of " << outputNoble.warriorRoster.size() << endl;
     // iterates through warrior Roster to output data
     for (size_t i=0;i<outputNoble.warriorRoster.size();++i) {
               if (outputNoble.warriorRoster[i] != nullptr){
                    os << "\t" << *(outputNoble.warriorRoster[i]);
                    if (i<outputNoble.warriorRoster.size()-1){
                         os << endl;
                    }
               }
     }
     return os;
     };
};

int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");
	
    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);
	
    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);

	
    cout << "==========\n"
         << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";

     art.fire(cheetah);



    cout << art << endl;
     cout << lance << endl;

	
    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "==========\n"
         << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";
}

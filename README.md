# OOPHW4
Assignment for NYU CS


Homework 4
Focus:
Classes,
Pointers,
Association

**Problem:**
We will [continue to] model a game of medieval times. Our world is filled with not only warriors but also nobles. Nobles don't have much to do except do battle with each other. (We'll leave the feasting and other entertainments for add-ons.) Warriors don't have much to do except hire out to a noble and fight in his behalf. Of course the nobles are pretty wimpy themselves and will lose if they don't have warriors to defend them. How does all this work?

Warriors start out with a specified strength.
A battle between nobles is won by the noble who commands the stronger army.
The army's strength is simply the combined strengths of all its warriors.
A battle is to the death. The losing noble dies as does his warriors.
The winner does not usually walk away unscarred. All his men lose a portion of their strength equal to the ratio of the enemy army's combined strength to their army's. If the losing army had a combined strength that was 1/4 the size of the winning army's, then each soldier in the winning army will have their own strength reduced by 1/4. (Yes, strength will need to be a double.)

**Hiring and Firing**
Warriors are hired and fired by Nobles. Lack of adequate labor laws, have left the Warriors without the ability to quit, nor even to have a say on whether or not a Noble can hire them.
However it is possible that an attempt to hire or fire may fail. Naturally the methods should not "fail silently". Instead, they will return true or false depending on whether they succeed or not.
A Warrior can only be employed by one Noble at a time and cannot be hired away if he is already employed.
As noted below, Nobles who are dead can neither hire nor fire anyone. (Note this will implicitly prevent dead Warriors from being hired.)
When a warrior is fired, he is no longer part of the army of the Noble that hired him. He is then free to be hired by another Noble.

**Death**
It's a sad topic, but one we do have to address.

People die when they lose a battle, whether they are a Nobles or Warriors.
Nobles who are dead are in no position to hire or fire anyone. Any attempt by a dead Lord to hire someone will simply fail and the Warrior will remain unhired.
However curiously, as has been seen before, Nobles can declare battle even though they are dead.
Note that when a Noble is created he does not have any strength. At the same time he is obviously alive. So lack of strength and being dead are clearly not equivalent.

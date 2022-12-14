#include <Arduino.h>

// Song data as 2D array of [note, duration]
// Note: 1 is a C4, 24 is a B6, etc. 0 is a rest (no sound) 
// Duration: note/rest time in milliseconds

typedef struct {
  uint8_t note;
  uint16_t duration;
} note_t;

// Last christmas:
const note_t last_christmas[] = {{17,737},{0,64},{17,438},{0,93},{15,108},{0,427},{10,60},{0,206},{17,193},{0,73},{17,202},{0,65},{19,161},{0,107},{15,578},{0,222},{12,191},{0,75},{12,165},{0,97},{17,214},{0,51},{17,198},{0,70},{19,180},{0,354},{15,571},{0,225},{12,64},{0,204},{14,247},{0,20},{15,266},{0,0},{14,208},{0,60},{12,880},{0,455},{19,681},{0,120},{17,806},{0,261},{12,77},{0,191},{19,197},{0,66},{20,194},{0,72},{19,166},{0,101},{17,697},{0,376},{15,63},{0,202},{14,246},{0,21},{15,207},{0,58},{14,63},{0,207},{14,412},{0,120},{15,90},{0,446},{14,218},{0,318},{10,936}};
const note_t jingle[] = {{20,105},{0,233},{20,1},{0,0},{20,1},{0,168},{20,121},{0,217},{20,113},{0,55},{19,90},{0,248},{19,66},{0,103},{19,87},{0,251},{19,84},{0,84},{17,309},{0,29},{19,108},{0,60},{17,143},{0,195},{12,381},{0,127},{10,129},{0,39},{10,92},{0,76},{13,63},{0,105},{15,74},{0,95},{17,198},{0,140},{19,71},{0,97},{17,158},{0,180},{12,540},{0,137},{15,360},{0,148},{17,328},{0,10},{19,79},{0,90},{17,119},{0,219},{13,368},{0,140},{13,148},{0,360},{13,116},{0,52},{10,137},{0,201},{12,76},{0,92},{13,95},{0,243},{15,354},{0,153},{17,338},{0,169},{15,121},{0,47},{10,100},{0,238},{12,74},{0,95},{13,105},{0,233},{15,296},{0,211},{15,1},{0,0},{15,1},{0,168},{15,137},{0,201},{15,84},{0,84},{17,227},{0,280},{17,296},{0,211},{19,119},{0,219},{17,111},{0,58},{15,105},{0,233},{20,582}};
const note_t i_want[] = {{1,428},{0,0},{5,428},{0,0},{8,428},{0,0},{12,214},{0,0},{13,428},{0,0},{12,428},{0,0},{10,428},{0,0},{8,642},{0,0},{15,428},{0,0},{13,428},{0,0},{13,214},{0,0},{12,428},{0,0},{13,428},{0,0},{12,428},{0,0},{10,214},{0,0},{8,857},{0,428},{10,428},{0,0},{13,428},{0,0},{15,214},{0,0},{17,428},{0,0},{15,428},{0,0},{13,428},{0,0},{10,642},{0,0},{6,428},{0,0},{9,214},{0,0},{13,642},{0,0},{15,214},{0,0},{16,428},{0,0},{15,428},{0,0},{11,428},{0,0},{9,642},{0,0},{13,428},{0,0},{15,428},{0,0},{12,428},{0,0},{13,214},{0,0},{10,428},{0,0},{12,428},{0,0},{9,1071},{0,0},{13,428},{0,0},{15,428},{0,0},{12,428},{0,0},{13,214},{0,0},{10,428},{0,0},{12,428},{0,0},{9,1071},{0,0},{8,428},{0,0},{10,428},{0,0},{13,214},{0,0},{20,428},{0,0},{18,428},{0,0},{20,214},{0,0},{18,428},{0,428},{20,107},{0,107},{20,214},{0,0},{17,428},{0,0},{15,428},{0,0},{13,428},{0,0},{10,428},{0,0},{9,428},{0,0},{15,857},{0,0},{17,428},{0,0},{13,2142}};
const note_t rockin[] = {{14,260},{0,17},{14,121},{0,17},{14,399},{0,17},{16,399},{0,17},{16,399},{0,17},{14,399},{0,17},{14,260},{0,17},{16,538},{0,17},{14,260},{0,17},{14,121},{0,17},{18,399},{0,17},{16,399},{0,17},{12,399},{0,17},{9,260},{0,17},{6,243},{0,312},{2,121},{0,156},{2,121},{0,17},{1,260},{0,17},{2,538},{0,17},{16,260},{0,17},{16,121},{0,17},{16,399},{0,17},{18,399},{0,17},{18,399},{0,17},{16,399},{0,17},{16,260},{0,17},{18,538},{0,17},{16,260},{0,17},{16,121},{0,17},{14,399},{0,17},{15,399},{0,17},{16,399},{0,17},{12,399},{0,17},{11,208},{0,104},{7,121},{0,156},{7,121},{0,17},{6,260},{0,17},{7,538},{0,121},{14,260},{0,17},{14,121},{0,17},{14,399},{0,17},{16,399},{0,17},{16,399},{0,17},{14,399},{0,17},{14,260},{0,17},{16,538},{0,17},{14,260},{0,17},{14,121},{0,17},{18,399},{0,17},{16,399},{0,17},{12,399},{0,17},{9,260},{0,17},{6,243},{0,312},{2,121},{0,156},{2,121},{0,17},{1,260},{0,17},{2,538},{0,17},{16,260},{0,17},{16,121},{0,17},{16,399},{0,17},{18,399},{0,17},{18,399},{0,17},{16,399},{0,17},{16,260},{0,17},{18,538},{0,17},{16,260},{0,17},{16,121},{0,17},{14,399},{0,17},{15,399},{0,17},{16,399},{0,17},{6,399},{0,17},{7,1145}};
const note_t feliz[] = {{10,217},{0,11},{15,316},{0,143},{14,213},{0,16},{15,225},{0,4},{12,428},{0,31},{10,62},{0,167},{8,71},{0,158},{7,62},{0,167},{3,69},{0,390},{10,229},{0,689},{12,213},{0,16},{17,299},{0,160},{15,193},{0,35},{12,229},{0,0},{10,423},{0,35},{10,67},{0,162},{8,76},{0,153},{7,71},{0,158},{10,76},{0,383},{3,229},{0,689},{10,229},{0,0},{15,292},{0,167},{14,205},{0,23},{15,229},{0,0},{12,500},{0,189},{8,170},{0,59},{12,311},{0,148},{12,205},{0,23},{10,263},{0,196},{10,244},{0,215},{10,203},{0,26},{8,282},{0,177},{8,229},{0,0},{5,344}};
const note_t wish_merry[] = {{3,394},{0,0},{8,197},{0,197},{8,193},{0,4},{10,197},{0,0},{8,197},{0,0},{7,185},{0,12},{5,234},{0,160},{5,201},{0,193},{5,361},{0,32},{10,197},{0,197},{10,189},{0,8},{12,197},{0,0},{10,197},{0,0},{8,197},{0,0},{7,394},{0,0},{3,189},{0,205},{3,275},{0,119},{12,164},{0,230},{12,197},{0,0},{13,197},{0,0},{12,197},{0,0},{10,185},{0,12},{8,337},{0,57},{5,283},{0,111},{3,106},{0,90},{3,185},{0,12},{5,341},{0,53},{10,304},{0,90},{7,234},{0,160},{8,596},{0,193},{3,378},{0,16},{8,271},{0,123},{8,320},{0,74},{8,312},{0,82},{7,686},{0,102},{7,353},{0,41},{8,337},{0,57},{7,365},{0,28},{5,394},{0,0},{3,670},{0,119},{10,263},{0,131},{12,394},{0,0},{10,127},{0,69},{10,185},{0,12},{8,131},{0,65},{8,197},{0,0},{15,357},{0,37},{3,263},{0,131},{3,119},{0,78},{3,160},{0,37},{5,378},{0,16},{10,349},{0,45},{7,312},{0,82},{8,629}};

const note_t silent[] = {{8,768},{0,7},{10,166},{0,10},{8,497},{0,0},{5,1406},{0,127},{8,812},{0,15},{10,171},{0,7},{8,486},{0,2},{5,1156},{0,346},{15,937},{0,39},{15,502},{0,23},{12,1276},{0,250},{13,947},{0,33},{13,476},{0,18},{8,489},{0,10},{6,489},{0,10},{8,489},{0,23},{10,937},{0,41},{10,440},{0,62},{13,750},{0,59},{12,182},{0,2},{10,442},{0,49},{8,825},{0,10},{10,114},{0,57},{8,455},{0,44},{8,174},{0,2},{5,914},{0,416},{10,966},{0,57},{10,411},{0,52},{13,760},{0,59},{12,177},{0,2},{10,447},{0,49},{8,763},{0,59},{10,184},{0,5},{8,492},{0,257},{5,1005},{0,242},{15,953},{0,44},{15,505},{0,2},{18,786},{0,7},{15,182},{0,20},{12,343},{0,153},{13,1221},{0,135},{13,145},{0,26},{17,1111},{0,375},{13,500},{0,7},{8,473},{0,5},{5,500},{0,0},{8,820},{0,0},{6,179},{0,13},{3,486},{0,2},{1,1666}};
const note_t funky[] = {{13, 99}, {0, 251}, {13, 137}, {0, 213}, {11, 140}, {0, 210}, {13, 128}, {0, 573}, {8, 193}, {0, 509}, {8, 169}, {0, 181}, {13, 152}, {0, 199}, {18, 172}, {0, 178}, {17, 137}, {0, 213}, {13, 143}, {0, 1612}, {13, 102}, {0, 248}, {13, 125}, {0, 225}, {11, 134}, {0, 216}, {13, 128}, {0, 573}, {8, 169}, {0, 532}, {8, 146}, {0, 204}, {13, 149}, {0, 201}, {18, 178}, {0, 172}, {17, 155}, {0, 196}, {13, 146}, {0, 1610}, {1, 172}, {0, 178}, {1, 172}, {0, 178}, {1, 172}, {0, 178}, {1, 348}, {0, 2}, {5, 524}, {0, 178}, {5, 172}, {0, 178}, {5, 172}, {0, 178}, {8, 172}, {0, 178}, {8, 172}, {0, 178}, {8, 348}, {0, 2}, {17, 524}, {0, 178}, {15, 172}, {0, 178}, {13, 351}, {0, 351}, {13, 96}, {0, 254}, {13, 131}, {0, 219}, {11, 140}, {0, 210}, {13, 125}, {0, 576}, {8, 152}, {0, 550}, {8, 161}, {0, 190}, {13, 140}, {0, 210}, {18, 166}, {0, 184}, {17, 155}, {0, 196}, {13, 146}};
const note_t groove[] = {{1,666},{0,128},{4,72},{0,201},{6,436},{0,106},{4,442},{0,95},{3,604},{0,190},{8,408},{0,140},{6,106},{0,156},{8,364},{0,179},{1,666},{0,128},{4,72},{0,201},{6,436},{0,106},{4,442},{0,95},{3,604},{0,190},{8,408},{0,140},{6,106},{0,156},{8,364},{0,173},{13,420},{0,649},{8,263},{0,16},{11,240},{0,28},{13,263},{0,0},{15,190},{0,352},{11,145},{0,392},{6,397},{0,128},{8,252},{0,16},{11,235},{0,33},{11,173},{0,638},{20,246},{0,28},{18,756},{0,39},{16,257},{0,22},{15,778},{0,16},{22,263},{0,16},{20,800},{0,806},{22,84},{0,184},{22,196},{0,336},{8,263},{0,16},{11,240},{0,28},{13,263},{0,0},{15,184},{0,358},{11,145},{0,392},{6,528},{0,0},{8,252},{0,16},{11,235},{0,33},{11,173},{0,638},{20,246},{0,28},{18,756},{0,39},{16,257},{0,22},{15,778},{0,16},{22,263},{0,16},{20,800}};
const note_t rickroll[] = {};
const note_t mario[] = {{13,150},{0,0},{13,150},{0,149},{13,150},{0,149},{9,150},{0,0},{13,300},{0,0},{16,299},{0,300},{4,300},{0,300},{9,449},{0,0},{4,149},{0,300},{1,449},{0,0},{6,299},{0,0},{8,300},{0,0},{7,149},{0,0},{6,300},{0,0},{4,199},{0,0},{13,200},{0,0},{16,200},{0,0},{18,299},{0,0},{14,150},{0,0},{16,149},{0,150},{13,299},{0,0},{9,150},{0,0},{11,149},{0,0},{8,300},{0,149},{9,450},{0,0},{4,150},{0,299},{1,450},{0,0},{6,299},{0,0},{8,300},{0,0},{7,150},{0,0},{6,300},{0,0},{4,199},{0,0},{13,199},{0,0},{16,200},{0,0},{18,299},{0,0},{14,150},{0,0},{16,150},{0,150},{13,299},{0,0},{9,150},{0,0},{11,150},{0,0},{8,300},{0,449},{16,150},{0,0},{15,150},{0,0},{14,149},{0,0},{12,300},{0,0},{13,150},{0,150},{5,149},{0,0},{6,150},{0,0},{9,150},{0,150},{6,150},{0,0},{9,149},{0,0},{11,150},{0,300},{16,150},{0,0},{15,149},{0,0},{14,150},{0,0},{12,300},{0,0},{13,150},{0,149},{21,150},{0,150},{21,149},{0,0},{21,600},{0,300},{16,149},{0,0},{15,150},{0,0},{14,149},{0,0},{12,300},{0,0},{13,149},{0,150},{5,149},{0,0},{6,149},{0,0},{9,150},{0,149},{6,150},{0,0},{9,149},{0,0},{11,150},{0,299},{12,300},{0,150},{11,299},{0,150},{9,599}};
const note_t march[] = {{5, 281}, {0, 206}, {5, 307}, {0, 197}, {5, 312}, {0, 171}, {1, 244}, {0, 125}, {8, 67}, {0, 60}, {5, 416}, {0, 165}, {1, 287}, {0, 169}, {8, 85}, {0, 51}, {5, 747}, {0, 422}, {12, 377}, {0, 216}, {12, 371}, {0, 208}, {12, 386}, {0, 223}, {13, 257}, {0, 165}, {8, 95}, {0, 69}, {4, 416}, {0, 156}, {1, 248}, {0, 176}, {8, 85}, {0, 79}, {5, 514}, {0, 655}, {17, 457}, {0, 131}, {5, 297}, {0, 161}, {5, 116}, {0, 34}, {17, 371}, {0, 164}, {16, 318}, {0, 153}, {15, 98}, {0, 49}, {14, 140}, {0, 6}, {13, 101}, {0, 45}, {14, 132}, {0, 468}, {6, 113}, {0, 183}, {11, 389}, {0, 198}, {10, 322}, {0, 118}, {9, 83}, {0, 57}, {8, 113}, {0, 26}, {7, 89}, {0, 60}, {8, 128}, {0, 475}, {1, 98}, {0, 192}, {4, 355}, {0, 230}, {1, 337}, {0, 116}, {8, 73}, {0, 61}, {5, 398}, {0, 177}, {1, 330}, {0, 140}, {8, 79}, {0, 49}, {5, 741}};

const note_t * songs[] = {
  last_christmas,
  jingle,
  i_want, 
  rockin,
  feliz,
  wish_merry,
  silent,
  funky,
  groove,
  rickroll, 
  mario, 
  march
};

size_t sn = sizeof(note_t);

const uint32_t song_lengths[] = {
  sizeof(last_christmas)/sn,
  sizeof(jingle)/sn,
  sizeof(i_want)/sn,
  sizeof(rockin)/sn,
  sizeof(feliz)/sn,
  sizeof(wish_merry)/sn,
  sizeof(silent)/sn,
  sizeof(funky)/sn,
  sizeof(groove)/sn,
  sizeof(rickroll)/sn,
  sizeof(mario)/sn,
  sizeof(march)/sn
};


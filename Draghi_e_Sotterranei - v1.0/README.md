# Draghi e Sotterranei
**Draghi e Sotterranei** è un action RPG in 2D sviluppato nel corso del 2021.

## Ambientazione
Il gioco è ambientato in un mondo medieval-fantasy nel quale i sotterranei sono popolati da ostili mostri. L'obiettivo del nostro eroe è sconfiggerli tutti!

## Il gioco
### Vittoria
Colpisci i nemici e abbattili tutti per vincere. Sblocca nuovi Achievement compiendo particolari azioni.
![alt text](Resources/Images/GIF/GIF-Win.gif)

### Game Over
Se i nemici ti colpiranno troppe volte perderai tutti i tuoi punti ferita e perderai
![alt text](Resources/Images/GIF/GIF-GameOver.gif)

### Editor per mappa
Utilizza l'editor per creare nuove mappe tramite un fornito set di celle.
![alt text](Resources/Images/GIF/GIF-Tile.gif)

### Editor per nemici
Completa i tuoi livelli aggiungendo i nemici da sconfiggere.
![alt text](Resources/Images/GIF/GIF-EnemyEditor.gif)

### Dungeon con stanze multiple
Crea sotterranei con stanze multiple e nemici più forti per aumentare la difficoltà.
![alt text](Resources/Images/GIF/GIF-Dungeon.gif)

## Comandi
### In gioco
Muovi l'eroe per schivare i nemici che ti inseguono:
- premi W per andare in su
- premi S per andare in giù
- premi D per andare a destra
- premi A per andare a sinistra

Colpisci i nemici nel range dell'eroe per abbatterli premendo col tasto sinistro del mouse su di loro.

### In editor
#### Mappa
Crea la mappa usando il tasto sinistro del mouse e cliccando sulla cella da posizionare
- premi C per impostare celle di collisione su cui i personaggi collideranno
- premi freccia.su (o freccia.giù) per modificare il tipo di cella*
- premi L per impedire di posizionare nuove celle su altre già posizionate
- premi Save per salvare la tua mappa e Load per caricarla
- premi pag.sù per passare all'editor riservato ai nemici

#### Nemici
Usa il tasto sinistro del mouse per posizionare le celle di spawn dei nemici
- premi 1 (o shift+1) per far salire (o scendere) il numero corrispondente alla tipologia di nemico**
- premi 2 (o shift+2) per far salire (o scendere) il numero corrispondente alla quantità di nemici 
- premi 3 (o shift+3) per far salire (o scendere) il tempo di respawn
- premi 4 (o shift+4) per far salire (o scendere) la massima distanza di movimento di un nemico dalla sua cella di spawn
- premi pag.giù per tornare a quello di modifica della mappa

#### Tipi di cella*
- **0** = cella calpestabile
- **2** = cella in primo piano rispetto ai personaggi

#### Tipi di nemici**
- **0** = Mummia
- **1** = Scorpione
- **2** = Avvoltoio
- **3** = Iena
- **4** = Serpente
- **5** = Non Morto
- **6** = Big Bloated
- **7** = Centipede
- **8** = Tartaruga da Guerra

## Vecchia repository di archivio
https://github.com/ippo1997/Fani-Ippoliti
